/**
 *  @file
 *  @copyright defined in myeosio/LICENSE.txt
 */

#include <enulib/enu.hpp>

namespace asserter {
   struct assertdef {
      int8_t      condition;
      std::string message;

      MESLIB_SERIALIZE( assertdef, (condition)(message) )
   };
}
