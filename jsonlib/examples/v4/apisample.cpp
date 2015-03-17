#include <iostream>
#include "mxmz/json/v4/json_std.h"

using namespace mxmz::json::v4::std;
using namespace mxmz::json::v4::util;
using namespace std;

void slurp( ::std::istream& in, std::string& data );
::std::string slurp( ::std::istream& in );

namespace apisample {

// modified

template< class ToT, class FromT >
struct convert_helper {
};

template< class T >
struct convert_helper< T, json_value_handle > {
    typedef json_value_handle&       return_type;
    json_value_handle& operator()( json_value_handle& arg) {
        return arg;
    }
};


template< class T >
struct convert_helper < std::vector<T>, json_value_handle > {
        typedef std::vector<T>  return_type;
        return_type operator()( json_value_handle& a ) {
            std::vector<T> v;
            typedef typename std::vector<T>::value_type value_type;
            size_t size = a.size();
            for( size_t i = 0; i < size; ++i ) {
                    v.push_back( std::move( value_type( a[i]  ) ) );
            }
            return std::move(v);
        }
};



template< class T >
typename convert_helper<T,json_value_handle>::return_type convert_value( json_value_handle& arg );

json_value_handle to_struct_value( const std::string& obj )  { return std::move(json_value_handle(obj)); }
json_value_handle to_struct_value( const int& obj )          { return std::move(json_value_handle(obj)); }

template< class T >
json_value_handle to_struct_value( const T& obj )          { return std::move(json_value_handle(obj)); }

template< class ObjT >
json_value_handle     to_struct_value( const std::vector<ObjT>& v );

template<int i>
int&& greater_than( int&& v ) {
    if ( v < i ) { std::cerr << v << " not valid" << endl; abort(); }
    return v;
}
template<int i>
const int greater_than( const int& v ) {
    return greater_than<i>( std::move(int(v)) );
}

#include "__apisample.hxx"


template < class D, class  C >
typename mxmz::json::v4::json_value_handle_tmpl<D,C>::json_array& as_vector( 
                mxmz::json::v4::json_value_handle_tmpl<D,C>& v ) {
    D& dv = static_cast<D&>(v);
    return dv.template cast_value<json_array>(true);
}

template< class T >
class vector_adapter {
        T& ref;
        public:
        vector_adapter(T&r ): ref(r) {}
        void push_back( typename T::value_type&& v ) {
                    ref.push_back(v);
        }   
};

template< >
class vector_adapter<  mxmz::json::v4::std::json_value_handle > {
        mxmz::json::v4::std::json_value_handle& ref;
        public:
       vector_adapter(  mxmz::json::v4::std::json_value_handle& r ): ref(r) { }
        void push_back(   mxmz::json::v4::std::json_value_handle&& v ) {
                ref.push_back(v);
        }
};


// definitions
template< class T >
typename convert_helper<T,json_value_handle>::return_type convert_value( json_value_handle& arg ) {
        convert_helper<T,json_value_handle>    helper;
        return helper(arg);
}
template< class ObjT >
json_value_handle to_struct_value( const std::vector<ObjT >& v  ) {
        json_value_handle rv;
        vector_adapter<json_value_handle> a(rv);
        for( size_t i = 0; i < v.size(); ++i ) {
             a.push_back( std::move(  to_struct_value(v[i]) ) );
        }
        return std::move(rv);
}





}


int main() {
        json_value_handle obj;
        apisample::item i;
        cout << i.get_number() << endl;
        

        try {
            slurp(cin) >> obj;

            apisample::message msg( obj );
//            cout << msg.content().number() << endl;
  //          cout << msg.content().text() << endl;
            cout << msg.get_my_items().size() << endl;
            cout << msg.get_my_items()[0].get_text() << endl;
            cout << msg.get_my_items()[0].get_number() << endl;

            json_value_handle newobj = msg.to_struct();

            cout << newobj << endl;

        } catch( std::exception& e ) {
            cerr << e.what() << endl;
            exit(-1);
        }

}


void slurp( ::std::istream& in, std::string& data )
{
        data.clear();
        data.reserve( 1024*1024 );
//        char buf[1000000];
        while ( in )
        {
  //              in.read(buf, 1000000);
  //              data.append(buf, in.gcount());

                size_t size = data.size();
                data.resize( size + 10*1024 );
                in.read( &data[0] + size, 10*1024 );
                data.resize( size + in.gcount()  );

        }

        if ( in.bad() )
        {
                // an error occurred while reading
                throw "error while reading file";
        }
}

::std::string slurp( ::std::istream& in ) {
    ::std::string data;
    slurp(in,data);
    return data;
}
