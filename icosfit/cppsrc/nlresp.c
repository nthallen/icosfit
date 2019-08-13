/* nlresp.c defines nl_response.
 * nl_response defines how nl routines respond to error situations.
 * In most cases, an error is considered fatal, but in certain cases
 * an error can be tolerated. The nl routines will in general
 * support both responses based on the setting of nl_response.
 * If nl_response is NLRSP_DIE, errors result in termination
 * via nl_error(3, ...). If nl_response is NLRSP_WARN, errors
 * will result in nl_error(1, ...), but the defined error return
 * will occur. If nl_response is NLRSP_QUIET, no error message
 * will be printed, just the error return value.
 * The values chosen for NLRSP_* are arbitrarily chosen to match
 * the type codes to nl_error.
 */
#include "nl.h"

int nl_response = NLRSP_DIE;

int set_response(int newval) {
  int oldval;
  
  oldval = nl_response;
  nl_response = newval;
  return(oldval);
}
/*
=Name nl_response: Error Response Code
=Subject nl
=Name set_response(): Modify Error Response Code
=Subject nl
=Synopsis

#include "nl.h"
int nl_response;
int set_response(int newval);

=Description

  The nl_response setting determines how most all nl
  functions react to errors. nl_response may be set to any value
  acceptable as a level argument to =nl_error=() or msg(). By
  default, nl_response is set to 3, which means any error in a
  nl function will be considered a fatal error. By changing
  the setting to 1, an error will simply be reported as a
  warning.<P>
  
  The philosophy here is that if you have not taken steps to
  handle an error condition, then the error condition cannot be
  tolerated. This makes it possible to write simple programs
  simply and to find out if more sophisticated error handling is
  required. In many cases, additional error handling will not be
  required; If your program need to communicate with a particular
  server and the server cannot be located, that probably should
  be a fatal error, and no further programming is required to
  make it so. Additional code is only required when you wish to
  selectively tolerate specific errors.<P>
  
  set_response() is a convenient way to manipulate nl_response.
  It sets nl_response to a new value and returns the old value so
  that it can be saved and restored after the current operation
  is completed.<P>

=Returns
  set_response() returns the old value of nl_response so that it
  can be saved and restored.

=SeeAlso
  =nl_error=().

=End
*/
