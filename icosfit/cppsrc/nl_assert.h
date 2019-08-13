#ifndef NL_ASSERT_H_INCLUDED
#define NL_ASSERT_H_INCLUDED

#ifdef NDEBUG
  #define nl_assert(p) ((void)0)
#else
  #include "nl.h"

  #define nl_assert(e) \
    ((e) ? 0 : \
    nl_error( 4, "%s:%d - Assert Failed: '%s'", __FILE__, __LINE__, #e ))
#endif

#ifndef assert
  #define assert(p) nl_assert(p)
#endif

#endif
