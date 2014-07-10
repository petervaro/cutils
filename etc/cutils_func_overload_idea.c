/* INFO ************************************************************************
**                                                                            **
**                                   cutils                                   **
**                                   ======                                   **
**                                                                            **
**                     Modern and Lightweight C Utilities                     **
**                       Version: 0.8.72.258 (20140709)                       **
**                                                                            **
**                   File: etc/cutils_func_overload_idea.c                    **
**                                                                            **
**           Designed and written by Peter Varo. Copyright (c) 2014           **
**             License agreement is provided in the LICENSE file              **
**                 For more info visit: http://www.cutils.org                 **
**                                                                            **
************************************************************************ INFO */

#include <stdio.h>   /* printf() */

typedef struct {} Alpha;
typedef struct {} Beta;
typedef struct {} Gamma;
typedef struct {} Delta;

void new_alpha(Alpha *a, int b){printf("I'm an Alpha!\n");}
void new_beta(Beta *b, void *v){printf("I'm a Beta!\n");}
void new_gamma(Gamma *g){printf("I'm a Gamma!\n");}
void new_delta(Delta *d){printf("I'm a Delta!\n");}

#define new2(arg1, arg2) _Generic((arg1),  \
    Alpha*: new_alpha,                     \
    Beta* : new_beta)(arg1, arg2)

#define new1(arg1) _Generic((arg1),        \
    Gamma*: new_gamma,                     \
    Delta*: new_delta)(arg1)

#define GET_MACRO_BY_ARG_COUNT(_1, _2, MACRO_NAME, ...) MACRO_NAME
#define new(...) GET_MACRO_BY_ARG_COUNT(__VA_ARGS__, new2, new1)(__VA_ARGS__)


int main(void)
{
    Alpha *alpha = NULL;
    Beta  *beta  = NULL;
    Gamma *gamma = NULL;
    Delta *delta = NULL;

    int i = 0;

    new(alpha, i);
    new(beta, &i);
    new(gamma);
    new(delta);

    return 0;
}
