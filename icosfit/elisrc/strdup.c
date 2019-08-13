/* strdup is a replacement for the Lattice function of the same name.
*/
#include <string.h>
#include "nl.h"

/* t = nrtl_strdup(s);
char *t, *s;

strdup is a replacement for the Lattice function of the same name.
This one provides the same function, but uses my dynamic memory
allocators instead of malloc so it is guaranteed to return a valid
pointer or die!
-*/
char *nrtl_strdup(const char *s) {
  char *copy;

  copy = (char *)new_memory(strlen(s)+1);
  if (copy != NULL) strcpy(copy, s);
  return(copy);
}
/*
=Name nrtl_strdup(): Safe strdup() function
=Subject nl
=Name nl_strdup(): Safe strdup() function
=Subject nl
=Synopsis
#include "nl.h"
char *nrtl_strdup(const char *s);
char *nl_strdup(const char *s);

=Description

  nrtl_strdup() and nl_strdup() both provide the functionality of
  the semi-standard strdup() function with the exception that
  if memory allocation fails, it will cause a fatal error.
  As such, both functions are guaranteed to return a
  newly-allocated copy of the passed string.
  
  nrtl_strdup() is the function that is included in the nl
  library. nl_strdup() is implemented as a macro in nl.h
  only if memlib.h has not been included, since the name
  conflicts with a routine in that library.
  
=Returns

  Returns a newly allocated copy of the argument string.
  If memory allocation fails, the program will terminate
  via =nl_error=(3).

=SeeAlso
  =nl_response=, =new_memory=().
=End
*/
