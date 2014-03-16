[% USE JSON %]

[% FOREACH k IN sources.keys() %]
void assert_[%k%]( json_value_handle& v );
[%END%]

[% FOREACH k IN schemas.keys() %]
const char* check_[%k%]( json_value_handle& v ); // [%schemas.$k.desc %] //
[%END%]



#ifdef MXMZ_JSON_V4_IMPLEMENTATION
#include <set>

[% FOREACH k IN sources.keys() %]
void assert_[%k%]( json_value_handle& v ) {
        if ( const char* message = check_[%sources.$k.schema %](v) ) {
            throw(message);
        }
}
[%END%]




[% FOREACH k IN schemas.keys() %]
[% defs = schemas.$k.defs %]

// [%schemas.$k.desc %] //
/*
    [% schemas.$k.defs.json %]
*/   
[%IF defs.enum  %] // enum
[% values = defs.enum %]
const    std::set<std::string> enum_[%k%] = {
                    [% FOREACH s IN values %][%IF loop.index() != 0 %],[%END%] [%s.json%][%END%] };
[%END%]
const char* check_[%k%]( json_value_handle& v ) { 

 [%IF defs.required %] // required
    [% properties = defs.required %]
    [%FOREACH p IN properties %]
        if ( auto* [%p%] = v.attribute( [%p.json %]  ) ) {
        } else {
            return "Missing attribute " [%p.json%];
        }
    
    [%END%]

 [%END%]
 [%IF defs.properties %]  // properties [% defs.properties.json %]
    [% properties = defs.properties %]
    [%FOREACH p IN properties %]
    if ( auto* [%p.key%] = v.attribute( [%p.key.json %]  )  ) {
     if ( const char* message = check_[%p.value%] (*[%p.key%]) ) {
         return message;
     }
    }
    [%END%]
 [%END%]

 [%IF defs.oneOf %] // oneOf
    [% subschemas = defs.oneOf %]
    {   int count = 0;
        [%FOREACH s IN subschemas %]
            if ( ! check_[%s%](v) ) count++; // [% schemas.$s.desc %]
        [%END%]
        if ( count != 1 ) {
                return "oneOf must match 1 and only one: " [%schemas.$k.desc.json%] ;
        }
    }
 [%END%]

 [%IF defs.enum  %] // enum
    [% values = defs.enum %]
    if ( enum_[%k%].find(std::string(v) ) == enum_[%k%].end()  ) {
                    return "value must be one of enum" ;
     }
 [%END%]


 return 0;
} 
[%END%]










#endif
