/* INFO ************************************************************************
**                                                                            **
**                                   cutils                                   **
**                                   ======                                   **
**                                                                            **
**                     Modern and Lightweight C Utilities                     **
**                       Version: 0.8.72.259 (20140709)                       **
**                                                                            **
**                       File: etc/cutils_modern_api.c                        **
**                                                                            **
**           Designed and written by Peter Varo. Copyright (c) 2014           **
**             License agreement is provided in the LICENSE file              **
**                 For more info visit: http://www.cutils.org                 **
**                                                                            **
************************************************************************ INFO */

/*  Because C uses explicit error handling (there are no exceptions)
    it is a good idea to use the return value as a signal indicating if
    the subroutine was successful or not. And because C can only return
    a single value, use pointers to pass and recieve values */

bool function(void *result);



/*  Instead of trying to mimic OOP-like methods using function pointers
    and struct instances, build interfaces with the help of variadic
    arguments and generic macros */

#define method(o, ...) _Generic((o), int: function)(o)



/*  To achieve other languages default values, use variadic arguments
    macros. For example in Python, if a function looks something like this:

    def function(a, b=0, c=1):
        pass

    Then it could be called like:

    function(10)            == function(10, 0, 1)
    function(10, 12)        == function(10, 12, 1)
    function(10, 12, 50)

    In C, using cutils' vargs it will look like this */

void _function(int, int, int){}
#define function1(a)    _function(a, 0, 1)
#define function2(a, b) _function(a, b, 1)
#define function(...) vargs(__VA_ARGS__)(4)(__VA_ARGS__, zero, \
                            function2, function1)(__VA_ARGS__)

/* Now all these calls are valid */
function(10);
function(10, 12);
function(10, 12, 50);



/*  The generic macros are evaluating in a later stages of compilation,
    therefore they cannot choose a macro from their assoc list. The only
    hack one do is to use a generic macro to point at, which contains
    only a single default key */

/* THIS IS NOT WORKING... */
#define pointer(x) _Generic((x), int: (do {printf("%d\n", i);} while(0)))

/* 1) DESIGN   | the API first
   2) HACK     | the solution to see if working
   3) PRETTOFY | to make it idiomatic
   4) OPTIMISE | profile it and optimise if necessary */
