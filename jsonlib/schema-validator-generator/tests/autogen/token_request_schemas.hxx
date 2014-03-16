

void assert_token_request_json1( json_value_handle& v );

const char* check_jminLength_10_type_string( json_value_handle& v ); // {"minLength":10,"type":"string"} //
const char* check_0bf7c339f6a2e8d6f6dac9c4153a88d0( json_value_handle& v ); // Token request types //
const char* check_7a6a557ebd7c2610209d8dc9c994fe9b( json_value_handle& v ); // http://tools.ietf.org/html/rfc6749#section-4.1.3 //
const char* check_e38cedb1f8d7085e9509b2a0a5e2d235( json_value_handle& v ); // {"enum":["remote"],"type":"string"} //
const char* check_5599647dbc2e0ff930dd8472864fa4a9( json_value_handle& v ); // {"enum":["password"],"type":"string"} //
const char* check_jminLength_3_type_string( json_value_handle& v ); // {"minLength":3,"type":"string"} //
const char* check_30cdd0569a3575decdc7e16204acfb3b( json_value_handle& v ); // KQI custom grant_type for token revoke request //
const char* check_7cb8d9afdfd297c47dbba48647740c3d( json_value_handle& v ); // {"enum":["revoke_token"],"type":"string" //
const char* check_2d1e342e85ba281b61a4c625c936f27b( json_value_handle& v ); // http://tools.ietf.org/html/rfc6749#section-6 //
const char* check_f06b13cdc3a5fae8b04a2bf7dd13297a( json_value_handle& v ); // http://tools.ietf.org/html/rfc6749#section-4.3 //
const char* check_jformat_uri_type_string( json_value_handle& v ); // {"format":"uri","type":"string"} //
const char* check_7b14d1ba94943f2ce668eed8a8202696( json_value_handle& v ); // {"oneOf":["jformat_uri_type_string","55a //
const char* check_jminLength_1_type_string( json_value_handle& v ); // {"minLength":1,"type":"string"} //
const char* check_5494d2cceca04a3fc18f1b6e02224588( json_value_handle& v ); // {"enum":["authorization_code","refresh_t //
const char* check_jminLength_5_type_string( json_value_handle& v ); // {"minLength":5,"type":"string"} //
const char* check_55afd20080e4cc7e4acbbc2782cb738f( json_value_handle& v ); // {"enum":["urn:ietf:wg:oauth:2.0:oob"],"t //
const char* check_2ce5560223962b474be176cfe28f825e( json_value_handle& v ); // {"enum":["authorization_code"],"type":"s //
const char* check_c39515b54b770376dfc81091e1b5b996( json_value_handle& v ); // {"pattern":"^(([\\w\\.]+:)+\\w+)(\\s+([\ //
const char* check_e408326af928f7be800ba70153eceab6( json_value_handle& v ); // {"enum":["refresh_token"],"type":"string //
const char* check_5b273d16aff7b76ab068bf1c967f4479( json_value_handle& v ); // KQI custom grant_type for remote identities //



#ifdef MXMZ_JSON_V4_IMPLEMENTATION
#include <set>

void assert_token_request_json1( json_value_handle& v ) {
        if ( const char* message = check_0bf7c339f6a2e8d6f6dac9c4153a88d0(v) ) {
            throw(message);
        }
}





// {"minLength":10,"type":"string"} //
/*{"minLength":10,"type":"string"}
*/   
const char* check_jminLength_10_type_string( json_value_handle& v ) { 





 return 0;
} 

// Token request types //
/*{"oneOf":["7a6a557ebd7c2610209d8dc9c994fe9b","2d1e342e85ba281b61a4c625c936f27b","f06b13cdc3a5fae8b04a2bf7dd13297a","5b273d16aff7b76ab068bf1c967f4479","30cdd0569a3575decdc7e16204acfb3b"],"required":["grant_type"],"properties":{"grant_type":"5494d2cceca04a3fc18f1b6e02224588"}}
*/   
const char* check_0bf7c339f6a2e8d6f6dac9c4153a88d0( json_value_handle& v ) { 
 // required
        if ( auto* grant_type = v.attribute( "grant_type"  ) ) {
        } else {
            return "Missing attribute " "grant_type";
        }
    
  // properties {"grant_type":"5494d2cceca04a3fc18f1b6e02224588"}
    if ( auto* grant_type = v.attribute( "grant_type"  )  ) {
     if ( const char* message = check_5494d2cceca04a3fc18f1b6e02224588 (*grant_type) ) {
         return message;
     }
    }
 // oneOf
    {   int count = 0;
            if ( ! check_7a6a557ebd7c2610209d8dc9c994fe9b(v) ) count++; // http://tools.ietf.org/html/rfc6749#section-4.1.3
            if ( ! check_2d1e342e85ba281b61a4c625c936f27b(v) ) count++; // http://tools.ietf.org/html/rfc6749#section-6
            if ( ! check_f06b13cdc3a5fae8b04a2bf7dd13297a(v) ) count++; // http://tools.ietf.org/html/rfc6749#section-4.3
            if ( ! check_5b273d16aff7b76ab068bf1c967f4479(v) ) count++; // KQI custom grant_type for remote identities
            if ( ! check_30cdd0569a3575decdc7e16204acfb3b(v) ) count++; // KQI custom grant_type for token revoke request
        if ( count != 1 ) {
                return "oneOf must match 1 and only one: " "Token request types" ;
        }
    }



 return 0;
} 

// http://tools.ietf.org/html/rfc6749#section-4.1.3 //
/*{"required":["grant_type","code","redirect_uri"],"properties":{"grant_type":"2ce5560223962b474be176cfe28f825e","redirect_uri":"7b14d1ba94943f2ce668eed8a8202696","code":"jminLength_10_type_string"}}
*/   
const char* check_7a6a557ebd7c2610209d8dc9c994fe9b( json_value_handle& v ) { 
 // required
        if ( auto* grant_type = v.attribute( "grant_type"  ) ) {
        } else {
            return "Missing attribute " "grant_type";
        }
    
        if ( auto* code = v.attribute( "code"  ) ) {
        } else {
            return "Missing attribute " "code";
        }
    
        if ( auto* redirect_uri = v.attribute( "redirect_uri"  ) ) {
        } else {
            return "Missing attribute " "redirect_uri";
        }
    
  // properties {"grant_type":"2ce5560223962b474be176cfe28f825e","redirect_uri":"7b14d1ba94943f2ce668eed8a8202696","code":"jminLength_10_type_string"}
    if ( auto* code = v.attribute( "code"  )  ) {
     if ( const char* message = check_jminLength_10_type_string (*code) ) {
         return message;
     }
    }
    if ( auto* grant_type = v.attribute( "grant_type"  )  ) {
     if ( const char* message = check_2ce5560223962b474be176cfe28f825e (*grant_type) ) {
         return message;
     }
    }
    if ( auto* redirect_uri = v.attribute( "redirect_uri"  )  ) {
     if ( const char* message = check_7b14d1ba94943f2ce668eed8a8202696 (*redirect_uri) ) {
         return message;
     }
    }




 return 0;
} 

// {"enum":["remote"],"type":"string"} //
/*{"enum":["remote"],"type":"string"}
*/    // enum
const    std::set<std::string> enum_e38cedb1f8d7085e9509b2a0a5e2d235 = {"remote" };
const char* check_e38cedb1f8d7085e9509b2a0a5e2d235( json_value_handle& v ) { 


 // enum
    if ( enum_e38cedb1f8d7085e9509b2a0a5e2d235.find(std::string(v) ) == enum_e38cedb1f8d7085e9509b2a0a5e2d235.end()  ) {
                    return "value must be one of enum" ;
     }


 return 0;
} 

// {"enum":["password"],"type":"string"} //
/*{"enum":["password"],"type":"string"}
*/    // enum
const    std::set<std::string> enum_5599647dbc2e0ff930dd8472864fa4a9 = {"password" };
const char* check_5599647dbc2e0ff930dd8472864fa4a9( json_value_handle& v ) { 


 // enum
    if ( enum_5599647dbc2e0ff930dd8472864fa4a9.find(std::string(v) ) == enum_5599647dbc2e0ff930dd8472864fa4a9.end()  ) {
                    return "value must be one of enum" ;
     }


 return 0;
} 

// {"minLength":3,"type":"string"} //
/*{"minLength":3,"type":"string"}
*/   
const char* check_jminLength_3_type_string( json_value_handle& v ) { 





 return 0;
} 

// KQI custom grant_type for token revoke request //
/*{"properties":{"revoke_token":"jminLength_1_type_string","grant_type":"7cb8d9afdfd297c47dbba48647740c3d"}}
*/   
const char* check_30cdd0569a3575decdc7e16204acfb3b( json_value_handle& v ) { 
  // properties {"revoke_token":"jminLength_1_type_string","grant_type":"7cb8d9afdfd297c47dbba48647740c3d"}
    if ( auto* grant_type = v.attribute( "grant_type"  )  ) {
     if ( const char* message = check_7cb8d9afdfd297c47dbba48647740c3d (*grant_type) ) {
         return message;
     }
    }
    if ( auto* revoke_token = v.attribute( "revoke_token"  )  ) {
     if ( const char* message = check_jminLength_1_type_string (*revoke_token) ) {
         return message;
     }
    }




 return 0;
} 

// {"enum":["revoke_token"],"type":"string" //
/*{"enum":["revoke_token"],"type":"string"}
*/    // enum
const    std::set<std::string> enum_7cb8d9afdfd297c47dbba48647740c3d = {"revoke_token" };
const char* check_7cb8d9afdfd297c47dbba48647740c3d( json_value_handle& v ) { 


 // enum
    if ( enum_7cb8d9afdfd297c47dbba48647740c3d.find(std::string(v) ) == enum_7cb8d9afdfd297c47dbba48647740c3d.end()  ) {
                    return "value must be one of enum" ;
     }


 return 0;
} 

// http://tools.ietf.org/html/rfc6749#section-6 //
/*{"required":["grant_type","refresh_token"],"properties":{"grant_type":"e408326af928f7be800ba70153eceab6","refresh_token":"jminLength_1_type_string","scope":"c39515b54b770376dfc81091e1b5b996"}}
*/   
const char* check_2d1e342e85ba281b61a4c625c936f27b( json_value_handle& v ) { 
 // required
        if ( auto* grant_type = v.attribute( "grant_type"  ) ) {
        } else {
            return "Missing attribute " "grant_type";
        }
    
        if ( auto* refresh_token = v.attribute( "refresh_token"  ) ) {
        } else {
            return "Missing attribute " "refresh_token";
        }
    
  // properties {"grant_type":"e408326af928f7be800ba70153eceab6","refresh_token":"jminLength_1_type_string","scope":"c39515b54b770376dfc81091e1b5b996"}
    if ( auto* grant_type = v.attribute( "grant_type"  )  ) {
     if ( const char* message = check_e408326af928f7be800ba70153eceab6 (*grant_type) ) {
         return message;
     }
    }
    if ( auto* refresh_token = v.attribute( "refresh_token"  )  ) {
     if ( const char* message = check_jminLength_1_type_string (*refresh_token) ) {
         return message;
     }
    }
    if ( auto* scope = v.attribute( "scope"  )  ) {
     if ( const char* message = check_c39515b54b770376dfc81091e1b5b996 (*scope) ) {
         return message;
     }
    }




 return 0;
} 

// http://tools.ietf.org/html/rfc6749#section-4.3 //
/*{"required":["grant_type","username","password"],"properties":{"password":"jminLength_1_type_string","grant_type":"5599647dbc2e0ff930dd8472864fa4a9","scope":"c39515b54b770376dfc81091e1b5b996","username":"jminLength_1_type_string"}}
*/   
const char* check_f06b13cdc3a5fae8b04a2bf7dd13297a( json_value_handle& v ) { 
 // required
        if ( auto* grant_type = v.attribute( "grant_type"  ) ) {
        } else {
            return "Missing attribute " "grant_type";
        }
    
        if ( auto* username = v.attribute( "username"  ) ) {
        } else {
            return "Missing attribute " "username";
        }
    
        if ( auto* password = v.attribute( "password"  ) ) {
        } else {
            return "Missing attribute " "password";
        }
    
  // properties {"password":"jminLength_1_type_string","grant_type":"5599647dbc2e0ff930dd8472864fa4a9","scope":"c39515b54b770376dfc81091e1b5b996","username":"jminLength_1_type_string"}
    if ( auto* grant_type = v.attribute( "grant_type"  )  ) {
     if ( const char* message = check_5599647dbc2e0ff930dd8472864fa4a9 (*grant_type) ) {
         return message;
     }
    }
    if ( auto* password = v.attribute( "password"  )  ) {
     if ( const char* message = check_jminLength_1_type_string (*password) ) {
         return message;
     }
    }
    if ( auto* scope = v.attribute( "scope"  )  ) {
     if ( const char* message = check_c39515b54b770376dfc81091e1b5b996 (*scope) ) {
         return message;
     }
    }
    if ( auto* username = v.attribute( "username"  )  ) {
     if ( const char* message = check_jminLength_1_type_string (*username) ) {
         return message;
     }
    }




 return 0;
} 

// {"format":"uri","type":"string"} //
/*{"format":"uri","type":"string"}
*/   
const char* check_jformat_uri_type_string( json_value_handle& v ) { 





 return 0;
} 

// {"oneOf":["jformat_uri_type_string","55a //
/*{"oneOf":["jformat_uri_type_string","55afd20080e4cc7e4acbbc2782cb738f"]}
*/   
const char* check_7b14d1ba94943f2ce668eed8a8202696( json_value_handle& v ) { 

 // oneOf
    {   int count = 0;
            if ( ! check_jformat_uri_type_string(v) ) count++; // {"format":"uri","type":"string"}
            if ( ! check_55afd20080e4cc7e4acbbc2782cb738f(v) ) count++; // {"enum":["urn:ietf:wg:oauth:2.0:oob"],"t
        if ( count != 1 ) {
                return "oneOf must match 1 and only one: " "{\"oneOf\":[\"jformat_uri_type_string\",\"55a" ;
        }
    }



 return 0;
} 

// {"minLength":1,"type":"string"} //
/*{"minLength":1,"type":"string"}
*/   
const char* check_jminLength_1_type_string( json_value_handle& v ) { 





 return 0;
} 

// {"enum":["authorization_code","refresh_t //
/*{"enum":["authorization_code","refresh_token","password","revoke_token","remote"],"type":"string"}
*/    // enum
const    std::set<std::string> enum_5494d2cceca04a3fc18f1b6e02224588 = {"authorization_code","refresh_token","password","revoke_token","remote" };
const char* check_5494d2cceca04a3fc18f1b6e02224588( json_value_handle& v ) { 


 // enum
    if ( enum_5494d2cceca04a3fc18f1b6e02224588.find(std::string(v) ) == enum_5494d2cceca04a3fc18f1b6e02224588.end()  ) {
                    return "value must be one of enum" ;
     }


 return 0;
} 

// {"minLength":5,"type":"string"} //
/*{"minLength":5,"type":"string"}
*/   
const char* check_jminLength_5_type_string( json_value_handle& v ) { 





 return 0;
} 

// {"enum":["urn:ietf:wg:oauth:2.0:oob"],"t //
/*{"enum":["urn:ietf:wg:oauth:2.0:oob"],"type":"string"}
*/    // enum
const    std::set<std::string> enum_55afd20080e4cc7e4acbbc2782cb738f = {"urn:ietf:wg:oauth:2.0:oob" };
const char* check_55afd20080e4cc7e4acbbc2782cb738f( json_value_handle& v ) { 


 // enum
    if ( enum_55afd20080e4cc7e4acbbc2782cb738f.find(std::string(v) ) == enum_55afd20080e4cc7e4acbbc2782cb738f.end()  ) {
                    return "value must be one of enum" ;
     }


 return 0;
} 

// {"enum":["authorization_code"],"type":"s //
/*{"enum":["authorization_code"],"type":"string"}
*/    // enum
const    std::set<std::string> enum_2ce5560223962b474be176cfe28f825e = {"authorization_code" };
const char* check_2ce5560223962b474be176cfe28f825e( json_value_handle& v ) { 


 // enum
    if ( enum_2ce5560223962b474be176cfe28f825e.find(std::string(v) ) == enum_2ce5560223962b474be176cfe28f825e.end()  ) {
                    return "value must be one of enum" ;
     }


 return 0;
} 

// {"pattern":"^(([\\w\\.]+:)+\\w+)(\\s+([\ //
/*{"pattern":"^(([\\w\\.]+:)+\\w+)(\\s+([\\w\\.]+:)+\\w+)*$","minLength":5,"type":"string"}
*/   
const char* check_c39515b54b770376dfc81091e1b5b996( json_value_handle& v ) { 





 return 0;
} 

// {"enum":["refresh_token"],"type":"string //
/*{"enum":["refresh_token"],"type":"string"}
*/    // enum
const    std::set<std::string> enum_e408326af928f7be800ba70153eceab6 = {"refresh_token" };
const char* check_e408326af928f7be800ba70153eceab6( json_value_handle& v ) { 


 // enum
    if ( enum_e408326af928f7be800ba70153eceab6.find(std::string(v) ) == enum_e408326af928f7be800ba70153eceab6.end()  ) {
                    return "value must be one of enum" ;
     }


 return 0;
} 

// KQI custom grant_type for remote identities //
/*{"required":["grant_type","type","token"],"properties":{"grant_type":"e38cedb1f8d7085e9509b2a0a5e2d235","type":"jminLength_3_type_string","token":"jminLength_5_type_string","scope":"c39515b54b770376dfc81091e1b5b996"}}
*/   
const char* check_5b273d16aff7b76ab068bf1c967f4479( json_value_handle& v ) { 
 // required
        if ( auto* grant_type = v.attribute( "grant_type"  ) ) {
        } else {
            return "Missing attribute " "grant_type";
        }
    
        if ( auto* type = v.attribute( "type"  ) ) {
        } else {
            return "Missing attribute " "type";
        }
    
        if ( auto* token = v.attribute( "token"  ) ) {
        } else {
            return "Missing attribute " "token";
        }
    
  // properties {"grant_type":"e38cedb1f8d7085e9509b2a0a5e2d235","type":"jminLength_3_type_string","token":"jminLength_5_type_string","scope":"c39515b54b770376dfc81091e1b5b996"}
    if ( auto* grant_type = v.attribute( "grant_type"  )  ) {
     if ( const char* message = check_e38cedb1f8d7085e9509b2a0a5e2d235 (*grant_type) ) {
         return message;
     }
    }
    if ( auto* scope = v.attribute( "scope"  )  ) {
     if ( const char* message = check_c39515b54b770376dfc81091e1b5b996 (*scope) ) {
         return message;
     }
    }
    if ( auto* token = v.attribute( "token"  )  ) {
     if ( const char* message = check_jminLength_5_type_string (*token) ) {
         return message;
     }
    }
    if ( auto* type = v.attribute( "type"  )  ) {
     if ( const char* message = check_jminLength_3_type_string (*type) ) {
         return message;
     }
    }




 return 0;
} 










#endif
