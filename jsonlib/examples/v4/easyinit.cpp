  
  #include "mxmz/json/v4/json_std.hxx"
  #include <iostream>
  
  namespace js = mxmz::json::v4::std;

  int main() {
        
       js::json_value_handle v;
        v = 
        ( js::ObjectBeg
                << "hello"  << ( js::ArrayBeg
                                     << "pippo" 
                                     << "foo" 
                                     << 1 
                                     << 2 
                                     << 3 
                                     << ( js::ObjectBeg
                                          << "pippo" << 45
                                         << js::ObjectEnd )
                                << js::ArrayEnd )
                << "what" << "never"
                << "what" << js::json_value_handle()
         << js::ObjectEnd );

       std::cout << "v: " << v << "\n";
  }
