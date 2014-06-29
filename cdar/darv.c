
// INFO //
// INFO //

/* DOC:
 *      -DCDAR_OPT -- most optimised; no exceptions; not bound checked;
 *       no flag   -- more optimised; no exceptions;     bound checked;
 *      -DCEXC_USE -- less optimised;    exceptions;     bound checked;
 *      requirement: "cexc.h"
 *
 *      -DCDAR_JEM -- allocation functions using jemalloc
 *      requirement: "jemalloc.h"
 */

/*
    DA_int dynamic array
    SL_int single linked list
    DL_int double linked list
    HT_int hash table
 */

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


// TODO: implement: reverses count number of sub data starts at index
// void
// darv_reversesub(DynamicArray *dynarr,
//                 size_t index,
//                 size_t count)

// TODO: consider if an iterator method is necessary or not
// IterObject
// iter(DynamicArray *dynarr,
//      size_t index);
// void *
// next(IterObject *iterator);

// #define copy(dar_ptr_src, dar_ptr_dst)
//     do {
//         if (dar_ptr_dst) del(dar_ptr_src);
//         new(dar_ptr_dst, len(dar_ptr_src), raw(dar_ptr_src));
//     } while (0)

// #define swapto(dar_ptr_src, dar_ptr_dst, index_src, index_dst, count)

// #define appendto(dar_ptr_dst, dar_ptr_src)
//     do {
//         if (!dar_ptr_src) break;
//         append(dar_ptr_dst, len(dar_ptr_src), raw(dar_ptr_src));
//     } while (0)

// #define insertto(dar_ptr_dst, index, dar_ptr_src)
//     do {
//         if (!dar_ptr_src) break;
//         insert(dar_ptr_dst, index, len(dar_ptr_src), raw(dar_ptr_src));
//     } while (0)

// #define setto(dar_ptr_dst, index, dar_ptr_dst)
//     do {
//         if (!dar_ptr_dst) break;
//         set(dar_ptr_dst, index, len(dar_ptr_dst), raw(dar_ptr_dst));
//     } while (0)

// #define popto(dar_ptr_dst, index, count, dar_ptr_src)
//     do {
//         void *temp = malloc((size(dar_ptr_dst) / len(dar_ptr_dst)) * count);
//         if (!temp) break;
//         pop(dar_ptr_src, index, count, temp);
//         append(dar_ptr_dst, count, temp);
//         free(temp);
//     } while (0)


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

} DynamicArray;


/*----------------------------------------------------------------------------*/
static bool
__darv_resize(DynamicArray *dynarr,
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
dartg_new(DynamicArray **dynarr,
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
    DynamicArray *_dynarr = malloc(sizeof(DynamicArray));
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
darv_del(DynamicArray *dynarr)
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
darv_data(DynamicArray *dynarr,
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
darv_raw(DynamicArray *dynarr)
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
darv_len(DynamicArray *dynarr)
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
darv_size(DynamicArray *dynarr)
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
darv_clear(DynamicArray *dynarr)
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
darv_resize(DynamicArray *dynarr,
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
    if (!__darv_resize(dynarr, dynarr->size, count))
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
darv_swap(DynamicArray *dynarr,
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
darv_reverse(DynamicArray *dynarr)
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
darv_append(DynamicArray *dynarr,
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
        if (!__darv_resize(dynarr, item_size, count))
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
darv_insert(DynamicArray *dynarr,
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
    if (!__darv_resize(dynarr, item_size, count))
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
darv_remove(DynamicArray *dynarr,
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
darv_pop(DynamicArray *dynarr,
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
darv_sub(DynamicArray *dynarr,
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
darv_truncate(DynamicArray *dynarr,
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
darv_set(DynamicArray *dynarr,
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
darv_get(DynamicArray *dynarr,
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
darv_find(DynamicArray *dynarr,
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
darv_findall(DynamicArray *dynarr,
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
darv_sort(DynamicArray *dynarr,
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
darv_sortsub(DynamicArray *dynarr,
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
