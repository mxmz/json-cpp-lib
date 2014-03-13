#ifndef json_parser_hxx_435938059830585345305983053535305983095830598309
#define json_parser_hxx_435938059830585345305983053535305983095830598309


#ifdef JSON_PARSER_DEBUG
#define JSON_PARSER_CERR if(1) std::cerr
#define JSON_PARSER_COUT if(1) std::cerr
#else
#define JSON_PARSER_CERR if(0) std::cerr
#define JSON_PARSER_COUT if(0) std::cerr
#endif

#include <stdlib.h>

namespace mxmz {
namespace json {
namespace v4 {

template < class JsonValueHandleT >
class json_parser_tmpl {
public:
    typedef JsonValueHandleT json_value_handle;
    typedef typename json_value_handle::config_t        config_t;
    typedef typename json_value_handle::json_string     json_string;
    typedef typename json_value_handle::json_number     json_number;
    typedef typename json_value_handle::json_integer    json_integer;
    typedef typename json_value_handle::json_bool       json_bool;
    typedef typename json_value_handle::json_object     json_object;
    typedef typename json_value_handle::json_array      json_array;

    enum expected_things {  Nothing = 0,        SingleValue = 1,    ArrayItem = 2,  ArrayItemSeparator = 3,
                            ObjectKey = 4,      ObjectKeySeparator = 5,     ObjectValue = 6, ObjectItemSeparator = 7
                         };

    static const char* expected_name(expected_things t ) {
        switch (t) {
        case Nothing:
            return "nothing";
        case SingleValue:
            return "a single value";
        case ArrayItem:
            return "an array element or a closing bracket (])";
        case ArrayItemSeparator:
            return "an array element separator (,) or a closing bracket (])";
        case ObjectKey:
            return "an object key or a closing brace (})";
        case ObjectKeySeparator:
            return "a key-value separator (:)";
        case ObjectValue:
            return "a object item value";
        case ObjectItemSeparator:
            return "an object item separator (,) or a closing brace (})";
        }
        return "";
    }
    struct json_unexpected_token_exception: public std::exception {
        std::string message;

public:
        json_unexpected_token_exception( const char* got, expected_things t ) {
            message += "Found ";
            message += got;
            message += " but expecting ";
            message += expected_name(t);
        }
        const char* what() const throw() {
            return message.c_str();
        }
        ~json_unexpected_token_exception() throw() {
        }

    };


    struct stack_slot {
        json_value_handle* handle;
        json_object*      object_value;
        json_array*       array_value;

        expected_things expecting;

        stack_slot()
                : handle(0), object_value(0), array_value(0), expecting(Nothing) { }
    };


    std::vector< stack_slot >  stack;

    void handle_begin_document() {
    }

    void handle_end_document() {
        if ( stack.size() > 1 ) {
            stack_slot& s =  current_slot();
            throw json_unexpected_token_exception("end of input",s.expecting);
        }
    }


    json_parser_tmpl( json_value_handle& result ) {
        stack.resize(2);
        stack.reserve(100);
        stack[1].handle = &result;
        stack[1].expecting = SingleValue;
    }

    stack_slot& current_slot() {
        stack_slot& s =  stack[ stack.size() -1 ];
        JSON_PARSER_COUT << "current_slot "<<  (stack.size() -1 ) << " expecting: " << expected_name(s.expecting) << " / " << s.handle << "\n";
        return s;
    }

    inline void increase_stack() {
        JSON_PARSER_COUT << " increase_stack" << stack.size() << "\n";
        stack.resize( stack.size() + 1 );
        current_slot();
    }

    inline void decrease_stack() {
        JSON_PARSER_COUT << " decrease_stack < " << stack.size() << "\n";
//      assert( stack.size() > 0 );
        stack.resize( stack.size() - 1 );
        current_slot();
    }


    inline void handle_begin_object() {
        stack_slot& s =  current_slot();
        switch ( s.expecting ) {
        case ObjectValue:
        case SingleValue:
            s.object_value = &( (*s.handle).template coerce_value< json_object >() );
            s.expecting = ObjectKey;
            break;

        case ArrayItem: {
            json_value_handle& new_handle =  s.array_value->append(); //s.handle->template cast_value< json_array >().append();
            json_object& new_handle_value = new_handle.template coerce_value< json_object >();
            s.expecting = ArrayItemSeparator;
            increase_stack();
            stack_slot& new_s =  current_slot();
            new_s.handle = &new_handle;
            new_s.object_value = &new_handle_value;
            new_s.expecting = ObjectKey;
        }
        break;
        default:
            //assert( s.expecting == ObjectValue || s.expecting == SingleValue || s.expecting == ArrayItem );
            throw json_unexpected_token_exception("'{'",s.expecting);
        }
    }

    inline void handle_end_object() {
        stack_slot& s =  current_slot();
        switch ( s.expecting ) {
        case ObjectKey:
        case ObjectItemSeparator:
            break;
        default:
            throw json_unexpected_token_exception("'}'",s.expecting);
        }
        decrease_stack();

    }
    inline void handle_begin_array() {
        stack_slot& s =  current_slot();
        switch ( s.expecting ) {
        case ObjectValue:
        case SingleValue:
            s.array_value = &( s.handle->template coerce_value< json_array >() );
            s.expecting = ArrayItem;
            break;

        case ArrayItem: {
            json_value_handle& new_handle = s.array_value->append(); //s.handle->template cast_value< json_array>().append();
            json_array& new_handle_value = new_handle.template coerce_value< json_array>();
            s.expecting = ArrayItemSeparator;
            current_slot();
            increase_stack();
            stack_slot& new_s =  current_slot();
            new_s.handle = &new_handle;
            new_s.handle = &new_handle;
            new_s.array_value = &new_handle_value;
            new_s.expecting = ArrayItem;
        }
        break;
        default:
            //assert( s.expecting == ObjectValue || s.expecting == SingleValue || s.expecting == ArrayItem );
            throw json_unexpected_token_exception("'['",s.expecting);
        }


    }
    inline void handle_end_array() {
        stack_slot& s =  current_slot();
        switch ( s.expecting ) {
        case ArrayItem:
        case ArrayItemSeparator:
            break;
        default:
            throw json_unexpected_token_exception("']'",s.expecting);
        }
        decrease_stack();
    }

    inline void  handle_bracket( char c ) {
        JSON_PARSER_COUT << " ("  << c << ")\n";

        switch (c) {
        case '[':
            handle_begin_array();
            break;
        case ']':
            handle_end_array();
            break;
        case '{':
            handle_begin_object();
            break;
        case '}':
            handle_end_object();
            break;
        }
    }

    inline void handle_comma() {
        stack_slot& s =  current_slot();
        switch ( s.expecting ) {
        case ArrayItemSeparator:
            s.expecting = ArrayItem;
            break;
        case ObjectItemSeparator:
            s.expecting = ObjectKey;
            break;
        default:
            throw json_unexpected_token_exception("','",s.expecting);
        }

    }
    inline void handle_colon() {
        stack_slot& s =  current_slot();
        switch ( s.expecting ) {
        case ObjectKeySeparator:
            s.expecting = ObjectValue;
            break;
        default:
            throw json_unexpected_token_exception("':'",s.expecting);
        }

    }
    inline void  handle_separator( char c ) {
        JSON_PARSER_COUT << " <"  << c << ">\n";

        switch (c) {
        case ':':
            handle_colon();
            break;
        case ',':
            handle_comma();
            break;

        }
    }

    inline void  handle_token( std::string&& token, bool is_quoted = false ) {
        JSON_PARSER_COUT << "handle_token |"  << token << "| " << is_quoted << "\n";

        stack_slot& s =  current_slot();
        switch ( s.expecting ) {
        case ObjectKey: {
            json_value_handle& new_handle = s.object_value->item(token); // s.handle->template cast_value< json_object >().item(token);
            s.expecting = ObjectItemSeparator;
            current_slot();
            increase_stack();
            stack_slot& new_s =  current_slot();
            new_s.handle = &new_handle;
            new_s.expecting = ObjectKeySeparator;
        }
        break;
        case ObjectValue:
            read_value( std::move(token), is_quoted, *s.handle);
            s.expecting = Nothing;
            decrease_stack();
            break;
        case SingleValue:
            read_value( std::move(token), is_quoted, *s.handle);
            s.expecting = Nothing;
            break;
        case ArrayItem: {
            json_value_handle& new_obj = s.array_value->append(); //s.handle->template cast_value< json_array>().append();
            read_value( std::move(token), is_quoted, new_obj);
            s.expecting = ArrayItemSeparator;
        }
        break;
        default:
            throw json_unexpected_token_exception("a value",s.expecting);
        }
    }

    inline void  handle_qstring( std::string&& s) {
        JSON_PARSER_COUT << " \""  << s << "\"\n";
        handle_token(std::move(s),true);
    }

    inline void read_value( std::string&& token, bool is_quoted, json_value_handle& o ) {
        if ( is_quoted ) {
            o.template cast_value< json_string>().set(std::move(token));
        } else {
            if ( token == "true" ) {
                o.template cast_value< json_bool>().set(true);
            } else if ( token == "false" ) {
                o.template cast_value< json_bool>().set(false);
            } else if ( token == "null" ) {
                o = json_value_handle();
            } else if ( token.find('.') != token.npos || token.find('e') != token.npos || token.find('E') != token.npos ) {
                typename json_value_handle::number_t v;
//              std::cerr << " -------- " << token << " ----------\n";
                v = strtold( token.c_str(), 0 );
                o.template cast_value< json_number>().set(v);
            } else {
                typename json_value_handle::integer_t v;
                v = strtoll( token.c_str(), 0, 10 );
                o.template cast_value< json_integer>().set(v);
            }
        }
    }

};

}
}
}

#endif
