#include <iostream>
#include <string>
#include "json_lexcast.hxx"

using mxmz::json::v4::convert;
using namespace std;

int main () {

    std::string s = convert<std::string>("ciao");

    cerr << s << endl;

    std::string v("10.59e12");

    long long int i1 = convert<long long int>(v.c_str() );

    long double d1 = convert<long double>( v.c_str() );
    double d2 = convert<double>(true);
    std::string s1;
        s1 = convert<std::string>( 100 ) ;

    cerr << s1 << endl;

    std::string s2( convert<std::string>( d1 ) );
    std::string s3( convert<std::string>( true ) );

    cerr << i1 << endl;
    cerr << d1 << endl;
    cerr << d2 << endl;
    cerr << s1 << endl;
    cerr << s2 << endl;
    cerr << s3 << endl;




}
