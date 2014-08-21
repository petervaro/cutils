/* Include standard */
#include <stdio.h>
#include <stdlib.h>

/* Include cutils */
#define CEXC_SET
#include <cutils/call.h>

/* Include locals */
#include "local_file.h"

/* Purposeless macros */
#define formatter(...) #__VA_ARGS__
#define stringify(...) formatter(__VA_ARGS__)

/* Base type */
typedef struct
{
    DynamicArray_int     *array;
    SinglyLinkedList_int *list;
} DataStructures;


int main(void)
{
    start_exception_handling(stderr);

    DataStructures *data = malloc(sizeof(DataStructures));
    if (!data)
    {
        fprintf(stderr, "Allocation failed\n");
        exit(EXIT_FAILURE);
    }

    bool check = new(&(data->array), 4, ((int[]){45, 99, 23, 81}));
    catch();
    if (!check)
        exit(EXIT_FAILURE);

    append(data->array, &(int){78});
    print(data->array);

    check = new(&data->list, len(data->array), raw(data->array));
    catch();
    if (!check)
        exit(EXIT_FAILURE);

    append(data->list, 2, ((int[]){51, 37}));
    print(data->list);

    size_t length = len(data->list) - len(data->array);
    int numbers[length];

    sub(data->list, len(data->array), length, numbers);
    catch();

    append(data->array, length, numbers);
    print(data->array);

    del(data->array);
    del(data->list);
    free(data);

    stop_exception_handling();

    // Print out this random thing
    fprintf(stdout, "%s\n", stringify(NULL, 0, 1u, 2ul, 3ull, 4.f, u"end"));
    return 0;
}
