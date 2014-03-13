#ifndef json_value_handle_hxx_456948769485769845769845769485769485769485769485
#define json_value_handle_hxx_456948769485769845769845769485769485769485769485

#include <exception>
#include <typeinfo>
#include <assert.h>
#include <memory>
#include <map>
#include <vector>
#include <stdlib.h>

#ifdef __GNUC__
#include <cxxabi.h>
#endif

#include "mxmz/json/v4/json_lexcast.hxx"
#include "mxmz/json/v4/json_value_ptr.hxx"

#ifdef JSON_VALUE_DEBUG
#define JSON_VALUE_CERR if(1) ::std::cerr
#define JSON_VALUE_COUT if(1) ::std::cerr
#else
#define JSON_VALUE_CERR if(0) ::std::cerr
#define JSON_VALUE_COUT if(0) ::std::cerr
#endif

namespace mxmz {
namespace json {
namespace v4 {

enum type_tag {
    JsonNull,
    JsonString,
    JsonNumber,
    JsonInteger,
    JsonBool,
    JsonObject,
    JsonArray,
};


template < class JsonValueHandleDerivedT, class ConfigT >
class json_value_handle_tmpl {
public:
    typedef ConfigT                      config_t;
    typedef typename ConfigT::string_t   string_t;
    typedef typename ConfigT::integer_t  integer_t;
    typedef typename ConfigT::number_t   number_t;
    typedef typename ConfigT::boolean_t  boolean_t;
    typedef typename ConfigT::char_t     char_t;
    typedef JsonValueHandleDerivedT json_value_handle_derived;

    typedef json_value_handle_derived   value_type;

    class json_value_const_visitor;


    class json_value  {
        unsigned int refcount_;
    public:
        json_value(): refcount_(0) {
            JSON_VALUE_CERR << this << " ctor\n";
        };
        virtual json_value*   clone() const = 0;
        virtual type_tag      type() const = 0;
        virtual void          accept( json_value_const_visitor& ) const = 0;
        virtual ~json_value() throw() {
            JSON_VALUE_CERR << this << " dtor\n";
        }

        virtual void add_ref() {
            refcount_++;
            JSON_VALUE_CERR << this << " " << refcount_ << "\n";
        }
        virtual void release() {
            JSON_VALUE_CERR << this << " " << refcount_ << "\n";
            assert( refcount_ > 0 );
            --refcount_;
            if ( refcount_ == 0 ) delete this;
        }
        virtual void destroy() {
            delete this;
        }

    };

    class json_null_singleton : public json_value {
    public:

        virtual void add_ref() { }
        virtual void release() { }
        virtual void destroy() { }
        virtual json_value* clone() const {
            return const_cast<json_null_singleton*>(this);
        }
        virtual type_tag    type() const {
            return JsonNull;
        }
        virtual void        accept( json_value_const_visitor& v) const {
            v.visit();
        }
    };

    static json_null_singleton null_value;



    typedef typename json_value_ptr_choice<
        json_value,
        config_t::enable_value_sharing,
        config_t::use_std_shared_ptr >::ptr_type  value_ptr;



static void null_deleter(json_value* ) {
}

private:
    value_ptr value_;

   json_value_handle_tmpl( json_value* value );
protected:

    template< class JsonValueT >
    JsonValueT& reset( JsonValueT* value ) {
        value_.reset(value);
        return *value;
    }



    json_value_handle_tmpl()
            : value_(&null_value, &null_deleter) {
        JSON_VALUE_CERR << this << " ctor (handle)\n";
    }

    json_value_handle_tmpl( json_value_handle_tmpl&& temp )
            : value_(&null_value, &null_deleter) {
        JSON_VALUE_CERR << this << " ctor (handle&&)\n";
        temp.swap(*this);
    }

    json_value_handle_tmpl( const json_value_handle_tmpl& that )
            : value_(that.value_) {
        JSON_VALUE_CERR << this << " ctor (json_value_handle_tmpl) (handle) " << value_.get() << "\n";
        if ( ! that.is_null() ) {
                std::cerr << "tried to copy a non null value" << std::endl;
                abort();
        }
    }


    explicit json_value_handle_tmpl( const string_t& v ) : value_(&null_value,&null_deleter) {
        reset( new json_string() ).set(v);
        JSON_VALUE_CERR << this << " ctor (string)\n";
    }
    explicit json_value_handle_tmpl( const char_t* v ) : value_(&null_value,&null_deleter) {
        reset( new json_string() ).set(v);
        JSON_VALUE_CERR << this << " ctor (char*)\n";
    }

    explicit json_value_handle_tmpl( const number_t& v ) : value_(&null_value,&null_deleter) {
        reset( new json_number() ).set(v);
        JSON_VALUE_CERR << this << " ctor (number)\n";
    }

    explicit json_value_handle_tmpl( const integer_t& v ) : value_(&null_value,&null_deleter) {
        reset( new json_integer() ).set(v);
        JSON_VALUE_CERR << this << " ctor (int)\n";
    }

    explicit json_value_handle_tmpl( const boolean_t& v ) : value_(&null_value,&null_deleter) {
        reset( new json_bool() ).set(v);
        JSON_VALUE_CERR << this << " ctor (bool)\n";
    }

public:

    ~json_value_handle_tmpl() throw() {
        JSON_VALUE_CERR << this << " dtor (handle)\n";
    }

    void swap( json_value_handle_tmpl& that ) {
        value_.swap(that.value_ );
    }

    json_value_handle_derived clone() const {
        JSON_VALUE_CERR << this << " clone\n";
        json_value_handle_derived clone;
        clone.reset( (*value_).clone() );
        return static_cast<json_value_handle_derived&&>(clone);
    }

    type_tag type() const {
        return (*value_).type();
    }
    bool is_null () const {
        return value_.get() == &null_value;
    }

    class bad_cast : public ::std::bad_cast {
        string_t what_;
        public:
          bad_cast( const char* found, const char* wanted ) {
            what_ = "Cannot cast '";
            what_ += demangle_typename(found);
            what_ += "' to '";
            what_ += demangle_typename(wanted);
            what_ += "'";
          }
          const char* what() const throw() { return what_.c_str(); }
         ~ bad_cast() throw() {}
    };


    template< class JsonValueT >
    const JsonValueT&
    cast_value_const() const {
        if ( is_null() )    {
            throw bad_cast(typeid(null_value).name(), typeid(JsonValueT).name() );
        } else {
            try {
                return dynamic_cast< JsonValueT & >(*value_);
            } catch( std::bad_cast&  ) {
                throw bad_cast(typeid(*value_).name(), typeid(JsonValueT).name() );
            }
        }
    }

    template< class JsonValueT >
    JsonValueT&
    cast_value() const {
        if ( is_null() )    {
            throw bad_cast(typeid(null_value).name(), typeid(JsonValueT).name() );
        } else {
            try {
                return dynamic_cast< JsonValueT & >(*value_);
            } catch( std::bad_cast&  ) {
                throw bad_cast(typeid(*value_).name(), typeid(JsonValueT).name() );
            }
        }
    }

    template< class JsonValueT >
    JsonValueT&
    cast_value(bool autovivification = true) {
        return this->cast_value<JsonValueT,JsonValueT>(autovivification);
    }

    template< class JsonBaseT, class JsonValueT >
    JsonBaseT&
    cast_value( bool autovivification = true ) {
        if ( is_null() && autovivification )
            return reset(new JsonValueT());
        else {
            JsonBaseT* rv =  dynamic_cast< JsonBaseT* >(&*value_);
            if ( ! rv )
                throw bad_cast(typeid(*value_).name(), typeid(JsonValueT).name() );
            return *rv;
            }

    }
    template< class JsonValueT >
    JsonValueT&
    coerce_value() {
        return this->coerce_value<JsonValueT,JsonValueT>();
    }
    template< class JsonBaseT, class JsonValueT >
    JsonValueT&
    coerce_value() {
        JsonBaseT* rv = dynamic_cast< JsonBaseT* >(value_.get());
        if ( rv == 0 )
            return reset(new JsonValueT());
        else return *rv;
    }

    void accept( json_value_const_visitor& v ) const {
        (*value_).accept(v) ;
    }


    class json_scalar : public json_value {
    public:
        virtual string_t   string()  const = 0;
        virtual number_t   number()  const = 0;
        virtual integer_t  integer() const = 0;
        virtual boolean_t  boolean() const = 0;
    };

    class json_struct : public json_value {
    public:
        ~json_struct() throw() { }
    };

    template< class ValueT , class DerivedT, class JsonBaseT >
    class json_value_tmpl: public JsonBaseT {

    protected:
        ValueT    value_;

    public:
        typedef ValueT      value_type;

        json_value_tmpl() : value_( value_type() ) { }
        ~json_value_tmpl() throw() { }
        void     set( const ValueT& v)  {
            value_ = v;
        }
        void     set( ValueT&& v )  {
            value_ = std::move(v);
        }
        const value_type& get() const   {
            return value_;
        }
        value_type& get()         {
            return value_;
        }

        DerivedT& derived_this() {
            return static_cast<DerivedT&>(*this);
        }
        const DerivedT& derived_this() const {
            return static_cast<const DerivedT&>(*this);
        }

        DerivedT* clone_impl() const {
            JSON_VALUE_CERR << this << " clone_impl\n";
            return new DerivedT( derived_this() );
        }

        json_value_tmpl* clone() const {
            return this->clone_impl() ;
        }

        void      accept( json_value_const_visitor&  v) const {
            v.visit( derived_this() );

        };

        template< class T >
        T get() const {
            return util::convert<T>( this->get() );
        }

        template< class JsonValueT >
        JsonValueT* clone_convert() const {
            typedef typename JsonValueT::value_type value_type;
            JsonValueT* newval = new JsonValueT();
            newval->set( util::convert<value_type>( this->get() ) );
            return newval;
        }
    };

    typedef typename select_ptr_container_types< config_t::use_ptr_containers, string_t, json_value_handle_derived>::object_t object_t;
    typedef typename select_ptr_container_types< config_t::use_ptr_containers, string_t, json_value_handle_derived>::array_t  array_t;

    class json_string : public json_value_tmpl< string_t,  json_string, json_scalar >  {
    public:
        virtual string_t   string()  const  {
            return this->get();
        }
        virtual number_t   number()  const  {
            return this->template get<number_t>();
        }
        virtual integer_t  integer() const  {
            return this->template get<integer_t>();
        }
        virtual boolean_t  boolean() const  {
            return this->template get<boolean_t>();
        }
        virtual type_tag    type() const {
            return JsonString;
        }
    };
    class json_number : public json_value_tmpl< number_t,  json_number, json_scalar >  {
    public:
        virtual string_t   string()  const  {
            return this->template get<string_t>();
        }
        virtual number_t   number()  const  {
            return this->get();
        }
        virtual integer_t  integer() const  {
            return this->template get<integer_t>();
        }
        virtual boolean_t  boolean() const  {
            return this->template get<boolean_t>();
        }
        virtual type_tag    type() const {
            return JsonNumber;
        }
    };
    class json_integer: public json_value_tmpl< integer_t, json_integer, json_scalar > {
    public:
        virtual string_t   string()  const  {
            return this->template get<string_t>() ;
        }
        virtual number_t   number()  const  {
            return this->template get<number_t>();
        }
        virtual integer_t  integer() const  {
            return this->get() ;
        }
        virtual boolean_t  boolean() const  {
            return this->template get<boolean_t>();
        }
        virtual type_tag    type() const {
            return JsonInteger;
        }
    };
    class json_bool:    public json_value_tmpl< boolean_t,    json_bool, json_scalar > {
    public:
        virtual string_t   string()  const  {
            return this->template get<string_t>() ;
        }
        virtual number_t   number()  const  {
            return (int)this->get() ;
        }
        virtual integer_t  integer() const  {
            return (int)this->get() ;
        }
        virtual boolean_t  boolean() const  {
            return this->get();
        }
        virtual type_tag    type() const {
            return JsonBool;
        }
    };


    class json_object:   public json_value_tmpl< object_t,    json_object, json_struct > {
    public:
        virtual type_tag    type() const {
            return JsonObject;
        }
        json_value_handle_derived&    item( const string_t& k ) {
            return this->get() [ k ];
        }
    };

    class json_array:    public json_value_tmpl< array_t,  json_array, json_struct > {
    public:
        virtual type_tag    type() const {
            return JsonArray;
        }

        size_t size() const { return this->get().size(); }

        json_value_handle_derived&    item( unsigned int idx ) {
            array_t& a = this->get();
            if ( idx >= a.size() ) {
                a.resize(idx+1);
            }
            return a[ idx ];
        }
        const json_value_handle_derived&    item( unsigned int idx ) const {
            return this->get()[ idx ];
        }

        json_value_handle_derived&    append() {
            array_t& a = this->get();
            size_t size = a.size();
            a.resize( size + 1);
            return a[ size ];
        }
        void push_back( json_value_handle_derived&& v ) {
            json_value_handle_derived& newv = append();
            newv.swap(v);
        }
    };

    class json_value_const_visitor {
    public:
        virtual   void visit()   = 0;
        virtual   void visit( const json_string& ) = 0;
        virtual   void visit( const json_integer& ) = 0;
        virtual   void visit( const json_number& ) = 0;
        virtual   void visit( const json_bool& ) = 0;
        virtual   void visit( const json_object& ) = 0;
        virtual   void visit( const json_array& ) = 0;
    };


    private:
    static ::std::string demangle_typename( const char* name ) {
#ifdef __GNUC__
     int status;
     char  realname[200];
     size_t size = 200;
     abi::__cxa_demangle(name, realname, &size, &status);
     realname[size] = 0;
     if ( status != 0 ) {
             strncpy( realname, name, strlen(name));
     }
     const char* lastcolon = strrchr(realname,':');
     if ( lastcolon ) { ++lastcolon; }
     else lastcolon = realname;
     std::string rv(lastcolon);
     return rv;
#else
     return name;
#endif
    }

};

template < class T, class C >
typename json_value_handle_tmpl<T,C>::json_null_singleton json_value_handle_tmpl<T,C>::null_value;

template< int tag = 0 >
const char* type_tag_name(type_tag v) {
    switch (v) {
    case JsonNull:
        return "Null";
    case JsonString:
        return "String";
    case JsonNumber:
        return "Number";
    case JsonInteger:
        return "Integer";
    case JsonBool:
        return "Bool";
    case JsonObject:
        return "Object";
    case JsonArray:
        return "Array";
    default:
        return "";
    }
}




}
}
}


#endif
