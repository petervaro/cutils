
#include <stdlib.h>
#include <jemalloc/jemalloc.h>  // malloc(), realloc(), free()

#include <stdio.h>    // fprintf(), stderr, size_t
#include <string.h>   // memcpy(), strcpy(), strcat()


#ifdef usecexc
  #ifdef offcexc
    #define CEXC_OFF
  #endif
  #ifdef logcexc
    #define CEXC_LOG
  #endif
  #include "cexc.h"
#else
  #define raise(msg, len)
#endif


/*----------------------------------------------------------------------------*/
// Base type
typedef struct
{
    size_t allocated;  /* Number of buckets allocated */
    size_t used;       /* Number of buckets has been used */
    size_t size;       /* Size of an item */
    void *data;        /* Pointer to the actual data */

} DynamicArray;


/*----------------------------------------------------------------------------*/
int
_dynarr_resize(DynamicArray *dynarr,
                size_t item_size,
                size_t item_count)
{
    // If free space is greater than the space
    // required by the the array extend with
    if (dynarr->allocated - dynarr->used < item_count)
    {
        // Calculate new size (double it)
        size_t newsize = dynarr->allocated;
        while (newsize < dynarr->used + item_count) newsize *= 2;
        // Resize array
        void *data = realloc(dynarr->data, newsize*item_size);
        if (!data) return 0;
        dynarr->data = data;
        dynarr->allocated = newsize;
    }
    return 1;
}


/*----------------------------------------------------------------------------*/
int
dynarr_append(DynamicArray *dynarr,
              size_t count,
              void *array)
{
    if ((0 < count) && array)
    {
        // Resize array if necessary
        size_t item_size = dynarr->size;
        if (!_dynarr_resize(dynarr, item_size, count))
        {
#undef  excmsg
#define excmsg "DynamicArray, append: reallocation failed"
            raise(excmsg, sizeof(excmsg));
#undef  excmsg
            return 0;
        }
        // Extend Dynamic Array
        memcpy((char *)dynarr->data + dynarr->used*item_size,
                array,
                item_size*count);
        // Update usage data
        dynarr->used += count;
    }
    return 1;
}


/*----------------------------------------------------------------------------*/
DynamicArray *
dynarr_init(size_t count,
            size_t item_size,
            void *array)
{
    // Error print conditional
    char errfrom_struct = 0;

    // Calculate allocation size based on item count
    size_t alloc_size = count ? 2 * count : 1;

    // Allocate space for array data
    void *data = malloc(alloc_size * item_size);
    if (!data) goto Error_Array_Allocation_Failed;

    // Allocate space for struct
    DynamicArray *dynarr = malloc(sizeof(DynamicArray));
    if (!dynarr) goto Error_Struct_Allocation_Failed;

    // Fill struct with values
    dynarr->allocated = alloc_size;
    dynarr->used = 0;
    dynarr->data = data;
    dynarr->size = item_size;

    // Extend it with the provided array
    dynarr_append(dynarr, count, array);

    // If everything went fine,
    // return the new DynamicArray
    return dynarr;

    /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    // If some error occurred:
    Error_Struct_Allocation_Failed:
        fprintf(stderr, "Failed to allocate space"
                        "for DynamicArray's struct\n");
        errfrom_struct++;
        free(data);

    /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    Error_Array_Allocation_Failed:
        if(!errfrom_struct)
            fprintf(stderr, "Failed to allocate space"
                            "for DynamicArray's array\n");
        return (void *)NULL;
}


/*----------------------------------------------------------------------------*/
void
dynarr_del(DynamicArray *dynarr)
{
    free(dynarr->data);
    free(dynarr);
}


/*----------------------------------------------------------------------------*/
void *
dynarr_alldata(DynamicArray *dynarr,
               size_t *size,
               size_t *count)
{
    *size  = dynarr->used*dynarr->size;
    *count = dynarr->used;
    return dynarr->data;
}

/*----------------------------------------------------------------------------*/
void *
dynarr_data(DynamicArray *dynarr)
{
    return dynarr->data;
}


/*----------------------------------------------------------------------------*/
size_t
dynarr_len(DynamicArray *dynarr)
{
    return dynarr->used;
}


/*----------------------------------------------------------------------------*/
size_t
dynarr_size(DynamicArray *dynarr)
{
    return dynarr->used*dynarr->size;
}


/*----------------------------------------------------------------------------*/
void
dynarr_clear(DynamicArray *dynarr)
{
    dynarr->used = 0;
}


/*----------------------------------------------------------------------------*/
void
dynarr_swap(DynamicArray *dynarr,
            size_t index1,
            size_t index2)
{
    if (index1 != index2)
    {
        if ((0 > (int)index1) || (index1 >= dynarr->used) ||
            (0 > (int)index2) || (index2 >= dynarr->used))
        {
#define excmsg "DynamicArray, swap: index out of range"
            raise(excmsg, sizeof(excmsg));
#undef  excmsg
            return;
        }
        // Get/cast essential values
        size_t item_size = dynarr->size;
        char *data  = (char *)dynarr->data;
        char *item1 = data + index1*item_size;
        char *item2 = data + index2*item_size;
        char *temp  = malloc(item_size);
        // Swap elements
        memcpy(temp,  item1, item_size);
        memcpy(item1, item2, item_size);
        memcpy(item2, temp,  item_size);
        // Cleanup
        free(temp);
    }
}


/*----------------------------------------------------------------------------*/
int
dynarr_insert(DynamicArray *dynarr,
              size_t index,
              size_t count,
              void *array)
{
    if ((0 < count) && array)
    {
        if ((0 > (int)index) || (index >= dynarr->used))
        {
#define excmsg "DynamicArray, insert: index out of range"
            raise(excmsg, sizeof(excmsg));
#undef  excmsg
            return 0;
        }
        // Resize array if necessary
        size_t item_size = dynarr->size;
        if (!_dynarr_resize(dynarr, item_size, count))
        {
#define excmsg "DynamicArray, insert: reallocation failed"
            raise(excmsg, sizeof(excmsg));
#undef  excmsg
            return 0;
        }
        char *data = (char *)dynarr->data;
        // Shift original data
        if (dynarr->used)
        {
            for (int i=dynarr->used - 1; i >= index; i--)
                memcpy(data + (i + count)*item_size, data + i*item_size, item_size);
        }
        // Insert new data
        memcpy(data + index*item_size, array, item_size*count);
        // Update usage data
        dynarr->used += count;
    }
    return 1;
}


/*----------------------------------------------------------------------------*/
void
dynarr_remove(DynamicArray *dynarr,
              size_t index,
              size_t count)
{
    if (0 < count)
    {
        if ((0 > (int)index) || (index >= dynarr->used))
        {
#define excmsg "DynamicArray, remove: index out of range"
            raise(excmsg, sizeof(excmsg));
#undef  excmsg
            return;
        }
        size_t item_size = dynarr->size;
        char *data = (char *)dynarr->data;
        // Shift data
        for (int i=index; i<index + count; i++)
            memcpy(data + i*item_size, data + (i + count)*item_size, item_size);
        // Update usage data
        dynarr->used -= count;
    }
}


/*----------------------------------------------------------------------------*/
void
dynarr_replace(DynamicArray *dynarr,
               size_t index,
               size_t count,
               void *array)
{
    if ((0 < count) && array)
    {
        if ((0 > (int)index) || (index >= dynarr->used))
        {
#define excmsg "DynamicArray, replace: index out of range"
            raise(excmsg, sizeof(excmsg));
#undef  excmsg
            return;
        }
        size_t item_size = dynarr->size;
        size_t max_count = dynarr->used - (index + 1);
        char *data = (char *)dynarr->data;
        memcpy(data + index*item_size, array, (max_count >= count)
                                              ? count*item_size
                                              : max_count);
    }
}


/*----------------------------------------------------------------------------*/
void *
dynarr_get(DynamicArray *dynarr,
           size_t index)
{
    if ((0 > (int)index) || (index >= dynarr->used))
        return (void *)NULL;
    return (char *)dynarr->data + dynarr->size * index;
}
