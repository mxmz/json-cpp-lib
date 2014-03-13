#include <iostream>
using namespace std;

#include "mxmz/json/v4/json_std.hxx"

using namespace mxmz::json::v4::std;
using namespace mxmz::json::v4::util;

void slurp( ::std::istream& in, std::string& data );
::std::string slurp( ::std::istream& in );



template < class D, class  C >
typename mxmz::json::v4::json_value_handle_tmpl<D,C>::json_array& as_vector( 
                mxmz::json::v4::json_value_handle_tmpl<D,C>& v ) {
    return v.template cast_value<json_array>(true);
}




int main() {
        json_value_handle obj;

        as_vector(obj);

        try {
 //           std::string data;
   //         slurp( cin , data );
     //       cerr << "slurped " << data.size() << endl;
     //       data >> obj ;
            slurp(cin) >> obj;
            cerr << "parsed" << endl;

        } catch( std::exception& e ) {
            cerr << e.what() << endl;
            exit(-1);
        }

        std::string out;
       cout <<  ( out << obj ) << endl;
//        cout <<  obj  << endl;


    //    cout << obj;
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
