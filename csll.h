/* INFO ************************************************************************
**                                                                            **
**                                   cutils                                   **
**                                   ======                                   **
**                                                                            **
**                     Modern and Lightweight C Utilities                     **
**                       Version: 0.8.90.629 (20140820)                       **
**                                                                            **
**                                File: csll.h                                **
**                                                                            **
**           Designed and written by Peter Varo. Copyright (c) 2014           **
**             License agreement is provided in the LICENSE file              **
**                 For more info visit: http://www.cutils.org                 **
**                                                                            **
************************************************************************ INFO */

#ifndef _C_SINGLY_LINKED_LIST_H_35118355245711974_
#define _C_SINGLY_LINKED_LIST_H_35118355245711974_

#include <stddef.h>         /* ptrdiff_t */
#include <string.h>         /* strlen(), strncpy() */
#include "internal/fmtc.h"  /* cutils_fmtc_repr */
#include "internal/fcmp.h"  /* cutils_fcmp_compare */
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

/*----------------------------------------------------------------------------*/
typedef struct {} cutils_csll_SinglyLinkedList_char;
typedef struct {} cutils_csll_SinglyLinkedList_char_iterator;
extern bool cutils_csll_SinglyLinkedList_char_new(cutils_csll_SinglyLinkedList_char**,size_t,char*);
extern cutils_csll_SinglyLinkedList_char_iterator* cutils_csll_SinglyLinkedList_char_iter(cutils_csll_SinglyLinkedList_char*);
extern bool cutils_csll_SinglyLinkedList_char_next(cutils_csll_SinglyLinkedList_char_iterator*,char**);
extern bool cutils_csll_SinglyLinkedList_char_append(cutils_csll_SinglyLinkedList_char*,size_t,char*);
extern bool cutils_csll_SinglyLinkedList_char_push(cutils_csll_SinglyLinkedList_char*,size_t,size_t,char*);
extern bool cutils_csll_SinglyLinkedList_char_set(cutils_csll_SinglyLinkedList_char*,size_t,size_t,char*);
extern size_t cutils_csll_SinglyLinkedList_char_pop(cutils_csll_SinglyLinkedList_char*,size_t,size_t,char*);
extern size_t cutils_csll_SinglyLinkedList_char_sub(cutils_csll_SinglyLinkedList_char*,size_t,size_t,char*);
extern char cutils_csll_SinglyLinkedList_char_get(cutils_csll_SinglyLinkedList_char*,size_t);
extern bool cutils_csll_SinglyLinkedList_char_find(cutils_csll_SinglyLinkedList_char*,bool(*)(const void*,const void*,size_t),const void*,size_t*);
extern size_t cutils_csll_SinglyLinkedList_char_findall(cutils_csll_SinglyLinkedList_char*,bool(*)(const void*,const void*,size_t),const void*,size_t*);
extern bool cutils_csll_SinglyLinkedList_char_format(const char*,char**,size_t*);
extern bool cutils_csll_SinglyLinkedList_char_compare(const void*,const void*,size_t);
extern void(*cutils_csll_SinglyLinkedList_char_del)(cutils_csll_SinglyLinkedList_char*);
extern size_t(*cutils_csll_SinglyLinkedList_char_len)(cutils_csll_SinglyLinkedList_char*);
extern bool(*cutils_csll_SinglyLinkedList_char_swap)(cutils_csll_SinglyLinkedList_char*,size_t,size_t,size_t);
extern bool(*cutils_csll_SinglyLinkedList_char_reverse)(cutils_csll_SinglyLinkedList_char*);
extern size_t(*cutils_csll_SinglyLinkedList_char_pull)(cutils_csll_SinglyLinkedList_char*,size_t,size_t);
extern void(*cutils_csll_SinglyLinkedList_char_truncate)(cutils_csll_SinglyLinkedList_char*,size_t);
extern void(*cutils_csll_SinglyLinkedList_char_clear)(cutils_csll_SinglyLinkedList_char*);
extern void(*cutils_csll_SinglyLinkedList_char_map)(cutils_csll_SinglyLinkedList_char*,size_t,size_t,void(*)(size_t,char*));
extern void(*cutils_csll_SinglyLinkedList_char_print)(cutils_csll_SinglyLinkedList_char*,FILE*,const char*,bool(*)());
/*----------------------------------------------------------------------------*/
typedef struct {} cutils_csll_SinglyLinkedList_signed_char;
typedef struct {} cutils_csll_SinglyLinkedList_signed_char_iterator;
extern bool cutils_csll_SinglyLinkedList_signed_char_new(cutils_csll_SinglyLinkedList_signed_char**,size_t,signed char*);
extern cutils_csll_SinglyLinkedList_signed_char_iterator* cutils_csll_SinglyLinkedList_signed_char_iter(cutils_csll_SinglyLinkedList_signed_char*);
extern bool cutils_csll_SinglyLinkedList_signed_char_next(cutils_csll_SinglyLinkedList_signed_char_iterator*,signed char**);
extern bool cutils_csll_SinglyLinkedList_signed_char_append(cutils_csll_SinglyLinkedList_signed_char*,size_t,signed char*);
extern bool cutils_csll_SinglyLinkedList_signed_char_push(cutils_csll_SinglyLinkedList_signed_char*,size_t,size_t,signed char*);
extern bool cutils_csll_SinglyLinkedList_signed_char_set(cutils_csll_SinglyLinkedList_signed_char*,size_t,size_t,signed char*);
extern size_t cutils_csll_SinglyLinkedList_signed_char_pop(cutils_csll_SinglyLinkedList_signed_char*,size_t,size_t,signed char*);
extern size_t cutils_csll_SinglyLinkedList_signed_char_sub(cutils_csll_SinglyLinkedList_signed_char*,size_t,size_t,signed char*);
extern signed char cutils_csll_SinglyLinkedList_signed_char_get(cutils_csll_SinglyLinkedList_signed_char*,size_t);
extern bool cutils_csll_SinglyLinkedList_signed_char_find(cutils_csll_SinglyLinkedList_signed_char*,bool(*)(const void*,const void*,size_t),const void*,size_t*);
extern size_t cutils_csll_SinglyLinkedList_signed_char_findall(cutils_csll_SinglyLinkedList_signed_char*,bool(*)(const void*,const void*,size_t),const void*,size_t*);
extern bool cutils_csll_SinglyLinkedList_signed_char_format(const signed char*,char**,size_t*);
extern bool cutils_csll_SinglyLinkedList_signed_char_compare(const void*,const void*,size_t);
extern void(*cutils_csll_SinglyLinkedList_signed_char_del)(cutils_csll_SinglyLinkedList_signed_char*);
extern size_t(*cutils_csll_SinglyLinkedList_signed_char_len)(cutils_csll_SinglyLinkedList_signed_char*);
extern bool(*cutils_csll_SinglyLinkedList_signed_char_swap)(cutils_csll_SinglyLinkedList_signed_char*,size_t,size_t,size_t);
extern bool(*cutils_csll_SinglyLinkedList_signed_char_reverse)(cutils_csll_SinglyLinkedList_signed_char*);
extern size_t(*cutils_csll_SinglyLinkedList_signed_char_pull)(cutils_csll_SinglyLinkedList_signed_char*,size_t,size_t);
extern void(*cutils_csll_SinglyLinkedList_signed_char_truncate)(cutils_csll_SinglyLinkedList_signed_char*,size_t);
extern void(*cutils_csll_SinglyLinkedList_signed_char_clear)(cutils_csll_SinglyLinkedList_signed_char*);
extern void(*cutils_csll_SinglyLinkedList_signed_char_map)(cutils_csll_SinglyLinkedList_signed_char*,size_t,size_t,void(*)(size_t,signed char*));
extern void(*cutils_csll_SinglyLinkedList_signed_char_print)(cutils_csll_SinglyLinkedList_signed_char*,FILE*,const char*,bool(*)());
/*----------------------------------------------------------------------------*/
typedef struct {} cutils_csll_SinglyLinkedList_unsigned_char;
typedef struct {} cutils_csll_SinglyLinkedList_unsigned_char_iterator;
extern bool cutils_csll_SinglyLinkedList_unsigned_char_new(cutils_csll_SinglyLinkedList_unsigned_char**,size_t,unsigned char*);
extern cutils_csll_SinglyLinkedList_unsigned_char_iterator* cutils_csll_SinglyLinkedList_unsigned_char_iter(cutils_csll_SinglyLinkedList_unsigned_char*);
extern bool cutils_csll_SinglyLinkedList_unsigned_char_next(cutils_csll_SinglyLinkedList_unsigned_char_iterator*,unsigned char**);
extern bool cutils_csll_SinglyLinkedList_unsigned_char_append(cutils_csll_SinglyLinkedList_unsigned_char*,size_t,unsigned char*);
extern bool cutils_csll_SinglyLinkedList_unsigned_char_push(cutils_csll_SinglyLinkedList_unsigned_char*,size_t,size_t,unsigned char*);
extern bool cutils_csll_SinglyLinkedList_unsigned_char_set(cutils_csll_SinglyLinkedList_unsigned_char*,size_t,size_t,unsigned char*);
extern size_t cutils_csll_SinglyLinkedList_unsigned_char_pop(cutils_csll_SinglyLinkedList_unsigned_char*,size_t,size_t,unsigned char*);
extern size_t cutils_csll_SinglyLinkedList_unsigned_char_sub(cutils_csll_SinglyLinkedList_unsigned_char*,size_t,size_t,unsigned char*);
extern unsigned char cutils_csll_SinglyLinkedList_unsigned_char_get(cutils_csll_SinglyLinkedList_unsigned_char*,size_t);
extern bool cutils_csll_SinglyLinkedList_unsigned_char_find(cutils_csll_SinglyLinkedList_unsigned_char*,bool(*)(const void*,const void*,size_t),const void*,size_t*);
extern size_t cutils_csll_SinglyLinkedList_unsigned_char_findall(cutils_csll_SinglyLinkedList_unsigned_char*,bool(*)(const void*,const void*,size_t),const void*,size_t*);
extern bool cutils_csll_SinglyLinkedList_unsigned_char_format(const unsigned char*,char**,size_t*);
extern bool cutils_csll_SinglyLinkedList_unsigned_char_compare(const void*,const void*,size_t);
extern void(*cutils_csll_SinglyLinkedList_unsigned_char_del)(cutils_csll_SinglyLinkedList_unsigned_char*);
extern size_t(*cutils_csll_SinglyLinkedList_unsigned_char_len)(cutils_csll_SinglyLinkedList_unsigned_char*);
extern bool(*cutils_csll_SinglyLinkedList_unsigned_char_swap)(cutils_csll_SinglyLinkedList_unsigned_char*,size_t,size_t,size_t);
extern bool(*cutils_csll_SinglyLinkedList_unsigned_char_reverse)(cutils_csll_SinglyLinkedList_unsigned_char*);
extern size_t(*cutils_csll_SinglyLinkedList_unsigned_char_pull)(cutils_csll_SinglyLinkedList_unsigned_char*,size_t,size_t);
extern void(*cutils_csll_SinglyLinkedList_unsigned_char_truncate)(cutils_csll_SinglyLinkedList_unsigned_char*,size_t);
extern void(*cutils_csll_SinglyLinkedList_unsigned_char_clear)(cutils_csll_SinglyLinkedList_unsigned_char*);
extern void(*cutils_csll_SinglyLinkedList_unsigned_char_map)(cutils_csll_SinglyLinkedList_unsigned_char*,size_t,size_t,void(*)(size_t,unsigned char*));
extern void(*cutils_csll_SinglyLinkedList_unsigned_char_print)(cutils_csll_SinglyLinkedList_unsigned_char*,FILE*,const char*,bool(*)());
/*----------------------------------------------------------------------------*/
typedef struct {} cutils_csll_SinglyLinkedList_char_ptr;
typedef struct {} cutils_csll_SinglyLinkedList_char_ptr_iterator;
extern bool cutils_csll_SinglyLinkedList_char_ptr_new(cutils_csll_SinglyLinkedList_char_ptr**,size_t,char**);
extern cutils_csll_SinglyLinkedList_char_ptr_iterator* cutils_csll_SinglyLinkedList_char_ptr_iter(cutils_csll_SinglyLinkedList_char_ptr*);
extern bool cutils_csll_SinglyLinkedList_char_ptr_next(cutils_csll_SinglyLinkedList_char_ptr_iterator*,char***);
extern bool cutils_csll_SinglyLinkedList_char_ptr_append(cutils_csll_SinglyLinkedList_char_ptr*,size_t,char**);
extern bool cutils_csll_SinglyLinkedList_char_ptr_push(cutils_csll_SinglyLinkedList_char_ptr*,size_t,size_t,char**);
extern bool cutils_csll_SinglyLinkedList_char_ptr_set(cutils_csll_SinglyLinkedList_char_ptr*,size_t,size_t,char**);
extern size_t cutils_csll_SinglyLinkedList_char_ptr_pop(cutils_csll_SinglyLinkedList_char_ptr*,size_t,size_t,char**);
extern size_t cutils_csll_SinglyLinkedList_char_ptr_sub(cutils_csll_SinglyLinkedList_char_ptr*,size_t,size_t,char**);
extern char* cutils_csll_SinglyLinkedList_char_ptr_get(cutils_csll_SinglyLinkedList_char_ptr*,size_t);
extern bool cutils_csll_SinglyLinkedList_char_ptr_find(cutils_csll_SinglyLinkedList_char_ptr*,bool(*)(const void*,const void*,size_t),const void*,size_t*);
extern size_t cutils_csll_SinglyLinkedList_char_ptr_findall(cutils_csll_SinglyLinkedList_char_ptr*,bool(*)(const void*,const void*,size_t),const void*,size_t*);
extern bool cutils_csll_SinglyLinkedList_char_ptr_format(const char**,char**,size_t*);
extern bool cutils_csll_SinglyLinkedList_char_ptr_compare(const void*,const void*,size_t);
extern void(*cutils_csll_SinglyLinkedList_char_ptr_del)(cutils_csll_SinglyLinkedList_char_ptr*);
extern size_t(*cutils_csll_SinglyLinkedList_char_ptr_len)(cutils_csll_SinglyLinkedList_char_ptr*);
extern bool(*cutils_csll_SinglyLinkedList_char_ptr_swap)(cutils_csll_SinglyLinkedList_char_ptr*,size_t,size_t,size_t);
extern bool(*cutils_csll_SinglyLinkedList_char_ptr_reverse)(cutils_csll_SinglyLinkedList_char_ptr*);
extern size_t(*cutils_csll_SinglyLinkedList_char_ptr_pull)(cutils_csll_SinglyLinkedList_char_ptr*,size_t,size_t);
extern void(*cutils_csll_SinglyLinkedList_char_ptr_truncate)(cutils_csll_SinglyLinkedList_char_ptr*,size_t);
extern void(*cutils_csll_SinglyLinkedList_char_ptr_clear)(cutils_csll_SinglyLinkedList_char_ptr*);
extern void(*cutils_csll_SinglyLinkedList_char_ptr_map)(cutils_csll_SinglyLinkedList_char_ptr*,size_t,size_t,void(*)(size_t,char**));
extern void(*cutils_csll_SinglyLinkedList_char_ptr_print)(cutils_csll_SinglyLinkedList_char_ptr*,FILE*,const char*,bool(*)());
/*----------------------------------------------------------------------------*/
typedef struct {} cutils_csll_SinglyLinkedList_short;
typedef struct {} cutils_csll_SinglyLinkedList_short_iterator;
extern bool cutils_csll_SinglyLinkedList_short_new(cutils_csll_SinglyLinkedList_short**,size_t,short*);
extern cutils_csll_SinglyLinkedList_short_iterator* cutils_csll_SinglyLinkedList_short_iter(cutils_csll_SinglyLinkedList_short*);
extern bool cutils_csll_SinglyLinkedList_short_next(cutils_csll_SinglyLinkedList_short_iterator*,short**);
extern bool cutils_csll_SinglyLinkedList_short_append(cutils_csll_SinglyLinkedList_short*,size_t,short*);
extern bool cutils_csll_SinglyLinkedList_short_push(cutils_csll_SinglyLinkedList_short*,size_t,size_t,short*);
extern bool cutils_csll_SinglyLinkedList_short_set(cutils_csll_SinglyLinkedList_short*,size_t,size_t,short*);
extern size_t cutils_csll_SinglyLinkedList_short_pop(cutils_csll_SinglyLinkedList_short*,size_t,size_t,short*);
extern size_t cutils_csll_SinglyLinkedList_short_sub(cutils_csll_SinglyLinkedList_short*,size_t,size_t,short*);
extern short cutils_csll_SinglyLinkedList_short_get(cutils_csll_SinglyLinkedList_short*,size_t);
extern bool cutils_csll_SinglyLinkedList_short_find(cutils_csll_SinglyLinkedList_short*,bool(*)(const void*,const void*,size_t),const void*,size_t*);
extern size_t cutils_csll_SinglyLinkedList_short_findall(cutils_csll_SinglyLinkedList_short*,bool(*)(const void*,const void*,size_t),const void*,size_t*);
extern bool cutils_csll_SinglyLinkedList_short_format(const short*,char**,size_t*);
extern bool cutils_csll_SinglyLinkedList_short_compare(const void*,const void*,size_t);
extern void(*cutils_csll_SinglyLinkedList_short_del)(cutils_csll_SinglyLinkedList_short*);
extern size_t(*cutils_csll_SinglyLinkedList_short_len)(cutils_csll_SinglyLinkedList_short*);
extern bool(*cutils_csll_SinglyLinkedList_short_swap)(cutils_csll_SinglyLinkedList_short*,size_t,size_t,size_t);
extern bool(*cutils_csll_SinglyLinkedList_short_reverse)(cutils_csll_SinglyLinkedList_short*);
extern size_t(*cutils_csll_SinglyLinkedList_short_pull)(cutils_csll_SinglyLinkedList_short*,size_t,size_t);
extern void(*cutils_csll_SinglyLinkedList_short_truncate)(cutils_csll_SinglyLinkedList_short*,size_t);
extern void(*cutils_csll_SinglyLinkedList_short_clear)(cutils_csll_SinglyLinkedList_short*);
extern void(*cutils_csll_SinglyLinkedList_short_map)(cutils_csll_SinglyLinkedList_short*,size_t,size_t,void(*)(size_t,short*));
extern void(*cutils_csll_SinglyLinkedList_short_print)(cutils_csll_SinglyLinkedList_short*,FILE*,const char*,bool(*)());
/*----------------------------------------------------------------------------*/
typedef struct {} cutils_csll_SinglyLinkedList_unsigned_short;
typedef struct {} cutils_csll_SinglyLinkedList_unsigned_short_iterator;
extern bool cutils_csll_SinglyLinkedList_unsigned_short_new(cutils_csll_SinglyLinkedList_unsigned_short**,size_t,unsigned short*);
extern cutils_csll_SinglyLinkedList_unsigned_short_iterator* cutils_csll_SinglyLinkedList_unsigned_short_iter(cutils_csll_SinglyLinkedList_unsigned_short*);
extern bool cutils_csll_SinglyLinkedList_unsigned_short_next(cutils_csll_SinglyLinkedList_unsigned_short_iterator*,unsigned short**);
extern bool cutils_csll_SinglyLinkedList_unsigned_short_append(cutils_csll_SinglyLinkedList_unsigned_short*,size_t,unsigned short*);
extern bool cutils_csll_SinglyLinkedList_unsigned_short_push(cutils_csll_SinglyLinkedList_unsigned_short*,size_t,size_t,unsigned short*);
extern bool cutils_csll_SinglyLinkedList_unsigned_short_set(cutils_csll_SinglyLinkedList_unsigned_short*,size_t,size_t,unsigned short*);
extern size_t cutils_csll_SinglyLinkedList_unsigned_short_pop(cutils_csll_SinglyLinkedList_unsigned_short*,size_t,size_t,unsigned short*);
extern size_t cutils_csll_SinglyLinkedList_unsigned_short_sub(cutils_csll_SinglyLinkedList_unsigned_short*,size_t,size_t,unsigned short*);
extern unsigned short cutils_csll_SinglyLinkedList_unsigned_short_get(cutils_csll_SinglyLinkedList_unsigned_short*,size_t);
extern bool cutils_csll_SinglyLinkedList_unsigned_short_find(cutils_csll_SinglyLinkedList_unsigned_short*,bool(*)(const void*,const void*,size_t),const void*,size_t*);
extern size_t cutils_csll_SinglyLinkedList_unsigned_short_findall(cutils_csll_SinglyLinkedList_unsigned_short*,bool(*)(const void*,const void*,size_t),const void*,size_t*);
extern bool cutils_csll_SinglyLinkedList_unsigned_short_format(const unsigned short*,char**,size_t*);
extern bool cutils_csll_SinglyLinkedList_unsigned_short_compare(const void*,const void*,size_t);
extern void(*cutils_csll_SinglyLinkedList_unsigned_short_del)(cutils_csll_SinglyLinkedList_unsigned_short*);
extern size_t(*cutils_csll_SinglyLinkedList_unsigned_short_len)(cutils_csll_SinglyLinkedList_unsigned_short*);
extern bool(*cutils_csll_SinglyLinkedList_unsigned_short_swap)(cutils_csll_SinglyLinkedList_unsigned_short*,size_t,size_t,size_t);
extern bool(*cutils_csll_SinglyLinkedList_unsigned_short_reverse)(cutils_csll_SinglyLinkedList_unsigned_short*);
extern size_t(*cutils_csll_SinglyLinkedList_unsigned_short_pull)(cutils_csll_SinglyLinkedList_unsigned_short*,size_t,size_t);
extern void(*cutils_csll_SinglyLinkedList_unsigned_short_truncate)(cutils_csll_SinglyLinkedList_unsigned_short*,size_t);
extern void(*cutils_csll_SinglyLinkedList_unsigned_short_clear)(cutils_csll_SinglyLinkedList_unsigned_short*);
extern void(*cutils_csll_SinglyLinkedList_unsigned_short_map)(cutils_csll_SinglyLinkedList_unsigned_short*,size_t,size_t,void(*)(size_t,unsigned short*));
extern void(*cutils_csll_SinglyLinkedList_unsigned_short_print)(cutils_csll_SinglyLinkedList_unsigned_short*,FILE*,const char*,bool(*)());
/*----------------------------------------------------------------------------*/
typedef struct {} cutils_csll_SinglyLinkedList_int;
typedef struct {} cutils_csll_SinglyLinkedList_int_iterator;
extern bool cutils_csll_SinglyLinkedList_int_new(cutils_csll_SinglyLinkedList_int**,size_t,int*);
extern cutils_csll_SinglyLinkedList_int_iterator* cutils_csll_SinglyLinkedList_int_iter(cutils_csll_SinglyLinkedList_int*);
extern bool cutils_csll_SinglyLinkedList_int_next(cutils_csll_SinglyLinkedList_int_iterator*,int**);
extern bool cutils_csll_SinglyLinkedList_int_append(cutils_csll_SinglyLinkedList_int*,size_t,int*);
extern bool cutils_csll_SinglyLinkedList_int_push(cutils_csll_SinglyLinkedList_int*,size_t,size_t,int*);
extern bool cutils_csll_SinglyLinkedList_int_set(cutils_csll_SinglyLinkedList_int*,size_t,size_t,int*);
extern size_t cutils_csll_SinglyLinkedList_int_pop(cutils_csll_SinglyLinkedList_int*,size_t,size_t,int*);
extern size_t cutils_csll_SinglyLinkedList_int_sub(cutils_csll_SinglyLinkedList_int*,size_t,size_t,int*);
extern int cutils_csll_SinglyLinkedList_int_get(cutils_csll_SinglyLinkedList_int*,size_t);
extern bool cutils_csll_SinglyLinkedList_int_find(cutils_csll_SinglyLinkedList_int*,bool(*)(const void*,const void*,size_t),const void*,size_t*);
extern size_t cutils_csll_SinglyLinkedList_int_findall(cutils_csll_SinglyLinkedList_int*,bool(*)(const void*,const void*,size_t),const void*,size_t*);
extern bool cutils_csll_SinglyLinkedList_int_format(const int*,char**,size_t*);
extern bool cutils_csll_SinglyLinkedList_int_compare(const void*,const void*,size_t);
extern void(*cutils_csll_SinglyLinkedList_int_del)(cutils_csll_SinglyLinkedList_int*);
extern size_t(*cutils_csll_SinglyLinkedList_int_len)(cutils_csll_SinglyLinkedList_int*);
extern bool(*cutils_csll_SinglyLinkedList_int_swap)(cutils_csll_SinglyLinkedList_int*,size_t,size_t,size_t);
extern bool(*cutils_csll_SinglyLinkedList_int_reverse)(cutils_csll_SinglyLinkedList_int*);
extern size_t(*cutils_csll_SinglyLinkedList_int_pull)(cutils_csll_SinglyLinkedList_int*,size_t,size_t);
extern void(*cutils_csll_SinglyLinkedList_int_truncate)(cutils_csll_SinglyLinkedList_int*,size_t);
extern void(*cutils_csll_SinglyLinkedList_int_clear)(cutils_csll_SinglyLinkedList_int*);
extern void(*cutils_csll_SinglyLinkedList_int_map)(cutils_csll_SinglyLinkedList_int*,size_t,size_t,void(*)(size_t,int*));
extern void(*cutils_csll_SinglyLinkedList_int_print)(cutils_csll_SinglyLinkedList_int*,FILE*,const char*,bool(*)());
/*----------------------------------------------------------------------------*/
typedef struct {} cutils_csll_SinglyLinkedList_unsigned_int;
typedef struct {} cutils_csll_SinglyLinkedList_unsigned_int_iterator;
extern bool cutils_csll_SinglyLinkedList_unsigned_int_new(cutils_csll_SinglyLinkedList_unsigned_int**,size_t,unsigned int*);
extern cutils_csll_SinglyLinkedList_unsigned_int_iterator* cutils_csll_SinglyLinkedList_unsigned_int_iter(cutils_csll_SinglyLinkedList_unsigned_int*);
extern bool cutils_csll_SinglyLinkedList_unsigned_int_next(cutils_csll_SinglyLinkedList_unsigned_int_iterator*,unsigned int**);
extern bool cutils_csll_SinglyLinkedList_unsigned_int_append(cutils_csll_SinglyLinkedList_unsigned_int*,size_t,unsigned int*);
extern bool cutils_csll_SinglyLinkedList_unsigned_int_push(cutils_csll_SinglyLinkedList_unsigned_int*,size_t,size_t,unsigned int*);
extern bool cutils_csll_SinglyLinkedList_unsigned_int_set(cutils_csll_SinglyLinkedList_unsigned_int*,size_t,size_t,unsigned int*);
extern size_t cutils_csll_SinglyLinkedList_unsigned_int_pop(cutils_csll_SinglyLinkedList_unsigned_int*,size_t,size_t,unsigned int*);
extern size_t cutils_csll_SinglyLinkedList_unsigned_int_sub(cutils_csll_SinglyLinkedList_unsigned_int*,size_t,size_t,unsigned int*);
extern unsigned int cutils_csll_SinglyLinkedList_unsigned_int_get(cutils_csll_SinglyLinkedList_unsigned_int*,size_t);
extern bool cutils_csll_SinglyLinkedList_unsigned_int_find(cutils_csll_SinglyLinkedList_unsigned_int*,bool(*)(const void*,const void*,size_t),const void*,size_t*);
extern size_t cutils_csll_SinglyLinkedList_unsigned_int_findall(cutils_csll_SinglyLinkedList_unsigned_int*,bool(*)(const void*,const void*,size_t),const void*,size_t*);
extern bool cutils_csll_SinglyLinkedList_unsigned_int_format(const unsigned int*,char**,size_t*);
extern bool cutils_csll_SinglyLinkedList_unsigned_int_compare(const void*,const void*,size_t);
extern void(*cutils_csll_SinglyLinkedList_unsigned_int_del)(cutils_csll_SinglyLinkedList_unsigned_int*);
extern size_t(*cutils_csll_SinglyLinkedList_unsigned_int_len)(cutils_csll_SinglyLinkedList_unsigned_int*);
extern bool(*cutils_csll_SinglyLinkedList_unsigned_int_swap)(cutils_csll_SinglyLinkedList_unsigned_int*,size_t,size_t,size_t);
extern bool(*cutils_csll_SinglyLinkedList_unsigned_int_reverse)(cutils_csll_SinglyLinkedList_unsigned_int*);
extern size_t(*cutils_csll_SinglyLinkedList_unsigned_int_pull)(cutils_csll_SinglyLinkedList_unsigned_int*,size_t,size_t);
extern void(*cutils_csll_SinglyLinkedList_unsigned_int_truncate)(cutils_csll_SinglyLinkedList_unsigned_int*,size_t);
extern void(*cutils_csll_SinglyLinkedList_unsigned_int_clear)(cutils_csll_SinglyLinkedList_unsigned_int*);
extern void(*cutils_csll_SinglyLinkedList_unsigned_int_map)(cutils_csll_SinglyLinkedList_unsigned_int*,size_t,size_t,void(*)(size_t,unsigned int*));
extern void(*cutils_csll_SinglyLinkedList_unsigned_int_print)(cutils_csll_SinglyLinkedList_unsigned_int*,FILE*,const char*,bool(*)());
/*----------------------------------------------------------------------------*/
typedef struct {} cutils_csll_SinglyLinkedList_long;
typedef struct {} cutils_csll_SinglyLinkedList_long_iterator;
extern bool cutils_csll_SinglyLinkedList_long_new(cutils_csll_SinglyLinkedList_long**,size_t,long*);
extern cutils_csll_SinglyLinkedList_long_iterator* cutils_csll_SinglyLinkedList_long_iter(cutils_csll_SinglyLinkedList_long*);
extern bool cutils_csll_SinglyLinkedList_long_next(cutils_csll_SinglyLinkedList_long_iterator*,long**);
extern bool cutils_csll_SinglyLinkedList_long_append(cutils_csll_SinglyLinkedList_long*,size_t,long*);
extern bool cutils_csll_SinglyLinkedList_long_push(cutils_csll_SinglyLinkedList_long*,size_t,size_t,long*);
extern bool cutils_csll_SinglyLinkedList_long_set(cutils_csll_SinglyLinkedList_long*,size_t,size_t,long*);
extern size_t cutils_csll_SinglyLinkedList_long_pop(cutils_csll_SinglyLinkedList_long*,size_t,size_t,long*);
extern size_t cutils_csll_SinglyLinkedList_long_sub(cutils_csll_SinglyLinkedList_long*,size_t,size_t,long*);
extern long cutils_csll_SinglyLinkedList_long_get(cutils_csll_SinglyLinkedList_long*,size_t);
extern bool cutils_csll_SinglyLinkedList_long_find(cutils_csll_SinglyLinkedList_long*,bool(*)(const void*,const void*,size_t),const void*,size_t*);
extern size_t cutils_csll_SinglyLinkedList_long_findall(cutils_csll_SinglyLinkedList_long*,bool(*)(const void*,const void*,size_t),const void*,size_t*);
extern bool cutils_csll_SinglyLinkedList_long_format(const long*,char**,size_t*);
extern bool cutils_csll_SinglyLinkedList_long_compare(const void*,const void*,size_t);
extern void(*cutils_csll_SinglyLinkedList_long_del)(cutils_csll_SinglyLinkedList_long*);
extern size_t(*cutils_csll_SinglyLinkedList_long_len)(cutils_csll_SinglyLinkedList_long*);
extern bool(*cutils_csll_SinglyLinkedList_long_swap)(cutils_csll_SinglyLinkedList_long*,size_t,size_t,size_t);
extern bool(*cutils_csll_SinglyLinkedList_long_reverse)(cutils_csll_SinglyLinkedList_long*);
extern size_t(*cutils_csll_SinglyLinkedList_long_pull)(cutils_csll_SinglyLinkedList_long*,size_t,size_t);
extern void(*cutils_csll_SinglyLinkedList_long_truncate)(cutils_csll_SinglyLinkedList_long*,size_t);
extern void(*cutils_csll_SinglyLinkedList_long_clear)(cutils_csll_SinglyLinkedList_long*);
extern void(*cutils_csll_SinglyLinkedList_long_map)(cutils_csll_SinglyLinkedList_long*,size_t,size_t,void(*)(size_t,long*));
extern void(*cutils_csll_SinglyLinkedList_long_print)(cutils_csll_SinglyLinkedList_long*,FILE*,const char*,bool(*)());
/*----------------------------------------------------------------------------*/
typedef struct {} cutils_csll_SinglyLinkedList_unsigned_long;
typedef struct {} cutils_csll_SinglyLinkedList_unsigned_long_iterator;
extern bool cutils_csll_SinglyLinkedList_unsigned_long_new(cutils_csll_SinglyLinkedList_unsigned_long**,size_t,unsigned long*);
extern cutils_csll_SinglyLinkedList_unsigned_long_iterator* cutils_csll_SinglyLinkedList_unsigned_long_iter(cutils_csll_SinglyLinkedList_unsigned_long*);
extern bool cutils_csll_SinglyLinkedList_unsigned_long_next(cutils_csll_SinglyLinkedList_unsigned_long_iterator*,unsigned long**);
extern bool cutils_csll_SinglyLinkedList_unsigned_long_append(cutils_csll_SinglyLinkedList_unsigned_long*,size_t,unsigned long*);
extern bool cutils_csll_SinglyLinkedList_unsigned_long_push(cutils_csll_SinglyLinkedList_unsigned_long*,size_t,size_t,unsigned long*);
extern bool cutils_csll_SinglyLinkedList_unsigned_long_set(cutils_csll_SinglyLinkedList_unsigned_long*,size_t,size_t,unsigned long*);
extern size_t cutils_csll_SinglyLinkedList_unsigned_long_pop(cutils_csll_SinglyLinkedList_unsigned_long*,size_t,size_t,unsigned long*);
extern size_t cutils_csll_SinglyLinkedList_unsigned_long_sub(cutils_csll_SinglyLinkedList_unsigned_long*,size_t,size_t,unsigned long*);
extern unsigned long cutils_csll_SinglyLinkedList_unsigned_long_get(cutils_csll_SinglyLinkedList_unsigned_long*,size_t);
extern bool cutils_csll_SinglyLinkedList_unsigned_long_find(cutils_csll_SinglyLinkedList_unsigned_long*,bool(*)(const void*,const void*,size_t),const void*,size_t*);
extern size_t cutils_csll_SinglyLinkedList_unsigned_long_findall(cutils_csll_SinglyLinkedList_unsigned_long*,bool(*)(const void*,const void*,size_t),const void*,size_t*);
extern bool cutils_csll_SinglyLinkedList_unsigned_long_format(const unsigned long*,char**,size_t*);
extern bool cutils_csll_SinglyLinkedList_unsigned_long_compare(const void*,const void*,size_t);
extern void(*cutils_csll_SinglyLinkedList_unsigned_long_del)(cutils_csll_SinglyLinkedList_unsigned_long*);
extern size_t(*cutils_csll_SinglyLinkedList_unsigned_long_len)(cutils_csll_SinglyLinkedList_unsigned_long*);
extern bool(*cutils_csll_SinglyLinkedList_unsigned_long_swap)(cutils_csll_SinglyLinkedList_unsigned_long*,size_t,size_t,size_t);
extern bool(*cutils_csll_SinglyLinkedList_unsigned_long_reverse)(cutils_csll_SinglyLinkedList_unsigned_long*);
extern size_t(*cutils_csll_SinglyLinkedList_unsigned_long_pull)(cutils_csll_SinglyLinkedList_unsigned_long*,size_t,size_t);
extern void(*cutils_csll_SinglyLinkedList_unsigned_long_truncate)(cutils_csll_SinglyLinkedList_unsigned_long*,size_t);
extern void(*cutils_csll_SinglyLinkedList_unsigned_long_clear)(cutils_csll_SinglyLinkedList_unsigned_long*);
extern void(*cutils_csll_SinglyLinkedList_unsigned_long_map)(cutils_csll_SinglyLinkedList_unsigned_long*,size_t,size_t,void(*)(size_t,unsigned long*));
extern void(*cutils_csll_SinglyLinkedList_unsigned_long_print)(cutils_csll_SinglyLinkedList_unsigned_long*,FILE*,const char*,bool(*)());
/*----------------------------------------------------------------------------*/
typedef struct {} cutils_csll_SinglyLinkedList_long_long;
typedef struct {} cutils_csll_SinglyLinkedList_long_long_iterator;
extern bool cutils_csll_SinglyLinkedList_long_long_new(cutils_csll_SinglyLinkedList_long_long**,size_t,long long*);
extern cutils_csll_SinglyLinkedList_long_long_iterator* cutils_csll_SinglyLinkedList_long_long_iter(cutils_csll_SinglyLinkedList_long_long*);
extern bool cutils_csll_SinglyLinkedList_long_long_next(cutils_csll_SinglyLinkedList_long_long_iterator*,long long**);
extern bool cutils_csll_SinglyLinkedList_long_long_append(cutils_csll_SinglyLinkedList_long_long*,size_t,long long*);
extern bool cutils_csll_SinglyLinkedList_long_long_push(cutils_csll_SinglyLinkedList_long_long*,size_t,size_t,long long*);
extern bool cutils_csll_SinglyLinkedList_long_long_set(cutils_csll_SinglyLinkedList_long_long*,size_t,size_t,long long*);
extern size_t cutils_csll_SinglyLinkedList_long_long_pop(cutils_csll_SinglyLinkedList_long_long*,size_t,size_t,long long*);
extern size_t cutils_csll_SinglyLinkedList_long_long_sub(cutils_csll_SinglyLinkedList_long_long*,size_t,size_t,long long*);
extern long long cutils_csll_SinglyLinkedList_long_long_get(cutils_csll_SinglyLinkedList_long_long*,size_t);
extern bool cutils_csll_SinglyLinkedList_long_long_find(cutils_csll_SinglyLinkedList_long_long*,bool(*)(const void*,const void*,size_t),const void*,size_t*);
extern size_t cutils_csll_SinglyLinkedList_long_long_findall(cutils_csll_SinglyLinkedList_long_long*,bool(*)(const void*,const void*,size_t),const void*,size_t*);
extern bool cutils_csll_SinglyLinkedList_long_long_format(const long long*,char**,size_t*);
extern bool cutils_csll_SinglyLinkedList_long_long_compare(const void*,const void*,size_t);
extern void(*cutils_csll_SinglyLinkedList_long_long_del)(cutils_csll_SinglyLinkedList_long_long*);
extern size_t(*cutils_csll_SinglyLinkedList_long_long_len)(cutils_csll_SinglyLinkedList_long_long*);
extern bool(*cutils_csll_SinglyLinkedList_long_long_swap)(cutils_csll_SinglyLinkedList_long_long*,size_t,size_t,size_t);
extern bool(*cutils_csll_SinglyLinkedList_long_long_reverse)(cutils_csll_SinglyLinkedList_long_long*);
extern size_t(*cutils_csll_SinglyLinkedList_long_long_pull)(cutils_csll_SinglyLinkedList_long_long*,size_t,size_t);
extern void(*cutils_csll_SinglyLinkedList_long_long_truncate)(cutils_csll_SinglyLinkedList_long_long*,size_t);
extern void(*cutils_csll_SinglyLinkedList_long_long_clear)(cutils_csll_SinglyLinkedList_long_long*);
extern void(*cutils_csll_SinglyLinkedList_long_long_map)(cutils_csll_SinglyLinkedList_long_long*,size_t,size_t,void(*)(size_t,long long*));
extern void(*cutils_csll_SinglyLinkedList_long_long_print)(cutils_csll_SinglyLinkedList_long_long*,FILE*,const char*,bool(*)());
/*----------------------------------------------------------------------------*/
typedef struct {} cutils_csll_SinglyLinkedList_unsigned_long_long;
typedef struct {} cutils_csll_SinglyLinkedList_unsigned_long_long_iterator;
extern bool cutils_csll_SinglyLinkedList_unsigned_long_long_new(cutils_csll_SinglyLinkedList_unsigned_long_long**,size_t,unsigned long long*);
extern cutils_csll_SinglyLinkedList_unsigned_long_long_iterator* cutils_csll_SinglyLinkedList_unsigned_long_long_iter(cutils_csll_SinglyLinkedList_unsigned_long_long*);
extern bool cutils_csll_SinglyLinkedList_unsigned_long_long_next(cutils_csll_SinglyLinkedList_unsigned_long_long_iterator*,unsigned long long**);
extern bool cutils_csll_SinglyLinkedList_unsigned_long_long_append(cutils_csll_SinglyLinkedList_unsigned_long_long*,size_t,unsigned long long*);
extern bool cutils_csll_SinglyLinkedList_unsigned_long_long_push(cutils_csll_SinglyLinkedList_unsigned_long_long*,size_t,size_t,unsigned long long*);
extern bool cutils_csll_SinglyLinkedList_unsigned_long_long_set(cutils_csll_SinglyLinkedList_unsigned_long_long*,size_t,size_t,unsigned long long*);
extern size_t cutils_csll_SinglyLinkedList_unsigned_long_long_pop(cutils_csll_SinglyLinkedList_unsigned_long_long*,size_t,size_t,unsigned long long*);
extern size_t cutils_csll_SinglyLinkedList_unsigned_long_long_sub(cutils_csll_SinglyLinkedList_unsigned_long_long*,size_t,size_t,unsigned long long*);
extern unsigned long long cutils_csll_SinglyLinkedList_unsigned_long_long_get(cutils_csll_SinglyLinkedList_unsigned_long_long*,size_t);
extern bool cutils_csll_SinglyLinkedList_unsigned_long_long_find(cutils_csll_SinglyLinkedList_unsigned_long_long*,bool(*)(const void*,const void*,size_t),const void*,size_t*);
extern size_t cutils_csll_SinglyLinkedList_unsigned_long_long_findall(cutils_csll_SinglyLinkedList_unsigned_long_long*,bool(*)(const void*,const void*,size_t),const void*,size_t*);
extern bool cutils_csll_SinglyLinkedList_unsigned_long_long_format(const unsigned long long*,char**,size_t*);
extern bool cutils_csll_SinglyLinkedList_unsigned_long_long_compare(const void*,const void*,size_t);
extern void(*cutils_csll_SinglyLinkedList_unsigned_long_long_del)(cutils_csll_SinglyLinkedList_unsigned_long_long*);
extern size_t(*cutils_csll_SinglyLinkedList_unsigned_long_long_len)(cutils_csll_SinglyLinkedList_unsigned_long_long*);
extern bool(*cutils_csll_SinglyLinkedList_unsigned_long_long_swap)(cutils_csll_SinglyLinkedList_unsigned_long_long*,size_t,size_t,size_t);
extern bool(*cutils_csll_SinglyLinkedList_unsigned_long_long_reverse)(cutils_csll_SinglyLinkedList_unsigned_long_long*);
extern size_t(*cutils_csll_SinglyLinkedList_unsigned_long_long_pull)(cutils_csll_SinglyLinkedList_unsigned_long_long*,size_t,size_t);
extern void(*cutils_csll_SinglyLinkedList_unsigned_long_long_truncate)(cutils_csll_SinglyLinkedList_unsigned_long_long*,size_t);
extern void(*cutils_csll_SinglyLinkedList_unsigned_long_long_clear)(cutils_csll_SinglyLinkedList_unsigned_long_long*);
extern void(*cutils_csll_SinglyLinkedList_unsigned_long_long_map)(cutils_csll_SinglyLinkedList_unsigned_long_long*,size_t,size_t,void(*)(size_t,unsigned long long*));
extern void(*cutils_csll_SinglyLinkedList_unsigned_long_long_print)(cutils_csll_SinglyLinkedList_unsigned_long_long*,FILE*,const char*,bool(*)());
/*----------------------------------------------------------------------------*/
typedef struct {} cutils_csll_SinglyLinkedList_float;
typedef struct {} cutils_csll_SinglyLinkedList_float_iterator;
extern bool cutils_csll_SinglyLinkedList_float_new(cutils_csll_SinglyLinkedList_float**,size_t,float*);
extern cutils_csll_SinglyLinkedList_float_iterator* cutils_csll_SinglyLinkedList_float_iter(cutils_csll_SinglyLinkedList_float*);
extern bool cutils_csll_SinglyLinkedList_float_next(cutils_csll_SinglyLinkedList_float_iterator*,float**);
extern bool cutils_csll_SinglyLinkedList_float_append(cutils_csll_SinglyLinkedList_float*,size_t,float*);
extern bool cutils_csll_SinglyLinkedList_float_push(cutils_csll_SinglyLinkedList_float*,size_t,size_t,float*);
extern bool cutils_csll_SinglyLinkedList_float_set(cutils_csll_SinglyLinkedList_float*,size_t,size_t,float*);
extern size_t cutils_csll_SinglyLinkedList_float_pop(cutils_csll_SinglyLinkedList_float*,size_t,size_t,float*);
extern size_t cutils_csll_SinglyLinkedList_float_sub(cutils_csll_SinglyLinkedList_float*,size_t,size_t,float*);
extern float cutils_csll_SinglyLinkedList_float_get(cutils_csll_SinglyLinkedList_float*,size_t);
extern bool cutils_csll_SinglyLinkedList_float_find(cutils_csll_SinglyLinkedList_float*,bool(*)(const void*,const void*,size_t),const void*,size_t*);
extern size_t cutils_csll_SinglyLinkedList_float_findall(cutils_csll_SinglyLinkedList_float*,bool(*)(const void*,const void*,size_t),const void*,size_t*);
extern bool cutils_csll_SinglyLinkedList_float_format(const float*,char**,size_t*);
extern bool cutils_csll_SinglyLinkedList_float_compare(const void*,const void*,size_t);
extern void(*cutils_csll_SinglyLinkedList_float_del)(cutils_csll_SinglyLinkedList_float*);
extern size_t(*cutils_csll_SinglyLinkedList_float_len)(cutils_csll_SinglyLinkedList_float*);
extern bool(*cutils_csll_SinglyLinkedList_float_swap)(cutils_csll_SinglyLinkedList_float*,size_t,size_t,size_t);
extern bool(*cutils_csll_SinglyLinkedList_float_reverse)(cutils_csll_SinglyLinkedList_float*);
extern size_t(*cutils_csll_SinglyLinkedList_float_pull)(cutils_csll_SinglyLinkedList_float*,size_t,size_t);
extern void(*cutils_csll_SinglyLinkedList_float_truncate)(cutils_csll_SinglyLinkedList_float*,size_t);
extern void(*cutils_csll_SinglyLinkedList_float_clear)(cutils_csll_SinglyLinkedList_float*);
extern void(*cutils_csll_SinglyLinkedList_float_map)(cutils_csll_SinglyLinkedList_float*,size_t,size_t,void(*)(size_t,float*));
extern void(*cutils_csll_SinglyLinkedList_float_print)(cutils_csll_SinglyLinkedList_float*,FILE*,const char*,bool(*)());
/*----------------------------------------------------------------------------*/
typedef struct {} cutils_csll_SinglyLinkedList_double;
typedef struct {} cutils_csll_SinglyLinkedList_double_iterator;
extern bool cutils_csll_SinglyLinkedList_double_new(cutils_csll_SinglyLinkedList_double**,size_t,double*);
extern cutils_csll_SinglyLinkedList_double_iterator* cutils_csll_SinglyLinkedList_double_iter(cutils_csll_SinglyLinkedList_double*);
extern bool cutils_csll_SinglyLinkedList_double_next(cutils_csll_SinglyLinkedList_double_iterator*,double**);
extern bool cutils_csll_SinglyLinkedList_double_append(cutils_csll_SinglyLinkedList_double*,size_t,double*);
extern bool cutils_csll_SinglyLinkedList_double_push(cutils_csll_SinglyLinkedList_double*,size_t,size_t,double*);
extern bool cutils_csll_SinglyLinkedList_double_set(cutils_csll_SinglyLinkedList_double*,size_t,size_t,double*);
extern size_t cutils_csll_SinglyLinkedList_double_pop(cutils_csll_SinglyLinkedList_double*,size_t,size_t,double*);
extern size_t cutils_csll_SinglyLinkedList_double_sub(cutils_csll_SinglyLinkedList_double*,size_t,size_t,double*);
extern double cutils_csll_SinglyLinkedList_double_get(cutils_csll_SinglyLinkedList_double*,size_t);
extern bool cutils_csll_SinglyLinkedList_double_find(cutils_csll_SinglyLinkedList_double*,bool(*)(const void*,const void*,size_t),const void*,size_t*);
extern size_t cutils_csll_SinglyLinkedList_double_findall(cutils_csll_SinglyLinkedList_double*,bool(*)(const void*,const void*,size_t),const void*,size_t*);
extern bool cutils_csll_SinglyLinkedList_double_format(const double*,char**,size_t*);
extern bool cutils_csll_SinglyLinkedList_double_compare(const void*,const void*,size_t);
extern void(*cutils_csll_SinglyLinkedList_double_del)(cutils_csll_SinglyLinkedList_double*);
extern size_t(*cutils_csll_SinglyLinkedList_double_len)(cutils_csll_SinglyLinkedList_double*);
extern bool(*cutils_csll_SinglyLinkedList_double_swap)(cutils_csll_SinglyLinkedList_double*,size_t,size_t,size_t);
extern bool(*cutils_csll_SinglyLinkedList_double_reverse)(cutils_csll_SinglyLinkedList_double*);
extern size_t(*cutils_csll_SinglyLinkedList_double_pull)(cutils_csll_SinglyLinkedList_double*,size_t,size_t);
extern void(*cutils_csll_SinglyLinkedList_double_truncate)(cutils_csll_SinglyLinkedList_double*,size_t);
extern void(*cutils_csll_SinglyLinkedList_double_clear)(cutils_csll_SinglyLinkedList_double*);
extern void(*cutils_csll_SinglyLinkedList_double_map)(cutils_csll_SinglyLinkedList_double*,size_t,size_t,void(*)(size_t,double*));
extern void(*cutils_csll_SinglyLinkedList_double_print)(cutils_csll_SinglyLinkedList_double*,FILE*,const char*,bool(*)());
/*----------------------------------------------------------------------------*/
typedef struct {} cutils_csll_SinglyLinkedList_long_double;
typedef struct {} cutils_csll_SinglyLinkedList_long_double_iterator;
extern bool cutils_csll_SinglyLinkedList_long_double_new(cutils_csll_SinglyLinkedList_long_double**,size_t,long double*);
extern cutils_csll_SinglyLinkedList_long_double_iterator* cutils_csll_SinglyLinkedList_long_double_iter(cutils_csll_SinglyLinkedList_long_double*);
extern bool cutils_csll_SinglyLinkedList_long_double_next(cutils_csll_SinglyLinkedList_long_double_iterator*,long double**);
extern bool cutils_csll_SinglyLinkedList_long_double_append(cutils_csll_SinglyLinkedList_long_double*,size_t,long double*);
extern bool cutils_csll_SinglyLinkedList_long_double_push(cutils_csll_SinglyLinkedList_long_double*,size_t,size_t,long double*);
extern bool cutils_csll_SinglyLinkedList_long_double_set(cutils_csll_SinglyLinkedList_long_double*,size_t,size_t,long double*);
extern size_t cutils_csll_SinglyLinkedList_long_double_pop(cutils_csll_SinglyLinkedList_long_double*,size_t,size_t,long double*);
extern size_t cutils_csll_SinglyLinkedList_long_double_sub(cutils_csll_SinglyLinkedList_long_double*,size_t,size_t,long double*);
extern long double cutils_csll_SinglyLinkedList_long_double_get(cutils_csll_SinglyLinkedList_long_double*,size_t);
extern bool cutils_csll_SinglyLinkedList_long_double_find(cutils_csll_SinglyLinkedList_long_double*,bool(*)(const void*,const void*,size_t),const void*,size_t*);
extern size_t cutils_csll_SinglyLinkedList_long_double_findall(cutils_csll_SinglyLinkedList_long_double*,bool(*)(const void*,const void*,size_t),const void*,size_t*);
extern bool cutils_csll_SinglyLinkedList_long_double_format(const long double*,char**,size_t*);
extern bool cutils_csll_SinglyLinkedList_long_double_compare(const void*,const void*,size_t);
extern void(*cutils_csll_SinglyLinkedList_long_double_del)(cutils_csll_SinglyLinkedList_long_double*);
extern size_t(*cutils_csll_SinglyLinkedList_long_double_len)(cutils_csll_SinglyLinkedList_long_double*);
extern bool(*cutils_csll_SinglyLinkedList_long_double_swap)(cutils_csll_SinglyLinkedList_long_double*,size_t,size_t,size_t);
extern bool(*cutils_csll_SinglyLinkedList_long_double_reverse)(cutils_csll_SinglyLinkedList_long_double*);
extern size_t(*cutils_csll_SinglyLinkedList_long_double_pull)(cutils_csll_SinglyLinkedList_long_double*,size_t,size_t);
extern void(*cutils_csll_SinglyLinkedList_long_double_truncate)(cutils_csll_SinglyLinkedList_long_double*,size_t);
extern void(*cutils_csll_SinglyLinkedList_long_double_clear)(cutils_csll_SinglyLinkedList_long_double*);
extern void(*cutils_csll_SinglyLinkedList_long_double_map)(cutils_csll_SinglyLinkedList_long_double*,size_t,size_t,void(*)(size_t,long double*));
extern void(*cutils_csll_SinglyLinkedList_long_double_print)(cutils_csll_SinglyLinkedList_long_double*,FILE*,const char*,bool(*)());
/*----------------------------------------------------------------------------*/
typedef struct {} cutils_csll_SinglyLinkedList_bool;
typedef struct {} cutils_csll_SinglyLinkedList_bool_iterator;
extern bool cutils_csll_SinglyLinkedList_bool_new(cutils_csll_SinglyLinkedList_bool**,size_t,bool*);
extern cutils_csll_SinglyLinkedList_bool_iterator* cutils_csll_SinglyLinkedList_bool_iter(cutils_csll_SinglyLinkedList_bool*);
extern bool cutils_csll_SinglyLinkedList_bool_next(cutils_csll_SinglyLinkedList_bool_iterator*,bool**);
extern bool cutils_csll_SinglyLinkedList_bool_append(cutils_csll_SinglyLinkedList_bool*,size_t,bool*);
extern bool cutils_csll_SinglyLinkedList_bool_push(cutils_csll_SinglyLinkedList_bool*,size_t,size_t,bool*);
extern bool cutils_csll_SinglyLinkedList_bool_set(cutils_csll_SinglyLinkedList_bool*,size_t,size_t,bool*);
extern size_t cutils_csll_SinglyLinkedList_bool_pop(cutils_csll_SinglyLinkedList_bool*,size_t,size_t,bool*);
extern size_t cutils_csll_SinglyLinkedList_bool_sub(cutils_csll_SinglyLinkedList_bool*,size_t,size_t,bool*);
extern bool cutils_csll_SinglyLinkedList_bool_get(cutils_csll_SinglyLinkedList_bool*,size_t);
extern bool cutils_csll_SinglyLinkedList_bool_find(cutils_csll_SinglyLinkedList_bool*,bool(*)(const void*,const void*,size_t),const void*,size_t*);
extern size_t cutils_csll_SinglyLinkedList_bool_findall(cutils_csll_SinglyLinkedList_bool*,bool(*)(const void*,const void*,size_t),const void*,size_t*);
extern bool cutils_csll_SinglyLinkedList_bool_format(const bool*,char**,size_t*);
extern bool cutils_csll_SinglyLinkedList_bool_compare(const void*,const void*,size_t);
extern void(*cutils_csll_SinglyLinkedList_bool_del)(cutils_csll_SinglyLinkedList_bool*);
extern size_t(*cutils_csll_SinglyLinkedList_bool_len)(cutils_csll_SinglyLinkedList_bool*);
extern bool(*cutils_csll_SinglyLinkedList_bool_swap)(cutils_csll_SinglyLinkedList_bool*,size_t,size_t,size_t);
extern bool(*cutils_csll_SinglyLinkedList_bool_reverse)(cutils_csll_SinglyLinkedList_bool*);
extern size_t(*cutils_csll_SinglyLinkedList_bool_pull)(cutils_csll_SinglyLinkedList_bool*,size_t,size_t);
extern void(*cutils_csll_SinglyLinkedList_bool_truncate)(cutils_csll_SinglyLinkedList_bool*,size_t);
extern void(*cutils_csll_SinglyLinkedList_bool_clear)(cutils_csll_SinglyLinkedList_bool*);
extern void(*cutils_csll_SinglyLinkedList_bool_map)(cutils_csll_SinglyLinkedList_bool*,size_t,size_t,void(*)(size_t,bool*));
extern void(*cutils_csll_SinglyLinkedList_bool_print)(cutils_csll_SinglyLinkedList_bool*,FILE*,const char*,bool(*)());
/*----------------------------------------------------------------------------*/
typedef struct {} cutils_csll_SinglyLinkedList_size_t;
typedef struct {} cutils_csll_SinglyLinkedList_size_t_iterator;
extern bool cutils_csll_SinglyLinkedList_size_t_new(cutils_csll_SinglyLinkedList_size_t**,size_t,size_t*);
extern cutils_csll_SinglyLinkedList_size_t_iterator* cutils_csll_SinglyLinkedList_size_t_iter(cutils_csll_SinglyLinkedList_size_t*);
extern bool cutils_csll_SinglyLinkedList_size_t_next(cutils_csll_SinglyLinkedList_size_t_iterator*,size_t**);
extern bool cutils_csll_SinglyLinkedList_size_t_append(cutils_csll_SinglyLinkedList_size_t*,size_t,size_t*);
extern bool cutils_csll_SinglyLinkedList_size_t_push(cutils_csll_SinglyLinkedList_size_t*,size_t,size_t,size_t*);
extern bool cutils_csll_SinglyLinkedList_size_t_set(cutils_csll_SinglyLinkedList_size_t*,size_t,size_t,size_t*);
extern size_t cutils_csll_SinglyLinkedList_size_t_pop(cutils_csll_SinglyLinkedList_size_t*,size_t,size_t,size_t*);
extern size_t cutils_csll_SinglyLinkedList_size_t_sub(cutils_csll_SinglyLinkedList_size_t*,size_t,size_t,size_t*);
extern size_t cutils_csll_SinglyLinkedList_size_t_get(cutils_csll_SinglyLinkedList_size_t*,size_t);
extern bool cutils_csll_SinglyLinkedList_size_t_find(cutils_csll_SinglyLinkedList_size_t*,bool(*)(const void*,const void*,size_t),const void*,size_t*);
extern size_t cutils_csll_SinglyLinkedList_size_t_findall(cutils_csll_SinglyLinkedList_size_t*,bool(*)(const void*,const void*,size_t),const void*,size_t*);
extern bool cutils_csll_SinglyLinkedList_size_t_format(const size_t*,char**,size_t*);
extern bool cutils_csll_SinglyLinkedList_size_t_compare(const void*,const void*,size_t);
extern void(*cutils_csll_SinglyLinkedList_size_t_del)(cutils_csll_SinglyLinkedList_size_t*);
extern size_t(*cutils_csll_SinglyLinkedList_size_t_len)(cutils_csll_SinglyLinkedList_size_t*);
extern bool(*cutils_csll_SinglyLinkedList_size_t_swap)(cutils_csll_SinglyLinkedList_size_t*,size_t,size_t,size_t);
extern bool(*cutils_csll_SinglyLinkedList_size_t_reverse)(cutils_csll_SinglyLinkedList_size_t*);
extern size_t(*cutils_csll_SinglyLinkedList_size_t_pull)(cutils_csll_SinglyLinkedList_size_t*,size_t,size_t);
extern void(*cutils_csll_SinglyLinkedList_size_t_truncate)(cutils_csll_SinglyLinkedList_size_t*,size_t);
extern void(*cutils_csll_SinglyLinkedList_size_t_clear)(cutils_csll_SinglyLinkedList_size_t*);
extern void(*cutils_csll_SinglyLinkedList_size_t_map)(cutils_csll_SinglyLinkedList_size_t*,size_t,size_t,void(*)(size_t,size_t*));
extern void(*cutils_csll_SinglyLinkedList_size_t_print)(cutils_csll_SinglyLinkedList_size_t*,FILE*,const char*,bool(*)());
/*----------------------------------------------------------------------------*/
typedef struct {} cutils_csll_SinglyLinkedList_ptrdiff_t;
typedef struct {} cutils_csll_SinglyLinkedList_ptrdiff_t_iterator;
extern bool cutils_csll_SinglyLinkedList_ptrdiff_t_new(cutils_csll_SinglyLinkedList_ptrdiff_t**,size_t,ptrdiff_t*);
extern cutils_csll_SinglyLinkedList_ptrdiff_t_iterator* cutils_csll_SinglyLinkedList_ptrdiff_t_iter(cutils_csll_SinglyLinkedList_ptrdiff_t*);
extern bool cutils_csll_SinglyLinkedList_ptrdiff_t_next(cutils_csll_SinglyLinkedList_ptrdiff_t_iterator*,ptrdiff_t**);
extern bool cutils_csll_SinglyLinkedList_ptrdiff_t_append(cutils_csll_SinglyLinkedList_ptrdiff_t*,size_t,ptrdiff_t*);
extern bool cutils_csll_SinglyLinkedList_ptrdiff_t_push(cutils_csll_SinglyLinkedList_ptrdiff_t*,size_t,size_t,ptrdiff_t*);
extern bool cutils_csll_SinglyLinkedList_ptrdiff_t_set(cutils_csll_SinglyLinkedList_ptrdiff_t*,size_t,size_t,ptrdiff_t*);
extern size_t cutils_csll_SinglyLinkedList_ptrdiff_t_pop(cutils_csll_SinglyLinkedList_ptrdiff_t*,size_t,size_t,ptrdiff_t*);
extern size_t cutils_csll_SinglyLinkedList_ptrdiff_t_sub(cutils_csll_SinglyLinkedList_ptrdiff_t*,size_t,size_t,ptrdiff_t*);
extern ptrdiff_t cutils_csll_SinglyLinkedList_ptrdiff_t_get(cutils_csll_SinglyLinkedList_ptrdiff_t*,size_t);
extern bool cutils_csll_SinglyLinkedList_ptrdiff_t_find(cutils_csll_SinglyLinkedList_ptrdiff_t*,bool(*)(const void*,const void*,size_t),const void*,size_t*);
extern size_t cutils_csll_SinglyLinkedList_ptrdiff_t_findall(cutils_csll_SinglyLinkedList_ptrdiff_t*,bool(*)(const void*,const void*,size_t),const void*,size_t*);
extern bool cutils_csll_SinglyLinkedList_ptrdiff_t_format(const ptrdiff_t*,char**,size_t*);
extern bool cutils_csll_SinglyLinkedList_ptrdiff_t_compare(const void*,const void*,size_t);
extern void(*cutils_csll_SinglyLinkedList_ptrdiff_t_del)(cutils_csll_SinglyLinkedList_ptrdiff_t*);
extern size_t(*cutils_csll_SinglyLinkedList_ptrdiff_t_len)(cutils_csll_SinglyLinkedList_ptrdiff_t*);
extern bool(*cutils_csll_SinglyLinkedList_ptrdiff_t_swap)(cutils_csll_SinglyLinkedList_ptrdiff_t*,size_t,size_t,size_t);
extern bool(*cutils_csll_SinglyLinkedList_ptrdiff_t_reverse)(cutils_csll_SinglyLinkedList_ptrdiff_t*);
extern size_t(*cutils_csll_SinglyLinkedList_ptrdiff_t_pull)(cutils_csll_SinglyLinkedList_ptrdiff_t*,size_t,size_t);
extern void(*cutils_csll_SinglyLinkedList_ptrdiff_t_truncate)(cutils_csll_SinglyLinkedList_ptrdiff_t*,size_t);
extern void(*cutils_csll_SinglyLinkedList_ptrdiff_t_clear)(cutils_csll_SinglyLinkedList_ptrdiff_t*);
extern void(*cutils_csll_SinglyLinkedList_ptrdiff_t_map)(cutils_csll_SinglyLinkedList_ptrdiff_t*,size_t,size_t,void(*)(size_t,ptrdiff_t*));
extern void(*cutils_csll_SinglyLinkedList_ptrdiff_t_print)(cutils_csll_SinglyLinkedList_ptrdiff_t*,FILE*,const char*,bool(*)());
#endif /* _C_SINGLY_LINKED_LIST_H_35118355245711974_ */
