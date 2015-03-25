'use strict'
var fs = require('fs');
var preprocess = require('../lib/schema-preprocess');


function main(files) {
        var sources = {};
        var args = [];
        files.forEach( function(path) {
                var content =   fs.readFileSync(path);
                var schemas = JSON.parse(content);
                if ( ! Array.isArray(schemas) ) {
                    schemas = [ schemas ];
                }
                var c = 1;
                schemas.forEach( function(v) {
                        var id = path.replace(/[\/\.\-]/g, "_") + c++;
                        args.push( {    
                                        id: id,
                                        schema: v
                                } );
               } );
           } );
        var result = preprocess(args);
        console.log( JSON.stringify( {
                                    sources: result.sources,
                                    schemas: result.schemas
                                } ) ) ;
}



main( process.argv.slice(2) || [] );







