/* INFO ************************************************************************
**                                                                            **
**                                   cutils                                   **
**                                   ======                                   **
**                                                                            **
**                     Modern and Lightweight C Utilities                     **
**                       Version: 0.8.72.004 (20140703)                       **
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

/* Return value type */
#if __STDC__
typedef int errno_t;
#else
#include <errno.h>
#endif

/* If setup mode */
#ifdef CUTT_SET
#include <stdio.h>  /* fprintf(), stderr, stdout */

/*------------------------------------------------------------------------------
 * Setup tester object */
#undef  tester
#define tester()                                                               \
        struct {                                                               \
            size_t count;                                                      \
            size_t fails;                                                      \
            const char *funcs[];                                               \
        } _TESTER_2755985868339231_ = {0}

/*------------------------------------------------------------------------------
 * Interface function-like macro for testcase function */
#undef  test
#define test(function, ...)                                                    \
    do {                                                                       \
        fprintf(stderr,                                                        \
                "----- TEST %03zu -----\n%s()\n",                              \
                _TESTER_2755985868339231_.count,                               \
                #function);                                                    \
        /* If test failed */                                                   \
        if (function(__VA_ARGS__))                                             \
        {                                                                      \
            _TESTER_2755985868339231_.funcs[_TESTER_2755985868339231_.fails] = \
            #function;                                                         \
            _TESTER_2755985868339231_.fails++;                                 \
        }                                                                      \
        _TESTER_2755985868339231_.count++;                                     \
    } while (0)

#endif /* CUTT_SET */

/*------------------------------------------------------------------------------
 * Test reporting function */
#undef  report
#define report()                                                               \
    do {                                                                       \
        fprintf(stderr, "----- REPORT -----\n");                               \
        /* If some tests failed */                                             \
        if (_TESTER_2755985868339231_.fails)                                   \
        {                                                                      \
            fprintf(stderr,                                                    \
                    "SOME TESTS [FAILED] (%zu/%zu)\n"                          \
                    "In the following function(s):\n",                         \
                    _TESTER_2755985868339231_.fails,                           \
                    _TESTER_2755985868339231_.count);                          \
            for (size_t i=0; i<_TESTER_2755985868339231_.fails; i++)           \
                fprintf(stderr,                                                \
                        "\t%s()\n",                                            \
                        _TESTER_2755985868339231_.funcs[i]);                   \
            fprintf(stderr, "\n");                                             \
            break;                                                             \
        }                                                                      \
        /* If everything went fine */                                          \
        fprintf(stderr,                                                        \
                "ALL TESTS [PASSED] (%zu/%zu)\n\n",                            \
                _TESTER_2755985868339231_.count,                               \
                _TESTER_2755985868339231_.count);                              \
    } while (0)

#undef  try
#define try(expr)                                                              \
    do {                                                                       \
        if (!(expr))                                                           \
        {                                                                      \
            fprintf(stderr,                                                    \
                    "\n\t[FAILED] File: '%s', line: %d, function: '%s'\n\n\n", \
                    __FILE__, __LINE__, __func__);                             \
            return 1;                                                          \
        }                                                                      \
    } while (0)

#undef  pass
#define pass()                                                                 \
    do {                                                                       \
        fprintf(stdout, "\n\t[PASSED]\n\n\n");                                 \
        return 0;                                                              \
    } while (0)

#endif /* _C_UNIT_TEST_TOOLS_H_3818217702141947_ */
