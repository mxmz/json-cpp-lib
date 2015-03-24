var swig = require('swig');

function main(argv) {
        var tpl = swig.compileFile(  argv[0] );

        var inputStream = process.stdin
          , data = '';
         
        process.stdin.resume();
        inputStream.on('data', function(chunk) {
          data += chunk;
        });
        inputStream.on('end', function() {
          var json = JSON.parse(data)

            console.log(tpl(json));

        });

}
main( process.argv.slice(2) || [] );
