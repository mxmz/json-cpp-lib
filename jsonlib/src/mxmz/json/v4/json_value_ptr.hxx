#ifndef json_ptr_hxx_456948769485769845769845769485769485769485769485234
#define json_ptr_hxx_456948769485769845769845769485769485769485769485234

#include <exception>
#include <typeinfo>
#include <assert.h>
#include <memory>
#include <map>
#include <vector>
#include <memory>

namespace mxmz {
namespace json {
namespace v4 {

template< class JsonValueT >
class json_value_shared_ptr_tmpl  {
        JsonValueT*  value_;
    public:
        template < class IgnoreT >
        json_value_shared_ptr_tmpl(JsonValueT* ptr, IgnoreT) : value_(ptr) {
           value_->add_ref();
        }
        json_value_shared_ptr_tmpl(JsonValueT* ptr) : value_(ptr) {
           value_->add_ref();
        }
        json_value_shared_ptr_tmpl( const json_value_shared_ptr_tmpl& that ) : value_(that.value_) {
            value_->add_ref();
        }

        ~json_value_shared_ptr_tmpl() throw () {
            value_->release();
        }

        void reset( JsonValueT* value ) {
            value_->release();
            value_ = value;
            value_->add_ref();
        }
        void operator=( const json_value_shared_ptr_tmpl& that ) {
            value_->release();
            value_ = that.value_;
            value_->add_ref();
        }
        /*
        json_value_shared_ptr_tmpl clone() const {
            return json_value_shared_ptr_tmpl( value_->clone() );
        }*/

        JsonValueT&  operator*() const {
            return *value_;
        }

        JsonValueT*  get() const {
            return value_;
        }
        void swap( json_value_shared_ptr_tmpl& that ) {
            std::swap( value_, that.value_ );
        }

    };

    template< class JsonValueT>
    class json_value_cloning_ptr_tmpl  {
        JsonValueT*  value_;
    public:

        template < class IgnoreT >
        json_value_cloning_ptr_tmpl(JsonValueT* ptr, IgnoreT ) : value_(ptr) {
        }

        json_value_cloning_ptr_tmpl(JsonValueT* ptr ) : value_(ptr) {
        }

        json_value_cloning_ptr_tmpl( const json_value_cloning_ptr_tmpl& that )
            : value_( that.value_->clone() ) {
        }

        ~json_value_cloning_ptr_tmpl() throw () {
            value_->destroy();
        }


        void reset( JsonValueT* ptr ) {
            value_->destroy();
            value_ = ptr;

        }
        void operator=( const json_value_cloning_ptr_tmpl& that ) {
            value_->destroy();
            value_ = that.value_->clone();
        }
        /*
        json_value_cloning_ptr_tmpl clone() const {
            return *this; ;
        }
        */

        JsonValueT&  operator*() const {
            return *value_;
        }

        JsonValueT* get() const {
            return value_;
        }
        const JsonValueT*  ptr() const {
            return value_;
        }
        void swap( json_value_cloning_ptr_tmpl& that ) {
            std::swap( value_, that.value_ );
        }

    };


    template< class JsonValueT, bool EnableSharing, bool UseStdPtr >
    struct json_value_ptr_choice {
            private:
            typedef void* ptr_type;
        } ;

    template<class JsonValueT>
    struct json_value_ptr_choice<JsonValueT,true,false> {
                typedef json_value_shared_ptr_tmpl<JsonValueT>  ptr_type;

    };

    template<class JsonValueT>
    struct json_value_ptr_choice<JsonValueT,false,false> {
                typedef json_value_cloning_ptr_tmpl<JsonValueT>  ptr_type;

    };

    template<class JsonValueT>
    struct json_value_ptr_choice<JsonValueT,true,true> {
                typedef std::shared_ptr <JsonValueT> ptr_type;

    };



    template< class StringT, class JsonValueHandleT >
            class ptr_map {

                    typedef typename std::map < StringT, JsonValueHandleT* > map_type;
                    map_type map_;

                    public:
                    typedef typename std::map < StringT, JsonValueHandleT* >::const_iterator const_iterator;

                    const_iterator begin() const { return map_.begin(); }
                    const_iterator end() const { return map_.end(); }
                    
                    template< class FuncT >
                    void for_each( FuncT & func ) {
                        for( typename map_type::iterator i = map_.begin(); i != map_.end(); ++i ) {
                            func( (*i).first, *( (*i).second ) );
                        }

                    }
                    JsonValueHandleT& operator[] ( const StringT& key ) {
                            JsonValueHandleT* & p = map_[key];
                            if ( ! p ) {
                                    p = new JsonValueHandleT();
                            }
                            return *p;
                    }

                    ~ptr_map() {
                            for( typename map_type::iterator i = map_.begin(); i != map_.end(); ++i ) {
                                    delete (*i).second;
                            }
                    }
                    ptr_map() {}
                    ptr_map( const ptr_map& that ) {
                            for( typename map_type::const_iterator i = that.map_.begin(); i != that.map_.end() ; ++i ) {
                                    map_[ (*i).first ] = new  JsonValueHandleT( *( (*i).second ) ) ;

                            }
                    }
            };


    template< class JsonValueHandleT >
            class ptr_vector {

                    typedef typename std::vector < JsonValueHandleT* >     vector_type;

                    vector_type vector_;

                    public:
                    typedef typename std::vector < JsonValueHandleT* >::const_iterator const_iterator;

                    const_iterator begin() const { return vector_.begin(); }
                    const_iterator end() const { return vector_.end(); }

                    template< class FuncT >
                    void for_each( FuncT & func ) {
                        for( typename vector_type::iterator i = vector_.begin(); i != vector_.end(); ++i ) {
                            func( *( *i ) );
                        }

                    }
                    JsonValueHandleT& operator[] ( unsigned int idx ) {
                            JsonValueHandleT* & p = vector_[idx];
                            if ( ! p ) {
                                    p = new JsonValueHandleT();
                            }
                            return *p;
                    }

                    unsigned int    size() const { return vector_.size(); }
                    void            resize(unsigned int s ) { vector_.resize(s); }

                    ~ptr_vector() {
                            for( typename vector_type::iterator i = vector_.begin(); i != vector_.end(); ++i ) {
                                    delete *i;
                            }
                    }

                    ptr_vector() { }
                    ptr_vector( const ptr_vector& that ) {
                            vector_.reserve( that.vector_.size() ) ;
                            for( typename vector_type::const_iterator i = that.vector_.begin(); i != that.vector_.end() ; ++i ) {
                                    vector_.push_back( new JsonValueHandleT( *(*i) ) );
                            }


                    }
            };


    template < bool, class StringT, class ValueT >
        struct select_ptr_container_types {
        
        };
    
    template <class StringT, class ValueT >
        struct select_ptr_container_types<false,StringT,ValueT> {
            typedef std::map< StringT, ValueT >  object_t;
            typedef std::vector< ValueT >   array_t;
        };

    template <class StringT, class ValueT >
        struct select_ptr_container_types<true,StringT,ValueT> {
            typedef ptr_map< StringT,ValueT >  object_t;
            typedef ptr_vector<ValueT >   array_t;
        };





    template< class T >
            T& deref_ptr( T& v ) { return v; }


    template< class T >
            T& deref_ptr( T* v ) { return *v; }













}
}
}


#endif
