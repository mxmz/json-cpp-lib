#ifndef json_std_h_43739847983749587349587339487593857398573985398572938
#define json_std_h_43739847983749587349587339487593857398573985398572938

#include <string>
#include <iostream>
#include <map>
#include <vector>

#include "mxmz/json/v4/json_value_handle.hxx"
#include "mxmz/json/v4/json_tokenizer.hxx"
#include "mxmz/json/v4/json_parser.hxx"
#include "mxmz/json/v4/json_reader.hxx"
#include "mxmz/json/v4/json_writer.hxx"


namespace mxmz {
namespace json {
namespace v4 {
namespace std {



struct config {
    typedef ::std::string                string_t;
    typedef long long int                integer_t;
    typedef long double                  number_t;
    typedef bool                         boolean_t;
    typedef char                         char_t;
    typedef unsigned char                u_char_t;

    static const bool  enable_value_sharing = false;
    static const bool  use_ptr_containers   = false;
    static const bool  use_std_shared_ptr   = false;
};


class json_value_handle : public json_value_handle_tmpl<json_value_handle, config> {
    typedef json_value_handle_tmpl<json_value_handle, config> base_t;

public:
    json_value_handle() {
        JSON_VALUE_CERR << this << " ctor (std::json_value_handle)\n";
    }

    template< class T >
     json_value_handle( const T& v ) : base_t(v) {
        JSON_VALUE_CERR << this << " ctor(T) (std::json_value_handle)\n";
     }

    json_value_handle( int v ) : base_t( integer_t(v) ) {
    }

    json_value_handle( long int v ) : base_t( integer_t(v) ) {
    }

    json_value_handle( double v ) : base_t( number_t(v) ) {
    }

    json_value_handle( json_value_handle&& temp ) : base_t( ::std::move(temp) ) {
        JSON_VALUE_CERR << this << " ctor(json_value_handle&&) (std::json_value_handle)\n";
    }
    json_value_handle& operator=( json_value_handle&& temp ) {
        JSON_VALUE_CERR << this << " operator=(temp&&)\n";
        temp.swap(*this);
        return (*this);
    }

    // special features ...

    json_value_handle& operator[]( const char* k ) {
        return this->cast_value<json_object>(true).item(k);
    }

    json_value_handle& operator[]( const ::std::string& k ) {
        return this->cast_value<json_object>(true).item(k);
    }

    const json_value_handle* attribute( const ::std::string& k ) const {
        const auto& v = this->cast_value_const<json_object>();
        const auto it = v.get().find(k);
        if ( it != v.get().end() ) {
                    return &(it->second);
        } else {
            return 0;
        }
    }
    
    json_value_handle* attribute( const ::std::string& k ) {
        return const_cast<json_value_handle*>( static_cast<const json_value_handle&>(*this).attribute(k) );
    }

    json_value_handle& operator[]( size_t idx ) {
        return this->cast_value<json_array>(true).item(idx);
    }

    void push_back( json_value_handle&& arg ) {
        this->cast_value<json_array>(true).push_back(::std::move(arg));
    }
    size_t size() const {
        return this->cast_value<json_array>().size();
    }

    operator string_t () const {
        return this->is_null() ? "" : this->cast_value_const<json_scalar>().string();
    }
    operator integer_t () const {
        return this->is_null() ? 0 : this->cast_value_const<json_scalar>().integer();
    }
    operator number_t () const {
        return this->is_null() ? 0: this->cast_value_const<json_scalar>().number();
    }
    operator boolean_t () const {
        return this->is_null() ? false : this->cast_value_const<json_scalar>().boolean();
    }

    operator int () const {
        return this->is_null() ? 0 : this->cast_value_const<json_scalar>().integer();
    }
    operator long int () const {
        return this->is_null() ? 0 : this->cast_value_const<json_scalar>().integer();
    }
    operator double () const {
        return this->is_null() ? 0 : this->cast_value_const<json_scalar>().number();
    }



};


typedef json_value_handle::json_string     json_string;
typedef json_value_handle::json_number     json_number;
typedef json_value_handle::json_integer    json_integer;
typedef json_value_handle::json_bool       json_bool;
typedef json_value_handle::json_object     json_object;
typedef json_value_handle::json_array      json_array;

typedef json_parser_tmpl<json_value_handle>         json_parser;

typedef json_tokenizer_tmpl< json_parser >  json_tokenizer;


typedef json_reader_tmpl< json_tokenizer >         json_reader;


typedef json_writer_tmpl< ::std::ostream, json_value_handle >       json_ostream_writer;

typedef json_writer_tmpl<
mxmz::json::v4::util::string_writer , json_value_handle >    json_string_writer;


::std::istream&
operator>>( ::std::istream& in, mxmz::json::v4::std::json_value_handle& o );

template< class BufferLikeT >
const BufferLikeT&
operator>>( const BufferLikeT& in, mxmz::json::v4::std::json_value_handle& o ) {
    mxmz::json::v4::std::json_reader reader;
    mxmz::json::v4::util::buffer_reader buff_in( in.data(), in.size() );
    reader.read( buff_in, o );
    return in;

}

/*

::std::ostream&
operator<<( ::std::ostream& out, const mxmz::json::v4::std::json_value_handle& o ) {
    mxmz::json::v4::std::json_ostream_writer writer;
    writer.write(o,out);
    return out;
}

*/

::std::string&
operator<<( ::std::string& out, mxmz::json::v4::std::json_value_handle& o );



  enum object_beg_tag { ObjectBeg };
  enum object_end_tag { ObjectEnd };
  enum array_beg_tag { ArrayBeg };
  enum array_end_tag { ArrayEnd };
    
  typedef ::std::pair< json_value_handle, ::std::string&& >    json_object_key_temp_pair;
  typedef ::std::pair< json_value_handle, bool>                json_object_void_temp_pair;
 
  typedef ::std::pair< json_value_handle, size_t>             json_array_idx_temp_pair;




}
}
}
}


::std::ostream&
operator<<( ::std::ostream& out, const mxmz::json::v4::std::json_value_handle& o );


  mxmz::json::v4::std::json_object_key_temp_pair 
  operator<<( mxmz::json::v4::std::object_beg_tag , std::string&& key );

  mxmz::json::v4::std::json_object_void_temp_pair
  operator<< ( mxmz::json::v4::std::json_object_key_temp_pair&& pair, mxmz::json::v4::std::json_value_handle&& value );

  mxmz::json::v4::std::json_object_key_temp_pair 
  operator<<( mxmz::json::v4::std::json_object_void_temp_pair&& pair, std::string&& key );

  mxmz::json::v4::std::json_value_handle&& 
  operator<<( mxmz::json::v4::std::json_object_void_temp_pair&& pair, mxmz::json::v4::std::object_end_tag );

  mxmz::json::v4::std::json_array_idx_temp_pair 
  operator<<( mxmz::json::v4::std::array_beg_tag , mxmz::json::v4::std::json_value_handle&& value  );

  mxmz::json::v4::std::json_array_idx_temp_pair
  operator<< ( mxmz::json::v4::std::json_array_idx_temp_pair&& pair, mxmz::json::v4::std::json_value_handle&& value );

  mxmz::json::v4::std::json_value_handle&& 
  operator<<( mxmz::json::v4::std::json_array_idx_temp_pair&& pair, mxmz::json::v4::std::array_end_tag );







#endif
