/**
 *  @file
 *  @copyright defined in myeosio/LICENSE.txt
 */

#include <myeosio/utilities/tempdir.hpp>

#include <cstdlib>

namespace myeosio { namespace utilities {

fc::path temp_directory_path()
{
   const char* enu_tempdir = getenv("MES_TEMPDIR");
   if( enu_tempdir != nullptr )
      return fc::path( enu_tempdir );
   return fc::temp_directory_path() / "enu-tmp";
}

} } // myeosio::utilities
