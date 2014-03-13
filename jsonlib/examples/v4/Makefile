




jsonreadwrite: ../../src/mxmz/json/v4/json_*.h* jsonreadwrite.cpp Makefile
	g++ -g -D_JSON_PARSER_DEBUG -std=c++0x -O3 -I../../src/ jsonreadwrite.cpp -o jsonreadwrite

csvreadjsonwrite: ../../src/mxmz/json/v4/*.h* csvreadjsonwrite.cpp Makefile
	g++ -g -D_CSV_READER_DEBUG -std=c++0x -O3 -I../../src/ csvreadjsonwrite.cpp -o csvreadjsonwrite


gettingstarted: ../../src/mxmz/json/v4/json_*.h* gettingstarted.cpp Makefile
	g++ -g -DJSON_VALUE_DEBUG -std=c++0x -O3 -I../../src/ gettingstarted.cpp -o gettingstarted

clone: ../../src/mxmz/json/v4/json_*.h* clone.cpp Makefile
	g++ -g -DJSON_VALUE_DEBUG -std=c++0x -O3 -I../../src/ clone.cpp -o clone

easyinit: ../../src/mxmz/json/v4/json_*.h* easyinit.cpp Makefile
	g++ -g --save-temps -D_JSON_VALUE_DEBUG -std=c++0x -O3 -I../../src/ easyinit.cpp -o easyinit

__apisample.hxx:	apisample.defs.json ../../scripts/generate_defs_impl.pl Makefile
	perl ../../scripts/generate_defs_impl.pl \
		--convert-value-template-function 'convert_value' \
		--to-struct-function 'to_struct_value' \
		--struct-type='json_value_handle' \
			< apisample.defs.json > __apisample.hxx


apisample: __apisample.hxx ../../src/mxmz/json/v4/json_*.h* apisample.cpp Makefile
	g++ -g -D_JSON_PARSER_DEBUG -std=c++0x -O3 -I../../src/ apisample.cpp -o apisample

__string_only_apisample.hxx:	string_only_apisample.defs.json ../../scripts/generate_defs_impl.pl
	perl ../../scripts/generate_defs_impl.pl < string_only_apisample.defs.json > __string_only_apisample.hxx
	
string_only_apisample: __string_only_apisample.hxx ../../src/mxmz/json/v4/json_*.h* string_only_apisample.cpp Makefile
	g++ -g -D_JSON_PARSER_DEBUG -std=c++0x -O3 -I../../src/ string_only_apisample.cpp -o string_only_apisample
