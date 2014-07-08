/* INFO ************************************************************************
**                                                                            **
**                                   cutils                                   **
**                                   ======                                   **
**                                                                            **
**                     Modern and Lightweight C Utilities                     **
**                       Version: 0.8.72.220 (20140708)                       **
**                                                                            **
**                                File: cfps.h                                **
**                                                                            **
**           Designed and written by Peter Varo. Copyright (c) 2014           **
**             License agreement is provided in the LICENSE file              **
**                 For more info visit: http://www.cutils.org                 **
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
