#ifndef json_tokenizer_hxx_456456495840698450694564650465984059409684064
#define json_tokenizer_hxx_456456495840698450694564650465984059409684064

#include <ctype.h>
#include <exception>
#include <stdlib.h>


namespace mxmz {
namespace json {
namespace v4 {

template< class ConfigT >
struct json_tokenizer_default_features_tmpl {
    typedef typename ConfigT::string_t  string_t;
    typedef typename ConfigT::char_t    char_t;
    typedef typename ConfigT::u_char_t  u_char_t;

    struct utf8_encode_append {
        inline void operator()( unsigned int ucs, string_t& output );
    };

    typedef utf8_encode_append  unicode_appender_t;
};


template< class ConsumerT, template<class C> class FeaturesTmpl = json_tokenizer_default_features_tmpl >
struct json_tokenizer_tmpl {
    typedef ConsumerT consumer_t;
    typedef typename ConsumerT::config_t    config_t;
    typedef FeaturesTmpl<config_t>           features_t;
    typedef typename features_t::string_t   string_t;
    typedef typename features_t::char_t     char_t;
    typedef typename features_t::unicode_appender_t     unicode_appender_t;

    struct json_illegal_character: public std::exception {
        std::string message;

public:
        json_illegal_character( char c ) {
            message += "illegal character '";
            message += c;
            message += "'";
        }
        const char* what() const throw() {
            return message.c_str();
        }
        ~json_illegal_character() throw() {
        }

    };


    struct qstring_reader {
        unicode_appender_t uni_app;
        string_t&    buffer;

        char_t    qchar;
        char      u_digits[5];
        enum state_t { Plain, Esc, U_Esc  } ;
        state_t   state;
        size_t    u_count;

        qstring_reader(string_t& s) : buffer(s), state(Plain), u_count(0) { }

        inline bool read( char_t c );
        void reset( char_t c) {
            qchar = c;
            buffer.resize(0);
            state = Plain;
        }

    };


    enum state_t {  Space, Quoted, Token } ;

    consumer_t&  consumer;

    qstring_reader  rqstr;
    string_t  buffer;
    state_t   state;


    json_tokenizer_tmpl(consumer_t& p) : consumer(p), rqstr(buffer), state(Space) { }


    inline void read( char_t c );

    void open() {
        consumer.handle_begin_document();
    }

    void close() {
        consumer.handle_end_document();
    }

};


/*  definitions */

template< class ConsumerT, template<class> class FeaturesT >
inline
bool
json_tokenizer_tmpl<ConsumerT, FeaturesT>::qstring_reader::read( char_t c ) {
    switch (state) {
    case Plain: {
        if ( c == '\\' ) {
            state = Esc;
        } else if ( c == qchar ) {
            return  false;
        } else {
            buffer.append(&c,1);
        }
    }
    break;
    case Esc:
        do {
            switch (c) {
            case 'u':
                state= U_Esc;
                continue;
            case 'n':
                c = '\n';
                break;
            case 'b':
                c = '\b';
                break;
            case 't':
                c = '\t';
                break;
            case 'r':
                c = '\r';
                break;
            case 'f':
                c = '\f';
                break;
            default:        { }

            }
            buffer.append(&c,1);
            state = Plain;
        } while (0);
        break;
    case U_Esc: {
        u_digits[ u_count++ ] = c;
        if ( u_count == 4 ) {
            u_digits[4] = '\0';
            unsigned int n = strtoul(u_digits,0,16);
            uni_app(n,buffer);
            state = Plain;
            u_count = 0;
        }
    }
    }
    return true;
}


#define JSON_VALID_CHAR_FOR_BARE_STRING(C)  ( isalnum(C) || C == '_' || C == '+' || C == '-' || C == '.' )

template< class ConsumerT, template<class> class FeaturesT >
inline
void
json_tokenizer_tmpl<ConsumerT,FeaturesT>::read( char_t c ) {
    switch (state) {
    case Space: {
        switch (c) {
        case ' ':
        case '\n':
        case '\t':
        case '\r':
            break;
        case '[':
        case ']':
        case '}':
        case '{':
            consumer.handle_bracket(c);
            break;
        case ':':
        case ',':
            consumer.handle_separator(c);
            break;
        case '"':
        case '\'':
            state = Quoted;
            rqstr.reset(c);
            break;
        default:
            if ( JSON_VALID_CHAR_FOR_BARE_STRING(c) ) {
                buffer.assign(&c,1);
                state = Token;
            } else throw json_illegal_character(c);
        }

    }
    break;

    case Token: {
        switch (c) {
        case ' ':
        case '\n':
        case '\t':
        case '\r':
            consumer.handle_token(::std::move(buffer));
            state = Space;
            break;
        case '[':
        case ']':
        case '}':
        case '{':
            consumer.handle_token(::std::move(buffer));
            consumer.handle_bracket(c);
            state = Space;
            break;
        case ':':
        case ',':
            consumer.handle_token(::std::move(buffer));
            consumer.handle_separator(c);
            state = Space;
            break;
        case '"':
        case '\'':
            consumer.handle_token(::std::move(buffer));
            rqstr.reset(c);
            state = Quoted;
            break;
        default:
            if ( JSON_VALID_CHAR_FOR_BARE_STRING(c) ) {
                buffer.append(&c,1);
            } else throw json_illegal_character(c);
        }

    }
    break;

    case Quoted: {
        if ( ! rqstr.read(c) ) {
            state = Space;
            consumer.handle_qstring( std::move(buffer) );
        }

    }

    }

}


template < class ConfigT >
void
json_tokenizer_default_features_tmpl<ConfigT>::utf8_encode_append::operator()( unsigned int ucs_char, string_t& output ) {
    u_char_t utf_out[3];

    if (ucs_char < 0x80) {
        utf_out[0] = ucs_char;
        output.append( (char_t*)utf_out, 1);
    } else if (ucs_char < 0x800) {
        utf_out[0] = 0xc0 | (ucs_char >> 6);
        utf_out[1] = 0x80 | (ucs_char & 0x3f);
        output.append( (char_t*)utf_out, 2);
    } else {
        utf_out[0] = 0xe0 | (ucs_char >> 12);
        utf_out[1] = 0x80 | ((ucs_char >> 6) & 0x3f);
        utf_out[2] = 0x80 | (ucs_char & 0x3f);
        output.append( (char_t*)utf_out, 3);
    }
}


}
}
}




#endif
