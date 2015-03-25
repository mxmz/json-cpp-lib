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
            return 'X'+md5Hex(json.id).toUpperCase();
         }
         function jsonDigest(str) {
            if ( str.match( /^[\"\{\},\w\:\-]{1,60}$/ ) ) {
                    return 'J'+ str
                            .replace(/[:,]/g, "0")
                            .replace(/[\{\}\"-]/g, "").toUpperCase();
            } else {
                    return 'X'+ md5Hex(str).toUpperCase();
            }
         }
         return jsonDigest(JSON.stringify(json) );
}



function cacheSchema(schema, cache ) {
    var $ref = schema['$ref'];
    delete schema['$ref'];
    if ( $ref ) {
            return 'X'+ md5Hex($ref).toUpperCase();
    }    

    var desc = schema.description || JSON.stringify(schema).substr(0,40)
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
            desc: desc 
    }
    return id;
}


function preprocess( schemas ) {
        var cache = {};
        var sources = {};
        schemas.forEach( function(e) {
                sources[ e.id ] = {
                        id: e.id,
                        schema: cacheSchema( e.schema, cache )
                    };
       } );
       return {
                sources: sources,
                schemas: cache
       }
}




module.exports = preprocess;



