/* INFO ************************************************************************
**                                                                            **
**                                   cutils                                   **
**                                   ======                                   **
**                                                                            **
**                     Modern and Lightweight C Utilities                     **
**                       Version: 0.8.90.471 (20140819)                       **
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
#include <stdlib.h>   /* size_t */
#include <stdbool.h>  /* bool */

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
extern void
cutils_csll_SinglyLinkedList_void_ptr_map(cutils_csll_SinglyLinkedList_void_ptr *linlist,
                                          size_t index,
                                          size_t count,
                                          void (*function)());
/*----------------------------------------------------------------------------*/
extern bool
cutils_csll_SinglyLinkedList_void_ptr_format(const void *data,
                                             char **buffer,
                                             size_t *buffer_size);
/*----------------------------------------------------------------------------*/
extern void
cutils_csll_SinglyLinkedList_void_ptr_print(cutils_csll_SinglyLinkedList_void_ptr *linlist,
                                            FILE *stream,
                                            const char *sub_type,
                                            bool(*format)());
/*----------------------------------------------------------------------------*/
extern bool
cutils_csll_SinglyLinkedList_void_ptr_compare(const void *item1,
                                              const void *item2,
                                              size_t item_size);
