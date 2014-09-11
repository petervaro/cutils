/* INFO ************************************************************************
**                                                                            **
**                                   cutils                                   **
**                                   ======                                   **
**                                                                            **
**                     Modern and Lightweight C Utilities                     **
**                       Version: 0.8.96.219 (20140908)                       **
**                                                                            **
**                                File: cdar.h                                **
**                                                                            **
**   For more information about the project, visit <http://www.cutils.org>.   **
**                       Copyright (C) 2014 Peter Varo                        **
**                                                                            **
**  This program is free software: you can redistribute it and/or modify it   **
**   under the terms of the GNU General Public License as published by the    **
**       Free Software Foundation, either version 3 of the License, or        **
**                    (at your option) any later version.                     **
**                                                                            **
**    This program is distributed in the hope that it will be useful, but     **
**         WITHOUT ANY WARRANTY; without even the implied warranty of         **
**            MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.            **
**            See the GNU General Public License for more details.            **
**                                                                            **
**     You should have received a copy of the GNU General Public License      **
**     along with this program, most likely a file in the root directory,     **
**        called 'LICENSE'. If not, see <http://www.gnu.org/licenses>.        **
**                                                                            **
************************************************************************ INFO */

#ifndef _C_DYNAMIC_ARRAY_H_2427147457128005_
#define _C_DYNAMIC_ARRAY_H_2427147457128005_

#include <stddef.h>   /* ptrdiff_t */
#include <stdlib.h>   /* size_t */
#include <stdbool.h>  /* bool */

/*----------------------------------------------------------------------------*/
/* Shorthands for this source */
#undef _concat_underscore
#undef concat_underscore
#undef DYNAMIC_ARRAY
#undef METHOD
#undef SUPPORT
#undef SUPPORT_METHOD
#define _concat_underscore(token1, token2) token1##_##token2
#define concat_underscore(token1, token2) _concat_underscore(token1, token2)
#define DYNAMIC_ARRAY cutils_cdar_DynamicArray_void_ptr
#define METHOD(func)  concat_underscore(DYNAMIC_ARRAY, func)
#define SUPPORT(type) concat_underscore(DYNAMIC_ARRAY, type)
#define SUPPORT_METHOD(type, func) concat_underscore(DYNAMIC_ARRAY, type##_##func)

/*----------------------------------------------------------------------------*/
typedef struct {} DYNAMIC_ARRAY;
/*----------------------------------------------------------------------------*/
extern bool
METHOD(new)(DYNAMIC_ARRAY **dynarr,
            size_t item_size,
            size_t count,
            void *source);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
extern bool
METHOD(new_default3)(DYNAMIC_ARRAY **dynarr,
                     size_t item_size,
                     size_t count);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
extern bool
METHOD(new_default2)(DYNAMIC_ARRAY **dynarr,
                     size_t item_size);
/*----------------------------------------------------------------------------*/
extern void
METHOD(del)(DYNAMIC_ARRAY *dynarr);
/*----------------------------------------------------------------------------*/
extern void *
METHOD(data)(DYNAMIC_ARRAY *dynarr,
             size_t *size,
             size_t *count);
/*----------------------------------------------------------------------------*/
extern void *
METHOD(raw)(DYNAMIC_ARRAY *dynarr);
/*----------------------------------------------------------------------------*/
extern size_t
METHOD(len)(DYNAMIC_ARRAY *dynarr);
/*----------------------------------------------------------------------------*/
extern size_t
METHOD(size)(DYNAMIC_ARRAY *dynarr);
/*----------------------------------------------------------------------------*/
extern void
METHOD(clear)(DYNAMIC_ARRAY *dynarr);
/*----------------------------------------------------------------------------*/
extern bool
METHOD(resize)(DYNAMIC_ARRAY *dynarr,
               size_t count);
/*----------------------------------------------------------------------------*/
extern bool
METHOD(swap)(DYNAMIC_ARRAY *dynarr,
             size_t index1,
             size_t index2,
             size_t count);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
extern bool
METHOD(swap_default3)(DYNAMIC_ARRAY *dynarr,
                      size_t index1,
                      size_t index2);
/*----------------------------------------------------------------------------*/
extern bool
METHOD(reverse)(DYNAMIC_ARRAY *dynarr);
/*----------------------------------------------------------------------------*/
extern bool
METHOD(append)(DYNAMIC_ARRAY *dynarr,
               size_t count,
               void *source);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
extern bool
METHOD(append_default2)(DYNAMIC_ARRAY *dynarr,
                        void *source);
/*----------------------------------------------------------------------------*/
extern bool
METHOD(push)(DYNAMIC_ARRAY *dynarr,
             size_t index,
             size_t count,
             void *source);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
extern bool
METHOD(push_default3)(DYNAMIC_ARRAY *dynarr,
                      size_t index,
                      void *source);
/*----------------------------------------------------------------------------*/
extern size_t
METHOD(pull)(DYNAMIC_ARRAY *dynarr,
             size_t index,
             size_t count);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
extern size_t
METHOD(pull_default2)(DYNAMIC_ARRAY *dynarr,
                      size_t index);
/*----------------------------------------------------------------------------*/
extern size_t
METHOD(pop)(DYNAMIC_ARRAY *dynarr,
            size_t index,
            size_t count,
            void *destination);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
extern size_t
METHOD(pop_default3)(DYNAMIC_ARRAY *dynarr,
                     size_t index,
                     void *destination);
/*----------------------------------------------------------------------------*/
extern size_t
METHOD(sub)(DYNAMIC_ARRAY *dynarr,
            size_t index,
            size_t count,
            void *destination);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
extern size_t
METHOD(sub_default3)(DYNAMIC_ARRAY *dynarr,
                     size_t index,
                     void *destination);
/*----------------------------------------------------------------------------*/
extern void
METHOD(truncate)(DYNAMIC_ARRAY *dynarr,
                 size_t index);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
extern void
METHOD(truncate_default1)(DYNAMIC_ARRAY *dynarr);
/*----------------------------------------------------------------------------*/
extern bool
METHOD(set)(DYNAMIC_ARRAY *dynarr,
            size_t index,
            size_t count,
            void *source);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
extern bool
METHOD(set_default3)(DYNAMIC_ARRAY *dynarr,
                     size_t index,
                     void *source);
/*----------------------------------------------------------------------------*/
extern void *
METHOD(get)(DYNAMIC_ARRAY *dynarr,
            size_t index);
/*----------------------------------------------------------------------------*/
extern bool
METHOD(find)(DYNAMIC_ARRAY *dynarr,
             bool (*compare)(const void*, const void*, size_t),
             const void *item,
             size_t *index);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
extern bool
METHOD(find_default3)(DYNAMIC_ARRAY *dynarr,
                      const void *item,
                      size_t *index);
/*----------------------------------------------------------------------------*/
extern size_t
METHOD(findall)(DYNAMIC_ARRAY *dynarr,
                bool (*compare)(const void*, const void*, size_t),
                const void *item,
                size_t *indices);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
extern size_t
METHOD(findall_default3)(DYNAMIC_ARRAY *dynarr,
                         const void *item,
                         size_t *index);
/*----------------------------------------------------------------------------*/
extern void
METHOD(sort)(DYNAMIC_ARRAY *dynarr,
             int (*compare)(const void*, const void*));
/*----------------------------------------------------------------------------*/
extern void
METHOD(sortsub)(DYNAMIC_ARRAY *dynarr,
                size_t index,
                size_t count,
                int (*compare)(const void*, const void*));
/*----------------------------------------------------------------------------*/
extern void
METHOD(map)(DYNAMIC_ARRAY *dynarr,
            size_t index,
            size_t count,
            void (*function)());
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
extern void
METHOD(map_default3)(DYNAMIC_ARRAY *dynarr,
                     size_t count,
                     void (*function)());
/*----------------------------------------------------------------------------*/
extern void
METHOD(print)(DYNAMIC_ARRAY *dynarr,
              FILE *stream,
              const char *sub_type,
              bool(*format)());
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
extern void
METHOD(print_default1)(DYNAMIC_ARRAY *dynarr);
/*----------------------------------------------------------------------------*/
extern bool
METHOD(format)(const void *item,
               char **buffer,
               size_t *buffer_size);
/*----------------------------------------------------------------------------*/
extern bool
METHOD(compare)(const void *item1,
                const void *item2,
                size_t item_size);

/*----------------------------------------------------------------------------*/
/* Undefine helper macros */
#undef _concat_underscore
#undef concat_underscore
#undef DYNAMIC_ARRAY
#undef METHOD
#undef SUPPORT
#undef SUPPORT_METHOD

/*----------------------------------------------------------------------------*/
typedef struct {} cutils_cdar_DynamicArray_char;
extern bool cutils_cdar_DynamicArray_char_new(cutils_cdar_DynamicArray_char**,size_t,char*);
extern void(*cutils_cdar_DynamicArray_char_del)(cutils_cdar_DynamicArray_char*);
extern char* cutils_cdar_DynamicArray_char_data(cutils_cdar_DynamicArray_char*,size_t*,size_t*);
extern size_t(*cutils_cdar_DynamicArray_char_len)(cutils_cdar_DynamicArray_char*);
extern size_t(*cutils_cdar_DynamicArray_char_size)(cutils_cdar_DynamicArray_char*);
extern char* cutils_cdar_DynamicArray_char_raw(cutils_cdar_DynamicArray_char*);
extern bool(*cutils_cdar_DynamicArray_char_resize)(cutils_cdar_DynamicArray_char*,size_t);
extern void(*cutils_cdar_DynamicArray_char_truncate)(cutils_cdar_DynamicArray_char*,size_t);
extern void(*cutils_cdar_DynamicArray_char_clear)(cutils_cdar_DynamicArray_char*);
extern bool(*cutils_cdar_DynamicArray_char_swap)(cutils_cdar_DynamicArray_char*,size_t,size_t,size_t);
extern bool(*cutils_cdar_DynamicArray_char_reverse)(cutils_cdar_DynamicArray_char*);
extern bool cutils_cdar_DynamicArray_char_append(cutils_cdar_DynamicArray_char*,size_t,char*);
extern bool cutils_cdar_DynamicArray_char_push(cutils_cdar_DynamicArray_char*,size_t,size_t,char*);
extern size_t(*cutils_cdar_DynamicArray_char_pull)(cutils_cdar_DynamicArray_char*,size_t,size_t);
extern bool cutils_cdar_DynamicArray_char_set(cutils_cdar_DynamicArray_char*,size_t,size_t,char*);
extern size_t cutils_cdar_DynamicArray_char_pop(cutils_cdar_DynamicArray_char*,size_t,size_t,char*);
extern char cutils_cdar_DynamicArray_char_get(cutils_cdar_DynamicArray_char*,size_t);
extern size_t cutils_cdar_DynamicArray_char_sub(cutils_cdar_DynamicArray_char*,size_t,size_t,char*);
extern void(*cutils_cdar_DynamicArray_char_map)(cutils_cdar_DynamicArray_char*,size_t,size_t,void(*)());
extern bool cutils_cdar_DynamicArray_char_find(cutils_cdar_DynamicArray_char*,bool(*)(const void*,const void*,size_t),char*,size_t*);
extern size_t cutils_cdar_DynamicArray_char_findall(cutils_cdar_DynamicArray_char*,bool(*)(const void*,const void*,size_t),char*,size_t*);
extern void(*cutils_cdar_DynamicArray_char_print)(cutils_cdar_DynamicArray_char*,FILE*,const char*,bool(*)());
extern bool cutils_cdar_DynamicArray_char_format(const char*,char **,size_t*);
extern bool cutils_cdar_DynamicArray_char_compare(const void*,const void*,size_t);
extern bool cutils_cdar_DynamicArray_char_new_default1(cutils_cdar_DynamicArray_char**);
extern bool cutils_cdar_DynamicArray_char_new_default2(cutils_cdar_DynamicArray_char**,size_t);
extern void cutils_cdar_DynamicArray_char_truncate_default1(cutils_cdar_DynamicArray_char*);
extern bool cutils_cdar_DynamicArray_char_swap_default3(cutils_cdar_DynamicArray_char*,size_t,size_t);
extern bool cutils_cdar_DynamicArray_char_append_default2(cutils_cdar_DynamicArray_char*,char*);
extern bool cutils_cdar_DynamicArray_char_push_default3(cutils_cdar_DynamicArray_char*,size_t,char*);
extern size_t cutils_cdar_DynamicArray_char_pull_default2(cutils_cdar_DynamicArray_char*,size_t);
extern bool cutils_cdar_DynamicArray_char_set_default3(cutils_cdar_DynamicArray_char*,size_t,char*);
extern size_t cutils_cdar_DynamicArray_char_pop_default3(cutils_cdar_DynamicArray_char*,size_t,char*);
extern size_t cutils_cdar_DynamicArray_char_sub_default3(cutils_cdar_DynamicArray_char*,size_t,char*);
extern void cutils_cdar_DynamicArray_char_map_default3(cutils_cdar_DynamicArray_char*,size_t,void(*)());
extern bool cutils_cdar_DynamicArray_char_find_default3(cutils_cdar_DynamicArray_char*,char*,size_t*);
extern size_t cutils_cdar_DynamicArray_char_findall_default3(cutils_cdar_DynamicArray_char*,char*,size_t*);
extern void cutils_cdar_DynamicArray_char_print_default1(cutils_cdar_DynamicArray_char*);
/*----------------------------------------------------------------------------*/
typedef struct {} cutils_cdar_DynamicArray_signed_char;
extern bool cutils_cdar_DynamicArray_signed_char_new(cutils_cdar_DynamicArray_signed_char**,size_t,signed char*);
extern void(*cutils_cdar_DynamicArray_signed_char_del)(cutils_cdar_DynamicArray_signed_char*);
extern signed char* cutils_cdar_DynamicArray_signed_char_data(cutils_cdar_DynamicArray_signed_char*,size_t*,size_t*);
extern size_t(*cutils_cdar_DynamicArray_signed_char_len)(cutils_cdar_DynamicArray_signed_char*);
extern size_t(*cutils_cdar_DynamicArray_signed_char_size)(cutils_cdar_DynamicArray_signed_char*);
extern signed char* cutils_cdar_DynamicArray_signed_char_raw(cutils_cdar_DynamicArray_signed_char*);
extern bool(*cutils_cdar_DynamicArray_signed_char_resize)(cutils_cdar_DynamicArray_signed_char*,size_t);
extern void(*cutils_cdar_DynamicArray_signed_char_truncate)(cutils_cdar_DynamicArray_signed_char*,size_t);
extern void(*cutils_cdar_DynamicArray_signed_char_clear)(cutils_cdar_DynamicArray_signed_char*);
extern bool(*cutils_cdar_DynamicArray_signed_char_swap)(cutils_cdar_DynamicArray_signed_char*,size_t,size_t,size_t);
extern bool(*cutils_cdar_DynamicArray_signed_char_reverse)(cutils_cdar_DynamicArray_signed_char*);
extern bool cutils_cdar_DynamicArray_signed_char_append(cutils_cdar_DynamicArray_signed_char*,size_t,signed char*);
extern bool cutils_cdar_DynamicArray_signed_char_push(cutils_cdar_DynamicArray_signed_char*,size_t,size_t,signed char*);
extern size_t(*cutils_cdar_DynamicArray_signed_char_pull)(cutils_cdar_DynamicArray_signed_char*,size_t,size_t);
extern bool cutils_cdar_DynamicArray_signed_char_set(cutils_cdar_DynamicArray_signed_char*,size_t,size_t,signed char*);
extern size_t cutils_cdar_DynamicArray_signed_char_pop(cutils_cdar_DynamicArray_signed_char*,size_t,size_t,signed char*);
extern signed char cutils_cdar_DynamicArray_signed_char_get(cutils_cdar_DynamicArray_signed_char*,size_t);
extern size_t cutils_cdar_DynamicArray_signed_char_sub(cutils_cdar_DynamicArray_signed_char*,size_t,size_t,signed char*);
extern void(*cutils_cdar_DynamicArray_signed_char_map)(cutils_cdar_DynamicArray_signed_char*,size_t,size_t,void(*)());
extern bool cutils_cdar_DynamicArray_signed_char_find(cutils_cdar_DynamicArray_signed_char*,bool(*)(const void*,const void*,size_t),signed char*,size_t*);
extern size_t cutils_cdar_DynamicArray_signed_char_findall(cutils_cdar_DynamicArray_signed_char*,bool(*)(const void*,const void*,size_t),signed char*,size_t*);
extern void(*cutils_cdar_DynamicArray_signed_char_print)(cutils_cdar_DynamicArray_signed_char*,FILE*,const char*,bool(*)());
extern bool cutils_cdar_DynamicArray_signed_char_format(const signed char*,char **,size_t*);
extern bool cutils_cdar_DynamicArray_signed_char_compare(const void*,const void*,size_t);
extern bool cutils_cdar_DynamicArray_signed_char_new_default1(cutils_cdar_DynamicArray_signed_char**);
extern bool cutils_cdar_DynamicArray_signed_char_new_default2(cutils_cdar_DynamicArray_signed_char**,size_t);
extern void cutils_cdar_DynamicArray_signed_char_truncate_default1(cutils_cdar_DynamicArray_signed_char*);
extern bool cutils_cdar_DynamicArray_signed_char_swap_default3(cutils_cdar_DynamicArray_signed_char*,size_t,size_t);
extern bool cutils_cdar_DynamicArray_signed_char_append_default2(cutils_cdar_DynamicArray_signed_char*,signed char*);
extern bool cutils_cdar_DynamicArray_signed_char_push_default3(cutils_cdar_DynamicArray_signed_char*,size_t,signed char*);
extern size_t cutils_cdar_DynamicArray_signed_char_pull_default2(cutils_cdar_DynamicArray_signed_char*,size_t);
extern bool cutils_cdar_DynamicArray_signed_char_set_default3(cutils_cdar_DynamicArray_signed_char*,size_t,signed char*);
extern size_t cutils_cdar_DynamicArray_signed_char_pop_default3(cutils_cdar_DynamicArray_signed_char*,size_t,signed char*);
extern size_t cutils_cdar_DynamicArray_signed_char_sub_default3(cutils_cdar_DynamicArray_signed_char*,size_t,signed char*);
extern void cutils_cdar_DynamicArray_signed_char_map_default3(cutils_cdar_DynamicArray_signed_char*,size_t,void(*)());
extern bool cutils_cdar_DynamicArray_signed_char_find_default3(cutils_cdar_DynamicArray_signed_char*,signed char*,size_t*);
extern size_t cutils_cdar_DynamicArray_signed_char_findall_default3(cutils_cdar_DynamicArray_signed_char*,signed char*,size_t*);
extern void cutils_cdar_DynamicArray_signed_char_print_default1(cutils_cdar_DynamicArray_signed_char*);
/*----------------------------------------------------------------------------*/
typedef struct {} cutils_cdar_DynamicArray_unsigned_char;
extern bool cutils_cdar_DynamicArray_unsigned_char_new(cutils_cdar_DynamicArray_unsigned_char**,size_t,unsigned char*);
extern void(*cutils_cdar_DynamicArray_unsigned_char_del)(cutils_cdar_DynamicArray_unsigned_char*);
extern unsigned char* cutils_cdar_DynamicArray_unsigned_char_data(cutils_cdar_DynamicArray_unsigned_char*,size_t*,size_t*);
extern size_t(*cutils_cdar_DynamicArray_unsigned_char_len)(cutils_cdar_DynamicArray_unsigned_char*);
extern size_t(*cutils_cdar_DynamicArray_unsigned_char_size)(cutils_cdar_DynamicArray_unsigned_char*);
extern unsigned char* cutils_cdar_DynamicArray_unsigned_char_raw(cutils_cdar_DynamicArray_unsigned_char*);
extern bool(*cutils_cdar_DynamicArray_unsigned_char_resize)(cutils_cdar_DynamicArray_unsigned_char*,size_t);
extern void(*cutils_cdar_DynamicArray_unsigned_char_truncate)(cutils_cdar_DynamicArray_unsigned_char*,size_t);
extern void(*cutils_cdar_DynamicArray_unsigned_char_clear)(cutils_cdar_DynamicArray_unsigned_char*);
extern bool(*cutils_cdar_DynamicArray_unsigned_char_swap)(cutils_cdar_DynamicArray_unsigned_char*,size_t,size_t,size_t);
extern bool(*cutils_cdar_DynamicArray_unsigned_char_reverse)(cutils_cdar_DynamicArray_unsigned_char*);
extern bool cutils_cdar_DynamicArray_unsigned_char_append(cutils_cdar_DynamicArray_unsigned_char*,size_t,unsigned char*);
extern bool cutils_cdar_DynamicArray_unsigned_char_push(cutils_cdar_DynamicArray_unsigned_char*,size_t,size_t,unsigned char*);
extern size_t(*cutils_cdar_DynamicArray_unsigned_char_pull)(cutils_cdar_DynamicArray_unsigned_char*,size_t,size_t);
extern bool cutils_cdar_DynamicArray_unsigned_char_set(cutils_cdar_DynamicArray_unsigned_char*,size_t,size_t,unsigned char*);
extern size_t cutils_cdar_DynamicArray_unsigned_char_pop(cutils_cdar_DynamicArray_unsigned_char*,size_t,size_t,unsigned char*);
extern unsigned char cutils_cdar_DynamicArray_unsigned_char_get(cutils_cdar_DynamicArray_unsigned_char*,size_t);
extern size_t cutils_cdar_DynamicArray_unsigned_char_sub(cutils_cdar_DynamicArray_unsigned_char*,size_t,size_t,unsigned char*);
extern void(*cutils_cdar_DynamicArray_unsigned_char_map)(cutils_cdar_DynamicArray_unsigned_char*,size_t,size_t,void(*)());
extern bool cutils_cdar_DynamicArray_unsigned_char_find(cutils_cdar_DynamicArray_unsigned_char*,bool(*)(const void*,const void*,size_t),unsigned char*,size_t*);
extern size_t cutils_cdar_DynamicArray_unsigned_char_findall(cutils_cdar_DynamicArray_unsigned_char*,bool(*)(const void*,const void*,size_t),unsigned char*,size_t*);
extern void(*cutils_cdar_DynamicArray_unsigned_char_print)(cutils_cdar_DynamicArray_unsigned_char*,FILE*,const char*,bool(*)());
extern bool cutils_cdar_DynamicArray_unsigned_char_format(const unsigned char*,char **,size_t*);
extern bool cutils_cdar_DynamicArray_unsigned_char_compare(const void*,const void*,size_t);
extern bool cutils_cdar_DynamicArray_unsigned_char_new_default1(cutils_cdar_DynamicArray_unsigned_char**);
extern bool cutils_cdar_DynamicArray_unsigned_char_new_default2(cutils_cdar_DynamicArray_unsigned_char**,size_t);
extern void cutils_cdar_DynamicArray_unsigned_char_truncate_default1(cutils_cdar_DynamicArray_unsigned_char*);
extern bool cutils_cdar_DynamicArray_unsigned_char_swap_default3(cutils_cdar_DynamicArray_unsigned_char*,size_t,size_t);
extern bool cutils_cdar_DynamicArray_unsigned_char_append_default2(cutils_cdar_DynamicArray_unsigned_char*,unsigned char*);
extern bool cutils_cdar_DynamicArray_unsigned_char_push_default3(cutils_cdar_DynamicArray_unsigned_char*,size_t,unsigned char*);
extern size_t cutils_cdar_DynamicArray_unsigned_char_pull_default2(cutils_cdar_DynamicArray_unsigned_char*,size_t);
extern bool cutils_cdar_DynamicArray_unsigned_char_set_default3(cutils_cdar_DynamicArray_unsigned_char*,size_t,unsigned char*);
extern size_t cutils_cdar_DynamicArray_unsigned_char_pop_default3(cutils_cdar_DynamicArray_unsigned_char*,size_t,unsigned char*);
extern size_t cutils_cdar_DynamicArray_unsigned_char_sub_default3(cutils_cdar_DynamicArray_unsigned_char*,size_t,unsigned char*);
extern void cutils_cdar_DynamicArray_unsigned_char_map_default3(cutils_cdar_DynamicArray_unsigned_char*,size_t,void(*)());
extern bool cutils_cdar_DynamicArray_unsigned_char_find_default3(cutils_cdar_DynamicArray_unsigned_char*,unsigned char*,size_t*);
extern size_t cutils_cdar_DynamicArray_unsigned_char_findall_default3(cutils_cdar_DynamicArray_unsigned_char*,unsigned char*,size_t*);
extern void cutils_cdar_DynamicArray_unsigned_char_print_default1(cutils_cdar_DynamicArray_unsigned_char*);
/*----------------------------------------------------------------------------*/
typedef struct {} cutils_cdar_DynamicArray_char_ptr;
extern bool cutils_cdar_DynamicArray_char_ptr_new(cutils_cdar_DynamicArray_char_ptr**,size_t,char**);
extern void(*cutils_cdar_DynamicArray_char_ptr_del)(cutils_cdar_DynamicArray_char_ptr*);
extern char** cutils_cdar_DynamicArray_char_ptr_data(cutils_cdar_DynamicArray_char_ptr*,size_t*,size_t*);
extern size_t(*cutils_cdar_DynamicArray_char_ptr_len)(cutils_cdar_DynamicArray_char_ptr*);
extern size_t(*cutils_cdar_DynamicArray_char_ptr_size)(cutils_cdar_DynamicArray_char_ptr*);
extern char** cutils_cdar_DynamicArray_char_ptr_raw(cutils_cdar_DynamicArray_char_ptr*);
extern bool(*cutils_cdar_DynamicArray_char_ptr_resize)(cutils_cdar_DynamicArray_char_ptr*,size_t);
extern void(*cutils_cdar_DynamicArray_char_ptr_truncate)(cutils_cdar_DynamicArray_char_ptr*,size_t);
extern void(*cutils_cdar_DynamicArray_char_ptr_clear)(cutils_cdar_DynamicArray_char_ptr*);
extern bool(*cutils_cdar_DynamicArray_char_ptr_swap)(cutils_cdar_DynamicArray_char_ptr*,size_t,size_t,size_t);
extern bool(*cutils_cdar_DynamicArray_char_ptr_reverse)(cutils_cdar_DynamicArray_char_ptr*);
extern bool cutils_cdar_DynamicArray_char_ptr_append(cutils_cdar_DynamicArray_char_ptr*,size_t,char**);
extern bool cutils_cdar_DynamicArray_char_ptr_push(cutils_cdar_DynamicArray_char_ptr*,size_t,size_t,char**);
extern size_t(*cutils_cdar_DynamicArray_char_ptr_pull)(cutils_cdar_DynamicArray_char_ptr*,size_t,size_t);
extern bool cutils_cdar_DynamicArray_char_ptr_set(cutils_cdar_DynamicArray_char_ptr*,size_t,size_t,char**);
extern size_t cutils_cdar_DynamicArray_char_ptr_pop(cutils_cdar_DynamicArray_char_ptr*,size_t,size_t,char**);
extern char* cutils_cdar_DynamicArray_char_ptr_get(cutils_cdar_DynamicArray_char_ptr*,size_t);
extern size_t cutils_cdar_DynamicArray_char_ptr_sub(cutils_cdar_DynamicArray_char_ptr*,size_t,size_t,char**);
extern void(*cutils_cdar_DynamicArray_char_ptr_map)(cutils_cdar_DynamicArray_char_ptr*,size_t,size_t,void(*)());
extern bool cutils_cdar_DynamicArray_char_ptr_find(cutils_cdar_DynamicArray_char_ptr*,bool(*)(const void*,const void*,size_t),char**,size_t*);
extern size_t cutils_cdar_DynamicArray_char_ptr_findall(cutils_cdar_DynamicArray_char_ptr*,bool(*)(const void*,const void*,size_t),char**,size_t*);
extern void(*cutils_cdar_DynamicArray_char_ptr_print)(cutils_cdar_DynamicArray_char_ptr*,FILE*,const char*,bool(*)());
extern bool cutils_cdar_DynamicArray_char_ptr_format(const char**,char **,size_t*);
extern bool cutils_cdar_DynamicArray_char_ptr_compare(const void*,const void*,size_t);
extern bool cutils_cdar_DynamicArray_char_ptr_new_default1(cutils_cdar_DynamicArray_char_ptr**);
extern bool cutils_cdar_DynamicArray_char_ptr_new_default2(cutils_cdar_DynamicArray_char_ptr**,size_t);
extern void cutils_cdar_DynamicArray_char_ptr_truncate_default1(cutils_cdar_DynamicArray_char_ptr*);
extern bool cutils_cdar_DynamicArray_char_ptr_swap_default3(cutils_cdar_DynamicArray_char_ptr*,size_t,size_t);
extern bool cutils_cdar_DynamicArray_char_ptr_append_default2(cutils_cdar_DynamicArray_char_ptr*,char**);
extern bool cutils_cdar_DynamicArray_char_ptr_push_default3(cutils_cdar_DynamicArray_char_ptr*,size_t,char**);
extern size_t cutils_cdar_DynamicArray_char_ptr_pull_default2(cutils_cdar_DynamicArray_char_ptr*,size_t);
extern bool cutils_cdar_DynamicArray_char_ptr_set_default3(cutils_cdar_DynamicArray_char_ptr*,size_t,char**);
extern size_t cutils_cdar_DynamicArray_char_ptr_pop_default3(cutils_cdar_DynamicArray_char_ptr*,size_t,char**);
extern size_t cutils_cdar_DynamicArray_char_ptr_sub_default3(cutils_cdar_DynamicArray_char_ptr*,size_t,char**);
extern void cutils_cdar_DynamicArray_char_ptr_map_default3(cutils_cdar_DynamicArray_char_ptr*,size_t,void(*)());
extern bool cutils_cdar_DynamicArray_char_ptr_find_default3(cutils_cdar_DynamicArray_char_ptr*,char**,size_t*);
extern size_t cutils_cdar_DynamicArray_char_ptr_findall_default3(cutils_cdar_DynamicArray_char_ptr*,char**,size_t*);
extern void cutils_cdar_DynamicArray_char_ptr_print_default1(cutils_cdar_DynamicArray_char_ptr*);
/*----------------------------------------------------------------------------*/
typedef struct {} cutils_cdar_DynamicArray_short;
extern bool cutils_cdar_DynamicArray_short_new(cutils_cdar_DynamicArray_short**,size_t,short*);
extern void(*cutils_cdar_DynamicArray_short_del)(cutils_cdar_DynamicArray_short*);
extern short* cutils_cdar_DynamicArray_short_data(cutils_cdar_DynamicArray_short*,size_t*,size_t*);
extern size_t(*cutils_cdar_DynamicArray_short_len)(cutils_cdar_DynamicArray_short*);
extern size_t(*cutils_cdar_DynamicArray_short_size)(cutils_cdar_DynamicArray_short*);
extern short* cutils_cdar_DynamicArray_short_raw(cutils_cdar_DynamicArray_short*);
extern bool(*cutils_cdar_DynamicArray_short_resize)(cutils_cdar_DynamicArray_short*,size_t);
extern void(*cutils_cdar_DynamicArray_short_truncate)(cutils_cdar_DynamicArray_short*,size_t);
extern void(*cutils_cdar_DynamicArray_short_clear)(cutils_cdar_DynamicArray_short*);
extern bool(*cutils_cdar_DynamicArray_short_swap)(cutils_cdar_DynamicArray_short*,size_t,size_t,size_t);
extern bool(*cutils_cdar_DynamicArray_short_reverse)(cutils_cdar_DynamicArray_short*);
extern bool cutils_cdar_DynamicArray_short_append(cutils_cdar_DynamicArray_short*,size_t,short*);
extern bool cutils_cdar_DynamicArray_short_push(cutils_cdar_DynamicArray_short*,size_t,size_t,short*);
extern size_t(*cutils_cdar_DynamicArray_short_pull)(cutils_cdar_DynamicArray_short*,size_t,size_t);
extern bool cutils_cdar_DynamicArray_short_set(cutils_cdar_DynamicArray_short*,size_t,size_t,short*);
extern size_t cutils_cdar_DynamicArray_short_pop(cutils_cdar_DynamicArray_short*,size_t,size_t,short*);
extern short cutils_cdar_DynamicArray_short_get(cutils_cdar_DynamicArray_short*,size_t);
extern size_t cutils_cdar_DynamicArray_short_sub(cutils_cdar_DynamicArray_short*,size_t,size_t,short*);
extern void(*cutils_cdar_DynamicArray_short_map)(cutils_cdar_DynamicArray_short*,size_t,size_t,void(*)());
extern bool cutils_cdar_DynamicArray_short_find(cutils_cdar_DynamicArray_short*,bool(*)(const void*,const void*,size_t),short*,size_t*);
extern size_t cutils_cdar_DynamicArray_short_findall(cutils_cdar_DynamicArray_short*,bool(*)(const void*,const void*,size_t),short*,size_t*);
extern void(*cutils_cdar_DynamicArray_short_print)(cutils_cdar_DynamicArray_short*,FILE*,const char*,bool(*)());
extern bool cutils_cdar_DynamicArray_short_format(const short*,char **,size_t*);
extern bool cutils_cdar_DynamicArray_short_compare(const void*,const void*,size_t);
extern bool cutils_cdar_DynamicArray_short_new_default1(cutils_cdar_DynamicArray_short**);
extern bool cutils_cdar_DynamicArray_short_new_default2(cutils_cdar_DynamicArray_short**,size_t);
extern void cutils_cdar_DynamicArray_short_truncate_default1(cutils_cdar_DynamicArray_short*);
extern bool cutils_cdar_DynamicArray_short_swap_default3(cutils_cdar_DynamicArray_short*,size_t,size_t);
extern bool cutils_cdar_DynamicArray_short_append_default2(cutils_cdar_DynamicArray_short*,short*);
extern bool cutils_cdar_DynamicArray_short_push_default3(cutils_cdar_DynamicArray_short*,size_t,short*);
extern size_t cutils_cdar_DynamicArray_short_pull_default2(cutils_cdar_DynamicArray_short*,size_t);
extern bool cutils_cdar_DynamicArray_short_set_default3(cutils_cdar_DynamicArray_short*,size_t,short*);
extern size_t cutils_cdar_DynamicArray_short_pop_default3(cutils_cdar_DynamicArray_short*,size_t,short*);
extern size_t cutils_cdar_DynamicArray_short_sub_default3(cutils_cdar_DynamicArray_short*,size_t,short*);
extern void cutils_cdar_DynamicArray_short_map_default3(cutils_cdar_DynamicArray_short*,size_t,void(*)());
extern bool cutils_cdar_DynamicArray_short_find_default3(cutils_cdar_DynamicArray_short*,short*,size_t*);
extern size_t cutils_cdar_DynamicArray_short_findall_default3(cutils_cdar_DynamicArray_short*,short*,size_t*);
extern void cutils_cdar_DynamicArray_short_print_default1(cutils_cdar_DynamicArray_short*);
/*----------------------------------------------------------------------------*/
typedef struct {} cutils_cdar_DynamicArray_unsigned_short;
extern bool cutils_cdar_DynamicArray_unsigned_short_new(cutils_cdar_DynamicArray_unsigned_short**,size_t,unsigned short*);
extern void(*cutils_cdar_DynamicArray_unsigned_short_del)(cutils_cdar_DynamicArray_unsigned_short*);
extern unsigned short* cutils_cdar_DynamicArray_unsigned_short_data(cutils_cdar_DynamicArray_unsigned_short*,size_t*,size_t*);
extern size_t(*cutils_cdar_DynamicArray_unsigned_short_len)(cutils_cdar_DynamicArray_unsigned_short*);
extern size_t(*cutils_cdar_DynamicArray_unsigned_short_size)(cutils_cdar_DynamicArray_unsigned_short*);
extern unsigned short* cutils_cdar_DynamicArray_unsigned_short_raw(cutils_cdar_DynamicArray_unsigned_short*);
extern bool(*cutils_cdar_DynamicArray_unsigned_short_resize)(cutils_cdar_DynamicArray_unsigned_short*,size_t);
extern void(*cutils_cdar_DynamicArray_unsigned_short_truncate)(cutils_cdar_DynamicArray_unsigned_short*,size_t);
extern void(*cutils_cdar_DynamicArray_unsigned_short_clear)(cutils_cdar_DynamicArray_unsigned_short*);
extern bool(*cutils_cdar_DynamicArray_unsigned_short_swap)(cutils_cdar_DynamicArray_unsigned_short*,size_t,size_t,size_t);
extern bool(*cutils_cdar_DynamicArray_unsigned_short_reverse)(cutils_cdar_DynamicArray_unsigned_short*);
extern bool cutils_cdar_DynamicArray_unsigned_short_append(cutils_cdar_DynamicArray_unsigned_short*,size_t,unsigned short*);
extern bool cutils_cdar_DynamicArray_unsigned_short_push(cutils_cdar_DynamicArray_unsigned_short*,size_t,size_t,unsigned short*);
extern size_t(*cutils_cdar_DynamicArray_unsigned_short_pull)(cutils_cdar_DynamicArray_unsigned_short*,size_t,size_t);
extern bool cutils_cdar_DynamicArray_unsigned_short_set(cutils_cdar_DynamicArray_unsigned_short*,size_t,size_t,unsigned short*);
extern size_t cutils_cdar_DynamicArray_unsigned_short_pop(cutils_cdar_DynamicArray_unsigned_short*,size_t,size_t,unsigned short*);
extern unsigned short cutils_cdar_DynamicArray_unsigned_short_get(cutils_cdar_DynamicArray_unsigned_short*,size_t);
extern size_t cutils_cdar_DynamicArray_unsigned_short_sub(cutils_cdar_DynamicArray_unsigned_short*,size_t,size_t,unsigned short*);
extern void(*cutils_cdar_DynamicArray_unsigned_short_map)(cutils_cdar_DynamicArray_unsigned_short*,size_t,size_t,void(*)());
extern bool cutils_cdar_DynamicArray_unsigned_short_find(cutils_cdar_DynamicArray_unsigned_short*,bool(*)(const void*,const void*,size_t),unsigned short*,size_t*);
extern size_t cutils_cdar_DynamicArray_unsigned_short_findall(cutils_cdar_DynamicArray_unsigned_short*,bool(*)(const void*,const void*,size_t),unsigned short*,size_t*);
extern void(*cutils_cdar_DynamicArray_unsigned_short_print)(cutils_cdar_DynamicArray_unsigned_short*,FILE*,const char*,bool(*)());
extern bool cutils_cdar_DynamicArray_unsigned_short_format(const unsigned short*,char **,size_t*);
extern bool cutils_cdar_DynamicArray_unsigned_short_compare(const void*,const void*,size_t);
extern bool cutils_cdar_DynamicArray_unsigned_short_new_default1(cutils_cdar_DynamicArray_unsigned_short**);
extern bool cutils_cdar_DynamicArray_unsigned_short_new_default2(cutils_cdar_DynamicArray_unsigned_short**,size_t);
extern void cutils_cdar_DynamicArray_unsigned_short_truncate_default1(cutils_cdar_DynamicArray_unsigned_short*);
extern bool cutils_cdar_DynamicArray_unsigned_short_swap_default3(cutils_cdar_DynamicArray_unsigned_short*,size_t,size_t);
extern bool cutils_cdar_DynamicArray_unsigned_short_append_default2(cutils_cdar_DynamicArray_unsigned_short*,unsigned short*);
extern bool cutils_cdar_DynamicArray_unsigned_short_push_default3(cutils_cdar_DynamicArray_unsigned_short*,size_t,unsigned short*);
extern size_t cutils_cdar_DynamicArray_unsigned_short_pull_default2(cutils_cdar_DynamicArray_unsigned_short*,size_t);
extern bool cutils_cdar_DynamicArray_unsigned_short_set_default3(cutils_cdar_DynamicArray_unsigned_short*,size_t,unsigned short*);
extern size_t cutils_cdar_DynamicArray_unsigned_short_pop_default3(cutils_cdar_DynamicArray_unsigned_short*,size_t,unsigned short*);
extern size_t cutils_cdar_DynamicArray_unsigned_short_sub_default3(cutils_cdar_DynamicArray_unsigned_short*,size_t,unsigned short*);
extern void cutils_cdar_DynamicArray_unsigned_short_map_default3(cutils_cdar_DynamicArray_unsigned_short*,size_t,void(*)());
extern bool cutils_cdar_DynamicArray_unsigned_short_find_default3(cutils_cdar_DynamicArray_unsigned_short*,unsigned short*,size_t*);
extern size_t cutils_cdar_DynamicArray_unsigned_short_findall_default3(cutils_cdar_DynamicArray_unsigned_short*,unsigned short*,size_t*);
extern void cutils_cdar_DynamicArray_unsigned_short_print_default1(cutils_cdar_DynamicArray_unsigned_short*);
/*----------------------------------------------------------------------------*/
typedef struct {} cutils_cdar_DynamicArray_int;
extern bool cutils_cdar_DynamicArray_int_new(cutils_cdar_DynamicArray_int**,size_t,int*);
extern void(*cutils_cdar_DynamicArray_int_del)(cutils_cdar_DynamicArray_int*);
extern int* cutils_cdar_DynamicArray_int_data(cutils_cdar_DynamicArray_int*,size_t*,size_t*);
extern size_t(*cutils_cdar_DynamicArray_int_len)(cutils_cdar_DynamicArray_int*);
extern size_t(*cutils_cdar_DynamicArray_int_size)(cutils_cdar_DynamicArray_int*);
extern int* cutils_cdar_DynamicArray_int_raw(cutils_cdar_DynamicArray_int*);
extern bool(*cutils_cdar_DynamicArray_int_resize)(cutils_cdar_DynamicArray_int*,size_t);
extern void(*cutils_cdar_DynamicArray_int_truncate)(cutils_cdar_DynamicArray_int*,size_t);
extern void(*cutils_cdar_DynamicArray_int_clear)(cutils_cdar_DynamicArray_int*);
extern bool(*cutils_cdar_DynamicArray_int_swap)(cutils_cdar_DynamicArray_int*,size_t,size_t,size_t);
extern bool(*cutils_cdar_DynamicArray_int_reverse)(cutils_cdar_DynamicArray_int*);
extern bool cutils_cdar_DynamicArray_int_append(cutils_cdar_DynamicArray_int*,size_t,int*);
extern bool cutils_cdar_DynamicArray_int_push(cutils_cdar_DynamicArray_int*,size_t,size_t,int*);
extern size_t(*cutils_cdar_DynamicArray_int_pull)(cutils_cdar_DynamicArray_int*,size_t,size_t);
extern bool cutils_cdar_DynamicArray_int_set(cutils_cdar_DynamicArray_int*,size_t,size_t,int*);
extern size_t cutils_cdar_DynamicArray_int_pop(cutils_cdar_DynamicArray_int*,size_t,size_t,int*);
extern int cutils_cdar_DynamicArray_int_get(cutils_cdar_DynamicArray_int*,size_t);
extern size_t cutils_cdar_DynamicArray_int_sub(cutils_cdar_DynamicArray_int*,size_t,size_t,int*);
extern void(*cutils_cdar_DynamicArray_int_map)(cutils_cdar_DynamicArray_int*,size_t,size_t,void(*)());
extern bool cutils_cdar_DynamicArray_int_find(cutils_cdar_DynamicArray_int*,bool(*)(const void*,const void*,size_t),int*,size_t*);
extern size_t cutils_cdar_DynamicArray_int_findall(cutils_cdar_DynamicArray_int*,bool(*)(const void*,const void*,size_t),int*,size_t*);
extern void(*cutils_cdar_DynamicArray_int_print)(cutils_cdar_DynamicArray_int*,FILE*,const char*,bool(*)());
extern bool cutils_cdar_DynamicArray_int_format(const int*,char **,size_t*);
extern bool cutils_cdar_DynamicArray_int_compare(const void*,const void*,size_t);
extern bool cutils_cdar_DynamicArray_int_new_default1(cutils_cdar_DynamicArray_int**);
extern bool cutils_cdar_DynamicArray_int_new_default2(cutils_cdar_DynamicArray_int**,size_t);
extern void cutils_cdar_DynamicArray_int_truncate_default1(cutils_cdar_DynamicArray_int*);
extern bool cutils_cdar_DynamicArray_int_swap_default3(cutils_cdar_DynamicArray_int*,size_t,size_t);
extern bool cutils_cdar_DynamicArray_int_append_default2(cutils_cdar_DynamicArray_int*,int*);
extern bool cutils_cdar_DynamicArray_int_push_default3(cutils_cdar_DynamicArray_int*,size_t,int*);
extern size_t cutils_cdar_DynamicArray_int_pull_default2(cutils_cdar_DynamicArray_int*,size_t);
extern bool cutils_cdar_DynamicArray_int_set_default3(cutils_cdar_DynamicArray_int*,size_t,int*);
extern size_t cutils_cdar_DynamicArray_int_pop_default3(cutils_cdar_DynamicArray_int*,size_t,int*);
extern size_t cutils_cdar_DynamicArray_int_sub_default3(cutils_cdar_DynamicArray_int*,size_t,int*);
extern void cutils_cdar_DynamicArray_int_map_default3(cutils_cdar_DynamicArray_int*,size_t,void(*)());
extern bool cutils_cdar_DynamicArray_int_find_default3(cutils_cdar_DynamicArray_int*,int*,size_t*);
extern size_t cutils_cdar_DynamicArray_int_findall_default3(cutils_cdar_DynamicArray_int*,int*,size_t*);
extern void cutils_cdar_DynamicArray_int_print_default1(cutils_cdar_DynamicArray_int*);
/*----------------------------------------------------------------------------*/
typedef struct {} cutils_cdar_DynamicArray_unsigned_int;
extern bool cutils_cdar_DynamicArray_unsigned_int_new(cutils_cdar_DynamicArray_unsigned_int**,size_t,unsigned int*);
extern void(*cutils_cdar_DynamicArray_unsigned_int_del)(cutils_cdar_DynamicArray_unsigned_int*);
extern unsigned int* cutils_cdar_DynamicArray_unsigned_int_data(cutils_cdar_DynamicArray_unsigned_int*,size_t*,size_t*);
extern size_t(*cutils_cdar_DynamicArray_unsigned_int_len)(cutils_cdar_DynamicArray_unsigned_int*);
extern size_t(*cutils_cdar_DynamicArray_unsigned_int_size)(cutils_cdar_DynamicArray_unsigned_int*);
extern unsigned int* cutils_cdar_DynamicArray_unsigned_int_raw(cutils_cdar_DynamicArray_unsigned_int*);
extern bool(*cutils_cdar_DynamicArray_unsigned_int_resize)(cutils_cdar_DynamicArray_unsigned_int*,size_t);
extern void(*cutils_cdar_DynamicArray_unsigned_int_truncate)(cutils_cdar_DynamicArray_unsigned_int*,size_t);
extern void(*cutils_cdar_DynamicArray_unsigned_int_clear)(cutils_cdar_DynamicArray_unsigned_int*);
extern bool(*cutils_cdar_DynamicArray_unsigned_int_swap)(cutils_cdar_DynamicArray_unsigned_int*,size_t,size_t,size_t);
extern bool(*cutils_cdar_DynamicArray_unsigned_int_reverse)(cutils_cdar_DynamicArray_unsigned_int*);
extern bool cutils_cdar_DynamicArray_unsigned_int_append(cutils_cdar_DynamicArray_unsigned_int*,size_t,unsigned int*);
extern bool cutils_cdar_DynamicArray_unsigned_int_push(cutils_cdar_DynamicArray_unsigned_int*,size_t,size_t,unsigned int*);
extern size_t(*cutils_cdar_DynamicArray_unsigned_int_pull)(cutils_cdar_DynamicArray_unsigned_int*,size_t,size_t);
extern bool cutils_cdar_DynamicArray_unsigned_int_set(cutils_cdar_DynamicArray_unsigned_int*,size_t,size_t,unsigned int*);
extern size_t cutils_cdar_DynamicArray_unsigned_int_pop(cutils_cdar_DynamicArray_unsigned_int*,size_t,size_t,unsigned int*);
extern unsigned int cutils_cdar_DynamicArray_unsigned_int_get(cutils_cdar_DynamicArray_unsigned_int*,size_t);
extern size_t cutils_cdar_DynamicArray_unsigned_int_sub(cutils_cdar_DynamicArray_unsigned_int*,size_t,size_t,unsigned int*);
extern void(*cutils_cdar_DynamicArray_unsigned_int_map)(cutils_cdar_DynamicArray_unsigned_int*,size_t,size_t,void(*)());
extern bool cutils_cdar_DynamicArray_unsigned_int_find(cutils_cdar_DynamicArray_unsigned_int*,bool(*)(const void*,const void*,size_t),unsigned int*,size_t*);
extern size_t cutils_cdar_DynamicArray_unsigned_int_findall(cutils_cdar_DynamicArray_unsigned_int*,bool(*)(const void*,const void*,size_t),unsigned int*,size_t*);
extern void(*cutils_cdar_DynamicArray_unsigned_int_print)(cutils_cdar_DynamicArray_unsigned_int*,FILE*,const char*,bool(*)());
extern bool cutils_cdar_DynamicArray_unsigned_int_format(const unsigned int*,char **,size_t*);
extern bool cutils_cdar_DynamicArray_unsigned_int_compare(const void*,const void*,size_t);
extern bool cutils_cdar_DynamicArray_unsigned_int_new_default1(cutils_cdar_DynamicArray_unsigned_int**);
extern bool cutils_cdar_DynamicArray_unsigned_int_new_default2(cutils_cdar_DynamicArray_unsigned_int**,size_t);
extern void cutils_cdar_DynamicArray_unsigned_int_truncate_default1(cutils_cdar_DynamicArray_unsigned_int*);
extern bool cutils_cdar_DynamicArray_unsigned_int_swap_default3(cutils_cdar_DynamicArray_unsigned_int*,size_t,size_t);
extern bool cutils_cdar_DynamicArray_unsigned_int_append_default2(cutils_cdar_DynamicArray_unsigned_int*,unsigned int*);
extern bool cutils_cdar_DynamicArray_unsigned_int_push_default3(cutils_cdar_DynamicArray_unsigned_int*,size_t,unsigned int*);
extern size_t cutils_cdar_DynamicArray_unsigned_int_pull_default2(cutils_cdar_DynamicArray_unsigned_int*,size_t);
extern bool cutils_cdar_DynamicArray_unsigned_int_set_default3(cutils_cdar_DynamicArray_unsigned_int*,size_t,unsigned int*);
extern size_t cutils_cdar_DynamicArray_unsigned_int_pop_default3(cutils_cdar_DynamicArray_unsigned_int*,size_t,unsigned int*);
extern size_t cutils_cdar_DynamicArray_unsigned_int_sub_default3(cutils_cdar_DynamicArray_unsigned_int*,size_t,unsigned int*);
extern void cutils_cdar_DynamicArray_unsigned_int_map_default3(cutils_cdar_DynamicArray_unsigned_int*,size_t,void(*)());
extern bool cutils_cdar_DynamicArray_unsigned_int_find_default3(cutils_cdar_DynamicArray_unsigned_int*,unsigned int*,size_t*);
extern size_t cutils_cdar_DynamicArray_unsigned_int_findall_default3(cutils_cdar_DynamicArray_unsigned_int*,unsigned int*,size_t*);
extern void cutils_cdar_DynamicArray_unsigned_int_print_default1(cutils_cdar_DynamicArray_unsigned_int*);
/*----------------------------------------------------------------------------*/
typedef struct {} cutils_cdar_DynamicArray_long;
extern bool cutils_cdar_DynamicArray_long_new(cutils_cdar_DynamicArray_long**,size_t,long*);
extern void(*cutils_cdar_DynamicArray_long_del)(cutils_cdar_DynamicArray_long*);
extern long* cutils_cdar_DynamicArray_long_data(cutils_cdar_DynamicArray_long*,size_t*,size_t*);
extern size_t(*cutils_cdar_DynamicArray_long_len)(cutils_cdar_DynamicArray_long*);
extern size_t(*cutils_cdar_DynamicArray_long_size)(cutils_cdar_DynamicArray_long*);
extern long* cutils_cdar_DynamicArray_long_raw(cutils_cdar_DynamicArray_long*);
extern bool(*cutils_cdar_DynamicArray_long_resize)(cutils_cdar_DynamicArray_long*,size_t);
extern void(*cutils_cdar_DynamicArray_long_truncate)(cutils_cdar_DynamicArray_long*,size_t);
extern void(*cutils_cdar_DynamicArray_long_clear)(cutils_cdar_DynamicArray_long*);
extern bool(*cutils_cdar_DynamicArray_long_swap)(cutils_cdar_DynamicArray_long*,size_t,size_t,size_t);
extern bool(*cutils_cdar_DynamicArray_long_reverse)(cutils_cdar_DynamicArray_long*);
extern bool cutils_cdar_DynamicArray_long_append(cutils_cdar_DynamicArray_long*,size_t,long*);
extern bool cutils_cdar_DynamicArray_long_push(cutils_cdar_DynamicArray_long*,size_t,size_t,long*);
extern size_t(*cutils_cdar_DynamicArray_long_pull)(cutils_cdar_DynamicArray_long*,size_t,size_t);
extern bool cutils_cdar_DynamicArray_long_set(cutils_cdar_DynamicArray_long*,size_t,size_t,long*);
extern size_t cutils_cdar_DynamicArray_long_pop(cutils_cdar_DynamicArray_long*,size_t,size_t,long*);
extern long cutils_cdar_DynamicArray_long_get(cutils_cdar_DynamicArray_long*,size_t);
extern size_t cutils_cdar_DynamicArray_long_sub(cutils_cdar_DynamicArray_long*,size_t,size_t,long*);
extern void(*cutils_cdar_DynamicArray_long_map)(cutils_cdar_DynamicArray_long*,size_t,size_t,void(*)());
extern bool cutils_cdar_DynamicArray_long_find(cutils_cdar_DynamicArray_long*,bool(*)(const void*,const void*,size_t),long*,size_t*);
extern size_t cutils_cdar_DynamicArray_long_findall(cutils_cdar_DynamicArray_long*,bool(*)(const void*,const void*,size_t),long*,size_t*);
extern void(*cutils_cdar_DynamicArray_long_print)(cutils_cdar_DynamicArray_long*,FILE*,const char*,bool(*)());
extern bool cutils_cdar_DynamicArray_long_format(const long*,char **,size_t*);
extern bool cutils_cdar_DynamicArray_long_compare(const void*,const void*,size_t);
extern bool cutils_cdar_DynamicArray_long_new_default1(cutils_cdar_DynamicArray_long**);
extern bool cutils_cdar_DynamicArray_long_new_default2(cutils_cdar_DynamicArray_long**,size_t);
extern void cutils_cdar_DynamicArray_long_truncate_default1(cutils_cdar_DynamicArray_long*);
extern bool cutils_cdar_DynamicArray_long_swap_default3(cutils_cdar_DynamicArray_long*,size_t,size_t);
extern bool cutils_cdar_DynamicArray_long_append_default2(cutils_cdar_DynamicArray_long*,long*);
extern bool cutils_cdar_DynamicArray_long_push_default3(cutils_cdar_DynamicArray_long*,size_t,long*);
extern size_t cutils_cdar_DynamicArray_long_pull_default2(cutils_cdar_DynamicArray_long*,size_t);
extern bool cutils_cdar_DynamicArray_long_set_default3(cutils_cdar_DynamicArray_long*,size_t,long*);
extern size_t cutils_cdar_DynamicArray_long_pop_default3(cutils_cdar_DynamicArray_long*,size_t,long*);
extern size_t cutils_cdar_DynamicArray_long_sub_default3(cutils_cdar_DynamicArray_long*,size_t,long*);
extern void cutils_cdar_DynamicArray_long_map_default3(cutils_cdar_DynamicArray_long*,size_t,void(*)());
extern bool cutils_cdar_DynamicArray_long_find_default3(cutils_cdar_DynamicArray_long*,long*,size_t*);
extern size_t cutils_cdar_DynamicArray_long_findall_default3(cutils_cdar_DynamicArray_long*,long*,size_t*);
extern void cutils_cdar_DynamicArray_long_print_default1(cutils_cdar_DynamicArray_long*);
/*----------------------------------------------------------------------------*/
typedef struct {} cutils_cdar_DynamicArray_unsigned_long;
extern bool cutils_cdar_DynamicArray_unsigned_long_new(cutils_cdar_DynamicArray_unsigned_long**,size_t,unsigned long*);
extern void(*cutils_cdar_DynamicArray_unsigned_long_del)(cutils_cdar_DynamicArray_unsigned_long*);
extern unsigned long* cutils_cdar_DynamicArray_unsigned_long_data(cutils_cdar_DynamicArray_unsigned_long*,size_t*,size_t*);
extern size_t(*cutils_cdar_DynamicArray_unsigned_long_len)(cutils_cdar_DynamicArray_unsigned_long*);
extern size_t(*cutils_cdar_DynamicArray_unsigned_long_size)(cutils_cdar_DynamicArray_unsigned_long*);
extern unsigned long* cutils_cdar_DynamicArray_unsigned_long_raw(cutils_cdar_DynamicArray_unsigned_long*);
extern bool(*cutils_cdar_DynamicArray_unsigned_long_resize)(cutils_cdar_DynamicArray_unsigned_long*,size_t);
extern void(*cutils_cdar_DynamicArray_unsigned_long_truncate)(cutils_cdar_DynamicArray_unsigned_long*,size_t);
extern void(*cutils_cdar_DynamicArray_unsigned_long_clear)(cutils_cdar_DynamicArray_unsigned_long*);
extern bool(*cutils_cdar_DynamicArray_unsigned_long_swap)(cutils_cdar_DynamicArray_unsigned_long*,size_t,size_t,size_t);
extern bool(*cutils_cdar_DynamicArray_unsigned_long_reverse)(cutils_cdar_DynamicArray_unsigned_long*);
extern bool cutils_cdar_DynamicArray_unsigned_long_append(cutils_cdar_DynamicArray_unsigned_long*,size_t,unsigned long*);
extern bool cutils_cdar_DynamicArray_unsigned_long_push(cutils_cdar_DynamicArray_unsigned_long*,size_t,size_t,unsigned long*);
extern size_t(*cutils_cdar_DynamicArray_unsigned_long_pull)(cutils_cdar_DynamicArray_unsigned_long*,size_t,size_t);
extern bool cutils_cdar_DynamicArray_unsigned_long_set(cutils_cdar_DynamicArray_unsigned_long*,size_t,size_t,unsigned long*);
extern size_t cutils_cdar_DynamicArray_unsigned_long_pop(cutils_cdar_DynamicArray_unsigned_long*,size_t,size_t,unsigned long*);
extern unsigned long cutils_cdar_DynamicArray_unsigned_long_get(cutils_cdar_DynamicArray_unsigned_long*,size_t);
extern size_t cutils_cdar_DynamicArray_unsigned_long_sub(cutils_cdar_DynamicArray_unsigned_long*,size_t,size_t,unsigned long*);
extern void(*cutils_cdar_DynamicArray_unsigned_long_map)(cutils_cdar_DynamicArray_unsigned_long*,size_t,size_t,void(*)());
extern bool cutils_cdar_DynamicArray_unsigned_long_find(cutils_cdar_DynamicArray_unsigned_long*,bool(*)(const void*,const void*,size_t),unsigned long*,size_t*);
extern size_t cutils_cdar_DynamicArray_unsigned_long_findall(cutils_cdar_DynamicArray_unsigned_long*,bool(*)(const void*,const void*,size_t),unsigned long*,size_t*);
extern void(*cutils_cdar_DynamicArray_unsigned_long_print)(cutils_cdar_DynamicArray_unsigned_long*,FILE*,const char*,bool(*)());
extern bool cutils_cdar_DynamicArray_unsigned_long_format(const unsigned long*,char **,size_t*);
extern bool cutils_cdar_DynamicArray_unsigned_long_compare(const void*,const void*,size_t);
extern bool cutils_cdar_DynamicArray_unsigned_long_new_default1(cutils_cdar_DynamicArray_unsigned_long**);
extern bool cutils_cdar_DynamicArray_unsigned_long_new_default2(cutils_cdar_DynamicArray_unsigned_long**,size_t);
extern void cutils_cdar_DynamicArray_unsigned_long_truncate_default1(cutils_cdar_DynamicArray_unsigned_long*);
extern bool cutils_cdar_DynamicArray_unsigned_long_swap_default3(cutils_cdar_DynamicArray_unsigned_long*,size_t,size_t);
extern bool cutils_cdar_DynamicArray_unsigned_long_append_default2(cutils_cdar_DynamicArray_unsigned_long*,unsigned long*);
extern bool cutils_cdar_DynamicArray_unsigned_long_push_default3(cutils_cdar_DynamicArray_unsigned_long*,size_t,unsigned long*);
extern size_t cutils_cdar_DynamicArray_unsigned_long_pull_default2(cutils_cdar_DynamicArray_unsigned_long*,size_t);
extern bool cutils_cdar_DynamicArray_unsigned_long_set_default3(cutils_cdar_DynamicArray_unsigned_long*,size_t,unsigned long*);
extern size_t cutils_cdar_DynamicArray_unsigned_long_pop_default3(cutils_cdar_DynamicArray_unsigned_long*,size_t,unsigned long*);
extern size_t cutils_cdar_DynamicArray_unsigned_long_sub_default3(cutils_cdar_DynamicArray_unsigned_long*,size_t,unsigned long*);
extern void cutils_cdar_DynamicArray_unsigned_long_map_default3(cutils_cdar_DynamicArray_unsigned_long*,size_t,void(*)());
extern bool cutils_cdar_DynamicArray_unsigned_long_find_default3(cutils_cdar_DynamicArray_unsigned_long*,unsigned long*,size_t*);
extern size_t cutils_cdar_DynamicArray_unsigned_long_findall_default3(cutils_cdar_DynamicArray_unsigned_long*,unsigned long*,size_t*);
extern void cutils_cdar_DynamicArray_unsigned_long_print_default1(cutils_cdar_DynamicArray_unsigned_long*);
/*----------------------------------------------------------------------------*/
typedef struct {} cutils_cdar_DynamicArray_long_long;
extern bool cutils_cdar_DynamicArray_long_long_new(cutils_cdar_DynamicArray_long_long**,size_t,long long*);
extern void(*cutils_cdar_DynamicArray_long_long_del)(cutils_cdar_DynamicArray_long_long*);
extern long long* cutils_cdar_DynamicArray_long_long_data(cutils_cdar_DynamicArray_long_long*,size_t*,size_t*);
extern size_t(*cutils_cdar_DynamicArray_long_long_len)(cutils_cdar_DynamicArray_long_long*);
extern size_t(*cutils_cdar_DynamicArray_long_long_size)(cutils_cdar_DynamicArray_long_long*);
extern long long* cutils_cdar_DynamicArray_long_long_raw(cutils_cdar_DynamicArray_long_long*);
extern bool(*cutils_cdar_DynamicArray_long_long_resize)(cutils_cdar_DynamicArray_long_long*,size_t);
extern void(*cutils_cdar_DynamicArray_long_long_truncate)(cutils_cdar_DynamicArray_long_long*,size_t);
extern void(*cutils_cdar_DynamicArray_long_long_clear)(cutils_cdar_DynamicArray_long_long*);
extern bool(*cutils_cdar_DynamicArray_long_long_swap)(cutils_cdar_DynamicArray_long_long*,size_t,size_t,size_t);
extern bool(*cutils_cdar_DynamicArray_long_long_reverse)(cutils_cdar_DynamicArray_long_long*);
extern bool cutils_cdar_DynamicArray_long_long_append(cutils_cdar_DynamicArray_long_long*,size_t,long long*);
extern bool cutils_cdar_DynamicArray_long_long_push(cutils_cdar_DynamicArray_long_long*,size_t,size_t,long long*);
extern size_t(*cutils_cdar_DynamicArray_long_long_pull)(cutils_cdar_DynamicArray_long_long*,size_t,size_t);
extern bool cutils_cdar_DynamicArray_long_long_set(cutils_cdar_DynamicArray_long_long*,size_t,size_t,long long*);
extern size_t cutils_cdar_DynamicArray_long_long_pop(cutils_cdar_DynamicArray_long_long*,size_t,size_t,long long*);
extern long long cutils_cdar_DynamicArray_long_long_get(cutils_cdar_DynamicArray_long_long*,size_t);
extern size_t cutils_cdar_DynamicArray_long_long_sub(cutils_cdar_DynamicArray_long_long*,size_t,size_t,long long*);
extern void(*cutils_cdar_DynamicArray_long_long_map)(cutils_cdar_DynamicArray_long_long*,size_t,size_t,void(*)());
extern bool cutils_cdar_DynamicArray_long_long_find(cutils_cdar_DynamicArray_long_long*,bool(*)(const void*,const void*,size_t),long long*,size_t*);
extern size_t cutils_cdar_DynamicArray_long_long_findall(cutils_cdar_DynamicArray_long_long*,bool(*)(const void*,const void*,size_t),long long*,size_t*);
extern void(*cutils_cdar_DynamicArray_long_long_print)(cutils_cdar_DynamicArray_long_long*,FILE*,const char*,bool(*)());
extern bool cutils_cdar_DynamicArray_long_long_format(const long long*,char **,size_t*);
extern bool cutils_cdar_DynamicArray_long_long_compare(const void*,const void*,size_t);
extern bool cutils_cdar_DynamicArray_long_long_new_default1(cutils_cdar_DynamicArray_long_long**);
extern bool cutils_cdar_DynamicArray_long_long_new_default2(cutils_cdar_DynamicArray_long_long**,size_t);
extern void cutils_cdar_DynamicArray_long_long_truncate_default1(cutils_cdar_DynamicArray_long_long*);
extern bool cutils_cdar_DynamicArray_long_long_swap_default3(cutils_cdar_DynamicArray_long_long*,size_t,size_t);
extern bool cutils_cdar_DynamicArray_long_long_append_default2(cutils_cdar_DynamicArray_long_long*,long long*);
extern bool cutils_cdar_DynamicArray_long_long_push_default3(cutils_cdar_DynamicArray_long_long*,size_t,long long*);
extern size_t cutils_cdar_DynamicArray_long_long_pull_default2(cutils_cdar_DynamicArray_long_long*,size_t);
extern bool cutils_cdar_DynamicArray_long_long_set_default3(cutils_cdar_DynamicArray_long_long*,size_t,long long*);
extern size_t cutils_cdar_DynamicArray_long_long_pop_default3(cutils_cdar_DynamicArray_long_long*,size_t,long long*);
extern size_t cutils_cdar_DynamicArray_long_long_sub_default3(cutils_cdar_DynamicArray_long_long*,size_t,long long*);
extern void cutils_cdar_DynamicArray_long_long_map_default3(cutils_cdar_DynamicArray_long_long*,size_t,void(*)());
extern bool cutils_cdar_DynamicArray_long_long_find_default3(cutils_cdar_DynamicArray_long_long*,long long*,size_t*);
extern size_t cutils_cdar_DynamicArray_long_long_findall_default3(cutils_cdar_DynamicArray_long_long*,long long*,size_t*);
extern void cutils_cdar_DynamicArray_long_long_print_default1(cutils_cdar_DynamicArray_long_long*);
/*----------------------------------------------------------------------------*/
typedef struct {} cutils_cdar_DynamicArray_unsigned_long_long;
extern bool cutils_cdar_DynamicArray_unsigned_long_long_new(cutils_cdar_DynamicArray_unsigned_long_long**,size_t,unsigned long long*);
extern void(*cutils_cdar_DynamicArray_unsigned_long_long_del)(cutils_cdar_DynamicArray_unsigned_long_long*);
extern unsigned long long* cutils_cdar_DynamicArray_unsigned_long_long_data(cutils_cdar_DynamicArray_unsigned_long_long*,size_t*,size_t*);
extern size_t(*cutils_cdar_DynamicArray_unsigned_long_long_len)(cutils_cdar_DynamicArray_unsigned_long_long*);
extern size_t(*cutils_cdar_DynamicArray_unsigned_long_long_size)(cutils_cdar_DynamicArray_unsigned_long_long*);
extern unsigned long long* cutils_cdar_DynamicArray_unsigned_long_long_raw(cutils_cdar_DynamicArray_unsigned_long_long*);
extern bool(*cutils_cdar_DynamicArray_unsigned_long_long_resize)(cutils_cdar_DynamicArray_unsigned_long_long*,size_t);
extern void(*cutils_cdar_DynamicArray_unsigned_long_long_truncate)(cutils_cdar_DynamicArray_unsigned_long_long*,size_t);
extern void(*cutils_cdar_DynamicArray_unsigned_long_long_clear)(cutils_cdar_DynamicArray_unsigned_long_long*);
extern bool(*cutils_cdar_DynamicArray_unsigned_long_long_swap)(cutils_cdar_DynamicArray_unsigned_long_long*,size_t,size_t,size_t);
extern bool(*cutils_cdar_DynamicArray_unsigned_long_long_reverse)(cutils_cdar_DynamicArray_unsigned_long_long*);
extern bool cutils_cdar_DynamicArray_unsigned_long_long_append(cutils_cdar_DynamicArray_unsigned_long_long*,size_t,unsigned long long*);
extern bool cutils_cdar_DynamicArray_unsigned_long_long_push(cutils_cdar_DynamicArray_unsigned_long_long*,size_t,size_t,unsigned long long*);
extern size_t(*cutils_cdar_DynamicArray_unsigned_long_long_pull)(cutils_cdar_DynamicArray_unsigned_long_long*,size_t,size_t);
extern bool cutils_cdar_DynamicArray_unsigned_long_long_set(cutils_cdar_DynamicArray_unsigned_long_long*,size_t,size_t,unsigned long long*);
extern size_t cutils_cdar_DynamicArray_unsigned_long_long_pop(cutils_cdar_DynamicArray_unsigned_long_long*,size_t,size_t,unsigned long long*);
extern unsigned long long cutils_cdar_DynamicArray_unsigned_long_long_get(cutils_cdar_DynamicArray_unsigned_long_long*,size_t);
extern size_t cutils_cdar_DynamicArray_unsigned_long_long_sub(cutils_cdar_DynamicArray_unsigned_long_long*,size_t,size_t,unsigned long long*);
extern void(*cutils_cdar_DynamicArray_unsigned_long_long_map)(cutils_cdar_DynamicArray_unsigned_long_long*,size_t,size_t,void(*)());
extern bool cutils_cdar_DynamicArray_unsigned_long_long_find(cutils_cdar_DynamicArray_unsigned_long_long*,bool(*)(const void*,const void*,size_t),unsigned long long*,size_t*);
extern size_t cutils_cdar_DynamicArray_unsigned_long_long_findall(cutils_cdar_DynamicArray_unsigned_long_long*,bool(*)(const void*,const void*,size_t),unsigned long long*,size_t*);
extern void(*cutils_cdar_DynamicArray_unsigned_long_long_print)(cutils_cdar_DynamicArray_unsigned_long_long*,FILE*,const char*,bool(*)());
extern bool cutils_cdar_DynamicArray_unsigned_long_long_format(const unsigned long long*,char **,size_t*);
extern bool cutils_cdar_DynamicArray_unsigned_long_long_compare(const void*,const void*,size_t);
extern bool cutils_cdar_DynamicArray_unsigned_long_long_new_default1(cutils_cdar_DynamicArray_unsigned_long_long**);
extern bool cutils_cdar_DynamicArray_unsigned_long_long_new_default2(cutils_cdar_DynamicArray_unsigned_long_long**,size_t);
extern void cutils_cdar_DynamicArray_unsigned_long_long_truncate_default1(cutils_cdar_DynamicArray_unsigned_long_long*);
extern bool cutils_cdar_DynamicArray_unsigned_long_long_swap_default3(cutils_cdar_DynamicArray_unsigned_long_long*,size_t,size_t);
extern bool cutils_cdar_DynamicArray_unsigned_long_long_append_default2(cutils_cdar_DynamicArray_unsigned_long_long*,unsigned long long*);
extern bool cutils_cdar_DynamicArray_unsigned_long_long_push_default3(cutils_cdar_DynamicArray_unsigned_long_long*,size_t,unsigned long long*);
extern size_t cutils_cdar_DynamicArray_unsigned_long_long_pull_default2(cutils_cdar_DynamicArray_unsigned_long_long*,size_t);
extern bool cutils_cdar_DynamicArray_unsigned_long_long_set_default3(cutils_cdar_DynamicArray_unsigned_long_long*,size_t,unsigned long long*);
extern size_t cutils_cdar_DynamicArray_unsigned_long_long_pop_default3(cutils_cdar_DynamicArray_unsigned_long_long*,size_t,unsigned long long*);
extern size_t cutils_cdar_DynamicArray_unsigned_long_long_sub_default3(cutils_cdar_DynamicArray_unsigned_long_long*,size_t,unsigned long long*);
extern void cutils_cdar_DynamicArray_unsigned_long_long_map_default3(cutils_cdar_DynamicArray_unsigned_long_long*,size_t,void(*)());
extern bool cutils_cdar_DynamicArray_unsigned_long_long_find_default3(cutils_cdar_DynamicArray_unsigned_long_long*,unsigned long long*,size_t*);
extern size_t cutils_cdar_DynamicArray_unsigned_long_long_findall_default3(cutils_cdar_DynamicArray_unsigned_long_long*,unsigned long long*,size_t*);
extern void cutils_cdar_DynamicArray_unsigned_long_long_print_default1(cutils_cdar_DynamicArray_unsigned_long_long*);
/*----------------------------------------------------------------------------*/
typedef struct {} cutils_cdar_DynamicArray_float;
extern bool cutils_cdar_DynamicArray_float_new(cutils_cdar_DynamicArray_float**,size_t,float*);
extern void(*cutils_cdar_DynamicArray_float_del)(cutils_cdar_DynamicArray_float*);
extern float* cutils_cdar_DynamicArray_float_data(cutils_cdar_DynamicArray_float*,size_t*,size_t*);
extern size_t(*cutils_cdar_DynamicArray_float_len)(cutils_cdar_DynamicArray_float*);
extern size_t(*cutils_cdar_DynamicArray_float_size)(cutils_cdar_DynamicArray_float*);
extern float* cutils_cdar_DynamicArray_float_raw(cutils_cdar_DynamicArray_float*);
extern bool(*cutils_cdar_DynamicArray_float_resize)(cutils_cdar_DynamicArray_float*,size_t);
extern void(*cutils_cdar_DynamicArray_float_truncate)(cutils_cdar_DynamicArray_float*,size_t);
extern void(*cutils_cdar_DynamicArray_float_clear)(cutils_cdar_DynamicArray_float*);
extern bool(*cutils_cdar_DynamicArray_float_swap)(cutils_cdar_DynamicArray_float*,size_t,size_t,size_t);
extern bool(*cutils_cdar_DynamicArray_float_reverse)(cutils_cdar_DynamicArray_float*);
extern bool cutils_cdar_DynamicArray_float_append(cutils_cdar_DynamicArray_float*,size_t,float*);
extern bool cutils_cdar_DynamicArray_float_push(cutils_cdar_DynamicArray_float*,size_t,size_t,float*);
extern size_t(*cutils_cdar_DynamicArray_float_pull)(cutils_cdar_DynamicArray_float*,size_t,size_t);
extern bool cutils_cdar_DynamicArray_float_set(cutils_cdar_DynamicArray_float*,size_t,size_t,float*);
extern size_t cutils_cdar_DynamicArray_float_pop(cutils_cdar_DynamicArray_float*,size_t,size_t,float*);
extern float cutils_cdar_DynamicArray_float_get(cutils_cdar_DynamicArray_float*,size_t);
extern size_t cutils_cdar_DynamicArray_float_sub(cutils_cdar_DynamicArray_float*,size_t,size_t,float*);
extern void(*cutils_cdar_DynamicArray_float_map)(cutils_cdar_DynamicArray_float*,size_t,size_t,void(*)());
extern bool cutils_cdar_DynamicArray_float_find(cutils_cdar_DynamicArray_float*,bool(*)(const void*,const void*,size_t),float*,size_t*);
extern size_t cutils_cdar_DynamicArray_float_findall(cutils_cdar_DynamicArray_float*,bool(*)(const void*,const void*,size_t),float*,size_t*);
extern void(*cutils_cdar_DynamicArray_float_print)(cutils_cdar_DynamicArray_float*,FILE*,const char*,bool(*)());
extern bool cutils_cdar_DynamicArray_float_format(const float*,char **,size_t*);
extern bool cutils_cdar_DynamicArray_float_compare(const void*,const void*,size_t);
extern bool cutils_cdar_DynamicArray_float_new_default1(cutils_cdar_DynamicArray_float**);
extern bool cutils_cdar_DynamicArray_float_new_default2(cutils_cdar_DynamicArray_float**,size_t);
extern void cutils_cdar_DynamicArray_float_truncate_default1(cutils_cdar_DynamicArray_float*);
extern bool cutils_cdar_DynamicArray_float_swap_default3(cutils_cdar_DynamicArray_float*,size_t,size_t);
extern bool cutils_cdar_DynamicArray_float_append_default2(cutils_cdar_DynamicArray_float*,float*);
extern bool cutils_cdar_DynamicArray_float_push_default3(cutils_cdar_DynamicArray_float*,size_t,float*);
extern size_t cutils_cdar_DynamicArray_float_pull_default2(cutils_cdar_DynamicArray_float*,size_t);
extern bool cutils_cdar_DynamicArray_float_set_default3(cutils_cdar_DynamicArray_float*,size_t,float*);
extern size_t cutils_cdar_DynamicArray_float_pop_default3(cutils_cdar_DynamicArray_float*,size_t,float*);
extern size_t cutils_cdar_DynamicArray_float_sub_default3(cutils_cdar_DynamicArray_float*,size_t,float*);
extern void cutils_cdar_DynamicArray_float_map_default3(cutils_cdar_DynamicArray_float*,size_t,void(*)());
extern bool cutils_cdar_DynamicArray_float_find_default3(cutils_cdar_DynamicArray_float*,float*,size_t*);
extern size_t cutils_cdar_DynamicArray_float_findall_default3(cutils_cdar_DynamicArray_float*,float*,size_t*);
extern void cutils_cdar_DynamicArray_float_print_default1(cutils_cdar_DynamicArray_float*);
/*----------------------------------------------------------------------------*/
typedef struct {} cutils_cdar_DynamicArray_double;
extern bool cutils_cdar_DynamicArray_double_new(cutils_cdar_DynamicArray_double**,size_t,double*);
extern void(*cutils_cdar_DynamicArray_double_del)(cutils_cdar_DynamicArray_double*);
extern double* cutils_cdar_DynamicArray_double_data(cutils_cdar_DynamicArray_double*,size_t*,size_t*);
extern size_t(*cutils_cdar_DynamicArray_double_len)(cutils_cdar_DynamicArray_double*);
extern size_t(*cutils_cdar_DynamicArray_double_size)(cutils_cdar_DynamicArray_double*);
extern double* cutils_cdar_DynamicArray_double_raw(cutils_cdar_DynamicArray_double*);
extern bool(*cutils_cdar_DynamicArray_double_resize)(cutils_cdar_DynamicArray_double*,size_t);
extern void(*cutils_cdar_DynamicArray_double_truncate)(cutils_cdar_DynamicArray_double*,size_t);
extern void(*cutils_cdar_DynamicArray_double_clear)(cutils_cdar_DynamicArray_double*);
extern bool(*cutils_cdar_DynamicArray_double_swap)(cutils_cdar_DynamicArray_double*,size_t,size_t,size_t);
extern bool(*cutils_cdar_DynamicArray_double_reverse)(cutils_cdar_DynamicArray_double*);
extern bool cutils_cdar_DynamicArray_double_append(cutils_cdar_DynamicArray_double*,size_t,double*);
extern bool cutils_cdar_DynamicArray_double_push(cutils_cdar_DynamicArray_double*,size_t,size_t,double*);
extern size_t(*cutils_cdar_DynamicArray_double_pull)(cutils_cdar_DynamicArray_double*,size_t,size_t);
extern bool cutils_cdar_DynamicArray_double_set(cutils_cdar_DynamicArray_double*,size_t,size_t,double*);
extern size_t cutils_cdar_DynamicArray_double_pop(cutils_cdar_DynamicArray_double*,size_t,size_t,double*);
extern double cutils_cdar_DynamicArray_double_get(cutils_cdar_DynamicArray_double*,size_t);
extern size_t cutils_cdar_DynamicArray_double_sub(cutils_cdar_DynamicArray_double*,size_t,size_t,double*);
extern void(*cutils_cdar_DynamicArray_double_map)(cutils_cdar_DynamicArray_double*,size_t,size_t,void(*)());
extern bool cutils_cdar_DynamicArray_double_find(cutils_cdar_DynamicArray_double*,bool(*)(const void*,const void*,size_t),double*,size_t*);
extern size_t cutils_cdar_DynamicArray_double_findall(cutils_cdar_DynamicArray_double*,bool(*)(const void*,const void*,size_t),double*,size_t*);
extern void(*cutils_cdar_DynamicArray_double_print)(cutils_cdar_DynamicArray_double*,FILE*,const char*,bool(*)());
extern bool cutils_cdar_DynamicArray_double_format(const double*,char **,size_t*);
extern bool cutils_cdar_DynamicArray_double_compare(const void*,const void*,size_t);
extern bool cutils_cdar_DynamicArray_double_new_default1(cutils_cdar_DynamicArray_double**);
extern bool cutils_cdar_DynamicArray_double_new_default2(cutils_cdar_DynamicArray_double**,size_t);
extern void cutils_cdar_DynamicArray_double_truncate_default1(cutils_cdar_DynamicArray_double*);
extern bool cutils_cdar_DynamicArray_double_swap_default3(cutils_cdar_DynamicArray_double*,size_t,size_t);
extern bool cutils_cdar_DynamicArray_double_append_default2(cutils_cdar_DynamicArray_double*,double*);
extern bool cutils_cdar_DynamicArray_double_push_default3(cutils_cdar_DynamicArray_double*,size_t,double*);
extern size_t cutils_cdar_DynamicArray_double_pull_default2(cutils_cdar_DynamicArray_double*,size_t);
extern bool cutils_cdar_DynamicArray_double_set_default3(cutils_cdar_DynamicArray_double*,size_t,double*);
extern size_t cutils_cdar_DynamicArray_double_pop_default3(cutils_cdar_DynamicArray_double*,size_t,double*);
extern size_t cutils_cdar_DynamicArray_double_sub_default3(cutils_cdar_DynamicArray_double*,size_t,double*);
extern void cutils_cdar_DynamicArray_double_map_default3(cutils_cdar_DynamicArray_double*,size_t,void(*)());
extern bool cutils_cdar_DynamicArray_double_find_default3(cutils_cdar_DynamicArray_double*,double*,size_t*);
extern size_t cutils_cdar_DynamicArray_double_findall_default3(cutils_cdar_DynamicArray_double*,double*,size_t*);
extern void cutils_cdar_DynamicArray_double_print_default1(cutils_cdar_DynamicArray_double*);
/*----------------------------------------------------------------------------*/
typedef struct {} cutils_cdar_DynamicArray_long_double;
extern bool cutils_cdar_DynamicArray_long_double_new(cutils_cdar_DynamicArray_long_double**,size_t,long double*);
extern void(*cutils_cdar_DynamicArray_long_double_del)(cutils_cdar_DynamicArray_long_double*);
extern long double* cutils_cdar_DynamicArray_long_double_data(cutils_cdar_DynamicArray_long_double*,size_t*,size_t*);
extern size_t(*cutils_cdar_DynamicArray_long_double_len)(cutils_cdar_DynamicArray_long_double*);
extern size_t(*cutils_cdar_DynamicArray_long_double_size)(cutils_cdar_DynamicArray_long_double*);
extern long double* cutils_cdar_DynamicArray_long_double_raw(cutils_cdar_DynamicArray_long_double*);
extern bool(*cutils_cdar_DynamicArray_long_double_resize)(cutils_cdar_DynamicArray_long_double*,size_t);
extern void(*cutils_cdar_DynamicArray_long_double_truncate)(cutils_cdar_DynamicArray_long_double*,size_t);
extern void(*cutils_cdar_DynamicArray_long_double_clear)(cutils_cdar_DynamicArray_long_double*);
extern bool(*cutils_cdar_DynamicArray_long_double_swap)(cutils_cdar_DynamicArray_long_double*,size_t,size_t,size_t);
extern bool(*cutils_cdar_DynamicArray_long_double_reverse)(cutils_cdar_DynamicArray_long_double*);
extern bool cutils_cdar_DynamicArray_long_double_append(cutils_cdar_DynamicArray_long_double*,size_t,long double*);
extern bool cutils_cdar_DynamicArray_long_double_push(cutils_cdar_DynamicArray_long_double*,size_t,size_t,long double*);
extern size_t(*cutils_cdar_DynamicArray_long_double_pull)(cutils_cdar_DynamicArray_long_double*,size_t,size_t);
extern bool cutils_cdar_DynamicArray_long_double_set(cutils_cdar_DynamicArray_long_double*,size_t,size_t,long double*);
extern size_t cutils_cdar_DynamicArray_long_double_pop(cutils_cdar_DynamicArray_long_double*,size_t,size_t,long double*);
extern long double cutils_cdar_DynamicArray_long_double_get(cutils_cdar_DynamicArray_long_double*,size_t);
extern size_t cutils_cdar_DynamicArray_long_double_sub(cutils_cdar_DynamicArray_long_double*,size_t,size_t,long double*);
extern void(*cutils_cdar_DynamicArray_long_double_map)(cutils_cdar_DynamicArray_long_double*,size_t,size_t,void(*)());
extern bool cutils_cdar_DynamicArray_long_double_find(cutils_cdar_DynamicArray_long_double*,bool(*)(const void*,const void*,size_t),long double*,size_t*);
extern size_t cutils_cdar_DynamicArray_long_double_findall(cutils_cdar_DynamicArray_long_double*,bool(*)(const void*,const void*,size_t),long double*,size_t*);
extern void(*cutils_cdar_DynamicArray_long_double_print)(cutils_cdar_DynamicArray_long_double*,FILE*,const char*,bool(*)());
extern bool cutils_cdar_DynamicArray_long_double_format(const long double*,char **,size_t*);
extern bool cutils_cdar_DynamicArray_long_double_compare(const void*,const void*,size_t);
extern bool cutils_cdar_DynamicArray_long_double_new_default1(cutils_cdar_DynamicArray_long_double**);
extern bool cutils_cdar_DynamicArray_long_double_new_default2(cutils_cdar_DynamicArray_long_double**,size_t);
extern void cutils_cdar_DynamicArray_long_double_truncate_default1(cutils_cdar_DynamicArray_long_double*);
extern bool cutils_cdar_DynamicArray_long_double_swap_default3(cutils_cdar_DynamicArray_long_double*,size_t,size_t);
extern bool cutils_cdar_DynamicArray_long_double_append_default2(cutils_cdar_DynamicArray_long_double*,long double*);
extern bool cutils_cdar_DynamicArray_long_double_push_default3(cutils_cdar_DynamicArray_long_double*,size_t,long double*);
extern size_t cutils_cdar_DynamicArray_long_double_pull_default2(cutils_cdar_DynamicArray_long_double*,size_t);
extern bool cutils_cdar_DynamicArray_long_double_set_default3(cutils_cdar_DynamicArray_long_double*,size_t,long double*);
extern size_t cutils_cdar_DynamicArray_long_double_pop_default3(cutils_cdar_DynamicArray_long_double*,size_t,long double*);
extern size_t cutils_cdar_DynamicArray_long_double_sub_default3(cutils_cdar_DynamicArray_long_double*,size_t,long double*);
extern void cutils_cdar_DynamicArray_long_double_map_default3(cutils_cdar_DynamicArray_long_double*,size_t,void(*)());
extern bool cutils_cdar_DynamicArray_long_double_find_default3(cutils_cdar_DynamicArray_long_double*,long double*,size_t*);
extern size_t cutils_cdar_DynamicArray_long_double_findall_default3(cutils_cdar_DynamicArray_long_double*,long double*,size_t*);
extern void cutils_cdar_DynamicArray_long_double_print_default1(cutils_cdar_DynamicArray_long_double*);
/*----------------------------------------------------------------------------*/
typedef struct {} cutils_cdar_DynamicArray_bool;
extern bool cutils_cdar_DynamicArray_bool_new(cutils_cdar_DynamicArray_bool**,size_t,bool*);
extern void(*cutils_cdar_DynamicArray_bool_del)(cutils_cdar_DynamicArray_bool*);
extern bool* cutils_cdar_DynamicArray_bool_data(cutils_cdar_DynamicArray_bool*,size_t*,size_t*);
extern size_t(*cutils_cdar_DynamicArray_bool_len)(cutils_cdar_DynamicArray_bool*);
extern size_t(*cutils_cdar_DynamicArray_bool_size)(cutils_cdar_DynamicArray_bool*);
extern bool* cutils_cdar_DynamicArray_bool_raw(cutils_cdar_DynamicArray_bool*);
extern bool(*cutils_cdar_DynamicArray_bool_resize)(cutils_cdar_DynamicArray_bool*,size_t);
extern void(*cutils_cdar_DynamicArray_bool_truncate)(cutils_cdar_DynamicArray_bool*,size_t);
extern void(*cutils_cdar_DynamicArray_bool_clear)(cutils_cdar_DynamicArray_bool*);
extern bool(*cutils_cdar_DynamicArray_bool_swap)(cutils_cdar_DynamicArray_bool*,size_t,size_t,size_t);
extern bool(*cutils_cdar_DynamicArray_bool_reverse)(cutils_cdar_DynamicArray_bool*);
extern bool cutils_cdar_DynamicArray_bool_append(cutils_cdar_DynamicArray_bool*,size_t,bool*);
extern bool cutils_cdar_DynamicArray_bool_push(cutils_cdar_DynamicArray_bool*,size_t,size_t,bool*);
extern size_t(*cutils_cdar_DynamicArray_bool_pull)(cutils_cdar_DynamicArray_bool*,size_t,size_t);
extern bool cutils_cdar_DynamicArray_bool_set(cutils_cdar_DynamicArray_bool*,size_t,size_t,bool*);
extern size_t cutils_cdar_DynamicArray_bool_pop(cutils_cdar_DynamicArray_bool*,size_t,size_t,bool*);
extern bool cutils_cdar_DynamicArray_bool_get(cutils_cdar_DynamicArray_bool*,size_t);
extern size_t cutils_cdar_DynamicArray_bool_sub(cutils_cdar_DynamicArray_bool*,size_t,size_t,bool*);
extern void(*cutils_cdar_DynamicArray_bool_map)(cutils_cdar_DynamicArray_bool*,size_t,size_t,void(*)());
extern bool cutils_cdar_DynamicArray_bool_find(cutils_cdar_DynamicArray_bool*,bool(*)(const void*,const void*,size_t),bool*,size_t*);
extern size_t cutils_cdar_DynamicArray_bool_findall(cutils_cdar_DynamicArray_bool*,bool(*)(const void*,const void*,size_t),bool*,size_t*);
extern void(*cutils_cdar_DynamicArray_bool_print)(cutils_cdar_DynamicArray_bool*,FILE*,const char*,bool(*)());
extern bool cutils_cdar_DynamicArray_bool_format(const bool*,char **,size_t*);
extern bool cutils_cdar_DynamicArray_bool_compare(const void*,const void*,size_t);
extern bool cutils_cdar_DynamicArray_bool_new_default1(cutils_cdar_DynamicArray_bool**);
extern bool cutils_cdar_DynamicArray_bool_new_default2(cutils_cdar_DynamicArray_bool**,size_t);
extern void cutils_cdar_DynamicArray_bool_truncate_default1(cutils_cdar_DynamicArray_bool*);
extern bool cutils_cdar_DynamicArray_bool_swap_default3(cutils_cdar_DynamicArray_bool*,size_t,size_t);
extern bool cutils_cdar_DynamicArray_bool_append_default2(cutils_cdar_DynamicArray_bool*,bool*);
extern bool cutils_cdar_DynamicArray_bool_push_default3(cutils_cdar_DynamicArray_bool*,size_t,bool*);
extern size_t cutils_cdar_DynamicArray_bool_pull_default2(cutils_cdar_DynamicArray_bool*,size_t);
extern bool cutils_cdar_DynamicArray_bool_set_default3(cutils_cdar_DynamicArray_bool*,size_t,bool*);
extern size_t cutils_cdar_DynamicArray_bool_pop_default3(cutils_cdar_DynamicArray_bool*,size_t,bool*);
extern size_t cutils_cdar_DynamicArray_bool_sub_default3(cutils_cdar_DynamicArray_bool*,size_t,bool*);
extern void cutils_cdar_DynamicArray_bool_map_default3(cutils_cdar_DynamicArray_bool*,size_t,void(*)());
extern bool cutils_cdar_DynamicArray_bool_find_default3(cutils_cdar_DynamicArray_bool*,bool*,size_t*);
extern size_t cutils_cdar_DynamicArray_bool_findall_default3(cutils_cdar_DynamicArray_bool*,bool*,size_t*);
extern void cutils_cdar_DynamicArray_bool_print_default1(cutils_cdar_DynamicArray_bool*);
/*----------------------------------------------------------------------------*/
typedef struct {} cutils_cdar_DynamicArray_size_t;
extern bool cutils_cdar_DynamicArray_size_t_new(cutils_cdar_DynamicArray_size_t**,size_t,size_t*);
extern void(*cutils_cdar_DynamicArray_size_t_del)(cutils_cdar_DynamicArray_size_t*);
extern size_t* cutils_cdar_DynamicArray_size_t_data(cutils_cdar_DynamicArray_size_t*,size_t*,size_t*);
extern size_t(*cutils_cdar_DynamicArray_size_t_len)(cutils_cdar_DynamicArray_size_t*);
extern size_t(*cutils_cdar_DynamicArray_size_t_size)(cutils_cdar_DynamicArray_size_t*);
extern size_t* cutils_cdar_DynamicArray_size_t_raw(cutils_cdar_DynamicArray_size_t*);
extern bool(*cutils_cdar_DynamicArray_size_t_resize)(cutils_cdar_DynamicArray_size_t*,size_t);
extern void(*cutils_cdar_DynamicArray_size_t_truncate)(cutils_cdar_DynamicArray_size_t*,size_t);
extern void(*cutils_cdar_DynamicArray_size_t_clear)(cutils_cdar_DynamicArray_size_t*);
extern bool(*cutils_cdar_DynamicArray_size_t_swap)(cutils_cdar_DynamicArray_size_t*,size_t,size_t,size_t);
extern bool(*cutils_cdar_DynamicArray_size_t_reverse)(cutils_cdar_DynamicArray_size_t*);
extern bool cutils_cdar_DynamicArray_size_t_append(cutils_cdar_DynamicArray_size_t*,size_t,size_t*);
extern bool cutils_cdar_DynamicArray_size_t_push(cutils_cdar_DynamicArray_size_t*,size_t,size_t,size_t*);
extern size_t(*cutils_cdar_DynamicArray_size_t_pull)(cutils_cdar_DynamicArray_size_t*,size_t,size_t);
extern bool cutils_cdar_DynamicArray_size_t_set(cutils_cdar_DynamicArray_size_t*,size_t,size_t,size_t*);
extern size_t cutils_cdar_DynamicArray_size_t_pop(cutils_cdar_DynamicArray_size_t*,size_t,size_t,size_t*);
extern size_t cutils_cdar_DynamicArray_size_t_get(cutils_cdar_DynamicArray_size_t*,size_t);
extern size_t cutils_cdar_DynamicArray_size_t_sub(cutils_cdar_DynamicArray_size_t*,size_t,size_t,size_t*);
extern void(*cutils_cdar_DynamicArray_size_t_map)(cutils_cdar_DynamicArray_size_t*,size_t,size_t,void(*)());
extern bool cutils_cdar_DynamicArray_size_t_find(cutils_cdar_DynamicArray_size_t*,bool(*)(const void*,const void*,size_t),size_t*,size_t*);
extern size_t cutils_cdar_DynamicArray_size_t_findall(cutils_cdar_DynamicArray_size_t*,bool(*)(const void*,const void*,size_t),size_t*,size_t*);
extern void(*cutils_cdar_DynamicArray_size_t_print)(cutils_cdar_DynamicArray_size_t*,FILE*,const char*,bool(*)());
extern bool cutils_cdar_DynamicArray_size_t_format(const size_t*,char **,size_t*);
extern bool cutils_cdar_DynamicArray_size_t_compare(const void*,const void*,size_t);
extern bool cutils_cdar_DynamicArray_size_t_new_default1(cutils_cdar_DynamicArray_size_t**);
extern bool cutils_cdar_DynamicArray_size_t_new_default2(cutils_cdar_DynamicArray_size_t**,size_t);
extern void cutils_cdar_DynamicArray_size_t_truncate_default1(cutils_cdar_DynamicArray_size_t*);
extern bool cutils_cdar_DynamicArray_size_t_swap_default3(cutils_cdar_DynamicArray_size_t*,size_t,size_t);
extern bool cutils_cdar_DynamicArray_size_t_append_default2(cutils_cdar_DynamicArray_size_t*,size_t*);
extern bool cutils_cdar_DynamicArray_size_t_push_default3(cutils_cdar_DynamicArray_size_t*,size_t,size_t*);
extern size_t cutils_cdar_DynamicArray_size_t_pull_default2(cutils_cdar_DynamicArray_size_t*,size_t);
extern bool cutils_cdar_DynamicArray_size_t_set_default3(cutils_cdar_DynamicArray_size_t*,size_t,size_t*);
extern size_t cutils_cdar_DynamicArray_size_t_pop_default3(cutils_cdar_DynamicArray_size_t*,size_t,size_t*);
extern size_t cutils_cdar_DynamicArray_size_t_sub_default3(cutils_cdar_DynamicArray_size_t*,size_t,size_t*);
extern void cutils_cdar_DynamicArray_size_t_map_default3(cutils_cdar_DynamicArray_size_t*,size_t,void(*)());
extern bool cutils_cdar_DynamicArray_size_t_find_default3(cutils_cdar_DynamicArray_size_t*,size_t*,size_t*);
extern size_t cutils_cdar_DynamicArray_size_t_findall_default3(cutils_cdar_DynamicArray_size_t*,size_t*,size_t*);
extern void cutils_cdar_DynamicArray_size_t_print_default1(cutils_cdar_DynamicArray_size_t*);
/*----------------------------------------------------------------------------*/
typedef struct {} cutils_cdar_DynamicArray_ptrdiff_t;
extern bool cutils_cdar_DynamicArray_ptrdiff_t_new(cutils_cdar_DynamicArray_ptrdiff_t**,size_t,ptrdiff_t*);
extern void(*cutils_cdar_DynamicArray_ptrdiff_t_del)(cutils_cdar_DynamicArray_ptrdiff_t*);
extern ptrdiff_t* cutils_cdar_DynamicArray_ptrdiff_t_data(cutils_cdar_DynamicArray_ptrdiff_t*,size_t*,size_t*);
extern size_t(*cutils_cdar_DynamicArray_ptrdiff_t_len)(cutils_cdar_DynamicArray_ptrdiff_t*);
extern size_t(*cutils_cdar_DynamicArray_ptrdiff_t_size)(cutils_cdar_DynamicArray_ptrdiff_t*);
extern ptrdiff_t* cutils_cdar_DynamicArray_ptrdiff_t_raw(cutils_cdar_DynamicArray_ptrdiff_t*);
extern bool(*cutils_cdar_DynamicArray_ptrdiff_t_resize)(cutils_cdar_DynamicArray_ptrdiff_t*,size_t);
extern void(*cutils_cdar_DynamicArray_ptrdiff_t_truncate)(cutils_cdar_DynamicArray_ptrdiff_t*,size_t);
extern void(*cutils_cdar_DynamicArray_ptrdiff_t_clear)(cutils_cdar_DynamicArray_ptrdiff_t*);
extern bool(*cutils_cdar_DynamicArray_ptrdiff_t_swap)(cutils_cdar_DynamicArray_ptrdiff_t*,size_t,size_t,size_t);
extern bool(*cutils_cdar_DynamicArray_ptrdiff_t_reverse)(cutils_cdar_DynamicArray_ptrdiff_t*);
extern bool cutils_cdar_DynamicArray_ptrdiff_t_append(cutils_cdar_DynamicArray_ptrdiff_t*,size_t,ptrdiff_t*);
extern bool cutils_cdar_DynamicArray_ptrdiff_t_push(cutils_cdar_DynamicArray_ptrdiff_t*,size_t,size_t,ptrdiff_t*);
extern size_t(*cutils_cdar_DynamicArray_ptrdiff_t_pull)(cutils_cdar_DynamicArray_ptrdiff_t*,size_t,size_t);
extern bool cutils_cdar_DynamicArray_ptrdiff_t_set(cutils_cdar_DynamicArray_ptrdiff_t*,size_t,size_t,ptrdiff_t*);
extern size_t cutils_cdar_DynamicArray_ptrdiff_t_pop(cutils_cdar_DynamicArray_ptrdiff_t*,size_t,size_t,ptrdiff_t*);
extern ptrdiff_t cutils_cdar_DynamicArray_ptrdiff_t_get(cutils_cdar_DynamicArray_ptrdiff_t*,size_t);
extern size_t cutils_cdar_DynamicArray_ptrdiff_t_sub(cutils_cdar_DynamicArray_ptrdiff_t*,size_t,size_t,ptrdiff_t*);
extern void(*cutils_cdar_DynamicArray_ptrdiff_t_map)(cutils_cdar_DynamicArray_ptrdiff_t*,size_t,size_t,void(*)());
extern bool cutils_cdar_DynamicArray_ptrdiff_t_find(cutils_cdar_DynamicArray_ptrdiff_t*,bool(*)(const void*,const void*,size_t),ptrdiff_t*,size_t*);
extern size_t cutils_cdar_DynamicArray_ptrdiff_t_findall(cutils_cdar_DynamicArray_ptrdiff_t*,bool(*)(const void*,const void*,size_t),ptrdiff_t*,size_t*);
extern void(*cutils_cdar_DynamicArray_ptrdiff_t_print)(cutils_cdar_DynamicArray_ptrdiff_t*,FILE*,const char*,bool(*)());
extern bool cutils_cdar_DynamicArray_ptrdiff_t_format(const ptrdiff_t*,char **,size_t*);
extern bool cutils_cdar_DynamicArray_ptrdiff_t_compare(const void*,const void*,size_t);
extern bool cutils_cdar_DynamicArray_ptrdiff_t_new_default1(cutils_cdar_DynamicArray_ptrdiff_t**);
extern bool cutils_cdar_DynamicArray_ptrdiff_t_new_default2(cutils_cdar_DynamicArray_ptrdiff_t**,size_t);
extern void cutils_cdar_DynamicArray_ptrdiff_t_truncate_default1(cutils_cdar_DynamicArray_ptrdiff_t*);
extern bool cutils_cdar_DynamicArray_ptrdiff_t_swap_default3(cutils_cdar_DynamicArray_ptrdiff_t*,size_t,size_t);
extern bool cutils_cdar_DynamicArray_ptrdiff_t_append_default2(cutils_cdar_DynamicArray_ptrdiff_t*,ptrdiff_t*);
extern bool cutils_cdar_DynamicArray_ptrdiff_t_push_default3(cutils_cdar_DynamicArray_ptrdiff_t*,size_t,ptrdiff_t*);
extern size_t cutils_cdar_DynamicArray_ptrdiff_t_pull_default2(cutils_cdar_DynamicArray_ptrdiff_t*,size_t);
extern bool cutils_cdar_DynamicArray_ptrdiff_t_set_default3(cutils_cdar_DynamicArray_ptrdiff_t*,size_t,ptrdiff_t*);
extern size_t cutils_cdar_DynamicArray_ptrdiff_t_pop_default3(cutils_cdar_DynamicArray_ptrdiff_t*,size_t,ptrdiff_t*);
extern size_t cutils_cdar_DynamicArray_ptrdiff_t_sub_default3(cutils_cdar_DynamicArray_ptrdiff_t*,size_t,ptrdiff_t*);
extern void cutils_cdar_DynamicArray_ptrdiff_t_map_default3(cutils_cdar_DynamicArray_ptrdiff_t*,size_t,void(*)());
extern bool cutils_cdar_DynamicArray_ptrdiff_t_find_default3(cutils_cdar_DynamicArray_ptrdiff_t*,ptrdiff_t*,size_t*);
extern size_t cutils_cdar_DynamicArray_ptrdiff_t_findall_default3(cutils_cdar_DynamicArray_ptrdiff_t*,ptrdiff_t*,size_t*);
extern void cutils_cdar_DynamicArray_ptrdiff_t_print_default1(cutils_cdar_DynamicArray_ptrdiff_t*);

#endif /* _C_DYNAMIC_ARRAY_H_2427147457128005_ */
