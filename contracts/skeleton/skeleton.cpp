#include <enulib/enu.hpp>

using namespace myeosio;

class hello : public myeosio::contract {
  public:
      using contract::contract;

      /// @abi action 
      void hi( account_name user ) {
         print( "Hello, ", name{user} );
      }
};

ENUMIVO_ABI( hello, (hi) )
