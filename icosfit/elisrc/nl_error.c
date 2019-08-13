/* nl_error.c provides a default error routine for nl routines.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "nl.h"

int nl_err(int level, const char *s, ...) {
  va_list arg;

  va_start(arg, s);
  nl_verror(stderr, level, s, arg);
  va_end(arg);
  return(level);
}

int (*nl_error)(int level, const char *s, ...) = nl_err;
/*
=Name nl_error(): Standard error message function
=Subject nl
=Name nl_err(): Default nl_error function
=Subject nl
=Synopsis
#include "nl.h"
int (*nl_error)(int level, char *s, ...);
int nl_err(int level, char *s, ...);

=Description

  nl_error() is a retargettable standard error message function.
  It is actually a function pointer which may be modified either
  statically or dynamically as the application requires.<P>
  
  nl_error() functions provide standard printf-style formatting
  for status messages. The level argument determines how the
  message is handled:
  
  <UL>
    <LI>0: Informational Message
    <LI>1: Warning Message
    <LI>2: Error Message
    <LI>3: Fatal Error Message
    <LI>4: Internal Fatal Error Message
    <LI>-1: Normal Exit with Message
    <LI>-2: Debug level 1 Message
    <LI>-3: Debug level 2 Message
  </UL>

  Debug messages normally do not appear, but you can adjust the
  debug level to see some or all of your debugging messages. For
  the default functions nl_err() and nl_verror(), the current
  debug level is stored in the variable nl_debug_level, which may
  be adjustable by command line flags. For msg(), the debug level
  is controlled via the -l flag and does not use
  nl_debug_level.<P>

  The nl library provides a default function, nl_err(),
  which reports warnings to stderr and normal messages to stdout.
  The default function is included in the same module with the
  default definition of the nl_error pointer. In order to
  override the default, you must include your own definition of
  nl_error and initialize it to point to your own function.<P>
  
  This is done automatically for programs developed using the ARP
  Data Acquisition Systems architecture, where nl_error is mapped
  to the msg() function, which routes messages to a central memo
  utility. nl_error is also retargetted for many of our compilers
  to a function which prints out the current input file name and
  line number. It is then dynamically remapped to the default
  when input processing is completed. RTG and other QNX
  Windows-based programs remap nl_error to a function which pops
  up a window.<P>
  
  The point here is that library functions can count on calling a
  standard error message routine, and their messages will be
  mapped to the correct output processor depending on the
  application they are linked into.
  
=Returns

  For non-fatal errors, returns the error level code.

=SeeAlso
  =nl_response=, =nl_verror=().
=End
*/
