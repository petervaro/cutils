/* INFO ************************************************************************
**                                                                            **
**                                   cutils                                   **
**                                   ======                                   **
**                                                                            **
**                     Modern and Lightweight C Utilities                     **
**                       Version: 0.8.72.365 (20140711)                       **
**                                                                            **
**                       File: internal/dynamic_array.h                       **
**                                                                            **
**           Designed and written by Peter Varo. Copyright (c) 2014           **
**             License agreement is provided in the LICENSE file              **
**                 For more info visit: http://www.cutils.org                 **
**                                                                            **
************************************************************************ INFO */

/* !!! DON NOT ADD GUARD TO THIS FILE !!! */

#define FILE_STARTS_HERE
#include <stdio.h>    /* size_t */
#include <stdbool.h>  /* bool */

/*----------------------------------------------------------------------------*/
typedef struct {} cutils_cdar_DynamicArray_void_ptr;
/*----------------------------------------------------------------------------*/
bool
cutils_cdar_DynamicArray_void_ptr_new(cutils_cdar_DynamicArray_void_ptr **dynarr,
                                      size_t count,
                                      size_t item_size,
                                      void *source);
/*----------------------------------------------------------------------------*/
void
cutils_cdar_DynamicArray_void_ptr_del(cutils_cdar_DynamicArray_void_ptr *dynarr);
/*----------------------------------------------------------------------------*/
void *
cutils_cdar_DynamicArray_void_ptr_data(cutils_cdar_DynamicArray_void_ptr *dynarr,
                                       size_t *size,
                                       size_t *count);
/*----------------------------------------------------------------------------*/
void *
cutils_cdar_DynamicArray_void_ptr_raw(cutils_cdar_DynamicArray_void_ptr *dynarr);
/*----------------------------------------------------------------------------*/
size_t
cutils_cdar_DynamicArray_void_ptr_len(cutils_cdar_DynamicArray_void_ptr *dynarr);
/*----------------------------------------------------------------------------*/
size_t
cutils_cdar_DynamicArray_void_ptr_size(cutils_cdar_DynamicArray_void_ptr *dynarr);
/*----------------------------------------------------------------------------*/
void
cutils_cdar_DynamicArray_void_ptr_clear(cutils_cdar_DynamicArray_void_ptr *dynarr);
/*----------------------------------------------------------------------------*/
bool
cutils_cdar_DynamicArray_void_ptr_resize(cutils_cdar_DynamicArray_void_ptr *dynarr,
                                         size_t count);
/*----------------------------------------------------------------------------*/
bool
cutils_cdar_DynamicArray_void_ptr_swap(cutils_cdar_DynamicArray_void_ptr *dynarr,
                                       size_t index1,
                                       size_t index2,
                                       size_t count);
/*----------------------------------------------------------------------------*/
bool
cutils_cdar_DynamicArray_void_ptr_reverse(cutils_cdar_DynamicArray_void_ptr *dynarr);
/*----------------------------------------------------------------------------*/
bool
cutils_cdar_DynamicArray_void_ptr_append(cutils_cdar_DynamicArray_void_ptr *dynarr,
                                         size_t count,
                                         void *source);
/*----------------------------------------------------------------------------*/
bool
cutils_cdar_DynamicArray_void_ptr_push(cutils_cdar_DynamicArray_void_ptr *dynarr,
                                      size_t index,
                                      size_t count,
                                      void *source);
/*----------------------------------------------------------------------------*/
size_t
cutils_cdar_DynamicArray_void_ptr_pull(cutils_cdar_DynamicArray_void_ptr *dynarr,
                                       size_t index,
                                       size_t count);
/*----------------------------------------------------------------------------*/
size_t
cutils_cdar_DynamicArray_void_ptr_pop(cutils_cdar_DynamicArray_void_ptr *dynarr,
                                      size_t index,
                                      size_t count,
                                      void *destination);
/*----------------------------------------------------------------------------*/
size_t
cutils_cdar_DynamicArray_void_ptr_sub(cutils_cdar_DynamicArray_void_ptr *dynarr,
                                      size_t index,
                                      size_t count,
                                      void *destination);
/*----------------------------------------------------------------------------*/
void
cutils_cdar_DynamicArray_void_ptr_truncate(cutils_cdar_DynamicArray_void_ptr *dynarr,
                                           size_t index);
/*----------------------------------------------------------------------------*/
bool
cutils_cdar_DynamicArray_void_ptr_set(cutils_cdar_DynamicArray_void_ptr *dynarr,
                                      size_t index,
                                      size_t count,
                                      void *source);
/*----------------------------------------------------------------------------*/
void *
cutils_cdar_DynamicArray_void_ptr_get(cutils_cdar_DynamicArray_void_ptr *dynarr,
                                      size_t index);
/*----------------------------------------------------------------------------*/
bool
cutils_cdar_DynamicArray_void_ptr_find(cutils_cdar_DynamicArray_void_ptr *dynarr,
                                       const void *item,
                                       size_t *index);
/*----------------------------------------------------------------------------*/
size_t
cutils_cdar_DynamicArray_void_ptr_findall(cutils_cdar_DynamicArray_void_ptr *dynarr,
                                          const void *item,
                                          size_t *indices);
/*----------------------------------------------------------------------------*/
void
cutils_cdar_DynamicArray_void_ptr_sort(cutils_cdar_DynamicArray_void_ptr *dynarr,
                                       int (*compare)(const void*, const void*));
/*----------------------------------------------------------------------------*/
void
cutils_cdar_DynamicArray_void_ptr_sortsub(cutils_cdar_DynamicArray_void_ptr *dynarr,
                                          size_t index,
                                          size_t count,
                                          int (*compare)(const void *, const void*));
