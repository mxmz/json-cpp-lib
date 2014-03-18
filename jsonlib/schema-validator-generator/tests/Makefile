


cpp: jsonreadwrite autogen/all_schemas.hxx

js: autogen/token_request_schemas.js autogen/all_schemas.js

jsonreadwrite: ../../src/mxmz/json/v4/json_*.h* jsonreadwrite.cpp Makefile autogen/token_request_schemas.hxx
	g++ -g -D_JSON_PARSER_DEBUG -std=c++0x -O3 -I../../src/ jsonreadwrite.cpp -o jsonreadwrite



autogen/token_request_schemas.hxx: ../schemas/04/token-request.json  ../templates/mxmz_v4.tmpl
	mkdir -p ./autogen && ( cd ../schemas/04 && perl ../../scripts/flatten.pl token-request.json | perl ../../scripts/expand_template.pl ../../templates/mxmz_v4.tmpl ) > autogen/token_request_schemas.hxx



autogen/token_request_schemas.js: ../schemas/04/token-request.json  ../templates/javascript.tmpl
	mkdir -p ./autogen && ( cd ../schemas/04 && perl ../../scripts/flatten.pl token-request.json | perl ../../scripts/expand_template.pl ../../templates/javascript.tmpl ) > autogen/token_request_schemas.js


autogen/all_schemas.js: ../schemas/04/*.json  ../templates/javascript.tmpl
	mkdir -p ./autogen && ( cd ../schemas/04 && perl ../../scripts/flatten.pl *.json | perl ../../scripts/expand_template.pl ../../templates/javascript.tmpl ) > autogen/all_schemas.js


autogen/all_schemas.hxx: ../schemas/04/*.json  ../templates/mxmz_v4.tmpl
	mkdir -p ./autogen && ( cd ../schemas/04 && perl ../../scripts/flatten.pl *.json | perl ../../scripts/expand_template.pl ../../templates/mxmz_v4.tmpl ) > autogen/all_schemas.hxx



clean:
	rm autogen/*
