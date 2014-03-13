#include <iostream>
using namespace std;

#include "mxmz/json/v4/json_std.hxx"
#include "mxmz/json/v4/csv_reader.hxx"

using namespace mxmz::json::v4::std;
using namespace mxmz::json::v4::util;

void slurp( ::std::istream& in, std::string& data );
::std::string slurp( ::std::istream& in );

typedef mxmz::json::v4::json_parser_tmpl<json_value_handle>     parser_t;
typedef mxmz::json::v4::csv_reader_tmpl<parser_t> csv_reader_t;




int main() {
        json_value_handle obj;


        try {
            csv_reader_t reader;
            cin.unsetf(::std::ios_base::skipws);
            reader.read(cin, obj, ',' );
            cerr << "parsed" << endl;

        } catch( std::exception& e ) {
            cerr << e.what() << endl;
            exit(-1);
        }

        std::string out;
        cout <<  ( out << obj ) << endl;
        cerr << "printed" << endl;
}


void slurp( ::std::istream& in, std::string& data )
{
        data.clear();
        data.reserve( 1024*1024 );
//        char buf[1000000];
        while ( in )
        {
  //              in.read(buf, 1000000);
  //              data.append(buf, in.gcount());

                size_t size = data.size();
                data.resize( size + 10*1024 );
                in.read( &data[0] + size, 10*1024 );
                data.resize( size + in.gcount()  );

        }

        if ( in.bad() )
        {
                // an error occurred while reading
                throw "error while reading file";
        }
}

::std::string slurp( ::std::istream& in ) {
    ::std::string data;
    slurp(in,data);
    return data;
}
