

void assert_token_request_json1( json_value_handle& v );

const char* check_813d7836431a71c50750ee4fa462296db61f0b88( json_value_handle& v ); // {"enum":["refresh_token"],"type":"string //
const char* check_7f72af75b029951947c54c0c35744efdc8e4ef40( json_value_handle& v ); // {"enum":["password"],"type":"string"} //
const char* check_e21ac7ba60ebac162c6319801b525eadca2978bd( json_value_handle& v ); // {"enum":["authorization_code"],"type":"s //
const char* check_338f90f73fd99b260a510f2c7bce77639f0791cf( json_value_handle& v ); // {"enum":["revoke_token"],"type":"string" //
const char* check_a282002c48e893ebe85fb38e87cf4d0d7c0f9697( json_value_handle& v ); // {"enum":["authorization_code","refresh_t //
const char* check_956e97e4401594a9a90df1c67968da468fbd979e( json_value_handle& v ); // http://tools.ietf.org/html/rfc6749#section-4.1.3 //
const char* check_aff948820f2a9e3188cea37ba1ab7e6db41c85b9( json_value_handle& v ); // {"pattern":"^(([\\w\\.]+:)+\\w+)(\\s+([\ //
const char* check_8937091eb5dd77e18d573f38de19940d34e1b6d9( json_value_handle& v ); // http://tools.ietf.org/html/rfc6749#section-6 //
const char* check_94b16e2e791613fcb3a4cf79a5cd7fa79433bf73( json_value_handle& v ); // {"enum":["remote"],"type":"string"} //
const char* check_a2ffe808ab8f05fe610d5fbc0c29bf5aa883b8e9( json_value_handle& v ); // Token request types //
const char* check_14e95954da43939733abe09d41f7699aa62dcb17( json_value_handle& v ); // KQI custom grant_type for token revoke request //
const char* check_jformat_uri_type_string( json_value_handle& v ); // {"format":"uri","type":"string"} //
const char* check_jminLength_1_type_string( json_value_handle& v ); // {"minLength":1,"type":"string"} //
const char* check_a88c5a8894f85d0a295670f15956eee9d25a833d( json_value_handle& v ); // http://tools.ietf.org/html/rfc6749#section-4.3 //
const char* check_5fd67638293b5fde3046c63e48ed984dc4523f5a( json_value_handle& v ); // KQI custom grant_type for remote identities //
const char* check_f509cb62059c9cab3f4105ab68f5c4faed4b2927( json_value_handle& v ); // {"oneOf":[{"format":"uri","type":"string //
const char* check_e4e0fc27050f4b7bfbe0f2e3da5ddabf8c3301be( json_value_handle& v ); // {"enum":["urn:ietf:wg:oauth:2.0:oob"],"t //



#ifdef MXMZ_JSON_V4_IMPLEMENTATION

void assert_token_request_json1( json_value_handle& v ) {
        if ( const char* message = check_a2ffe808ab8f05fe610d5fbc0c29bf5aa883b8e9(v) ) {
            throw(message);
        }
}





// {"enum":["refresh_token"],"type":"string //
/*[{"value":["refresh_token"],"type":"equals_one_of"},{"value":"string","type":"has_type"}]
*/   
const char* check_813d7836431a71c50750ee4fa462296db61f0b88( json_value_handle& v ) {  // equals_one_of
    {    
                 if ( std::string(v) == "refresh_token"  ) {
                            return 0;
                  }
            return "value must be one of enum" ;
    }




 return 0;
} 

// {"enum":["password"],"type":"string"} //
/*[{"value":["password"],"type":"equals_one_of"},{"value":"string","type":"has_type"}]
*/   
const char* check_7f72af75b029951947c54c0c35744efdc8e4ef40( json_value_handle& v ) {  // equals_one_of
    {    
                 if ( std::string(v) == "password"  ) {
                            return 0;
                  }
            return "value must be one of enum" ;
    }




 return 0;
} 

// {"enum":["authorization_code"],"type":"s //
/*[{"value":["authorization_code"],"type":"equals_one_of"},{"value":"string","type":"has_type"}]
*/   
const char* check_e21ac7ba60ebac162c6319801b525eadca2978bd( json_value_handle& v ) {  // equals_one_of
    {    
                 if ( std::string(v) == "authorization_code"  ) {
                            return 0;
                  }
            return "value must be one of enum" ;
    }




 return 0;
} 

// {"enum":["revoke_token"],"type":"string" //
/*[{"value":["revoke_token"],"type":"equals_one_of"},{"value":"string","type":"has_type"}]
*/   
const char* check_338f90f73fd99b260a510f2c7bce77639f0791cf( json_value_handle& v ) {  // equals_one_of
    {    
                 if ( std::string(v) == "revoke_token"  ) {
                            return 0;
                  }
            return "value must be one of enum" ;
    }




 return 0;
} 

// {"enum":["authorization_code","refresh_t //
/*[{"value":["authorization_code","refresh_token","password","revoke_token","remote"],"type":"equals_one_of"},{"value":"string","type":"has_type"}]
*/   
const char* check_a282002c48e893ebe85fb38e87cf4d0d7c0f9697( json_value_handle& v ) {  // equals_one_of
    {    
                 if ( std::string(v) == "authorization_code"  ) {
                            return 0;
                  } 
                 if ( std::string(v) == "refresh_token"  ) {
                            return 0;
                  } 
                 if ( std::string(v) == "password"  ) {
                            return 0;
                  } 
                 if ( std::string(v) == "revoke_token"  ) {
                            return 0;
                  } 
                 if ( std::string(v) == "remote"  ) {
                            return 0;
                  }
            return "value must be one of enum" ;
    }




 return 0;
} 

// http://tools.ietf.org/html/rfc6749#section-4.1.3 //
/*[{"value":["grant_type","code","redirect_uri"],"type":"must_have"},{"value":{"name":"grant_type","schema":"e21ac7ba60ebac162c6319801b525eadca2978bd"},"type":"has_property"},{"value":{"name":"redirect_uri","schema":"f509cb62059c9cab3f4105ab68f5c4faed4b2927"},"type":"has_property"},{"value":{"name":"code","schema":"jminLength_1_type_string"},"type":"has_property"}]
*/   
const char* check_956e97e4401594a9a90df1c67968da468fbd979e( json_value_handle& v ) { 
 
    
    json_value_handle& grant_type = v[ "grant_type" ];
     if ( const char* message = check_e21ac7ba60ebac162c6319801b525eadca2978bd (grant_type) ) {
         return message;
    }
 
    
    json_value_handle& redirect_uri = v[ "redirect_uri" ];
     if ( const char* message = check_f509cb62059c9cab3f4105ab68f5c4faed4b2927 (redirect_uri) ) {
         return message;
    }
 
    
    json_value_handle& code = v[ "code" ];
     if ( const char* message = check_jminLength_1_type_string (code) ) {
         return message;
    }

 return 0;
} 

// {"pattern":"^(([\\w\\.]+:)+\\w+)(\\s+([\ //
/*[{"value":"string","type":"has_type"}]
*/   
const char* check_aff948820f2a9e3188cea37ba1ab7e6db41c85b9( json_value_handle& v ) { 

 return 0;
} 

// http://tools.ietf.org/html/rfc6749#section-6 //
/*[{"value":["grant_type","refresh_token"],"type":"must_have"},{"value":{"name":"grant_type","schema":"813d7836431a71c50750ee4fa462296db61f0b88"},"type":"has_property"},{"value":{"name":"refresh_token","schema":"jminLength_1_type_string"},"type":"has_property"},{"value":{"name":"scope","schema":"aff948820f2a9e3188cea37ba1ab7e6db41c85b9"},"type":"has_property"}]
*/   
const char* check_8937091eb5dd77e18d573f38de19940d34e1b6d9( json_value_handle& v ) { 
 
    
    json_value_handle& grant_type = v[ "grant_type" ];
     if ( const char* message = check_813d7836431a71c50750ee4fa462296db61f0b88 (grant_type) ) {
         return message;
    }
 
    
    json_value_handle& refresh_token = v[ "refresh_token" ];
     if ( const char* message = check_jminLength_1_type_string (refresh_token) ) {
         return message;
    }
 
    
    json_value_handle& scope = v[ "scope" ];
     if ( const char* message = check_aff948820f2a9e3188cea37ba1ab7e6db41c85b9 (scope) ) {
         return message;
    }

 return 0;
} 

// {"enum":["remote"],"type":"string"} //
/*[{"value":["remote"],"type":"equals_one_of"},{"value":"string","type":"has_type"}]
*/   
const char* check_94b16e2e791613fcb3a4cf79a5cd7fa79433bf73( json_value_handle& v ) {  // equals_one_of
    {    
                 if ( std::string(v) == "remote"  ) {
                            return 0;
                  }
            return "value must be one of enum" ;
    }




 return 0;
} 

// Token request types //
/*[{"value":["grant_type"],"type":"must_have"},{"value":["956e97e4401594a9a90df1c67968da468fbd979e","8937091eb5dd77e18d573f38de19940d34e1b6d9","a88c5a8894f85d0a295670f15956eee9d25a833d","5fd67638293b5fde3046c63e48ed984dc4523f5a","14e95954da43939733abe09d41f7699aa62dcb17"],"type":"satisfies_one"},{"value":{"name":"grant_type","schema":"a282002c48e893ebe85fb38e87cf4d0d7c0f9697"},"type":"has_property"}]
*/   
const char* check_a2ffe808ab8f05fe610d5fbc0c29bf5aa883b8e9( json_value_handle& v ) { 

    {   int count = 0;
            if ( ! check_956e97e4401594a9a90df1c67968da468fbd979e(v) ) count++; // http://tools.ietf.org/html/rfc6749#section-4.1.3
            if ( ! check_8937091eb5dd77e18d573f38de19940d34e1b6d9(v) ) count++; // http://tools.ietf.org/html/rfc6749#section-6
            if ( ! check_a88c5a8894f85d0a295670f15956eee9d25a833d(v) ) count++; // http://tools.ietf.org/html/rfc6749#section-4.3
            if ( ! check_5fd67638293b5fde3046c63e48ed984dc4523f5a(v) ) count++; // KQI custom grant_type for remote identities
            if ( ! check_14e95954da43939733abe09d41f7699aa62dcb17(v) ) count++; // KQI custom grant_type for token revoke request
        if ( count != 1 ) {
                return "oneOf must match 1 and only one: " "Token request types" ;
        }
    }
 
    
    json_value_handle& grant_type = v[ "grant_type" ];
     if ( const char* message = check_a282002c48e893ebe85fb38e87cf4d0d7c0f9697 (grant_type) ) {
         return message;
    }

 return 0;
} 

// KQI custom grant_type for token revoke request //
/*[{"value":{"name":"revoke_token","schema":"jminLength_1_type_string"},"type":"has_property"},{"value":{"name":"grant_type","schema":"338f90f73fd99b260a510f2c7bce77639f0791cf"},"type":"has_property"}]
*/   
const char* check_14e95954da43939733abe09d41f7699aa62dcb17( json_value_handle& v ) {  
    
    json_value_handle& revoke_token = v[ "revoke_token" ];
     if ( const char* message = check_jminLength_1_type_string (revoke_token) ) {
         return message;
    }
 
    
    json_value_handle& grant_type = v[ "grant_type" ];
     if ( const char* message = check_338f90f73fd99b260a510f2c7bce77639f0791cf (grant_type) ) {
         return message;
    }

 return 0;
} 

// {"format":"uri","type":"string"} //
/*[{"value":"uri","type":"has_format"},{"value":"string","type":"has_type"}]
*/   
const char* check_jformat_uri_type_string( json_value_handle& v ) { 


 return 0;
} 

// {"minLength":1,"type":"string"} //
/*[{"value":"string","type":"has_type"}]
*/   
const char* check_jminLength_1_type_string( json_value_handle& v ) { 

 return 0;
} 

// http://tools.ietf.org/html/rfc6749#section-4.3 //
/*[{"value":["grant_type","username","password"],"type":"must_have"},{"value":{"name":"password","schema":"jminLength_1_type_string"},"type":"has_property"},{"value":{"name":"grant_type","schema":"7f72af75b029951947c54c0c35744efdc8e4ef40"},"type":"has_property"},{"value":{"name":"scope","schema":"aff948820f2a9e3188cea37ba1ab7e6db41c85b9"},"type":"has_property"},{"value":{"name":"username","schema":"jminLength_1_type_string"},"type":"has_property"}]
*/   
const char* check_a88c5a8894f85d0a295670f15956eee9d25a833d( json_value_handle& v ) { 
 
    
    json_value_handle& password = v[ "password" ];
     if ( const char* message = check_jminLength_1_type_string (password) ) {
         return message;
    }
 
    
    json_value_handle& grant_type = v[ "grant_type" ];
     if ( const char* message = check_7f72af75b029951947c54c0c35744efdc8e4ef40 (grant_type) ) {
         return message;
    }
 
    
    json_value_handle& scope = v[ "scope" ];
     if ( const char* message = check_aff948820f2a9e3188cea37ba1ab7e6db41c85b9 (scope) ) {
         return message;
    }
 
    
    json_value_handle& username = v[ "username" ];
     if ( const char* message = check_jminLength_1_type_string (username) ) {
         return message;
    }

 return 0;
} 

// KQI custom grant_type for remote identities //
/*[{"value":["grant_type","type","token"],"type":"must_have"},{"value":{"name":"grant_type","schema":"94b16e2e791613fcb3a4cf79a5cd7fa79433bf73"},"type":"has_property"},{"value":{"name":"type","schema":"jminLength_1_type_string"},"type":"has_property"},{"value":{"name":"token","schema":"jminLength_1_type_string"},"type":"has_property"},{"value":{"name":"scope","schema":"aff948820f2a9e3188cea37ba1ab7e6db41c85b9"},"type":"has_property"}]
*/   
const char* check_5fd67638293b5fde3046c63e48ed984dc4523f5a( json_value_handle& v ) { 
 
    
    json_value_handle& grant_type = v[ "grant_type" ];
     if ( const char* message = check_94b16e2e791613fcb3a4cf79a5cd7fa79433bf73 (grant_type) ) {
         return message;
    }
 
    
    json_value_handle& type = v[ "type" ];
     if ( const char* message = check_jminLength_1_type_string (type) ) {
         return message;
    }
 
    
    json_value_handle& token = v[ "token" ];
     if ( const char* message = check_jminLength_1_type_string (token) ) {
         return message;
    }
 
    
    json_value_handle& scope = v[ "scope" ];
     if ( const char* message = check_aff948820f2a9e3188cea37ba1ab7e6db41c85b9 (scope) ) {
         return message;
    }

 return 0;
} 

// {"oneOf":[{"format":"uri","type":"string //
/*[{"value":["jformat_uri_type_string","e4e0fc27050f4b7bfbe0f2e3da5ddabf8c3301be"],"type":"satisfies_one"}]
*/   
const char* check_f509cb62059c9cab3f4105ab68f5c4faed4b2927( json_value_handle& v ) { 
    {   int count = 0;
            if ( ! check_jformat_uri_type_string(v) ) count++; // {"format":"uri","type":"string"}
            if ( ! check_e4e0fc27050f4b7bfbe0f2e3da5ddabf8c3301be(v) ) count++; // {"enum":["urn:ietf:wg:oauth:2.0:oob"],"t
        if ( count != 1 ) {
                return "oneOf must match 1 and only one: " "{\"oneOf\":[{\"format\":\"uri\",\"type\":\"string" ;
        }
    }

 return 0;
} 

// {"enum":["urn:ietf:wg:oauth:2.0:oob"],"t //
/*[{"value":["urn:ietf:wg:oauth:2.0:oob"],"type":"equals_one_of"},{"value":"string","type":"has_type"}]
*/   
const char* check_e4e0fc27050f4b7bfbe0f2e3da5ddabf8c3301be( json_value_handle& v ) {  // equals_one_of
    {    
                 if ( std::string(v) == "urn:ietf:wg:oauth:2.0:oob"  ) {
                            return 0;
                  }
            return "value must be one of enum" ;
    }




 return 0;
} 










#endif
