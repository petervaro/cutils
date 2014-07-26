/* INFO ************************************************************************
**                                                                            **
**                                   cutils                                   **
**                                   ======                                   **
**                                                                            **
**                     Modern and Lightweight C Utilities                     **
**                       Version: 0.8.80.307 (20140726)                       **
**                                                                            **
**                    File: internal/singly_linked_list.h                     **
**                                                                            **
**           Designed and written by Peter Varo. Copyright (c) 2014           **
**             License agreement is provided in the LICENSE file              **
**                 For more info visit: http://www.cutils.org                 **
**                                                                            **
************************************************************************ INFO */

/* !!! DON NOT ADD GUARD TO THIS FILE !!! */

#define FILE_STARTS_HERE
#include <stdio.h>   /* stdout */
#include <stdlib.h>  /* size_t */

/*----------------------------------------------------------------------------*/
typedef struct {} cutils_csll_SinglyLinkedList_void_ptr;
typedef struct {} cutils_csll_SinglyLinkedList_void_ptr_iterator;

/*----------------------------------------------------------------------------*/
extern bool
cutils_csll_SinglyLinkedList_void_ptr_new(cutils_csll_SinglyLinkedList_void_ptr **linlist,
                                          size_t item_size,
                                          size_t count,
                                          void *source);
/*----------------------------------------------------------------------------*/
extern void
cutils_csll_SinglyLinkedList_void_ptr_del(cutils_csll_SinglyLinkedList_void_ptr *linlist);
/*----------------------------------------------------------------------------*/
extern void
cutils_csll_SinglyLinkedList_void_ptr_clear(cutils_csll_SinglyLinkedList_void_ptr *linlist);
/*----------------------------------------------------------------------------*/
extern size_t
cutils_csll_SinglyLinkedList_void_ptr_len(cutils_csll_SinglyLinkedList_void_ptr *linlist);
/*----------------------------------------------------------------------------*/
extern bool
cutils_csll_SinglyLinkedList_void_ptr_swap(cutils_csll_SinglyLinkedList_void_ptr *linlist,
                                           size_t index1,
                                           size_t index2,
                                           size_t count);
/*----------------------------------------------------------------------------*/
extern bool
cutils_csll_SinglyLinkedList_void_ptr_reverse(cutils_csll_SinglyLinkedList_void_ptr *linlist);
/*----------------------------------------------------------------------------*/
extern bool
cutils_csll_SinglyLinkedList_void_ptr_append(cutils_csll_SinglyLinkedList_void_ptr *linlist,
                                             size_t count,
                                             void *source);
/*----------------------------------------------------------------------------*/
extern bool
cutils_csll_SinglyLinkedList_void_ptr_push(cutils_csll_SinglyLinkedList_void_ptr *linlist,
                                           size_t index,
                                           size_t count,
                                           void *source);
/*----------------------------------------------------------------------------*/
extern size_t
cutils_csll_SinglyLinkedList_void_ptr_pull(cutils_csll_SinglyLinkedList_void_ptr *linlist,
                                           size_t index,
                                           size_t count);
/*----------------------------------------------------------------------------*/
extern size_t
cutils_csll_SinglyLinkedList_void_ptr_pop(cutils_csll_SinglyLinkedList_void_ptr *linlist,
                                          size_t index,
                                          size_t count,
                                          void *destination);
/*----------------------------------------------------------------------------*/
extern size_t
cutils_csll_SinglyLinkedList_void_ptr_sub(cutils_csll_SinglyLinkedList_void_ptr *linlist,
                                          size_t index,
                                          size_t count,
                                          void *destination);
/*----------------------------------------------------------------------------*/
extern void
cutils_csll_SinglyLinkedList_void_ptr_truncate(cutils_csll_SinglyLinkedList_void_ptr *linlist,
                                               size_t index);
/*----------------------------------------------------------------------------*/
extern bool
cutils_csll_SinglyLinkedList_void_ptr_set(cutils_csll_SinglyLinkedList_void_ptr *linlist,
                                          size_t index,
                                          size_t count,
                                          void *source);
/*----------------------------------------------------------------------------*/
extern void *
cutils_csll_SinglyLinkedList_void_ptr_get(cutils_csll_SinglyLinkedList_void_ptr *linlist,
                                          size_t index);
/*----------------------------------------------------------------------------*/
extern bool
cutils_csll_SinglyLinkedList_void_ptr_find(cutils_csll_SinglyLinkedList_void_ptr *linlist,
                                           bool (*compare)(const void*, const void*, size_t),
                                           const void *item,
                                           size_t *index);
/*----------------------------------------------------------------------------*/
extern size_t
cutils_csll_SinglyLinkedList_void_ptr_findall(cutils_csll_SinglyLinkedList_void_ptr *linlist,
                                              bool (*compare)(const void*, const void*, size_t),
                                              const void *item,
                                              size_t *indices);
/*----------------------------------------------------------------------------*/
extern cutils_csll_SinglyLinkedList_void_ptr_iterator *
cutils_csll_SinglyLinkedList_void_ptr_iter(cutils_csll_SinglyLinkedList_void_ptr *linlist);
/*----------------------------------------------------------------------------*/
extern bool
cutils_csll_SinglyLinkedList_void_ptr_next(cutils_csll_SinglyLinkedList_void_ptr_iterator *node,
                                           void *data);
/*----------------------------------------------------------------------------*/
extern char *
cutils_csll_SinglyLinkedList_void_ptr_format(const void *data,
                                             char **buffer,
                                             size_t *buffer_size);
/*----------------------------------------------------------------------------*/
extern void
cutils_csll_SinglyLinkedList_void_ptr_print(cutils_csll_SinglyLinkedList_void_ptr *linlist,
                                            FILE *stream,
                                            const char *name,
                                            char *(*format)(const void*, char**, size_t*));



/*----------------------------------------------------------------------------*/
/* Fake CAPI for testing */
#include "cutils/internal/fcmp.h"
typedef cutils_csll_SinglyLinkedList_void_ptr SinglyLinkedList_void_ptr;
typedef cutils_csll_SinglyLinkedList_void_ptr_iterator SinglyLinkedList_void_ptr_iterator;

static bool __csll_fcmp(const void *p1,
                        const void *p2,
                        size_t s)
{
    return cutils_fcmp_float_compare(*(float *)p1, *(float *)p2);
}

#define new(...) cutils_csll_SinglyLinkedList_void_ptr_new(__VA_ARGS__)
#define del(...) cutils_csll_SinglyLinkedList_void_ptr_del(__VA_ARGS__)
#define len(...) cutils_csll_SinglyLinkedList_void_ptr_len(__VA_ARGS__)
#define swap(...) cutils_csll_SinglyLinkedList_void_ptr_swap(__VA_ARGS__)
#define reverse(...) cutils_csll_SinglyLinkedList_void_ptr_reverse(__VA_ARGS__)
#define append(...) cutils_csll_SinglyLinkedList_void_ptr_append(__VA_ARGS__)
#define push(...) cutils_csll_SinglyLinkedList_void_ptr_push(__VA_ARGS__)
#define pull(...) cutils_csll_SinglyLinkedList_void_ptr_pull(__VA_ARGS__)
#define pop(...) cutils_csll_SinglyLinkedList_void_ptr_pop(__VA_ARGS__)
#define sub(...) cutils_csll_SinglyLinkedList_void_ptr_sub(__VA_ARGS__)
#define truncate(...) cutils_csll_SinglyLinkedList_void_ptr_truncate(__VA_ARGS__)
#define set(...) cutils_csll_SinglyLinkedList_void_ptr_set(__VA_ARGS__)
#define get(...) *(float *)cutils_csll_SinglyLinkedList_void_ptr_get(__VA_ARGS__)
#define find(l,t,i,...) cutils_csll_SinglyLinkedList_void_ptr_find(l,__csll_fcmp,t,i,##__VA_ARGS__)
#define findall(l,t,i,...) cutils_csll_SinglyLinkedList_void_ptr_findall(l,__csll_fcmp,t,i,##__VA_ARGS__)
#define iter(...) cutils_csll_SinglyLinkedList_void_ptr_iter(__VA_ARGS__)
#define next(...) cutils_csll_SinglyLinkedList_void_ptr_next(__VA_ARGS__)
#define print(linlist, ...) \
    cutils_csll_SinglyLinkedList_void_ptr_print(linlist, stdout, "SinglyLinkedList", \
        cutils_csll_SinglyLinkedList_void_ptr_format,##__VA_ARGS__)
