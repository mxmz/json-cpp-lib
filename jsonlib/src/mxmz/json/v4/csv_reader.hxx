#ifndef csv_reader_hxx_3049853049583049583049853049850349850394850394850
#define csv_reader_hxx_3049853049583049583049853049850349850394850394850

#include <unistd.h>
#include <exception>
#ifdef CSV_READER_DEBUG
#define CSV_READER_CERR if(1) std::cerr
#define CSV_READER_CERR if(1) std::cerr
#else
#define CSV_READER_CERR if(0) std::cerr
#define CSV_READER_CERR if(0) std::cerr
#endif
namespace mxmz {
namespace json {
namespace v4 {


template< class ConsumerT >
struct csv_reader_tmpl {
    typedef ConsumerT consumer_t;
    typedef typename consumer_t::json_value_handle json_value_handle;

    json_value_handle   result;
    consumer_t          parser;

    csv_reader_tmpl() : parser(result) {
    }

    class csv_parse_exception
            : public ::std::exception {
        ::std::string message;

    public:
        const size_t line;
        const size_t offset;

        csv_parse_exception(size_t l, size_t  c, ::std::string m ) : line(l), offset(c) {
            message.swap(m);
            char linespec[100];
            sprintf(linespec, " [line %d, offset %d]", l,c );
            message += linespec;
        }
        const char* what() const throw() {
            return message.c_str();
        }

        ~csv_parse_exception() throw() {
        }

    };
    static const char double_quotes = '"';
    static const char end_of_line   = '\n';

    template< class IStreamT >
    void read( IStreamT& in, json_value_handle& o, char separator = ',' ) {
        char c;
        size_t line = 1;
        size_t offset = 0;
        size_t column = 0;
        size_t record = 0;
        enum state_t { Unquoted, Quoted };
        parser.handle_begin_array();
        state_t state = Unquoted;
        ::std::string buffer;
        try {

                while (1) {
                    in >> c;
                    if (  in.eof() ) break;
                    ++offset; if ( c == '\n' ) { ++line; offset = 0; }

                    if ( state ==  Quoted ) {
                            if ( c == double_quotes ) {
                                in >> c;
                                ++offset;
                                if ( c == double_quotes ) { // double double-quotes
                                    buffer.append(&c,1);
                                    continue;
                                } else {
                                    if ( c == '\n' ) { ++line; offset = 0; }
                                    state = Unquoted;  // no break!
                                }

                            } else {
                                    buffer.append(&c,1);
                                    continue;
                            }
                        }
                        if ( state ==  Unquoted ) {
                            if ( c == separator ) {
                                push_value( record == 0, column == 0, ::std::move(buffer) );
                                buffer.resize(0);
                                ++column;
                            } else
                            if ( c == '\r' ) {
                            } else
                            if ( c == end_of_line ) {
                                push_value( record == 0, column == 0, ::std::move(buffer) );
                                buffer.resize(0);
                                column = 0;
                                ++record;
                            }
                            else
                            if ( c == double_quotes ) {
                                if ( ! buffer.empty() ) {
                                    throw csv_parse_exception( line,offset, "Unexpected double quotes" );
                                }
                                state = Quoted;
                            } else {

                                buffer.append(&c,1);
                            }
                        }
                }
            push_value( record == 0, column == 0, ::std::move(buffer), true );
            parser.handle_end_array();
            parser.handle_end_document();

        } catch ( typename consumer_t::json_unexpected_token_exception& e ) {
            throw csv_parse_exception( line, offset, e.message );

        }
        result.swap(o);
    }

    void push_value(  bool first_record, bool first_column, ::std::string&& value, bool is_last = false ) {
        if ( first_column ) {
            if ( first_record ) {
                parser.handle_begin_array();
            } else {
                parser.handle_end_array();
                parser.handle_comma();
                parser.handle_begin_array();
            }
        } else {
            parser.handle_comma();
        }
        if ( is_last ) {
            if ( ! value.empty() ) {
                parser.handle_qstring( ::std::move(value) );
            }
            parser.handle_end_array();


        } else {
            parser.handle_qstring( ::std::move(value) );
        }
    }




};


}
}
}




#endif
