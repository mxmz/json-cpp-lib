#ifndef json_std_hxx_437398479837495873495873394875938573985739853985729
#define json_std_hxx_437398479837495873495873394875938573985739853985729

#include <string>
#include <iostream>
#include <map>
#include <vector>

#include "mxmz/json/v4/json_std.h"


namespace mxmz {
namespace json {
namespace v4 {
namespace std {


::std::istream&
operator>>( ::std::istream& in, mxmz::json::v4::std::json_value_handle& o ) {
    mxmz::json::v4::std::json_reader reader;
    in.unsetf(::std::ios_base::skipws);
    reader.read( in, o );
    return in;

}


::std::string&
operator<<( ::std::string& out, mxmz::json::v4::std::json_value_handle& o ) {
    mxmz::json::v4::std::json_string_writer writer;
    mxmz::json::v4::util::string_writer strout;
    writer.write(o,strout);
    strout.str().swap(out);
    return out;
}



}
}
}
}


::std::ostream&
operator<<( ::std::ostream& out, const mxmz::json::v4::std::json_value_handle& o ) {
    mxmz::json::v4::std::json_ostream_writer writer;
    writer.write(o,out);
    return out;
}


  mxmz::json::v4::std::json_object_key_temp_pair 
  operator<<( mxmz::json::v4::std::object_beg_tag , std::string&& key ) {
    return mxmz::json::v4::std::json_object_key_temp_pair( mxmz::json::v4::std::json_value_handle(), std::move(key) );
  }


  mxmz::json::v4::std::json_object_void_temp_pair
  operator<< ( mxmz::json::v4::std::json_object_key_temp_pair&& pair, mxmz::json::v4::std::json_value_handle&& value ) {
        pair.first[pair.second] = std::move(value);  
        return mxmz::json::v4::std::json_object_void_temp_pair( std::move(pair.first), true );
  }

  mxmz::json::v4::std::json_object_key_temp_pair 
  operator<<( mxmz::json::v4::std::json_object_void_temp_pair&& pair, std::string&& key ) {
        return mxmz::json::v4::std::json_object_key_temp_pair( std::move(pair.first), std::move(key) );
  }

  mxmz::json::v4::std::json_value_handle&& 
  operator<<( mxmz::json::v4::std::json_object_void_temp_pair&& pair, mxmz::json::v4::std::object_end_tag ) {
        return std::move(pair.first);
  }

  mxmz::json::v4::std::json_array_idx_temp_pair 
  operator<<( mxmz::json::v4::std::array_beg_tag , mxmz::json::v4::std::json_value_handle&& value  ) {
    mxmz::json::v4::std::json_value_handle newjs; 
    newjs[size_t(0)] = std::move(value);  
    return mxmz::json::v4::std::json_array_idx_temp_pair( std::move(newjs), 1 );
  }

 mxmz::json::v4::std::json_array_idx_temp_pair
  operator<< ( mxmz::json::v4::std::json_array_idx_temp_pair&& pair, mxmz::json::v4::std::json_value_handle&& value ) {
        pair.first[pair.second] = std::move(value);  
        return mxmz::json::v4::std::json_array_idx_temp_pair( std::move(pair.first), pair.second + 1 );
 }

 mxmz::json::v4::std::json_value_handle&& 
 operator<<( mxmz::json::v4::std::json_array_idx_temp_pair&& pair, mxmz::json::v4::std::array_end_tag ) {
        return std::move(pair.first);
  }






















#endif
