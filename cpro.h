/* INFO ************************************************************************
**                                                                            **
**                                   cutils                                   **
**                                   ======                                   **
**                                                                            **
**                     Modern and Lightweight C Utilities                     **
**                       Version: 0.8.72.220 (20140708)                       **
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
#undef  cutils_cpro_profile
#define cutils_cpro_profile(cycles, time, function, ...)                       \
    do {                                                                       \
        size_t start = clock();                                                \
        for(size_t i=0; i<(size_t)cycles; i++)                                 \
            function(__VA_ARGS__);                                             \
        size_t end = clock();                                                  \
        time = (double)(end - start) / CLOCKS_PER_SEC;                         \
    } while (0)

#endif /* _C_PROFILER_H_6503982333617538_ */
