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
