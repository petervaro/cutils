/* INFO ************************************************************************
**                                                                            **
**                                   cutils                                   **
**                                   ======                                   **
**                                                                            **
**                     Modern and Lightweight C Utilities                     **
**                       Version: 0.8.72.365 (20140711)                       **
**                                                                            **
**                                File: cpro.h                                **
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
