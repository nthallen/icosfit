/* nldbg.c defines nl_debug_level
 */
#include "nl.h"

int nl_debug_level = -1;
/*
=Name nl_debug_level: Select level of debug messages
=Subject Nortlib
=Synopsis
int nl_debug_level;

=Description

nl_debug_level controls which debug messages are output in
=nl_err=() by =nl_verror=(). nl_debug_level has no effect on
msg(), which controls debug verbosity via the -l flag.

=SeeAlso

  =Nortlib= functions.

=End
*/
