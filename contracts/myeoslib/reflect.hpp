#pragma once
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/seq/seq.hpp>
#include <boost/preprocessor/stringize.hpp>

namespace myeosio {
  template<typename T>
  struct reflector {
     typedef std::false_type is_reflected;
     typedef std::false_type is_enum;
  };

} /// myeosio



#define MYEOSLIB_REFLECT_VISIT_BASE(r, visitor, base) \
  myeosio::reflector<base>::visit( visitor );

#define MYEOSLIB_REFLECT_VISIT2_BASE(r, visitor, base) \
  myeosio::reflector<base>::visit( t, forward<Visitor>(visitor) );


#define MYEOSLIB_REFLECT_VISIT_MEMBER( r, visitor, elem ) \
{ typedef decltype((static_cast<type*>(nullptr))->elem) member_type;  \
   visitor( &type::elem ); \
}

#define MYEOSLIB_REFLECT_VISIT2_MEMBER( r, visitor, elem ) \
{ typedef decltype((static_cast<type*>(nullptr))->elem) member_type;  \
   visitor( t.elem ); \
}


#define MYEOSLIB_REFLECT_BASE_MEMBER_COUNT( r, OP, elem ) \
  OP myeosio::reflector<elem>::total_member_count

#define MYEOSLIB_REFLECT_MEMBER_COUNT( r, OP, elem ) \
  OP 1

#define MYEOSLIB_REFLECT_DERIVED_IMPL_INLINE( TYPE, INHERITS, MEMBERS ) \
template<typename Visitor>\
static inline void visit( Visitor&& v ) { \
    BOOST_PP_SEQ_FOR_EACH( MYEOSLIB_REFLECT_VISIT_BASE, v, INHERITS ) \
    BOOST_PP_SEQ_FOR_EACH( MYEOSLIB_REFLECT_VISIT_MEMBER, v, MEMBERS ) \
} \
template<typename Visitor>\
static inline void visit( const type& t, Visitor&& v ) { \
    BOOST_PP_SEQ_FOR_EACH( MYEOSLIB_REFLECT_VISIT2_BASE, v, INHERITS ) \
    BOOST_PP_SEQ_FOR_EACH( MYEOSLIB_REFLECT_VISIT2_MEMBER, v, MEMBERS ) \
} \
template<typename Visitor>\
static inline void visit( type& t, Visitor&& v ) { \
    BOOST_PP_SEQ_FOR_EACH( MYEOSLIB_REFLECT_VISIT2_BASE, v, INHERITS ) \
    BOOST_PP_SEQ_FOR_EACH( MYEOSLIB_REFLECT_VISIT2_MEMBER, v, MEMBERS ) \
}

#define MYEOSLIB_REFLECT_DERIVED_IMPL_EXT( TYPE, INHERITS, MEMBERS ) \
template<typename Visitor>\
void myeosio::reflector<TYPE>::visit( Visitor&& v ) { \
    BOOST_PP_SEQ_FOR_EACH( MYEOSLIB_REFLECT_VISIT_BASE, v, INHERITS ) \
    BOOST_PP_SEQ_FOR_EACH( MYEOSLIB_REFLECT_VISIT_MEMBER, v, MEMBERS ) \
}


/**
 *  @def MYEOSLIB_REFLECT(TYPE,MEMBERS)
 *  @brief Specializes myeosio::reflector for TYPE
 *
 *  @param MEMBERS - a sequence of member names.  (field1)(field2)(field3)
 *
 *  @see MYEOSLIB_REFLECT_DERIVED
 */
#define MYEOSLIB_REFLECT( TYPE, MEMBERS ) \
    MYEOSLIB_REFLECT_DERIVED( TYPE, BOOST_PP_SEQ_NIL, MEMBERS )

#define MYEOSLIB_REFLECT_TEMPLATE( TEMPLATE_ARGS, TYPE, MEMBERS ) \
    MYEOSLIB_REFLECT_DERIVED_TEMPLATE( TEMPLATE_ARGS, TYPE, BOOST_PP_SEQ_NIL, MEMBERS )

#define MYEOSLIB_REFLECT_EMPTY( TYPE ) \
    MYEOSLIB_REFLECT_DERIVED( TYPE, BOOST_PP_SEQ_NIL, BOOST_PP_SEQ_NIL )


#define MYEOSLIB_REFLECT_FWD( TYPE ) \
namespace myeosio { \
  template<> struct reflector<TYPE> {\
       typedef TYPE type; \
       typedef myeosio::true_type is_reflected; \
       enum  member_count_enum {  \
         local_member_count = BOOST_PP_SEQ_SIZE(MEMBERS), \
         total_member_count = local_member_count BOOST_PP_SEQ_FOR_EACH( MYEOSLIB_REFLECT_BASE_MEMBER_COUNT, +, INHERITS )\
       }; \
       template<typename Visitor> static void visit( Visitor&& v ); \
       template<typename Visitor> static void visit( const type& t, Visitor&& v ); \
       template<typename Visitor> static void visit( type& t, Visitor&& v ); \
  }; }


#define MYEOSLIB_REFLECT_DERIVED_IMPL( TYPE, MEMBERS ) \
    MYEOSLIB_REFLECT_IMPL_DERIVED_EXT( TYPE, BOOST_PP_SEQ_NIL, MEMBERS )

#define MYEOSLIB_REFLECT_IMPL( TYPE, MEMBERS ) \
    MYEOSLIB_REFLECT_DERIVED_IMPL_EXT( TYPE, BOOST_PP_SEQ_NIL, MEMBERS )



/**
 *  @def MYEOSLIB_REFLECT_DERIVED(TYPE,INHERITS,MEMBERS)
 *
 *  @brief Specializes myeosio::reflector for TYPE where
 *         type inherits other reflected classes
 *
 *  @param INHERITS - a sequence of base class names (basea)(baseb)(basec)
 *  @param MEMBERS - a sequence of member names.  (field1)(field2)(field3)
 */
#define MYEOSLIB_REFLECT_DERIVED( TYPE, INHERITS, MEMBERS ) \
namespace myeosio {  \
template<> struct reflector<TYPE> {\
    typedef TYPE type; \
    typedef myeosio::true_type  is_reflected; \
    typedef myeosio::false_type is_enum; \
    enum  member_count_enum {  \
      local_member_count = 0  BOOST_PP_SEQ_FOR_EACH( MYEOSLIB_REFLECT_MEMBER_COUNT, +, MEMBERS ),\
      total_member_count = local_member_count BOOST_PP_SEQ_FOR_EACH( MYEOSLIB_REFLECT_BASE_MEMBER_COUNT, +, INHERITS )\
    }; \
    MYEOSLIB_REFLECT_DERIVED_IMPL_INLINE( TYPE, INHERITS, MEMBERS ) \
}; }
#define MYEOSLIB_REFLECT_DERIVED_TEMPLATE( TEMPLATE_ARGS, TYPE, INHERITS, MEMBERS ) \
namespace myeosio {  \
template<BOOST_PP_SEQ_ENUM(TEMPLATE_ARGS)> struct reflector<TYPE> {\
    typedef TYPE type; \
    typedef myeosio::true_type  is_defined; \
    typedef myeosio::false_type is_enum; \
    enum  member_count_enum {  \
      local_member_count = 0  BOOST_PP_SEQ_FOR_EACH( MYEOSLIB_REFLECT_MEMBER_COUNT, +, MEMBERS ),\
      total_member_count = local_member_count BOOST_PP_SEQ_FOR_EACH( MYEOSLIB_REFLECT_BASE_MEMBER_COUNT, +, INHERITS )\
    }; \
    MYEOSLIB_REFLECT_DERIVED_IMPL_INLINE( TYPE, INHERITS, MEMBERS ) \
}; }
