'use strict'
var crypto = require('crypto');
var fs = require('fs');

function md5Hex(material) {
    var md5sum = crypto.createHash('md5');
    md5sum.update(material);
    return md5sum.digest('hex');

}

function idFromJson(json) {
         if ( json.id !== undefined && json.id.length ) {
            return md5_hex(id);
         }
         function jsonDigest(str) {
            if ( str.match( /^[\"\{\},\w\:\-]{1,60}$/ ) ) {
                    return 'j'+ str
                            .replace(/[:,]/g, "_")
                            .replace(/[\{\}\"-]/g, "");
            } else {
                    return md5Hex(str);
            }
         }
         return jsonDigest(JSON.stringify(json) );
}



function cacheSchema(schema, cache ) {
    var $ref = schema['$ref'];
    delete schema['$ref'];
    if ( $ref ) {
            return md5Hex($ref);
    }    

    var desc = schema.description;
    var id = idFromJson(schema);

    if ( cache.id ) {
        console.error("schema already in cache: ", JSON.stringify(schema) );
        cache[ id ].used ++ ;
        return id;
    }

    my @checks ;
    my %defs;

    var checks = [];
    var defs = [];
/*
    foreach my $k ( keys %subschema_defs ) {
            if ( $schema->{$k}  ) {
                 $schema->{$k} = ref($schema->{$k}) eq 'HASH' ?
                                        cache_schema( $schema->{$k}  , $cache ) :
                                         [  map { cache_schema($_,$cache)  }  @{ $schema->{$k} } ]
            }
    }
*/
  
    ["anyOf", "allOf", "oneOf", "items"].forEach( function(v) {
                var 

                    } );


    if ( $schema->{'properties'} ) {
        my %properties;
        foreach my $key ( keys %{$schema->{'properties'}} ) {
                my $value = $schema->{'properties'}->{$key} ;
                my $schema_id = cache_schema($value, $cache ) ;
                $properties{$key} = $schema_id;
        }
        $schema->{'properties'} = \%properties;
    }
        $cache->{$id} = {
            defs   => $schema,
            used => 1,
            desc => $desc || substr( encode_json($schema), 0, 40 )
            };
    return $id;

}




























 console.log( id_from_json( {

                            "a": 1,
                            "b": 2,
                            "c": {
                                    "casa1": "asd",
                                    "casa2": "asd",

                                    }
                         } ) );
