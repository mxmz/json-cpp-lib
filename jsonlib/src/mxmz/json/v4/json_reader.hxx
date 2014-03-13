#ifndef json_reader_hxx_349857394857337625376235479059678059678004958348
#define json_reader_hxx_349857394857337625376235479059678059678004958348

#include <unistd.h>
#ifdef JSON_READER_DEBUG
#define JSON_READER_CERR if(1) std::cerr
#define JSON_READER_COUT if(1) std::cerr
#else
#define JSON_READER_CERR if(0) std::cerr
#define JSON_READER_COUT if(0) std::cerr
#endif
namespace mxmz {
namespace json {
namespace v4 {



template< class JsonTokenizerT >
struct json_reader_tmpl {
    typedef JsonTokenizerT json_tokenizer;
    typedef typename JsonTokenizerT::consumer_t consumer_t;
    typedef typename consumer_t::json_value_handle json_value_handle;

    json_value_handle   result;
    consumer_t          parser;
    json_tokenizer      tokenizer;


    json_reader_tmpl() : parser(result), tokenizer(parser) {
    }

    class json_parse_exception: public std::exception {
        std::string message;

    public:
        const size_t line;
        const size_t offset;

        json_parse_exception(size_t l, size_t  c, std::string m ) : line(l), offset(c) {
            message.swap(m);
            char linespec[100];
            sprintf(linespec, " [line %d, offset %d]", l,c );
            message += linespec;
        }
        const char* what() const throw() {
            return message.c_str();
        }

        ~json_parse_exception() throw() {
        }

    };

    template< class IStreamT >
    void eat_comment_block(IStreamT& in, size_t&line, size_t&col ) {
        size_t line_save = line;
        size_t col_save = col;
        char c;
        while (1) {
            in >> c;
            //in.read(&c,1);
            if (  in.eof() ) break;
            ++col;
            if ( c == '*' ) {
                in >> c;
                //in.read(&c,1);
                if (  in.eof() ) break;
                ++col;
                if ( c == '/' ) return;
            }
            if ( c == '\n' ) {
                ++line;
                col = 0;
            }
        }
        throw json_parse_exception( line_save,col_save, "unterminated comment" );

    }
    template< class IStreamT >
    void eat_comment_line(IStreamT& in ) {
        char c;
        while (1) {
            in >> c;
            //in.read(&c,1);
            JSON_READER_CERR << "comment " << c << ":" << int(c) << "\n";
            if (  in.eof() ) break;
            if ( c == '\n' ) break;
        }
    }
    template< class IStreamT >
    void read( IStreamT& in, json_value_handle& o, bool handle_comments = false ) {
        char c;
        size_t line = 1;
        size_t col = 0;
        tokenizer.open();
        try {
            if ( ! handle_comments ) {
                while (1) {
                    in >> c;
                    if (  in.eof() ) break;
                    tokenizer.read(c);
                    ++col;
                    if ( c == '\n' ) {
                        ++line;
                        col = 0;
                    }
                }
            } else {
                while ( 1 ) {
                    in >> c;
                    //in.read(&c,1);
                    if (  in.eof() ) break;
                    ++col;
                    if ( ( c == '/') && (tokenizer.state != json_tokenizer::Quoted )) {
                        in >> c;
                        //in.read(&c,1);
                        if (  in.eof() ) break;
                        ++col;
                        if ( c == '*' ) {
                            tokenizer.read( ' ' );
                            eat_comment_block(in,line,col);
                            continue;
                        } else if (c == '/' ) {
                            tokenizer.read( ' ' );
                            eat_comment_line(in);
                            ++line;
                            col = 0;
                            continue;
                        } else {
                            tokenizer.read( '/' );
                            tokenizer.read( c );
                            if ( c == '\n' ) {
                                ++line;
                                col = 0;
                            }
                        }

                    } else {
                        tokenizer.read( c );
                        if ( c == '\n' ) {
                            ++line;
                            col = 0;
                        }
                    }

                }

            }
            tokenizer.read( ' ' );
            tokenizer.close();

        } catch ( typename consumer_t::json_unexpected_token_exception& e ) {
            throw json_parse_exception( line,col, e.message );

        } catch ( typename json_tokenizer::json_illegal_character& e ) {
            throw json_parse_exception( line,col, e.message );
        }
        result.swap(o);
    }

};


}
}
}



namespace mxmz {
namespace json {
namespace v4 {
namespace util {


struct buffer_reader {
    const char* buffer;
    size_t size;

    size_t cursor;
    bool eof_flag;

    buffer_reader(const char*p, size_t l ) {
        bind(p,l);
    }

    void bind( const char*p, size_t l ) {
        buffer = p;
        size = l;
        cursor = 0;
        eof_flag = false;
    }


    void rewind() {
        cursor = 0;
        eof_flag = false;
    }

    bool eof() const {
        return eof_flag;
    }

    inline  buffer_reader& operator>>( char & c ) {
        if (cursor == size) eof_flag = true;
        else {
            c = buffer[cursor++];
        }
        return *this;
    }
};

struct fd_reader {
    int fd;
    bool eof_flag;

    fd_reader(int fd )
            :   fd(fd), eof_flag(false) {
    }

    bool eof() const {
        return eof_flag;
    }

    fd_reader& operator>>( char & c ) {
        if ( ! eof_flag ) {
            int rc = read( fd, &c, 1 );
            if ( rc <= 0 ) eof_flag = true;
        }
        return *this;
    }
};

struct FILE_reader {
    FILE* fd;
    bool eof_flag;

    FILE_reader(FILE* fd )
            :   fd(fd), eof_flag(false) {
    }

    bool eof() const {
        return eof_flag;
    }

    FILE_reader& operator>>( char & c ) {
        if ( ! eof_flag ) {
            int rc = fread( &c, 1, 1, fd );
            if ( rc <= 0 ) eof_flag = true;
        }
        return *this;
    }
};



}
}
}
}


#endif
