#include <myeoslib/enu.hpp>
using namespace myeosio;

class hello : public myeosio::contract {
  public:
      using contract::contract;

      /// @abi action 
      void hi( account_name user ) {
         print( "Hello, ", name{user} );
      }
};

MYEOSIO_ABI( hello, (hi) )
