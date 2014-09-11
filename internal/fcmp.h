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
