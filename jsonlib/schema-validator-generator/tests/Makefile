




jsonreadwrite: ../../src/mxmz/json/v4/json_*.h* jsonreadwrite.cpp Makefile autogen/token_request_schemas.hxx
	g++ -g -D_JSON_PARSER_DEBUG -std=c++0x -O3 -I../../src/ jsonreadwrite.cpp -o jsonreadwrite



autogen/token_request_schemas.hxx:
	( cd ../schemas/04 && perl ../../scripts/flatten.pl token-request.json | perl ../../scripts/expand_template.pl ../../templates/mxmz_v4.tmpl ) > autogen/token_request_schemas.hxx
