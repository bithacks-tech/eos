/**
 *  @file
 *  @copyright defined in myeosio/LICENSE.txt
 */
#pragma once

#include <myeosio/chain/types.hpp>
#include <myeosio/chain/contract_types.hpp>

namespace myeosio { namespace chain {

   class apply_context;

   /**
    * @defgroup native_action_handlers Native Action Handlers
    */
   ///@{
   void apply_myeosio_newaccount(apply_context&);
   void apply_myeosio_updateauth(apply_context&);
   void apply_myeosio_deleteauth(apply_context&);
   void apply_myeosio_linkauth(apply_context&);
   void apply_myeosio_unlinkauth(apply_context&);

   /*
   void apply_myeosio_postrecovery(apply_context&);
   void apply_myeosio_passrecovery(apply_context&);
   void apply_myeosio_vetorecovery(apply_context&);
   */

   void apply_myeosio_setcode(apply_context&);
   void apply_myeosio_setabi(apply_context&);

   void apply_myeosio_canceldelay(apply_context&);
   ///@}  end action handlers

} } /// namespace myeosio::chain
