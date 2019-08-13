/* nl.h include file for nl library
 */
#ifndef _NL_H_INCLUDED
#define _NL_H_INCLUDED

#include <stdio.h>
#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

int Skel_open(const char *name);
int Skel_copy(FILE *ofp, const char *label, int copyout);

extern int (*nl_error)(int level, const char *s, ...); /* nl_error.c */
int nl_err(int level, const char *s, ...); /* nl_error.c */
#ifdef va_start
  int nl_verror(FILE *ef, int level, const char *fmt, va_list args); /* nl_verr.c */
#endif

/* These codes are taken from the old msg.h */
#define MSG_DEBUG -2
#define MSG_EXIT -1
#define MSG_EXIT_NORM MSG_EXIT
#define MSG 0
#define MSG_PASS MSG
#define MSG_WARN 1
#define MSG_ERROR 2
#define MSG_FAIL MSG_ERROR
#define MSG_FATAL 3
#define MSG_EXIT_ABNORM 4
#define MSG_DBG(X) (MSG_DEBUG-(X))

extern int nl_debug_level; /* nldbg.c */
extern int nl_response; /* nlresp.c */
int set_response(int newval); /* nlresp.c */
#define NLRSP_DIE 3
#define NLRSP_WARN 1
#define NLRSP_QUIET 0

/* guaranteed memory allocator, memlib.h subset.
 * Include memlib.h to obtain the full definition
 */
#ifndef MEMLIB_H_INCLUDED
  #define new_memory(x) nl_new_memory(x)
  #define free_memory(x) nl_free_memory(x)
  #define nl_strdup(x) nrtl_strdup(x)
#endif
void *nl_new_memory(size_t size);
void nl_free_memory(void *p);
char *nrtl_strdup(const char *s);

/* ascii_escape.c */
const char *ascii_escape(const char *ibuf);

#if defined(__QNXNTO__)
  #define OPTIND_RESET 1
#else
  #define OPTIND_RESET 0
#endif

#ifdef __cplusplus
};
#endif

#endif
