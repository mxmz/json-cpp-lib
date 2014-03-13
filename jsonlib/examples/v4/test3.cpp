#include <iostream>
using namespace std;

#include "json/v4/json_std.h"


using namespace mxmz::json::v4::std;

int main() {

        typedef json_value_handle::json_scalar json_scalar;
        typedef json_value_handle::json_string json_string;
        typedef json_value_handle::json_string json_string;

        json_value_handle obj;
        
        try {
            
            cin >> obj;
            
        } catch( std::exception& e ) {
            cerr << e.what() << endl;
        }
        //cerr << type_tag_name(obj.type()) << endl;
              
        cout << obj;
        cout << endl;
        
        cout << ( obj.try_cast<json_value_handle::json_number>().get<bool>() ) << endl;
        
}
