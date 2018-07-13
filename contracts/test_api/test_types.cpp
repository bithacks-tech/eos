/**
 *  @file
 *  @copyright defined in myeosio/LICENSE.txt
 */
#include <myeoslib/enu.hpp>

#include "test_api.hpp"

void test_types::types_size() {

   myeosio_assert( sizeof(int64_t) == 8, "int64_t size != 8");
   myeosio_assert( sizeof(uint64_t) ==  8, "uint64_t size != 8");
   myeosio_assert( sizeof(uint32_t) ==  4, "uint32_t size != 4");
   myeosio_assert( sizeof(int32_t) ==  4, "int32_t size != 4");
   myeosio_assert( sizeof(uint128_t) == 16, "uint128_t size != 16");
   myeosio_assert( sizeof(int128_t) == 16, "int128_t size != 16");
   myeosio_assert( sizeof(uint8_t) ==  1, "uint8_t size != 1");

   myeosio_assert( sizeof(account_name) ==  8, "account_name size !=  8");
   myeosio_assert( sizeof(table_name) ==  8, "table_name size !=  8");
   myeosio_assert( sizeof(time) ==  4, "time size !=  4");
   myeosio_assert( sizeof(myeosio::key256) == 32, "key256 size != 32" );
}

void test_types::char_to_symbol() {

   myeosio_assert( myeosio::char_to_symbol('1') ==  1, "myeosio::char_to_symbol('1') !=  1");
   myeosio_assert( myeosio::char_to_symbol('2') ==  2, "myeosio::char_to_symbol('2') !=  2");
   myeosio_assert( myeosio::char_to_symbol('3') ==  3, "myeosio::char_to_symbol('3') !=  3");
   myeosio_assert( myeosio::char_to_symbol('4') ==  4, "myeosio::char_to_symbol('4') !=  4");
   myeosio_assert( myeosio::char_to_symbol('5') ==  5, "myeosio::char_to_symbol('5') !=  5");
   myeosio_assert( myeosio::char_to_symbol('a') ==  6, "myeosio::char_to_symbol('a') !=  6");
   myeosio_assert( myeosio::char_to_symbol('b') ==  7, "myeosio::char_to_symbol('b') !=  7");
   myeosio_assert( myeosio::char_to_symbol('c') ==  8, "myeosio::char_to_symbol('c') !=  8");
   myeosio_assert( myeosio::char_to_symbol('d') ==  9, "myeosio::char_to_symbol('d') !=  9");
   myeosio_assert( myeosio::char_to_symbol('e') == 10, "myeosio::char_to_symbol('e') != 10");
   myeosio_assert( myeosio::char_to_symbol('f') == 11, "myeosio::char_to_symbol('f') != 11");
   myeosio_assert( myeosio::char_to_symbol('g') == 12, "myeosio::char_to_symbol('g') != 12");
   myeosio_assert( myeosio::char_to_symbol('h') == 13, "myeosio::char_to_symbol('h') != 13");
   myeosio_assert( myeosio::char_to_symbol('i') == 14, "myeosio::char_to_symbol('i') != 14");
   myeosio_assert( myeosio::char_to_symbol('j') == 15, "myeosio::char_to_symbol('j') != 15");
   myeosio_assert( myeosio::char_to_symbol('k') == 16, "myeosio::char_to_symbol('k') != 16");
   myeosio_assert( myeosio::char_to_symbol('l') == 17, "myeosio::char_to_symbol('l') != 17");
   myeosio_assert( myeosio::char_to_symbol('m') == 18, "myeosio::char_to_symbol('m') != 18");
   myeosio_assert( myeosio::char_to_symbol('n') == 19, "myeosio::char_to_symbol('n') != 19");
   myeosio_assert( myeosio::char_to_symbol('o') == 20, "myeosio::char_to_symbol('o') != 20");
   myeosio_assert( myeosio::char_to_symbol('p') == 21, "myeosio::char_to_symbol('p') != 21");
   myeosio_assert( myeosio::char_to_symbol('q') == 22, "myeosio::char_to_symbol('q') != 22");
   myeosio_assert( myeosio::char_to_symbol('r') == 23, "myeosio::char_to_symbol('r') != 23");
   myeosio_assert( myeosio::char_to_symbol('s') == 24, "myeosio::char_to_symbol('s') != 24");
   myeosio_assert( myeosio::char_to_symbol('t') == 25, "myeosio::char_to_symbol('t') != 25");
   myeosio_assert( myeosio::char_to_symbol('u') == 26, "myeosio::char_to_symbol('u') != 26");
   myeosio_assert( myeosio::char_to_symbol('v') == 27, "myeosio::char_to_symbol('v') != 27");
   myeosio_assert( myeosio::char_to_symbol('w') == 28, "myeosio::char_to_symbol('w') != 28");
   myeosio_assert( myeosio::char_to_symbol('x') == 29, "myeosio::char_to_symbol('x') != 29");
   myeosio_assert( myeosio::char_to_symbol('y') == 30, "myeosio::char_to_symbol('y') != 30");
   myeosio_assert( myeosio::char_to_symbol('z') == 31, "myeosio::char_to_symbol('z') != 31");

   for(unsigned char i = 0; i<255; i++) {
      if((i >= 'a' && i <= 'z') || (i >= '1' || i <= '5')) continue;
      myeosio_assert( myeosio::char_to_symbol((char)i) == 0, "myeosio::char_to_symbol() != 0");
   }
}

void test_types::string_to_name() {

   myeosio_assert( myeosio::string_to_name("a") == N(a) , "myeosio::string_to_name(a)" );
   myeosio_assert( myeosio::string_to_name("ba") == N(ba) , "myeosio::string_to_name(ba)" );
   myeosio_assert( myeosio::string_to_name("cba") == N(cba) , "myeosio::string_to_name(cba)" );
   myeosio_assert( myeosio::string_to_name("dcba") == N(dcba) , "myeosio::string_to_name(dcba)" );
   myeosio_assert( myeosio::string_to_name("edcba") == N(edcba) , "myeosio::string_to_name(edcba)" );
   myeosio_assert( myeosio::string_to_name("fedcba") == N(fedcba) , "myeosio::string_to_name(fedcba)" );
   myeosio_assert( myeosio::string_to_name("gfedcba") == N(gfedcba) , "myeosio::string_to_name(gfedcba)" );
   myeosio_assert( myeosio::string_to_name("hgfedcba") == N(hgfedcba) , "myeosio::string_to_name(hgfedcba)" );
   myeosio_assert( myeosio::string_to_name("ihgfedcba") == N(ihgfedcba) , "myeosio::string_to_name(ihgfedcba)" );
   myeosio_assert( myeosio::string_to_name("jihgfedcba") == N(jihgfedcba) , "myeosio::string_to_name(jihgfedcba)" );
   myeosio_assert( myeosio::string_to_name("kjihgfedcba") == N(kjihgfedcba) , "myeosio::string_to_name(kjihgfedcba)" );
   myeosio_assert( myeosio::string_to_name("lkjihgfedcba") == N(lkjihgfedcba) , "myeosio::string_to_name(lkjihgfedcba)" );
   myeosio_assert( myeosio::string_to_name("mlkjihgfedcba") == N(mlkjihgfedcba) , "myeosio::string_to_name(mlkjihgfedcba)" );
   myeosio_assert( myeosio::string_to_name("mlkjihgfedcba1") == N(mlkjihgfedcba2) , "myeosio::string_to_name(mlkjihgfedcba2)" );
   myeosio_assert( myeosio::string_to_name("mlkjihgfedcba55") == N(mlkjihgfedcba14) , "myeosio::string_to_name(mlkjihgfedcba14)" );

   myeosio_assert( myeosio::string_to_name("azAA34") == N(azBB34) , "myeosio::string_to_name N(azBB34)" );
   myeosio_assert( myeosio::string_to_name("AZaz12Bc34") == N(AZaz12Bc34) , "myeosio::string_to_name AZaz12Bc34" );
   myeosio_assert( myeosio::string_to_name("AAAAAAAAAAAAAAA") == myeosio::string_to_name("BBBBBBBBBBBBBDDDDDFFFGG") , "myeosio::string_to_name BBBBBBBBBBBBBDDDDDFFFGG" );
}

void test_types::name_class() {

   myeosio_assert( myeosio::name{myeosio::string_to_name("azAA34")}.value == N(azAA34), "myeosio::name != N(azAA34)" );
   myeosio_assert( myeosio::name{myeosio::string_to_name("AABBCC")}.value == 0, "myeosio::name != N(0)" );
   myeosio_assert( myeosio::name{myeosio::string_to_name("AA11")}.value == N(AA11), "myeosio::name != N(AA11)" );
   myeosio_assert( myeosio::name{myeosio::string_to_name("11AA")}.value == N(11), "myeosio::name != N(11)" );
   myeosio_assert( myeosio::name{myeosio::string_to_name("22BBCCXXAA")}.value == N(22), "myeosio::name != N(22)" );
   myeosio_assert( myeosio::name{myeosio::string_to_name("AAAbbcccdd")} == myeosio::name{myeosio::string_to_name("AAAbbcccdd")}, "myeosio::name == myeosio::name" );

   uint64_t tmp = myeosio::name{myeosio::string_to_name("11bbcccdd")};
   myeosio_assert(N(11bbcccdd) == tmp, "N(11bbcccdd) == tmp");
}
