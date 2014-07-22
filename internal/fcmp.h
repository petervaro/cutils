/* INFO ************************************************************************
**                                                                            **
**                                   cutils                                   **
**                                   ======                                   **
**                                                                            **
**                     Modern and Lightweight C Utilities                     **
**                       Version: 0.8.80.128 (20140721)                       **
**                                                                            **
**                           File: internal/fcmp.h                            **
**                                                                            **
**           Designed and written by Peter Varo. Copyright (c) 2014           **
**             License agreement is provided in the LICENSE file              **
**                 For more info visit: http://www.cutils.org                 **
**                                                                            **
************************************************************************ INFO */

#ifndef _FLOATING_POINT_COMPARISON_H_35435743482877113_
#define _FLOATING_POINT_COMPARISON_H_35435743482877113_

#include <math.h>     /* fabs(f|l)?() */
#include <float.h>    /* (FLT|L?DBL)_EPSILON */
#include <stdbool.h>  /* bool */

/*----------------------------------------------------------------------------*/
static inline bool
cutils_fcmp_float_compare(float a,
                          float b)
{
    return fabsf(a - b) < FLT_EPSILON;
}


/*----------------------------------------------------------------------------*/
static inline bool
cutils_fcmp_double_compare(double a,
                           double b)
{
    return fabs(a - b) < DBL_EPSILON;
}


/*----------------------------------------------------------------------------*/
static inline bool
cutils_fcmp_long_double_compare(long double a,
                                long double b)
{
    return fabsl(a - b) < LDBL_EPSILON;
}


/*----------------------------------------------------------------------------*/
#define cutils_fcmp_compare(a, b) _Generic((a), \
    float: _Generic((b), \
        float: cutils_fcmp_float_compare, \
        double: cutils_fcmp_double_compare, \
        default: cutils_fcmp_long_double_compare), \
    double: _Generic((b), \
        long double: cutils_fcmp_long_double_compare, \
        default: cutils_fcmp_double_compare), \
    default: cutils_fcmp_long_double_compare)(a, b)

#endif /* _FLOATING_POINT_COMPARISON_H_35435743482877113_ */
