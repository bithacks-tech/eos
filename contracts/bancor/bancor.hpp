/**
 *  @file
 *  @copyright defined in myeosio/LICENSE.txt
 */
#pragma once

#include <enulib/enu.hpp>
#include <enulib/token.hpp>
#include <enulib/reflect.hpp>
#include <enulib/generic_currency.hpp>

#include <bancor/converter.hpp>
#include <currency/currency.hpp>

namespace bancor {
   typedef myeosio::generic_currency< myeosio::token<N(other),S(4,OTHER)> >  other_currency;
   typedef myeosio::generic_currency< myeosio::token<N(bancor),S(4,RELAY)> > relay_currency;
   typedef myeosio::generic_currency< myeosio::token<N(currency),S(4,CUR)> > cur_currency;

   typedef converter<relay_currency, other_currency, cur_currency > example_converter;
} /// bancor

