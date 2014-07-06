/* INFO ************************************************************************
**                                                                            **
**                                   cutils                                   **
**                                   ======                                   **
**                                                                            **
**                     Modern and Lightweight C Utilities                     **
**                       Version: 0.8.72.026 (20140706)                       **
**                                                                            **
**                                File: cpro.h                                **
**                                                                            **
**           Designed and written by Peter Varo. Copyright (c) 2014           **
**             License agreement is provided in the LICENSE file              **
**                 For more info visit: http://www.cutils.org                 **
**                                                                            **
************************************************************************ INFO */

#ifndef _C_PROFILER_H_6503982333617538_
#define _C_PROFILER_H_6503982333617538_

#include <time.h>
#include <stdlib.h>

/*----------------------------------------------------------------------------*/
#ifdef __profile
  #error we are so fucked
#endif
#undef  __profile
#define __profile(cycles, time, function, ...)                                 \
    do {                                                                       \
        size_t start = clock();                                                \
        for(size_t i=0; i<(size_t)cycles; i++)                                 \
            function(__VA_ARGS__);                                             \
        size_t end = clock();                                                  \
        time = (double)(end - start) / CLOCKS_PER_SEC;                         \
    } while (0)

/* Decide use prefix or not */
#ifdef CUTILS_NAMESPACE
  #undef  cutils_profile
  #define cutils_profile(...) __profile(__VA_ARGS__)
#else
  #undef  profile
  #define profile(...) __profile(__VA_ARGS__)
#endif /* CUTILS_NAMESPACE*/

#endif /* _C_PROFILER_H_6503982333617538_ */
