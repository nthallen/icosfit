/* newmem.c contains a simple new_memory() function. It is named
 * nl_new_memory() in order not to conflict with memlib.h, but
 * nl.h will define new_memory to be nl_new_memory if memlib.h
 * has not been included.
 */
#include <stdlib.h>
#include "nl.h"

void *new_memory(size_t size) {
  void *p;
  
  p = malloc(size);
  if (p == 0 && nl_response)
    nl_error(nl_response, "Memory allocation error");
  return p;
}

void nl_free_memory(void *p) {
  free(p);
}
/*
=Name new_memory(): Safe memory allocation function
=Subject nl
=Name nl_free_memory(): Safe memory free function
=Subject nl
=Synopsis
#include "nl.h"
void *new_memory(size_t size);
void nl_free_memory(void *p);

=Description

  new_memory() is a thin cover for malloc() that guarantees
  a non-NULL return. If memory allocation fails, new_memory()
  will terminate the program by calling =nl_error=(3).
  
=Returns

  Returns a newly allocated copy of the argument string.
  If memory allocation fails, the program will terminate
  via =nl_error=(3).
  
  new_memory() uses the same name as a function in the memlib
  library which provides more sophisticated memory allocation
  strategies, including hooks for garbage collection or a limited
  form of virtual memory.
  
  nl_free_memory() is an extremely thin cover for free().

=SeeAlso
  =nl_response=, =nl_strdup=().
=End
*/
