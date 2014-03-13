#include <iostream>
using namespace std;

#include "json/v4/json_std.h"


using namespace mxmz::json::v4::std;



template< class ConvertT >
class converter: public
    json_value_handle::json_value_const_visitor {

        json_value_handle newo_;
        typedef typename json_value_handle::json_object     json_object;
        typedef typename json_value_handle::json_array      json_array;

        public:

        void visit()                                { newo_.coerce_value<ConvertT>(); }
        void visit_impl( const json_object& v )     { newo_.coerce_value<ConvertT>(); };
        void visit_impl( const json_array& v )      { newo_.coerce_value<ConvertT>(); };

        void visit_impl( const ConvertT& v ) {
           // keep original value
            }

        template< class VisitedT >
            void visit_impl( const VisitedT& v ) {
                typedef typename ConvertT::value_type value_type;
                newo_.coerce_value<ConvertT>().set(
                        mxmz::json::v4::util::convert<value_type>( v.get() )
                );
            }

        virtual   void visit( const json_string& v) { visit_impl(v); }
        virtual   void visit( const json_integer& v){ visit_impl(v); }
        virtual   void visit( const json_number& v) { visit_impl(v); }
        virtual   void visit( const json_bool& v)   { visit_impl(v); }
        virtual   void visit( const json_object& v) { visit_impl(v); }
        virtual   void visit( const json_array& v)  { visit_impl(v); }

        void convert( json_value_handle& o ) {
            newo_ = o;
            o.accept(*this);
            o.swap(newo_);
        }
};





int main() {
        json_value_handle obj;
        try {

            cin >> obj;

        } catch( std::exception& e ) {
            cerr << e.what() << endl;
        }



        cout << obj<< endl;
        converter< json_value_handle::json_number >().convert(obj);
        cout << type_tag_name(obj.type()) << ": ";
        cout << obj << endl;

        /*
        obj = json_value_handle("pippo");
        cout << type_tag_name(obj.type()) << ": ";
        cout << obj << endl;

        obj = json_value_handle(true);
        cout << type_tag_name(obj.type()) << ": ";
        cout << obj << endl;

        obj = json_value_handle(false);
        cout << type_tag_name(obj.type()) << ": ";
        cout << obj << endl;

        obj = json_value_handle(1.1L);
        cout << type_tag_name(obj.type()) << ": ";
        cout << obj << endl;

        obj = 1;
        cout << type_tag_name(obj.type()) << ": ";
        cout << obj << endl;

        obj = true;
        cout << type_tag_name(obj.type()) << ": ";
        cout << obj << endl;
        obj = 1.1;
        cout << type_tag_name(obj.type()) << ": ";
        cout << obj << endl;
        obj = "ciao";
        cout << type_tag_name(obj.type()) << ": ";
        cout << obj << endl;

        obj["pippo"] = 10.123;



        obj["pluto"]["pippo"]["ciao"] = "pippo";

        json_value_handle obj2 =  obj["pluto"]["pippo"].clone();
        obj["pluto"]["pippo"]["ciao"] = obj2;

        cout << obj2 << endl;

        obj["brazo"] = ( obj["cocco"][3]["ciao"] = 2).clone();


        obj["braza"] = ( (json_value_handle())["pippo"] );


        cout << obj << endl;


        std::string a = obj["pippo"];
         int i = obj["pippo"];
        long double n = obj["pippo"];
        bool b = obj["pippo"];

        cerr << a << " " << i << " " << n << " " << b << endl;

        */



}
