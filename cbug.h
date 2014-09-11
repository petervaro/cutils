/* INFO ************************************************************************
**                                                                            **
**                                   cutils                                   **
**                                   ======                                   **
**                                                                            **
**                     Modern and Lightweight C Utilities                     **
**                       Version: 0.8.90.788 (20140826)                       **
**                                                                            **
**                                File: cbug.h                                **
**                                                                            **
**   For more information about the project, visit <http://www.cutils.org>.   **
**                       Copyright (C) 2014 Peter Varo                        **
**                                                                            **
**  This program is free software: you can redistribute it and/or modify it   **
**   under the terms of the GNU General Public License as published by the    **
**       Free Software Foundation, either version 3 of the License, or        **
**                    (at your option) any later version.                     **
**                                                                            **
**    This program is distributed in the hope that it will be useful, but     **
**         WITHOUT ANY WARRANTY; without even the implied warranty of         **
**            MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.            **
**            See the GNU General Public License for more details.            **
**                                                                            **
**     You should have received a copy of the GNU General Public License      **
**     along with this program, most likely a file in the root directory,     **
**        called 'LICENSE'. If not, see <http://www.gnu.org/licenses>.        **
**                                                                            **
************************************************************************ INFO */

#ifndef _C_DEBUG_H_10629572188582681_
#define _C_DEBUG_H_10629572188582681_

/* TODO: sdebug() -> expands to string literal or
         debugexc(func, msg, len) -> calls raise() or ccraise() */

#ifndef CBUG_OFF

#include <stdio.h>   /* fprintf(), stderr */
#include "carg.h"    /* vargs() */

/* Make macro variables available */
#undef __space
#undef __tab
#undef __debug0
#undef __debug1
#undef __debug2
#undef cutils_cbug_debug

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
#define __space " "
#define __tab __space __space __space __space

/* Generic debug information */
#define __debug0() (__debug_9802738545513323(__FILE__, __LINE__, __func__))

/* Generic debug information + simple string */
#define __debug1(str) \
    do { __debug0(); fprintf(stderr, __tab "%s\n", str); } while(0)

/* Generic debug information + formatted string */
#define __debug2(fmt, ...) \
    do { __debug0(); fprintf(stderr, __tab fmt "\n", __VA_ARGS__); } while (0)

/* Debug dispatcher */
#define cutils_cbug_debug(...) cutils_carg_vargs(__VA_ARGS__)(64)(__VA_ARGS__, \
    __debug0,__debug2,__debug2,__debug2,__debug2,__debug2,__debug2,__debug2,   \
    __debug2,__debug2,__debug2,__debug2,__debug2,__debug2,__debug2,__debug2,   \
    __debug2,__debug2,__debug2,__debug2,__debug2,__debug2,__debug2,__debug2,   \
    __debug2,__debug2,__debug2,__debug2,__debug2,__debug2,__debug2,__debug2,   \
    __debug2,__debug2,__debug2,__debug2,__debug2,__debug2,__debug2,__debug2,   \
    __debug2,__debug2,__debug2,__debug2,__debug2,__debug2,__debug2,__debug2,   \
    __debug2,__debug2,__debug2,__debug2,__debug2,__debug2,__debug2,__debug2,   \
    __debug2,__debug2,__debug2,__debug2,__debug2,__debug2,__debug2,__debug1)   \
    (__VA_ARGS__)

#else
  #undef  cutils_cbug_debug
  #define cutils_cbug_debug(...)
#endif  /* CBUG_OFF */

/* Format value into boolean representation */
#undef  cutils_cbug_boolean
#define cutils_cbug_boolean(value) (value ? "true" : "false")

#endif  /* _C_DEBUG_H_10629572188582681_ */
