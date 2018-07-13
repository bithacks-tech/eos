#include <myeoslib/enu.hpp>
#include <myeoslib/print.hpp>
using namespace myeosio;

class payloadless : public myeosio::contract {
  public:
      using contract::contract;

      void doit() {
         print( "Im a payloadless action" );
      }
};

ENUMIVO_ABI( payloadless, (doit) )
