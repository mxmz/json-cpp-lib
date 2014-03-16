var token_request_schemas = require("./autogen/token_request_schemas");


console.log(token_request_schemas);

token_request_schemas.assert_token_request_json1(
                {
                    "grant_type": "remotes",
                    "type": "pippo",
                    "token": "asdasdasd",
                    "scope": "asd asd asda "
                }
                
                
          );
