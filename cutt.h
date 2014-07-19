/* INFO ************************************************************************
**                                                                            **
**                                   cutils                                   **
**                                   ======                                   **
**                                                                            **
**                     Modern and Lightweight C Utilities                     **
**                       Version: 0.8.72.556 (20140718)                       **
**                                                                            **
**                                File: cutt.h                                **
**                                                                            **
**           Designed and written by Peter Varo. Copyright (c) 2014           **
**             License agreement is provided in the LICENSE file              **
**                 For more info visit: http://www.cutils.org                 **
**                                                                            **
************************************************************************ INFO */

#ifndef _C_UNIT_TEST_TOOLS_H_3818217702141947_
#define _C_UNIT_TEST_TOOLS_H_3818217702141947_

#include <stdio.h>   /* fprintf(), stderr, stdout */
#include <stdlib.h>  /* malloc(), free(), exit(), EXIT_FAILURE */

#undef  __str
#undef  _str
#undef cutils_cutt_try
#undef cutils_cutt_report

#define __str(value) #value
#define _str(value) __str(value)

/*----------------------------------------------------------------------------*/
typedef struct
{
    size_t fail;
    size_t size;
    char *info[];
} cutils_cutt_Tester;

/*----------------------------------------------------------------------------*/
static inline void
cutils_cutt_Tester_new(cutils_cutt_Tester **tester,
                       size_t count)
{
    cutils_cutt_Tester *_tester = malloc(sizeof(cutils_cutt_Tester) +
                                         count*sizeof(char *));
    if (!_tester)
    {
        fprintf(stderr, "CUTT: Internal allocation failed\n");
        exit(EXIT_FAILURE);
    }
    _tester->fail = 0;
    _tester->size = count;
    *tester = _tester;
}

/*----------------------------------------------------------------------------*/
static inline void
cutils_cutt_Tester_del(cutils_cutt_Tester *tester)
{
    free(tester);
}


/*----------------------------------------------------------------------------*/
#define cutils_cutt_Tester_try(tester, expression)                             \
    do {                                                                       \
        if (!(expression))                                                     \
            tester->info[tester->fail++] = "CUTT: in file: '" __FILE__         \
                                           "', at line: "_str(__LINE__)        \
                                           ": '"#expression"'";                \
    } while (0)


/*----------------------------------------------------------------------------*/
#define cutils_cutt_Tester_report(tester)                                      \
    do {                                                                       \
        size_t fail = tester->fail, size = tester->size;                       \
        if (fail)                                                              \
        {                                                                      \
            fprintf(stderr, "CUTT: Some tests "                                \
                            "(%zu / %zu) failed:\n", size-fail, size);         \
            for (size_t i=0; i<fail; i++)                                      \
                fprintf(stderr, "%s\n", tester->info[i]);                      \
        }                                                                      \
        else                                                                   \
            fprintf(stderr, "CUTT: All tests "                                 \
                            "(%zu / %zu) passed.\n", size, size);              \
    } while (0)

#endif /* _C_UNIT_TEST_TOOLS_H_3818217702141947_ */
