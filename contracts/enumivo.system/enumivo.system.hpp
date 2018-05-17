/**
 *  @file
 *  @copyright defined in enumivo/LICENSE.txt
 */
#pragma once

#include <enumivo.system/native.hpp>
#include <enumivolib/asset.hpp>
#include <enumivolib/time.hpp>
#include <enumivolib/privileged.hpp>
#include <enumivolib/singleton.hpp>
#include <enumivo.system/exchange_state.hpp>

#include <string>

namespace enumivosystem {

   using enumivo::asset;
   using enumivo::indexed_by;
   using enumivo::const_mem_fun;
   using enumivo::block_timestamp;

   struct enumivo_parameters : enumivo::blockchain_parameters {
      uint64_t          max_ram_size = 64ll*1024 * 1024 * 1024;

      // explicit serialization macro is not necessary, used here only to improve compilation time
      ENULIB_SERIALIZE_DERIVED( enumivo_parameters, enumivo::blockchain_parameters, (max_ram_size) )
   };

   struct enumivo_global_state : enumivo_parameters {
      uint64_t free_ram()const { return max_ram_size - total_ram_bytes_reserved; }

      uint64_t             total_ram_bytes_reserved = 0;
      int64_t              total_ram_stake = 0;

      block_timestamp      last_producer_schedule_update;
      uint64_t             last_pervote_bucket_fill = 0;
      int64_t              pervote_bucket = 0;
      int64_t              perblock_bucket = 0;
      int64_t              savings = 0;
      uint32_t             total_unpaid_blocks = 0; /// all blocks which have been produced but not paid
      int64_t              total_activated_stake = 0;
      checksum160          last_producer_schedule_id;
      double               total_producer_vote_weight = 0; /// the sum of all producer votes

      // explicit serialization macro is not necessary, used here only to improve compilation time
      ENULIB_SERIALIZE_DERIVED( enumivo_global_state, enumivo_parameters, (total_ram_bytes_reserved)(total_ram_stake)
                                (last_producer_schedule_update)
                                (last_pervote_bucket_fill)
                                (pervote_bucket)(perblock_bucket)(savings)(total_unpaid_blocks)(total_activated_stake)(last_producer_schedule_id)(total_producer_vote_weight) )
   };

   struct producer_info {
      account_name          owner;
      double                total_votes = 0;
      enumivo::public_key     producer_key; /// a packed public key object
      std::string           url;
      uint32_t              unpaid_blocks = 0;
      uint64_t              last_claim_time = 0;
      uint16_t              location = 0;
      block_timestamp       time_became_active;
      block_timestamp       last_produced_block_time;

      uint64_t    primary_key()const { return owner;                        }
      double      by_votes()const    { return -total_votes;                 }
      bool        active() const     { return producer_key != public_key(); }

      // explicit serialization macro is not necessary, used here only to improve compilation time
      ENULIB_SERIALIZE( producer_info, (owner)(total_votes)(producer_key)(url)
                        (unpaid_blocks)(last_claim_time)(location)
                        (time_became_active)(last_produced_block_time) )
   };

   struct voter_info {
      account_name                owner = 0; /// the voter
      account_name                proxy = 0; /// the proxy set by the voter, if any
      std::vector<account_name>   producers; /// the producers approved by this voter if no proxy set
      int64_t                     staked = 0;

      /**
       *  Every time a vote is cast we must first "undo" the last vote weight, before casting the
       *  new vote weight.  Vote weight is calculated as:
       *
       *  stated.amount * 2 ^ ( weeks_since_launch/weeks_per_year)
       */
      double                      last_vote_weight = 0; /// the vote weight cast the last time the vote was updated

      /**
       * Total vote weight delegated to this voter.
       */
      double                      proxied_vote_weight= 0; /// the total vote weight delegated to this voter as a proxy
      bool                        is_proxy = 0; /// whether the voter is a proxy for others


      uint32_t                    deferred_trx_id = 0; /// the ID of the 3-day delay deferred transaction
      time                        last_unstake_time = 0; /// the time when the deferred_trx_id was sent
      enumivo::asset                unstaking; /// the total unstaking (pending 3 day delay)

      uint64_t primary_key()const { return owner; }

      // explicit serialization macro is not necessary, used here only to improve compilation time
      ENULIB_SERIALIZE( voter_info, (owner)(proxy)(producers)(staked)(last_vote_weight)(proxied_vote_weight)(is_proxy)(deferred_trx_id)(last_unstake_time)(unstaking) )
   };

   typedef enumivo::multi_index< N(voters), voter_info>  voters_table;


   typedef enumivo::multi_index< N(producers), producer_info,
                               indexed_by<N(prototalvote), const_mem_fun<producer_info, double, &producer_info::by_votes>  >
                               >  producers_table;

   typedef enumivo::singleton<N(global), enumivo_global_state> global_state_singleton;

   //   static constexpr uint32_t     max_inflation_rate = 5;  // 5% annual inflation
   static constexpr uint32_t     seconds_per_day = 24 * 3600;
   static constexpr uint64_t     system_token_symbol = S(4,EOS);

   class system_contract : public native {
      private:
         voters_table           _voters;
         producers_table        _producers;
         global_state_singleton _global;

         enumivo_global_state     _gstate;
         rammarket              _rammarket;

      public:
         system_contract( account_name s );
         ~system_contract();

         // Actions:
         void onblock( block_timestamp timestamp, account_name producer );
                      // const block_header& header ); /// only parse first 3 fields of block header

         // functions defined in delegate_bandwidth.cpp

         /**
          *  Stakes SYS from the balance of 'from' for the benfit of 'receiver'. 
          *  If transfer == true, then 'receiver' can unstake to their account
          *  Else 'from' can unstake at any time.
          */
         void delegatebw( account_name from, account_name receiver,
                          asset stake_net_quantity, asset stake_cpu_quantity, bool transfer );


         /**
          *  Decreases the total tokens delegated by from to receiver and/or
          *  frees the memory associated with the delegation if there is nothing
          *  left to delegate.
          *
          *  This will cause an immediate reduction in net/cpu bandwidth of the
          *  receiver. 
          *
          *  A transaction is scheduled to send the tokens back to 'from' after
          *  the staking period has passed. If existing transaction is scheduled, it
          *  will be canceled and a new transaction issued that has the combined
          *  undelegated amount.
          *
          *  The 'from' account loses voting power as a result of this call and
          *  all producer tallies are updated.
          */
         void undelegatebw( account_name from, account_name receiver,
                            asset unstake_net_quantity, asset unstake_cpu_quantity );


         /**
          * Increases receiver's ram quota based upon current price and quantity of
          * tokens provided. An inline transfer from receiver to system contract of
          * tokens will be executed.
          */
         void buyram( account_name buyer, account_name receiver, asset tokens );
         void buyrambytes( account_name buyer, account_name receiver, uint32_t bytes );

         /**
          *  Reduces quota my bytes and then performs an inline transfer of tokens
          *  to receiver based upon the average purchase price of the original quota.
          */
         void sellram( account_name receiver, int64_t bytes );

         /**
          *  This action is called after the delegation-period to claim all pending
          *  unstaked tokens belonging to owner
          */
         void refund( account_name owner );

         // functions defined in voting.cpp

         void regproducer( const account_name producer, const public_key& producer_key, const std::string& url, uint16_t location );

         void unregprod( const account_name producer );

         void setram( uint64_t max_ram_size );

         void voteproducer( const account_name voter, const account_name proxy, const std::vector<account_name>& producers );

         void regproxy( const account_name proxy, bool isproxy );

         // functions defined in producer_pay.cpp
         void claimrewards( const account_name& owner );

         void setpriv( account_name account, uint8_t ispriv );

      private:
         void update_elected_producers( block_timestamp timestamp );

         // Implementation details:

         //defined in voting.hpp
         static enumivo_global_state get_default_parameters();

         // defined in voting.cpp
         void propagate_weight_change( const voter_info& voter );
   };

} /// enumivosystem
