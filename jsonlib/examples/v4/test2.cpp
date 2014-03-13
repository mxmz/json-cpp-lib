#include <iostream>
using namespace std;

#define JSON_DEBUG 1
#include "json/v4/json_std.h"


using namespace mxm::json::v4::std;

int main() {

        typedef json_value_handle::json_scalar json_scalar;
        typedef json_value_handle::json_string json_string;

        json_value_handle obj;

            obj.force_cast<json_string>().set("  1.1e11");

            cerr << obj.try_cast_const<json_scalar>().string() << endl;
            cerr << obj.try_cast_const<json_scalar>().integer() << endl;
            cerr << obj.try_cast_const<json_scalar>().number() << endl;
            cerr << obj.try_cast_const<json_scalar>().boolean() << endl;

            json_parser     parser(obj);
            json_tokenizer  tokenizer(parser);
}
