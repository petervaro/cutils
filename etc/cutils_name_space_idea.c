/* INFO ************************************************************************
**                                                                            **
**                                   cutils                                   **
**                                   ======                                   **
**                                                                            **
**                     Modern and Lightweight C Utilities                     **
**                       Version: 0.8.72.365 (20140711)                       **
**                                                                            **
**                     File: etc/cutils_name_space_idea.c                     **
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

/*--- helloworld.h -----------------------------------------------------------*/
typedef struct
{
    void (*print)(int);
    int  (*add)(int, int);

} NameSpace_HelloWorld;

extern NameSpace_HelloWorld helloworld;

extern void
import_helloworld(void);



/*--- helloworld.c -----------------------------------------------------------*/
#include <stdio.h>

typedef struct
{
    void (*print)(int);
    int  (*add)(int, int);

} NameSpace_HelloWorld;

NameSpace_HelloWorld helloworld = {0};

static void
print(int x)
{
    printf("%d\n", x);
}

static int
add(int a, int b)
{
    return a + b;
}

void
import_helloworld(void)
{
    helloworld.print = print;
    helloworld.add   = add;
}



/*--- main.c -----------------------------------------------------------------*/
#include "helloworld.h"

int main(void)
{
    import_helloworld();

    int result,
        x = 10,
        y = 23;

    result = helloworld.add(x, y);
    helloworld.print(result);
    return 0;
}



/*--- OUTPUT -----------------------------------------------------------------*/
33
