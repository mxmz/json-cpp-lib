#ifndef json_lexcast_hxx_30458304958309458309583453985039850398503958309
#define json_lexcast_hxx_30458304958309458309583453985039850398503958309

#include <string>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string>

namespace mxmz { namespace json { namespace v4 { namespace util {


template< int MaxLen, typename ArgT>
::std::string string_printf( const char* fmt, ArgT a ) {
         char data[MaxLen];
         ::snprintf( data, MaxLen, fmt, a );
         return data;
}





template< class DestT, class SrcT>
struct convert_helper {
    DestT convert( SrcT v ) {
        return DestT(v);
    }
};



template< class T>
struct convert_helper<T,T> {
    const T& convert( const T& v ) {
        return v;
    }
};

template<>
struct convert_helper< ::std::string, int> {
    ::std::string convert(int v) {
        return string_printf<20>("%d",v);
    }
};


template<>
struct convert_helper< ::std::string, double> {
    ::std::string convert(double v) {
        return string_printf<20>("%g",v);
    }
};

template<>
struct convert_helper< ::std::string, long long int> {
    ::std::string convert(long long int v) {
        return string_printf<20>("%lld",v);
    }
};

template<>
struct convert_helper< ::std::string, bool> {
    ::std::string convert(bool v) {
        return ( v ? "true": "false");
    }
};

template<>
struct convert_helper< ::std::string, long double> {
    ::std::string convert(long double v) {
        return string_printf<20>("%llg",v);
    }
};

template<>
struct convert_helper<int, const char* > {
    int convert(const char* v) {
        return ::atoi( v );
    }
    int convert(const ::std::string& v) {
        return convert(v.c_str());
    }
};

template<>
struct convert_helper<long long int, const char* > {
    long long int convert(const char* v) {
        return strtoll( v , (char **)NULL, 10);
    }
    long long int convert(const ::std::string& v) {
        return convert(v.c_str());
    }
};

template<>
struct convert_helper<bool, const char* > {
    bool convert(const char* v) {
        return ::atoi(v) > 0 ||
                (strcmp(v,"true") == 0 ) ;
    }
     bool convert(const ::std::string& v) {
        return convert( v.c_str() );
    }
};


template<>
struct convert_helper<double, const char* > {
    double convert(const char* v) {
        return strtod( v, 0 );
    }
    double convert(const ::std::string& v) {
        return convert(v.c_str());
    }
};

template<>
struct convert_helper<long double, const char* > {
    long double convert(const char* v) {
        return strtold( v, 0 );
    }
    long double convert(const ::std::string& v) {
        return convert(v.c_str());
    }
};


template<>
struct convert_helper<int, double> {
    int convert(double v) {
        return (int)round(v);
    }
};

template<>
struct convert_helper<long long int, long double> {
    long long int convert(long double v) {
        return (long long int)roundl(v);
    }
};

template<>
struct convert_helper< ::std::string, const char* > :
    public convert_helper< ::std::string, ::std::string > { } ;

template < typename DestT, typename SrcT >
 DestT convert( const SrcT& v ) {
            convert_helper<DestT,SrcT >  helper;
            return helper.convert(v) ;
}


template < typename DestT >
 DestT convert( const char* v ) {
            convert_helper< DestT, const char * >  helper;
            return helper.convert( v );
}

template < typename DestT >
 DestT convert( const ::std::string& v ) {
            convert_helper< DestT, const char * >  helper;
            return helper.convert( v );
}





} } } }



#endif
