
#ifndef _DYNAMIC_ARRAY_C_
#define _DYNAMIC_ARRAY_C_

#include <stdio.h>  // size_t

#ifdef offcexc
  #define CEXC_OFF
#endif
#ifdef logcexc
  #define CEXC_LOG
#endif
#ifdef usecexc
  #include "cexc.h"
#endif

/*
 * Usage:
 * ======
 *
 * Define an empty integer DynamicArray:
 *      DynamicArray *dynarr = dynarr_init(0, sizeof(int), NULL);
 *
 * Define integer DynamicArray:
 *      DynamicArray *dynarr = dynarr_init(4, sizeof(int), (int[]){0, 1, 2, 3});
 *
 * Append integer DynamicArray dynarr with values:
 *      dynarr_append(dynarr, 2, (int[]){4, 5})
 *
 * Get the actual array data from an integer DynamicArray:
 *      int *data = (int *)dynarr_data(dynarr);
 *
 * Get the actual data and other informations from
 * an integer DynamicArray with a single call:
 *      size_t size, length;
 *      int *data = (int *)dynarr_alldata(dynarr, &size, &length);
 *
 * Get a pointer to the fourth item in an integer DynamicArray:
 *      int *item = (int *)dynarr_get(dynarr, 3);
 */

/*----------------------------------------------------------------------------*/
// DynamicArray type. DynamicArray stores item by value, not by pointer, so all
// starting, appended, inserted and replaced values are copied into it.
typedef struct {} DynamicArray;

/*----------------------------------------------------------------------------*/
// Initialisation: returns a pointer to the newly created DynamicArray
//                 on error: returns a NULL pointer
DynamicArray *
dynarr_init(size_t count,
            size_t item_size,
            void *array);

/*----------------------------------------------------------------------------*/
// Deletion: deletes both the DynamicArray and the data stored in it
void
dynarr_del(DynamicArray *dynarr);

/*----------------------------------------------------------------------------*/
// Get All Data: returns the direct pointer to the actual array containing data
//               size: returns the full size of all elements in the array (used)
//               count: returns the number of elements in the array (used)
void *
dynarr_alldata(DynamicArray *dynarr,
               size_t *size,
               size_t *count);

/*----------------------------------------------------------------------------*/
// Get Data Only: returns the direct pointer to the actual array containing data
void *
dynarr_data(DynamicArray *dynarr);

/*----------------------------------------------------------------------------*/
// Length: returns number of items in DynamicArray (used)
size_t
dynarr_len(DynamicArray *dynarr);

/*----------------------------------------------------------------------------*/
// Array Size: returns the size of the data stored in DynamicArray (used)
size_t
dynarr_size(DynamicArray *dynarr);

/*----------------------------------------------------------------------------*/
// Swapping: swaps two items at given indices
//           if cexc.h included: raises exception if index is out of range
void
dynarr_swap(DynamicArray *dynarr,
            size_t index1,
            size_t index2);

/*----------------------------------------------------------------------------*/
// Append: appends count number of data from array to DynamicArray
//         returns 1 if succeded else 0
//         if cexc.h included: raises exception if reallocation failed
int
dynarr_append(DynamicArray *dynarr,
              size_t count,
              void *array);

/*----------------------------------------------------------------------------*/
// Insert: inserts count number of data from array to DynamicArray at index
//         returns 1 if succeded else 0
//         if cexc.h included: raises exception if index is out of range
//                             raises exception if reallocation failed
int
dynarr_insert(DynamicArray *dynarr,
              size_t index,
              size_t count,
              void *array);

/*----------------------------------------------------------------------------*/
// Remove: removes count number of data from DynamicArray started from index
//         if cexc.h included: raises exception if index is out of range
void
dynarr_remove(DynamicArray *dynarr,
              size_t index,
              size_t count);

/*----------------------------------------------------------------------------*/
// Replace: reassign count number of data from array to DynamicArray from index
//          if cexc.h included: raises exception if index is out of range
void
dynarr_replace(DynamicArray *dynarr,
               size_t index,
               size_t count,
               void *array);

/*----------------------------------------------------------------------------*/
// Get Item: returns a pointer to the item in DynamicArray at a given index
//           returns NULL pointer if index is out of range
void *
dynarr_get(DynamicArray *dynarr,
           size_t index);

/*----------------------------------------------------------------------------*/
// Clear: clears content of DynamicArray
void
dynarr_clear(DynamicArray *dynarr);

/*----------------------------------------------------------------------------*/
// Pretty print of DynamicArray
#define dynarr_printf(dynarr, type, fmt)                                       \
    do {                                                                       \
        type *__dynarr_data = (type *)dynarr_data(dynarr);                     \
        printf("DynamicArray\n{\n");                                           \
        for (int i=0; i<dynarr_len(dynarr); i++)                               \
            printf("    [%d] " fmt "\n", i, *(__dynarr_data + i));             \
        printf("}\n");                                                         \
    } while (0)

#endif
