
#ifndef _DYNAMIC_ARRAY_VOID_POINTER_H_
#define _DYNAMIC_ARRAY_VOID_POINTER_H_

#include <stdio.h>    // size_t, printf()
#include <stdbool.h>  // bool

/*
 * Usage:
 * ======
 *
 * Define an empty integer DynamicArray:
 *      DynamicArray *dar = dar_init(0, sizeof(int), NULL);
 *
 * Define integer DynamicArray:
 *      DynamicArray *dar = dar_init(4, sizeof(int), (int[]){0, 1, 2, 3});
 *
 * Append integer DynamicArray dar with values:
 *      dar_append(dar, 2, (int[]){4, 5})
 *
 * Get the actual array data from an integer DynamicArray:
 *      int *data = (int *)dar_data(dar);
 *
 * Get the actual data and other informations from
 * an integer DynamicArray with a single call:
 *      size_t size, length;
 *      int *data = (int *)dar_alldata(dar, &size, &length);
 *
 * Get a pointer to the fourth item in an integer DynamicArray:
 *      int *item = (int *)dar_get(dar, 3);
 */

// TODO: universal functions for all cutils data structures:
//       new()
//       del()
//       data() -> alldata
//       raw() -> data
//       len()
//       size()
//       clear()
//       scale() -> resize
//       swap()
//       reverse()
//       add() -> append
//       push() -> insert
//       rem() -> remove
//       pop()
//       trunc() -> truncate
//       set() -> replace
//       get()
//       sub()
//       swapsub()
//       reversesub()
//       find()
//       findall()
//       sort()
//       print() -> printf
//
// copy:
//     new(&darf2, len(darf1), raw(darf1));

/*
#define at(dar_ptr, index, data_ptr) get(dar_ptr, index, 1, data_ptr)
#define pop(dar_ptr, data_ptr) pull(dar_ptr, len(dar_ptr) - 1, 1, data_ptr)
#define append(dar_ptr, data_ptr) push(data_ptr, len(dar_ptr) - 1, 1, data_ptr)
*/


/*----------------------------------------------------------------------------*/
/*
 * Exception handling of cutils is already included, here is how to activate it:
 *
 *    1) place 'cexc.h' header file next to the source file (cdar.c)
 *    2) compile source file with '-DCEXC_USE' flag
 *    3) call start_exception_handling(ptr) before using array
 *    4) call stop_exception_handling() after array used
 *
 * For exception handling's logging-mode use the '-DCEXC_LOG' compiler flag.
 */

/*----------------------------------------------------------------------------*/
// DynamicArray object type. DynamicArray stores items by their values, not only
// by pointer to them, so all data passed to it with the following methods are
// going to be copied into the array. (Example: if the array is an integer type
// it will save a copy of the integer itself inside itself. If the array is a
// a pointer type, then all the pointers will be copied into the array, pointing
// at the same memory location as the original pointers)
typedef struct {} DynamicArray;

/*----------------------------------------------------------------------------*/
// Initialisation: returns 1 on success
//                 on error: 0
extern bool
darv_new(DynamicArray **dar,
         size_t count,
         void *data);

/*----------------------------------------------------------------------------*/
// Deletion: deletes both the DynamicArray and the data stored in it
extern void
darv_del(DynamicArray *dar);

/*----------------------------------------------------------------------------*/
// Get All Data: returns the direct pointer to the actual array containing data
//               size: returns the full size of all elements in the array (used)
//               count: returns the number of elements in the array (used)
extern void *
darv_data(DynamicArray *dar,
             size_t *size,
             size_t *count);

/*----------------------------------------------------------------------------*/
// Get Data Only: returns the direct pointer to the actual array containing data
extern void *
darv_raw(DynamicArray *dar);

/*----------------------------------------------------------------------------*/
// Length: returns number of items in DynamicArray (used)
extern size_t
darv_len(DynamicArray *dar);

/*----------------------------------------------------------------------------*/
// Array Size: returns the size of the data stored in DynamicArray (used)
extern size_t
darv_size(DynamicArray *dar);

/*----------------------------------------------------------------------------*/
// Resize: forces array to being allocated with a given size. If the given size
//         is lesser than the current size of the array, the array will be
//         truncated.
//         if cexc.h included: raises exception if reallocation failed
extern bool
darv_resize(DynamicArray *dar,
            size_t count);

/*----------------------------------------------------------------------------*/
// Swapping: swaps two items at given indices
//           returns: 1 if succeded else 0
//           if cexc.h included: raises exception if index is out of range
extern bool
darv_swap(DynamicArray *dar,
          size_t index1,
          size_t index2,
          size_t count);

/*----------------------------------------------------------------------------*/
// Reverse: reverses array items
//          returns: 1 if succeded else 0
//          if cexc.h included: raises exception if array is empty
extern bool
darv_reverse(DynamicArray *dar);

/*----------------------------------------------------------------------------*/
// Append: appends count number of data from array to DynamicArray
//         returns 1 if succeded else 0
//         if cexc.h included: raises exception if reallocation failed
extern bool
darv_append(DynamicArray *dar,
            size_t count,
            void *data);

/*----------------------------------------------------------------------------*/
// Insert: inserts count number of data from array to DynamicArray at index. If
//         index is greater than last used index + 1, the data will be be
//         appended at the end of the array.
//         returns: 1 if succeded else 0
//         if cexc.h included: raises exception if reallocation failed
extern bool
darv_insert(DynamicArray *dar,
            size_t index,
            size_t count,
            void *data);

/*----------------------------------------------------------------------------*/
// Remove: removes count number of data from DynamicArray started from index
//         returns: number of items removed
//         if cexc.h included: raises exception if index is out of range
extern size_t
darv_remove(DynamicArray *dar,
            size_t index,
            size_t count);

/*----------------------------------------------------------------------------*/
// Pop: pops out count number of data starts at index and copies to destination
//      returns the number of items popped out
//      if cexc.h included: raises error if destination is NULL
//                          raises error if array is empty
//                          raises error if index is out of range
extern size_t
darv_pop(DynamicArray *dar,
         size_t index,
         size_t count,
         void *destination);

/*----------------------------------------------------------------------------*/
// Sub data: copies count number of sub data to destination started from index
//           returns: the number of items copied
//           if cexc.h included: raises
extern size_t
darv_sub(DynamicArray *dynarr,
         size_t index,
         size_t count,
         void *destination);

/*----------------------------------------------------------------------------*/
// Truncate: removes all items starts from index to the end
//           if cexc.h included: raises exception if index out of range
extern void
darv_truncate(DynamicArray *dar,
              size_t index);

/*----------------------------------------------------------------------------*/
// Replace: reassign count number of data from array to DynamicArray from index
//          if cexc.h included: raises exception if index is out of range
extern bool
darv_set(DynamicArray *dar,
         size_t index,
         size_t count,
         void *data);

/*----------------------------------------------------------------------------*/
// Get Item: returns a pointer to the item in a DynamicArray at a given index
//           if array is empty, or index out of range it is undefined behaviour,
//           the return values can be memory garbage.
//           if cexc.h included: raises exception if array is empty also
//                               raises exception if index out of range
extern void *
darv_get(DynamicArray *dar,
         size_t index);

/*----------------------------------------------------------------------------*/
// Find Item: search array for item, if found writes first index to index
//            returns: true if found else false (can be used as an 'isin' func)
extern bool
darv_find(DynamicArray *dar,
          const void *item,
          size_t *index);

/*----------------------------------------------------------------------------*/
// Find All: search array for all appereances of item in array and write the
//           index to indices if found any
//           returns: the number of appereances found
extern size_t
darv_findall(DynamicArray *dynarr,
             const void *item,
             size_t *indices);

/*----------------------------------------------------------------------------*/
extern void
darv_sort(DynamicArray *dar,
          int (*compare)(const void*, const void*));

/*----------------------------------------------------------------------------*/
extern void
darv_sortsub(DynamicArray *dar,
             size_t index,
             size_t count,
             int (*compare)(const void *, const void*));

/*----------------------------------------------------------------------------*/
// Clear: clears content of DynamicArray
extern void
darv_clear(DynamicArray *dar);

/*----------------------------------------------------------------------------*/
// Pretty print:
extern void
darv_print(DynamicArray *dar);

/*----------------------------------------------------------------------------*/
// DON'T USE THIS METHOD DIRECTLY UNLESS YOU KNOW EXACTLY WHAT YOU ARE DOING!
// This is the type-generic initialiser for DynamicArrays.
extern bool
dartg_new(DynamicArray **dar,
          size_t count,
          size_t item_size,
          void *data);

/*----------------------------------------------------------------------------*/
// DON'T USE THIS MACRO DIRECTLY UNLESS YOU KNOW EXACTLY WHAT YOU ARE DOING!
// This is the type generic pretty print method of DynamicArray
#define dartg_print(dar, type, repr, fmt)                                      \
    do {                                                                       \
        type *__dar_tmp_data__ = (type *)darv_raw(dar);                        \
        if (!darv_len(dar))                                                    \
        {                                                                      \
            printf("DynamicArray" repr " {}\n");                               \
            break;                                                             \
        }                                                                      \
        printf("DynamicArray" repr "\n{\n");                                   \
        for (size_t i=0; i<darv_len(dar); i++)                                 \
            printf("    [%zu] " fmt "\n", i, *(__dar_tmp_data__ + i));         \
        printf("}\n");                                                         \
    } while (0)

/*----------------------------------------------------------------------------*/
// DON'T USE THIS MACRO DIRECTLY UNLESS YOU KNOW EXACTLY WHAT YOU ARE DOING!
// This is the custom, user defined pretty print method of DynamicArray
#define dartg_printcb(dar, callback)                                           \
    do {                                                                       \
        char **__dar_tmp_data__ = (char **)darv_raw(dar);                      \
        if (!darv_len(dar))                                                    \
        {                                                                      \
            printf("DynamicArray_void {}\n");                                  \
            break;                                                             \
        }                                                                      \
        printf("DynamicArray_void\n{\n");                                      \
        for (size_t i=0; i<darv_len(dar); i++)                                 \
            callback(i, *(void **)(__dar_tmp_data__ + i));                     \
        printf("}\n");                                                         \
    } while (0)
#endif
