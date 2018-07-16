/**
 *  @file
 *  @copyright defined in myeosio/LICENSE.txt
 */

#include <myeoslib/myeos.hpp>

namespace asserter {
   struct assertdef {
      int8_t      condition;
      std::string message;

      MYEOSLIB_SERIALIZE( assertdef, (condition)(message) )
   };
}
