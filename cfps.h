/* INFO ************************************************************************
**                                                                            **
**                                   cutils                                   **
**                                   ======                                   **
**                                                                            **
**                     Modern and Lightweight C Utilities                     **
**                       Version: 0.8.72.365 (20140711)                       **
**                                                                            **
**                                File: cfps.h                                **
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

#ifndef _C_FRAME_PER_SECOND_H_2834550704086395_
#define _C_FRAME_PER_SECOND_H_2834550704086395_

#include <stdio.h>  /* fprintf() */

/* TODO: At the moment in a single scope only the first appearence of
         these functions will work. NOTE: If you want to use both printfps
         and getfps at the same time, use the getfps function only, and pass
         a getter function which can also implement the printing functionality */

/*----------------------------------------------------------------------------*/
static inline void
cutils_cfps_getfps(double (*gettime)(void),
            void (*getter)(int, void*),
            void *data)
{
    static double old_time = 0.0;
    static double time_sum = 0.0;
    static float  interval = 1.f;
    static int    fpscount = 0;

    double new_time  = gettime();
    time_sum += new_time - old_time;
    old_time = new_time;
    fpscount++;

    if (time_sum > interval)
    {
        getter(fpscount, data);
        fpscount = 0;
        time_sum = 0;
    }
}


/*----------------------------------------------------------------------------*/
static inline void
__printfps_getter_func(int fps, void *data)
{
    fprintf(stdout, "FPS: %d\n", fps);
}


/*----------------------------------------------------------------------------*/
#undef  cutils_cfps_printfps
#define cutils_cfps_printfps(gettime) __getfps(gettime, __printfps_getter_func, NULL)

#endif /* _C_FRAME_PER_SECOND_H_2834550704086395_ */
