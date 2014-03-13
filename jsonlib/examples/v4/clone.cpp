  
  #include "mxmz/json/v4/json_std.h"
  #include <iostream>

  namespace js = mxmz::json::v4::std;
  

  int main() {
        
       js::json_value_handle v;

       std::cin >> v;   // parse from stdin, throws on errors
  
       std::cout << v << "\n";   // print JSON

       js::json_value_handle v2;
       
       v2 = v.clone();

       std::cout << "v2: " << v2 << "\n";
  
     
       js::json_value_handle v3 ;
       v3 = std::move(v2) ;
       std::cout << "v3: " << v3 << "\n";
       std::cout << "v2: " << v2 << "\n";
  }
