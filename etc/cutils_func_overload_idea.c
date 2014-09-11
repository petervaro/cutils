/* INFO ************************************************************************
**                                                                            **
**                                   cutils                                   **
**                                   ======                                   **
**                                                                            **
**                     Modern and Lightweight C Utilities                     **
**                       Version: 0.8.72.365 (20140711)                       **
**                                                                            **
**                   File: etc/cutils_func_overload_idea.c                    **
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
