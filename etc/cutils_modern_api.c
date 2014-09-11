/* INFO ************************************************************************
**                                                                            **
**                                   cutils                                   **
**                                   ======                                   **
**                                                                            **
**                     Modern and Lightweight C Utilities                     **
**                       Version: 0.8.90.725 (20140821)                       **
**                                                                            **
**                       File: etc/cutils_modern_api.c                        **
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

/* Use something like this instead ??? */
static void _f_i_i(int a,   int b)   {printf("a:int,   b:int\n");}
static void _f_i_f(int a,   float b) {printf("a:int,   b:float\n");}
static void _f_f_i(float a, int b)   {printf("a:float, b:int\n");}
static void _f_f_f(float a, float b) {printf("a:float, b:float\n");}

#define f(a, b) _Generic((a),                         \
    int:   _Generic((b), int: _f_i_i, float: _f_i_f), \
    float: _Generic((b), int: _f_f_i, float: _f_f_f))(a, b)

int main(void)
{
    f(1,   2);
    f(1,   2.f);
    f(1.f, 2);
    f(1.f, 2.f);
    return 0;
}

/* HACK: the re-casting of the pointers is a dirty but useful hack which is
         needed to set the assignment-expression to a function call instead of
         the function name itself. If re-casting is not added, the code will
         also work, however the compiler will generate 2 warnings.
         more info: http://stackoverflow.com/questions/24743520 */
#define func(o, ...) _Generic((o),                 \
        char : func_char((char)o, ## __VA_ARGS__), \
        bool : func_bool((bool)o, ## __VA_ARGS__), \
        float: func_float((float)o, ## __VA_ARGS__))

/*  drawbacks[1]: macro(((cast){1, 2, 3}))
                       ^
               extra parenthesis
    drawbacks[2]: one has to write/exzend the interface header
                 if one wants to use the same generic macro
    drawbacks[3]: -std=c11

    advantage: OOP => instance.method(args...)
                                     ^
                 instance passed implicitly as first argument

              before: object_method(instance, args...)
                        ^              ^
          name space is token name   instance passed explicitly

              now: method(instance, args...)
                      ^
              method decides which object's method to use */
