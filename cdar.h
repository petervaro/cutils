/* INFO ************************************************************************
**                                                                            **
**                                   cutils                                   **
**                                   ======                                   **
**                                                                            **
**                     Modern and Lightweight C Utilities                     **
**                       Version: 0.8.72.314 (20140710)                       **
**                                                                            **
**                                File: cdar.h                                **
**                                                                            **
**           Designed and written by Peter Varo. Copyright (c) 2014           **
**             License agreement is provided in the LICENSE file              **
**                 For more info visit: http://www.cutils.org                 **
**                                                                            **
************************************************************************ INFO */

#ifndef _C_DYNAMIC_ARRAY_H_2427147457128005_
#define _C_DYNAMIC_ARRAY_H_2427147457128005_

#include <stddef.h>   /* ptrdiff_t */
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

/*----------------------------------------------------------------------------*/
typedef struct {} cutils_cdar_DynamicArray_char;
extern bool cutils_cdar_DynamicArray_char_new(cutils_cdar_DynamicArray_char**,size_t,char*);
extern char* cutils_cdar_DynamicArray_char_data(cutils_cdar_DynamicArray_char*,size_t*,size_t*);
extern char* cutils_cdar_DynamicArray_char_raw(cutils_cdar_DynamicArray_char*);
extern bool cutils_cdar_DynamicArray_char_append(cutils_cdar_DynamicArray_char*,size_t,char*);
extern bool cutils_cdar_DynamicArray_char_push(cutils_cdar_DynamicArray_char*,size_t,size_t,char*);
extern bool cutils_cdar_DynamicArray_char_set(cutils_cdar_DynamicArray_char*,size_t,size_t,char*);
extern size_t cutils_cdar_DynamicArray_char_pop(cutils_cdar_DynamicArray_char*,size_t,size_t,char*);
extern size_t cutils_cdar_DynamicArray_char_sub(cutils_cdar_DynamicArray_char*,size_t,size_t,char*);
extern char cutils_cdar_DynamicArray_char_get(cutils_cdar_DynamicArray_char*,size_t);
extern bool cutils_cdar_DynamicArray_char_find(cutils_cdar_DynamicArray_char*,const char*,size_t*);
extern size_t cutils_cdar_DynamicArray_char_findall(cutils_cdar_DynamicArray_char*,const char*,size_t*);
extern void(*cutils_cdar_DynamicArray_char_del)(cutils_cdar_DynamicArray_char*);
extern size_t(*cutils_cdar_DynamicArray_char_len)(cutils_cdar_DynamicArray_char*);
extern size_t(*cutils_cdar_DynamicArray_char_size)(cutils_cdar_DynamicArray_char*);
extern bool(*cutils_cdar_DynamicArray_char_resize)(cutils_cdar_DynamicArray_char*,size_t);
extern bool(*cutils_cdar_DynamicArray_char_swap)(cutils_cdar_DynamicArray_char*,size_t,size_t,size_t);
extern bool(*cutils_cdar_DynamicArray_char_reverse)(cutils_cdar_DynamicArray_char*);
extern size_t(*cutils_cdar_DynamicArray_char_pull)(cutils_cdar_DynamicArray_char*,size_t,size_t);
extern void(*cutils_cdar_DynamicArray_char_truncate)(cutils_cdar_DynamicArray_char*,size_t);
extern void(*cutils_cdar_DynamicArray_char_clear)(cutils_cdar_DynamicArray_char*);
/*----------------------------------------------------------------------------*/
typedef struct {} cutils_cdar_DynamicArray_signed_char;
extern bool cutils_cdar_DynamicArray_signed_char_new(cutils_cdar_DynamicArray_signed_char**,size_t,signed char*);
extern signed char* cutils_cdar_DynamicArray_signed_char_data(cutils_cdar_DynamicArray_signed_char*,size_t*,size_t*);
extern signed char* cutils_cdar_DynamicArray_signed_char_raw(cutils_cdar_DynamicArray_signed_char*);
extern bool cutils_cdar_DynamicArray_signed_char_append(cutils_cdar_DynamicArray_signed_char*,size_t,signed char*);
extern bool cutils_cdar_DynamicArray_signed_char_push(cutils_cdar_DynamicArray_signed_char*,size_t,size_t,signed char*);
extern bool cutils_cdar_DynamicArray_signed_char_set(cutils_cdar_DynamicArray_signed_char*,size_t,size_t,signed char*);
extern size_t cutils_cdar_DynamicArray_signed_char_pop(cutils_cdar_DynamicArray_signed_char*,size_t,size_t,signed char*);
extern size_t cutils_cdar_DynamicArray_signed_char_sub(cutils_cdar_DynamicArray_signed_char*,size_t,size_t,signed char*);
extern signed char cutils_cdar_DynamicArray_signed_char_get(cutils_cdar_DynamicArray_signed_char*,size_t);
extern bool cutils_cdar_DynamicArray_signed_char_find(cutils_cdar_DynamicArray_signed_char*,const signed char*,size_t*);
extern size_t cutils_cdar_DynamicArray_signed_char_findall(cutils_cdar_DynamicArray_signed_char*,const signed char*,size_t*);
extern void(*cutils_cdar_DynamicArray_signed_char_del)(cutils_cdar_DynamicArray_signed_char*);
extern size_t(*cutils_cdar_DynamicArray_signed_char_len)(cutils_cdar_DynamicArray_signed_char*);
extern size_t(*cutils_cdar_DynamicArray_signed_char_size)(cutils_cdar_DynamicArray_signed_char*);
extern bool(*cutils_cdar_DynamicArray_signed_char_resize)(cutils_cdar_DynamicArray_signed_char*,size_t);
extern bool(*cutils_cdar_DynamicArray_signed_char_swap)(cutils_cdar_DynamicArray_signed_char*,size_t,size_t,size_t);
extern bool(*cutils_cdar_DynamicArray_signed_char_reverse)(cutils_cdar_DynamicArray_signed_char*);
extern size_t(*cutils_cdar_DynamicArray_signed_char_pull)(cutils_cdar_DynamicArray_signed_char*,size_t,size_t);
extern void(*cutils_cdar_DynamicArray_signed_char_truncate)(cutils_cdar_DynamicArray_signed_char*,size_t);
extern void(*cutils_cdar_DynamicArray_signed_char_clear)(cutils_cdar_DynamicArray_signed_char*);
/*----------------------------------------------------------------------------*/
typedef struct {} cutils_cdar_DynamicArray_unsigned_char;
extern bool cutils_cdar_DynamicArray_unsigned_char_new(cutils_cdar_DynamicArray_unsigned_char**,size_t,unsigned char*);
extern unsigned char* cutils_cdar_DynamicArray_unsigned_char_data(cutils_cdar_DynamicArray_unsigned_char*,size_t*,size_t*);
extern unsigned char* cutils_cdar_DynamicArray_unsigned_char_raw(cutils_cdar_DynamicArray_unsigned_char*);
extern bool cutils_cdar_DynamicArray_unsigned_char_append(cutils_cdar_DynamicArray_unsigned_char*,size_t,unsigned char*);
extern bool cutils_cdar_DynamicArray_unsigned_char_push(cutils_cdar_DynamicArray_unsigned_char*,size_t,size_t,unsigned char*);
extern bool cutils_cdar_DynamicArray_unsigned_char_set(cutils_cdar_DynamicArray_unsigned_char*,size_t,size_t,unsigned char*);
extern size_t cutils_cdar_DynamicArray_unsigned_char_pop(cutils_cdar_DynamicArray_unsigned_char*,size_t,size_t,unsigned char*);
extern size_t cutils_cdar_DynamicArray_unsigned_char_sub(cutils_cdar_DynamicArray_unsigned_char*,size_t,size_t,unsigned char*);
extern unsigned char cutils_cdar_DynamicArray_unsigned_char_get(cutils_cdar_DynamicArray_unsigned_char*,size_t);
extern bool cutils_cdar_DynamicArray_unsigned_char_find(cutils_cdar_DynamicArray_unsigned_char*,const unsigned char*,size_t*);
extern size_t cutils_cdar_DynamicArray_unsigned_char_findall(cutils_cdar_DynamicArray_unsigned_char*,const unsigned char*,size_t*);
extern void(*cutils_cdar_DynamicArray_unsigned_char_del)(cutils_cdar_DynamicArray_unsigned_char*);
extern size_t(*cutils_cdar_DynamicArray_unsigned_char_len)(cutils_cdar_DynamicArray_unsigned_char*);
extern size_t(*cutils_cdar_DynamicArray_unsigned_char_size)(cutils_cdar_DynamicArray_unsigned_char*);
extern bool(*cutils_cdar_DynamicArray_unsigned_char_resize)(cutils_cdar_DynamicArray_unsigned_char*,size_t);
extern bool(*cutils_cdar_DynamicArray_unsigned_char_swap)(cutils_cdar_DynamicArray_unsigned_char*,size_t,size_t,size_t);
extern bool(*cutils_cdar_DynamicArray_unsigned_char_reverse)(cutils_cdar_DynamicArray_unsigned_char*);
extern size_t(*cutils_cdar_DynamicArray_unsigned_char_pull)(cutils_cdar_DynamicArray_unsigned_char*,size_t,size_t);
extern void(*cutils_cdar_DynamicArray_unsigned_char_truncate)(cutils_cdar_DynamicArray_unsigned_char*,size_t);
extern void(*cutils_cdar_DynamicArray_unsigned_char_clear)(cutils_cdar_DynamicArray_unsigned_char*);
/*----------------------------------------------------------------------------*/
typedef struct {} cutils_cdar_DynamicArray_char_ptr;
extern bool cutils_cdar_DynamicArray_char_ptr_new(cutils_cdar_DynamicArray_char_ptr**,size_t,char**);
extern char** cutils_cdar_DynamicArray_char_ptr_data(cutils_cdar_DynamicArray_char_ptr*,size_t*,size_t*);
extern char** cutils_cdar_DynamicArray_char_ptr_raw(cutils_cdar_DynamicArray_char_ptr*);
extern bool cutils_cdar_DynamicArray_char_ptr_append(cutils_cdar_DynamicArray_char_ptr*,size_t,char**);
extern bool cutils_cdar_DynamicArray_char_ptr_push(cutils_cdar_DynamicArray_char_ptr*,size_t,size_t,char**);
extern bool cutils_cdar_DynamicArray_char_ptr_set(cutils_cdar_DynamicArray_char_ptr*,size_t,size_t,char**);
extern size_t cutils_cdar_DynamicArray_char_ptr_pop(cutils_cdar_DynamicArray_char_ptr*,size_t,size_t,char**);
extern size_t cutils_cdar_DynamicArray_char_ptr_sub(cutils_cdar_DynamicArray_char_ptr*,size_t,size_t,char**);
extern char* cutils_cdar_DynamicArray_char_ptr_get(cutils_cdar_DynamicArray_char_ptr*,size_t);
extern bool cutils_cdar_DynamicArray_char_ptr_find(cutils_cdar_DynamicArray_char_ptr*,const char**,size_t*);
extern size_t cutils_cdar_DynamicArray_char_ptr_findall(cutils_cdar_DynamicArray_char_ptr*,const char**,size_t*);
extern void(*cutils_cdar_DynamicArray_char_ptr_del)(cutils_cdar_DynamicArray_char_ptr*);
extern size_t(*cutils_cdar_DynamicArray_char_ptr_len)(cutils_cdar_DynamicArray_char_ptr*);
extern size_t(*cutils_cdar_DynamicArray_char_ptr_size)(cutils_cdar_DynamicArray_char_ptr*);
extern bool(*cutils_cdar_DynamicArray_char_ptr_resize)(cutils_cdar_DynamicArray_char_ptr*,size_t);
extern bool(*cutils_cdar_DynamicArray_char_ptr_swap)(cutils_cdar_DynamicArray_char_ptr*,size_t,size_t,size_t);
extern bool(*cutils_cdar_DynamicArray_char_ptr_reverse)(cutils_cdar_DynamicArray_char_ptr*);
extern size_t(*cutils_cdar_DynamicArray_char_ptr_pull)(cutils_cdar_DynamicArray_char_ptr*,size_t,size_t);
extern void(*cutils_cdar_DynamicArray_char_ptr_truncate)(cutils_cdar_DynamicArray_char_ptr*,size_t);
extern void(*cutils_cdar_DynamicArray_char_ptr_clear)(cutils_cdar_DynamicArray_char_ptr*);
/*----------------------------------------------------------------------------*/
typedef struct {} cutils_cdar_DynamicArray_short;
extern bool cutils_cdar_DynamicArray_short_new(cutils_cdar_DynamicArray_short**,size_t,short*);
extern short* cutils_cdar_DynamicArray_short_data(cutils_cdar_DynamicArray_short*,size_t*,size_t*);
extern short* cutils_cdar_DynamicArray_short_raw(cutils_cdar_DynamicArray_short*);
extern bool cutils_cdar_DynamicArray_short_append(cutils_cdar_DynamicArray_short*,size_t,short*);
extern bool cutils_cdar_DynamicArray_short_push(cutils_cdar_DynamicArray_short*,size_t,size_t,short*);
extern bool cutils_cdar_DynamicArray_short_set(cutils_cdar_DynamicArray_short*,size_t,size_t,short*);
extern size_t cutils_cdar_DynamicArray_short_pop(cutils_cdar_DynamicArray_short*,size_t,size_t,short*);
extern size_t cutils_cdar_DynamicArray_short_sub(cutils_cdar_DynamicArray_short*,size_t,size_t,short*);
extern short cutils_cdar_DynamicArray_short_get(cutils_cdar_DynamicArray_short*,size_t);
extern bool cutils_cdar_DynamicArray_short_find(cutils_cdar_DynamicArray_short*,const short*,size_t*);
extern size_t cutils_cdar_DynamicArray_short_findall(cutils_cdar_DynamicArray_short*,const short*,size_t*);
extern void(*cutils_cdar_DynamicArray_short_del)(cutils_cdar_DynamicArray_short*);
extern size_t(*cutils_cdar_DynamicArray_short_len)(cutils_cdar_DynamicArray_short*);
extern size_t(*cutils_cdar_DynamicArray_short_size)(cutils_cdar_DynamicArray_short*);
extern bool(*cutils_cdar_DynamicArray_short_resize)(cutils_cdar_DynamicArray_short*,size_t);
extern bool(*cutils_cdar_DynamicArray_short_swap)(cutils_cdar_DynamicArray_short*,size_t,size_t,size_t);
extern bool(*cutils_cdar_DynamicArray_short_reverse)(cutils_cdar_DynamicArray_short*);
extern size_t(*cutils_cdar_DynamicArray_short_pull)(cutils_cdar_DynamicArray_short*,size_t,size_t);
extern void(*cutils_cdar_DynamicArray_short_truncate)(cutils_cdar_DynamicArray_short*,size_t);
extern void(*cutils_cdar_DynamicArray_short_clear)(cutils_cdar_DynamicArray_short*);
/*----------------------------------------------------------------------------*/
typedef struct {} cutils_cdar_DynamicArray_unsigned_short;
extern bool cutils_cdar_DynamicArray_unsigned_short_new(cutils_cdar_DynamicArray_unsigned_short**,size_t,unsigned short*);
extern unsigned short* cutils_cdar_DynamicArray_unsigned_short_data(cutils_cdar_DynamicArray_unsigned_short*,size_t*,size_t*);
extern unsigned short* cutils_cdar_DynamicArray_unsigned_short_raw(cutils_cdar_DynamicArray_unsigned_short*);
extern bool cutils_cdar_DynamicArray_unsigned_short_append(cutils_cdar_DynamicArray_unsigned_short*,size_t,unsigned short*);
extern bool cutils_cdar_DynamicArray_unsigned_short_push(cutils_cdar_DynamicArray_unsigned_short*,size_t,size_t,unsigned short*);
extern bool cutils_cdar_DynamicArray_unsigned_short_set(cutils_cdar_DynamicArray_unsigned_short*,size_t,size_t,unsigned short*);
extern size_t cutils_cdar_DynamicArray_unsigned_short_pop(cutils_cdar_DynamicArray_unsigned_short*,size_t,size_t,unsigned short*);
extern size_t cutils_cdar_DynamicArray_unsigned_short_sub(cutils_cdar_DynamicArray_unsigned_short*,size_t,size_t,unsigned short*);
extern unsigned short cutils_cdar_DynamicArray_unsigned_short_get(cutils_cdar_DynamicArray_unsigned_short*,size_t);
extern bool cutils_cdar_DynamicArray_unsigned_short_find(cutils_cdar_DynamicArray_unsigned_short*,const unsigned short*,size_t*);
extern size_t cutils_cdar_DynamicArray_unsigned_short_findall(cutils_cdar_DynamicArray_unsigned_short*,const unsigned short*,size_t*);
extern void(*cutils_cdar_DynamicArray_unsigned_short_del)(cutils_cdar_DynamicArray_unsigned_short*);
extern size_t(*cutils_cdar_DynamicArray_unsigned_short_len)(cutils_cdar_DynamicArray_unsigned_short*);
extern size_t(*cutils_cdar_DynamicArray_unsigned_short_size)(cutils_cdar_DynamicArray_unsigned_short*);
extern bool(*cutils_cdar_DynamicArray_unsigned_short_resize)(cutils_cdar_DynamicArray_unsigned_short*,size_t);
extern bool(*cutils_cdar_DynamicArray_unsigned_short_swap)(cutils_cdar_DynamicArray_unsigned_short*,size_t,size_t,size_t);
extern bool(*cutils_cdar_DynamicArray_unsigned_short_reverse)(cutils_cdar_DynamicArray_unsigned_short*);
extern size_t(*cutils_cdar_DynamicArray_unsigned_short_pull)(cutils_cdar_DynamicArray_unsigned_short*,size_t,size_t);
extern void(*cutils_cdar_DynamicArray_unsigned_short_truncate)(cutils_cdar_DynamicArray_unsigned_short*,size_t);
extern void(*cutils_cdar_DynamicArray_unsigned_short_clear)(cutils_cdar_DynamicArray_unsigned_short*);
/*----------------------------------------------------------------------------*/
typedef struct {} cutils_cdar_DynamicArray_int;
extern bool cutils_cdar_DynamicArray_int_new(cutils_cdar_DynamicArray_int**,size_t,int*);
extern int* cutils_cdar_DynamicArray_int_data(cutils_cdar_DynamicArray_int*,size_t*,size_t*);
extern int* cutils_cdar_DynamicArray_int_raw(cutils_cdar_DynamicArray_int*);
extern bool cutils_cdar_DynamicArray_int_append(cutils_cdar_DynamicArray_int*,size_t,int*);
extern bool cutils_cdar_DynamicArray_int_push(cutils_cdar_DynamicArray_int*,size_t,size_t,int*);
extern bool cutils_cdar_DynamicArray_int_set(cutils_cdar_DynamicArray_int*,size_t,size_t,int*);
extern size_t cutils_cdar_DynamicArray_int_pop(cutils_cdar_DynamicArray_int*,size_t,size_t,int*);
extern size_t cutils_cdar_DynamicArray_int_sub(cutils_cdar_DynamicArray_int*,size_t,size_t,int*);
extern int cutils_cdar_DynamicArray_int_get(cutils_cdar_DynamicArray_int*,size_t);
extern bool cutils_cdar_DynamicArray_int_find(cutils_cdar_DynamicArray_int*,const int*,size_t*);
extern size_t cutils_cdar_DynamicArray_int_findall(cutils_cdar_DynamicArray_int*,const int*,size_t*);
extern void(*cutils_cdar_DynamicArray_int_del)(cutils_cdar_DynamicArray_int*);
extern size_t(*cutils_cdar_DynamicArray_int_len)(cutils_cdar_DynamicArray_int*);
extern size_t(*cutils_cdar_DynamicArray_int_size)(cutils_cdar_DynamicArray_int*);
extern bool(*cutils_cdar_DynamicArray_int_resize)(cutils_cdar_DynamicArray_int*,size_t);
extern bool(*cutils_cdar_DynamicArray_int_swap)(cutils_cdar_DynamicArray_int*,size_t,size_t,size_t);
extern bool(*cutils_cdar_DynamicArray_int_reverse)(cutils_cdar_DynamicArray_int*);
extern size_t(*cutils_cdar_DynamicArray_int_pull)(cutils_cdar_DynamicArray_int*,size_t,size_t);
extern void(*cutils_cdar_DynamicArray_int_truncate)(cutils_cdar_DynamicArray_int*,size_t);
extern void(*cutils_cdar_DynamicArray_int_clear)(cutils_cdar_DynamicArray_int*);
/*----------------------------------------------------------------------------*/
typedef struct {} cutils_cdar_DynamicArray_unsigned_int;
extern bool cutils_cdar_DynamicArray_unsigned_int_new(cutils_cdar_DynamicArray_unsigned_int**,size_t,unsigned int*);
extern unsigned int* cutils_cdar_DynamicArray_unsigned_int_data(cutils_cdar_DynamicArray_unsigned_int*,size_t*,size_t*);
extern unsigned int* cutils_cdar_DynamicArray_unsigned_int_raw(cutils_cdar_DynamicArray_unsigned_int*);
extern bool cutils_cdar_DynamicArray_unsigned_int_append(cutils_cdar_DynamicArray_unsigned_int*,size_t,unsigned int*);
extern bool cutils_cdar_DynamicArray_unsigned_int_push(cutils_cdar_DynamicArray_unsigned_int*,size_t,size_t,unsigned int*);
extern bool cutils_cdar_DynamicArray_unsigned_int_set(cutils_cdar_DynamicArray_unsigned_int*,size_t,size_t,unsigned int*);
extern size_t cutils_cdar_DynamicArray_unsigned_int_pop(cutils_cdar_DynamicArray_unsigned_int*,size_t,size_t,unsigned int*);
extern size_t cutils_cdar_DynamicArray_unsigned_int_sub(cutils_cdar_DynamicArray_unsigned_int*,size_t,size_t,unsigned int*);
extern unsigned int cutils_cdar_DynamicArray_unsigned_int_get(cutils_cdar_DynamicArray_unsigned_int*,size_t);
extern bool cutils_cdar_DynamicArray_unsigned_int_find(cutils_cdar_DynamicArray_unsigned_int*,const unsigned int*,size_t*);
extern size_t cutils_cdar_DynamicArray_unsigned_int_findall(cutils_cdar_DynamicArray_unsigned_int*,const unsigned int*,size_t*);
extern void(*cutils_cdar_DynamicArray_unsigned_int_del)(cutils_cdar_DynamicArray_unsigned_int*);
extern size_t(*cutils_cdar_DynamicArray_unsigned_int_len)(cutils_cdar_DynamicArray_unsigned_int*);
extern size_t(*cutils_cdar_DynamicArray_unsigned_int_size)(cutils_cdar_DynamicArray_unsigned_int*);
extern bool(*cutils_cdar_DynamicArray_unsigned_int_resize)(cutils_cdar_DynamicArray_unsigned_int*,size_t);
extern bool(*cutils_cdar_DynamicArray_unsigned_int_swap)(cutils_cdar_DynamicArray_unsigned_int*,size_t,size_t,size_t);
extern bool(*cutils_cdar_DynamicArray_unsigned_int_reverse)(cutils_cdar_DynamicArray_unsigned_int*);
extern size_t(*cutils_cdar_DynamicArray_unsigned_int_pull)(cutils_cdar_DynamicArray_unsigned_int*,size_t,size_t);
extern void(*cutils_cdar_DynamicArray_unsigned_int_truncate)(cutils_cdar_DynamicArray_unsigned_int*,size_t);
extern void(*cutils_cdar_DynamicArray_unsigned_int_clear)(cutils_cdar_DynamicArray_unsigned_int*);
/*----------------------------------------------------------------------------*/
typedef struct {} cutils_cdar_DynamicArray_long;
extern bool cutils_cdar_DynamicArray_long_new(cutils_cdar_DynamicArray_long**,size_t,long*);
extern long* cutils_cdar_DynamicArray_long_data(cutils_cdar_DynamicArray_long*,size_t*,size_t*);
extern long* cutils_cdar_DynamicArray_long_raw(cutils_cdar_DynamicArray_long*);
extern bool cutils_cdar_DynamicArray_long_append(cutils_cdar_DynamicArray_long*,size_t,long*);
extern bool cutils_cdar_DynamicArray_long_push(cutils_cdar_DynamicArray_long*,size_t,size_t,long*);
extern bool cutils_cdar_DynamicArray_long_set(cutils_cdar_DynamicArray_long*,size_t,size_t,long*);
extern size_t cutils_cdar_DynamicArray_long_pop(cutils_cdar_DynamicArray_long*,size_t,size_t,long*);
extern size_t cutils_cdar_DynamicArray_long_sub(cutils_cdar_DynamicArray_long*,size_t,size_t,long*);
extern long cutils_cdar_DynamicArray_long_get(cutils_cdar_DynamicArray_long*,size_t);
extern bool cutils_cdar_DynamicArray_long_find(cutils_cdar_DynamicArray_long*,const long*,size_t*);
extern size_t cutils_cdar_DynamicArray_long_findall(cutils_cdar_DynamicArray_long*,const long*,size_t*);
extern void(*cutils_cdar_DynamicArray_long_del)(cutils_cdar_DynamicArray_long*);
extern size_t(*cutils_cdar_DynamicArray_long_len)(cutils_cdar_DynamicArray_long*);
extern size_t(*cutils_cdar_DynamicArray_long_size)(cutils_cdar_DynamicArray_long*);
extern bool(*cutils_cdar_DynamicArray_long_resize)(cutils_cdar_DynamicArray_long*,size_t);
extern bool(*cutils_cdar_DynamicArray_long_swap)(cutils_cdar_DynamicArray_long*,size_t,size_t,size_t);
extern bool(*cutils_cdar_DynamicArray_long_reverse)(cutils_cdar_DynamicArray_long*);
extern size_t(*cutils_cdar_DynamicArray_long_pull)(cutils_cdar_DynamicArray_long*,size_t,size_t);
extern void(*cutils_cdar_DynamicArray_long_truncate)(cutils_cdar_DynamicArray_long*,size_t);
extern void(*cutils_cdar_DynamicArray_long_clear)(cutils_cdar_DynamicArray_long*);
/*----------------------------------------------------------------------------*/
typedef struct {} cutils_cdar_DynamicArray_unsigned_long;
extern bool cutils_cdar_DynamicArray_unsigned_long_new(cutils_cdar_DynamicArray_unsigned_long**,size_t,unsigned long*);
extern unsigned long* cutils_cdar_DynamicArray_unsigned_long_data(cutils_cdar_DynamicArray_unsigned_long*,size_t*,size_t*);
extern unsigned long* cutils_cdar_DynamicArray_unsigned_long_raw(cutils_cdar_DynamicArray_unsigned_long*);
extern bool cutils_cdar_DynamicArray_unsigned_long_append(cutils_cdar_DynamicArray_unsigned_long*,size_t,unsigned long*);
extern bool cutils_cdar_DynamicArray_unsigned_long_push(cutils_cdar_DynamicArray_unsigned_long*,size_t,size_t,unsigned long*);
extern bool cutils_cdar_DynamicArray_unsigned_long_set(cutils_cdar_DynamicArray_unsigned_long*,size_t,size_t,unsigned long*);
extern size_t cutils_cdar_DynamicArray_unsigned_long_pop(cutils_cdar_DynamicArray_unsigned_long*,size_t,size_t,unsigned long*);
extern size_t cutils_cdar_DynamicArray_unsigned_long_sub(cutils_cdar_DynamicArray_unsigned_long*,size_t,size_t,unsigned long*);
extern unsigned long cutils_cdar_DynamicArray_unsigned_long_get(cutils_cdar_DynamicArray_unsigned_long*,size_t);
extern bool cutils_cdar_DynamicArray_unsigned_long_find(cutils_cdar_DynamicArray_unsigned_long*,const unsigned long*,size_t*);
extern size_t cutils_cdar_DynamicArray_unsigned_long_findall(cutils_cdar_DynamicArray_unsigned_long*,const unsigned long*,size_t*);
extern void(*cutils_cdar_DynamicArray_unsigned_long_del)(cutils_cdar_DynamicArray_unsigned_long*);
extern size_t(*cutils_cdar_DynamicArray_unsigned_long_len)(cutils_cdar_DynamicArray_unsigned_long*);
extern size_t(*cutils_cdar_DynamicArray_unsigned_long_size)(cutils_cdar_DynamicArray_unsigned_long*);
extern bool(*cutils_cdar_DynamicArray_unsigned_long_resize)(cutils_cdar_DynamicArray_unsigned_long*,size_t);
extern bool(*cutils_cdar_DynamicArray_unsigned_long_swap)(cutils_cdar_DynamicArray_unsigned_long*,size_t,size_t,size_t);
extern bool(*cutils_cdar_DynamicArray_unsigned_long_reverse)(cutils_cdar_DynamicArray_unsigned_long*);
extern size_t(*cutils_cdar_DynamicArray_unsigned_long_pull)(cutils_cdar_DynamicArray_unsigned_long*,size_t,size_t);
extern void(*cutils_cdar_DynamicArray_unsigned_long_truncate)(cutils_cdar_DynamicArray_unsigned_long*,size_t);
extern void(*cutils_cdar_DynamicArray_unsigned_long_clear)(cutils_cdar_DynamicArray_unsigned_long*);
/*----------------------------------------------------------------------------*/
typedef struct {} cutils_cdar_DynamicArray_long_long;
extern bool cutils_cdar_DynamicArray_long_long_new(cutils_cdar_DynamicArray_long_long**,size_t,long long*);
extern long long* cutils_cdar_DynamicArray_long_long_data(cutils_cdar_DynamicArray_long_long*,size_t*,size_t*);
extern long long* cutils_cdar_DynamicArray_long_long_raw(cutils_cdar_DynamicArray_long_long*);
extern bool cutils_cdar_DynamicArray_long_long_append(cutils_cdar_DynamicArray_long_long*,size_t,long long*);
extern bool cutils_cdar_DynamicArray_long_long_push(cutils_cdar_DynamicArray_long_long*,size_t,size_t,long long*);
extern bool cutils_cdar_DynamicArray_long_long_set(cutils_cdar_DynamicArray_long_long*,size_t,size_t,long long*);
extern size_t cutils_cdar_DynamicArray_long_long_pop(cutils_cdar_DynamicArray_long_long*,size_t,size_t,long long*);
extern size_t cutils_cdar_DynamicArray_long_long_sub(cutils_cdar_DynamicArray_long_long*,size_t,size_t,long long*);
extern long long cutils_cdar_DynamicArray_long_long_get(cutils_cdar_DynamicArray_long_long*,size_t);
extern bool cutils_cdar_DynamicArray_long_long_find(cutils_cdar_DynamicArray_long_long*,const long long*,size_t*);
extern size_t cutils_cdar_DynamicArray_long_long_findall(cutils_cdar_DynamicArray_long_long*,const long long*,size_t*);
extern void(*cutils_cdar_DynamicArray_long_long_del)(cutils_cdar_DynamicArray_long_long*);
extern size_t(*cutils_cdar_DynamicArray_long_long_len)(cutils_cdar_DynamicArray_long_long*);
extern size_t(*cutils_cdar_DynamicArray_long_long_size)(cutils_cdar_DynamicArray_long_long*);
extern bool(*cutils_cdar_DynamicArray_long_long_resize)(cutils_cdar_DynamicArray_long_long*,size_t);
extern bool(*cutils_cdar_DynamicArray_long_long_swap)(cutils_cdar_DynamicArray_long_long*,size_t,size_t,size_t);
extern bool(*cutils_cdar_DynamicArray_long_long_reverse)(cutils_cdar_DynamicArray_long_long*);
extern size_t(*cutils_cdar_DynamicArray_long_long_pull)(cutils_cdar_DynamicArray_long_long*,size_t,size_t);
extern void(*cutils_cdar_DynamicArray_long_long_truncate)(cutils_cdar_DynamicArray_long_long*,size_t);
extern void(*cutils_cdar_DynamicArray_long_long_clear)(cutils_cdar_DynamicArray_long_long*);
/*----------------------------------------------------------------------------*/
typedef struct {} cutils_cdar_DynamicArray_unsigned_long_long;
extern bool cutils_cdar_DynamicArray_unsigned_long_long_new(cutils_cdar_DynamicArray_unsigned_long_long**,size_t,unsigned long long*);
extern unsigned long long* cutils_cdar_DynamicArray_unsigned_long_long_data(cutils_cdar_DynamicArray_unsigned_long_long*,size_t*,size_t*);
extern unsigned long long* cutils_cdar_DynamicArray_unsigned_long_long_raw(cutils_cdar_DynamicArray_unsigned_long_long*);
extern bool cutils_cdar_DynamicArray_unsigned_long_long_append(cutils_cdar_DynamicArray_unsigned_long_long*,size_t,unsigned long long*);
extern bool cutils_cdar_DynamicArray_unsigned_long_long_push(cutils_cdar_DynamicArray_unsigned_long_long*,size_t,size_t,unsigned long long*);
extern bool cutils_cdar_DynamicArray_unsigned_long_long_set(cutils_cdar_DynamicArray_unsigned_long_long*,size_t,size_t,unsigned long long*);
extern size_t cutils_cdar_DynamicArray_unsigned_long_long_pop(cutils_cdar_DynamicArray_unsigned_long_long*,size_t,size_t,unsigned long long*);
extern size_t cutils_cdar_DynamicArray_unsigned_long_long_sub(cutils_cdar_DynamicArray_unsigned_long_long*,size_t,size_t,unsigned long long*);
extern unsigned long long cutils_cdar_DynamicArray_unsigned_long_long_get(cutils_cdar_DynamicArray_unsigned_long_long*,size_t);
extern bool cutils_cdar_DynamicArray_unsigned_long_long_find(cutils_cdar_DynamicArray_unsigned_long_long*,const unsigned long long*,size_t*);
extern size_t cutils_cdar_DynamicArray_unsigned_long_long_findall(cutils_cdar_DynamicArray_unsigned_long_long*,const unsigned long long*,size_t*);
extern void(*cutils_cdar_DynamicArray_unsigned_long_long_del)(cutils_cdar_DynamicArray_unsigned_long_long*);
extern size_t(*cutils_cdar_DynamicArray_unsigned_long_long_len)(cutils_cdar_DynamicArray_unsigned_long_long*);
extern size_t(*cutils_cdar_DynamicArray_unsigned_long_long_size)(cutils_cdar_DynamicArray_unsigned_long_long*);
extern bool(*cutils_cdar_DynamicArray_unsigned_long_long_resize)(cutils_cdar_DynamicArray_unsigned_long_long*,size_t);
extern bool(*cutils_cdar_DynamicArray_unsigned_long_long_swap)(cutils_cdar_DynamicArray_unsigned_long_long*,size_t,size_t,size_t);
extern bool(*cutils_cdar_DynamicArray_unsigned_long_long_reverse)(cutils_cdar_DynamicArray_unsigned_long_long*);
extern size_t(*cutils_cdar_DynamicArray_unsigned_long_long_pull)(cutils_cdar_DynamicArray_unsigned_long_long*,size_t,size_t);
extern void(*cutils_cdar_DynamicArray_unsigned_long_long_truncate)(cutils_cdar_DynamicArray_unsigned_long_long*,size_t);
extern void(*cutils_cdar_DynamicArray_unsigned_long_long_clear)(cutils_cdar_DynamicArray_unsigned_long_long*);
/*----------------------------------------------------------------------------*/
typedef struct {} cutils_cdar_DynamicArray_float;
extern bool cutils_cdar_DynamicArray_float_new(cutils_cdar_DynamicArray_float**,size_t,float*);
extern float* cutils_cdar_DynamicArray_float_data(cutils_cdar_DynamicArray_float*,size_t*,size_t*);
extern float* cutils_cdar_DynamicArray_float_raw(cutils_cdar_DynamicArray_float*);
extern bool cutils_cdar_DynamicArray_float_append(cutils_cdar_DynamicArray_float*,size_t,float*);
extern bool cutils_cdar_DynamicArray_float_push(cutils_cdar_DynamicArray_float*,size_t,size_t,float*);
extern bool cutils_cdar_DynamicArray_float_set(cutils_cdar_DynamicArray_float*,size_t,size_t,float*);
extern size_t cutils_cdar_DynamicArray_float_pop(cutils_cdar_DynamicArray_float*,size_t,size_t,float*);
extern size_t cutils_cdar_DynamicArray_float_sub(cutils_cdar_DynamicArray_float*,size_t,size_t,float*);
extern float cutils_cdar_DynamicArray_float_get(cutils_cdar_DynamicArray_float*,size_t);
extern bool cutils_cdar_DynamicArray_float_find(cutils_cdar_DynamicArray_float*,const float*,size_t*);
extern size_t cutils_cdar_DynamicArray_float_findall(cutils_cdar_DynamicArray_float*,const float*,size_t*);
extern void(*cutils_cdar_DynamicArray_float_del)(cutils_cdar_DynamicArray_float*);
extern size_t(*cutils_cdar_DynamicArray_float_len)(cutils_cdar_DynamicArray_float*);
extern size_t(*cutils_cdar_DynamicArray_float_size)(cutils_cdar_DynamicArray_float*);
extern bool(*cutils_cdar_DynamicArray_float_resize)(cutils_cdar_DynamicArray_float*,size_t);
extern bool(*cutils_cdar_DynamicArray_float_swap)(cutils_cdar_DynamicArray_float*,size_t,size_t,size_t);
extern bool(*cutils_cdar_DynamicArray_float_reverse)(cutils_cdar_DynamicArray_float*);
extern size_t(*cutils_cdar_DynamicArray_float_pull)(cutils_cdar_DynamicArray_float*,size_t,size_t);
extern void(*cutils_cdar_DynamicArray_float_truncate)(cutils_cdar_DynamicArray_float*,size_t);
extern void(*cutils_cdar_DynamicArray_float_clear)(cutils_cdar_DynamicArray_float*);
/*----------------------------------------------------------------------------*/
typedef struct {} cutils_cdar_DynamicArray_double;
extern bool cutils_cdar_DynamicArray_double_new(cutils_cdar_DynamicArray_double**,size_t,double*);
extern double* cutils_cdar_DynamicArray_double_data(cutils_cdar_DynamicArray_double*,size_t*,size_t*);
extern double* cutils_cdar_DynamicArray_double_raw(cutils_cdar_DynamicArray_double*);
extern bool cutils_cdar_DynamicArray_double_append(cutils_cdar_DynamicArray_double*,size_t,double*);
extern bool cutils_cdar_DynamicArray_double_push(cutils_cdar_DynamicArray_double*,size_t,size_t,double*);
extern bool cutils_cdar_DynamicArray_double_set(cutils_cdar_DynamicArray_double*,size_t,size_t,double*);
extern size_t cutils_cdar_DynamicArray_double_pop(cutils_cdar_DynamicArray_double*,size_t,size_t,double*);
extern size_t cutils_cdar_DynamicArray_double_sub(cutils_cdar_DynamicArray_double*,size_t,size_t,double*);
extern double cutils_cdar_DynamicArray_double_get(cutils_cdar_DynamicArray_double*,size_t);
extern bool cutils_cdar_DynamicArray_double_find(cutils_cdar_DynamicArray_double*,const double*,size_t*);
extern size_t cutils_cdar_DynamicArray_double_findall(cutils_cdar_DynamicArray_double*,const double*,size_t*);
extern void(*cutils_cdar_DynamicArray_double_del)(cutils_cdar_DynamicArray_double*);
extern size_t(*cutils_cdar_DynamicArray_double_len)(cutils_cdar_DynamicArray_double*);
extern size_t(*cutils_cdar_DynamicArray_double_size)(cutils_cdar_DynamicArray_double*);
extern bool(*cutils_cdar_DynamicArray_double_resize)(cutils_cdar_DynamicArray_double*,size_t);
extern bool(*cutils_cdar_DynamicArray_double_swap)(cutils_cdar_DynamicArray_double*,size_t,size_t,size_t);
extern bool(*cutils_cdar_DynamicArray_double_reverse)(cutils_cdar_DynamicArray_double*);
extern size_t(*cutils_cdar_DynamicArray_double_pull)(cutils_cdar_DynamicArray_double*,size_t,size_t);
extern void(*cutils_cdar_DynamicArray_double_truncate)(cutils_cdar_DynamicArray_double*,size_t);
extern void(*cutils_cdar_DynamicArray_double_clear)(cutils_cdar_DynamicArray_double*);
/*----------------------------------------------------------------------------*/
typedef struct {} cutils_cdar_DynamicArray_long_double;
extern bool cutils_cdar_DynamicArray_long_double_new(cutils_cdar_DynamicArray_long_double**,size_t,long double*);
extern long double* cutils_cdar_DynamicArray_long_double_data(cutils_cdar_DynamicArray_long_double*,size_t*,size_t*);
extern long double* cutils_cdar_DynamicArray_long_double_raw(cutils_cdar_DynamicArray_long_double*);
extern bool cutils_cdar_DynamicArray_long_double_append(cutils_cdar_DynamicArray_long_double*,size_t,long double*);
extern bool cutils_cdar_DynamicArray_long_double_push(cutils_cdar_DynamicArray_long_double*,size_t,size_t,long double*);
extern bool cutils_cdar_DynamicArray_long_double_set(cutils_cdar_DynamicArray_long_double*,size_t,size_t,long double*);
extern size_t cutils_cdar_DynamicArray_long_double_pop(cutils_cdar_DynamicArray_long_double*,size_t,size_t,long double*);
extern size_t cutils_cdar_DynamicArray_long_double_sub(cutils_cdar_DynamicArray_long_double*,size_t,size_t,long double*);
extern long double cutils_cdar_DynamicArray_long_double_get(cutils_cdar_DynamicArray_long_double*,size_t);
extern bool cutils_cdar_DynamicArray_long_double_find(cutils_cdar_DynamicArray_long_double*,const long double*,size_t*);
extern size_t cutils_cdar_DynamicArray_long_double_findall(cutils_cdar_DynamicArray_long_double*,const long double*,size_t*);
extern void(*cutils_cdar_DynamicArray_long_double_del)(cutils_cdar_DynamicArray_long_double*);
extern size_t(*cutils_cdar_DynamicArray_long_double_len)(cutils_cdar_DynamicArray_long_double*);
extern size_t(*cutils_cdar_DynamicArray_long_double_size)(cutils_cdar_DynamicArray_long_double*);
extern bool(*cutils_cdar_DynamicArray_long_double_resize)(cutils_cdar_DynamicArray_long_double*,size_t);
extern bool(*cutils_cdar_DynamicArray_long_double_swap)(cutils_cdar_DynamicArray_long_double*,size_t,size_t,size_t);
extern bool(*cutils_cdar_DynamicArray_long_double_reverse)(cutils_cdar_DynamicArray_long_double*);
extern size_t(*cutils_cdar_DynamicArray_long_double_pull)(cutils_cdar_DynamicArray_long_double*,size_t,size_t);
extern void(*cutils_cdar_DynamicArray_long_double_truncate)(cutils_cdar_DynamicArray_long_double*,size_t);
extern void(*cutils_cdar_DynamicArray_long_double_clear)(cutils_cdar_DynamicArray_long_double*);
/*----------------------------------------------------------------------------*/
typedef struct {} cutils_cdar_DynamicArray_bool;
extern bool cutils_cdar_DynamicArray_bool_new(cutils_cdar_DynamicArray_bool**,size_t,bool*);
extern bool* cutils_cdar_DynamicArray_bool_data(cutils_cdar_DynamicArray_bool*,size_t*,size_t*);
extern bool* cutils_cdar_DynamicArray_bool_raw(cutils_cdar_DynamicArray_bool*);
extern bool cutils_cdar_DynamicArray_bool_append(cutils_cdar_DynamicArray_bool*,size_t,bool*);
extern bool cutils_cdar_DynamicArray_bool_push(cutils_cdar_DynamicArray_bool*,size_t,size_t,bool*);
extern bool cutils_cdar_DynamicArray_bool_set(cutils_cdar_DynamicArray_bool*,size_t,size_t,bool*);
extern size_t cutils_cdar_DynamicArray_bool_pop(cutils_cdar_DynamicArray_bool*,size_t,size_t,bool*);
extern size_t cutils_cdar_DynamicArray_bool_sub(cutils_cdar_DynamicArray_bool*,size_t,size_t,bool*);
extern bool cutils_cdar_DynamicArray_bool_get(cutils_cdar_DynamicArray_bool*,size_t);
extern bool cutils_cdar_DynamicArray_bool_find(cutils_cdar_DynamicArray_bool*,const bool*,size_t*);
extern size_t cutils_cdar_DynamicArray_bool_findall(cutils_cdar_DynamicArray_bool*,const bool*,size_t*);
extern void(*cutils_cdar_DynamicArray_bool_del)(cutils_cdar_DynamicArray_bool*);
extern size_t(*cutils_cdar_DynamicArray_bool_len)(cutils_cdar_DynamicArray_bool*);
extern size_t(*cutils_cdar_DynamicArray_bool_size)(cutils_cdar_DynamicArray_bool*);
extern bool(*cutils_cdar_DynamicArray_bool_resize)(cutils_cdar_DynamicArray_bool*,size_t);
extern bool(*cutils_cdar_DynamicArray_bool_swap)(cutils_cdar_DynamicArray_bool*,size_t,size_t,size_t);
extern bool(*cutils_cdar_DynamicArray_bool_reverse)(cutils_cdar_DynamicArray_bool*);
extern size_t(*cutils_cdar_DynamicArray_bool_pull)(cutils_cdar_DynamicArray_bool*,size_t,size_t);
extern void(*cutils_cdar_DynamicArray_bool_truncate)(cutils_cdar_DynamicArray_bool*,size_t);
extern void(*cutils_cdar_DynamicArray_bool_clear)(cutils_cdar_DynamicArray_bool*);
/*----------------------------------------------------------------------------*/
typedef struct {} cutils_cdar_DynamicArray_size_t;
extern bool cutils_cdar_DynamicArray_size_t_new(cutils_cdar_DynamicArray_size_t**,size_t,size_t*);
extern size_t* cutils_cdar_DynamicArray_size_t_data(cutils_cdar_DynamicArray_size_t*,size_t*,size_t*);
extern size_t* cutils_cdar_DynamicArray_size_t_raw(cutils_cdar_DynamicArray_size_t*);
extern bool cutils_cdar_DynamicArray_size_t_append(cutils_cdar_DynamicArray_size_t*,size_t,size_t*);
extern bool cutils_cdar_DynamicArray_size_t_push(cutils_cdar_DynamicArray_size_t*,size_t,size_t,size_t*);
extern bool cutils_cdar_DynamicArray_size_t_set(cutils_cdar_DynamicArray_size_t*,size_t,size_t,size_t*);
extern size_t cutils_cdar_DynamicArray_size_t_pop(cutils_cdar_DynamicArray_size_t*,size_t,size_t,size_t*);
extern size_t cutils_cdar_DynamicArray_size_t_sub(cutils_cdar_DynamicArray_size_t*,size_t,size_t,size_t*);
extern size_t cutils_cdar_DynamicArray_size_t_get(cutils_cdar_DynamicArray_size_t*,size_t);
extern bool cutils_cdar_DynamicArray_size_t_find(cutils_cdar_DynamicArray_size_t*,const size_t*,size_t*);
extern size_t cutils_cdar_DynamicArray_size_t_findall(cutils_cdar_DynamicArray_size_t*,const size_t*,size_t*);
extern void(*cutils_cdar_DynamicArray_size_t_del)(cutils_cdar_DynamicArray_size_t*);
extern size_t(*cutils_cdar_DynamicArray_size_t_len)(cutils_cdar_DynamicArray_size_t*);
extern size_t(*cutils_cdar_DynamicArray_size_t_size)(cutils_cdar_DynamicArray_size_t*);
extern bool(*cutils_cdar_DynamicArray_size_t_resize)(cutils_cdar_DynamicArray_size_t*,size_t);
extern bool(*cutils_cdar_DynamicArray_size_t_swap)(cutils_cdar_DynamicArray_size_t*,size_t,size_t,size_t);
extern bool(*cutils_cdar_DynamicArray_size_t_reverse)(cutils_cdar_DynamicArray_size_t*);
extern size_t(*cutils_cdar_DynamicArray_size_t_pull)(cutils_cdar_DynamicArray_size_t*,size_t,size_t);
extern void(*cutils_cdar_DynamicArray_size_t_truncate)(cutils_cdar_DynamicArray_size_t*,size_t);
extern void(*cutils_cdar_DynamicArray_size_t_clear)(cutils_cdar_DynamicArray_size_t*);
/*----------------------------------------------------------------------------*/
typedef struct {} cutils_cdar_DynamicArray_ptrdiff_t;
extern bool cutils_cdar_DynamicArray_ptrdiff_t_new(cutils_cdar_DynamicArray_ptrdiff_t**,size_t,ptrdiff_t*);
extern ptrdiff_t* cutils_cdar_DynamicArray_ptrdiff_t_data(cutils_cdar_DynamicArray_ptrdiff_t*,size_t*,size_t*);
extern ptrdiff_t* cutils_cdar_DynamicArray_ptrdiff_t_raw(cutils_cdar_DynamicArray_ptrdiff_t*);
extern bool cutils_cdar_DynamicArray_ptrdiff_t_append(cutils_cdar_DynamicArray_ptrdiff_t*,size_t,ptrdiff_t*);
extern bool cutils_cdar_DynamicArray_ptrdiff_t_push(cutils_cdar_DynamicArray_ptrdiff_t*,size_t,size_t,ptrdiff_t*);
extern bool cutils_cdar_DynamicArray_ptrdiff_t_set(cutils_cdar_DynamicArray_ptrdiff_t*,size_t,size_t,ptrdiff_t*);
extern size_t cutils_cdar_DynamicArray_ptrdiff_t_pop(cutils_cdar_DynamicArray_ptrdiff_t*,size_t,size_t,ptrdiff_t*);
extern size_t cutils_cdar_DynamicArray_ptrdiff_t_sub(cutils_cdar_DynamicArray_ptrdiff_t*,size_t,size_t,ptrdiff_t*);
extern ptrdiff_t cutils_cdar_DynamicArray_ptrdiff_t_get(cutils_cdar_DynamicArray_ptrdiff_t*,size_t);
extern bool cutils_cdar_DynamicArray_ptrdiff_t_find(cutils_cdar_DynamicArray_ptrdiff_t*,const ptrdiff_t*,size_t*);
extern size_t cutils_cdar_DynamicArray_ptrdiff_t_findall(cutils_cdar_DynamicArray_ptrdiff_t*,const ptrdiff_t*,size_t*);
extern void(*cutils_cdar_DynamicArray_ptrdiff_t_del)(cutils_cdar_DynamicArray_ptrdiff_t*);
extern size_t(*cutils_cdar_DynamicArray_ptrdiff_t_len)(cutils_cdar_DynamicArray_ptrdiff_t*);
extern size_t(*cutils_cdar_DynamicArray_ptrdiff_t_size)(cutils_cdar_DynamicArray_ptrdiff_t*);
extern bool(*cutils_cdar_DynamicArray_ptrdiff_t_resize)(cutils_cdar_DynamicArray_ptrdiff_t*,size_t);
extern bool(*cutils_cdar_DynamicArray_ptrdiff_t_swap)(cutils_cdar_DynamicArray_ptrdiff_t*,size_t,size_t,size_t);
extern bool(*cutils_cdar_DynamicArray_ptrdiff_t_reverse)(cutils_cdar_DynamicArray_ptrdiff_t*);
extern size_t(*cutils_cdar_DynamicArray_ptrdiff_t_pull)(cutils_cdar_DynamicArray_ptrdiff_t*,size_t,size_t);
extern void(*cutils_cdar_DynamicArray_ptrdiff_t_truncate)(cutils_cdar_DynamicArray_ptrdiff_t*,size_t);
extern void(*cutils_cdar_DynamicArray_ptrdiff_t_clear)(cutils_cdar_DynamicArray_ptrdiff_t*);
#endif /* _C_DYNAMIC_ARRAY_H_2427147457128005_ */
