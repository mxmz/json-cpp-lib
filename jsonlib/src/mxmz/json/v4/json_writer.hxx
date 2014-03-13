#ifndef json_writer_hxx_374827627653726346239234029302039029309489884842
#define json_writer_hxx_374827627653726346239234029302039029309489884842

#include <string>

namespace mxmz {
namespace json {
namespace v4 {


struct json_element_writer_default_features {
    typedef ::std::string string_t;
    typedef char    char_t;

    static const char array_beg  = '[';
    static const char array_end  = ']';
    static const char map_beg  = '{';
    static const char map_end  = '}';
    static const char element_sep = ',';
    static const char key_sep = ':';
    static const char space = ' ';

    static const char* E_bs() {
        return "\\\\";
    }
    static const char* E_lf() {
        return "\\n";
    }
    static const char* E_tab() {
        return "\\t";
    }
    static const char* E_cr() {
        return "\\r";
    }
    static const char* E_ff() {
        return "\\f";
    }

    static const char quotes = '"';
    static const char* E_quotes() {
        return "\\\"";
    }
};



template< class OStreamT, class WriterFeatures = json_element_writer_default_features >
struct json_token_writer_tmpl {

    typedef WriterFeatures feat_t;

    typedef typename feat_t::string_t string_t;

private:
    OStreamT*   out;

public:
    json_token_writer_tmpl() : out(0) {
    }
    void bind( OStreamT* o ) {
        out = o;
    }

    void write_map_begin()      {
        *out << feat_t::map_beg;
    }
    void write_map_end()        {
        *out << feat_t::map_end ;
    }
    void write_array_begin()    {
        *out << feat_t::array_beg;
    }
    void write_array_end()      {
        *out << feat_t::array_end;
    }
    void write_element_separator()  {
        *out << feat_t::element_sep;
    }
    void write_key_separator()  {
        *out << feat_t::key_sep;
    }

    void write_integer(long long int v) {
        *out << v;
    }
    void write_double(long double v)    {
        *out << v;
    }
    void write_bool( bool v )   {
        *out << (v ? "true": "false") ;
    }
    void write_null()       {
        *out << "null" ;
    }

    void write_qstring( const string_t& s ) {
        *out<< feat_t::quotes;
        for ( typename string_t::const_iterator i = s.begin(); i != s.end(); ++i ) {
            switch (*i) {
            case '\\':
                *out << feat_t::E_bs();
                break;
            case '\n':
                *out << feat_t::E_lf();
                break;
            case '\t':
                *out << feat_t::E_tab();
                break;
            case '\r':
                *out << feat_t::E_cr();
                break;
            case '\f':
                *out << feat_t::E_ff();
                break;
                /*
                case '\"': *out << feat_t::E_dq(); break;
                case '\'': *out << feat_t::E_sq(); break;
                */
            case feat_t::quotes:
                *out << feat_t::E_quotes();
                break;
            default: {
                if ( (unsigned char)*i < 32 ) {
                    char ucode[7];
                    sprintf(ucode, "\\u%.04d",*i);
                    *out << ucode;
                    continue;
                } else
                    *out << *i;
            }
            }
        }
        *out<< feat_t::quotes;
    }

    void write_key_pair( const string_t& k, const string_t& v, bool quoted ) {
        write_qstring(k);
        *out << feat_t::key_sep;
        if ( quoted ) {
            write_qstring(v);
        } else {
            *out << v;
        }
    }
};



template< class OStreamT, class JsonValueHandleT,
class WriterT = json_token_writer_tmpl<OStreamT> >
struct json_writer_tmpl :public JsonValueHandleT::json_value_const_visitor {
    typedef JsonValueHandleT json_value_handle;
    typedef WriterT  writer_t;


    typedef typename json_value_handle::json_string     json_string;
    typedef typename json_value_handle::json_number     json_number;
    typedef typename json_value_handle::json_integer    json_integer;
    typedef typename json_value_handle::json_bool       json_bool;
    typedef typename json_value_handle::json_object     json_object;
    typedef typename json_value_handle::json_array      json_array;

    typedef typename json_value_handle::string_t string_t;
    typedef typename json_value_handle::number_t number_t;
    typedef typename json_value_handle::integer_t integer_t;


    typedef typename  writer_t::feat_t feat_t;

    WriterT writer;

    void visit( const json_object&  jm ) {
        const typename json_object::value_type& m = jm.get();
        writer.write_map_begin();
        typename json_object::value_type::const_iterator i = m.begin();
        if ( i != m.end() ) {
            writer.write_qstring(i->first);
            writer.write_key_separator();
            deref_ptr(i->second).accept(*this);
            ++i;
            while ( i != m.end() ) {
                writer.write_element_separator();
                writer.write_qstring(i->first);
                writer.write_key_separator();
                deref_ptr(i->second).accept(*this);
                ++i;
            }

        }
        writer.write_map_end();
    }

    void visit( const json_array& ja ) {
        const typename json_array::value_type& a = ja.get();

        writer.write_array_begin();
        typename json_array::value_type::const_iterator i= a.begin();
        if ( i != a.end() ) {
            ( deref_ptr( *i ) ).accept(*this);
            ++i;
            while ( i != a.end()) {
                writer.write_element_separator();
                ( deref_ptr( *i ) ).accept(*this);
                ++i;
            }
        }
        writer.write_array_end();
    }


    void write( const json_value_handle& o, OStreamT&out ) {
        writer.bind(&out);
        o.accept(*this);
    }


    void visit() {
        writer.write_null();
    }
    void visit( const json_string& v ) {
        writer.write_qstring( v.get() );
    }
    void visit( const json_number& v ) {
        writer.write_double( v.get() );
    }
    void visit( const json_integer& v ) {
        writer.write_integer( v.get() );
    }
    void visit( const json_bool& v ) {
        writer.write_bool(v.get());
    }


};


}
}
}

namespace mxmz {
namespace json {
namespace v4 {
namespace util {


class string_writer {
    ::std::string buffer;

public:

    ::std::string& str() {
        return buffer;
    }
    void reset() {
        buffer.resize(0);
    }


    string_writer& operator<<( char c ) {
        buffer += c;
        return *this;
    }
    string_writer& operator<<( const char* p ) {
        buffer += p;
        return *this;
    }
    string_writer& operator<<( const ::std::string& s ) {
        buffer += s;
        return *this;
    }

    string_writer& operator<<( double v ) {
        char buf[30];
        sprintf( buf, "%g", v );
        buffer += buf;
        return *this;
    }
    string_writer& operator<<( long double v ) {
        char buf[30];
        sprintf( buf, "%llg", v );
        buffer += buf;
        return *this;
    }
    string_writer& operator<<( long long int v ) {
        char buf[30];
        sprintf( buf, "%lld", v );
        buffer += buf;
        return *this;
    }


};





}
}
}
}



#endif
