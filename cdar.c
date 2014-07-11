/* INFO ************************************************************************
**                                                                            **
**                                   cutils                                   **
**                                   ======                                   **
**                                                                            **
**                     Modern and Lightweight C Utilities                     **
**                       Version: 0.8.72.365 (20140711)                       **
**                                                                            **
**                                File: cdar.c                                **
**                                                                            **
**           Designed and written by Peter Varo. Copyright (c) 2014           **
**             License agreement is provided in the LICENSE file              **
**                 For more info visit: http://www.cutils.org                 **
**                                                                            **
************************************************************************ INFO */

#include <stddef.h>   /* ptrdiff_t */
#include <stdlib.h>   /* malloc(), realloc(), free() */
#ifdef CDAR_JEM
  #include <jemalloc/jemalloc.h>  /* malloc(), realloc(), free() */
#endif

#include <stdio.h>    /* fprintf(), stderr, size_t */
#include <string.h>   /* memcpy(), strcpy(), strcat() */
#include <stdbool.h>  /* bool, true, false */

/* If 'optimised' or the 'exceptions are not available' */
#if defined CDAR_OPT || !defined CEXC_USE
  #define raise(msg, len)
#else
  #include "cexc.h"
#endif

/*----------------------------------------------------------------------------*/
/* Exception messages */
#undef  CEXC_MSG_TYPE
#define CEXC_MSG_TYPE "DynamicArray"

#undef  CEXC_MSG_ARGUMENT_NULL
#define CEXC_MSG_ARGUMENT_NULL(func, idx, arg) \
        CEXC_MSG_TYPE ", " func ": " idx " argument '" #arg "' is NULL"

#undef  CEXC_MSG_ARGUMENT_OUTOF
#define CEXC_MSG_ARGUMENT_OUTOF(func, idx, arg) \
        CEXC_MSG_TYPE ", " func ": " idx " argument '" #arg "' is out of range"

#undef  CEXC_MSG_NOT_INIT
#define CEXC_MSG_NOT_INIT(func) \
        CEXC_MSG_TYPE ", " func ": array is not initialised"

#undef  CEXC_MSG_EMPTY
#define CEXC_MSG_EMPTY(func) \
        CEXC_MSG_TYPE ", " func ": array is empty"

#undef  CEXC_MSG_REALLOC_FAIL
#define CEXC_MSG_REALLOC_FAIL(func) \
        CEXC_MSG_TYPE ", " func ": internal reallocation failed"

#undef  CEXC_MSG_ALLOC_FAIL
#define CEXC_MSG_ALLOC_FAIL(func) \
        CEXC_MSG_TYPE ", " func ": internal allocation failed"

#undef  CEXC_MSG_OVERLAP
#define CEXC_MSG_OVERLAP(func) \
        CEXC_MSG_TYPE ", " func ": blocks are overlapping"

/* A variable to construct the exception message in */
#undef  EXCEPTION_MSG


/*----------------------------------------------------------------------------*/
/* Base type */
typedef struct
{
    size_t allocated;  /* Number of buckets allocated */
    size_t used;       /* Number of buckets has been used */
    size_t size;       /* Size of an item */
    void *data;        /* Pointer to the actual data */

} cutils_cdar_DynamicArray_void_ptr;


/*----------------------------------------------------------------------------*/
static bool
__cdar_resize(cutils_cdar_DynamicArray_void_ptr *dynarr,
              size_t item_size,
              size_t item_count)
{
    /* If free space is lesser than the space required */
    if (dynarr->allocated - dynarr->used < item_count)
    {
        /* Calculate new size (doubling strategy) */
        size_t newsize = 2 * dynarr->allocated;
        while (newsize < dynarr->used + item_count) newsize *= 2;
        /* Resize array */
        void *data = realloc(dynarr->data, newsize*item_size);
        if (!data) return false;
        dynarr->data = data;
        dynarr->allocated = newsize;
    }
    return true;
}


/*----------------------------------------------------------------------------*/
bool
cutils_cdar_DynamicArray_void_ptr_new(cutils_cdar_DynamicArray_void_ptr **dynarr,
                                      size_t count,
                                      size_t item_size,
                                      void *source)
{
    /* Calculate allocation size based on item count */
    size_t alloc_size = count ? 2 * count : 1;

    /* Allocate space for array data */
    void *data = malloc(alloc_size * item_size);
    if (!data) goto Error_Array_Allocation_Failed;

    /* Allocate space for struct */
    cutils_cdar_DynamicArray_void_ptr *_dynarr = malloc(sizeof(cutils_cdar_DynamicArray_void_ptr));
    if (!_dynarr) goto Error_Struct_Allocation_Failed;

    /* Fill struct with values */
    _dynarr->allocated = alloc_size;
    _dynarr->used = 0;
    _dynarr->data = data;
    _dynarr->size = item_size;

    /* Extend it with the provided source */
    if (source)
    {
        memcpy(_dynarr->data, source, item_size*count);
        _dynarr->used = count;
    }

    /* Assign newly created array to pointer*/
    *dynarr = _dynarr;
    /* If everything went fine, return the new DynamicArray */
    return true;

    /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /* If some error occurred: */
    Error_Struct_Allocation_Failed:
        free(data);
    /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    Error_Array_Allocation_Failed:
        #define EXCEPTION_MSG CEXC_MSG_ALLOC_FAIL("new")
        raise(EXCEPTION_MSG, sizeof(EXCEPTION_MSG));
        #undef EXCEPTION_MSG
        return false;
}


/*----------------------------------------------------------------------------*/
void
cutils_cdar_DynamicArray_void_ptr_del(cutils_cdar_DynamicArray_void_ptr *dynarr)
{
#ifndef CDAR_OPT
    /* If array initialised, free raw data too */
    if (dynarr)
#endif
        free(dynarr->data);
    free(dynarr);
}


/*----------------------------------------------------------------------------*/
void *
cutils_cdar_DynamicArray_void_ptr_data(cutils_cdar_DynamicArray_void_ptr *dynarr,
                                       size_t *size,
                                       size_t *count)
{
#ifndef CDAR_OPT
    /* Not initialised */
    if (!dynarr)
    {
        #define EXCEPTION_MSG CEXC_MSG_NOT_INIT("data")
        raise(EXCEPTION_MSG, sizeof(EXCEPTION_MSG));
        #undef EXCEPTION_MSG
        return NULL; /* Cannot operate on nothing */
    }
    /* Invalid size */
    if (!size)
        #define EXCEPTION_MSG CEXC_MSG_ARGUMENT_NULL("data", "2nd", size)
        raise(EXCEPTION_MSG, sizeof(EXCEPTION_MSG));
        #undef EXCEPTION_MSG
    else
#endif /* CDAR_OPT */

    /* CORE FUNCTIONALITY */
    *size = dynarr->used*dynarr->size;

#ifndef CDAR_OPT
    /* Invalid count */
    if (!count)
        #define EXCEPTION_MSG CEXC_MSG_ARGUMENT_NULL("data", "3rd", count)
        raise(EXCEPTION_MSG, sizeof(EXCEPTION_MSG));
        #undef EXCEPTION_MSG
    else
#endif /* CDAR_OPT */

    /* CORE FUNCTIONALITY */
    *count = dynarr->used;
    return dynarr->data;
}


/*----------------------------------------------------------------------------*/
void *
cutils_cdar_DynamicArray_void_ptr_raw(cutils_cdar_DynamicArray_void_ptr *dynarr)
{
#ifndef CDAR_OPT
    /* Not initialised */
    if (!dynarr)
    {
        #define EXCEPTION_MSG CEXC_MSG_NOT_INIT("raw")
        raise(EXCEPTION_MSG, sizeof(EXCEPTION_MSG));
        #undef EXCEPTION_MSG
        return NULL; /* Cannot operate on nothing */
    }
#endif /* CDAR_OPT */

    /* CORE FUNCTIONALITY */
    return dynarr->data;
}


/*----------------------------------------------------------------------------*/
size_t
cutils_cdar_DynamicArray_void_ptr_len(cutils_cdar_DynamicArray_void_ptr *dynarr)
{
#ifndef CDAR_OPT
    /* Not initialised */
    if (!dynarr)
    {
        #define EXCEPTION_MSG CEXC_MSG_NOT_INIT("len")
        raise(EXCEPTION_MSG, sizeof(EXCEPTION_MSG));
        #undef EXCEPTION_MSG
        return 0; /* Cannot operate on nothing */
    }
#endif /* CDAR_OPT */

    /* CORE FUNCTIONALITY */
    return dynarr->used;
}


/*----------------------------------------------------------------------------*/
size_t
cutils_cdar_DynamicArray_void_ptr_size(cutils_cdar_DynamicArray_void_ptr *dynarr)
{
#ifndef CDAR_OPT
    /* Not initialised */
    if (!dynarr)
    {
        #define EXCEPTION_MSG CEXC_MSG_NOT_INIT("size")
        raise(EXCEPTION_MSG, sizeof(EXCEPTION_MSG));
        #undef EXCEPTION_MSG
        return 0; /* Cannot operate on nothing */
    }
#endif /* CDAR_OPT */

    /* CORE FUNCTIONALITY */
    return dynarr->used*dynarr->size;
}


/*----------------------------------------------------------------------------*/
void
cutils_cdar_DynamicArray_void_ptr_clear(cutils_cdar_DynamicArray_void_ptr *dynarr)
{
#ifdef CDAR_OPT
    /* Not initialised */
    if (!dynarr)
    {
        #define EXCEPTION_MSG CEXC_MSG_NOT_INIT("clear")
        raise(EXCEPTION_MSG, sizeof(EXCEPTION_MSG));
        #undef EXCEPTION_MSG
        return; /* Cannot operate on nothing */
    }
#endif /* CDAR_OPT */

    /* CORE FUNCTIONALITY */
    dynarr->used = 0;
}


/*----------------------------------------------------------------------------*/
bool
cutils_cdar_DynamicArray_void_ptr_resize(cutils_cdar_DynamicArray_void_ptr *dynarr,
                                         size_t count)
{
#ifndef CDAR_OPT
    /* Not initialised */
    if (!dynarr)
    {
        #define EXCEPTION_MSG CEXC_MSG_NOT_INIT("resize")
        raise(EXCEPTION_MSG, sizeof(EXCEPTION_MSG));
        #undef EXCEPTION_MSG
        return false; /* Cannot operate on nothing */
    }
    else
#endif /* CDAR_OPT */

    /* CORE FUNCTIONALITY */
    /* Make it smaller */
    if (count < dynarr->used)
    {
        dynarr->used = count;
        return true; /* Successfully truncated */
    }
    /* Make it bigger */
    if (!__cdar_resize(dynarr, dynarr->size, count))
    {
        #define EXCEPTION_MSG CEXC_MSG_REALLOC_FAIL("resize")
        raise(EXCEPTION_MSG, sizeof(EXCEPTION_MSG));
        #undef EXCEPTION_MSG
        return false; /* No place to grow */
    }
    return true; /* Successfully grew */
}


/*----------------------------------------------------------------------------*/
bool
cutils_cdar_DynamicArray_void_ptr_swap(cutils_cdar_DynamicArray_void_ptr *dynarr,
                                       size_t index1,
                                       size_t index2,
                                       size_t count)
{
#ifndef CDAR_OPT
    /* Not initialised */
    if (!dynarr)
    {
        #define EXCEPTION_MSG CEXC_MSG_NOT_INIT("swap")
        raise(EXCEPTION_MSG, sizeof(EXCEPTION_MSG));
        #undef EXCEPTION_MSG
        return false; /* Cannot operate on nothing */
    }
    else
#endif /* CDAR_OPT */
    /* No swapping needed */
    if ((index1 == index2) || !count)
    {
        return true; /* Successfully did nothing */
    }
    /* Empty array */
    else if (!dynarr->used)
    {
        #define EXCEPTION_MSG CEXC_MSG_EMPTY("swap")
        raise(EXCEPTION_MSG, sizeof(EXCEPTION_MSG));
        #undef EXCEPTION_MSG
        return true; /* Successfully did nothing */
    }
#ifndef CDAR_OPT
    /* Out of range */
    else if (index1 >= dynarr->used)
    {
        #define EXCEPTION_MSG CEXC_MSG_ARGUMENT_OUTOF("swap", "2nd", index1)
        raise(EXCEPTION_MSG, sizeof(EXCEPTION_MSG));
        #undef EXCEPTION_MSG
        return false; /* Not valid index */
    }
    /* Out of range */
    else if (index2 >= dynarr->used)
    {
        #define EXCEPTION_MSG CEXC_MSG_ARGUMENT_OUTOF("swap", "3rd", index2)
        raise(EXCEPTION_MSG, sizeof(EXCEPTION_MSG));
        #undef EXCEPTION_MSG
        return false; /* Not valid index */
    }

    /* Sort indices */
    size_t greater, smaller;
    if (index1 > index2) { greater = index1; smaller = index2; }
    else                 { greater = index2; smaller = index1; }

    /* Limit count size, if overlapping */
    if (smaller + count >= greater)
    {
        #define EXCEPTION_MSG CEXC_MSG_OVERLAP("swap")
        raise(EXCEPTION_MSG, sizeof(EXCEPTION_MSG));
        #undef EXCEPTION_MSG
        count = greater - smaller;
    }

    /* Limit count size, if out of range */
    if ((greater + count) > dynarr->used)
    {
        #define EXCEPTION_MSG CEXC_MSG_ARGUMENT_OUTOF("swap", "4th", count)
        raise(EXCEPTION_MSG, sizeof(EXCEPTION_MSG));
        #undef EXCEPTION_MSG
        count = dynarr->used - greater;
        if (!count) return true; /* Successfully did nothing */
    }
#endif /* CDAR_OPT */

    /* CORE FUNCTIONALITY
       Create/get/cast essential values */
    size_t item_size  = dynarr->size,
           block_size = item_size*count;
    char *data  = (char *)dynarr->data,
         *item1 = data + index1*item_size,
         *item2 = data + index2*item_size,
         *temp  = malloc(block_size);
    if (!temp)
    {
        #define EXCEPTION_MSG CEXC_MSG_ALLOC_FAIL("swap")
        raise(EXCEPTION_MSG, sizeof(EXCEPTION_MSG));
        #undef EXCEPTION_MSG
        return false; /* No place to store variable */
    }

    /* Swap elements */
    memcpy(temp,  item1, block_size);
    memcpy(item1, item2, block_size);
    memcpy(item2, temp,  block_size);

    /* Cleanup */
    free(temp);
    return true; /* Successfully swapped items */
}


/*----------------------------------------------------------------------------*/
bool
cutils_cdar_DynamicArray_void_ptr_reverse(cutils_cdar_DynamicArray_void_ptr *dynarr)
{
    size_t length;
#ifndef CDAR_OPT
    if (!dynarr)
    {
        #define EXCEPTION_MSG CEXC_MSG_NOT_INIT("reverse")
        raise(EXCEPTION_MSG, sizeof(EXCEPTION_MSG));
        #undef EXCEPTION_MSG
        return false; /* Cannot operate on nothing */
    }
    else
#endif /* CDAR_OPT */
    if (!(length = dynarr->used))
    {
        #define EXCEPTION_MSG CEXC_MSG_EMPTY("reverse")
        raise(EXCEPTION_MSG, sizeof(EXCEPTION_MSG));
        #undef EXCEPTION_MSG
        return true; /* Successfully did nothing */
    }

    /* CORE FUNCTIONALITY
       Create/get/cast essential values */
    size_t item_size = dynarr->size;
    char *item1,
         *item2,
         *data = (char *)dynarr->data,
         *temp = malloc(item_size);
    if (!temp)
    {
        #define EXCEPTION_MSG CEXC_MSG_ALLOC_FAIL("reverse")
        raise(EXCEPTION_MSG, sizeof(EXCEPTION_MSG));
        #undef EXCEPTION_MSG
        return false; /* No place to store variable */
    }
    /* Swap items in place */
    for (size_t i=0; i < (length/2); i++)
    {
        item1 = data + i*item_size;
        item2 = data + (length - i - 1)*item_size;

        memcpy(temp,  item1, item_size);
        memcpy(item1, item2, item_size);
        memcpy(item2, temp,  item_size);
    }
    /* Clean up */
    free(temp);
    return true; /* Successfully reversed */
}


/*----------------------------------------------------------------------------*/
bool
cutils_cdar_DynamicArray_void_ptr_append(cutils_cdar_DynamicArray_void_ptr *dynarr,
                                         size_t count,
                                         void *source)
{
#ifndef CDAR_OPT
    /* Not initialised */
    if (!dynarr)
    {
        #define EXCEPTION_MSG CEXC_MSG_NOT_INIT("append")
        raise(EXCEPTION_MSG, sizeof(EXCEPTION_MSG));
        #undef EXCEPTION_MSG
        return false; /* Cannot operate on nothing */
    }
    /* Invalid source */
    else if (!source)
    {
        #define EXCEPTION_MSG CEXC_MSG_ARGUMENT_NULL("append", "3rd", source)
        raise(EXCEPTION_MSG, sizeof(EXCEPTION_MSG));
        #undef EXCEPTION_MSG
        return true; /* Successfully added nothing */
    }
    else
#else
    /* Something to append */
    if (count)
#endif /* CDAR_OPT */
    {
        /* CORE FUNCTIONALITY
           Resize array if necessary */
        size_t item_size = dynarr->size;
        if (!__cdar_resize(dynarr, item_size, count))
        {
            #define EXCEPTION_MSG CEXC_MSG_REALLOC_FAIL("append")
            raise(EXCEPTION_MSG, sizeof(EXCEPTION_MSG));
            #undef EXCEPTION_MSG
            return false; /* No place to append */
        }
        /* Extend array with data */
        memcpy((char *)dynarr->data + dynarr->used*item_size,
                source,
                item_size*count);
        /* Update usage data */
        dynarr->used += count;
    }
    return true; /* Successfully added 0 or more items */
}


/*----------------------------------------------------------------------------*/
bool
cutils_cdar_DynamicArray_void_ptr_push(cutils_cdar_DynamicArray_void_ptr *dynarr,
                                      size_t index,
                                      size_t count,
                                      void *source)
{
#ifndef CDAR_OPT
    /* Not initialised */
    if (!dynarr)
    {
        #define EXCEPTION_MSG CEXC_MSG_NOT_INIT("insert")
        raise(EXCEPTION_MSG, sizeof(EXCEPTION_MSG));
        #undef EXCEPTION_MSG
        return false; /* Cannot operate on nothing */
    }
    /* Nothing to insert */
    else if (!count)
    {
        return true; /* Successfully did nothing */
    }
    /* Invalid source */
    else if (!source)
    {
        #define EXCEPTION_MSG CEXC_MSG_ARGUMENT_NULL("insert", "4th", source)
        raise(EXCEPTION_MSG, sizeof(EXCEPTION_MSG));
        #undef EXCEPTION_MSG
        return true; /* Successfully did nothing */
    }
#else
    /* Nothing to insert */
    if (!count) return true; /* Successfully did nothing */
#endif /* CDAR_OPT */

    /* CORE FUNCTIONALITY
       Resize array if necessary */
    size_t item_size = dynarr->size;
    if (!__cdar_resize(dynarr, item_size, count))
    {
        #define EXCEPTION_MSG CEXC_MSG_REALLOC_FAIL("insert")
        raise(EXCEPTION_MSG, sizeof(EXCEPTION_MSG));
        #undef EXCEPTION_MSG
        return false; /* No place to insert */
    }
    char *data = (char *)dynarr->data;
    /* If insertion will shift the data (not last index) */
    if (index < dynarr->used)
    {
        /* Shift original data if array is not empty, and
           index is not the last index (append) */
        if (dynarr->used)
        {
            /* Copy data with offset until we reach -1 -> size_t max value */
            for (size_t i=dynarr->used - 1; (i>=index) && (i!=(size_t)-1); i--)
                memcpy(data + (i + count)*item_size, data + i*item_size, item_size);
        }
    }
#ifndef CDAR_OPT
    /* If insertion won't shift data,
       because index is the last index */
    else
        /* Limit index */
        index = dynarr->used;
#endif /* CDAR_OPT */

    /* Insert new data */
    memcpy(data + index*item_size, source, item_size*count);
    /* Update usage data */
    dynarr->used += count;
    return true; /* Successfully inserted */
}


/*----------------------------------------------------------------------------*/
size_t
cutils_cdar_DynamicArray_void_ptr_pull(cutils_cdar_DynamicArray_void_ptr *dynarr,
                                       size_t index,
                                       size_t count)
{
#ifndef CDAR_OPT
    /* Not initialised */
    if (!dynarr)
    {
        #define EXCEPTION_MSG CEXC_MSG_NOT_INIT("remove")
        raise(EXCEPTION_MSG, sizeof(EXCEPTION_MSG));
        #undef EXCEPTION_MSG
        return 0; /* Cannot operate on nothing */
    }
    /* Nothing to remove */
    else if (!count)
    {
        return 0; /* Successfully removed nothing */
    }
    /* Empty array */
    else if (!dynarr->used)
    {
        #define EXCEPTION_MSG CEXC_MSG_EMPTY("remove")
        raise(EXCEPTION_MSG, sizeof(EXCEPTION_MSG));
        #undef EXCEPTION_MSG
        return 0; /* Successfully removed nothing */
    }
    /* Out of range */
    else if (index >= dynarr->used)
    {
        #define EXCEPTION_MSG CEXC_MSG_ARGUMENT_OUTOF("remove", "2nd", index)
        raise(EXCEPTION_MSG, sizeof(EXCEPTION_MSG));
        #undef EXCEPTION_MSG
        return 0; /* Successfully removed nothing */
    }
#else
    /* Nothing to remove or Empty array */
    if (!count || !dynarr->used) return 0;
#endif /* CDAR_OPT */

    /* CORE FUNCTIONALITY
       If remove from end */
    else if ((index + count) >= dynarr->used)
    {
        count = dynarr->used - index;
        dynarr->used = index;
        return count; /* Successfully removed */
    }

    /* If remove from "middle" */
    size_t item_size = dynarr->size;
    char *data = (char *)dynarr->data;
    size_t repeat = dynarr->used - count;

    /* Shift data */
    for (size_t i=index; i<repeat; i++)
        memcpy(data + i*item_size, data + (i + count)*item_size, item_size);

    /* Update usage data */
    dynarr->used -= count;
    return count; /* Successfully removed */
}


/*----------------------------------------------------------------------------*/
size_t
cutils_cdar_DynamicArray_void_ptr_pop(cutils_cdar_DynamicArray_void_ptr *dynarr,
                                      size_t index,
                                      size_t count,
                                      void *destination)
{
#ifndef CDAR_OPT
    /* Not initialised */
    if (!dynarr)
    {
        #define EXCEPTION_MSG CEXC_MSG_NOT_INIT("pop")
        raise(EXCEPTION_MSG, sizeof(EXCEPTION_MSG));
        #undef EXCEPTION_MSG
        return 0;
    }
    /* Nothing to pop */
    else if (!count)
    {
        return 0; /* Successfully popped nothing */
    }
    /* Invalid destination */
    else if (!destination)
    {
        #define EXCEPTION_MSG CEXC_MSG_ARGUMENT_NULL("pop", "4th", destination)
        raise(EXCEPTION_MSG, sizeof(EXCEPTION_MSG));
        #undef EXCEPTION_MSG
        return 0; /* Successfully popped nothing */
    }
    /* Empty array */
    else if (!dynarr->used)
    {
        #define EXCEPTION_MSG CEXC_MSG_EMPTY("pop")
        raise(EXCEPTION_MSG, sizeof(EXCEPTION_MSG));
        #undef EXCEPTION_MSG
        return 0; /* Successfully popped nothing */
    }
    /* Out of range */
    else if (index >= dynarr->used)
    {
        #define EXCEPTION_MSG CEXC_MSG_ARGUMENT_OUTOF("pop", "2nd", index)
        raise(EXCEPTION_MSG, sizeof(EXCEPTION_MSG));
        #undef EXCEPTION_MSG
        return 0; /* Successfully popped nothing */
    }
#else
    /* Nothing to pop or Empty array */
    if (!count || !dynarr->used) return 0;
#endif /* CDAR_OPT */

    /* CORE FUNCTIONALITY
       Limit count */
    else if ((index + count) >= dynarr->used)
        count = dynarr->used - index;

    /* Create/get/cast essential values */
    size_t item_size = dynarr->size;
    char *data = (char *)dynarr->data;

    /* Copy data to destination */
    memcpy(destination, data + index*item_size, count*item_size);

    /* Shift data */
    for (size_t i=0; i<count; i++)
        memcpy(data + (index + i)*item_size,
               data + (index + count + i)*item_size,
               item_size);

    /* Update usage data */
    dynarr->used -= count;
    return count; /* Successfully popped */
}


/*----------------------------------------------------------------------------*/
size_t
cutils_cdar_DynamicArray_void_ptr_sub(cutils_cdar_DynamicArray_void_ptr *dynarr,
                                      size_t index,
                                      size_t count,
                                      void *destination)
{
#ifndef CDAR_OPT
    /* Not initialised */
    if (!dynarr)
    {
        #define EXCEPTION_MSG CEXC_MSG_NOT_INIT("sub")
        raise(EXCEPTION_MSG, sizeof(EXCEPTION_MSG));
        #undef EXCEPTION_MSG
        return 0; /* Cannot operate on nothing */
    }
    /* Nothing to sub */
    else if (!count)
    {
        return 0; /* Successfully subbed nothing */
    }
    /* Invalid destination */
    else if (!destination)
    {
        #define EXCEPTION_MSG CEXC_MSG_ARGUMENT_NULL("sub", "4th", destination)
        raise(EXCEPTION_MSG, sizeof(EXCEPTION_MSG));
        #undef EXCEPTION_MSG
        return 0; /* Successfully subbed nothing */
    }
    /* Empty array */
    else if (!dynarr->used)
    {
        #define EXCEPTION_MSG CEXC_MSG_EMPTY("sub")
        raise(EXCEPTION_MSG, sizeof(EXCEPTION_MSG));
        #undef EXCEPTION_MSG
        return 0; /* Successfully subbed nothing */
    }
    /* Out of range */
    else if (index >= dynarr->used)
    {
        #define EXCEPTION_MSG CEXC_MSG_ARGUMENT_OUTOF("sub", "2nd", index)
        raise(EXCEPTION_MSG, sizeof(EXCEPTION_MSG));
        #undef EXCEPTION_MSG
        return 0; /* Successfully subbed nothing */
    }
#else
    /* Nothing to sub or Empty array */
    if (!count || !dynarr->used) return 0;
#endif /* CDAR_OPT */

    /* CORE FUNCTIONALITY
       Limit count */
    else if ((index + count) >= dynarr->used)
        count = dynarr->used - index;

    /* Create/get/cast essential values */
    size_t item_size = dynarr->size;

    /* Copy data to destination */
    memcpy(destination, (char *)dynarr->data + index*item_size, count*item_size);
    return count; /* Successfully subbed */
}

/*----------------------------------------------------------------------------*/
void
cutils_cdar_DynamicArray_void_ptr_truncate(cutils_cdar_DynamicArray_void_ptr *dynarr,
                                           size_t index)
{
#ifndef CDAR_OPT
    /* Not initialised */
    if (!dynarr)
    {
        #define EXCEPTION_MSG CEXC_MSG_NOT_INIT("truncate")
        raise(EXCEPTION_MSG, sizeof(EXCEPTION_MSG));
        #undef EXCEPTION_MSG
        return; /* Cannot operate on nothing */
    }
    else
#endif /* CDAR_OPT */
    /* Out of range */
    if (index >= dynarr->used)
    {
        #define EXCEPTION_MSG CEXC_MSG_ARGUMENT_OUTOF("truncate", "2nd", index)
        raise(EXCEPTION_MSG, sizeof(EXCEPTION_MSG));
        #undef EXCEPTION_MSG
        return; /* Out of range */
    }

    /* CORE FUNCTIONALITY */
    dynarr->used = index;
}


/*----------------------------------------------------------------------------*/
bool
cutils_cdar_DynamicArray_void_ptr_set(cutils_cdar_DynamicArray_void_ptr *dynarr,
                                      size_t index,
                                      size_t count,
                                      void *source)
{
#ifndef CDAR_OPT
    /* Not initialised */
    if (!dynarr)
    {
        #define EXCEPTION_MSG CEXC_MSG_NOT_INIT("set")
        raise(EXCEPTION_MSG, sizeof(EXCEPTION_MSG));
        #undef EXCEPTION_MSG
        return false; /* Cannot operate on nothing */
    }
    /* Nothing to set */
    else if (!count)
    {
        return true; /* Successfully set nothing */
    }
    /* Invalid source */
    else if (!source)
    {
        #define EXCEPTION_MSG CEXC_MSG_ARGUMENT_NULL("set", "4th", destination)
        raise(EXCEPTION_MSG, sizeof(EXCEPTION_MSG));
        #undef EXCEPTION_MSG
        return true; /* Successfully set nothing */
    }
    /* Out of range */
    else if (index >= dynarr->used)
    {
        #define EXCEPTION_MSG CEXC_MSG_ARGUMENT_OUTOF("set", "2nd", index)
        raise(EXCEPTION_MSG, sizeof(EXCEPTION_MSG));
        #undef EXCEPTION_MSG
        return false; /* Out of range */
    }
#else
    /* Nothing to set */
    if (!count) return true; /* Successfully set nothing */
#endif /* CDAR_OPT */

    /* CORE FUNCTIONALITY
       Create/get/cast essential values */
    size_t item_size = dynarr->size;
    size_t max_count = dynarr->used - index;
    char *data = (char *)dynarr->data;

    /* Replace items until reached end */
    memcpy(data + index*item_size, source,
           ((max_count >= count) ? count : max_count)*item_size);
    return true; /* Successfully set */
}


/*----------------------------------------------------------------------------*/
void *
cutils_cdar_DynamicArray_void_ptr_get(cutils_cdar_DynamicArray_void_ptr *dynarr,
                                      size_t index)
{
#ifndef CDAR_OPT
    if (!dynarr)
    {
        #define EXCEPTION_MSG CEXC_MSG_NOT_INIT("get")
        raise(EXCEPTION_MSG, sizeof(EXCEPTION_MSG));
        #undef EXCEPTION_MSG
        return NULL; /* Cannot operate on nothing */
    }
    else if (!dynarr->used)
    {
        #define EXCEPTION_MSG CEXC_MSG_EMPTY("get")
        raise(EXCEPTION_MSG, sizeof(EXCEPTION_MSG));
        #undef EXCEPTION_MSG
        return NULL;
    }
    else if (index >= dynarr->used)
    {
        #define EXCEPTION_MSG CEXC_MSG_ARGUMENT_OUTOF("get", "2nd", index)
        raise(EXCEPTION_MSG, sizeof(EXCEPTION_MSG));
        #undef EXCEPTION_MSG
        return NULL;
    }
#endif /* CDAR_OPT */

    /* CORE FUNCTIONALITY */
    return (char *)dynarr->data + dynarr->size * index;
}


/*----------------------------------------------------------------------------*/
bool
cutils_cdar_DynamicArray_void_ptr_find(cutils_cdar_DynamicArray_void_ptr *dynarr,
                                       const void *item,
                                       size_t *index)
{
#ifndef CDAR_OPT
    if (!dynarr)
    {
        #define EXCEPTION_MSG CEXC_MSG_NOT_INIT("find")
        raise(EXCEPTION_MSG, sizeof(EXCEPTION_MSG));
        #undef EXCEPTION_MSG
        return false; /* Cannot operate on nothing */
    }
    else if (!index)
    {
        #define EXCEPTION_MSG CEXC_MSG_ARGUMENT_NULL("find", "3rd", index)
        raise(EXCEPTION_MSG, sizeof(EXCEPTION_MSG));
        #undef EXCEPTION_MSG
        return false; /* Invalid data */
    }
    else
#endif /* CDAR_OPT */
    if (dynarr->used)
    {

        /* CORE FUNCTIONALITY
           Create/get/cast essentials */
        size_t item_size = dynarr->size;
        char *data = (char *)dynarr->data;

        /* Search for item */
        for (size_t i=0; i<dynarr->used; i++)
        {
            if (!memcmp(item, data + i*item_size, item_size))
            {
                *index = i;
                return true; /* Successfully found */
            }
        }
    #ifdef CEXC_USE
        return false; /* Successfully not found */
    #endif /* CEXC_USE */
    }
    #define EXCEPTION_MSG CEXC_MSG_EMPTY("find")
    raise(EXCEPTION_MSG, sizeof(EXCEPTION_MSG));
    #undef EXCEPTION_MSG
    return false; /* Successfully found */
}


/*----------------------------------------------------------------------------*/
size_t
cutils_cdar_DynamicArray_void_ptr_findall(cutils_cdar_DynamicArray_void_ptr *dynarr,
                                          const void *item,
                                          size_t *indices)
{
#ifndef CDAR_OPT
    if (!dynarr)
    {
        #define EXCEPTION_MSG CEXC_MSG_NOT_INIT("findall")
        raise(EXCEPTION_MSG, sizeof(EXCEPTION_MSG));
        #undef EXCEPTION_MSG
        return 0; /* Cannot operate on nothing */
    }
    else if (!indices)
    {
        #define EXCEPTION_MSG CEXC_MSG_ARGUMENT_NULL("findall", "3rd", indices)
        raise(EXCEPTION_MSG, sizeof(EXCEPTION_MSG));
        #undef EXCEPTION_MSG
        return 0;
    }
    else
#endif /* CDAR_OPT */
    if (dynarr->used)
    {
        /* CORE FUNCTIONALITY
           Create/get/cast essentials */
        size_t item_size = dynarr->size;
        char *data = (char *)dynarr->data;
        size_t count = 0;

        /* Search for item */
        for (size_t i=0; i<dynarr->used; i++)
            if (!memcmp(item, data + i*item_size, item_size))
                indices[count++] = i;
        return count;
    }
    #define EXCEPTION_MSG CEXC_MSG_EMPTY("findall")
    raise(EXCEPTION_MSG, sizeof(EXCEPTION_MSG));
    #undef EXCEPTION_MSG
    return 0;
}

/*----------------------------------------------------------------------------*/
void
cutils_cdar_DynamicArray_void_ptr_sort(cutils_cdar_DynamicArray_void_ptr *dynarr,
                                       int (*compare)(const void*, const void*))
{
#ifndef CDAR_OPT
    if (!dynarr)
    {
        #define EXCEPTION_MSG CEXC_MSG_NOT_INIT("sort")
        raise(EXCEPTION_MSG, sizeof(EXCEPTION_MSG));
        #undef EXCEPTION_MSG
        return; /* Cannot operate on nothing */
    }
    else
#endif /* CDAR_OPT */
    if (!dynarr->used)
    {
        #define EXCEPTION_MSG CEXC_MSG_EMPTY("sort")
        raise(EXCEPTION_MSG, sizeof(EXCEPTION_MSG));
        #undef EXCEPTION_MSG
        return;
    }

    /* CORE FUNCTIONALITY */
    qsort(dynarr->data, dynarr->used, dynarr->size, compare);
}


/*----------------------------------------------------------------------------*/
void
cutils_cdar_DynamicArray_void_ptr_sortsub(cutils_cdar_DynamicArray_void_ptr *dynarr,
                                          size_t index,
                                          size_t count,
                                          int (*compare)(const void *, const void*))
{
#ifndef CDAR_OPT
    if (!dynarr)
    {
        #define EXCEPTION_MSG CEXC_MSG_NOT_INIT("sortsub")
        raise(EXCEPTION_MSG, sizeof(EXCEPTION_MSG));
        #undef EXCEPTION_MSG
        return; /* Cannot operate on nothing */
    }
    else if (!dynarr->used)
    {
        #define EXCEPTION_MSG CEXC_MSG_EMPTY("sortsub")
        raise(EXCEPTION_MSG, sizeof(EXCEPTION_MSG));
        #undef EXCEPTION_MSG
        return;
    }
    else if (index >= dynarr->used)
    {
        #define EXCEPTION_MSG CEXC_MSG_ARGUMENT_OUTOF("sortsub", "2nd", index)
        raise(EXCEPTION_MSG, sizeof(EXCEPTION_MSG));
        #undef EXCEPTION_MSG
        return;
    }
#else
    if (!dynarr->used) return;
#endif /* CDAR_OPT */

    /* CORE FUNCTIONALITY
       Limit count */
    if ((index + count) >= dynarr->used)
        count = dynarr->used - index;
    /* Cast data & search */
    qsort((char *)dynarr->data + dynarr->size * index, count, dynarr->size, compare);
}

/*----------------------------------------------------------------------------*/
typedef cutils_cdar_DynamicArray_void_ptr cutils_cdar_DynamicArray_char;
bool cutils_cdar_DynamicArray_char_new(cutils_cdar_DynamicArray_char**d,size_t c,char*a){return cutils_cdar_DynamicArray_void_ptr_new(d,c,sizeof(char),a);}
char* cutils_cdar_DynamicArray_char_data(cutils_cdar_DynamicArray_char*d,size_t*s,size_t*c){return cutils_cdar_DynamicArray_void_ptr_data(d,s,c);}
char* cutils_cdar_DynamicArray_char_raw(cutils_cdar_DynamicArray_char*d){return (char*)cutils_cdar_DynamicArray_void_ptr_raw(d);}
bool cutils_cdar_DynamicArray_char_append(cutils_cdar_DynamicArray_char*d,size_t c,char*a){return cutils_cdar_DynamicArray_void_ptr_append(d,c,a);}
bool cutils_cdar_DynamicArray_char_push(cutils_cdar_DynamicArray_char*d,size_t i,size_t c,char*a){return cutils_cdar_DynamicArray_void_ptr_push(d,i,c,a);}
bool cutils_cdar_DynamicArray_char_set(cutils_cdar_DynamicArray_char*d,size_t i,size_t c,char*s){return cutils_cdar_DynamicArray_void_ptr_set(d,i,c,s);}
size_t cutils_cdar_DynamicArray_char_pop(cutils_cdar_DynamicArray_char*d,size_t i,size_t c,char*a){return cutils_cdar_DynamicArray_void_ptr_pop(d,i,c,a);}
size_t cutils_cdar_DynamicArray_char_sub(cutils_cdar_DynamicArray_char*d,size_t i,size_t c,char*a){return cutils_cdar_DynamicArray_void_ptr_sub(d,i,c,a);}
char cutils_cdar_DynamicArray_char_get(cutils_cdar_DynamicArray_char*d,size_t i){return *(char*)cutils_cdar_DynamicArray_void_ptr_get(d,i);}
bool cutils_cdar_DynamicArray_char_find(cutils_cdar_DynamicArray_char*d,const char*p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_find(d,p,i);}
size_t cutils_cdar_DynamicArray_char_findall(cutils_cdar_DynamicArray_char*d,const char*p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_findall(d,p,i);}
void(*cutils_cdar_DynamicArray_char_del)(cutils_cdar_DynamicArray_char*)=cutils_cdar_DynamicArray_void_ptr_del;
size_t(*cutils_cdar_DynamicArray_char_len)(cutils_cdar_DynamicArray_char*)=cutils_cdar_DynamicArray_void_ptr_len;
size_t(*cutils_cdar_DynamicArray_char_size)(cutils_cdar_DynamicArray_char*)=cutils_cdar_DynamicArray_void_ptr_size;
bool(*cutils_cdar_DynamicArray_char_resize)(cutils_cdar_DynamicArray_char*,size_t)=cutils_cdar_DynamicArray_void_ptr_resize;
bool(*cutils_cdar_DynamicArray_char_swap)(cutils_cdar_DynamicArray_char*,size_t,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_swap;
bool(*cutils_cdar_DynamicArray_char_reverse)(cutils_cdar_DynamicArray_char*)=cutils_cdar_DynamicArray_void_ptr_reverse;
size_t(*cutils_cdar_DynamicArray_char_pull)(cutils_cdar_DynamicArray_char*,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_pull;
void(*cutils_cdar_DynamicArray_char_truncate)(cutils_cdar_DynamicArray_char*,size_t)=cutils_cdar_DynamicArray_void_ptr_truncate;
void(*cutils_cdar_DynamicArray_char_clear)(cutils_cdar_DynamicArray_char*)=cutils_cdar_DynamicArray_void_ptr_clear;
/*----------------------------------------------------------------------------*/
typedef cutils_cdar_DynamicArray_void_ptr cutils_cdar_DynamicArray_signed_char;
bool cutils_cdar_DynamicArray_signed_char_new(cutils_cdar_DynamicArray_signed_char**d,size_t c,signed char*a){return cutils_cdar_DynamicArray_void_ptr_new(d,c,sizeof(signed char),a);}
signed char* cutils_cdar_DynamicArray_signed_char_data(cutils_cdar_DynamicArray_signed_char*d,size_t*s,size_t*c){return cutils_cdar_DynamicArray_void_ptr_data(d,s,c);}
signed char* cutils_cdar_DynamicArray_signed_char_raw(cutils_cdar_DynamicArray_signed_char*d){return (signed char*)cutils_cdar_DynamicArray_void_ptr_raw(d);}
bool cutils_cdar_DynamicArray_signed_char_append(cutils_cdar_DynamicArray_signed_char*d,size_t c,signed char*a){return cutils_cdar_DynamicArray_void_ptr_append(d,c,a);}
bool cutils_cdar_DynamicArray_signed_char_push(cutils_cdar_DynamicArray_signed_char*d,size_t i,size_t c,signed char*a){return cutils_cdar_DynamicArray_void_ptr_push(d,i,c,a);}
bool cutils_cdar_DynamicArray_signed_char_set(cutils_cdar_DynamicArray_signed_char*d,size_t i,size_t c,signed char*s){return cutils_cdar_DynamicArray_void_ptr_set(d,i,c,s);}
size_t cutils_cdar_DynamicArray_signed_char_pop(cutils_cdar_DynamicArray_signed_char*d,size_t i,size_t c,signed char*a){return cutils_cdar_DynamicArray_void_ptr_pop(d,i,c,a);}
size_t cutils_cdar_DynamicArray_signed_char_sub(cutils_cdar_DynamicArray_signed_char*d,size_t i,size_t c,signed char*a){return cutils_cdar_DynamicArray_void_ptr_sub(d,i,c,a);}
signed char cutils_cdar_DynamicArray_signed_char_get(cutils_cdar_DynamicArray_signed_char*d,size_t i){return *(signed char*)cutils_cdar_DynamicArray_void_ptr_get(d,i);}
bool cutils_cdar_DynamicArray_signed_char_find(cutils_cdar_DynamicArray_signed_char*d,const signed char*p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_find(d,p,i);}
size_t cutils_cdar_DynamicArray_signed_char_findall(cutils_cdar_DynamicArray_signed_char*d,const signed char*p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_findall(d,p,i);}
void(*cutils_cdar_DynamicArray_signed_char_del)(cutils_cdar_DynamicArray_signed_char*)=cutils_cdar_DynamicArray_void_ptr_del;
size_t(*cutils_cdar_DynamicArray_signed_char_len)(cutils_cdar_DynamicArray_signed_char*)=cutils_cdar_DynamicArray_void_ptr_len;
size_t(*cutils_cdar_DynamicArray_signed_char_size)(cutils_cdar_DynamicArray_signed_char*)=cutils_cdar_DynamicArray_void_ptr_size;
bool(*cutils_cdar_DynamicArray_signed_char_resize)(cutils_cdar_DynamicArray_signed_char*,size_t)=cutils_cdar_DynamicArray_void_ptr_resize;
bool(*cutils_cdar_DynamicArray_signed_char_swap)(cutils_cdar_DynamicArray_signed_char*,size_t,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_swap;
bool(*cutils_cdar_DynamicArray_signed_char_reverse)(cutils_cdar_DynamicArray_signed_char*)=cutils_cdar_DynamicArray_void_ptr_reverse;
size_t(*cutils_cdar_DynamicArray_signed_char_pull)(cutils_cdar_DynamicArray_signed_char*,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_pull;
void(*cutils_cdar_DynamicArray_signed_char_truncate)(cutils_cdar_DynamicArray_signed_char*,size_t)=cutils_cdar_DynamicArray_void_ptr_truncate;
void(*cutils_cdar_DynamicArray_signed_char_clear)(cutils_cdar_DynamicArray_signed_char*)=cutils_cdar_DynamicArray_void_ptr_clear;
/*----------------------------------------------------------------------------*/
typedef cutils_cdar_DynamicArray_void_ptr cutils_cdar_DynamicArray_unsigned_char;
bool cutils_cdar_DynamicArray_unsigned_char_new(cutils_cdar_DynamicArray_unsigned_char**d,size_t c,unsigned char*a){return cutils_cdar_DynamicArray_void_ptr_new(d,c,sizeof(unsigned char),a);}
unsigned char* cutils_cdar_DynamicArray_unsigned_char_data(cutils_cdar_DynamicArray_unsigned_char*d,size_t*s,size_t*c){return cutils_cdar_DynamicArray_void_ptr_data(d,s,c);}
unsigned char* cutils_cdar_DynamicArray_unsigned_char_raw(cutils_cdar_DynamicArray_unsigned_char*d){return (unsigned char*)cutils_cdar_DynamicArray_void_ptr_raw(d);}
bool cutils_cdar_DynamicArray_unsigned_char_append(cutils_cdar_DynamicArray_unsigned_char*d,size_t c,unsigned char*a){return cutils_cdar_DynamicArray_void_ptr_append(d,c,a);}
bool cutils_cdar_DynamicArray_unsigned_char_push(cutils_cdar_DynamicArray_unsigned_char*d,size_t i,size_t c,unsigned char*a){return cutils_cdar_DynamicArray_void_ptr_push(d,i,c,a);}
bool cutils_cdar_DynamicArray_unsigned_char_set(cutils_cdar_DynamicArray_unsigned_char*d,size_t i,size_t c,unsigned char*s){return cutils_cdar_DynamicArray_void_ptr_set(d,i,c,s);}
size_t cutils_cdar_DynamicArray_unsigned_char_pop(cutils_cdar_DynamicArray_unsigned_char*d,size_t i,size_t c,unsigned char*a){return cutils_cdar_DynamicArray_void_ptr_pop(d,i,c,a);}
size_t cutils_cdar_DynamicArray_unsigned_char_sub(cutils_cdar_DynamicArray_unsigned_char*d,size_t i,size_t c,unsigned char*a){return cutils_cdar_DynamicArray_void_ptr_sub(d,i,c,a);}
unsigned char cutils_cdar_DynamicArray_unsigned_char_get(cutils_cdar_DynamicArray_unsigned_char*d,size_t i){return *(unsigned char*)cutils_cdar_DynamicArray_void_ptr_get(d,i);}
bool cutils_cdar_DynamicArray_unsigned_char_find(cutils_cdar_DynamicArray_unsigned_char*d,const unsigned char*p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_find(d,p,i);}
size_t cutils_cdar_DynamicArray_unsigned_char_findall(cutils_cdar_DynamicArray_unsigned_char*d,const unsigned char*p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_findall(d,p,i);}
void(*cutils_cdar_DynamicArray_unsigned_char_del)(cutils_cdar_DynamicArray_unsigned_char*)=cutils_cdar_DynamicArray_void_ptr_del;
size_t(*cutils_cdar_DynamicArray_unsigned_char_len)(cutils_cdar_DynamicArray_unsigned_char*)=cutils_cdar_DynamicArray_void_ptr_len;
size_t(*cutils_cdar_DynamicArray_unsigned_char_size)(cutils_cdar_DynamicArray_unsigned_char*)=cutils_cdar_DynamicArray_void_ptr_size;
bool(*cutils_cdar_DynamicArray_unsigned_char_resize)(cutils_cdar_DynamicArray_unsigned_char*,size_t)=cutils_cdar_DynamicArray_void_ptr_resize;
bool(*cutils_cdar_DynamicArray_unsigned_char_swap)(cutils_cdar_DynamicArray_unsigned_char*,size_t,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_swap;
bool(*cutils_cdar_DynamicArray_unsigned_char_reverse)(cutils_cdar_DynamicArray_unsigned_char*)=cutils_cdar_DynamicArray_void_ptr_reverse;
size_t(*cutils_cdar_DynamicArray_unsigned_char_pull)(cutils_cdar_DynamicArray_unsigned_char*,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_pull;
void(*cutils_cdar_DynamicArray_unsigned_char_truncate)(cutils_cdar_DynamicArray_unsigned_char*,size_t)=cutils_cdar_DynamicArray_void_ptr_truncate;
void(*cutils_cdar_DynamicArray_unsigned_char_clear)(cutils_cdar_DynamicArray_unsigned_char*)=cutils_cdar_DynamicArray_void_ptr_clear;
/*----------------------------------------------------------------------------*/
typedef cutils_cdar_DynamicArray_void_ptr cutils_cdar_DynamicArray_char_ptr;
bool cutils_cdar_DynamicArray_char_ptr_new(cutils_cdar_DynamicArray_char_ptr**d,size_t c,char**a){return cutils_cdar_DynamicArray_void_ptr_new(d,c,sizeof(char*),a);}
char** cutils_cdar_DynamicArray_char_ptr_data(cutils_cdar_DynamicArray_char_ptr*d,size_t*s,size_t*c){return cutils_cdar_DynamicArray_void_ptr_data(d,s,c);}
char** cutils_cdar_DynamicArray_char_ptr_raw(cutils_cdar_DynamicArray_char_ptr*d){return (char**)cutils_cdar_DynamicArray_void_ptr_raw(d);}
bool cutils_cdar_DynamicArray_char_ptr_append(cutils_cdar_DynamicArray_char_ptr*d,size_t c,char**a){return cutils_cdar_DynamicArray_void_ptr_append(d,c,a);}
bool cutils_cdar_DynamicArray_char_ptr_push(cutils_cdar_DynamicArray_char_ptr*d,size_t i,size_t c,char**a){return cutils_cdar_DynamicArray_void_ptr_push(d,i,c,a);}
bool cutils_cdar_DynamicArray_char_ptr_set(cutils_cdar_DynamicArray_char_ptr*d,size_t i,size_t c,char**s){return cutils_cdar_DynamicArray_void_ptr_set(d,i,c,s);}
size_t cutils_cdar_DynamicArray_char_ptr_pop(cutils_cdar_DynamicArray_char_ptr*d,size_t i,size_t c,char**a){return cutils_cdar_DynamicArray_void_ptr_pop(d,i,c,a);}
size_t cutils_cdar_DynamicArray_char_ptr_sub(cutils_cdar_DynamicArray_char_ptr*d,size_t i,size_t c,char**a){return cutils_cdar_DynamicArray_void_ptr_sub(d,i,c,a);}
char* cutils_cdar_DynamicArray_char_ptr_get(cutils_cdar_DynamicArray_char_ptr*d,size_t i){return *(char**)cutils_cdar_DynamicArray_void_ptr_get(d,i);}
bool cutils_cdar_DynamicArray_char_ptr_find(cutils_cdar_DynamicArray_char_ptr*d,const char**p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_find(d,p,i);}
size_t cutils_cdar_DynamicArray_char_ptr_findall(cutils_cdar_DynamicArray_char_ptr*d,const char**p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_findall(d,p,i);}
void(*cutils_cdar_DynamicArray_char_ptr_del)(cutils_cdar_DynamicArray_char_ptr*)=cutils_cdar_DynamicArray_void_ptr_del;
size_t(*cutils_cdar_DynamicArray_char_ptr_len)(cutils_cdar_DynamicArray_char_ptr*)=cutils_cdar_DynamicArray_void_ptr_len;
size_t(*cutils_cdar_DynamicArray_char_ptr_size)(cutils_cdar_DynamicArray_char_ptr*)=cutils_cdar_DynamicArray_void_ptr_size;
bool(*cutils_cdar_DynamicArray_char_ptr_resize)(cutils_cdar_DynamicArray_char_ptr*,size_t)=cutils_cdar_DynamicArray_void_ptr_resize;
bool(*cutils_cdar_DynamicArray_char_ptr_swap)(cutils_cdar_DynamicArray_char_ptr*,size_t,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_swap;
bool(*cutils_cdar_DynamicArray_char_ptr_reverse)(cutils_cdar_DynamicArray_char_ptr*)=cutils_cdar_DynamicArray_void_ptr_reverse;
size_t(*cutils_cdar_DynamicArray_char_ptr_pull)(cutils_cdar_DynamicArray_char_ptr*,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_pull;
void(*cutils_cdar_DynamicArray_char_ptr_truncate)(cutils_cdar_DynamicArray_char_ptr*,size_t)=cutils_cdar_DynamicArray_void_ptr_truncate;
void(*cutils_cdar_DynamicArray_char_ptr_clear)(cutils_cdar_DynamicArray_char_ptr*)=cutils_cdar_DynamicArray_void_ptr_clear;
/*----------------------------------------------------------------------------*/
typedef cutils_cdar_DynamicArray_void_ptr cutils_cdar_DynamicArray_short;
bool cutils_cdar_DynamicArray_short_new(cutils_cdar_DynamicArray_short**d,size_t c,short*a){return cutils_cdar_DynamicArray_void_ptr_new(d,c,sizeof(short),a);}
short* cutils_cdar_DynamicArray_short_data(cutils_cdar_DynamicArray_short*d,size_t*s,size_t*c){return cutils_cdar_DynamicArray_void_ptr_data(d,s,c);}
short* cutils_cdar_DynamicArray_short_raw(cutils_cdar_DynamicArray_short*d){return (short*)cutils_cdar_DynamicArray_void_ptr_raw(d);}
bool cutils_cdar_DynamicArray_short_append(cutils_cdar_DynamicArray_short*d,size_t c,short*a){return cutils_cdar_DynamicArray_void_ptr_append(d,c,a);}
bool cutils_cdar_DynamicArray_short_push(cutils_cdar_DynamicArray_short*d,size_t i,size_t c,short*a){return cutils_cdar_DynamicArray_void_ptr_push(d,i,c,a);}
bool cutils_cdar_DynamicArray_short_set(cutils_cdar_DynamicArray_short*d,size_t i,size_t c,short*s){return cutils_cdar_DynamicArray_void_ptr_set(d,i,c,s);}
size_t cutils_cdar_DynamicArray_short_pop(cutils_cdar_DynamicArray_short*d,size_t i,size_t c,short*a){return cutils_cdar_DynamicArray_void_ptr_pop(d,i,c,a);}
size_t cutils_cdar_DynamicArray_short_sub(cutils_cdar_DynamicArray_short*d,size_t i,size_t c,short*a){return cutils_cdar_DynamicArray_void_ptr_sub(d,i,c,a);}
short cutils_cdar_DynamicArray_short_get(cutils_cdar_DynamicArray_short*d,size_t i){return *(short*)cutils_cdar_DynamicArray_void_ptr_get(d,i);}
bool cutils_cdar_DynamicArray_short_find(cutils_cdar_DynamicArray_short*d,const short*p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_find(d,p,i);}
size_t cutils_cdar_DynamicArray_short_findall(cutils_cdar_DynamicArray_short*d,const short*p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_findall(d,p,i);}
void(*cutils_cdar_DynamicArray_short_del)(cutils_cdar_DynamicArray_short*)=cutils_cdar_DynamicArray_void_ptr_del;
size_t(*cutils_cdar_DynamicArray_short_len)(cutils_cdar_DynamicArray_short*)=cutils_cdar_DynamicArray_void_ptr_len;
size_t(*cutils_cdar_DynamicArray_short_size)(cutils_cdar_DynamicArray_short*)=cutils_cdar_DynamicArray_void_ptr_size;
bool(*cutils_cdar_DynamicArray_short_resize)(cutils_cdar_DynamicArray_short*,size_t)=cutils_cdar_DynamicArray_void_ptr_resize;
bool(*cutils_cdar_DynamicArray_short_swap)(cutils_cdar_DynamicArray_short*,size_t,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_swap;
bool(*cutils_cdar_DynamicArray_short_reverse)(cutils_cdar_DynamicArray_short*)=cutils_cdar_DynamicArray_void_ptr_reverse;
size_t(*cutils_cdar_DynamicArray_short_pull)(cutils_cdar_DynamicArray_short*,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_pull;
void(*cutils_cdar_DynamicArray_short_truncate)(cutils_cdar_DynamicArray_short*,size_t)=cutils_cdar_DynamicArray_void_ptr_truncate;
void(*cutils_cdar_DynamicArray_short_clear)(cutils_cdar_DynamicArray_short*)=cutils_cdar_DynamicArray_void_ptr_clear;
/*----------------------------------------------------------------------------*/
typedef cutils_cdar_DynamicArray_void_ptr cutils_cdar_DynamicArray_unsigned_short;
bool cutils_cdar_DynamicArray_unsigned_short_new(cutils_cdar_DynamicArray_unsigned_short**d,size_t c,unsigned short*a){return cutils_cdar_DynamicArray_void_ptr_new(d,c,sizeof(unsigned short),a);}
unsigned short* cutils_cdar_DynamicArray_unsigned_short_data(cutils_cdar_DynamicArray_unsigned_short*d,size_t*s,size_t*c){return cutils_cdar_DynamicArray_void_ptr_data(d,s,c);}
unsigned short* cutils_cdar_DynamicArray_unsigned_short_raw(cutils_cdar_DynamicArray_unsigned_short*d){return (unsigned short*)cutils_cdar_DynamicArray_void_ptr_raw(d);}
bool cutils_cdar_DynamicArray_unsigned_short_append(cutils_cdar_DynamicArray_unsigned_short*d,size_t c,unsigned short*a){return cutils_cdar_DynamicArray_void_ptr_append(d,c,a);}
bool cutils_cdar_DynamicArray_unsigned_short_push(cutils_cdar_DynamicArray_unsigned_short*d,size_t i,size_t c,unsigned short*a){return cutils_cdar_DynamicArray_void_ptr_push(d,i,c,a);}
bool cutils_cdar_DynamicArray_unsigned_short_set(cutils_cdar_DynamicArray_unsigned_short*d,size_t i,size_t c,unsigned short*s){return cutils_cdar_DynamicArray_void_ptr_set(d,i,c,s);}
size_t cutils_cdar_DynamicArray_unsigned_short_pop(cutils_cdar_DynamicArray_unsigned_short*d,size_t i,size_t c,unsigned short*a){return cutils_cdar_DynamicArray_void_ptr_pop(d,i,c,a);}
size_t cutils_cdar_DynamicArray_unsigned_short_sub(cutils_cdar_DynamicArray_unsigned_short*d,size_t i,size_t c,unsigned short*a){return cutils_cdar_DynamicArray_void_ptr_sub(d,i,c,a);}
unsigned short cutils_cdar_DynamicArray_unsigned_short_get(cutils_cdar_DynamicArray_unsigned_short*d,size_t i){return *(unsigned short*)cutils_cdar_DynamicArray_void_ptr_get(d,i);}
bool cutils_cdar_DynamicArray_unsigned_short_find(cutils_cdar_DynamicArray_unsigned_short*d,const unsigned short*p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_find(d,p,i);}
size_t cutils_cdar_DynamicArray_unsigned_short_findall(cutils_cdar_DynamicArray_unsigned_short*d,const unsigned short*p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_findall(d,p,i);}
void(*cutils_cdar_DynamicArray_unsigned_short_del)(cutils_cdar_DynamicArray_unsigned_short*)=cutils_cdar_DynamicArray_void_ptr_del;
size_t(*cutils_cdar_DynamicArray_unsigned_short_len)(cutils_cdar_DynamicArray_unsigned_short*)=cutils_cdar_DynamicArray_void_ptr_len;
size_t(*cutils_cdar_DynamicArray_unsigned_short_size)(cutils_cdar_DynamicArray_unsigned_short*)=cutils_cdar_DynamicArray_void_ptr_size;
bool(*cutils_cdar_DynamicArray_unsigned_short_resize)(cutils_cdar_DynamicArray_unsigned_short*,size_t)=cutils_cdar_DynamicArray_void_ptr_resize;
bool(*cutils_cdar_DynamicArray_unsigned_short_swap)(cutils_cdar_DynamicArray_unsigned_short*,size_t,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_swap;
bool(*cutils_cdar_DynamicArray_unsigned_short_reverse)(cutils_cdar_DynamicArray_unsigned_short*)=cutils_cdar_DynamicArray_void_ptr_reverse;
size_t(*cutils_cdar_DynamicArray_unsigned_short_pull)(cutils_cdar_DynamicArray_unsigned_short*,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_pull;
void(*cutils_cdar_DynamicArray_unsigned_short_truncate)(cutils_cdar_DynamicArray_unsigned_short*,size_t)=cutils_cdar_DynamicArray_void_ptr_truncate;
void(*cutils_cdar_DynamicArray_unsigned_short_clear)(cutils_cdar_DynamicArray_unsigned_short*)=cutils_cdar_DynamicArray_void_ptr_clear;
/*----------------------------------------------------------------------------*/
typedef cutils_cdar_DynamicArray_void_ptr cutils_cdar_DynamicArray_int;
bool cutils_cdar_DynamicArray_int_new(cutils_cdar_DynamicArray_int**d,size_t c,int*a){return cutils_cdar_DynamicArray_void_ptr_new(d,c,sizeof(int),a);}
int* cutils_cdar_DynamicArray_int_data(cutils_cdar_DynamicArray_int*d,size_t*s,size_t*c){return cutils_cdar_DynamicArray_void_ptr_data(d,s,c);}
int* cutils_cdar_DynamicArray_int_raw(cutils_cdar_DynamicArray_int*d){return (int*)cutils_cdar_DynamicArray_void_ptr_raw(d);}
bool cutils_cdar_DynamicArray_int_append(cutils_cdar_DynamicArray_int*d,size_t c,int*a){return cutils_cdar_DynamicArray_void_ptr_append(d,c,a);}
bool cutils_cdar_DynamicArray_int_push(cutils_cdar_DynamicArray_int*d,size_t i,size_t c,int*a){return cutils_cdar_DynamicArray_void_ptr_push(d,i,c,a);}
bool cutils_cdar_DynamicArray_int_set(cutils_cdar_DynamicArray_int*d,size_t i,size_t c,int*s){return cutils_cdar_DynamicArray_void_ptr_set(d,i,c,s);}
size_t cutils_cdar_DynamicArray_int_pop(cutils_cdar_DynamicArray_int*d,size_t i,size_t c,int*a){return cutils_cdar_DynamicArray_void_ptr_pop(d,i,c,a);}
size_t cutils_cdar_DynamicArray_int_sub(cutils_cdar_DynamicArray_int*d,size_t i,size_t c,int*a){return cutils_cdar_DynamicArray_void_ptr_sub(d,i,c,a);}
int cutils_cdar_DynamicArray_int_get(cutils_cdar_DynamicArray_int*d,size_t i){return *(int*)cutils_cdar_DynamicArray_void_ptr_get(d,i);}
bool cutils_cdar_DynamicArray_int_find(cutils_cdar_DynamicArray_int*d,const int*p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_find(d,p,i);}
size_t cutils_cdar_DynamicArray_int_findall(cutils_cdar_DynamicArray_int*d,const int*p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_findall(d,p,i);}
void(*cutils_cdar_DynamicArray_int_del)(cutils_cdar_DynamicArray_int*)=cutils_cdar_DynamicArray_void_ptr_del;
size_t(*cutils_cdar_DynamicArray_int_len)(cutils_cdar_DynamicArray_int*)=cutils_cdar_DynamicArray_void_ptr_len;
size_t(*cutils_cdar_DynamicArray_int_size)(cutils_cdar_DynamicArray_int*)=cutils_cdar_DynamicArray_void_ptr_size;
bool(*cutils_cdar_DynamicArray_int_resize)(cutils_cdar_DynamicArray_int*,size_t)=cutils_cdar_DynamicArray_void_ptr_resize;
bool(*cutils_cdar_DynamicArray_int_swap)(cutils_cdar_DynamicArray_int*,size_t,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_swap;
bool(*cutils_cdar_DynamicArray_int_reverse)(cutils_cdar_DynamicArray_int*)=cutils_cdar_DynamicArray_void_ptr_reverse;
size_t(*cutils_cdar_DynamicArray_int_pull)(cutils_cdar_DynamicArray_int*,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_pull;
void(*cutils_cdar_DynamicArray_int_truncate)(cutils_cdar_DynamicArray_int*,size_t)=cutils_cdar_DynamicArray_void_ptr_truncate;
void(*cutils_cdar_DynamicArray_int_clear)(cutils_cdar_DynamicArray_int*)=cutils_cdar_DynamicArray_void_ptr_clear;
/*----------------------------------------------------------------------------*/
typedef cutils_cdar_DynamicArray_void_ptr cutils_cdar_DynamicArray_unsigned_int;
bool cutils_cdar_DynamicArray_unsigned_int_new(cutils_cdar_DynamicArray_unsigned_int**d,size_t c,unsigned int*a){return cutils_cdar_DynamicArray_void_ptr_new(d,c,sizeof(unsigned int),a);}
unsigned int* cutils_cdar_DynamicArray_unsigned_int_data(cutils_cdar_DynamicArray_unsigned_int*d,size_t*s,size_t*c){return cutils_cdar_DynamicArray_void_ptr_data(d,s,c);}
unsigned int* cutils_cdar_DynamicArray_unsigned_int_raw(cutils_cdar_DynamicArray_unsigned_int*d){return (unsigned int*)cutils_cdar_DynamicArray_void_ptr_raw(d);}
bool cutils_cdar_DynamicArray_unsigned_int_append(cutils_cdar_DynamicArray_unsigned_int*d,size_t c,unsigned int*a){return cutils_cdar_DynamicArray_void_ptr_append(d,c,a);}
bool cutils_cdar_DynamicArray_unsigned_int_push(cutils_cdar_DynamicArray_unsigned_int*d,size_t i,size_t c,unsigned int*a){return cutils_cdar_DynamicArray_void_ptr_push(d,i,c,a);}
bool cutils_cdar_DynamicArray_unsigned_int_set(cutils_cdar_DynamicArray_unsigned_int*d,size_t i,size_t c,unsigned int*s){return cutils_cdar_DynamicArray_void_ptr_set(d,i,c,s);}
size_t cutils_cdar_DynamicArray_unsigned_int_pop(cutils_cdar_DynamicArray_unsigned_int*d,size_t i,size_t c,unsigned int*a){return cutils_cdar_DynamicArray_void_ptr_pop(d,i,c,a);}
size_t cutils_cdar_DynamicArray_unsigned_int_sub(cutils_cdar_DynamicArray_unsigned_int*d,size_t i,size_t c,unsigned int*a){return cutils_cdar_DynamicArray_void_ptr_sub(d,i,c,a);}
unsigned int cutils_cdar_DynamicArray_unsigned_int_get(cutils_cdar_DynamicArray_unsigned_int*d,size_t i){return *(unsigned int*)cutils_cdar_DynamicArray_void_ptr_get(d,i);}
bool cutils_cdar_DynamicArray_unsigned_int_find(cutils_cdar_DynamicArray_unsigned_int*d,const unsigned int*p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_find(d,p,i);}
size_t cutils_cdar_DynamicArray_unsigned_int_findall(cutils_cdar_DynamicArray_unsigned_int*d,const unsigned int*p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_findall(d,p,i);}
void(*cutils_cdar_DynamicArray_unsigned_int_del)(cutils_cdar_DynamicArray_unsigned_int*)=cutils_cdar_DynamicArray_void_ptr_del;
size_t(*cutils_cdar_DynamicArray_unsigned_int_len)(cutils_cdar_DynamicArray_unsigned_int*)=cutils_cdar_DynamicArray_void_ptr_len;
size_t(*cutils_cdar_DynamicArray_unsigned_int_size)(cutils_cdar_DynamicArray_unsigned_int*)=cutils_cdar_DynamicArray_void_ptr_size;
bool(*cutils_cdar_DynamicArray_unsigned_int_resize)(cutils_cdar_DynamicArray_unsigned_int*,size_t)=cutils_cdar_DynamicArray_void_ptr_resize;
bool(*cutils_cdar_DynamicArray_unsigned_int_swap)(cutils_cdar_DynamicArray_unsigned_int*,size_t,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_swap;
bool(*cutils_cdar_DynamicArray_unsigned_int_reverse)(cutils_cdar_DynamicArray_unsigned_int*)=cutils_cdar_DynamicArray_void_ptr_reverse;
size_t(*cutils_cdar_DynamicArray_unsigned_int_pull)(cutils_cdar_DynamicArray_unsigned_int*,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_pull;
void(*cutils_cdar_DynamicArray_unsigned_int_truncate)(cutils_cdar_DynamicArray_unsigned_int*,size_t)=cutils_cdar_DynamicArray_void_ptr_truncate;
void(*cutils_cdar_DynamicArray_unsigned_int_clear)(cutils_cdar_DynamicArray_unsigned_int*)=cutils_cdar_DynamicArray_void_ptr_clear;
/*----------------------------------------------------------------------------*/
typedef cutils_cdar_DynamicArray_void_ptr cutils_cdar_DynamicArray_long;
bool cutils_cdar_DynamicArray_long_new(cutils_cdar_DynamicArray_long**d,size_t c,long*a){return cutils_cdar_DynamicArray_void_ptr_new(d,c,sizeof(long),a);}
long* cutils_cdar_DynamicArray_long_data(cutils_cdar_DynamicArray_long*d,size_t*s,size_t*c){return cutils_cdar_DynamicArray_void_ptr_data(d,s,c);}
long* cutils_cdar_DynamicArray_long_raw(cutils_cdar_DynamicArray_long*d){return (long*)cutils_cdar_DynamicArray_void_ptr_raw(d);}
bool cutils_cdar_DynamicArray_long_append(cutils_cdar_DynamicArray_long*d,size_t c,long*a){return cutils_cdar_DynamicArray_void_ptr_append(d,c,a);}
bool cutils_cdar_DynamicArray_long_push(cutils_cdar_DynamicArray_long*d,size_t i,size_t c,long*a){return cutils_cdar_DynamicArray_void_ptr_push(d,i,c,a);}
bool cutils_cdar_DynamicArray_long_set(cutils_cdar_DynamicArray_long*d,size_t i,size_t c,long*s){return cutils_cdar_DynamicArray_void_ptr_set(d,i,c,s);}
size_t cutils_cdar_DynamicArray_long_pop(cutils_cdar_DynamicArray_long*d,size_t i,size_t c,long*a){return cutils_cdar_DynamicArray_void_ptr_pop(d,i,c,a);}
size_t cutils_cdar_DynamicArray_long_sub(cutils_cdar_DynamicArray_long*d,size_t i,size_t c,long*a){return cutils_cdar_DynamicArray_void_ptr_sub(d,i,c,a);}
long cutils_cdar_DynamicArray_long_get(cutils_cdar_DynamicArray_long*d,size_t i){return *(long*)cutils_cdar_DynamicArray_void_ptr_get(d,i);}
bool cutils_cdar_DynamicArray_long_find(cutils_cdar_DynamicArray_long*d,const long*p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_find(d,p,i);}
size_t cutils_cdar_DynamicArray_long_findall(cutils_cdar_DynamicArray_long*d,const long*p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_findall(d,p,i);}
void(*cutils_cdar_DynamicArray_long_del)(cutils_cdar_DynamicArray_long*)=cutils_cdar_DynamicArray_void_ptr_del;
size_t(*cutils_cdar_DynamicArray_long_len)(cutils_cdar_DynamicArray_long*)=cutils_cdar_DynamicArray_void_ptr_len;
size_t(*cutils_cdar_DynamicArray_long_size)(cutils_cdar_DynamicArray_long*)=cutils_cdar_DynamicArray_void_ptr_size;
bool(*cutils_cdar_DynamicArray_long_resize)(cutils_cdar_DynamicArray_long*,size_t)=cutils_cdar_DynamicArray_void_ptr_resize;
bool(*cutils_cdar_DynamicArray_long_swap)(cutils_cdar_DynamicArray_long*,size_t,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_swap;
bool(*cutils_cdar_DynamicArray_long_reverse)(cutils_cdar_DynamicArray_long*)=cutils_cdar_DynamicArray_void_ptr_reverse;
size_t(*cutils_cdar_DynamicArray_long_pull)(cutils_cdar_DynamicArray_long*,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_pull;
void(*cutils_cdar_DynamicArray_long_truncate)(cutils_cdar_DynamicArray_long*,size_t)=cutils_cdar_DynamicArray_void_ptr_truncate;
void(*cutils_cdar_DynamicArray_long_clear)(cutils_cdar_DynamicArray_long*)=cutils_cdar_DynamicArray_void_ptr_clear;
/*----------------------------------------------------------------------------*/
typedef cutils_cdar_DynamicArray_void_ptr cutils_cdar_DynamicArray_unsigned_long;
bool cutils_cdar_DynamicArray_unsigned_long_new(cutils_cdar_DynamicArray_unsigned_long**d,size_t c,unsigned long*a){return cutils_cdar_DynamicArray_void_ptr_new(d,c,sizeof(unsigned long),a);}
unsigned long* cutils_cdar_DynamicArray_unsigned_long_data(cutils_cdar_DynamicArray_unsigned_long*d,size_t*s,size_t*c){return cutils_cdar_DynamicArray_void_ptr_data(d,s,c);}
unsigned long* cutils_cdar_DynamicArray_unsigned_long_raw(cutils_cdar_DynamicArray_unsigned_long*d){return (unsigned long*)cutils_cdar_DynamicArray_void_ptr_raw(d);}
bool cutils_cdar_DynamicArray_unsigned_long_append(cutils_cdar_DynamicArray_unsigned_long*d,size_t c,unsigned long*a){return cutils_cdar_DynamicArray_void_ptr_append(d,c,a);}
bool cutils_cdar_DynamicArray_unsigned_long_push(cutils_cdar_DynamicArray_unsigned_long*d,size_t i,size_t c,unsigned long*a){return cutils_cdar_DynamicArray_void_ptr_push(d,i,c,a);}
bool cutils_cdar_DynamicArray_unsigned_long_set(cutils_cdar_DynamicArray_unsigned_long*d,size_t i,size_t c,unsigned long*s){return cutils_cdar_DynamicArray_void_ptr_set(d,i,c,s);}
size_t cutils_cdar_DynamicArray_unsigned_long_pop(cutils_cdar_DynamicArray_unsigned_long*d,size_t i,size_t c,unsigned long*a){return cutils_cdar_DynamicArray_void_ptr_pop(d,i,c,a);}
size_t cutils_cdar_DynamicArray_unsigned_long_sub(cutils_cdar_DynamicArray_unsigned_long*d,size_t i,size_t c,unsigned long*a){return cutils_cdar_DynamicArray_void_ptr_sub(d,i,c,a);}
unsigned long cutils_cdar_DynamicArray_unsigned_long_get(cutils_cdar_DynamicArray_unsigned_long*d,size_t i){return *(unsigned long*)cutils_cdar_DynamicArray_void_ptr_get(d,i);}
bool cutils_cdar_DynamicArray_unsigned_long_find(cutils_cdar_DynamicArray_unsigned_long*d,const unsigned long*p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_find(d,p,i);}
size_t cutils_cdar_DynamicArray_unsigned_long_findall(cutils_cdar_DynamicArray_unsigned_long*d,const unsigned long*p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_findall(d,p,i);}
void(*cutils_cdar_DynamicArray_unsigned_long_del)(cutils_cdar_DynamicArray_unsigned_long*)=cutils_cdar_DynamicArray_void_ptr_del;
size_t(*cutils_cdar_DynamicArray_unsigned_long_len)(cutils_cdar_DynamicArray_unsigned_long*)=cutils_cdar_DynamicArray_void_ptr_len;
size_t(*cutils_cdar_DynamicArray_unsigned_long_size)(cutils_cdar_DynamicArray_unsigned_long*)=cutils_cdar_DynamicArray_void_ptr_size;
bool(*cutils_cdar_DynamicArray_unsigned_long_resize)(cutils_cdar_DynamicArray_unsigned_long*,size_t)=cutils_cdar_DynamicArray_void_ptr_resize;
bool(*cutils_cdar_DynamicArray_unsigned_long_swap)(cutils_cdar_DynamicArray_unsigned_long*,size_t,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_swap;
bool(*cutils_cdar_DynamicArray_unsigned_long_reverse)(cutils_cdar_DynamicArray_unsigned_long*)=cutils_cdar_DynamicArray_void_ptr_reverse;
size_t(*cutils_cdar_DynamicArray_unsigned_long_pull)(cutils_cdar_DynamicArray_unsigned_long*,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_pull;
void(*cutils_cdar_DynamicArray_unsigned_long_truncate)(cutils_cdar_DynamicArray_unsigned_long*,size_t)=cutils_cdar_DynamicArray_void_ptr_truncate;
void(*cutils_cdar_DynamicArray_unsigned_long_clear)(cutils_cdar_DynamicArray_unsigned_long*)=cutils_cdar_DynamicArray_void_ptr_clear;
/*----------------------------------------------------------------------------*/
typedef cutils_cdar_DynamicArray_void_ptr cutils_cdar_DynamicArray_long_long;
bool cutils_cdar_DynamicArray_long_long_new(cutils_cdar_DynamicArray_long_long**d,size_t c,long long*a){return cutils_cdar_DynamicArray_void_ptr_new(d,c,sizeof(long long),a);}
long long* cutils_cdar_DynamicArray_long_long_data(cutils_cdar_DynamicArray_long_long*d,size_t*s,size_t*c){return cutils_cdar_DynamicArray_void_ptr_data(d,s,c);}
long long* cutils_cdar_DynamicArray_long_long_raw(cutils_cdar_DynamicArray_long_long*d){return (long long*)cutils_cdar_DynamicArray_void_ptr_raw(d);}
bool cutils_cdar_DynamicArray_long_long_append(cutils_cdar_DynamicArray_long_long*d,size_t c,long long*a){return cutils_cdar_DynamicArray_void_ptr_append(d,c,a);}
bool cutils_cdar_DynamicArray_long_long_push(cutils_cdar_DynamicArray_long_long*d,size_t i,size_t c,long long*a){return cutils_cdar_DynamicArray_void_ptr_push(d,i,c,a);}
bool cutils_cdar_DynamicArray_long_long_set(cutils_cdar_DynamicArray_long_long*d,size_t i,size_t c,long long*s){return cutils_cdar_DynamicArray_void_ptr_set(d,i,c,s);}
size_t cutils_cdar_DynamicArray_long_long_pop(cutils_cdar_DynamicArray_long_long*d,size_t i,size_t c,long long*a){return cutils_cdar_DynamicArray_void_ptr_pop(d,i,c,a);}
size_t cutils_cdar_DynamicArray_long_long_sub(cutils_cdar_DynamicArray_long_long*d,size_t i,size_t c,long long*a){return cutils_cdar_DynamicArray_void_ptr_sub(d,i,c,a);}
long long cutils_cdar_DynamicArray_long_long_get(cutils_cdar_DynamicArray_long_long*d,size_t i){return *(long long*)cutils_cdar_DynamicArray_void_ptr_get(d,i);}
bool cutils_cdar_DynamicArray_long_long_find(cutils_cdar_DynamicArray_long_long*d,const long long*p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_find(d,p,i);}
size_t cutils_cdar_DynamicArray_long_long_findall(cutils_cdar_DynamicArray_long_long*d,const long long*p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_findall(d,p,i);}
void(*cutils_cdar_DynamicArray_long_long_del)(cutils_cdar_DynamicArray_long_long*)=cutils_cdar_DynamicArray_void_ptr_del;
size_t(*cutils_cdar_DynamicArray_long_long_len)(cutils_cdar_DynamicArray_long_long*)=cutils_cdar_DynamicArray_void_ptr_len;
size_t(*cutils_cdar_DynamicArray_long_long_size)(cutils_cdar_DynamicArray_long_long*)=cutils_cdar_DynamicArray_void_ptr_size;
bool(*cutils_cdar_DynamicArray_long_long_resize)(cutils_cdar_DynamicArray_long_long*,size_t)=cutils_cdar_DynamicArray_void_ptr_resize;
bool(*cutils_cdar_DynamicArray_long_long_swap)(cutils_cdar_DynamicArray_long_long*,size_t,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_swap;
bool(*cutils_cdar_DynamicArray_long_long_reverse)(cutils_cdar_DynamicArray_long_long*)=cutils_cdar_DynamicArray_void_ptr_reverse;
size_t(*cutils_cdar_DynamicArray_long_long_pull)(cutils_cdar_DynamicArray_long_long*,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_pull;
void(*cutils_cdar_DynamicArray_long_long_truncate)(cutils_cdar_DynamicArray_long_long*,size_t)=cutils_cdar_DynamicArray_void_ptr_truncate;
void(*cutils_cdar_DynamicArray_long_long_clear)(cutils_cdar_DynamicArray_long_long*)=cutils_cdar_DynamicArray_void_ptr_clear;
/*----------------------------------------------------------------------------*/
typedef cutils_cdar_DynamicArray_void_ptr cutils_cdar_DynamicArray_unsigned_long_long;
bool cutils_cdar_DynamicArray_unsigned_long_long_new(cutils_cdar_DynamicArray_unsigned_long_long**d,size_t c,unsigned long long*a){return cutils_cdar_DynamicArray_void_ptr_new(d,c,sizeof(unsigned long long),a);}
unsigned long long* cutils_cdar_DynamicArray_unsigned_long_long_data(cutils_cdar_DynamicArray_unsigned_long_long*d,size_t*s,size_t*c){return cutils_cdar_DynamicArray_void_ptr_data(d,s,c);}
unsigned long long* cutils_cdar_DynamicArray_unsigned_long_long_raw(cutils_cdar_DynamicArray_unsigned_long_long*d){return (unsigned long long*)cutils_cdar_DynamicArray_void_ptr_raw(d);}
bool cutils_cdar_DynamicArray_unsigned_long_long_append(cutils_cdar_DynamicArray_unsigned_long_long*d,size_t c,unsigned long long*a){return cutils_cdar_DynamicArray_void_ptr_append(d,c,a);}
bool cutils_cdar_DynamicArray_unsigned_long_long_push(cutils_cdar_DynamicArray_unsigned_long_long*d,size_t i,size_t c,unsigned long long*a){return cutils_cdar_DynamicArray_void_ptr_push(d,i,c,a);}
bool cutils_cdar_DynamicArray_unsigned_long_long_set(cutils_cdar_DynamicArray_unsigned_long_long*d,size_t i,size_t c,unsigned long long*s){return cutils_cdar_DynamicArray_void_ptr_set(d,i,c,s);}
size_t cutils_cdar_DynamicArray_unsigned_long_long_pop(cutils_cdar_DynamicArray_unsigned_long_long*d,size_t i,size_t c,unsigned long long*a){return cutils_cdar_DynamicArray_void_ptr_pop(d,i,c,a);}
size_t cutils_cdar_DynamicArray_unsigned_long_long_sub(cutils_cdar_DynamicArray_unsigned_long_long*d,size_t i,size_t c,unsigned long long*a){return cutils_cdar_DynamicArray_void_ptr_sub(d,i,c,a);}
unsigned long long cutils_cdar_DynamicArray_unsigned_long_long_get(cutils_cdar_DynamicArray_unsigned_long_long*d,size_t i){return *(unsigned long long*)cutils_cdar_DynamicArray_void_ptr_get(d,i);}
bool cutils_cdar_DynamicArray_unsigned_long_long_find(cutils_cdar_DynamicArray_unsigned_long_long*d,const unsigned long long*p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_find(d,p,i);}
size_t cutils_cdar_DynamicArray_unsigned_long_long_findall(cutils_cdar_DynamicArray_unsigned_long_long*d,const unsigned long long*p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_findall(d,p,i);}
void(*cutils_cdar_DynamicArray_unsigned_long_long_del)(cutils_cdar_DynamicArray_unsigned_long_long*)=cutils_cdar_DynamicArray_void_ptr_del;
size_t(*cutils_cdar_DynamicArray_unsigned_long_long_len)(cutils_cdar_DynamicArray_unsigned_long_long*)=cutils_cdar_DynamicArray_void_ptr_len;
size_t(*cutils_cdar_DynamicArray_unsigned_long_long_size)(cutils_cdar_DynamicArray_unsigned_long_long*)=cutils_cdar_DynamicArray_void_ptr_size;
bool(*cutils_cdar_DynamicArray_unsigned_long_long_resize)(cutils_cdar_DynamicArray_unsigned_long_long*,size_t)=cutils_cdar_DynamicArray_void_ptr_resize;
bool(*cutils_cdar_DynamicArray_unsigned_long_long_swap)(cutils_cdar_DynamicArray_unsigned_long_long*,size_t,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_swap;
bool(*cutils_cdar_DynamicArray_unsigned_long_long_reverse)(cutils_cdar_DynamicArray_unsigned_long_long*)=cutils_cdar_DynamicArray_void_ptr_reverse;
size_t(*cutils_cdar_DynamicArray_unsigned_long_long_pull)(cutils_cdar_DynamicArray_unsigned_long_long*,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_pull;
void(*cutils_cdar_DynamicArray_unsigned_long_long_truncate)(cutils_cdar_DynamicArray_unsigned_long_long*,size_t)=cutils_cdar_DynamicArray_void_ptr_truncate;
void(*cutils_cdar_DynamicArray_unsigned_long_long_clear)(cutils_cdar_DynamicArray_unsigned_long_long*)=cutils_cdar_DynamicArray_void_ptr_clear;
/*----------------------------------------------------------------------------*/
typedef cutils_cdar_DynamicArray_void_ptr cutils_cdar_DynamicArray_float;
bool cutils_cdar_DynamicArray_float_new(cutils_cdar_DynamicArray_float**d,size_t c,float*a){return cutils_cdar_DynamicArray_void_ptr_new(d,c,sizeof(float),a);}
float* cutils_cdar_DynamicArray_float_data(cutils_cdar_DynamicArray_float*d,size_t*s,size_t*c){return cutils_cdar_DynamicArray_void_ptr_data(d,s,c);}
float* cutils_cdar_DynamicArray_float_raw(cutils_cdar_DynamicArray_float*d){return (float*)cutils_cdar_DynamicArray_void_ptr_raw(d);}
bool cutils_cdar_DynamicArray_float_append(cutils_cdar_DynamicArray_float*d,size_t c,float*a){return cutils_cdar_DynamicArray_void_ptr_append(d,c,a);}
bool cutils_cdar_DynamicArray_float_push(cutils_cdar_DynamicArray_float*d,size_t i,size_t c,float*a){return cutils_cdar_DynamicArray_void_ptr_push(d,i,c,a);}
bool cutils_cdar_DynamicArray_float_set(cutils_cdar_DynamicArray_float*d,size_t i,size_t c,float*s){return cutils_cdar_DynamicArray_void_ptr_set(d,i,c,s);}
size_t cutils_cdar_DynamicArray_float_pop(cutils_cdar_DynamicArray_float*d,size_t i,size_t c,float*a){return cutils_cdar_DynamicArray_void_ptr_pop(d,i,c,a);}
size_t cutils_cdar_DynamicArray_float_sub(cutils_cdar_DynamicArray_float*d,size_t i,size_t c,float*a){return cutils_cdar_DynamicArray_void_ptr_sub(d,i,c,a);}
float cutils_cdar_DynamicArray_float_get(cutils_cdar_DynamicArray_float*d,size_t i){return *(float*)cutils_cdar_DynamicArray_void_ptr_get(d,i);}
bool cutils_cdar_DynamicArray_float_find(cutils_cdar_DynamicArray_float*d,const float*p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_find(d,p,i);}
size_t cutils_cdar_DynamicArray_float_findall(cutils_cdar_DynamicArray_float*d,const float*p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_findall(d,p,i);}
void(*cutils_cdar_DynamicArray_float_del)(cutils_cdar_DynamicArray_float*)=cutils_cdar_DynamicArray_void_ptr_del;
size_t(*cutils_cdar_DynamicArray_float_len)(cutils_cdar_DynamicArray_float*)=cutils_cdar_DynamicArray_void_ptr_len;
size_t(*cutils_cdar_DynamicArray_float_size)(cutils_cdar_DynamicArray_float*)=cutils_cdar_DynamicArray_void_ptr_size;
bool(*cutils_cdar_DynamicArray_float_resize)(cutils_cdar_DynamicArray_float*,size_t)=cutils_cdar_DynamicArray_void_ptr_resize;
bool(*cutils_cdar_DynamicArray_float_swap)(cutils_cdar_DynamicArray_float*,size_t,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_swap;
bool(*cutils_cdar_DynamicArray_float_reverse)(cutils_cdar_DynamicArray_float*)=cutils_cdar_DynamicArray_void_ptr_reverse;
size_t(*cutils_cdar_DynamicArray_float_pull)(cutils_cdar_DynamicArray_float*,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_pull;
void(*cutils_cdar_DynamicArray_float_truncate)(cutils_cdar_DynamicArray_float*,size_t)=cutils_cdar_DynamicArray_void_ptr_truncate;
void(*cutils_cdar_DynamicArray_float_clear)(cutils_cdar_DynamicArray_float*)=cutils_cdar_DynamicArray_void_ptr_clear;
/*----------------------------------------------------------------------------*/
typedef cutils_cdar_DynamicArray_void_ptr cutils_cdar_DynamicArray_double;
bool cutils_cdar_DynamicArray_double_new(cutils_cdar_DynamicArray_double**d,size_t c,double*a){return cutils_cdar_DynamicArray_void_ptr_new(d,c,sizeof(double),a);}
double* cutils_cdar_DynamicArray_double_data(cutils_cdar_DynamicArray_double*d,size_t*s,size_t*c){return cutils_cdar_DynamicArray_void_ptr_data(d,s,c);}
double* cutils_cdar_DynamicArray_double_raw(cutils_cdar_DynamicArray_double*d){return (double*)cutils_cdar_DynamicArray_void_ptr_raw(d);}
bool cutils_cdar_DynamicArray_double_append(cutils_cdar_DynamicArray_double*d,size_t c,double*a){return cutils_cdar_DynamicArray_void_ptr_append(d,c,a);}
bool cutils_cdar_DynamicArray_double_push(cutils_cdar_DynamicArray_double*d,size_t i,size_t c,double*a){return cutils_cdar_DynamicArray_void_ptr_push(d,i,c,a);}
bool cutils_cdar_DynamicArray_double_set(cutils_cdar_DynamicArray_double*d,size_t i,size_t c,double*s){return cutils_cdar_DynamicArray_void_ptr_set(d,i,c,s);}
size_t cutils_cdar_DynamicArray_double_pop(cutils_cdar_DynamicArray_double*d,size_t i,size_t c,double*a){return cutils_cdar_DynamicArray_void_ptr_pop(d,i,c,a);}
size_t cutils_cdar_DynamicArray_double_sub(cutils_cdar_DynamicArray_double*d,size_t i,size_t c,double*a){return cutils_cdar_DynamicArray_void_ptr_sub(d,i,c,a);}
double cutils_cdar_DynamicArray_double_get(cutils_cdar_DynamicArray_double*d,size_t i){return *(double*)cutils_cdar_DynamicArray_void_ptr_get(d,i);}
bool cutils_cdar_DynamicArray_double_find(cutils_cdar_DynamicArray_double*d,const double*p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_find(d,p,i);}
size_t cutils_cdar_DynamicArray_double_findall(cutils_cdar_DynamicArray_double*d,const double*p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_findall(d,p,i);}
void(*cutils_cdar_DynamicArray_double_del)(cutils_cdar_DynamicArray_double*)=cutils_cdar_DynamicArray_void_ptr_del;
size_t(*cutils_cdar_DynamicArray_double_len)(cutils_cdar_DynamicArray_double*)=cutils_cdar_DynamicArray_void_ptr_len;
size_t(*cutils_cdar_DynamicArray_double_size)(cutils_cdar_DynamicArray_double*)=cutils_cdar_DynamicArray_void_ptr_size;
bool(*cutils_cdar_DynamicArray_double_resize)(cutils_cdar_DynamicArray_double*,size_t)=cutils_cdar_DynamicArray_void_ptr_resize;
bool(*cutils_cdar_DynamicArray_double_swap)(cutils_cdar_DynamicArray_double*,size_t,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_swap;
bool(*cutils_cdar_DynamicArray_double_reverse)(cutils_cdar_DynamicArray_double*)=cutils_cdar_DynamicArray_void_ptr_reverse;
size_t(*cutils_cdar_DynamicArray_double_pull)(cutils_cdar_DynamicArray_double*,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_pull;
void(*cutils_cdar_DynamicArray_double_truncate)(cutils_cdar_DynamicArray_double*,size_t)=cutils_cdar_DynamicArray_void_ptr_truncate;
void(*cutils_cdar_DynamicArray_double_clear)(cutils_cdar_DynamicArray_double*)=cutils_cdar_DynamicArray_void_ptr_clear;
/*----------------------------------------------------------------------------*/
typedef cutils_cdar_DynamicArray_void_ptr cutils_cdar_DynamicArray_long_double;
bool cutils_cdar_DynamicArray_long_double_new(cutils_cdar_DynamicArray_long_double**d,size_t c,long double*a){return cutils_cdar_DynamicArray_void_ptr_new(d,c,sizeof(long double),a);}
long double* cutils_cdar_DynamicArray_long_double_data(cutils_cdar_DynamicArray_long_double*d,size_t*s,size_t*c){return cutils_cdar_DynamicArray_void_ptr_data(d,s,c);}
long double* cutils_cdar_DynamicArray_long_double_raw(cutils_cdar_DynamicArray_long_double*d){return (long double*)cutils_cdar_DynamicArray_void_ptr_raw(d);}
bool cutils_cdar_DynamicArray_long_double_append(cutils_cdar_DynamicArray_long_double*d,size_t c,long double*a){return cutils_cdar_DynamicArray_void_ptr_append(d,c,a);}
bool cutils_cdar_DynamicArray_long_double_push(cutils_cdar_DynamicArray_long_double*d,size_t i,size_t c,long double*a){return cutils_cdar_DynamicArray_void_ptr_push(d,i,c,a);}
bool cutils_cdar_DynamicArray_long_double_set(cutils_cdar_DynamicArray_long_double*d,size_t i,size_t c,long double*s){return cutils_cdar_DynamicArray_void_ptr_set(d,i,c,s);}
size_t cutils_cdar_DynamicArray_long_double_pop(cutils_cdar_DynamicArray_long_double*d,size_t i,size_t c,long double*a){return cutils_cdar_DynamicArray_void_ptr_pop(d,i,c,a);}
size_t cutils_cdar_DynamicArray_long_double_sub(cutils_cdar_DynamicArray_long_double*d,size_t i,size_t c,long double*a){return cutils_cdar_DynamicArray_void_ptr_sub(d,i,c,a);}
long double cutils_cdar_DynamicArray_long_double_get(cutils_cdar_DynamicArray_long_double*d,size_t i){return *(long double*)cutils_cdar_DynamicArray_void_ptr_get(d,i);}
bool cutils_cdar_DynamicArray_long_double_find(cutils_cdar_DynamicArray_long_double*d,const long double*p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_find(d,p,i);}
size_t cutils_cdar_DynamicArray_long_double_findall(cutils_cdar_DynamicArray_long_double*d,const long double*p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_findall(d,p,i);}
void(*cutils_cdar_DynamicArray_long_double_del)(cutils_cdar_DynamicArray_long_double*)=cutils_cdar_DynamicArray_void_ptr_del;
size_t(*cutils_cdar_DynamicArray_long_double_len)(cutils_cdar_DynamicArray_long_double*)=cutils_cdar_DynamicArray_void_ptr_len;
size_t(*cutils_cdar_DynamicArray_long_double_size)(cutils_cdar_DynamicArray_long_double*)=cutils_cdar_DynamicArray_void_ptr_size;
bool(*cutils_cdar_DynamicArray_long_double_resize)(cutils_cdar_DynamicArray_long_double*,size_t)=cutils_cdar_DynamicArray_void_ptr_resize;
bool(*cutils_cdar_DynamicArray_long_double_swap)(cutils_cdar_DynamicArray_long_double*,size_t,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_swap;
bool(*cutils_cdar_DynamicArray_long_double_reverse)(cutils_cdar_DynamicArray_long_double*)=cutils_cdar_DynamicArray_void_ptr_reverse;
size_t(*cutils_cdar_DynamicArray_long_double_pull)(cutils_cdar_DynamicArray_long_double*,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_pull;
void(*cutils_cdar_DynamicArray_long_double_truncate)(cutils_cdar_DynamicArray_long_double*,size_t)=cutils_cdar_DynamicArray_void_ptr_truncate;
void(*cutils_cdar_DynamicArray_long_double_clear)(cutils_cdar_DynamicArray_long_double*)=cutils_cdar_DynamicArray_void_ptr_clear;
/*----------------------------------------------------------------------------*/
typedef cutils_cdar_DynamicArray_void_ptr cutils_cdar_DynamicArray_bool;
bool cutils_cdar_DynamicArray_bool_new(cutils_cdar_DynamicArray_bool**d,size_t c,bool*a){return cutils_cdar_DynamicArray_void_ptr_new(d,c,sizeof(bool),a);}
bool* cutils_cdar_DynamicArray_bool_data(cutils_cdar_DynamicArray_bool*d,size_t*s,size_t*c){return cutils_cdar_DynamicArray_void_ptr_data(d,s,c);}
bool* cutils_cdar_DynamicArray_bool_raw(cutils_cdar_DynamicArray_bool*d){return (bool*)cutils_cdar_DynamicArray_void_ptr_raw(d);}
bool cutils_cdar_DynamicArray_bool_append(cutils_cdar_DynamicArray_bool*d,size_t c,bool*a){return cutils_cdar_DynamicArray_void_ptr_append(d,c,a);}
bool cutils_cdar_DynamicArray_bool_push(cutils_cdar_DynamicArray_bool*d,size_t i,size_t c,bool*a){return cutils_cdar_DynamicArray_void_ptr_push(d,i,c,a);}
bool cutils_cdar_DynamicArray_bool_set(cutils_cdar_DynamicArray_bool*d,size_t i,size_t c,bool*s){return cutils_cdar_DynamicArray_void_ptr_set(d,i,c,s);}
size_t cutils_cdar_DynamicArray_bool_pop(cutils_cdar_DynamicArray_bool*d,size_t i,size_t c,bool*a){return cutils_cdar_DynamicArray_void_ptr_pop(d,i,c,a);}
size_t cutils_cdar_DynamicArray_bool_sub(cutils_cdar_DynamicArray_bool*d,size_t i,size_t c,bool*a){return cutils_cdar_DynamicArray_void_ptr_sub(d,i,c,a);}
bool cutils_cdar_DynamicArray_bool_get(cutils_cdar_DynamicArray_bool*d,size_t i){return *(bool*)cutils_cdar_DynamicArray_void_ptr_get(d,i);}
bool cutils_cdar_DynamicArray_bool_find(cutils_cdar_DynamicArray_bool*d,const bool*p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_find(d,p,i);}
size_t cutils_cdar_DynamicArray_bool_findall(cutils_cdar_DynamicArray_bool*d,const bool*p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_findall(d,p,i);}
void(*cutils_cdar_DynamicArray_bool_del)(cutils_cdar_DynamicArray_bool*)=cutils_cdar_DynamicArray_void_ptr_del;
size_t(*cutils_cdar_DynamicArray_bool_len)(cutils_cdar_DynamicArray_bool*)=cutils_cdar_DynamicArray_void_ptr_len;
size_t(*cutils_cdar_DynamicArray_bool_size)(cutils_cdar_DynamicArray_bool*)=cutils_cdar_DynamicArray_void_ptr_size;
bool(*cutils_cdar_DynamicArray_bool_resize)(cutils_cdar_DynamicArray_bool*,size_t)=cutils_cdar_DynamicArray_void_ptr_resize;
bool(*cutils_cdar_DynamicArray_bool_swap)(cutils_cdar_DynamicArray_bool*,size_t,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_swap;
bool(*cutils_cdar_DynamicArray_bool_reverse)(cutils_cdar_DynamicArray_bool*)=cutils_cdar_DynamicArray_void_ptr_reverse;
size_t(*cutils_cdar_DynamicArray_bool_pull)(cutils_cdar_DynamicArray_bool*,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_pull;
void(*cutils_cdar_DynamicArray_bool_truncate)(cutils_cdar_DynamicArray_bool*,size_t)=cutils_cdar_DynamicArray_void_ptr_truncate;
void(*cutils_cdar_DynamicArray_bool_clear)(cutils_cdar_DynamicArray_bool*)=cutils_cdar_DynamicArray_void_ptr_clear;
/*----------------------------------------------------------------------------*/
typedef cutils_cdar_DynamicArray_void_ptr cutils_cdar_DynamicArray_size_t;
bool cutils_cdar_DynamicArray_size_t_new(cutils_cdar_DynamicArray_size_t**d,size_t c,size_t*a){return cutils_cdar_DynamicArray_void_ptr_new(d,c,sizeof(size_t),a);}
size_t* cutils_cdar_DynamicArray_size_t_data(cutils_cdar_DynamicArray_size_t*d,size_t*s,size_t*c){return cutils_cdar_DynamicArray_void_ptr_data(d,s,c);}
size_t* cutils_cdar_DynamicArray_size_t_raw(cutils_cdar_DynamicArray_size_t*d){return (size_t*)cutils_cdar_DynamicArray_void_ptr_raw(d);}
bool cutils_cdar_DynamicArray_size_t_append(cutils_cdar_DynamicArray_size_t*d,size_t c,size_t*a){return cutils_cdar_DynamicArray_void_ptr_append(d,c,a);}
bool cutils_cdar_DynamicArray_size_t_push(cutils_cdar_DynamicArray_size_t*d,size_t i,size_t c,size_t*a){return cutils_cdar_DynamicArray_void_ptr_push(d,i,c,a);}
bool cutils_cdar_DynamicArray_size_t_set(cutils_cdar_DynamicArray_size_t*d,size_t i,size_t c,size_t*s){return cutils_cdar_DynamicArray_void_ptr_set(d,i,c,s);}
size_t cutils_cdar_DynamicArray_size_t_pop(cutils_cdar_DynamicArray_size_t*d,size_t i,size_t c,size_t*a){return cutils_cdar_DynamicArray_void_ptr_pop(d,i,c,a);}
size_t cutils_cdar_DynamicArray_size_t_sub(cutils_cdar_DynamicArray_size_t*d,size_t i,size_t c,size_t*a){return cutils_cdar_DynamicArray_void_ptr_sub(d,i,c,a);}
size_t cutils_cdar_DynamicArray_size_t_get(cutils_cdar_DynamicArray_size_t*d,size_t i){return *(size_t*)cutils_cdar_DynamicArray_void_ptr_get(d,i);}
bool cutils_cdar_DynamicArray_size_t_find(cutils_cdar_DynamicArray_size_t*d,const size_t*p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_find(d,p,i);}
size_t cutils_cdar_DynamicArray_size_t_findall(cutils_cdar_DynamicArray_size_t*d,const size_t*p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_findall(d,p,i);}
void(*cutils_cdar_DynamicArray_size_t_del)(cutils_cdar_DynamicArray_size_t*)=cutils_cdar_DynamicArray_void_ptr_del;
size_t(*cutils_cdar_DynamicArray_size_t_len)(cutils_cdar_DynamicArray_size_t*)=cutils_cdar_DynamicArray_void_ptr_len;
size_t(*cutils_cdar_DynamicArray_size_t_size)(cutils_cdar_DynamicArray_size_t*)=cutils_cdar_DynamicArray_void_ptr_size;
bool(*cutils_cdar_DynamicArray_size_t_resize)(cutils_cdar_DynamicArray_size_t*,size_t)=cutils_cdar_DynamicArray_void_ptr_resize;
bool(*cutils_cdar_DynamicArray_size_t_swap)(cutils_cdar_DynamicArray_size_t*,size_t,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_swap;
bool(*cutils_cdar_DynamicArray_size_t_reverse)(cutils_cdar_DynamicArray_size_t*)=cutils_cdar_DynamicArray_void_ptr_reverse;
size_t(*cutils_cdar_DynamicArray_size_t_pull)(cutils_cdar_DynamicArray_size_t*,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_pull;
void(*cutils_cdar_DynamicArray_size_t_truncate)(cutils_cdar_DynamicArray_size_t*,size_t)=cutils_cdar_DynamicArray_void_ptr_truncate;
void(*cutils_cdar_DynamicArray_size_t_clear)(cutils_cdar_DynamicArray_size_t*)=cutils_cdar_DynamicArray_void_ptr_clear;
/*----------------------------------------------------------------------------*/
typedef cutils_cdar_DynamicArray_void_ptr cutils_cdar_DynamicArray_ptrdiff_t;
bool cutils_cdar_DynamicArray_ptrdiff_t_new(cutils_cdar_DynamicArray_ptrdiff_t**d,size_t c,ptrdiff_t*a){return cutils_cdar_DynamicArray_void_ptr_new(d,c,sizeof(ptrdiff_t),a);}
ptrdiff_t* cutils_cdar_DynamicArray_ptrdiff_t_data(cutils_cdar_DynamicArray_ptrdiff_t*d,size_t*s,size_t*c){return cutils_cdar_DynamicArray_void_ptr_data(d,s,c);}
ptrdiff_t* cutils_cdar_DynamicArray_ptrdiff_t_raw(cutils_cdar_DynamicArray_ptrdiff_t*d){return (ptrdiff_t*)cutils_cdar_DynamicArray_void_ptr_raw(d);}
bool cutils_cdar_DynamicArray_ptrdiff_t_append(cutils_cdar_DynamicArray_ptrdiff_t*d,size_t c,ptrdiff_t*a){return cutils_cdar_DynamicArray_void_ptr_append(d,c,a);}
bool cutils_cdar_DynamicArray_ptrdiff_t_push(cutils_cdar_DynamicArray_ptrdiff_t*d,size_t i,size_t c,ptrdiff_t*a){return cutils_cdar_DynamicArray_void_ptr_push(d,i,c,a);}
bool cutils_cdar_DynamicArray_ptrdiff_t_set(cutils_cdar_DynamicArray_ptrdiff_t*d,size_t i,size_t c,ptrdiff_t*s){return cutils_cdar_DynamicArray_void_ptr_set(d,i,c,s);}
size_t cutils_cdar_DynamicArray_ptrdiff_t_pop(cutils_cdar_DynamicArray_ptrdiff_t*d,size_t i,size_t c,ptrdiff_t*a){return cutils_cdar_DynamicArray_void_ptr_pop(d,i,c,a);}
size_t cutils_cdar_DynamicArray_ptrdiff_t_sub(cutils_cdar_DynamicArray_ptrdiff_t*d,size_t i,size_t c,ptrdiff_t*a){return cutils_cdar_DynamicArray_void_ptr_sub(d,i,c,a);}
ptrdiff_t cutils_cdar_DynamicArray_ptrdiff_t_get(cutils_cdar_DynamicArray_ptrdiff_t*d,size_t i){return *(ptrdiff_t*)cutils_cdar_DynamicArray_void_ptr_get(d,i);}
bool cutils_cdar_DynamicArray_ptrdiff_t_find(cutils_cdar_DynamicArray_ptrdiff_t*d,const ptrdiff_t*p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_find(d,p,i);}
size_t cutils_cdar_DynamicArray_ptrdiff_t_findall(cutils_cdar_DynamicArray_ptrdiff_t*d,const ptrdiff_t*p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_findall(d,p,i);}
void(*cutils_cdar_DynamicArray_ptrdiff_t_del)(cutils_cdar_DynamicArray_ptrdiff_t*)=cutils_cdar_DynamicArray_void_ptr_del;
size_t(*cutils_cdar_DynamicArray_ptrdiff_t_len)(cutils_cdar_DynamicArray_ptrdiff_t*)=cutils_cdar_DynamicArray_void_ptr_len;
size_t(*cutils_cdar_DynamicArray_ptrdiff_t_size)(cutils_cdar_DynamicArray_ptrdiff_t*)=cutils_cdar_DynamicArray_void_ptr_size;
bool(*cutils_cdar_DynamicArray_ptrdiff_t_resize)(cutils_cdar_DynamicArray_ptrdiff_t*,size_t)=cutils_cdar_DynamicArray_void_ptr_resize;
bool(*cutils_cdar_DynamicArray_ptrdiff_t_swap)(cutils_cdar_DynamicArray_ptrdiff_t*,size_t,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_swap;
bool(*cutils_cdar_DynamicArray_ptrdiff_t_reverse)(cutils_cdar_DynamicArray_ptrdiff_t*)=cutils_cdar_DynamicArray_void_ptr_reverse;
size_t(*cutils_cdar_DynamicArray_ptrdiff_t_pull)(cutils_cdar_DynamicArray_ptrdiff_t*,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_pull;
void(*cutils_cdar_DynamicArray_ptrdiff_t_truncate)(cutils_cdar_DynamicArray_ptrdiff_t*,size_t)=cutils_cdar_DynamicArray_void_ptr_truncate;
void(*cutils_cdar_DynamicArray_ptrdiff_t_clear)(cutils_cdar_DynamicArray_ptrdiff_t*)=cutils_cdar_DynamicArray_void_ptr_clear;