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
    delete schema.description;
    var id = idFromJson(schema);

    if ( cache[id] ) {
        console.error("schema already in cache: ", JSON.stringify(schema) );
        cache[ id ].used ++ ;
        return id;
    }

    var checks = [];
    var defs = [];
  
    ["anyOf", "allOf", "oneOf", "items"].forEach( function(name) {
                var v = schema[name];
                if ( v !== undefined ) {
                    if ( Array.isArray(v) ) {
                            schema[name] = v.map( function(elem) { return cacheSchema(elem,cache); } );
                    } else {
                            schema[name] = cacheSchema( v, cache );
                    }
                }
                  
      } );

    var props = schema["properties"];
    if ( props !== undefined ) {
        for( var k in props ) {
                var v = props[k];
                props[k] = cacheSchema( v, cache );
        }
    }

    cache[id] = {
            defs : schema,
            used: 1,
            desc: desc || JSON.stringify(schema).substr(0,40)
    }
    return id;
}


function main(files) {
        var sources = {};
        var cache = {};
        files.forEach( function(path) {
                var content =   fs.readFileSync(path);
                var schemas = JSON.parse(content);
                if ( ! Array.isArray(schemas) ) {
                    schemas = [ schemas ];
                }
                var c = 1;
                schemas.forEach( function(v) {
                        var id = path.replace(/[\/\.\-]/g, "_") + c++;
                        sources[id] = {
                                id : id,
                                schema : cacheSchema(v,cache)
                        }
               } );
           } );
        console.log( JSON.stringify( {
                                    files: sources,
                                    schemas: cache
                                } ) ) ;
}



main( process.argv.slice(2) || [] );







