/* INFO ************************************************************************
**                                                                            **
**                                   cutils                                   **
**                                   ======                                   **
**                                                                            **
**                     Modern and Lightweight C Utilities                     **
**                       Version: 0.8.90.629 (20140820)                       **
**                                                                            **
**                                File: cdar.c                                **
**                                                                            **
**           Designed and written by Peter Varo. Copyright (c) 2014           **
**             License agreement is provided in the LICENSE file              **
**                 For more info visit: http://www.cutils.org                 **
**                                                                            **
************************************************************************ INFO */

#include <stddef.h>         /* ptrdiff_t */
#include <string.h>         /* strlen(), strncpy() */
#include "internal/fmtc.h"  /* cutils_fmtc_repr */
#include "internal/fcmp.h"  /* cutils_fcmp_compare */
#include <stdlib.h>   /* malloc(), realloc(), free() */
#ifdef CDAR_JEM
  #include <jemalloc/jemalloc.h>  /* malloc(), realloc(), free() */
#endif

#include <stdio.h>    /* fprintf(), snprintf(), stderr, size_t, FILE */
#include <string.h>   /* memcpy(), strcpy(), strcat() */
#include <stdbool.h>  /* bool, true, false */

/* If 'optimised' or the 'exceptions are not available' */
#if defined CDAR_OPT
  #define cutils_cexc_raise(msg, len)
#else
  #include "cexc.h"
  #include "internal/defs.h"
#endif

/*----------------------------------------------------------------------------*/
/* Exception messages */
#undef  TYPE_REPR
#define TYPE_REPR "DynamicArray"
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
                                      size_t item_size,
                                      size_t count,
                                      void *source)
{
    /* Calculate allocation size based on item count */
    size_t alloc_size = count ? 2 * count : 1;

    /* Allocate space for array data */
    void *data = malloc(alloc_size * item_size);
    if (!data) goto Error_Array_Allocation_Failed;

    /* Allocate space for struct */
    cutils_cdar_DynamicArray_void_ptr *_dynarr =
        malloc(sizeof(cutils_cdar_DynamicArray_void_ptr));
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
        #define EXCEPTION_MSG EXCEPTION_MESSAGE_ALLOC_FAIL(TYPE_REPR, "new")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        #undef EXCEPTION_MSG
        #ifndef CDAR_OPT
        /* Set pointer to array to NULL, so all other methods of
           DynamicArray won't break the code, just raise exceptions */
        *dynarr = NULL;
        #endif
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
        #define EXCEPTION_MSG EXCEPTION_MESSAGE_NULL_POINTER(TYPE_REPR, "data")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        #undef EXCEPTION_MSG
        return NULL; /* Cannot operate on nothing */
    }
    /* Invalid size */
    if (!size)
        #define EXCEPTION_MSG \
            EXCEPTION_MESSAGE_ARGUMENT_NULL(TYPE_REPR, "data", "2nd", size)
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        #undef EXCEPTION_MSG
    else
#endif /* CDAR_OPT */

    /* CORE FUNCTIONALITY */
    *size = dynarr->used*dynarr->size;

#ifndef CDAR_OPT
    /* Invalid count */
    if (!count)
        #define EXCEPTION_MSG \
            EXCEPTION_MESSAGE_ARGUMENT_NULL(TYPE_REPR, "data", "3rd", count)
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
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
        #define EXCEPTION_MSG EXCEPTION_MESSAGE_NULL_POINTER(TYPE_REPR, "raw")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
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
        #define EXCEPTION_MSG EXCEPTION_MESSAGE_NULL_POINTER(TYPE_REPR, "len")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
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
        #define EXCEPTION_MSG EXCEPTION_MESSAGE_NULL_POINTER(TYPE_REPR, "size")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
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
#ifndef CDAR_OPT
    /* Not initialised */
    if (!dynarr)
    {
        #define EXCEPTION_MSG EXCEPTION_MESSAGE_NULL_POINTER(TYPE_REPR, "clear")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
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
        #define EXCEPTION_MSG EXCEPTION_MESSAGE_NULL_POINTER(TYPE_REPR, "resize")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
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
        #define EXCEPTION_MSG EXCEPTION_MESSAGE_REALLOC_FAIL(TYPE_REPR, "resize")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
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
        #define EXCEPTION_MSG EXCEPTION_MESSAGE_NULL_POINTER(TYPE_REPR, "swap")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
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
        #define EXCEPTION_MSG EXCEPTION_MESSAGE_EMPTY(TYPE_REPR, "swap")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        #undef EXCEPTION_MSG
        return true; /* Successfully did nothing */
    }
#ifndef CDAR_OPT
    /* Out of range */
    else if (index1 >= dynarr->used)
    {
        #define EXCEPTION_MSG \
            EXCEPTION_MESSAGE_ARGUMENT_OUTOF(TYPE_REPR, "swap", "2nd", index1)
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        #undef EXCEPTION_MSG
        return false; /* Not valid index */
    }
    /* Out of range */
    else if (index2 >= dynarr->used)
    {
        #define EXCEPTION_MSG \
            EXCEPTION_MESSAGE_ARGUMENT_OUTOF(TYPE_REPR, "swap", "3rd", index2)
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        #undef EXCEPTION_MSG
        return false; /* Not valid index */
    }

    /* TODO: change behaviour: return false, instead of limiting,
             just like in csll; also: correct the documentation */

    /* Sort indices */
    size_t greater, smaller;
    if (index1 > index2) { greater = index1; smaller = index2; }
    else                 { greater = index2; smaller = index1; }

    /* Limit count size, if overlapping */
    if (smaller + count >= greater)
    {
        #define EXCEPTION_MSG EXCEPTION_MESSAGE_OVERLAP(TYPE_REPR, "swap")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        #undef EXCEPTION_MSG
        count = greater - smaller;
    }

    /* Limit count size, if out of range */
    if ((greater + count) > dynarr->used)
    {
        #define EXCEPTION_MSG \
            EXCEPTION_MESSAGE_ARGUMENT_OUTOF(TYPE_REPR, "swap", "4th", count)
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
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
         *item2 = data + index2*item_size;
    char temp[block_size];

    /* Swap elements */
    memcpy(temp,  item1, block_size);
    memcpy(item1, item2, block_size);
    memcpy(item2, temp,  block_size);

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
        #define EXCEPTION_MSG EXCEPTION_MESSAGE_NULL_POINTER(TYPE_REPR, "reverse")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        #undef EXCEPTION_MSG
        return false; /* Cannot operate on nothing */
    }
    else
#endif /* CDAR_OPT */
    if (!(length = dynarr->used))
    {
        #define EXCEPTION_MSG EXCEPTION_MESSAGE_EMPTY(TYPE_REPR, "reverse")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        #undef EXCEPTION_MSG
        return true; /* Successfully did nothing */
    }

    /* CORE FUNCTIONALITY
       Create/get/cast essential values */
    size_t item_size = dynarr->size;
    char *item1,
         *item2,
         *data = (char *)dynarr->data;
    char temp[item_size];
    /* Swap items in place */
    for (size_t i=0; i < (length/2); i++)
    {
        item1 = data + i*item_size;
        item2 = data + (length - i - 1)*item_size;

        memcpy(temp,  item1, item_size);
        memcpy(item1, item2, item_size);
        memcpy(item2, temp,  item_size);
    }
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
        #define EXCEPTION_MSG \
            EXCEPTION_MESSAGE_NULL_POINTER(TYPE_REPR, "append")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        #undef EXCEPTION_MSG
        return false; /* Cannot operate on nothing */
    }
    /* Invalid source */
    else if (!source)
    {
        #define EXCEPTION_MSG \
            EXCEPTION_MESSAGE_ARGUMENT_NULL(TYPE_REPR, "append", "3rd", source)
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        #undef EXCEPTION_MSG
        return true; /* Successfully added nothing */
    }
    else
#endif /* CDAR_OPT */
    /* Something to append */
    if (count)
    {
        /* CORE FUNCTIONALITY
           Resize array if necessary */
        size_t item_size = dynarr->size;
        if (!__cdar_resize(dynarr, item_size, count))
        {
            #define EXCEPTION_MSG \
                EXCEPTION_MESSAGE_REALLOC_FAIL(TYPE_REPR, "append")
            cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
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
        #define EXCEPTION_MSG EXCEPTION_MESSAGE_NULL_POINTER(TYPE_REPR, "push")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
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
        #define EXCEPTION_MSG \
            EXCEPTION_MESSAGE_ARGUMENT_NULL(TYPE_REPR, "push", "4th", source)
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
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
        #define EXCEPTION_MSG EXCEPTION_MESSAGE_REALLOC_FAIL(TYPE_REPR, "push")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
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
        #define EXCEPTION_MSG EXCEPTION_MESSAGE_NULL_POINTER(TYPE_REPR, "pull")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
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
        #define EXCEPTION_MSG EXCEPTION_MESSAGE_EMPTY(TYPE_REPR, "pull")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        #undef EXCEPTION_MSG
        return 0; /* Successfully removed nothing */
    }
    /* Out of range */
    else if (index >= dynarr->used)
    {
        #define EXCEPTION_MSG \
            EXCEPTION_MESSAGE_ARGUMENT_OUTOF(TYPE_REPR, "pull", "2nd", index)
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
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
        #define EXCEPTION_MSG EXCEPTION_MESSAGE_NULL_POINTER(TYPE_REPR, "pop")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
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
        #define EXCEPTION_MSG \
            EXCEPTION_MESSAGE_ARGUMENT_NULL(TYPE_REPR, "pop", "4th", destination)
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        #undef EXCEPTION_MSG
        return 0; /* Successfully popped nothing */
    }
    /* Empty array */
    else if (!dynarr->used)
    {
        #define EXCEPTION_MSG EXCEPTION_MESSAGE_EMPTY(TYPE_REPR, "pop")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        #undef EXCEPTION_MSG
        return 0; /* Successfully popped nothing */
    }
    /* Out of range */
    else if (index >= dynarr->used)
    {
        #define EXCEPTION_MSG \
            EXCEPTION_MESSAGE_ARGUMENT_OUTOF(TYPE_REPR, "pop", "2nd", index)
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
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
        #define EXCEPTION_MSG EXCEPTION_MESSAGE_NULL_POINTER(TYPE_REPR, "sub")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
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
        #define EXCEPTION_MSG \
            EXCEPTION_MESSAGE_ARGUMENT_NULL(TYPE_REPR, "sub", "4th", destination)
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        #undef EXCEPTION_MSG
        return 0; /* Successfully subbed nothing */
    }
    /* Empty array */
    else if (!dynarr->used)
    {
        #define EXCEPTION_MSG \
            EXCEPTION_MESSAGE_EMPTY(TYPE_REPR, "sub")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        #undef EXCEPTION_MSG
        return 0; /* Successfully subbed nothing */
    }
    /* Out of range */
    else if (index >= dynarr->used)
    {
        #define EXCEPTION_MSG \
            EXCEPTION_MESSAGE_ARGUMENT_OUTOF(TYPE_REPR, "sub", "2nd", index)
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
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
        #define EXCEPTION_MSG EXCEPTION_MESSAGE_NULL_POINTER(TYPE_REPR, "truncate")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        #undef EXCEPTION_MSG
        return; /* Cannot operate on nothing */
    }
    else
#endif /* CDAR_OPT */
    /* Out of range */
    if (index >= dynarr->used)
    {
        #define EXCEPTION_MSG \
            EXCEPTION_MESSAGE_ARGUMENT_OUTOF(TYPE_REPR, "truncate", "2nd", index)
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
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
        #define EXCEPTION_MSG EXCEPTION_MESSAGE_NULL_POINTER(TYPE_REPR, "set")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
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
        #define EXCEPTION_MSG \
            EXCEPTION_MESSAGE_ARGUMENT_NULL(TYPE_REPR, "set", "4th", destination)
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        #undef EXCEPTION_MSG
        return true; /* Successfully set nothing */
    }
    /* Out of range */
    else if (index >= dynarr->used)
    {
        #define EXCEPTION_MSG \
            EXCEPTION_MESSAGE_ARGUMENT_OUTOF(TYPE_REPR, "set", "2nd", index)
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
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
        #define EXCEPTION_MSG EXCEPTION_MESSAGE_NULL_POINTER(TYPE_REPR, "get")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        #undef EXCEPTION_MSG
        return NULL; /* Cannot operate on nothing */
    }
    else if (!dynarr->used)
    {
        #define EXCEPTION_MSG EXCEPTION_MESSAGE_EMPTY(TYPE_REPR, "get")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        #undef EXCEPTION_MSG
        return NULL;
    }
    else if (index >= dynarr->used)
    {
        #define EXCEPTION_MSG \
            EXCEPTION_MESSAGE_ARGUMENT_OUTOF(TYPE_REPR, "get", "2nd", index)
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
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
                                       bool (*compare)(const void*, const void*, size_t),
                                       const void *item,
                                       size_t *index)
{
#ifndef CDAR_OPT
    if (!dynarr)
    {
        #define EXCEPTION_MSG \
            EXCEPTION_MESSAGE_NULL_POINTER(TYPE_REPR, "find")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        #undef EXCEPTION_MSG
        return false; /* Cannot operate on nothing */
    }
    else if (!index)
    {
        #define EXCEPTION_MSG \
            EXCEPTION_MESSAGE_ARGUMENT_NULL(TYPE_REPR, "find", "4th", index)
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
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
            if (compare(item, data + i*item_size, item_size))
            {
                *index = i;
                return true; /* Successfully found */
            }
        }
        return false; /* Successfully not found */
    }
    #define EXCEPTION_MSG EXCEPTION_MESSAGE_EMPTY(TYPE_REPR, "find")
    cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
    #undef EXCEPTION_MSG
    return false; /* Successfully not found */
}


/*----------------------------------------------------------------------------*/
size_t
cutils_cdar_DynamicArray_void_ptr_findall(cutils_cdar_DynamicArray_void_ptr *dynarr,
                                          bool (*compare)(const void*, const void*, size_t),
                                          const void *item,
                                          size_t *indices)
{
#ifndef CDAR_OPT
    if (!dynarr)
    {
        #define EXCEPTION_MSG \
            EXCEPTION_MESSAGE_NULL_POINTER(TYPE_REPR, "findall")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        #undef EXCEPTION_MSG
        return 0; /* Cannot operate on nothing */
    }
    else if (!indices)
    {
        #define EXCEPTION_MSG \
            EXCEPTION_MESSAGE_ARGUMENT_NULL(TYPE_REPR, "findall", "3rd", indices)
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
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
            if (compare(item, data + i*item_size, item_size))
                indices[count++] = i;
        return count;
    }
    #define EXCEPTION_MSG EXCEPTION_MESSAGE_EMPTY(TYPE_REPR, "findall")
    cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
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
        #define EXCEPTION_MSG EXCEPTION_MESSAGE_NULL_POINTER(TYPE_REPR, "sort")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        #undef EXCEPTION_MSG
        return; /* Cannot operate on nothing */
    }
    else
#endif /* CDAR_OPT */
    if (!dynarr->used)
    {
        #define EXCEPTION_MSG EXCEPTION_MESSAGE_EMPTY(TYPE_REPR, "sort")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
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
                                          int (*compare)(const void*, const void*))
{
#ifndef CDAR_OPT
    if (!dynarr)
    {
        #define EXCEPTION_MSG EXCEPTION_MESSAGE_NULL_POINTER(TYPE_REPR, "sortsub")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        #undef EXCEPTION_MSG
        return; /* Cannot operate on nothing */
    }
    else if (!dynarr->used)
    {
        #define EXCEPTION_MSG EXCEPTION_MESSAGE_EMPTY(TYPE_REPR, "sortsub")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        #undef EXCEPTION_MSG
        return;
    }
    else if (index >= dynarr->used)
    {
        #define EXCEPTION_MSG \
            EXCEPTION_MESSAGE_ARGUMENT_OUTOF(TYPE_REPR, "sortsub", "2nd", index)
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
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
void
cutils_cdar_DynamicArray_void_ptr_map(cutils_cdar_DynamicArray_void_ptr *dynarr,
                                      size_t index,
                                      size_t count,
                                      void (*function)())
{
#ifndef CDAR_OPT
    if (!dynarr)
    {
        #define EXCEPTION_MSG EXCEPTION_MESSAGE_NULL_POINTER(TYPE_REPR, "map")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        #undef EXCEPTION_MSG
        return; /* Cannot operate on nothing */
    }
    else if (!dynarr->used)
    {
        #define EXCEPTION_MSG EXCEPTION_MESSAGE_EMPTY(TYPE_REPR, "map")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        #undef EXCEPTION_MSG
        return; /* Successfully did nothing */
    }
    else if (index >= dynarr->used)
    {
        #define EXCEPTION_MSG \
            EXCEPTION_MESSAGE_ARGUMENT_OUTOF(TYPE_REPR, "map", "2nd", index)
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        #undef EXCEPTION_MSG
        return;
    }
    else if (!function)
    {
        #define EXCEPTION_MSG \
            EXCEPTION_MESSAGE_ARGUMENT_NULL(TYPE_REPR, "map", "4th", function)
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        #undef EXCEPTION_MSG
        return; /* Cannot call NULL on items */
    }
#endif
    /* CORE FUNCTIONALITY
       Get/set/cast values */
    char *data = (char *)dynarr->data;
    size_t size = dynarr->size;
    /* Limit count */
    if ((index + count) >= dynarr->used)
        count = dynarr->used - index;
    /* Call function on each item in array */
    for (size_t i=index; i<count; i++)
        function(i, data + i*size);
}


/*----------------------------------------------------------------------------*/
bool
cutils_cdar_DynamicArray_void_ptr_format(const void *item,
                                         char **buffer,
                                         size_t *buffer_size)
{
    /* buffer_size could be used to realloc buffer if
       it is too small to contain the formatted item */
    if (!*(char **)item)
        *buffer = REPRESENTATION_OF_NULL_POINTERS;
    else
        snprintf(*buffer, *buffer_size, REPRESENTATION_OF_REAL_POINTERS, item);
    return true;
}


/*----------------------------------------------------------------------------*/
void
cutils_cdar_DynamicArray_void_ptr_print(cutils_cdar_DynamicArray_void_ptr *dynarr,
                                        FILE *stream,
                                        const char *sub_type,
                                        bool(*format)())
                                        // char *(*format)(const void*, char**, size_t*))
{
#ifndef CDAR_OPT
    if (!dynarr)
    {
        #define EXCEPTION_MSG EXCEPTION_MESSAGE_NULL_POINTER(TYPE_REPR, "print")
        cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
        #undef EXCEPTION_MSG
        fprintf(stream, REPRESENTATION_OF_NULL_POINTERS "\n");
        return; /* Cannot operate on nothing */
    }
#endif
    char *opening;

    /* If object is "sub-typed" */
    if (sub_type)
        opening = TYPE_REPR "_%s{";
    else
        opening = TYPE_REPR "{";

    fprintf(stream, opening, sub_type);
    /* If array is filled */
    if (dynarr->used)
    {
        /* Create a dynamically allocated buffer for representation */
        size_t buffer_size = 128;
        char *buffer = malloc(buffer_size);
        if (!buffer)
        {
            #define EXCEPTION_MSG EXCEPTION_MESSAGE_ALLOC_FAIL(TYPE_REPR, "print")
            cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
            #undef EXCEPTION_MSG
            fprintf(stream, "...}\n");
            return;
        }
        /* Create/get/set/cast essentaial values */
        char *data = (char *)dynarr->data;
        size_t size = dynarr->size;
        char **buffer_ptr = &buffer;
        /* Print all remaining items, with leading comma */
        for (size_t i=0; i<dynarr->used; i++)
        {
            /* If not the first item */
            if (i) fprintf(stream, ", ");
            /* If formatting representation was successful */
            if (!format(data + size*i, buffer_ptr, &buffer_size))
            {
                #define EXCEPTION_MSG \
                    EXCEPTION_MESSAGE_REALLOC_FAIL(TYPE_REPR, "print")
                cutils_cexc_raise(EXCEPTION_MSG, sizeof EXCEPTION_MSG);
                #undef EXCEPTION_MSG
                fprintf(stream, "...");
                break;
            }
            /* Print representation and re-set buffer pointer */
            fprintf(stream, "%s", *buffer_ptr);
            *buffer_ptr = buffer;
        }
        free(buffer);
    }
    fprintf(stream, "}\n");
}

/*----------------------------------------------------------------------------*/
bool
cutils_cdar_DynamicArray_void_ptr_compare(const void *item1,
                                          const void *item2,
                                          size_t item_size)
{
    return !memcmp(item1, item2, item_size);
}

/*----------------------------------------------------------------------------*/
typedef cutils_cdar_DynamicArray_void_ptr cutils_cdar_DynamicArray_char;
bool cutils_cdar_DynamicArray_char_new(cutils_cdar_DynamicArray_char**d,size_t c,char*a){return cutils_cdar_DynamicArray_void_ptr_new(d,sizeof(char),c,a);}
char* cutils_cdar_DynamicArray_char_data(cutils_cdar_DynamicArray_char*d,size_t*s,size_t*c){return cutils_cdar_DynamicArray_void_ptr_data(d,s,c);}
char* cutils_cdar_DynamicArray_char_raw(cutils_cdar_DynamicArray_char*d){return (char*)cutils_cdar_DynamicArray_void_ptr_raw(d);}
bool cutils_cdar_DynamicArray_char_append(cutils_cdar_DynamicArray_char*d,size_t c,char*a){return cutils_cdar_DynamicArray_void_ptr_append(d,c,a);}
bool cutils_cdar_DynamicArray_char_push(cutils_cdar_DynamicArray_char*d,size_t i,size_t c,char*a){return cutils_cdar_DynamicArray_void_ptr_push(d,i,c,a);}
bool cutils_cdar_DynamicArray_char_set(cutils_cdar_DynamicArray_char*d,size_t i,size_t c,char*s){return cutils_cdar_DynamicArray_void_ptr_set(d,i,c,s);}
size_t cutils_cdar_DynamicArray_char_pop(cutils_cdar_DynamicArray_char*d,size_t i,size_t c,char*a){return cutils_cdar_DynamicArray_void_ptr_pop(d,i,c,a);}
size_t cutils_cdar_DynamicArray_char_sub(cutils_cdar_DynamicArray_char*d,size_t i,size_t c,char*a){return cutils_cdar_DynamicArray_void_ptr_sub(d,i,c,a);}
char cutils_cdar_DynamicArray_char_get(cutils_cdar_DynamicArray_char*d,size_t i){return *(char*)cutils_cdar_DynamicArray_void_ptr_get(d,i);}
bool cutils_cdar_DynamicArray_char_find(cutils_cdar_DynamicArray_char*d,bool(*f)(const void*,const void*,size_t),const void*p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_find(d,f,p,i);}
size_t cutils_cdar_DynamicArray_char_findall(cutils_cdar_DynamicArray_char*d,bool(*f)(const void*,const void*,size_t),const void*p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_findall(d,f,p,i);}
bool cutils_cdar_DynamicArray_char_format(const char*i,char**b,size_t*s){cutils_fmtc_repr(*b,*s,i,1);return true;}
bool cutils_cdar_DynamicArray_char_compare(const void*p1,const void*p2,size_t s){return !memcmp(p1,p2,s);}
void(*cutils_cdar_DynamicArray_char_del)(cutils_cdar_DynamicArray_char*)=cutils_cdar_DynamicArray_void_ptr_del;
size_t(*cutils_cdar_DynamicArray_char_len)(cutils_cdar_DynamicArray_char*)=cutils_cdar_DynamicArray_void_ptr_len;
size_t(*cutils_cdar_DynamicArray_char_size)(cutils_cdar_DynamicArray_char*)=cutils_cdar_DynamicArray_void_ptr_size;
bool(*cutils_cdar_DynamicArray_char_resize)(cutils_cdar_DynamicArray_char*,size_t)=cutils_cdar_DynamicArray_void_ptr_resize;
bool(*cutils_cdar_DynamicArray_char_swap)(cutils_cdar_DynamicArray_char*,size_t,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_swap;
bool(*cutils_cdar_DynamicArray_char_reverse)(cutils_cdar_DynamicArray_char*)=cutils_cdar_DynamicArray_void_ptr_reverse;
size_t(*cutils_cdar_DynamicArray_char_pull)(cutils_cdar_DynamicArray_char*,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_pull;
void(*cutils_cdar_DynamicArray_char_truncate)(cutils_cdar_DynamicArray_char*,size_t)=cutils_cdar_DynamicArray_void_ptr_truncate;
void(*cutils_cdar_DynamicArray_char_clear)(cutils_cdar_DynamicArray_char*)=cutils_cdar_DynamicArray_void_ptr_clear;
void(*cutils_cdar_DynamicArray_char_map)(cutils_cdar_DynamicArray_char*,size_t,size_t,void(*)(size_t,char*))=cutils_cdar_DynamicArray_void_ptr_map;
void(*cutils_cdar_DynamicArray_char_print)(cutils_cdar_DynamicArray_char*,FILE*,const char*,bool(*)())=cutils_cdar_DynamicArray_void_ptr_print;
/*----------------------------------------------------------------------------*/
typedef cutils_cdar_DynamicArray_void_ptr cutils_cdar_DynamicArray_signed_char;
bool cutils_cdar_DynamicArray_signed_char_new(cutils_cdar_DynamicArray_signed_char**d,size_t c,signed char*a){return cutils_cdar_DynamicArray_void_ptr_new(d,sizeof(signed char),c,a);}
signed char* cutils_cdar_DynamicArray_signed_char_data(cutils_cdar_DynamicArray_signed_char*d,size_t*s,size_t*c){return cutils_cdar_DynamicArray_void_ptr_data(d,s,c);}
signed char* cutils_cdar_DynamicArray_signed_char_raw(cutils_cdar_DynamicArray_signed_char*d){return (signed char*)cutils_cdar_DynamicArray_void_ptr_raw(d);}
bool cutils_cdar_DynamicArray_signed_char_append(cutils_cdar_DynamicArray_signed_char*d,size_t c,signed char*a){return cutils_cdar_DynamicArray_void_ptr_append(d,c,a);}
bool cutils_cdar_DynamicArray_signed_char_push(cutils_cdar_DynamicArray_signed_char*d,size_t i,size_t c,signed char*a){return cutils_cdar_DynamicArray_void_ptr_push(d,i,c,a);}
bool cutils_cdar_DynamicArray_signed_char_set(cutils_cdar_DynamicArray_signed_char*d,size_t i,size_t c,signed char*s){return cutils_cdar_DynamicArray_void_ptr_set(d,i,c,s);}
size_t cutils_cdar_DynamicArray_signed_char_pop(cutils_cdar_DynamicArray_signed_char*d,size_t i,size_t c,signed char*a){return cutils_cdar_DynamicArray_void_ptr_pop(d,i,c,a);}
size_t cutils_cdar_DynamicArray_signed_char_sub(cutils_cdar_DynamicArray_signed_char*d,size_t i,size_t c,signed char*a){return cutils_cdar_DynamicArray_void_ptr_sub(d,i,c,a);}
signed char cutils_cdar_DynamicArray_signed_char_get(cutils_cdar_DynamicArray_signed_char*d,size_t i){return *(signed char*)cutils_cdar_DynamicArray_void_ptr_get(d,i);}
bool cutils_cdar_DynamicArray_signed_char_find(cutils_cdar_DynamicArray_signed_char*d,bool(*f)(const void*,const void*,size_t),const void*p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_find(d,f,p,i);}
size_t cutils_cdar_DynamicArray_signed_char_findall(cutils_cdar_DynamicArray_signed_char*d,bool(*f)(const void*,const void*,size_t),const void*p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_findall(d,f,p,i);}
bool cutils_cdar_DynamicArray_signed_char_format(const signed char*i,char**b,size_t*s){snprintf(*b,*s,"%c",*i);return true;}
bool cutils_cdar_DynamicArray_signed_char_compare(const void*p1,const void*p2,size_t s){return !memcmp(p1,p2,s);}
void(*cutils_cdar_DynamicArray_signed_char_del)(cutils_cdar_DynamicArray_signed_char*)=cutils_cdar_DynamicArray_void_ptr_del;
size_t(*cutils_cdar_DynamicArray_signed_char_len)(cutils_cdar_DynamicArray_signed_char*)=cutils_cdar_DynamicArray_void_ptr_len;
size_t(*cutils_cdar_DynamicArray_signed_char_size)(cutils_cdar_DynamicArray_signed_char*)=cutils_cdar_DynamicArray_void_ptr_size;
bool(*cutils_cdar_DynamicArray_signed_char_resize)(cutils_cdar_DynamicArray_signed_char*,size_t)=cutils_cdar_DynamicArray_void_ptr_resize;
bool(*cutils_cdar_DynamicArray_signed_char_swap)(cutils_cdar_DynamicArray_signed_char*,size_t,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_swap;
bool(*cutils_cdar_DynamicArray_signed_char_reverse)(cutils_cdar_DynamicArray_signed_char*)=cutils_cdar_DynamicArray_void_ptr_reverse;
size_t(*cutils_cdar_DynamicArray_signed_char_pull)(cutils_cdar_DynamicArray_signed_char*,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_pull;
void(*cutils_cdar_DynamicArray_signed_char_truncate)(cutils_cdar_DynamicArray_signed_char*,size_t)=cutils_cdar_DynamicArray_void_ptr_truncate;
void(*cutils_cdar_DynamicArray_signed_char_clear)(cutils_cdar_DynamicArray_signed_char*)=cutils_cdar_DynamicArray_void_ptr_clear;
void(*cutils_cdar_DynamicArray_signed_char_map)(cutils_cdar_DynamicArray_signed_char*,size_t,size_t,void(*)(size_t,signed char*))=cutils_cdar_DynamicArray_void_ptr_map;
void(*cutils_cdar_DynamicArray_signed_char_print)(cutils_cdar_DynamicArray_signed_char*,FILE*,const char*,bool(*)())=cutils_cdar_DynamicArray_void_ptr_print;
/*----------------------------------------------------------------------------*/
typedef cutils_cdar_DynamicArray_void_ptr cutils_cdar_DynamicArray_unsigned_char;
bool cutils_cdar_DynamicArray_unsigned_char_new(cutils_cdar_DynamicArray_unsigned_char**d,size_t c,unsigned char*a){return cutils_cdar_DynamicArray_void_ptr_new(d,sizeof(unsigned char),c,a);}
unsigned char* cutils_cdar_DynamicArray_unsigned_char_data(cutils_cdar_DynamicArray_unsigned_char*d,size_t*s,size_t*c){return cutils_cdar_DynamicArray_void_ptr_data(d,s,c);}
unsigned char* cutils_cdar_DynamicArray_unsigned_char_raw(cutils_cdar_DynamicArray_unsigned_char*d){return (unsigned char*)cutils_cdar_DynamicArray_void_ptr_raw(d);}
bool cutils_cdar_DynamicArray_unsigned_char_append(cutils_cdar_DynamicArray_unsigned_char*d,size_t c,unsigned char*a){return cutils_cdar_DynamicArray_void_ptr_append(d,c,a);}
bool cutils_cdar_DynamicArray_unsigned_char_push(cutils_cdar_DynamicArray_unsigned_char*d,size_t i,size_t c,unsigned char*a){return cutils_cdar_DynamicArray_void_ptr_push(d,i,c,a);}
bool cutils_cdar_DynamicArray_unsigned_char_set(cutils_cdar_DynamicArray_unsigned_char*d,size_t i,size_t c,unsigned char*s){return cutils_cdar_DynamicArray_void_ptr_set(d,i,c,s);}
size_t cutils_cdar_DynamicArray_unsigned_char_pop(cutils_cdar_DynamicArray_unsigned_char*d,size_t i,size_t c,unsigned char*a){return cutils_cdar_DynamicArray_void_ptr_pop(d,i,c,a);}
size_t cutils_cdar_DynamicArray_unsigned_char_sub(cutils_cdar_DynamicArray_unsigned_char*d,size_t i,size_t c,unsigned char*a){return cutils_cdar_DynamicArray_void_ptr_sub(d,i,c,a);}
unsigned char cutils_cdar_DynamicArray_unsigned_char_get(cutils_cdar_DynamicArray_unsigned_char*d,size_t i){return *(unsigned char*)cutils_cdar_DynamicArray_void_ptr_get(d,i);}
bool cutils_cdar_DynamicArray_unsigned_char_find(cutils_cdar_DynamicArray_unsigned_char*d,bool(*f)(const void*,const void*,size_t),const void*p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_find(d,f,p,i);}
size_t cutils_cdar_DynamicArray_unsigned_char_findall(cutils_cdar_DynamicArray_unsigned_char*d,bool(*f)(const void*,const void*,size_t),const void*p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_findall(d,f,p,i);}
bool cutils_cdar_DynamicArray_unsigned_char_format(const unsigned char*i,char**b,size_t*s){snprintf(*b,*s,"%u",*i);return true;}
bool cutils_cdar_DynamicArray_unsigned_char_compare(const void*p1,const void*p2,size_t s){return !memcmp(p1,p2,s);}
void(*cutils_cdar_DynamicArray_unsigned_char_del)(cutils_cdar_DynamicArray_unsigned_char*)=cutils_cdar_DynamicArray_void_ptr_del;
size_t(*cutils_cdar_DynamicArray_unsigned_char_len)(cutils_cdar_DynamicArray_unsigned_char*)=cutils_cdar_DynamicArray_void_ptr_len;
size_t(*cutils_cdar_DynamicArray_unsigned_char_size)(cutils_cdar_DynamicArray_unsigned_char*)=cutils_cdar_DynamicArray_void_ptr_size;
bool(*cutils_cdar_DynamicArray_unsigned_char_resize)(cutils_cdar_DynamicArray_unsigned_char*,size_t)=cutils_cdar_DynamicArray_void_ptr_resize;
bool(*cutils_cdar_DynamicArray_unsigned_char_swap)(cutils_cdar_DynamicArray_unsigned_char*,size_t,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_swap;
bool(*cutils_cdar_DynamicArray_unsigned_char_reverse)(cutils_cdar_DynamicArray_unsigned_char*)=cutils_cdar_DynamicArray_void_ptr_reverse;
size_t(*cutils_cdar_DynamicArray_unsigned_char_pull)(cutils_cdar_DynamicArray_unsigned_char*,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_pull;
void(*cutils_cdar_DynamicArray_unsigned_char_truncate)(cutils_cdar_DynamicArray_unsigned_char*,size_t)=cutils_cdar_DynamicArray_void_ptr_truncate;
void(*cutils_cdar_DynamicArray_unsigned_char_clear)(cutils_cdar_DynamicArray_unsigned_char*)=cutils_cdar_DynamicArray_void_ptr_clear;
void(*cutils_cdar_DynamicArray_unsigned_char_map)(cutils_cdar_DynamicArray_unsigned_char*,size_t,size_t,void(*)(size_t,unsigned char*))=cutils_cdar_DynamicArray_void_ptr_map;
void(*cutils_cdar_DynamicArray_unsigned_char_print)(cutils_cdar_DynamicArray_unsigned_char*,FILE*,const char*,bool(*)())=cutils_cdar_DynamicArray_void_ptr_print;
/*----------------------------------------------------------------------------*/
typedef cutils_cdar_DynamicArray_void_ptr cutils_cdar_DynamicArray_char_ptr;
bool cutils_cdar_DynamicArray_char_ptr_new(cutils_cdar_DynamicArray_char_ptr**d,size_t c,char**a){return cutils_cdar_DynamicArray_void_ptr_new(d,sizeof(char*),c,a);}
char** cutils_cdar_DynamicArray_char_ptr_data(cutils_cdar_DynamicArray_char_ptr*d,size_t*s,size_t*c){return cutils_cdar_DynamicArray_void_ptr_data(d,s,c);}
char** cutils_cdar_DynamicArray_char_ptr_raw(cutils_cdar_DynamicArray_char_ptr*d){return (char**)cutils_cdar_DynamicArray_void_ptr_raw(d);}
bool cutils_cdar_DynamicArray_char_ptr_append(cutils_cdar_DynamicArray_char_ptr*d,size_t c,char**a){return cutils_cdar_DynamicArray_void_ptr_append(d,c,a);}
bool cutils_cdar_DynamicArray_char_ptr_push(cutils_cdar_DynamicArray_char_ptr*d,size_t i,size_t c,char**a){return cutils_cdar_DynamicArray_void_ptr_push(d,i,c,a);}
bool cutils_cdar_DynamicArray_char_ptr_set(cutils_cdar_DynamicArray_char_ptr*d,size_t i,size_t c,char**s){return cutils_cdar_DynamicArray_void_ptr_set(d,i,c,s);}
size_t cutils_cdar_DynamicArray_char_ptr_pop(cutils_cdar_DynamicArray_char_ptr*d,size_t i,size_t c,char**a){return cutils_cdar_DynamicArray_void_ptr_pop(d,i,c,a);}
size_t cutils_cdar_DynamicArray_char_ptr_sub(cutils_cdar_DynamicArray_char_ptr*d,size_t i,size_t c,char**a){return cutils_cdar_DynamicArray_void_ptr_sub(d,i,c,a);}
char* cutils_cdar_DynamicArray_char_ptr_get(cutils_cdar_DynamicArray_char_ptr*d,size_t i){return *(char**)cutils_cdar_DynamicArray_void_ptr_get(d,i);}
bool cutils_cdar_DynamicArray_char_ptr_find(cutils_cdar_DynamicArray_char_ptr*d,bool(*f)(const void*,const void*,size_t),const void*p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_find(d,f,p,i);}
size_t cutils_cdar_DynamicArray_char_ptr_findall(cutils_cdar_DynamicArray_char_ptr*d,bool(*f)(const void*,const void*,size_t),const void*p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_findall(d,f,p,i);}
bool cutils_cdar_DynamicArray_char_ptr_format(const char**i,char**b,size_t*s){size_t l=strlen(*i);if(*s<l+3)if(!(*b=realloc(*b,(*s=l*2+3))))
return false;cutils_fmtc_repr(*b,*s,*i,l);return true;}
bool cutils_cdar_DynamicArray_char_ptr_compare(const void*p1,const void*p2,size_t s){return !memcmp(p1,p2,s);}
void(*cutils_cdar_DynamicArray_char_ptr_del)(cutils_cdar_DynamicArray_char_ptr*)=cutils_cdar_DynamicArray_void_ptr_del;
size_t(*cutils_cdar_DynamicArray_char_ptr_len)(cutils_cdar_DynamicArray_char_ptr*)=cutils_cdar_DynamicArray_void_ptr_len;
size_t(*cutils_cdar_DynamicArray_char_ptr_size)(cutils_cdar_DynamicArray_char_ptr*)=cutils_cdar_DynamicArray_void_ptr_size;
bool(*cutils_cdar_DynamicArray_char_ptr_resize)(cutils_cdar_DynamicArray_char_ptr*,size_t)=cutils_cdar_DynamicArray_void_ptr_resize;
bool(*cutils_cdar_DynamicArray_char_ptr_swap)(cutils_cdar_DynamicArray_char_ptr*,size_t,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_swap;
bool(*cutils_cdar_DynamicArray_char_ptr_reverse)(cutils_cdar_DynamicArray_char_ptr*)=cutils_cdar_DynamicArray_void_ptr_reverse;
size_t(*cutils_cdar_DynamicArray_char_ptr_pull)(cutils_cdar_DynamicArray_char_ptr*,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_pull;
void(*cutils_cdar_DynamicArray_char_ptr_truncate)(cutils_cdar_DynamicArray_char_ptr*,size_t)=cutils_cdar_DynamicArray_void_ptr_truncate;
void(*cutils_cdar_DynamicArray_char_ptr_clear)(cutils_cdar_DynamicArray_char_ptr*)=cutils_cdar_DynamicArray_void_ptr_clear;
void(*cutils_cdar_DynamicArray_char_ptr_map)(cutils_cdar_DynamicArray_char_ptr*,size_t,size_t,void(*)(size_t,char**))=cutils_cdar_DynamicArray_void_ptr_map;
void(*cutils_cdar_DynamicArray_char_ptr_print)(cutils_cdar_DynamicArray_char_ptr*,FILE*,const char*,bool(*)())=cutils_cdar_DynamicArray_void_ptr_print;
/*----------------------------------------------------------------------------*/
typedef cutils_cdar_DynamicArray_void_ptr cutils_cdar_DynamicArray_short;
bool cutils_cdar_DynamicArray_short_new(cutils_cdar_DynamicArray_short**d,size_t c,short*a){return cutils_cdar_DynamicArray_void_ptr_new(d,sizeof(short),c,a);}
short* cutils_cdar_DynamicArray_short_data(cutils_cdar_DynamicArray_short*d,size_t*s,size_t*c){return cutils_cdar_DynamicArray_void_ptr_data(d,s,c);}
short* cutils_cdar_DynamicArray_short_raw(cutils_cdar_DynamicArray_short*d){return (short*)cutils_cdar_DynamicArray_void_ptr_raw(d);}
bool cutils_cdar_DynamicArray_short_append(cutils_cdar_DynamicArray_short*d,size_t c,short*a){return cutils_cdar_DynamicArray_void_ptr_append(d,c,a);}
bool cutils_cdar_DynamicArray_short_push(cutils_cdar_DynamicArray_short*d,size_t i,size_t c,short*a){return cutils_cdar_DynamicArray_void_ptr_push(d,i,c,a);}
bool cutils_cdar_DynamicArray_short_set(cutils_cdar_DynamicArray_short*d,size_t i,size_t c,short*s){return cutils_cdar_DynamicArray_void_ptr_set(d,i,c,s);}
size_t cutils_cdar_DynamicArray_short_pop(cutils_cdar_DynamicArray_short*d,size_t i,size_t c,short*a){return cutils_cdar_DynamicArray_void_ptr_pop(d,i,c,a);}
size_t cutils_cdar_DynamicArray_short_sub(cutils_cdar_DynamicArray_short*d,size_t i,size_t c,short*a){return cutils_cdar_DynamicArray_void_ptr_sub(d,i,c,a);}
short cutils_cdar_DynamicArray_short_get(cutils_cdar_DynamicArray_short*d,size_t i){return *(short*)cutils_cdar_DynamicArray_void_ptr_get(d,i);}
bool cutils_cdar_DynamicArray_short_find(cutils_cdar_DynamicArray_short*d,bool(*f)(const void*,const void*,size_t),const void*p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_find(d,f,p,i);}
size_t cutils_cdar_DynamicArray_short_findall(cutils_cdar_DynamicArray_short*d,bool(*f)(const void*,const void*,size_t),const void*p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_findall(d,f,p,i);}
bool cutils_cdar_DynamicArray_short_format(const short*i,char**b,size_t*s){snprintf(*b,*s,"%hd",*i);return true;}
bool cutils_cdar_DynamicArray_short_compare(const void*p1,const void*p2,size_t s){return !memcmp(p1,p2,s);}
void(*cutils_cdar_DynamicArray_short_del)(cutils_cdar_DynamicArray_short*)=cutils_cdar_DynamicArray_void_ptr_del;
size_t(*cutils_cdar_DynamicArray_short_len)(cutils_cdar_DynamicArray_short*)=cutils_cdar_DynamicArray_void_ptr_len;
size_t(*cutils_cdar_DynamicArray_short_size)(cutils_cdar_DynamicArray_short*)=cutils_cdar_DynamicArray_void_ptr_size;
bool(*cutils_cdar_DynamicArray_short_resize)(cutils_cdar_DynamicArray_short*,size_t)=cutils_cdar_DynamicArray_void_ptr_resize;
bool(*cutils_cdar_DynamicArray_short_swap)(cutils_cdar_DynamicArray_short*,size_t,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_swap;
bool(*cutils_cdar_DynamicArray_short_reverse)(cutils_cdar_DynamicArray_short*)=cutils_cdar_DynamicArray_void_ptr_reverse;
size_t(*cutils_cdar_DynamicArray_short_pull)(cutils_cdar_DynamicArray_short*,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_pull;
void(*cutils_cdar_DynamicArray_short_truncate)(cutils_cdar_DynamicArray_short*,size_t)=cutils_cdar_DynamicArray_void_ptr_truncate;
void(*cutils_cdar_DynamicArray_short_clear)(cutils_cdar_DynamicArray_short*)=cutils_cdar_DynamicArray_void_ptr_clear;
void(*cutils_cdar_DynamicArray_short_map)(cutils_cdar_DynamicArray_short*,size_t,size_t,void(*)(size_t,short*))=cutils_cdar_DynamicArray_void_ptr_map;
void(*cutils_cdar_DynamicArray_short_print)(cutils_cdar_DynamicArray_short*,FILE*,const char*,bool(*)())=cutils_cdar_DynamicArray_void_ptr_print;
/*----------------------------------------------------------------------------*/
typedef cutils_cdar_DynamicArray_void_ptr cutils_cdar_DynamicArray_unsigned_short;
bool cutils_cdar_DynamicArray_unsigned_short_new(cutils_cdar_DynamicArray_unsigned_short**d,size_t c,unsigned short*a){return cutils_cdar_DynamicArray_void_ptr_new(d,sizeof(unsigned short),c,a);}
unsigned short* cutils_cdar_DynamicArray_unsigned_short_data(cutils_cdar_DynamicArray_unsigned_short*d,size_t*s,size_t*c){return cutils_cdar_DynamicArray_void_ptr_data(d,s,c);}
unsigned short* cutils_cdar_DynamicArray_unsigned_short_raw(cutils_cdar_DynamicArray_unsigned_short*d){return (unsigned short*)cutils_cdar_DynamicArray_void_ptr_raw(d);}
bool cutils_cdar_DynamicArray_unsigned_short_append(cutils_cdar_DynamicArray_unsigned_short*d,size_t c,unsigned short*a){return cutils_cdar_DynamicArray_void_ptr_append(d,c,a);}
bool cutils_cdar_DynamicArray_unsigned_short_push(cutils_cdar_DynamicArray_unsigned_short*d,size_t i,size_t c,unsigned short*a){return cutils_cdar_DynamicArray_void_ptr_push(d,i,c,a);}
bool cutils_cdar_DynamicArray_unsigned_short_set(cutils_cdar_DynamicArray_unsigned_short*d,size_t i,size_t c,unsigned short*s){return cutils_cdar_DynamicArray_void_ptr_set(d,i,c,s);}
size_t cutils_cdar_DynamicArray_unsigned_short_pop(cutils_cdar_DynamicArray_unsigned_short*d,size_t i,size_t c,unsigned short*a){return cutils_cdar_DynamicArray_void_ptr_pop(d,i,c,a);}
size_t cutils_cdar_DynamicArray_unsigned_short_sub(cutils_cdar_DynamicArray_unsigned_short*d,size_t i,size_t c,unsigned short*a){return cutils_cdar_DynamicArray_void_ptr_sub(d,i,c,a);}
unsigned short cutils_cdar_DynamicArray_unsigned_short_get(cutils_cdar_DynamicArray_unsigned_short*d,size_t i){return *(unsigned short*)cutils_cdar_DynamicArray_void_ptr_get(d,i);}
bool cutils_cdar_DynamicArray_unsigned_short_find(cutils_cdar_DynamicArray_unsigned_short*d,bool(*f)(const void*,const void*,size_t),const void*p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_find(d,f,p,i);}
size_t cutils_cdar_DynamicArray_unsigned_short_findall(cutils_cdar_DynamicArray_unsigned_short*d,bool(*f)(const void*,const void*,size_t),const void*p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_findall(d,f,p,i);}
bool cutils_cdar_DynamicArray_unsigned_short_format(const unsigned short*i,char**b,size_t*s){snprintf(*b,*s,"%hu",*i);return true;}
bool cutils_cdar_DynamicArray_unsigned_short_compare(const void*p1,const void*p2,size_t s){return !memcmp(p1,p2,s);}
void(*cutils_cdar_DynamicArray_unsigned_short_del)(cutils_cdar_DynamicArray_unsigned_short*)=cutils_cdar_DynamicArray_void_ptr_del;
size_t(*cutils_cdar_DynamicArray_unsigned_short_len)(cutils_cdar_DynamicArray_unsigned_short*)=cutils_cdar_DynamicArray_void_ptr_len;
size_t(*cutils_cdar_DynamicArray_unsigned_short_size)(cutils_cdar_DynamicArray_unsigned_short*)=cutils_cdar_DynamicArray_void_ptr_size;
bool(*cutils_cdar_DynamicArray_unsigned_short_resize)(cutils_cdar_DynamicArray_unsigned_short*,size_t)=cutils_cdar_DynamicArray_void_ptr_resize;
bool(*cutils_cdar_DynamicArray_unsigned_short_swap)(cutils_cdar_DynamicArray_unsigned_short*,size_t,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_swap;
bool(*cutils_cdar_DynamicArray_unsigned_short_reverse)(cutils_cdar_DynamicArray_unsigned_short*)=cutils_cdar_DynamicArray_void_ptr_reverse;
size_t(*cutils_cdar_DynamicArray_unsigned_short_pull)(cutils_cdar_DynamicArray_unsigned_short*,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_pull;
void(*cutils_cdar_DynamicArray_unsigned_short_truncate)(cutils_cdar_DynamicArray_unsigned_short*,size_t)=cutils_cdar_DynamicArray_void_ptr_truncate;
void(*cutils_cdar_DynamicArray_unsigned_short_clear)(cutils_cdar_DynamicArray_unsigned_short*)=cutils_cdar_DynamicArray_void_ptr_clear;
void(*cutils_cdar_DynamicArray_unsigned_short_map)(cutils_cdar_DynamicArray_unsigned_short*,size_t,size_t,void(*)(size_t,unsigned short*))=cutils_cdar_DynamicArray_void_ptr_map;
void(*cutils_cdar_DynamicArray_unsigned_short_print)(cutils_cdar_DynamicArray_unsigned_short*,FILE*,const char*,bool(*)())=cutils_cdar_DynamicArray_void_ptr_print;
/*----------------------------------------------------------------------------*/
typedef cutils_cdar_DynamicArray_void_ptr cutils_cdar_DynamicArray_int;
bool cutils_cdar_DynamicArray_int_new(cutils_cdar_DynamicArray_int**d,size_t c,int*a){return cutils_cdar_DynamicArray_void_ptr_new(d,sizeof(int),c,a);}
int* cutils_cdar_DynamicArray_int_data(cutils_cdar_DynamicArray_int*d,size_t*s,size_t*c){return cutils_cdar_DynamicArray_void_ptr_data(d,s,c);}
int* cutils_cdar_DynamicArray_int_raw(cutils_cdar_DynamicArray_int*d){return (int*)cutils_cdar_DynamicArray_void_ptr_raw(d);}
bool cutils_cdar_DynamicArray_int_append(cutils_cdar_DynamicArray_int*d,size_t c,int*a){return cutils_cdar_DynamicArray_void_ptr_append(d,c,a);}
bool cutils_cdar_DynamicArray_int_push(cutils_cdar_DynamicArray_int*d,size_t i,size_t c,int*a){return cutils_cdar_DynamicArray_void_ptr_push(d,i,c,a);}
bool cutils_cdar_DynamicArray_int_set(cutils_cdar_DynamicArray_int*d,size_t i,size_t c,int*s){return cutils_cdar_DynamicArray_void_ptr_set(d,i,c,s);}
size_t cutils_cdar_DynamicArray_int_pop(cutils_cdar_DynamicArray_int*d,size_t i,size_t c,int*a){return cutils_cdar_DynamicArray_void_ptr_pop(d,i,c,a);}
size_t cutils_cdar_DynamicArray_int_sub(cutils_cdar_DynamicArray_int*d,size_t i,size_t c,int*a){return cutils_cdar_DynamicArray_void_ptr_sub(d,i,c,a);}
int cutils_cdar_DynamicArray_int_get(cutils_cdar_DynamicArray_int*d,size_t i){return *(int*)cutils_cdar_DynamicArray_void_ptr_get(d,i);}
bool cutils_cdar_DynamicArray_int_find(cutils_cdar_DynamicArray_int*d,bool(*f)(const void*,const void*,size_t),const void*p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_find(d,f,p,i);}
size_t cutils_cdar_DynamicArray_int_findall(cutils_cdar_DynamicArray_int*d,bool(*f)(const void*,const void*,size_t),const void*p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_findall(d,f,p,i);}
bool cutils_cdar_DynamicArray_int_format(const int*i,char**b,size_t*s){snprintf(*b,*s,"%d",*i);return true;}
bool cutils_cdar_DynamicArray_int_compare(const void*p1,const void*p2,size_t s){return !memcmp(p1,p2,s);}
void(*cutils_cdar_DynamicArray_int_del)(cutils_cdar_DynamicArray_int*)=cutils_cdar_DynamicArray_void_ptr_del;
size_t(*cutils_cdar_DynamicArray_int_len)(cutils_cdar_DynamicArray_int*)=cutils_cdar_DynamicArray_void_ptr_len;
size_t(*cutils_cdar_DynamicArray_int_size)(cutils_cdar_DynamicArray_int*)=cutils_cdar_DynamicArray_void_ptr_size;
bool(*cutils_cdar_DynamicArray_int_resize)(cutils_cdar_DynamicArray_int*,size_t)=cutils_cdar_DynamicArray_void_ptr_resize;
bool(*cutils_cdar_DynamicArray_int_swap)(cutils_cdar_DynamicArray_int*,size_t,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_swap;
bool(*cutils_cdar_DynamicArray_int_reverse)(cutils_cdar_DynamicArray_int*)=cutils_cdar_DynamicArray_void_ptr_reverse;
size_t(*cutils_cdar_DynamicArray_int_pull)(cutils_cdar_DynamicArray_int*,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_pull;
void(*cutils_cdar_DynamicArray_int_truncate)(cutils_cdar_DynamicArray_int*,size_t)=cutils_cdar_DynamicArray_void_ptr_truncate;
void(*cutils_cdar_DynamicArray_int_clear)(cutils_cdar_DynamicArray_int*)=cutils_cdar_DynamicArray_void_ptr_clear;
void(*cutils_cdar_DynamicArray_int_map)(cutils_cdar_DynamicArray_int*,size_t,size_t,void(*)(size_t,int*))=cutils_cdar_DynamicArray_void_ptr_map;
void(*cutils_cdar_DynamicArray_int_print)(cutils_cdar_DynamicArray_int*,FILE*,const char*,bool(*)())=cutils_cdar_DynamicArray_void_ptr_print;
/*----------------------------------------------------------------------------*/
typedef cutils_cdar_DynamicArray_void_ptr cutils_cdar_DynamicArray_unsigned_int;
bool cutils_cdar_DynamicArray_unsigned_int_new(cutils_cdar_DynamicArray_unsigned_int**d,size_t c,unsigned int*a){return cutils_cdar_DynamicArray_void_ptr_new(d,sizeof(unsigned int),c,a);}
unsigned int* cutils_cdar_DynamicArray_unsigned_int_data(cutils_cdar_DynamicArray_unsigned_int*d,size_t*s,size_t*c){return cutils_cdar_DynamicArray_void_ptr_data(d,s,c);}
unsigned int* cutils_cdar_DynamicArray_unsigned_int_raw(cutils_cdar_DynamicArray_unsigned_int*d){return (unsigned int*)cutils_cdar_DynamicArray_void_ptr_raw(d);}
bool cutils_cdar_DynamicArray_unsigned_int_append(cutils_cdar_DynamicArray_unsigned_int*d,size_t c,unsigned int*a){return cutils_cdar_DynamicArray_void_ptr_append(d,c,a);}
bool cutils_cdar_DynamicArray_unsigned_int_push(cutils_cdar_DynamicArray_unsigned_int*d,size_t i,size_t c,unsigned int*a){return cutils_cdar_DynamicArray_void_ptr_push(d,i,c,a);}
bool cutils_cdar_DynamicArray_unsigned_int_set(cutils_cdar_DynamicArray_unsigned_int*d,size_t i,size_t c,unsigned int*s){return cutils_cdar_DynamicArray_void_ptr_set(d,i,c,s);}
size_t cutils_cdar_DynamicArray_unsigned_int_pop(cutils_cdar_DynamicArray_unsigned_int*d,size_t i,size_t c,unsigned int*a){return cutils_cdar_DynamicArray_void_ptr_pop(d,i,c,a);}
size_t cutils_cdar_DynamicArray_unsigned_int_sub(cutils_cdar_DynamicArray_unsigned_int*d,size_t i,size_t c,unsigned int*a){return cutils_cdar_DynamicArray_void_ptr_sub(d,i,c,a);}
unsigned int cutils_cdar_DynamicArray_unsigned_int_get(cutils_cdar_DynamicArray_unsigned_int*d,size_t i){return *(unsigned int*)cutils_cdar_DynamicArray_void_ptr_get(d,i);}
bool cutils_cdar_DynamicArray_unsigned_int_find(cutils_cdar_DynamicArray_unsigned_int*d,bool(*f)(const void*,const void*,size_t),const void*p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_find(d,f,p,i);}
size_t cutils_cdar_DynamicArray_unsigned_int_findall(cutils_cdar_DynamicArray_unsigned_int*d,bool(*f)(const void*,const void*,size_t),const void*p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_findall(d,f,p,i);}
bool cutils_cdar_DynamicArray_unsigned_int_format(const unsigned int*i,char**b,size_t*s){snprintf(*b,*s,"%u",*i);return true;}
bool cutils_cdar_DynamicArray_unsigned_int_compare(const void*p1,const void*p2,size_t s){return !memcmp(p1,p2,s);}
void(*cutils_cdar_DynamicArray_unsigned_int_del)(cutils_cdar_DynamicArray_unsigned_int*)=cutils_cdar_DynamicArray_void_ptr_del;
size_t(*cutils_cdar_DynamicArray_unsigned_int_len)(cutils_cdar_DynamicArray_unsigned_int*)=cutils_cdar_DynamicArray_void_ptr_len;
size_t(*cutils_cdar_DynamicArray_unsigned_int_size)(cutils_cdar_DynamicArray_unsigned_int*)=cutils_cdar_DynamicArray_void_ptr_size;
bool(*cutils_cdar_DynamicArray_unsigned_int_resize)(cutils_cdar_DynamicArray_unsigned_int*,size_t)=cutils_cdar_DynamicArray_void_ptr_resize;
bool(*cutils_cdar_DynamicArray_unsigned_int_swap)(cutils_cdar_DynamicArray_unsigned_int*,size_t,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_swap;
bool(*cutils_cdar_DynamicArray_unsigned_int_reverse)(cutils_cdar_DynamicArray_unsigned_int*)=cutils_cdar_DynamicArray_void_ptr_reverse;
size_t(*cutils_cdar_DynamicArray_unsigned_int_pull)(cutils_cdar_DynamicArray_unsigned_int*,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_pull;
void(*cutils_cdar_DynamicArray_unsigned_int_truncate)(cutils_cdar_DynamicArray_unsigned_int*,size_t)=cutils_cdar_DynamicArray_void_ptr_truncate;
void(*cutils_cdar_DynamicArray_unsigned_int_clear)(cutils_cdar_DynamicArray_unsigned_int*)=cutils_cdar_DynamicArray_void_ptr_clear;
void(*cutils_cdar_DynamicArray_unsigned_int_map)(cutils_cdar_DynamicArray_unsigned_int*,size_t,size_t,void(*)(size_t,unsigned int*))=cutils_cdar_DynamicArray_void_ptr_map;
void(*cutils_cdar_DynamicArray_unsigned_int_print)(cutils_cdar_DynamicArray_unsigned_int*,FILE*,const char*,bool(*)())=cutils_cdar_DynamicArray_void_ptr_print;
/*----------------------------------------------------------------------------*/
typedef cutils_cdar_DynamicArray_void_ptr cutils_cdar_DynamicArray_long;
bool cutils_cdar_DynamicArray_long_new(cutils_cdar_DynamicArray_long**d,size_t c,long*a){return cutils_cdar_DynamicArray_void_ptr_new(d,sizeof(long),c,a);}
long* cutils_cdar_DynamicArray_long_data(cutils_cdar_DynamicArray_long*d,size_t*s,size_t*c){return cutils_cdar_DynamicArray_void_ptr_data(d,s,c);}
long* cutils_cdar_DynamicArray_long_raw(cutils_cdar_DynamicArray_long*d){return (long*)cutils_cdar_DynamicArray_void_ptr_raw(d);}
bool cutils_cdar_DynamicArray_long_append(cutils_cdar_DynamicArray_long*d,size_t c,long*a){return cutils_cdar_DynamicArray_void_ptr_append(d,c,a);}
bool cutils_cdar_DynamicArray_long_push(cutils_cdar_DynamicArray_long*d,size_t i,size_t c,long*a){return cutils_cdar_DynamicArray_void_ptr_push(d,i,c,a);}
bool cutils_cdar_DynamicArray_long_set(cutils_cdar_DynamicArray_long*d,size_t i,size_t c,long*s){return cutils_cdar_DynamicArray_void_ptr_set(d,i,c,s);}
size_t cutils_cdar_DynamicArray_long_pop(cutils_cdar_DynamicArray_long*d,size_t i,size_t c,long*a){return cutils_cdar_DynamicArray_void_ptr_pop(d,i,c,a);}
size_t cutils_cdar_DynamicArray_long_sub(cutils_cdar_DynamicArray_long*d,size_t i,size_t c,long*a){return cutils_cdar_DynamicArray_void_ptr_sub(d,i,c,a);}
long cutils_cdar_DynamicArray_long_get(cutils_cdar_DynamicArray_long*d,size_t i){return *(long*)cutils_cdar_DynamicArray_void_ptr_get(d,i);}
bool cutils_cdar_DynamicArray_long_find(cutils_cdar_DynamicArray_long*d,bool(*f)(const void*,const void*,size_t),const void*p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_find(d,f,p,i);}
size_t cutils_cdar_DynamicArray_long_findall(cutils_cdar_DynamicArray_long*d,bool(*f)(const void*,const void*,size_t),const void*p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_findall(d,f,p,i);}
bool cutils_cdar_DynamicArray_long_format(const long*i,char**b,size_t*s){snprintf(*b,*s,"%ld",*i);return true;}
bool cutils_cdar_DynamicArray_long_compare(const void*p1,const void*p2,size_t s){return !memcmp(p1,p2,s);}
void(*cutils_cdar_DynamicArray_long_del)(cutils_cdar_DynamicArray_long*)=cutils_cdar_DynamicArray_void_ptr_del;
size_t(*cutils_cdar_DynamicArray_long_len)(cutils_cdar_DynamicArray_long*)=cutils_cdar_DynamicArray_void_ptr_len;
size_t(*cutils_cdar_DynamicArray_long_size)(cutils_cdar_DynamicArray_long*)=cutils_cdar_DynamicArray_void_ptr_size;
bool(*cutils_cdar_DynamicArray_long_resize)(cutils_cdar_DynamicArray_long*,size_t)=cutils_cdar_DynamicArray_void_ptr_resize;
bool(*cutils_cdar_DynamicArray_long_swap)(cutils_cdar_DynamicArray_long*,size_t,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_swap;
bool(*cutils_cdar_DynamicArray_long_reverse)(cutils_cdar_DynamicArray_long*)=cutils_cdar_DynamicArray_void_ptr_reverse;
size_t(*cutils_cdar_DynamicArray_long_pull)(cutils_cdar_DynamicArray_long*,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_pull;
void(*cutils_cdar_DynamicArray_long_truncate)(cutils_cdar_DynamicArray_long*,size_t)=cutils_cdar_DynamicArray_void_ptr_truncate;
void(*cutils_cdar_DynamicArray_long_clear)(cutils_cdar_DynamicArray_long*)=cutils_cdar_DynamicArray_void_ptr_clear;
void(*cutils_cdar_DynamicArray_long_map)(cutils_cdar_DynamicArray_long*,size_t,size_t,void(*)(size_t,long*))=cutils_cdar_DynamicArray_void_ptr_map;
void(*cutils_cdar_DynamicArray_long_print)(cutils_cdar_DynamicArray_long*,FILE*,const char*,bool(*)())=cutils_cdar_DynamicArray_void_ptr_print;
/*----------------------------------------------------------------------------*/
typedef cutils_cdar_DynamicArray_void_ptr cutils_cdar_DynamicArray_unsigned_long;
bool cutils_cdar_DynamicArray_unsigned_long_new(cutils_cdar_DynamicArray_unsigned_long**d,size_t c,unsigned long*a){return cutils_cdar_DynamicArray_void_ptr_new(d,sizeof(unsigned long),c,a);}
unsigned long* cutils_cdar_DynamicArray_unsigned_long_data(cutils_cdar_DynamicArray_unsigned_long*d,size_t*s,size_t*c){return cutils_cdar_DynamicArray_void_ptr_data(d,s,c);}
unsigned long* cutils_cdar_DynamicArray_unsigned_long_raw(cutils_cdar_DynamicArray_unsigned_long*d){return (unsigned long*)cutils_cdar_DynamicArray_void_ptr_raw(d);}
bool cutils_cdar_DynamicArray_unsigned_long_append(cutils_cdar_DynamicArray_unsigned_long*d,size_t c,unsigned long*a){return cutils_cdar_DynamicArray_void_ptr_append(d,c,a);}
bool cutils_cdar_DynamicArray_unsigned_long_push(cutils_cdar_DynamicArray_unsigned_long*d,size_t i,size_t c,unsigned long*a){return cutils_cdar_DynamicArray_void_ptr_push(d,i,c,a);}
bool cutils_cdar_DynamicArray_unsigned_long_set(cutils_cdar_DynamicArray_unsigned_long*d,size_t i,size_t c,unsigned long*s){return cutils_cdar_DynamicArray_void_ptr_set(d,i,c,s);}
size_t cutils_cdar_DynamicArray_unsigned_long_pop(cutils_cdar_DynamicArray_unsigned_long*d,size_t i,size_t c,unsigned long*a){return cutils_cdar_DynamicArray_void_ptr_pop(d,i,c,a);}
size_t cutils_cdar_DynamicArray_unsigned_long_sub(cutils_cdar_DynamicArray_unsigned_long*d,size_t i,size_t c,unsigned long*a){return cutils_cdar_DynamicArray_void_ptr_sub(d,i,c,a);}
unsigned long cutils_cdar_DynamicArray_unsigned_long_get(cutils_cdar_DynamicArray_unsigned_long*d,size_t i){return *(unsigned long*)cutils_cdar_DynamicArray_void_ptr_get(d,i);}
bool cutils_cdar_DynamicArray_unsigned_long_find(cutils_cdar_DynamicArray_unsigned_long*d,bool(*f)(const void*,const void*,size_t),const void*p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_find(d,f,p,i);}
size_t cutils_cdar_DynamicArray_unsigned_long_findall(cutils_cdar_DynamicArray_unsigned_long*d,bool(*f)(const void*,const void*,size_t),const void*p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_findall(d,f,p,i);}
bool cutils_cdar_DynamicArray_unsigned_long_format(const unsigned long*i,char**b,size_t*s){snprintf(*b,*s,"%lu",*i);return true;}
bool cutils_cdar_DynamicArray_unsigned_long_compare(const void*p1,const void*p2,size_t s){return !memcmp(p1,p2,s);}
void(*cutils_cdar_DynamicArray_unsigned_long_del)(cutils_cdar_DynamicArray_unsigned_long*)=cutils_cdar_DynamicArray_void_ptr_del;
size_t(*cutils_cdar_DynamicArray_unsigned_long_len)(cutils_cdar_DynamicArray_unsigned_long*)=cutils_cdar_DynamicArray_void_ptr_len;
size_t(*cutils_cdar_DynamicArray_unsigned_long_size)(cutils_cdar_DynamicArray_unsigned_long*)=cutils_cdar_DynamicArray_void_ptr_size;
bool(*cutils_cdar_DynamicArray_unsigned_long_resize)(cutils_cdar_DynamicArray_unsigned_long*,size_t)=cutils_cdar_DynamicArray_void_ptr_resize;
bool(*cutils_cdar_DynamicArray_unsigned_long_swap)(cutils_cdar_DynamicArray_unsigned_long*,size_t,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_swap;
bool(*cutils_cdar_DynamicArray_unsigned_long_reverse)(cutils_cdar_DynamicArray_unsigned_long*)=cutils_cdar_DynamicArray_void_ptr_reverse;
size_t(*cutils_cdar_DynamicArray_unsigned_long_pull)(cutils_cdar_DynamicArray_unsigned_long*,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_pull;
void(*cutils_cdar_DynamicArray_unsigned_long_truncate)(cutils_cdar_DynamicArray_unsigned_long*,size_t)=cutils_cdar_DynamicArray_void_ptr_truncate;
void(*cutils_cdar_DynamicArray_unsigned_long_clear)(cutils_cdar_DynamicArray_unsigned_long*)=cutils_cdar_DynamicArray_void_ptr_clear;
void(*cutils_cdar_DynamicArray_unsigned_long_map)(cutils_cdar_DynamicArray_unsigned_long*,size_t,size_t,void(*)(size_t,unsigned long*))=cutils_cdar_DynamicArray_void_ptr_map;
void(*cutils_cdar_DynamicArray_unsigned_long_print)(cutils_cdar_DynamicArray_unsigned_long*,FILE*,const char*,bool(*)())=cutils_cdar_DynamicArray_void_ptr_print;
/*----------------------------------------------------------------------------*/
typedef cutils_cdar_DynamicArray_void_ptr cutils_cdar_DynamicArray_long_long;
bool cutils_cdar_DynamicArray_long_long_new(cutils_cdar_DynamicArray_long_long**d,size_t c,long long*a){return cutils_cdar_DynamicArray_void_ptr_new(d,sizeof(long long),c,a);}
long long* cutils_cdar_DynamicArray_long_long_data(cutils_cdar_DynamicArray_long_long*d,size_t*s,size_t*c){return cutils_cdar_DynamicArray_void_ptr_data(d,s,c);}
long long* cutils_cdar_DynamicArray_long_long_raw(cutils_cdar_DynamicArray_long_long*d){return (long long*)cutils_cdar_DynamicArray_void_ptr_raw(d);}
bool cutils_cdar_DynamicArray_long_long_append(cutils_cdar_DynamicArray_long_long*d,size_t c,long long*a){return cutils_cdar_DynamicArray_void_ptr_append(d,c,a);}
bool cutils_cdar_DynamicArray_long_long_push(cutils_cdar_DynamicArray_long_long*d,size_t i,size_t c,long long*a){return cutils_cdar_DynamicArray_void_ptr_push(d,i,c,a);}
bool cutils_cdar_DynamicArray_long_long_set(cutils_cdar_DynamicArray_long_long*d,size_t i,size_t c,long long*s){return cutils_cdar_DynamicArray_void_ptr_set(d,i,c,s);}
size_t cutils_cdar_DynamicArray_long_long_pop(cutils_cdar_DynamicArray_long_long*d,size_t i,size_t c,long long*a){return cutils_cdar_DynamicArray_void_ptr_pop(d,i,c,a);}
size_t cutils_cdar_DynamicArray_long_long_sub(cutils_cdar_DynamicArray_long_long*d,size_t i,size_t c,long long*a){return cutils_cdar_DynamicArray_void_ptr_sub(d,i,c,a);}
long long cutils_cdar_DynamicArray_long_long_get(cutils_cdar_DynamicArray_long_long*d,size_t i){return *(long long*)cutils_cdar_DynamicArray_void_ptr_get(d,i);}
bool cutils_cdar_DynamicArray_long_long_find(cutils_cdar_DynamicArray_long_long*d,bool(*f)(const void*,const void*,size_t),const void*p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_find(d,f,p,i);}
size_t cutils_cdar_DynamicArray_long_long_findall(cutils_cdar_DynamicArray_long_long*d,bool(*f)(const void*,const void*,size_t),const void*p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_findall(d,f,p,i);}
bool cutils_cdar_DynamicArray_long_long_format(const long long*i,char**b,size_t*s){snprintf(*b,*s,"%lld",*i);return true;}
bool cutils_cdar_DynamicArray_long_long_compare(const void*p1,const void*p2,size_t s){return !memcmp(p1,p2,s);}
void(*cutils_cdar_DynamicArray_long_long_del)(cutils_cdar_DynamicArray_long_long*)=cutils_cdar_DynamicArray_void_ptr_del;
size_t(*cutils_cdar_DynamicArray_long_long_len)(cutils_cdar_DynamicArray_long_long*)=cutils_cdar_DynamicArray_void_ptr_len;
size_t(*cutils_cdar_DynamicArray_long_long_size)(cutils_cdar_DynamicArray_long_long*)=cutils_cdar_DynamicArray_void_ptr_size;
bool(*cutils_cdar_DynamicArray_long_long_resize)(cutils_cdar_DynamicArray_long_long*,size_t)=cutils_cdar_DynamicArray_void_ptr_resize;
bool(*cutils_cdar_DynamicArray_long_long_swap)(cutils_cdar_DynamicArray_long_long*,size_t,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_swap;
bool(*cutils_cdar_DynamicArray_long_long_reverse)(cutils_cdar_DynamicArray_long_long*)=cutils_cdar_DynamicArray_void_ptr_reverse;
size_t(*cutils_cdar_DynamicArray_long_long_pull)(cutils_cdar_DynamicArray_long_long*,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_pull;
void(*cutils_cdar_DynamicArray_long_long_truncate)(cutils_cdar_DynamicArray_long_long*,size_t)=cutils_cdar_DynamicArray_void_ptr_truncate;
void(*cutils_cdar_DynamicArray_long_long_clear)(cutils_cdar_DynamicArray_long_long*)=cutils_cdar_DynamicArray_void_ptr_clear;
void(*cutils_cdar_DynamicArray_long_long_map)(cutils_cdar_DynamicArray_long_long*,size_t,size_t,void(*)(size_t,long long*))=cutils_cdar_DynamicArray_void_ptr_map;
void(*cutils_cdar_DynamicArray_long_long_print)(cutils_cdar_DynamicArray_long_long*,FILE*,const char*,bool(*)())=cutils_cdar_DynamicArray_void_ptr_print;
/*----------------------------------------------------------------------------*/
typedef cutils_cdar_DynamicArray_void_ptr cutils_cdar_DynamicArray_unsigned_long_long;
bool cutils_cdar_DynamicArray_unsigned_long_long_new(cutils_cdar_DynamicArray_unsigned_long_long**d,size_t c,unsigned long long*a){return cutils_cdar_DynamicArray_void_ptr_new(d,sizeof(unsigned long long),c,a);}
unsigned long long* cutils_cdar_DynamicArray_unsigned_long_long_data(cutils_cdar_DynamicArray_unsigned_long_long*d,size_t*s,size_t*c){return cutils_cdar_DynamicArray_void_ptr_data(d,s,c);}
unsigned long long* cutils_cdar_DynamicArray_unsigned_long_long_raw(cutils_cdar_DynamicArray_unsigned_long_long*d){return (unsigned long long*)cutils_cdar_DynamicArray_void_ptr_raw(d);}
bool cutils_cdar_DynamicArray_unsigned_long_long_append(cutils_cdar_DynamicArray_unsigned_long_long*d,size_t c,unsigned long long*a){return cutils_cdar_DynamicArray_void_ptr_append(d,c,a);}
bool cutils_cdar_DynamicArray_unsigned_long_long_push(cutils_cdar_DynamicArray_unsigned_long_long*d,size_t i,size_t c,unsigned long long*a){return cutils_cdar_DynamicArray_void_ptr_push(d,i,c,a);}
bool cutils_cdar_DynamicArray_unsigned_long_long_set(cutils_cdar_DynamicArray_unsigned_long_long*d,size_t i,size_t c,unsigned long long*s){return cutils_cdar_DynamicArray_void_ptr_set(d,i,c,s);}
size_t cutils_cdar_DynamicArray_unsigned_long_long_pop(cutils_cdar_DynamicArray_unsigned_long_long*d,size_t i,size_t c,unsigned long long*a){return cutils_cdar_DynamicArray_void_ptr_pop(d,i,c,a);}
size_t cutils_cdar_DynamicArray_unsigned_long_long_sub(cutils_cdar_DynamicArray_unsigned_long_long*d,size_t i,size_t c,unsigned long long*a){return cutils_cdar_DynamicArray_void_ptr_sub(d,i,c,a);}
unsigned long long cutils_cdar_DynamicArray_unsigned_long_long_get(cutils_cdar_DynamicArray_unsigned_long_long*d,size_t i){return *(unsigned long long*)cutils_cdar_DynamicArray_void_ptr_get(d,i);}
bool cutils_cdar_DynamicArray_unsigned_long_long_find(cutils_cdar_DynamicArray_unsigned_long_long*d,bool(*f)(const void*,const void*,size_t),const void*p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_find(d,f,p,i);}
size_t cutils_cdar_DynamicArray_unsigned_long_long_findall(cutils_cdar_DynamicArray_unsigned_long_long*d,bool(*f)(const void*,const void*,size_t),const void*p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_findall(d,f,p,i);}
bool cutils_cdar_DynamicArray_unsigned_long_long_format(const unsigned long long*i,char**b,size_t*s){snprintf(*b,*s,"%llu",*i);return true;}
bool cutils_cdar_DynamicArray_unsigned_long_long_compare(const void*p1,const void*p2,size_t s){return !memcmp(p1,p2,s);}
void(*cutils_cdar_DynamicArray_unsigned_long_long_del)(cutils_cdar_DynamicArray_unsigned_long_long*)=cutils_cdar_DynamicArray_void_ptr_del;
size_t(*cutils_cdar_DynamicArray_unsigned_long_long_len)(cutils_cdar_DynamicArray_unsigned_long_long*)=cutils_cdar_DynamicArray_void_ptr_len;
size_t(*cutils_cdar_DynamicArray_unsigned_long_long_size)(cutils_cdar_DynamicArray_unsigned_long_long*)=cutils_cdar_DynamicArray_void_ptr_size;
bool(*cutils_cdar_DynamicArray_unsigned_long_long_resize)(cutils_cdar_DynamicArray_unsigned_long_long*,size_t)=cutils_cdar_DynamicArray_void_ptr_resize;
bool(*cutils_cdar_DynamicArray_unsigned_long_long_swap)(cutils_cdar_DynamicArray_unsigned_long_long*,size_t,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_swap;
bool(*cutils_cdar_DynamicArray_unsigned_long_long_reverse)(cutils_cdar_DynamicArray_unsigned_long_long*)=cutils_cdar_DynamicArray_void_ptr_reverse;
size_t(*cutils_cdar_DynamicArray_unsigned_long_long_pull)(cutils_cdar_DynamicArray_unsigned_long_long*,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_pull;
void(*cutils_cdar_DynamicArray_unsigned_long_long_truncate)(cutils_cdar_DynamicArray_unsigned_long_long*,size_t)=cutils_cdar_DynamicArray_void_ptr_truncate;
void(*cutils_cdar_DynamicArray_unsigned_long_long_clear)(cutils_cdar_DynamicArray_unsigned_long_long*)=cutils_cdar_DynamicArray_void_ptr_clear;
void(*cutils_cdar_DynamicArray_unsigned_long_long_map)(cutils_cdar_DynamicArray_unsigned_long_long*,size_t,size_t,void(*)(size_t,unsigned long long*))=cutils_cdar_DynamicArray_void_ptr_map;
void(*cutils_cdar_DynamicArray_unsigned_long_long_print)(cutils_cdar_DynamicArray_unsigned_long_long*,FILE*,const char*,bool(*)())=cutils_cdar_DynamicArray_void_ptr_print;
/*----------------------------------------------------------------------------*/
typedef cutils_cdar_DynamicArray_void_ptr cutils_cdar_DynamicArray_float;
bool cutils_cdar_DynamicArray_float_new(cutils_cdar_DynamicArray_float**d,size_t c,float*a){return cutils_cdar_DynamicArray_void_ptr_new(d,sizeof(float),c,a);}
float* cutils_cdar_DynamicArray_float_data(cutils_cdar_DynamicArray_float*d,size_t*s,size_t*c){return cutils_cdar_DynamicArray_void_ptr_data(d,s,c);}
float* cutils_cdar_DynamicArray_float_raw(cutils_cdar_DynamicArray_float*d){return (float*)cutils_cdar_DynamicArray_void_ptr_raw(d);}
bool cutils_cdar_DynamicArray_float_append(cutils_cdar_DynamicArray_float*d,size_t c,float*a){return cutils_cdar_DynamicArray_void_ptr_append(d,c,a);}
bool cutils_cdar_DynamicArray_float_push(cutils_cdar_DynamicArray_float*d,size_t i,size_t c,float*a){return cutils_cdar_DynamicArray_void_ptr_push(d,i,c,a);}
bool cutils_cdar_DynamicArray_float_set(cutils_cdar_DynamicArray_float*d,size_t i,size_t c,float*s){return cutils_cdar_DynamicArray_void_ptr_set(d,i,c,s);}
size_t cutils_cdar_DynamicArray_float_pop(cutils_cdar_DynamicArray_float*d,size_t i,size_t c,float*a){return cutils_cdar_DynamicArray_void_ptr_pop(d,i,c,a);}
size_t cutils_cdar_DynamicArray_float_sub(cutils_cdar_DynamicArray_float*d,size_t i,size_t c,float*a){return cutils_cdar_DynamicArray_void_ptr_sub(d,i,c,a);}
float cutils_cdar_DynamicArray_float_get(cutils_cdar_DynamicArray_float*d,size_t i){return *(float*)cutils_cdar_DynamicArray_void_ptr_get(d,i);}
bool cutils_cdar_DynamicArray_float_find(cutils_cdar_DynamicArray_float*d,bool(*f)(const void*,const void*,size_t),const void*p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_find(d,f,p,i);}
size_t cutils_cdar_DynamicArray_float_findall(cutils_cdar_DynamicArray_float*d,bool(*f)(const void*,const void*,size_t),const void*p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_findall(d,f,p,i);}
bool cutils_cdar_DynamicArray_float_format(const float*i,char**b,size_t*s){snprintf(*b,*s,"%f",*i);return true;}
bool cutils_cdar_DynamicArray_float_compare(const void*p1,const void*p2,size_t s){return cutils_fcmp_float_compare(*(float*)p1,*(float*)p2);}
void(*cutils_cdar_DynamicArray_float_del)(cutils_cdar_DynamicArray_float*)=cutils_cdar_DynamicArray_void_ptr_del;
size_t(*cutils_cdar_DynamicArray_float_len)(cutils_cdar_DynamicArray_float*)=cutils_cdar_DynamicArray_void_ptr_len;
size_t(*cutils_cdar_DynamicArray_float_size)(cutils_cdar_DynamicArray_float*)=cutils_cdar_DynamicArray_void_ptr_size;
bool(*cutils_cdar_DynamicArray_float_resize)(cutils_cdar_DynamicArray_float*,size_t)=cutils_cdar_DynamicArray_void_ptr_resize;
bool(*cutils_cdar_DynamicArray_float_swap)(cutils_cdar_DynamicArray_float*,size_t,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_swap;
bool(*cutils_cdar_DynamicArray_float_reverse)(cutils_cdar_DynamicArray_float*)=cutils_cdar_DynamicArray_void_ptr_reverse;
size_t(*cutils_cdar_DynamicArray_float_pull)(cutils_cdar_DynamicArray_float*,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_pull;
void(*cutils_cdar_DynamicArray_float_truncate)(cutils_cdar_DynamicArray_float*,size_t)=cutils_cdar_DynamicArray_void_ptr_truncate;
void(*cutils_cdar_DynamicArray_float_clear)(cutils_cdar_DynamicArray_float*)=cutils_cdar_DynamicArray_void_ptr_clear;
void(*cutils_cdar_DynamicArray_float_map)(cutils_cdar_DynamicArray_float*,size_t,size_t,void(*)(size_t,float*))=cutils_cdar_DynamicArray_void_ptr_map;
void(*cutils_cdar_DynamicArray_float_print)(cutils_cdar_DynamicArray_float*,FILE*,const char*,bool(*)())=cutils_cdar_DynamicArray_void_ptr_print;
/*----------------------------------------------------------------------------*/
typedef cutils_cdar_DynamicArray_void_ptr cutils_cdar_DynamicArray_double;
bool cutils_cdar_DynamicArray_double_new(cutils_cdar_DynamicArray_double**d,size_t c,double*a){return cutils_cdar_DynamicArray_void_ptr_new(d,sizeof(double),c,a);}
double* cutils_cdar_DynamicArray_double_data(cutils_cdar_DynamicArray_double*d,size_t*s,size_t*c){return cutils_cdar_DynamicArray_void_ptr_data(d,s,c);}
double* cutils_cdar_DynamicArray_double_raw(cutils_cdar_DynamicArray_double*d){return (double*)cutils_cdar_DynamicArray_void_ptr_raw(d);}
bool cutils_cdar_DynamicArray_double_append(cutils_cdar_DynamicArray_double*d,size_t c,double*a){return cutils_cdar_DynamicArray_void_ptr_append(d,c,a);}
bool cutils_cdar_DynamicArray_double_push(cutils_cdar_DynamicArray_double*d,size_t i,size_t c,double*a){return cutils_cdar_DynamicArray_void_ptr_push(d,i,c,a);}
bool cutils_cdar_DynamicArray_double_set(cutils_cdar_DynamicArray_double*d,size_t i,size_t c,double*s){return cutils_cdar_DynamicArray_void_ptr_set(d,i,c,s);}
size_t cutils_cdar_DynamicArray_double_pop(cutils_cdar_DynamicArray_double*d,size_t i,size_t c,double*a){return cutils_cdar_DynamicArray_void_ptr_pop(d,i,c,a);}
size_t cutils_cdar_DynamicArray_double_sub(cutils_cdar_DynamicArray_double*d,size_t i,size_t c,double*a){return cutils_cdar_DynamicArray_void_ptr_sub(d,i,c,a);}
double cutils_cdar_DynamicArray_double_get(cutils_cdar_DynamicArray_double*d,size_t i){return *(double*)cutils_cdar_DynamicArray_void_ptr_get(d,i);}
bool cutils_cdar_DynamicArray_double_find(cutils_cdar_DynamicArray_double*d,bool(*f)(const void*,const void*,size_t),const void*p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_find(d,f,p,i);}
size_t cutils_cdar_DynamicArray_double_findall(cutils_cdar_DynamicArray_double*d,bool(*f)(const void*,const void*,size_t),const void*p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_findall(d,f,p,i);}
bool cutils_cdar_DynamicArray_double_format(const double*i,char**b,size_t*s){snprintf(*b,*s,"%lf",*i);return true;}
bool cutils_cdar_DynamicArray_double_compare(const void*p1,const void*p2,size_t s){return cutils_fcmp_double_compare(*(double*)p1,*(double*)p2);}
void(*cutils_cdar_DynamicArray_double_del)(cutils_cdar_DynamicArray_double*)=cutils_cdar_DynamicArray_void_ptr_del;
size_t(*cutils_cdar_DynamicArray_double_len)(cutils_cdar_DynamicArray_double*)=cutils_cdar_DynamicArray_void_ptr_len;
size_t(*cutils_cdar_DynamicArray_double_size)(cutils_cdar_DynamicArray_double*)=cutils_cdar_DynamicArray_void_ptr_size;
bool(*cutils_cdar_DynamicArray_double_resize)(cutils_cdar_DynamicArray_double*,size_t)=cutils_cdar_DynamicArray_void_ptr_resize;
bool(*cutils_cdar_DynamicArray_double_swap)(cutils_cdar_DynamicArray_double*,size_t,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_swap;
bool(*cutils_cdar_DynamicArray_double_reverse)(cutils_cdar_DynamicArray_double*)=cutils_cdar_DynamicArray_void_ptr_reverse;
size_t(*cutils_cdar_DynamicArray_double_pull)(cutils_cdar_DynamicArray_double*,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_pull;
void(*cutils_cdar_DynamicArray_double_truncate)(cutils_cdar_DynamicArray_double*,size_t)=cutils_cdar_DynamicArray_void_ptr_truncate;
void(*cutils_cdar_DynamicArray_double_clear)(cutils_cdar_DynamicArray_double*)=cutils_cdar_DynamicArray_void_ptr_clear;
void(*cutils_cdar_DynamicArray_double_map)(cutils_cdar_DynamicArray_double*,size_t,size_t,void(*)(size_t,double*))=cutils_cdar_DynamicArray_void_ptr_map;
void(*cutils_cdar_DynamicArray_double_print)(cutils_cdar_DynamicArray_double*,FILE*,const char*,bool(*)())=cutils_cdar_DynamicArray_void_ptr_print;
/*----------------------------------------------------------------------------*/
typedef cutils_cdar_DynamicArray_void_ptr cutils_cdar_DynamicArray_long_double;
bool cutils_cdar_DynamicArray_long_double_new(cutils_cdar_DynamicArray_long_double**d,size_t c,long double*a){return cutils_cdar_DynamicArray_void_ptr_new(d,sizeof(long double),c,a);}
long double* cutils_cdar_DynamicArray_long_double_data(cutils_cdar_DynamicArray_long_double*d,size_t*s,size_t*c){return cutils_cdar_DynamicArray_void_ptr_data(d,s,c);}
long double* cutils_cdar_DynamicArray_long_double_raw(cutils_cdar_DynamicArray_long_double*d){return (long double*)cutils_cdar_DynamicArray_void_ptr_raw(d);}
bool cutils_cdar_DynamicArray_long_double_append(cutils_cdar_DynamicArray_long_double*d,size_t c,long double*a){return cutils_cdar_DynamicArray_void_ptr_append(d,c,a);}
bool cutils_cdar_DynamicArray_long_double_push(cutils_cdar_DynamicArray_long_double*d,size_t i,size_t c,long double*a){return cutils_cdar_DynamicArray_void_ptr_push(d,i,c,a);}
bool cutils_cdar_DynamicArray_long_double_set(cutils_cdar_DynamicArray_long_double*d,size_t i,size_t c,long double*s){return cutils_cdar_DynamicArray_void_ptr_set(d,i,c,s);}
size_t cutils_cdar_DynamicArray_long_double_pop(cutils_cdar_DynamicArray_long_double*d,size_t i,size_t c,long double*a){return cutils_cdar_DynamicArray_void_ptr_pop(d,i,c,a);}
size_t cutils_cdar_DynamicArray_long_double_sub(cutils_cdar_DynamicArray_long_double*d,size_t i,size_t c,long double*a){return cutils_cdar_DynamicArray_void_ptr_sub(d,i,c,a);}
long double cutils_cdar_DynamicArray_long_double_get(cutils_cdar_DynamicArray_long_double*d,size_t i){return *(long double*)cutils_cdar_DynamicArray_void_ptr_get(d,i);}
bool cutils_cdar_DynamicArray_long_double_find(cutils_cdar_DynamicArray_long_double*d,bool(*f)(const void*,const void*,size_t),const void*p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_find(d,f,p,i);}
size_t cutils_cdar_DynamicArray_long_double_findall(cutils_cdar_DynamicArray_long_double*d,bool(*f)(const void*,const void*,size_t),const void*p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_findall(d,f,p,i);}
bool cutils_cdar_DynamicArray_long_double_format(const long double*i,char**b,size_t*s){snprintf(*b,*s,"%Lf",*i);return true;}
bool cutils_cdar_DynamicArray_long_double_compare(const void*p1,const void*p2,size_t s){return cutils_fcmp_long_double_compare(*(long double*)p1,*(long double*)p2);}
void(*cutils_cdar_DynamicArray_long_double_del)(cutils_cdar_DynamicArray_long_double*)=cutils_cdar_DynamicArray_void_ptr_del;
size_t(*cutils_cdar_DynamicArray_long_double_len)(cutils_cdar_DynamicArray_long_double*)=cutils_cdar_DynamicArray_void_ptr_len;
size_t(*cutils_cdar_DynamicArray_long_double_size)(cutils_cdar_DynamicArray_long_double*)=cutils_cdar_DynamicArray_void_ptr_size;
bool(*cutils_cdar_DynamicArray_long_double_resize)(cutils_cdar_DynamicArray_long_double*,size_t)=cutils_cdar_DynamicArray_void_ptr_resize;
bool(*cutils_cdar_DynamicArray_long_double_swap)(cutils_cdar_DynamicArray_long_double*,size_t,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_swap;
bool(*cutils_cdar_DynamicArray_long_double_reverse)(cutils_cdar_DynamicArray_long_double*)=cutils_cdar_DynamicArray_void_ptr_reverse;
size_t(*cutils_cdar_DynamicArray_long_double_pull)(cutils_cdar_DynamicArray_long_double*,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_pull;
void(*cutils_cdar_DynamicArray_long_double_truncate)(cutils_cdar_DynamicArray_long_double*,size_t)=cutils_cdar_DynamicArray_void_ptr_truncate;
void(*cutils_cdar_DynamicArray_long_double_clear)(cutils_cdar_DynamicArray_long_double*)=cutils_cdar_DynamicArray_void_ptr_clear;
void(*cutils_cdar_DynamicArray_long_double_map)(cutils_cdar_DynamicArray_long_double*,size_t,size_t,void(*)(size_t,long double*))=cutils_cdar_DynamicArray_void_ptr_map;
void(*cutils_cdar_DynamicArray_long_double_print)(cutils_cdar_DynamicArray_long_double*,FILE*,const char*,bool(*)())=cutils_cdar_DynamicArray_void_ptr_print;
/*----------------------------------------------------------------------------*/
typedef cutils_cdar_DynamicArray_void_ptr cutils_cdar_DynamicArray_bool;
bool cutils_cdar_DynamicArray_bool_new(cutils_cdar_DynamicArray_bool**d,size_t c,bool*a){return cutils_cdar_DynamicArray_void_ptr_new(d,sizeof(bool),c,a);}
bool* cutils_cdar_DynamicArray_bool_data(cutils_cdar_DynamicArray_bool*d,size_t*s,size_t*c){return cutils_cdar_DynamicArray_void_ptr_data(d,s,c);}
bool* cutils_cdar_DynamicArray_bool_raw(cutils_cdar_DynamicArray_bool*d){return (bool*)cutils_cdar_DynamicArray_void_ptr_raw(d);}
bool cutils_cdar_DynamicArray_bool_append(cutils_cdar_DynamicArray_bool*d,size_t c,bool*a){return cutils_cdar_DynamicArray_void_ptr_append(d,c,a);}
bool cutils_cdar_DynamicArray_bool_push(cutils_cdar_DynamicArray_bool*d,size_t i,size_t c,bool*a){return cutils_cdar_DynamicArray_void_ptr_push(d,i,c,a);}
bool cutils_cdar_DynamicArray_bool_set(cutils_cdar_DynamicArray_bool*d,size_t i,size_t c,bool*s){return cutils_cdar_DynamicArray_void_ptr_set(d,i,c,s);}
size_t cutils_cdar_DynamicArray_bool_pop(cutils_cdar_DynamicArray_bool*d,size_t i,size_t c,bool*a){return cutils_cdar_DynamicArray_void_ptr_pop(d,i,c,a);}
size_t cutils_cdar_DynamicArray_bool_sub(cutils_cdar_DynamicArray_bool*d,size_t i,size_t c,bool*a){return cutils_cdar_DynamicArray_void_ptr_sub(d,i,c,a);}
bool cutils_cdar_DynamicArray_bool_get(cutils_cdar_DynamicArray_bool*d,size_t i){return *(bool*)cutils_cdar_DynamicArray_void_ptr_get(d,i);}
bool cutils_cdar_DynamicArray_bool_find(cutils_cdar_DynamicArray_bool*d,bool(*f)(const void*,const void*,size_t),const void*p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_find(d,f,p,i);}
size_t cutils_cdar_DynamicArray_bool_findall(cutils_cdar_DynamicArray_bool*d,bool(*f)(const void*,const void*,size_t),const void*p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_findall(d,f,p,i);}
bool cutils_cdar_DynamicArray_bool_format(const bool*i,char**b,size_t*s){snprintf(*b,*s,"%s",*i?"true":"false");return true;}
bool cutils_cdar_DynamicArray_bool_compare(const void*p1,const void*p2,size_t s){return !memcmp(p1,p2,s);}
void(*cutils_cdar_DynamicArray_bool_del)(cutils_cdar_DynamicArray_bool*)=cutils_cdar_DynamicArray_void_ptr_del;
size_t(*cutils_cdar_DynamicArray_bool_len)(cutils_cdar_DynamicArray_bool*)=cutils_cdar_DynamicArray_void_ptr_len;
size_t(*cutils_cdar_DynamicArray_bool_size)(cutils_cdar_DynamicArray_bool*)=cutils_cdar_DynamicArray_void_ptr_size;
bool(*cutils_cdar_DynamicArray_bool_resize)(cutils_cdar_DynamicArray_bool*,size_t)=cutils_cdar_DynamicArray_void_ptr_resize;
bool(*cutils_cdar_DynamicArray_bool_swap)(cutils_cdar_DynamicArray_bool*,size_t,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_swap;
bool(*cutils_cdar_DynamicArray_bool_reverse)(cutils_cdar_DynamicArray_bool*)=cutils_cdar_DynamicArray_void_ptr_reverse;
size_t(*cutils_cdar_DynamicArray_bool_pull)(cutils_cdar_DynamicArray_bool*,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_pull;
void(*cutils_cdar_DynamicArray_bool_truncate)(cutils_cdar_DynamicArray_bool*,size_t)=cutils_cdar_DynamicArray_void_ptr_truncate;
void(*cutils_cdar_DynamicArray_bool_clear)(cutils_cdar_DynamicArray_bool*)=cutils_cdar_DynamicArray_void_ptr_clear;
void(*cutils_cdar_DynamicArray_bool_map)(cutils_cdar_DynamicArray_bool*,size_t,size_t,void(*)(size_t,bool*))=cutils_cdar_DynamicArray_void_ptr_map;
void(*cutils_cdar_DynamicArray_bool_print)(cutils_cdar_DynamicArray_bool*,FILE*,const char*,bool(*)())=cutils_cdar_DynamicArray_void_ptr_print;
/*----------------------------------------------------------------------------*/
typedef cutils_cdar_DynamicArray_void_ptr cutils_cdar_DynamicArray_size_t;
bool cutils_cdar_DynamicArray_size_t_new(cutils_cdar_DynamicArray_size_t**d,size_t c,size_t*a){return cutils_cdar_DynamicArray_void_ptr_new(d,sizeof(size_t),c,a);}
size_t* cutils_cdar_DynamicArray_size_t_data(cutils_cdar_DynamicArray_size_t*d,size_t*s,size_t*c){return cutils_cdar_DynamicArray_void_ptr_data(d,s,c);}
size_t* cutils_cdar_DynamicArray_size_t_raw(cutils_cdar_DynamicArray_size_t*d){return (size_t*)cutils_cdar_DynamicArray_void_ptr_raw(d);}
bool cutils_cdar_DynamicArray_size_t_append(cutils_cdar_DynamicArray_size_t*d,size_t c,size_t*a){return cutils_cdar_DynamicArray_void_ptr_append(d,c,a);}
bool cutils_cdar_DynamicArray_size_t_push(cutils_cdar_DynamicArray_size_t*d,size_t i,size_t c,size_t*a){return cutils_cdar_DynamicArray_void_ptr_push(d,i,c,a);}
bool cutils_cdar_DynamicArray_size_t_set(cutils_cdar_DynamicArray_size_t*d,size_t i,size_t c,size_t*s){return cutils_cdar_DynamicArray_void_ptr_set(d,i,c,s);}
size_t cutils_cdar_DynamicArray_size_t_pop(cutils_cdar_DynamicArray_size_t*d,size_t i,size_t c,size_t*a){return cutils_cdar_DynamicArray_void_ptr_pop(d,i,c,a);}
size_t cutils_cdar_DynamicArray_size_t_sub(cutils_cdar_DynamicArray_size_t*d,size_t i,size_t c,size_t*a){return cutils_cdar_DynamicArray_void_ptr_sub(d,i,c,a);}
size_t cutils_cdar_DynamicArray_size_t_get(cutils_cdar_DynamicArray_size_t*d,size_t i){return *(size_t*)cutils_cdar_DynamicArray_void_ptr_get(d,i);}
bool cutils_cdar_DynamicArray_size_t_find(cutils_cdar_DynamicArray_size_t*d,bool(*f)(const void*,const void*,size_t),const void*p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_find(d,f,p,i);}
size_t cutils_cdar_DynamicArray_size_t_findall(cutils_cdar_DynamicArray_size_t*d,bool(*f)(const void*,const void*,size_t),const void*p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_findall(d,f,p,i);}
bool cutils_cdar_DynamicArray_size_t_format(const size_t*i,char**b,size_t*s){snprintf(*b,*s,"%zu",*i);return true;}
bool cutils_cdar_DynamicArray_size_t_compare(const void*p1,const void*p2,size_t s){return !memcmp(p1,p2,s);}
void(*cutils_cdar_DynamicArray_size_t_del)(cutils_cdar_DynamicArray_size_t*)=cutils_cdar_DynamicArray_void_ptr_del;
size_t(*cutils_cdar_DynamicArray_size_t_len)(cutils_cdar_DynamicArray_size_t*)=cutils_cdar_DynamicArray_void_ptr_len;
size_t(*cutils_cdar_DynamicArray_size_t_size)(cutils_cdar_DynamicArray_size_t*)=cutils_cdar_DynamicArray_void_ptr_size;
bool(*cutils_cdar_DynamicArray_size_t_resize)(cutils_cdar_DynamicArray_size_t*,size_t)=cutils_cdar_DynamicArray_void_ptr_resize;
bool(*cutils_cdar_DynamicArray_size_t_swap)(cutils_cdar_DynamicArray_size_t*,size_t,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_swap;
bool(*cutils_cdar_DynamicArray_size_t_reverse)(cutils_cdar_DynamicArray_size_t*)=cutils_cdar_DynamicArray_void_ptr_reverse;
size_t(*cutils_cdar_DynamicArray_size_t_pull)(cutils_cdar_DynamicArray_size_t*,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_pull;
void(*cutils_cdar_DynamicArray_size_t_truncate)(cutils_cdar_DynamicArray_size_t*,size_t)=cutils_cdar_DynamicArray_void_ptr_truncate;
void(*cutils_cdar_DynamicArray_size_t_clear)(cutils_cdar_DynamicArray_size_t*)=cutils_cdar_DynamicArray_void_ptr_clear;
void(*cutils_cdar_DynamicArray_size_t_map)(cutils_cdar_DynamicArray_size_t*,size_t,size_t,void(*)(size_t,size_t*))=cutils_cdar_DynamicArray_void_ptr_map;
void(*cutils_cdar_DynamicArray_size_t_print)(cutils_cdar_DynamicArray_size_t*,FILE*,const char*,bool(*)())=cutils_cdar_DynamicArray_void_ptr_print;
/*----------------------------------------------------------------------------*/
typedef cutils_cdar_DynamicArray_void_ptr cutils_cdar_DynamicArray_ptrdiff_t;
bool cutils_cdar_DynamicArray_ptrdiff_t_new(cutils_cdar_DynamicArray_ptrdiff_t**d,size_t c,ptrdiff_t*a){return cutils_cdar_DynamicArray_void_ptr_new(d,sizeof(ptrdiff_t),c,a);}
ptrdiff_t* cutils_cdar_DynamicArray_ptrdiff_t_data(cutils_cdar_DynamicArray_ptrdiff_t*d,size_t*s,size_t*c){return cutils_cdar_DynamicArray_void_ptr_data(d,s,c);}
ptrdiff_t* cutils_cdar_DynamicArray_ptrdiff_t_raw(cutils_cdar_DynamicArray_ptrdiff_t*d){return (ptrdiff_t*)cutils_cdar_DynamicArray_void_ptr_raw(d);}
bool cutils_cdar_DynamicArray_ptrdiff_t_append(cutils_cdar_DynamicArray_ptrdiff_t*d,size_t c,ptrdiff_t*a){return cutils_cdar_DynamicArray_void_ptr_append(d,c,a);}
bool cutils_cdar_DynamicArray_ptrdiff_t_push(cutils_cdar_DynamicArray_ptrdiff_t*d,size_t i,size_t c,ptrdiff_t*a){return cutils_cdar_DynamicArray_void_ptr_push(d,i,c,a);}
bool cutils_cdar_DynamicArray_ptrdiff_t_set(cutils_cdar_DynamicArray_ptrdiff_t*d,size_t i,size_t c,ptrdiff_t*s){return cutils_cdar_DynamicArray_void_ptr_set(d,i,c,s);}
size_t cutils_cdar_DynamicArray_ptrdiff_t_pop(cutils_cdar_DynamicArray_ptrdiff_t*d,size_t i,size_t c,ptrdiff_t*a){return cutils_cdar_DynamicArray_void_ptr_pop(d,i,c,a);}
size_t cutils_cdar_DynamicArray_ptrdiff_t_sub(cutils_cdar_DynamicArray_ptrdiff_t*d,size_t i,size_t c,ptrdiff_t*a){return cutils_cdar_DynamicArray_void_ptr_sub(d,i,c,a);}
ptrdiff_t cutils_cdar_DynamicArray_ptrdiff_t_get(cutils_cdar_DynamicArray_ptrdiff_t*d,size_t i){return *(ptrdiff_t*)cutils_cdar_DynamicArray_void_ptr_get(d,i);}
bool cutils_cdar_DynamicArray_ptrdiff_t_find(cutils_cdar_DynamicArray_ptrdiff_t*d,bool(*f)(const void*,const void*,size_t),const void*p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_find(d,f,p,i);}
size_t cutils_cdar_DynamicArray_ptrdiff_t_findall(cutils_cdar_DynamicArray_ptrdiff_t*d,bool(*f)(const void*,const void*,size_t),const void*p,size_t*i){return cutils_cdar_DynamicArray_void_ptr_findall(d,f,p,i);}
bool cutils_cdar_DynamicArray_ptrdiff_t_format(const ptrdiff_t*i,char**b,size_t*s){snprintf(*b,*s,"%td",*i);return true;}
bool cutils_cdar_DynamicArray_ptrdiff_t_compare(const void*p1,const void*p2,size_t s){return !memcmp(p1,p2,s);}
void(*cutils_cdar_DynamicArray_ptrdiff_t_del)(cutils_cdar_DynamicArray_ptrdiff_t*)=cutils_cdar_DynamicArray_void_ptr_del;
size_t(*cutils_cdar_DynamicArray_ptrdiff_t_len)(cutils_cdar_DynamicArray_ptrdiff_t*)=cutils_cdar_DynamicArray_void_ptr_len;
size_t(*cutils_cdar_DynamicArray_ptrdiff_t_size)(cutils_cdar_DynamicArray_ptrdiff_t*)=cutils_cdar_DynamicArray_void_ptr_size;
bool(*cutils_cdar_DynamicArray_ptrdiff_t_resize)(cutils_cdar_DynamicArray_ptrdiff_t*,size_t)=cutils_cdar_DynamicArray_void_ptr_resize;
bool(*cutils_cdar_DynamicArray_ptrdiff_t_swap)(cutils_cdar_DynamicArray_ptrdiff_t*,size_t,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_swap;
bool(*cutils_cdar_DynamicArray_ptrdiff_t_reverse)(cutils_cdar_DynamicArray_ptrdiff_t*)=cutils_cdar_DynamicArray_void_ptr_reverse;
size_t(*cutils_cdar_DynamicArray_ptrdiff_t_pull)(cutils_cdar_DynamicArray_ptrdiff_t*,size_t,size_t)=cutils_cdar_DynamicArray_void_ptr_pull;
void(*cutils_cdar_DynamicArray_ptrdiff_t_truncate)(cutils_cdar_DynamicArray_ptrdiff_t*,size_t)=cutils_cdar_DynamicArray_void_ptr_truncate;
void(*cutils_cdar_DynamicArray_ptrdiff_t_clear)(cutils_cdar_DynamicArray_ptrdiff_t*)=cutils_cdar_DynamicArray_void_ptr_clear;
void(*cutils_cdar_DynamicArray_ptrdiff_t_map)(cutils_cdar_DynamicArray_ptrdiff_t*,size_t,size_t,void(*)(size_t,ptrdiff_t*))=cutils_cdar_DynamicArray_void_ptr_map;
void(*cutils_cdar_DynamicArray_ptrdiff_t_print)(cutils_cdar_DynamicArray_ptrdiff_t*,FILE*,const char*,bool(*)())=cutils_cdar_DynamicArray_void_ptr_print;