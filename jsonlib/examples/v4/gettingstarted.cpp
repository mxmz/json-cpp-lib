  
  #include "mxmz/json/v4/json_std.h"
  #include <iostream>

  namespace js = mxmz::json::v4::std;
  

  int main() {
        
       js::json_value_handle v;

       std::cin >> v;   // parse from stdin, throws on errors
  
       std::cout << v << "\n";   // print JSON


      v = js::json_value_handle(); // set to null
      
      // autovivification! 
      v["foo"]["bar"][2] = "hello world"; 
      v["foo"]["ber"] = 12.02; 
                                           
     std::cout  << v << "\n";
     /* prints
         {"foo":{"bar":[null,null,"hello world"],"ber":12.02}}
     */


       js::json_value_handle v2;
       
       v2 = v.clone();

       v2["foo"]["bar"] = 3;

       std::cout << v2 << "\n";
     
  }
