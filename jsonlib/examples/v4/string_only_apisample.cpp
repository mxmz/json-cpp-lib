#include <string>
#include <map>
#include <iostream>
using namespace std;

typedef std::map<std::string,std::string> map_t;

namespace apisample {

template< class T, class ObjT >
struct get_member_helper {
    typedef ObjT&       return_type;
//    ObjT& operator()( ObjT& arg, const std::string& k ) {
 //       return arg[k];
  //  }
};

template< class T , class V >
struct get_member_helper < T, ::std::map< ::std::string, V > >   {
        typedef ::std::map< ::std::string, V > map_type;
        typedef typename  map_type::value_type::second_type       return_type;
    return_type& operator()( map_type& arg, const std::string& k ) {
        return arg[k];
    }
};


template< class T, class MapT>
typename get_member_helper<T,MapT>::return_type get_member( MapT& arg, const std::string& k ) {
        get_member_helper<T,MapT>    helper;
        return helper(arg,k);
}




#include "__string_only_apisample.hxx"
}

int main() {

    map_t m;

    m["string1"] = "ciao1";
    m["string2"] = "ciao2";
    m["string3"] = "ciao3";

    apisample::message msg(m);

    cout << msg.get_string1() << endl;
    cout << msg.get_string2() << endl;
    cout << msg.get_string3() << endl;


}
