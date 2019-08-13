/* This file should be included by all sources. It is
   included by ICOSfit.h, but any files which don't include
   ICOSfit.h should include it explicitly.
*/
#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#ifdef _MALLOC_H_INCLUDED
  #error Wrong malloc.c included
#endif
#if HAVE_MALLOC_G_MALLOC_H
  #include <sys/types.h>
  #include <malloc_g/malloc.h>
  extern "C" {
     extern char *strerror( int __errnum );
  }
#else
  #include <string.h>
#endif

/* This could probably be located in a more appropriate place */
/* This is the type of the two header words at the top of my binary files 
   This is currently used in funcbase.c and ptread.c.
   This type should be a 4-byte unsigned integer. That would be
   a 'unsigned long' on Watcom and 'unsigned short' on a 64-bit
   architecture. *sigh*
*/
#include <stdint.h>
typedef uint32_t icos_hdr_t;

#define DOUBLE_PRECISION
#ifdef DOUBLE_PRECISION
typedef double ICOS_Float;
#define RESIZE_INPUT 1
#define FLOAT_STYLE "D"
#define FMT_E "le"
#define FMT_F "lf"
#define FMT_G "lg"
#else
typedef float ICOS_Float;
#define RESIZE_INPUT 0
#define FLOAT_STYLE "F"
#define FMT_E "e"
#define FMT_F "f"
#define FMT_G "g"
#endif

#include <endian.h>
#if BYTE_ORDER == BIG_ENDIAN
  #define USE_BIG_ENDIAN
  #include <stdio.h>
  extern int fread_swap32( void *buf, size_t size, size_t count, FILE *fp );

  /* Following functions stolen and modified from cygwin's byteswap.h */
  inline unsigned short bswap_16 (unsigned short __x) {
    return (__x >> 8) | (__x << 8);
  }

  inline unsigned int bswap_32 (unsigned int __x) {
    return (bswap_16 (__x & 0xffff) << 16) | (bswap_16 (__x >> 16));
  }

  inline double bswap_64 (double _dx) {
    unsigned long long __x = *((unsigned long long *)(&_dx));
    __x = (((unsigned long long) bswap_32 (__x & 0xffffffffull)) << 32) |
                                     (bswap_32 (__x >> 32));
    return *((double *)(&__x));
  }
#else
  #define fread_swap32 fread
#endif

#endif
