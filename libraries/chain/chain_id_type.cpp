/**
 *  @file
 *  @copyright defined in myeosio/LICENSE.txt
 */

#include <myeosio/chain/chain_id_type.hpp>
#include <myeosio/chain/exceptions.hpp>

namespace myeosio { namespace chain {

   void chain_id_type::reflector_verify()const {
      FC_ASSERT( *reinterpret_cast<const fc::sha256*>(this) != fc::sha256(), "chain_id_type cannot be zero" );
   }

} }  // namespace myeosio::chain

namespace fc {

   void to_variant(const myeosio::chain::chain_id_type& cid, fc::variant& v) {
      to_variant( static_cast<const fc::sha256&>(cid), v);
   }

   void from_variant(const fc::variant& v, myeosio::chain::chain_id_type& cid) {
      from_variant( v, static_cast<fc::sha256&>(cid) );
   }

} // fc
