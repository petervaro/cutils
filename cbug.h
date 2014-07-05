/* INFO ************************************************************************
**                                                                            **
**                                   cutils                                   **
**                                   ======                                   **
**                                                                            **
**                     Modern and Lightweight C Utilities                     **
**                       Version: 0.8.72.004 (20140703)                       **
**                                                                            **
**                                File: cbug.h                                **
**                                                                            **
**           Designed and written by Peter Varo. Copyright (c) 2014           **
**             License agreement is provided in the LICENSE file              **
**                 For more info visit: http://www.cutils.org                 **
**                                                                            **
************************************************************************ INFO */

#ifndef _CBUG_H_10629572188582681_
#define _CBUG_H_10629572188582681_

/* TODO: sdebug() -> expands to string literal or
         debugexc(func, msg, len) -> calls raise() or ccraise() */

#ifndef CBUG_OFF

#include <stdio.h>   /* fprintf(), stderr */
#include "carg.h"    /* vargs() */

/* Make macro variables available */
#undef __debug0
#undef __debug1
#undef __debug2
#undef __debug
#undef __s
#undef __t

/* Base function */
static inline void
__debug_9802738545513323(const char *file_name,
                         unsigned int line_number,
                         const char *function_name)
{
    static size_t counter = 0;
    fprintf(stderr, "%03zu\tFile: '%s', line: %d, function: '%s'\n",
            counter++, file_name, line_number, function_name);
}

/* White spaces */
#define __s " "
#define __t __s __s __s __s

/* Generic debug information */
#define __debug0() (__debug_9802738545513323(__FILE__, __LINE__, __func__))

/* Generic debug information + simple string */
#define __debug1(str) \
    do { __debug0(); fprintf(stderr, __t #str "\n"); } while(0)

/* Generic debug information + formatted string */
#define __debug2(fmt, ...) \
    do { __debug0(); fprintf(stderr, __t #fmt "\n", __VA_ARGS__); } while (0)

/* Debug dispatcher */
#define __debug(...) vargs(__VA_ARGS__)(64)(__VA_ARGS__, __debug0, __debug2,   \
    __debug2,__debug2,__debug2,__debug2,__debug2,__debug2,__debug2,__debug2,   \
    __debug2,__debug2,__debug2,__debug2,__debug2,__debug2,__debug2,__debug2,   \
    __debug2,__debug2,__debug2,__debug2,__debug2,__debug2,__debug2,__debug2,   \
    __debug2,__debug2,__debug2,__debug2,__debug2,__debug2,__debug2,__debug2,   \
    __debug2,__debug2,__debug2,__debug2,__debug2,__debug2,__debug2,__debug2,   \
    __debug2,__debug2,__debug2,__debug2,__debug2,__debug2,__debug2,__debug2,   \
    __debug2,__debug2,__debug2,__debug2,__debug2,__debug2,__debug2,__debug2,   \
    __debug2,__debug2,__debug2,__debug2,__debug2, __debug1)(__VA_ARGS__)

#else
  #undef  __debug
  #define __debug(...)
#endif  /* CBUG_OFF */

/* Decide use prefix or not */
#ifdef CUTILS_NAMESPACE
  #undef  cutils_debug
  #define cutils_debug(...) __debug(__VA_ARGS__)
#else
  #undef  debug
  #define debug(...) __debug(__VA_ARGS__)
#endif /* CUTILS_NAMESPACE*/

#endif  /* _CBUG_H_10629572188582681_ */
