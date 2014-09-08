/* INFO ************************************************************************
**                                                                            **
**                                   cutils                                   **
**                                   ======                                   **
**                                                                            **
**                     Modern and Lightweight C Utilities                     **
**                       Version: 0.8.96.219 (20140908)                       **
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

#include <stdio.h>    /* FILE */
#include <stddef.h>   /* ptrdiff_t */
#include <stddef.h>   /* size_t */
#include <stdbool.h>  /* bool */

/*----------------------------------------------------------------------------*/
/* Shorthands for this source */
#undef _concat_underscore
#undef concat_underscore
#undef LINKED_LIST
#undef METHOD
#undef SUPPORT
#undef SUPPORT_METHOD
#define _concat_underscore(token1, token2) token1##_##token2
#define concat_underscore(token1, token2) _concat_underscore(token1, token2)
#define LINKED_LIST cutils_csll_SinglyLinkedList_void_ptr
#define METHOD(func)  concat_underscore(LINKED_LIST, func)
#define SUPPORT(type) concat_underscore(LINKED_LIST, type)
#define SUPPORT_METHOD(type, func) concat_underscore(LINKED_LIST, type##_##func)

/*----------------------------------------------------------------------------*/
typedef struct {} LINKED_LIST;
typedef struct {} SUPPORT(iterator);

/*----------------------------------------------------------------------------*/
extern bool
METHOD(new)(LINKED_LIST **linlist,
            size_t item_size,
            size_t count,
            void *source);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
extern bool
METHOD(new_default1)(LINKED_LIST **linlist);
/*----------------------------------------------------------------------------*/
extern void
METHOD(del)(LINKED_LIST *linlist);
/*----------------------------------------------------------------------------*/
extern void
METHOD(clear)(LINKED_LIST *linlist);
/*----------------------------------------------------------------------------*/
extern size_t
METHOD(len)(LINKED_LIST *linlist);
/*----------------------------------------------------------------------------*/
extern bool
METHOD(swap)(LINKED_LIST *linlist,
             size_t index1,
             size_t index2,
             size_t count);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
extern bool
METHOD(swap_default3)(LINKED_LIST *linlist,
                      size_t index1,
                      size_t index2);
/*----------------------------------------------------------------------------*/
extern bool
METHOD(reverse)(LINKED_LIST *linlist);
/*----------------------------------------------------------------------------*/
extern bool
METHOD(append)(LINKED_LIST *linlist,
               size_t item_size,
               size_t count,
               void *source);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
extern bool
METHOD(append_default3)(LINKED_LIST *linlist,
                        size_t item_size,
                        void *source);
/*----------------------------------------------------------------------------*/
extern bool
METHOD(push)(LINKED_LIST *linlist,
             size_t index,
             size_t item_size,
             size_t count,
             void *source);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
extern bool
METHOD(push_default4)(LINKED_LIST *linlist,
                      size_t index,
                      size_t item_size,
                      void *source);
/*----------------------------------------------------------------------------*/
extern size_t
METHOD(pull)(LINKED_LIST *linlist,
             size_t index,
             size_t count);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
extern size_t
METHOD(pull_default2)(LINKED_LIST *linlist,
                      size_t index);
/*----------------------------------------------------------------------------*/
extern size_t
METHOD(pop)(LINKED_LIST *linlist,
            size_t index,
            size_t item_size,
            size_t count,
            void *destination);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
extern size_t
METHOD(pop_default4)(LINKED_LIST *linlist,
                     size_t index,
                     size_t item_size,
                     void *destination);
/*----------------------------------------------------------------------------*/
extern size_t
METHOD(sub)(LINKED_LIST *linlist,
            size_t index,
            size_t item_size,
            size_t count,
            void *destination);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
extern size_t
METHOD(sub_default4)(LINKED_LIST *linlist,
                     size_t index,
                     size_t item_size,
                     void *destination);
/*----------------------------------------------------------------------------*/
extern void
METHOD(truncate)(LINKED_LIST *linlist,
                 size_t index);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
extern void
METHOD(truncate_default1)(LINKED_LIST *linlist);
/*----------------------------------------------------------------------------*/
extern bool
METHOD(set)(LINKED_LIST *linlist,
            size_t index,
            size_t item_size,
            size_t count,
            void *source);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
extern bool
METHOD(set_default4)(LINKED_LIST *linlist,
                     size_t index,
                     size_t item_size,
                     void *source);
/*----------------------------------------------------------------------------*/
extern void *
METHOD(get)(LINKED_LIST *linlist,
            size_t index);
/*----------------------------------------------------------------------------*/
extern bool
METHOD(find)(LINKED_LIST *linlist,
             bool (*compare)(const void*, const void*, size_t),
             size_t item_size,
             const void *item,
             size_t *index);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
extern bool
METHOD(find_default4)(LINKED_LIST *linlist,
                      size_t item_size,
                      const void *item,
                      size_t *index);
/*----------------------------------------------------------------------------*/
extern size_t
METHOD(findall)(LINKED_LIST *linlist,
                bool (*compare)(const void*, const void*, size_t),
                size_t item_size,
                const void *item,
                size_t *indices);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
extern size_t
METHOD(findall_default4)(LINKED_LIST *linlist,
                         size_t item_size,
                         const void *item,
                         size_t *index);
/*----------------------------------------------------------------------------*/
extern SUPPORT(iterator) *
METHOD(iter)(LINKED_LIST *linlist);
/*----------------------------------------------------------------------------*/
extern void
SUPPORT_METHOD(iterator, del)(SUPPORT(iterator) *node);
/*----------------------------------------------------------------------------*/
extern bool
SUPPORT_METHOD(iterator, next)(SUPPORT(iterator) *node,
                               void *data);
/*----------------------------------------------------------------------------*/
extern void
SUPPORT_METHOD(iterator, pull)(SUPPORT(iterator) *iterator);
/*----------------------------------------------------------------------------*/
extern void
METHOD(map)(LINKED_LIST *linlist,
            size_t index,
            size_t count,
            void (*function)());
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
extern void
METHOD(map_default3)(LINKED_LIST *linlist,
                     size_t count,
                     void (*function)());
/*----------------------------------------------------------------------------*/
extern void
METHOD(print)(LINKED_LIST *linlist,
              FILE *stream,
              const char *sub_type,
              bool(*format)());
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
extern void
METHOD(print_default1)(LINKED_LIST *linlist);
/*----------------------------------------------------------------------------*/
extern bool
METHOD(format)(const void *data,
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
#undef LINKED_LIST
#undef METHOD
#undef SUPPORT
#undef SUPPORT_METHOD

/*----------------------------------------------------------------------------*/
typedef struct {} cutils_csll_SinglyLinkedList_char;
typedef struct {} cutils_csll_SinglyLinkedList_char_iterator;
extern bool cutils_csll_SinglyLinkedList_char_new(cutils_csll_SinglyLinkedList_char**,size_t,char*);
extern void(*cutils_csll_SinglyLinkedList_char_del)(cutils_csll_SinglyLinkedList_char*);
extern size_t(*cutils_csll_SinglyLinkedList_char_len)(cutils_csll_SinglyLinkedList_char*);
extern void(*cutils_csll_SinglyLinkedList_char_truncate)(cutils_csll_SinglyLinkedList_char*,size_t);
extern void(*cutils_csll_SinglyLinkedList_char_clear)(cutils_csll_SinglyLinkedList_char*);
extern cutils_csll_SinglyLinkedList_char_iterator* cutils_csll_SinglyLinkedList_char_iter(cutils_csll_SinglyLinkedList_char*);
extern void cutils_csll_SinglyLinkedList_char_iterator_del(cutils_csll_SinglyLinkedList_char_iterator*);
extern bool cutils_csll_SinglyLinkedList_char_iterator_next(cutils_csll_SinglyLinkedList_char_iterator*,char**);
extern void cutils_csll_SinglyLinkedList_char_iterator_pull(cutils_csll_SinglyLinkedList_char_iterator*);
extern bool(*cutils_csll_SinglyLinkedList_char_swap)(cutils_csll_SinglyLinkedList_char*,size_t,size_t,size_t);
extern bool(*cutils_csll_SinglyLinkedList_char_reverse)(cutils_csll_SinglyLinkedList_char*);
extern bool cutils_csll_SinglyLinkedList_char_append(cutils_csll_SinglyLinkedList_char*,size_t,char*);
extern bool cutils_csll_SinglyLinkedList_char_push(cutils_csll_SinglyLinkedList_char*,size_t,size_t,char*);
extern size_t(*cutils_csll_SinglyLinkedList_char_pull)(cutils_csll_SinglyLinkedList_char*,size_t,size_t);
extern bool cutils_csll_SinglyLinkedList_char_set(cutils_csll_SinglyLinkedList_char*,size_t,size_t,char*);
extern bool cutils_csll_SinglyLinkedList_char_pop(cutils_csll_SinglyLinkedList_char*,size_t,size_t,char*);
extern char cutils_csll_SinglyLinkedList_char_get(cutils_csll_SinglyLinkedList_char*,size_t);
extern bool cutils_csll_SinglyLinkedList_char_sub(cutils_csll_SinglyLinkedList_char*,size_t,size_t,char*);
extern void(*cutils_csll_SinglyLinkedList_char_map)(cutils_csll_SinglyLinkedList_char*,size_t,size_t,void(*)());
extern bool cutils_csll_SinglyLinkedList_char_find(cutils_csll_SinglyLinkedList_char*,bool(*)(const void*,const void*,size_t),char*,size_t*);
extern size_t cutils_csll_SinglyLinkedList_char_findall(cutils_csll_SinglyLinkedList_char*,bool(*)(const void*,const void*,size_t),char*,size_t*);
extern void(*cutils_csll_SinglyLinkedList_char_print)(cutils_csll_SinglyLinkedList_char*,FILE*,const char*,bool(*)());
extern bool cutils_csll_SinglyLinkedList_char_format(const char*,char**,size_t*);
extern bool cutils_csll_SinglyLinkedList_char_compare(const void*,const void*,size_t);
extern bool cutils_csll_SinglyLinkedList_char_new_default1(cutils_csll_SinglyLinkedList_char**);
extern void cutils_csll_SinglyLinkedList_char_truncate_default1(cutils_csll_SinglyLinkedList_char*);
extern bool cutils_csll_SinglyLinkedList_char_swap_default3(cutils_csll_SinglyLinkedList_char*,size_t,size_t);
extern bool cutils_csll_SinglyLinkedList_char_append_default2(cutils_csll_SinglyLinkedList_char*,char*);
extern bool cutils_csll_SinglyLinkedList_char_push_default3(cutils_csll_SinglyLinkedList_char*,size_t,char*);
extern size_t cutils_csll_SinglyLinkedList_char_pull_default2(cutils_csll_SinglyLinkedList_char*,size_t);
extern bool cutils_csll_SinglyLinkedList_char_set_default3(cutils_csll_SinglyLinkedList_char*,size_t,char*);
extern bool cutils_csll_SinglyLinkedList_char_pop_default3(cutils_csll_SinglyLinkedList_char*,size_t,char*);
extern bool cutils_csll_SinglyLinkedList_char_sub_default3(cutils_csll_SinglyLinkedList_char*,size_t,char*);
extern void cutils_csll_SinglyLinkedList_char_map_default3(cutils_csll_SinglyLinkedList_char*,size_t,void(*)());
extern bool cutils_csll_SinglyLinkedList_char_find_default3(cutils_csll_SinglyLinkedList_char*,char*,size_t*);
extern size_t cutils_csll_SinglyLinkedList_char_findall_default3(cutils_csll_SinglyLinkedList_char*,char*,size_t*);
extern void cutils_csll_SinglyLinkedList_char_print_default1(cutils_csll_SinglyLinkedList_char*);
/*----------------------------------------------------------------------------*/
typedef struct {} cutils_csll_SinglyLinkedList_signed_char;
typedef struct {} cutils_csll_SinglyLinkedList_signed_char_iterator;
extern bool cutils_csll_SinglyLinkedList_signed_char_new(cutils_csll_SinglyLinkedList_signed_char**,size_t,signed char*);
extern void(*cutils_csll_SinglyLinkedList_signed_char_del)(cutils_csll_SinglyLinkedList_signed_char*);
extern size_t(*cutils_csll_SinglyLinkedList_signed_char_len)(cutils_csll_SinglyLinkedList_signed_char*);
extern void(*cutils_csll_SinglyLinkedList_signed_char_truncate)(cutils_csll_SinglyLinkedList_signed_char*,size_t);
extern void(*cutils_csll_SinglyLinkedList_signed_char_clear)(cutils_csll_SinglyLinkedList_signed_char*);
extern cutils_csll_SinglyLinkedList_signed_char_iterator* cutils_csll_SinglyLinkedList_signed_char_iter(cutils_csll_SinglyLinkedList_signed_char*);
extern void cutils_csll_SinglyLinkedList_signed_char_iterator_del(cutils_csll_SinglyLinkedList_signed_char_iterator*);
extern bool cutils_csll_SinglyLinkedList_signed_char_iterator_next(cutils_csll_SinglyLinkedList_signed_char_iterator*,signed char**);
extern void cutils_csll_SinglyLinkedList_signed_char_iterator_pull(cutils_csll_SinglyLinkedList_signed_char_iterator*);
extern bool(*cutils_csll_SinglyLinkedList_signed_char_swap)(cutils_csll_SinglyLinkedList_signed_char*,size_t,size_t,size_t);
extern bool(*cutils_csll_SinglyLinkedList_signed_char_reverse)(cutils_csll_SinglyLinkedList_signed_char*);
extern bool cutils_csll_SinglyLinkedList_signed_char_append(cutils_csll_SinglyLinkedList_signed_char*,size_t,signed char*);
extern bool cutils_csll_SinglyLinkedList_signed_char_push(cutils_csll_SinglyLinkedList_signed_char*,size_t,size_t,signed char*);
extern size_t(*cutils_csll_SinglyLinkedList_signed_char_pull)(cutils_csll_SinglyLinkedList_signed_char*,size_t,size_t);
extern bool cutils_csll_SinglyLinkedList_signed_char_set(cutils_csll_SinglyLinkedList_signed_char*,size_t,size_t,signed char*);
extern bool cutils_csll_SinglyLinkedList_signed_char_pop(cutils_csll_SinglyLinkedList_signed_char*,size_t,size_t,signed char*);
extern signed char cutils_csll_SinglyLinkedList_signed_char_get(cutils_csll_SinglyLinkedList_signed_char*,size_t);
extern bool cutils_csll_SinglyLinkedList_signed_char_sub(cutils_csll_SinglyLinkedList_signed_char*,size_t,size_t,signed char*);
extern void(*cutils_csll_SinglyLinkedList_signed_char_map)(cutils_csll_SinglyLinkedList_signed_char*,size_t,size_t,void(*)());
extern bool cutils_csll_SinglyLinkedList_signed_char_find(cutils_csll_SinglyLinkedList_signed_char*,bool(*)(const void*,const void*,size_t),signed char*,size_t*);
extern size_t cutils_csll_SinglyLinkedList_signed_char_findall(cutils_csll_SinglyLinkedList_signed_char*,bool(*)(const void*,const void*,size_t),signed char*,size_t*);
extern void(*cutils_csll_SinglyLinkedList_signed_char_print)(cutils_csll_SinglyLinkedList_signed_char*,FILE*,const char*,bool(*)());
extern bool cutils_csll_SinglyLinkedList_signed_char_format(const signed char*,char**,size_t*);
extern bool cutils_csll_SinglyLinkedList_signed_char_compare(const void*,const void*,size_t);
extern bool cutils_csll_SinglyLinkedList_signed_char_new_default1(cutils_csll_SinglyLinkedList_signed_char**);
extern void cutils_csll_SinglyLinkedList_signed_char_truncate_default1(cutils_csll_SinglyLinkedList_signed_char*);
extern bool cutils_csll_SinglyLinkedList_signed_char_swap_default3(cutils_csll_SinglyLinkedList_signed_char*,size_t,size_t);
extern bool cutils_csll_SinglyLinkedList_signed_char_append_default2(cutils_csll_SinglyLinkedList_signed_char*,signed char*);
extern bool cutils_csll_SinglyLinkedList_signed_char_push_default3(cutils_csll_SinglyLinkedList_signed_char*,size_t,signed char*);
extern size_t cutils_csll_SinglyLinkedList_signed_char_pull_default2(cutils_csll_SinglyLinkedList_signed_char*,size_t);
extern bool cutils_csll_SinglyLinkedList_signed_char_set_default3(cutils_csll_SinglyLinkedList_signed_char*,size_t,signed char*);
extern bool cutils_csll_SinglyLinkedList_signed_char_pop_default3(cutils_csll_SinglyLinkedList_signed_char*,size_t,signed char*);
extern bool cutils_csll_SinglyLinkedList_signed_char_sub_default3(cutils_csll_SinglyLinkedList_signed_char*,size_t,signed char*);
extern void cutils_csll_SinglyLinkedList_signed_char_map_default3(cutils_csll_SinglyLinkedList_signed_char*,size_t,void(*)());
extern bool cutils_csll_SinglyLinkedList_signed_char_find_default3(cutils_csll_SinglyLinkedList_signed_char*,signed char*,size_t*);
extern size_t cutils_csll_SinglyLinkedList_signed_char_findall_default3(cutils_csll_SinglyLinkedList_signed_char*,signed char*,size_t*);
extern void cutils_csll_SinglyLinkedList_signed_char_print_default1(cutils_csll_SinglyLinkedList_signed_char*);
/*----------------------------------------------------------------------------*/
typedef struct {} cutils_csll_SinglyLinkedList_unsigned_char;
typedef struct {} cutils_csll_SinglyLinkedList_unsigned_char_iterator;
extern bool cutils_csll_SinglyLinkedList_unsigned_char_new(cutils_csll_SinglyLinkedList_unsigned_char**,size_t,unsigned char*);
extern void(*cutils_csll_SinglyLinkedList_unsigned_char_del)(cutils_csll_SinglyLinkedList_unsigned_char*);
extern size_t(*cutils_csll_SinglyLinkedList_unsigned_char_len)(cutils_csll_SinglyLinkedList_unsigned_char*);
extern void(*cutils_csll_SinglyLinkedList_unsigned_char_truncate)(cutils_csll_SinglyLinkedList_unsigned_char*,size_t);
extern void(*cutils_csll_SinglyLinkedList_unsigned_char_clear)(cutils_csll_SinglyLinkedList_unsigned_char*);
extern cutils_csll_SinglyLinkedList_unsigned_char_iterator* cutils_csll_SinglyLinkedList_unsigned_char_iter(cutils_csll_SinglyLinkedList_unsigned_char*);
extern void cutils_csll_SinglyLinkedList_unsigned_char_iterator_del(cutils_csll_SinglyLinkedList_unsigned_char_iterator*);
extern bool cutils_csll_SinglyLinkedList_unsigned_char_iterator_next(cutils_csll_SinglyLinkedList_unsigned_char_iterator*,unsigned char**);
extern void cutils_csll_SinglyLinkedList_unsigned_char_iterator_pull(cutils_csll_SinglyLinkedList_unsigned_char_iterator*);
extern bool(*cutils_csll_SinglyLinkedList_unsigned_char_swap)(cutils_csll_SinglyLinkedList_unsigned_char*,size_t,size_t,size_t);
extern bool(*cutils_csll_SinglyLinkedList_unsigned_char_reverse)(cutils_csll_SinglyLinkedList_unsigned_char*);
extern bool cutils_csll_SinglyLinkedList_unsigned_char_append(cutils_csll_SinglyLinkedList_unsigned_char*,size_t,unsigned char*);
extern bool cutils_csll_SinglyLinkedList_unsigned_char_push(cutils_csll_SinglyLinkedList_unsigned_char*,size_t,size_t,unsigned char*);
extern size_t(*cutils_csll_SinglyLinkedList_unsigned_char_pull)(cutils_csll_SinglyLinkedList_unsigned_char*,size_t,size_t);
extern bool cutils_csll_SinglyLinkedList_unsigned_char_set(cutils_csll_SinglyLinkedList_unsigned_char*,size_t,size_t,unsigned char*);
extern bool cutils_csll_SinglyLinkedList_unsigned_char_pop(cutils_csll_SinglyLinkedList_unsigned_char*,size_t,size_t,unsigned char*);
extern unsigned char cutils_csll_SinglyLinkedList_unsigned_char_get(cutils_csll_SinglyLinkedList_unsigned_char*,size_t);
extern bool cutils_csll_SinglyLinkedList_unsigned_char_sub(cutils_csll_SinglyLinkedList_unsigned_char*,size_t,size_t,unsigned char*);
extern void(*cutils_csll_SinglyLinkedList_unsigned_char_map)(cutils_csll_SinglyLinkedList_unsigned_char*,size_t,size_t,void(*)());
extern bool cutils_csll_SinglyLinkedList_unsigned_char_find(cutils_csll_SinglyLinkedList_unsigned_char*,bool(*)(const void*,const void*,size_t),unsigned char*,size_t*);
extern size_t cutils_csll_SinglyLinkedList_unsigned_char_findall(cutils_csll_SinglyLinkedList_unsigned_char*,bool(*)(const void*,const void*,size_t),unsigned char*,size_t*);
extern void(*cutils_csll_SinglyLinkedList_unsigned_char_print)(cutils_csll_SinglyLinkedList_unsigned_char*,FILE*,const char*,bool(*)());
extern bool cutils_csll_SinglyLinkedList_unsigned_char_format(const unsigned char*,char**,size_t*);
extern bool cutils_csll_SinglyLinkedList_unsigned_char_compare(const void*,const void*,size_t);
extern bool cutils_csll_SinglyLinkedList_unsigned_char_new_default1(cutils_csll_SinglyLinkedList_unsigned_char**);
extern void cutils_csll_SinglyLinkedList_unsigned_char_truncate_default1(cutils_csll_SinglyLinkedList_unsigned_char*);
extern bool cutils_csll_SinglyLinkedList_unsigned_char_swap_default3(cutils_csll_SinglyLinkedList_unsigned_char*,size_t,size_t);
extern bool cutils_csll_SinglyLinkedList_unsigned_char_append_default2(cutils_csll_SinglyLinkedList_unsigned_char*,unsigned char*);
extern bool cutils_csll_SinglyLinkedList_unsigned_char_push_default3(cutils_csll_SinglyLinkedList_unsigned_char*,size_t,unsigned char*);
extern size_t cutils_csll_SinglyLinkedList_unsigned_char_pull_default2(cutils_csll_SinglyLinkedList_unsigned_char*,size_t);
extern bool cutils_csll_SinglyLinkedList_unsigned_char_set_default3(cutils_csll_SinglyLinkedList_unsigned_char*,size_t,unsigned char*);
extern bool cutils_csll_SinglyLinkedList_unsigned_char_pop_default3(cutils_csll_SinglyLinkedList_unsigned_char*,size_t,unsigned char*);
extern bool cutils_csll_SinglyLinkedList_unsigned_char_sub_default3(cutils_csll_SinglyLinkedList_unsigned_char*,size_t,unsigned char*);
extern void cutils_csll_SinglyLinkedList_unsigned_char_map_default3(cutils_csll_SinglyLinkedList_unsigned_char*,size_t,void(*)());
extern bool cutils_csll_SinglyLinkedList_unsigned_char_find_default3(cutils_csll_SinglyLinkedList_unsigned_char*,unsigned char*,size_t*);
extern size_t cutils_csll_SinglyLinkedList_unsigned_char_findall_default3(cutils_csll_SinglyLinkedList_unsigned_char*,unsigned char*,size_t*);
extern void cutils_csll_SinglyLinkedList_unsigned_char_print_default1(cutils_csll_SinglyLinkedList_unsigned_char*);
/*----------------------------------------------------------------------------*/
typedef struct {} cutils_csll_SinglyLinkedList_char_ptr;
typedef struct {} cutils_csll_SinglyLinkedList_char_ptr_iterator;
extern bool cutils_csll_SinglyLinkedList_char_ptr_new(cutils_csll_SinglyLinkedList_char_ptr**,size_t,char**);
extern void(*cutils_csll_SinglyLinkedList_char_ptr_del)(cutils_csll_SinglyLinkedList_char_ptr*);
extern size_t(*cutils_csll_SinglyLinkedList_char_ptr_len)(cutils_csll_SinglyLinkedList_char_ptr*);
extern void(*cutils_csll_SinglyLinkedList_char_ptr_truncate)(cutils_csll_SinglyLinkedList_char_ptr*,size_t);
extern void(*cutils_csll_SinglyLinkedList_char_ptr_clear)(cutils_csll_SinglyLinkedList_char_ptr*);
extern cutils_csll_SinglyLinkedList_char_ptr_iterator* cutils_csll_SinglyLinkedList_char_ptr_iter(cutils_csll_SinglyLinkedList_char_ptr*);
extern void cutils_csll_SinglyLinkedList_char_ptr_iterator_del(cutils_csll_SinglyLinkedList_char_ptr_iterator*);
extern bool cutils_csll_SinglyLinkedList_char_ptr_iterator_next(cutils_csll_SinglyLinkedList_char_ptr_iterator*,char***);
extern void cutils_csll_SinglyLinkedList_char_ptr_iterator_pull(cutils_csll_SinglyLinkedList_char_ptr_iterator*);
extern bool(*cutils_csll_SinglyLinkedList_char_ptr_swap)(cutils_csll_SinglyLinkedList_char_ptr*,size_t,size_t,size_t);
extern bool(*cutils_csll_SinglyLinkedList_char_ptr_reverse)(cutils_csll_SinglyLinkedList_char_ptr*);
extern bool cutils_csll_SinglyLinkedList_char_ptr_append(cutils_csll_SinglyLinkedList_char_ptr*,size_t,char**);
extern bool cutils_csll_SinglyLinkedList_char_ptr_push(cutils_csll_SinglyLinkedList_char_ptr*,size_t,size_t,char**);
extern size_t(*cutils_csll_SinglyLinkedList_char_ptr_pull)(cutils_csll_SinglyLinkedList_char_ptr*,size_t,size_t);
extern bool cutils_csll_SinglyLinkedList_char_ptr_set(cutils_csll_SinglyLinkedList_char_ptr*,size_t,size_t,char**);
extern bool cutils_csll_SinglyLinkedList_char_ptr_pop(cutils_csll_SinglyLinkedList_char_ptr*,size_t,size_t,char**);
extern char* cutils_csll_SinglyLinkedList_char_ptr_get(cutils_csll_SinglyLinkedList_char_ptr*,size_t);
extern bool cutils_csll_SinglyLinkedList_char_ptr_sub(cutils_csll_SinglyLinkedList_char_ptr*,size_t,size_t,char**);
extern void(*cutils_csll_SinglyLinkedList_char_ptr_map)(cutils_csll_SinglyLinkedList_char_ptr*,size_t,size_t,void(*)());
extern bool cutils_csll_SinglyLinkedList_char_ptr_find(cutils_csll_SinglyLinkedList_char_ptr*,bool(*)(const void*,const void*,size_t),char**,size_t*);
extern size_t cutils_csll_SinglyLinkedList_char_ptr_findall(cutils_csll_SinglyLinkedList_char_ptr*,bool(*)(const void*,const void*,size_t),char**,size_t*);
extern void(*cutils_csll_SinglyLinkedList_char_ptr_print)(cutils_csll_SinglyLinkedList_char_ptr*,FILE*,const char*,bool(*)());
extern bool cutils_csll_SinglyLinkedList_char_ptr_format(const char**,char**,size_t*);
extern bool cutils_csll_SinglyLinkedList_char_ptr_compare(const void*,const void*,size_t);
extern bool cutils_csll_SinglyLinkedList_char_ptr_new_default1(cutils_csll_SinglyLinkedList_char_ptr**);
extern void cutils_csll_SinglyLinkedList_char_ptr_truncate_default1(cutils_csll_SinglyLinkedList_char_ptr*);
extern bool cutils_csll_SinglyLinkedList_char_ptr_swap_default3(cutils_csll_SinglyLinkedList_char_ptr*,size_t,size_t);
extern bool cutils_csll_SinglyLinkedList_char_ptr_append_default2(cutils_csll_SinglyLinkedList_char_ptr*,char**);
extern bool cutils_csll_SinglyLinkedList_char_ptr_push_default3(cutils_csll_SinglyLinkedList_char_ptr*,size_t,char**);
extern size_t cutils_csll_SinglyLinkedList_char_ptr_pull_default2(cutils_csll_SinglyLinkedList_char_ptr*,size_t);
extern bool cutils_csll_SinglyLinkedList_char_ptr_set_default3(cutils_csll_SinglyLinkedList_char_ptr*,size_t,char**);
extern bool cutils_csll_SinglyLinkedList_char_ptr_pop_default3(cutils_csll_SinglyLinkedList_char_ptr*,size_t,char**);
extern bool cutils_csll_SinglyLinkedList_char_ptr_sub_default3(cutils_csll_SinglyLinkedList_char_ptr*,size_t,char**);
extern void cutils_csll_SinglyLinkedList_char_ptr_map_default3(cutils_csll_SinglyLinkedList_char_ptr*,size_t,void(*)());
extern bool cutils_csll_SinglyLinkedList_char_ptr_find_default3(cutils_csll_SinglyLinkedList_char_ptr*,char**,size_t*);
extern size_t cutils_csll_SinglyLinkedList_char_ptr_findall_default3(cutils_csll_SinglyLinkedList_char_ptr*,char**,size_t*);
extern void cutils_csll_SinglyLinkedList_char_ptr_print_default1(cutils_csll_SinglyLinkedList_char_ptr*);
/*----------------------------------------------------------------------------*/
typedef struct {} cutils_csll_SinglyLinkedList_short;
typedef struct {} cutils_csll_SinglyLinkedList_short_iterator;
extern bool cutils_csll_SinglyLinkedList_short_new(cutils_csll_SinglyLinkedList_short**,size_t,short*);
extern void(*cutils_csll_SinglyLinkedList_short_del)(cutils_csll_SinglyLinkedList_short*);
extern size_t(*cutils_csll_SinglyLinkedList_short_len)(cutils_csll_SinglyLinkedList_short*);
extern void(*cutils_csll_SinglyLinkedList_short_truncate)(cutils_csll_SinglyLinkedList_short*,size_t);
extern void(*cutils_csll_SinglyLinkedList_short_clear)(cutils_csll_SinglyLinkedList_short*);
extern cutils_csll_SinglyLinkedList_short_iterator* cutils_csll_SinglyLinkedList_short_iter(cutils_csll_SinglyLinkedList_short*);
extern void cutils_csll_SinglyLinkedList_short_iterator_del(cutils_csll_SinglyLinkedList_short_iterator*);
extern bool cutils_csll_SinglyLinkedList_short_iterator_next(cutils_csll_SinglyLinkedList_short_iterator*,short**);
extern void cutils_csll_SinglyLinkedList_short_iterator_pull(cutils_csll_SinglyLinkedList_short_iterator*);
extern bool(*cutils_csll_SinglyLinkedList_short_swap)(cutils_csll_SinglyLinkedList_short*,size_t,size_t,size_t);
extern bool(*cutils_csll_SinglyLinkedList_short_reverse)(cutils_csll_SinglyLinkedList_short*);
extern bool cutils_csll_SinglyLinkedList_short_append(cutils_csll_SinglyLinkedList_short*,size_t,short*);
extern bool cutils_csll_SinglyLinkedList_short_push(cutils_csll_SinglyLinkedList_short*,size_t,size_t,short*);
extern size_t(*cutils_csll_SinglyLinkedList_short_pull)(cutils_csll_SinglyLinkedList_short*,size_t,size_t);
extern bool cutils_csll_SinglyLinkedList_short_set(cutils_csll_SinglyLinkedList_short*,size_t,size_t,short*);
extern bool cutils_csll_SinglyLinkedList_short_pop(cutils_csll_SinglyLinkedList_short*,size_t,size_t,short*);
extern short cutils_csll_SinglyLinkedList_short_get(cutils_csll_SinglyLinkedList_short*,size_t);
extern bool cutils_csll_SinglyLinkedList_short_sub(cutils_csll_SinglyLinkedList_short*,size_t,size_t,short*);
extern void(*cutils_csll_SinglyLinkedList_short_map)(cutils_csll_SinglyLinkedList_short*,size_t,size_t,void(*)());
extern bool cutils_csll_SinglyLinkedList_short_find(cutils_csll_SinglyLinkedList_short*,bool(*)(const void*,const void*,size_t),short*,size_t*);
extern size_t cutils_csll_SinglyLinkedList_short_findall(cutils_csll_SinglyLinkedList_short*,bool(*)(const void*,const void*,size_t),short*,size_t*);
extern void(*cutils_csll_SinglyLinkedList_short_print)(cutils_csll_SinglyLinkedList_short*,FILE*,const char*,bool(*)());
extern bool cutils_csll_SinglyLinkedList_short_format(const short*,char**,size_t*);
extern bool cutils_csll_SinglyLinkedList_short_compare(const void*,const void*,size_t);
extern bool cutils_csll_SinglyLinkedList_short_new_default1(cutils_csll_SinglyLinkedList_short**);
extern void cutils_csll_SinglyLinkedList_short_truncate_default1(cutils_csll_SinglyLinkedList_short*);
extern bool cutils_csll_SinglyLinkedList_short_swap_default3(cutils_csll_SinglyLinkedList_short*,size_t,size_t);
extern bool cutils_csll_SinglyLinkedList_short_append_default2(cutils_csll_SinglyLinkedList_short*,short*);
extern bool cutils_csll_SinglyLinkedList_short_push_default3(cutils_csll_SinglyLinkedList_short*,size_t,short*);
extern size_t cutils_csll_SinglyLinkedList_short_pull_default2(cutils_csll_SinglyLinkedList_short*,size_t);
extern bool cutils_csll_SinglyLinkedList_short_set_default3(cutils_csll_SinglyLinkedList_short*,size_t,short*);
extern bool cutils_csll_SinglyLinkedList_short_pop_default3(cutils_csll_SinglyLinkedList_short*,size_t,short*);
extern bool cutils_csll_SinglyLinkedList_short_sub_default3(cutils_csll_SinglyLinkedList_short*,size_t,short*);
extern void cutils_csll_SinglyLinkedList_short_map_default3(cutils_csll_SinglyLinkedList_short*,size_t,void(*)());
extern bool cutils_csll_SinglyLinkedList_short_find_default3(cutils_csll_SinglyLinkedList_short*,short*,size_t*);
extern size_t cutils_csll_SinglyLinkedList_short_findall_default3(cutils_csll_SinglyLinkedList_short*,short*,size_t*);
extern void cutils_csll_SinglyLinkedList_short_print_default1(cutils_csll_SinglyLinkedList_short*);
/*----------------------------------------------------------------------------*/
typedef struct {} cutils_csll_SinglyLinkedList_unsigned_short;
typedef struct {} cutils_csll_SinglyLinkedList_unsigned_short_iterator;
extern bool cutils_csll_SinglyLinkedList_unsigned_short_new(cutils_csll_SinglyLinkedList_unsigned_short**,size_t,unsigned short*);
extern void(*cutils_csll_SinglyLinkedList_unsigned_short_del)(cutils_csll_SinglyLinkedList_unsigned_short*);
extern size_t(*cutils_csll_SinglyLinkedList_unsigned_short_len)(cutils_csll_SinglyLinkedList_unsigned_short*);
extern void(*cutils_csll_SinglyLinkedList_unsigned_short_truncate)(cutils_csll_SinglyLinkedList_unsigned_short*,size_t);
extern void(*cutils_csll_SinglyLinkedList_unsigned_short_clear)(cutils_csll_SinglyLinkedList_unsigned_short*);
extern cutils_csll_SinglyLinkedList_unsigned_short_iterator* cutils_csll_SinglyLinkedList_unsigned_short_iter(cutils_csll_SinglyLinkedList_unsigned_short*);
extern void cutils_csll_SinglyLinkedList_unsigned_short_iterator_del(cutils_csll_SinglyLinkedList_unsigned_short_iterator*);
extern bool cutils_csll_SinglyLinkedList_unsigned_short_iterator_next(cutils_csll_SinglyLinkedList_unsigned_short_iterator*,unsigned short**);
extern void cutils_csll_SinglyLinkedList_unsigned_short_iterator_pull(cutils_csll_SinglyLinkedList_unsigned_short_iterator*);
extern bool(*cutils_csll_SinglyLinkedList_unsigned_short_swap)(cutils_csll_SinglyLinkedList_unsigned_short*,size_t,size_t,size_t);
extern bool(*cutils_csll_SinglyLinkedList_unsigned_short_reverse)(cutils_csll_SinglyLinkedList_unsigned_short*);
extern bool cutils_csll_SinglyLinkedList_unsigned_short_append(cutils_csll_SinglyLinkedList_unsigned_short*,size_t,unsigned short*);
extern bool cutils_csll_SinglyLinkedList_unsigned_short_push(cutils_csll_SinglyLinkedList_unsigned_short*,size_t,size_t,unsigned short*);
extern size_t(*cutils_csll_SinglyLinkedList_unsigned_short_pull)(cutils_csll_SinglyLinkedList_unsigned_short*,size_t,size_t);
extern bool cutils_csll_SinglyLinkedList_unsigned_short_set(cutils_csll_SinglyLinkedList_unsigned_short*,size_t,size_t,unsigned short*);
extern bool cutils_csll_SinglyLinkedList_unsigned_short_pop(cutils_csll_SinglyLinkedList_unsigned_short*,size_t,size_t,unsigned short*);
extern unsigned short cutils_csll_SinglyLinkedList_unsigned_short_get(cutils_csll_SinglyLinkedList_unsigned_short*,size_t);
extern bool cutils_csll_SinglyLinkedList_unsigned_short_sub(cutils_csll_SinglyLinkedList_unsigned_short*,size_t,size_t,unsigned short*);
extern void(*cutils_csll_SinglyLinkedList_unsigned_short_map)(cutils_csll_SinglyLinkedList_unsigned_short*,size_t,size_t,void(*)());
extern bool cutils_csll_SinglyLinkedList_unsigned_short_find(cutils_csll_SinglyLinkedList_unsigned_short*,bool(*)(const void*,const void*,size_t),unsigned short*,size_t*);
extern size_t cutils_csll_SinglyLinkedList_unsigned_short_findall(cutils_csll_SinglyLinkedList_unsigned_short*,bool(*)(const void*,const void*,size_t),unsigned short*,size_t*);
extern void(*cutils_csll_SinglyLinkedList_unsigned_short_print)(cutils_csll_SinglyLinkedList_unsigned_short*,FILE*,const char*,bool(*)());
extern bool cutils_csll_SinglyLinkedList_unsigned_short_format(const unsigned short*,char**,size_t*);
extern bool cutils_csll_SinglyLinkedList_unsigned_short_compare(const void*,const void*,size_t);
extern bool cutils_csll_SinglyLinkedList_unsigned_short_new_default1(cutils_csll_SinglyLinkedList_unsigned_short**);
extern void cutils_csll_SinglyLinkedList_unsigned_short_truncate_default1(cutils_csll_SinglyLinkedList_unsigned_short*);
extern bool cutils_csll_SinglyLinkedList_unsigned_short_swap_default3(cutils_csll_SinglyLinkedList_unsigned_short*,size_t,size_t);
extern bool cutils_csll_SinglyLinkedList_unsigned_short_append_default2(cutils_csll_SinglyLinkedList_unsigned_short*,unsigned short*);
extern bool cutils_csll_SinglyLinkedList_unsigned_short_push_default3(cutils_csll_SinglyLinkedList_unsigned_short*,size_t,unsigned short*);
extern size_t cutils_csll_SinglyLinkedList_unsigned_short_pull_default2(cutils_csll_SinglyLinkedList_unsigned_short*,size_t);
extern bool cutils_csll_SinglyLinkedList_unsigned_short_set_default3(cutils_csll_SinglyLinkedList_unsigned_short*,size_t,unsigned short*);
extern bool cutils_csll_SinglyLinkedList_unsigned_short_pop_default3(cutils_csll_SinglyLinkedList_unsigned_short*,size_t,unsigned short*);
extern bool cutils_csll_SinglyLinkedList_unsigned_short_sub_default3(cutils_csll_SinglyLinkedList_unsigned_short*,size_t,unsigned short*);
extern void cutils_csll_SinglyLinkedList_unsigned_short_map_default3(cutils_csll_SinglyLinkedList_unsigned_short*,size_t,void(*)());
extern bool cutils_csll_SinglyLinkedList_unsigned_short_find_default3(cutils_csll_SinglyLinkedList_unsigned_short*,unsigned short*,size_t*);
extern size_t cutils_csll_SinglyLinkedList_unsigned_short_findall_default3(cutils_csll_SinglyLinkedList_unsigned_short*,unsigned short*,size_t*);
extern void cutils_csll_SinglyLinkedList_unsigned_short_print_default1(cutils_csll_SinglyLinkedList_unsigned_short*);
/*----------------------------------------------------------------------------*/
typedef struct {} cutils_csll_SinglyLinkedList_int;
typedef struct {} cutils_csll_SinglyLinkedList_int_iterator;
extern bool cutils_csll_SinglyLinkedList_int_new(cutils_csll_SinglyLinkedList_int**,size_t,int*);
extern void(*cutils_csll_SinglyLinkedList_int_del)(cutils_csll_SinglyLinkedList_int*);
extern size_t(*cutils_csll_SinglyLinkedList_int_len)(cutils_csll_SinglyLinkedList_int*);
extern void(*cutils_csll_SinglyLinkedList_int_truncate)(cutils_csll_SinglyLinkedList_int*,size_t);
extern void(*cutils_csll_SinglyLinkedList_int_clear)(cutils_csll_SinglyLinkedList_int*);
extern cutils_csll_SinglyLinkedList_int_iterator* cutils_csll_SinglyLinkedList_int_iter(cutils_csll_SinglyLinkedList_int*);
extern void cutils_csll_SinglyLinkedList_int_iterator_del(cutils_csll_SinglyLinkedList_int_iterator*);
extern bool cutils_csll_SinglyLinkedList_int_iterator_next(cutils_csll_SinglyLinkedList_int_iterator*,int**);
extern void cutils_csll_SinglyLinkedList_int_iterator_pull(cutils_csll_SinglyLinkedList_int_iterator*);
extern bool(*cutils_csll_SinglyLinkedList_int_swap)(cutils_csll_SinglyLinkedList_int*,size_t,size_t,size_t);
extern bool(*cutils_csll_SinglyLinkedList_int_reverse)(cutils_csll_SinglyLinkedList_int*);
extern bool cutils_csll_SinglyLinkedList_int_append(cutils_csll_SinglyLinkedList_int*,size_t,int*);
extern bool cutils_csll_SinglyLinkedList_int_push(cutils_csll_SinglyLinkedList_int*,size_t,size_t,int*);
extern size_t(*cutils_csll_SinglyLinkedList_int_pull)(cutils_csll_SinglyLinkedList_int*,size_t,size_t);
extern bool cutils_csll_SinglyLinkedList_int_set(cutils_csll_SinglyLinkedList_int*,size_t,size_t,int*);
extern bool cutils_csll_SinglyLinkedList_int_pop(cutils_csll_SinglyLinkedList_int*,size_t,size_t,int*);
extern int cutils_csll_SinglyLinkedList_int_get(cutils_csll_SinglyLinkedList_int*,size_t);
extern bool cutils_csll_SinglyLinkedList_int_sub(cutils_csll_SinglyLinkedList_int*,size_t,size_t,int*);
extern void(*cutils_csll_SinglyLinkedList_int_map)(cutils_csll_SinglyLinkedList_int*,size_t,size_t,void(*)());
extern bool cutils_csll_SinglyLinkedList_int_find(cutils_csll_SinglyLinkedList_int*,bool(*)(const void*,const void*,size_t),int*,size_t*);
extern size_t cutils_csll_SinglyLinkedList_int_findall(cutils_csll_SinglyLinkedList_int*,bool(*)(const void*,const void*,size_t),int*,size_t*);
extern void(*cutils_csll_SinglyLinkedList_int_print)(cutils_csll_SinglyLinkedList_int*,FILE*,const char*,bool(*)());
extern bool cutils_csll_SinglyLinkedList_int_format(const int*,char**,size_t*);
extern bool cutils_csll_SinglyLinkedList_int_compare(const void*,const void*,size_t);
extern bool cutils_csll_SinglyLinkedList_int_new_default1(cutils_csll_SinglyLinkedList_int**);
extern void cutils_csll_SinglyLinkedList_int_truncate_default1(cutils_csll_SinglyLinkedList_int*);
extern bool cutils_csll_SinglyLinkedList_int_swap_default3(cutils_csll_SinglyLinkedList_int*,size_t,size_t);
extern bool cutils_csll_SinglyLinkedList_int_append_default2(cutils_csll_SinglyLinkedList_int*,int*);
extern bool cutils_csll_SinglyLinkedList_int_push_default3(cutils_csll_SinglyLinkedList_int*,size_t,int*);
extern size_t cutils_csll_SinglyLinkedList_int_pull_default2(cutils_csll_SinglyLinkedList_int*,size_t);
extern bool cutils_csll_SinglyLinkedList_int_set_default3(cutils_csll_SinglyLinkedList_int*,size_t,int*);
extern bool cutils_csll_SinglyLinkedList_int_pop_default3(cutils_csll_SinglyLinkedList_int*,size_t,int*);
extern bool cutils_csll_SinglyLinkedList_int_sub_default3(cutils_csll_SinglyLinkedList_int*,size_t,int*);
extern void cutils_csll_SinglyLinkedList_int_map_default3(cutils_csll_SinglyLinkedList_int*,size_t,void(*)());
extern bool cutils_csll_SinglyLinkedList_int_find_default3(cutils_csll_SinglyLinkedList_int*,int*,size_t*);
extern size_t cutils_csll_SinglyLinkedList_int_findall_default3(cutils_csll_SinglyLinkedList_int*,int*,size_t*);
extern void cutils_csll_SinglyLinkedList_int_print_default1(cutils_csll_SinglyLinkedList_int*);
/*----------------------------------------------------------------------------*/
typedef struct {} cutils_csll_SinglyLinkedList_unsigned_int;
typedef struct {} cutils_csll_SinglyLinkedList_unsigned_int_iterator;
extern bool cutils_csll_SinglyLinkedList_unsigned_int_new(cutils_csll_SinglyLinkedList_unsigned_int**,size_t,unsigned int*);
extern void(*cutils_csll_SinglyLinkedList_unsigned_int_del)(cutils_csll_SinglyLinkedList_unsigned_int*);
extern size_t(*cutils_csll_SinglyLinkedList_unsigned_int_len)(cutils_csll_SinglyLinkedList_unsigned_int*);
extern void(*cutils_csll_SinglyLinkedList_unsigned_int_truncate)(cutils_csll_SinglyLinkedList_unsigned_int*,size_t);
extern void(*cutils_csll_SinglyLinkedList_unsigned_int_clear)(cutils_csll_SinglyLinkedList_unsigned_int*);
extern cutils_csll_SinglyLinkedList_unsigned_int_iterator* cutils_csll_SinglyLinkedList_unsigned_int_iter(cutils_csll_SinglyLinkedList_unsigned_int*);
extern void cutils_csll_SinglyLinkedList_unsigned_int_iterator_del(cutils_csll_SinglyLinkedList_unsigned_int_iterator*);
extern bool cutils_csll_SinglyLinkedList_unsigned_int_iterator_next(cutils_csll_SinglyLinkedList_unsigned_int_iterator*,unsigned int**);
extern void cutils_csll_SinglyLinkedList_unsigned_int_iterator_pull(cutils_csll_SinglyLinkedList_unsigned_int_iterator*);
extern bool(*cutils_csll_SinglyLinkedList_unsigned_int_swap)(cutils_csll_SinglyLinkedList_unsigned_int*,size_t,size_t,size_t);
extern bool(*cutils_csll_SinglyLinkedList_unsigned_int_reverse)(cutils_csll_SinglyLinkedList_unsigned_int*);
extern bool cutils_csll_SinglyLinkedList_unsigned_int_append(cutils_csll_SinglyLinkedList_unsigned_int*,size_t,unsigned int*);
extern bool cutils_csll_SinglyLinkedList_unsigned_int_push(cutils_csll_SinglyLinkedList_unsigned_int*,size_t,size_t,unsigned int*);
extern size_t(*cutils_csll_SinglyLinkedList_unsigned_int_pull)(cutils_csll_SinglyLinkedList_unsigned_int*,size_t,size_t);
extern bool cutils_csll_SinglyLinkedList_unsigned_int_set(cutils_csll_SinglyLinkedList_unsigned_int*,size_t,size_t,unsigned int*);
extern bool cutils_csll_SinglyLinkedList_unsigned_int_pop(cutils_csll_SinglyLinkedList_unsigned_int*,size_t,size_t,unsigned int*);
extern unsigned int cutils_csll_SinglyLinkedList_unsigned_int_get(cutils_csll_SinglyLinkedList_unsigned_int*,size_t);
extern bool cutils_csll_SinglyLinkedList_unsigned_int_sub(cutils_csll_SinglyLinkedList_unsigned_int*,size_t,size_t,unsigned int*);
extern void(*cutils_csll_SinglyLinkedList_unsigned_int_map)(cutils_csll_SinglyLinkedList_unsigned_int*,size_t,size_t,void(*)());
extern bool cutils_csll_SinglyLinkedList_unsigned_int_find(cutils_csll_SinglyLinkedList_unsigned_int*,bool(*)(const void*,const void*,size_t),unsigned int*,size_t*);
extern size_t cutils_csll_SinglyLinkedList_unsigned_int_findall(cutils_csll_SinglyLinkedList_unsigned_int*,bool(*)(const void*,const void*,size_t),unsigned int*,size_t*);
extern void(*cutils_csll_SinglyLinkedList_unsigned_int_print)(cutils_csll_SinglyLinkedList_unsigned_int*,FILE*,const char*,bool(*)());
extern bool cutils_csll_SinglyLinkedList_unsigned_int_format(const unsigned int*,char**,size_t*);
extern bool cutils_csll_SinglyLinkedList_unsigned_int_compare(const void*,const void*,size_t);
extern bool cutils_csll_SinglyLinkedList_unsigned_int_new_default1(cutils_csll_SinglyLinkedList_unsigned_int**);
extern void cutils_csll_SinglyLinkedList_unsigned_int_truncate_default1(cutils_csll_SinglyLinkedList_unsigned_int*);
extern bool cutils_csll_SinglyLinkedList_unsigned_int_swap_default3(cutils_csll_SinglyLinkedList_unsigned_int*,size_t,size_t);
extern bool cutils_csll_SinglyLinkedList_unsigned_int_append_default2(cutils_csll_SinglyLinkedList_unsigned_int*,unsigned int*);
extern bool cutils_csll_SinglyLinkedList_unsigned_int_push_default3(cutils_csll_SinglyLinkedList_unsigned_int*,size_t,unsigned int*);
extern size_t cutils_csll_SinglyLinkedList_unsigned_int_pull_default2(cutils_csll_SinglyLinkedList_unsigned_int*,size_t);
extern bool cutils_csll_SinglyLinkedList_unsigned_int_set_default3(cutils_csll_SinglyLinkedList_unsigned_int*,size_t,unsigned int*);
extern bool cutils_csll_SinglyLinkedList_unsigned_int_pop_default3(cutils_csll_SinglyLinkedList_unsigned_int*,size_t,unsigned int*);
extern bool cutils_csll_SinglyLinkedList_unsigned_int_sub_default3(cutils_csll_SinglyLinkedList_unsigned_int*,size_t,unsigned int*);
extern void cutils_csll_SinglyLinkedList_unsigned_int_map_default3(cutils_csll_SinglyLinkedList_unsigned_int*,size_t,void(*)());
extern bool cutils_csll_SinglyLinkedList_unsigned_int_find_default3(cutils_csll_SinglyLinkedList_unsigned_int*,unsigned int*,size_t*);
extern size_t cutils_csll_SinglyLinkedList_unsigned_int_findall_default3(cutils_csll_SinglyLinkedList_unsigned_int*,unsigned int*,size_t*);
extern void cutils_csll_SinglyLinkedList_unsigned_int_print_default1(cutils_csll_SinglyLinkedList_unsigned_int*);
/*----------------------------------------------------------------------------*/
typedef struct {} cutils_csll_SinglyLinkedList_long;
typedef struct {} cutils_csll_SinglyLinkedList_long_iterator;
extern bool cutils_csll_SinglyLinkedList_long_new(cutils_csll_SinglyLinkedList_long**,size_t,long*);
extern void(*cutils_csll_SinglyLinkedList_long_del)(cutils_csll_SinglyLinkedList_long*);
extern size_t(*cutils_csll_SinglyLinkedList_long_len)(cutils_csll_SinglyLinkedList_long*);
extern void(*cutils_csll_SinglyLinkedList_long_truncate)(cutils_csll_SinglyLinkedList_long*,size_t);
extern void(*cutils_csll_SinglyLinkedList_long_clear)(cutils_csll_SinglyLinkedList_long*);
extern cutils_csll_SinglyLinkedList_long_iterator* cutils_csll_SinglyLinkedList_long_iter(cutils_csll_SinglyLinkedList_long*);
extern void cutils_csll_SinglyLinkedList_long_iterator_del(cutils_csll_SinglyLinkedList_long_iterator*);
extern bool cutils_csll_SinglyLinkedList_long_iterator_next(cutils_csll_SinglyLinkedList_long_iterator*,long**);
extern void cutils_csll_SinglyLinkedList_long_iterator_pull(cutils_csll_SinglyLinkedList_long_iterator*);
extern bool(*cutils_csll_SinglyLinkedList_long_swap)(cutils_csll_SinglyLinkedList_long*,size_t,size_t,size_t);
extern bool(*cutils_csll_SinglyLinkedList_long_reverse)(cutils_csll_SinglyLinkedList_long*);
extern bool cutils_csll_SinglyLinkedList_long_append(cutils_csll_SinglyLinkedList_long*,size_t,long*);
extern bool cutils_csll_SinglyLinkedList_long_push(cutils_csll_SinglyLinkedList_long*,size_t,size_t,long*);
extern size_t(*cutils_csll_SinglyLinkedList_long_pull)(cutils_csll_SinglyLinkedList_long*,size_t,size_t);
extern bool cutils_csll_SinglyLinkedList_long_set(cutils_csll_SinglyLinkedList_long*,size_t,size_t,long*);
extern bool cutils_csll_SinglyLinkedList_long_pop(cutils_csll_SinglyLinkedList_long*,size_t,size_t,long*);
extern long cutils_csll_SinglyLinkedList_long_get(cutils_csll_SinglyLinkedList_long*,size_t);
extern bool cutils_csll_SinglyLinkedList_long_sub(cutils_csll_SinglyLinkedList_long*,size_t,size_t,long*);
extern void(*cutils_csll_SinglyLinkedList_long_map)(cutils_csll_SinglyLinkedList_long*,size_t,size_t,void(*)());
extern bool cutils_csll_SinglyLinkedList_long_find(cutils_csll_SinglyLinkedList_long*,bool(*)(const void*,const void*,size_t),long*,size_t*);
extern size_t cutils_csll_SinglyLinkedList_long_findall(cutils_csll_SinglyLinkedList_long*,bool(*)(const void*,const void*,size_t),long*,size_t*);
extern void(*cutils_csll_SinglyLinkedList_long_print)(cutils_csll_SinglyLinkedList_long*,FILE*,const char*,bool(*)());
extern bool cutils_csll_SinglyLinkedList_long_format(const long*,char**,size_t*);
extern bool cutils_csll_SinglyLinkedList_long_compare(const void*,const void*,size_t);
extern bool cutils_csll_SinglyLinkedList_long_new_default1(cutils_csll_SinglyLinkedList_long**);
extern void cutils_csll_SinglyLinkedList_long_truncate_default1(cutils_csll_SinglyLinkedList_long*);
extern bool cutils_csll_SinglyLinkedList_long_swap_default3(cutils_csll_SinglyLinkedList_long*,size_t,size_t);
extern bool cutils_csll_SinglyLinkedList_long_append_default2(cutils_csll_SinglyLinkedList_long*,long*);
extern bool cutils_csll_SinglyLinkedList_long_push_default3(cutils_csll_SinglyLinkedList_long*,size_t,long*);
extern size_t cutils_csll_SinglyLinkedList_long_pull_default2(cutils_csll_SinglyLinkedList_long*,size_t);
extern bool cutils_csll_SinglyLinkedList_long_set_default3(cutils_csll_SinglyLinkedList_long*,size_t,long*);
extern bool cutils_csll_SinglyLinkedList_long_pop_default3(cutils_csll_SinglyLinkedList_long*,size_t,long*);
extern bool cutils_csll_SinglyLinkedList_long_sub_default3(cutils_csll_SinglyLinkedList_long*,size_t,long*);
extern void cutils_csll_SinglyLinkedList_long_map_default3(cutils_csll_SinglyLinkedList_long*,size_t,void(*)());
extern bool cutils_csll_SinglyLinkedList_long_find_default3(cutils_csll_SinglyLinkedList_long*,long*,size_t*);
extern size_t cutils_csll_SinglyLinkedList_long_findall_default3(cutils_csll_SinglyLinkedList_long*,long*,size_t*);
extern void cutils_csll_SinglyLinkedList_long_print_default1(cutils_csll_SinglyLinkedList_long*);
/*----------------------------------------------------------------------------*/
typedef struct {} cutils_csll_SinglyLinkedList_unsigned_long;
typedef struct {} cutils_csll_SinglyLinkedList_unsigned_long_iterator;
extern bool cutils_csll_SinglyLinkedList_unsigned_long_new(cutils_csll_SinglyLinkedList_unsigned_long**,size_t,unsigned long*);
extern void(*cutils_csll_SinglyLinkedList_unsigned_long_del)(cutils_csll_SinglyLinkedList_unsigned_long*);
extern size_t(*cutils_csll_SinglyLinkedList_unsigned_long_len)(cutils_csll_SinglyLinkedList_unsigned_long*);
extern void(*cutils_csll_SinglyLinkedList_unsigned_long_truncate)(cutils_csll_SinglyLinkedList_unsigned_long*,size_t);
extern void(*cutils_csll_SinglyLinkedList_unsigned_long_clear)(cutils_csll_SinglyLinkedList_unsigned_long*);
extern cutils_csll_SinglyLinkedList_unsigned_long_iterator* cutils_csll_SinglyLinkedList_unsigned_long_iter(cutils_csll_SinglyLinkedList_unsigned_long*);
extern void cutils_csll_SinglyLinkedList_unsigned_long_iterator_del(cutils_csll_SinglyLinkedList_unsigned_long_iterator*);
extern bool cutils_csll_SinglyLinkedList_unsigned_long_iterator_next(cutils_csll_SinglyLinkedList_unsigned_long_iterator*,unsigned long**);
extern void cutils_csll_SinglyLinkedList_unsigned_long_iterator_pull(cutils_csll_SinglyLinkedList_unsigned_long_iterator*);
extern bool(*cutils_csll_SinglyLinkedList_unsigned_long_swap)(cutils_csll_SinglyLinkedList_unsigned_long*,size_t,size_t,size_t);
extern bool(*cutils_csll_SinglyLinkedList_unsigned_long_reverse)(cutils_csll_SinglyLinkedList_unsigned_long*);
extern bool cutils_csll_SinglyLinkedList_unsigned_long_append(cutils_csll_SinglyLinkedList_unsigned_long*,size_t,unsigned long*);
extern bool cutils_csll_SinglyLinkedList_unsigned_long_push(cutils_csll_SinglyLinkedList_unsigned_long*,size_t,size_t,unsigned long*);
extern size_t(*cutils_csll_SinglyLinkedList_unsigned_long_pull)(cutils_csll_SinglyLinkedList_unsigned_long*,size_t,size_t);
extern bool cutils_csll_SinglyLinkedList_unsigned_long_set(cutils_csll_SinglyLinkedList_unsigned_long*,size_t,size_t,unsigned long*);
extern bool cutils_csll_SinglyLinkedList_unsigned_long_pop(cutils_csll_SinglyLinkedList_unsigned_long*,size_t,size_t,unsigned long*);
extern unsigned long cutils_csll_SinglyLinkedList_unsigned_long_get(cutils_csll_SinglyLinkedList_unsigned_long*,size_t);
extern bool cutils_csll_SinglyLinkedList_unsigned_long_sub(cutils_csll_SinglyLinkedList_unsigned_long*,size_t,size_t,unsigned long*);
extern void(*cutils_csll_SinglyLinkedList_unsigned_long_map)(cutils_csll_SinglyLinkedList_unsigned_long*,size_t,size_t,void(*)());
extern bool cutils_csll_SinglyLinkedList_unsigned_long_find(cutils_csll_SinglyLinkedList_unsigned_long*,bool(*)(const void*,const void*,size_t),unsigned long*,size_t*);
extern size_t cutils_csll_SinglyLinkedList_unsigned_long_findall(cutils_csll_SinglyLinkedList_unsigned_long*,bool(*)(const void*,const void*,size_t),unsigned long*,size_t*);
extern void(*cutils_csll_SinglyLinkedList_unsigned_long_print)(cutils_csll_SinglyLinkedList_unsigned_long*,FILE*,const char*,bool(*)());
extern bool cutils_csll_SinglyLinkedList_unsigned_long_format(const unsigned long*,char**,size_t*);
extern bool cutils_csll_SinglyLinkedList_unsigned_long_compare(const void*,const void*,size_t);
extern bool cutils_csll_SinglyLinkedList_unsigned_long_new_default1(cutils_csll_SinglyLinkedList_unsigned_long**);
extern void cutils_csll_SinglyLinkedList_unsigned_long_truncate_default1(cutils_csll_SinglyLinkedList_unsigned_long*);
extern bool cutils_csll_SinglyLinkedList_unsigned_long_swap_default3(cutils_csll_SinglyLinkedList_unsigned_long*,size_t,size_t);
extern bool cutils_csll_SinglyLinkedList_unsigned_long_append_default2(cutils_csll_SinglyLinkedList_unsigned_long*,unsigned long*);
extern bool cutils_csll_SinglyLinkedList_unsigned_long_push_default3(cutils_csll_SinglyLinkedList_unsigned_long*,size_t,unsigned long*);
extern size_t cutils_csll_SinglyLinkedList_unsigned_long_pull_default2(cutils_csll_SinglyLinkedList_unsigned_long*,size_t);
extern bool cutils_csll_SinglyLinkedList_unsigned_long_set_default3(cutils_csll_SinglyLinkedList_unsigned_long*,size_t,unsigned long*);
extern bool cutils_csll_SinglyLinkedList_unsigned_long_pop_default3(cutils_csll_SinglyLinkedList_unsigned_long*,size_t,unsigned long*);
extern bool cutils_csll_SinglyLinkedList_unsigned_long_sub_default3(cutils_csll_SinglyLinkedList_unsigned_long*,size_t,unsigned long*);
extern void cutils_csll_SinglyLinkedList_unsigned_long_map_default3(cutils_csll_SinglyLinkedList_unsigned_long*,size_t,void(*)());
extern bool cutils_csll_SinglyLinkedList_unsigned_long_find_default3(cutils_csll_SinglyLinkedList_unsigned_long*,unsigned long*,size_t*);
extern size_t cutils_csll_SinglyLinkedList_unsigned_long_findall_default3(cutils_csll_SinglyLinkedList_unsigned_long*,unsigned long*,size_t*);
extern void cutils_csll_SinglyLinkedList_unsigned_long_print_default1(cutils_csll_SinglyLinkedList_unsigned_long*);
/*----------------------------------------------------------------------------*/
typedef struct {} cutils_csll_SinglyLinkedList_long_long;
typedef struct {} cutils_csll_SinglyLinkedList_long_long_iterator;
extern bool cutils_csll_SinglyLinkedList_long_long_new(cutils_csll_SinglyLinkedList_long_long**,size_t,long long*);
extern void(*cutils_csll_SinglyLinkedList_long_long_del)(cutils_csll_SinglyLinkedList_long_long*);
extern size_t(*cutils_csll_SinglyLinkedList_long_long_len)(cutils_csll_SinglyLinkedList_long_long*);
extern void(*cutils_csll_SinglyLinkedList_long_long_truncate)(cutils_csll_SinglyLinkedList_long_long*,size_t);
extern void(*cutils_csll_SinglyLinkedList_long_long_clear)(cutils_csll_SinglyLinkedList_long_long*);
extern cutils_csll_SinglyLinkedList_long_long_iterator* cutils_csll_SinglyLinkedList_long_long_iter(cutils_csll_SinglyLinkedList_long_long*);
extern void cutils_csll_SinglyLinkedList_long_long_iterator_del(cutils_csll_SinglyLinkedList_long_long_iterator*);
extern bool cutils_csll_SinglyLinkedList_long_long_iterator_next(cutils_csll_SinglyLinkedList_long_long_iterator*,long long**);
extern void cutils_csll_SinglyLinkedList_long_long_iterator_pull(cutils_csll_SinglyLinkedList_long_long_iterator*);
extern bool(*cutils_csll_SinglyLinkedList_long_long_swap)(cutils_csll_SinglyLinkedList_long_long*,size_t,size_t,size_t);
extern bool(*cutils_csll_SinglyLinkedList_long_long_reverse)(cutils_csll_SinglyLinkedList_long_long*);
extern bool cutils_csll_SinglyLinkedList_long_long_append(cutils_csll_SinglyLinkedList_long_long*,size_t,long long*);
extern bool cutils_csll_SinglyLinkedList_long_long_push(cutils_csll_SinglyLinkedList_long_long*,size_t,size_t,long long*);
extern size_t(*cutils_csll_SinglyLinkedList_long_long_pull)(cutils_csll_SinglyLinkedList_long_long*,size_t,size_t);
extern bool cutils_csll_SinglyLinkedList_long_long_set(cutils_csll_SinglyLinkedList_long_long*,size_t,size_t,long long*);
extern bool cutils_csll_SinglyLinkedList_long_long_pop(cutils_csll_SinglyLinkedList_long_long*,size_t,size_t,long long*);
extern long long cutils_csll_SinglyLinkedList_long_long_get(cutils_csll_SinglyLinkedList_long_long*,size_t);
extern bool cutils_csll_SinglyLinkedList_long_long_sub(cutils_csll_SinglyLinkedList_long_long*,size_t,size_t,long long*);
extern void(*cutils_csll_SinglyLinkedList_long_long_map)(cutils_csll_SinglyLinkedList_long_long*,size_t,size_t,void(*)());
extern bool cutils_csll_SinglyLinkedList_long_long_find(cutils_csll_SinglyLinkedList_long_long*,bool(*)(const void*,const void*,size_t),long long*,size_t*);
extern size_t cutils_csll_SinglyLinkedList_long_long_findall(cutils_csll_SinglyLinkedList_long_long*,bool(*)(const void*,const void*,size_t),long long*,size_t*);
extern void(*cutils_csll_SinglyLinkedList_long_long_print)(cutils_csll_SinglyLinkedList_long_long*,FILE*,const char*,bool(*)());
extern bool cutils_csll_SinglyLinkedList_long_long_format(const long long*,char**,size_t*);
extern bool cutils_csll_SinglyLinkedList_long_long_compare(const void*,const void*,size_t);
extern bool cutils_csll_SinglyLinkedList_long_long_new_default1(cutils_csll_SinglyLinkedList_long_long**);
extern void cutils_csll_SinglyLinkedList_long_long_truncate_default1(cutils_csll_SinglyLinkedList_long_long*);
extern bool cutils_csll_SinglyLinkedList_long_long_swap_default3(cutils_csll_SinglyLinkedList_long_long*,size_t,size_t);
extern bool cutils_csll_SinglyLinkedList_long_long_append_default2(cutils_csll_SinglyLinkedList_long_long*,long long*);
extern bool cutils_csll_SinglyLinkedList_long_long_push_default3(cutils_csll_SinglyLinkedList_long_long*,size_t,long long*);
extern size_t cutils_csll_SinglyLinkedList_long_long_pull_default2(cutils_csll_SinglyLinkedList_long_long*,size_t);
extern bool cutils_csll_SinglyLinkedList_long_long_set_default3(cutils_csll_SinglyLinkedList_long_long*,size_t,long long*);
extern bool cutils_csll_SinglyLinkedList_long_long_pop_default3(cutils_csll_SinglyLinkedList_long_long*,size_t,long long*);
extern bool cutils_csll_SinglyLinkedList_long_long_sub_default3(cutils_csll_SinglyLinkedList_long_long*,size_t,long long*);
extern void cutils_csll_SinglyLinkedList_long_long_map_default3(cutils_csll_SinglyLinkedList_long_long*,size_t,void(*)());
extern bool cutils_csll_SinglyLinkedList_long_long_find_default3(cutils_csll_SinglyLinkedList_long_long*,long long*,size_t*);
extern size_t cutils_csll_SinglyLinkedList_long_long_findall_default3(cutils_csll_SinglyLinkedList_long_long*,long long*,size_t*);
extern void cutils_csll_SinglyLinkedList_long_long_print_default1(cutils_csll_SinglyLinkedList_long_long*);
/*----------------------------------------------------------------------------*/
typedef struct {} cutils_csll_SinglyLinkedList_unsigned_long_long;
typedef struct {} cutils_csll_SinglyLinkedList_unsigned_long_long_iterator;
extern bool cutils_csll_SinglyLinkedList_unsigned_long_long_new(cutils_csll_SinglyLinkedList_unsigned_long_long**,size_t,unsigned long long*);
extern void(*cutils_csll_SinglyLinkedList_unsigned_long_long_del)(cutils_csll_SinglyLinkedList_unsigned_long_long*);
extern size_t(*cutils_csll_SinglyLinkedList_unsigned_long_long_len)(cutils_csll_SinglyLinkedList_unsigned_long_long*);
extern void(*cutils_csll_SinglyLinkedList_unsigned_long_long_truncate)(cutils_csll_SinglyLinkedList_unsigned_long_long*,size_t);
extern void(*cutils_csll_SinglyLinkedList_unsigned_long_long_clear)(cutils_csll_SinglyLinkedList_unsigned_long_long*);
extern cutils_csll_SinglyLinkedList_unsigned_long_long_iterator* cutils_csll_SinglyLinkedList_unsigned_long_long_iter(cutils_csll_SinglyLinkedList_unsigned_long_long*);
extern void cutils_csll_SinglyLinkedList_unsigned_long_long_iterator_del(cutils_csll_SinglyLinkedList_unsigned_long_long_iterator*);
extern bool cutils_csll_SinglyLinkedList_unsigned_long_long_iterator_next(cutils_csll_SinglyLinkedList_unsigned_long_long_iterator*,unsigned long long**);
extern void cutils_csll_SinglyLinkedList_unsigned_long_long_iterator_pull(cutils_csll_SinglyLinkedList_unsigned_long_long_iterator*);
extern bool(*cutils_csll_SinglyLinkedList_unsigned_long_long_swap)(cutils_csll_SinglyLinkedList_unsigned_long_long*,size_t,size_t,size_t);
extern bool(*cutils_csll_SinglyLinkedList_unsigned_long_long_reverse)(cutils_csll_SinglyLinkedList_unsigned_long_long*);
extern bool cutils_csll_SinglyLinkedList_unsigned_long_long_append(cutils_csll_SinglyLinkedList_unsigned_long_long*,size_t,unsigned long long*);
extern bool cutils_csll_SinglyLinkedList_unsigned_long_long_push(cutils_csll_SinglyLinkedList_unsigned_long_long*,size_t,size_t,unsigned long long*);
extern size_t(*cutils_csll_SinglyLinkedList_unsigned_long_long_pull)(cutils_csll_SinglyLinkedList_unsigned_long_long*,size_t,size_t);
extern bool cutils_csll_SinglyLinkedList_unsigned_long_long_set(cutils_csll_SinglyLinkedList_unsigned_long_long*,size_t,size_t,unsigned long long*);
extern bool cutils_csll_SinglyLinkedList_unsigned_long_long_pop(cutils_csll_SinglyLinkedList_unsigned_long_long*,size_t,size_t,unsigned long long*);
extern unsigned long long cutils_csll_SinglyLinkedList_unsigned_long_long_get(cutils_csll_SinglyLinkedList_unsigned_long_long*,size_t);
extern bool cutils_csll_SinglyLinkedList_unsigned_long_long_sub(cutils_csll_SinglyLinkedList_unsigned_long_long*,size_t,size_t,unsigned long long*);
extern void(*cutils_csll_SinglyLinkedList_unsigned_long_long_map)(cutils_csll_SinglyLinkedList_unsigned_long_long*,size_t,size_t,void(*)());
extern bool cutils_csll_SinglyLinkedList_unsigned_long_long_find(cutils_csll_SinglyLinkedList_unsigned_long_long*,bool(*)(const void*,const void*,size_t),unsigned long long*,size_t*);
extern size_t cutils_csll_SinglyLinkedList_unsigned_long_long_findall(cutils_csll_SinglyLinkedList_unsigned_long_long*,bool(*)(const void*,const void*,size_t),unsigned long long*,size_t*);
extern void(*cutils_csll_SinglyLinkedList_unsigned_long_long_print)(cutils_csll_SinglyLinkedList_unsigned_long_long*,FILE*,const char*,bool(*)());
extern bool cutils_csll_SinglyLinkedList_unsigned_long_long_format(const unsigned long long*,char**,size_t*);
extern bool cutils_csll_SinglyLinkedList_unsigned_long_long_compare(const void*,const void*,size_t);
extern bool cutils_csll_SinglyLinkedList_unsigned_long_long_new_default1(cutils_csll_SinglyLinkedList_unsigned_long_long**);
extern void cutils_csll_SinglyLinkedList_unsigned_long_long_truncate_default1(cutils_csll_SinglyLinkedList_unsigned_long_long*);
extern bool cutils_csll_SinglyLinkedList_unsigned_long_long_swap_default3(cutils_csll_SinglyLinkedList_unsigned_long_long*,size_t,size_t);
extern bool cutils_csll_SinglyLinkedList_unsigned_long_long_append_default2(cutils_csll_SinglyLinkedList_unsigned_long_long*,unsigned long long*);
extern bool cutils_csll_SinglyLinkedList_unsigned_long_long_push_default3(cutils_csll_SinglyLinkedList_unsigned_long_long*,size_t,unsigned long long*);
extern size_t cutils_csll_SinglyLinkedList_unsigned_long_long_pull_default2(cutils_csll_SinglyLinkedList_unsigned_long_long*,size_t);
extern bool cutils_csll_SinglyLinkedList_unsigned_long_long_set_default3(cutils_csll_SinglyLinkedList_unsigned_long_long*,size_t,unsigned long long*);
extern bool cutils_csll_SinglyLinkedList_unsigned_long_long_pop_default3(cutils_csll_SinglyLinkedList_unsigned_long_long*,size_t,unsigned long long*);
extern bool cutils_csll_SinglyLinkedList_unsigned_long_long_sub_default3(cutils_csll_SinglyLinkedList_unsigned_long_long*,size_t,unsigned long long*);
extern void cutils_csll_SinglyLinkedList_unsigned_long_long_map_default3(cutils_csll_SinglyLinkedList_unsigned_long_long*,size_t,void(*)());
extern bool cutils_csll_SinglyLinkedList_unsigned_long_long_find_default3(cutils_csll_SinglyLinkedList_unsigned_long_long*,unsigned long long*,size_t*);
extern size_t cutils_csll_SinglyLinkedList_unsigned_long_long_findall_default3(cutils_csll_SinglyLinkedList_unsigned_long_long*,unsigned long long*,size_t*);
extern void cutils_csll_SinglyLinkedList_unsigned_long_long_print_default1(cutils_csll_SinglyLinkedList_unsigned_long_long*);
/*----------------------------------------------------------------------------*/
typedef struct {} cutils_csll_SinglyLinkedList_float;
typedef struct {} cutils_csll_SinglyLinkedList_float_iterator;
extern bool cutils_csll_SinglyLinkedList_float_new(cutils_csll_SinglyLinkedList_float**,size_t,float*);
extern void(*cutils_csll_SinglyLinkedList_float_del)(cutils_csll_SinglyLinkedList_float*);
extern size_t(*cutils_csll_SinglyLinkedList_float_len)(cutils_csll_SinglyLinkedList_float*);
extern void(*cutils_csll_SinglyLinkedList_float_truncate)(cutils_csll_SinglyLinkedList_float*,size_t);
extern void(*cutils_csll_SinglyLinkedList_float_clear)(cutils_csll_SinglyLinkedList_float*);
extern cutils_csll_SinglyLinkedList_float_iterator* cutils_csll_SinglyLinkedList_float_iter(cutils_csll_SinglyLinkedList_float*);
extern void cutils_csll_SinglyLinkedList_float_iterator_del(cutils_csll_SinglyLinkedList_float_iterator*);
extern bool cutils_csll_SinglyLinkedList_float_iterator_next(cutils_csll_SinglyLinkedList_float_iterator*,float**);
extern void cutils_csll_SinglyLinkedList_float_iterator_pull(cutils_csll_SinglyLinkedList_float_iterator*);
extern bool(*cutils_csll_SinglyLinkedList_float_swap)(cutils_csll_SinglyLinkedList_float*,size_t,size_t,size_t);
extern bool(*cutils_csll_SinglyLinkedList_float_reverse)(cutils_csll_SinglyLinkedList_float*);
extern bool cutils_csll_SinglyLinkedList_float_append(cutils_csll_SinglyLinkedList_float*,size_t,float*);
extern bool cutils_csll_SinglyLinkedList_float_push(cutils_csll_SinglyLinkedList_float*,size_t,size_t,float*);
extern size_t(*cutils_csll_SinglyLinkedList_float_pull)(cutils_csll_SinglyLinkedList_float*,size_t,size_t);
extern bool cutils_csll_SinglyLinkedList_float_set(cutils_csll_SinglyLinkedList_float*,size_t,size_t,float*);
extern bool cutils_csll_SinglyLinkedList_float_pop(cutils_csll_SinglyLinkedList_float*,size_t,size_t,float*);
extern float cutils_csll_SinglyLinkedList_float_get(cutils_csll_SinglyLinkedList_float*,size_t);
extern bool cutils_csll_SinglyLinkedList_float_sub(cutils_csll_SinglyLinkedList_float*,size_t,size_t,float*);
extern void(*cutils_csll_SinglyLinkedList_float_map)(cutils_csll_SinglyLinkedList_float*,size_t,size_t,void(*)());
extern bool cutils_csll_SinglyLinkedList_float_find(cutils_csll_SinglyLinkedList_float*,bool(*)(const void*,const void*,size_t),float*,size_t*);
extern size_t cutils_csll_SinglyLinkedList_float_findall(cutils_csll_SinglyLinkedList_float*,bool(*)(const void*,const void*,size_t),float*,size_t*);
extern void(*cutils_csll_SinglyLinkedList_float_print)(cutils_csll_SinglyLinkedList_float*,FILE*,const char*,bool(*)());
extern bool cutils_csll_SinglyLinkedList_float_format(const float*,char**,size_t*);
extern bool cutils_csll_SinglyLinkedList_float_compare(const void*,const void*,size_t);
extern bool cutils_csll_SinglyLinkedList_float_new_default1(cutils_csll_SinglyLinkedList_float**);
extern void cutils_csll_SinglyLinkedList_float_truncate_default1(cutils_csll_SinglyLinkedList_float*);
extern bool cutils_csll_SinglyLinkedList_float_swap_default3(cutils_csll_SinglyLinkedList_float*,size_t,size_t);
extern bool cutils_csll_SinglyLinkedList_float_append_default2(cutils_csll_SinglyLinkedList_float*,float*);
extern bool cutils_csll_SinglyLinkedList_float_push_default3(cutils_csll_SinglyLinkedList_float*,size_t,float*);
extern size_t cutils_csll_SinglyLinkedList_float_pull_default2(cutils_csll_SinglyLinkedList_float*,size_t);
extern bool cutils_csll_SinglyLinkedList_float_set_default3(cutils_csll_SinglyLinkedList_float*,size_t,float*);
extern bool cutils_csll_SinglyLinkedList_float_pop_default3(cutils_csll_SinglyLinkedList_float*,size_t,float*);
extern bool cutils_csll_SinglyLinkedList_float_sub_default3(cutils_csll_SinglyLinkedList_float*,size_t,float*);
extern void cutils_csll_SinglyLinkedList_float_map_default3(cutils_csll_SinglyLinkedList_float*,size_t,void(*)());
extern bool cutils_csll_SinglyLinkedList_float_find_default3(cutils_csll_SinglyLinkedList_float*,float*,size_t*);
extern size_t cutils_csll_SinglyLinkedList_float_findall_default3(cutils_csll_SinglyLinkedList_float*,float*,size_t*);
extern void cutils_csll_SinglyLinkedList_float_print_default1(cutils_csll_SinglyLinkedList_float*);
/*----------------------------------------------------------------------------*/
typedef struct {} cutils_csll_SinglyLinkedList_double;
typedef struct {} cutils_csll_SinglyLinkedList_double_iterator;
extern bool cutils_csll_SinglyLinkedList_double_new(cutils_csll_SinglyLinkedList_double**,size_t,double*);
extern void(*cutils_csll_SinglyLinkedList_double_del)(cutils_csll_SinglyLinkedList_double*);
extern size_t(*cutils_csll_SinglyLinkedList_double_len)(cutils_csll_SinglyLinkedList_double*);
extern void(*cutils_csll_SinglyLinkedList_double_truncate)(cutils_csll_SinglyLinkedList_double*,size_t);
extern void(*cutils_csll_SinglyLinkedList_double_clear)(cutils_csll_SinglyLinkedList_double*);
extern cutils_csll_SinglyLinkedList_double_iterator* cutils_csll_SinglyLinkedList_double_iter(cutils_csll_SinglyLinkedList_double*);
extern void cutils_csll_SinglyLinkedList_double_iterator_del(cutils_csll_SinglyLinkedList_double_iterator*);
extern bool cutils_csll_SinglyLinkedList_double_iterator_next(cutils_csll_SinglyLinkedList_double_iterator*,double**);
extern void cutils_csll_SinglyLinkedList_double_iterator_pull(cutils_csll_SinglyLinkedList_double_iterator*);
extern bool(*cutils_csll_SinglyLinkedList_double_swap)(cutils_csll_SinglyLinkedList_double*,size_t,size_t,size_t);
extern bool(*cutils_csll_SinglyLinkedList_double_reverse)(cutils_csll_SinglyLinkedList_double*);
extern bool cutils_csll_SinglyLinkedList_double_append(cutils_csll_SinglyLinkedList_double*,size_t,double*);
extern bool cutils_csll_SinglyLinkedList_double_push(cutils_csll_SinglyLinkedList_double*,size_t,size_t,double*);
extern size_t(*cutils_csll_SinglyLinkedList_double_pull)(cutils_csll_SinglyLinkedList_double*,size_t,size_t);
extern bool cutils_csll_SinglyLinkedList_double_set(cutils_csll_SinglyLinkedList_double*,size_t,size_t,double*);
extern bool cutils_csll_SinglyLinkedList_double_pop(cutils_csll_SinglyLinkedList_double*,size_t,size_t,double*);
extern double cutils_csll_SinglyLinkedList_double_get(cutils_csll_SinglyLinkedList_double*,size_t);
extern bool cutils_csll_SinglyLinkedList_double_sub(cutils_csll_SinglyLinkedList_double*,size_t,size_t,double*);
extern void(*cutils_csll_SinglyLinkedList_double_map)(cutils_csll_SinglyLinkedList_double*,size_t,size_t,void(*)());
extern bool cutils_csll_SinglyLinkedList_double_find(cutils_csll_SinglyLinkedList_double*,bool(*)(const void*,const void*,size_t),double*,size_t*);
extern size_t cutils_csll_SinglyLinkedList_double_findall(cutils_csll_SinglyLinkedList_double*,bool(*)(const void*,const void*,size_t),double*,size_t*);
extern void(*cutils_csll_SinglyLinkedList_double_print)(cutils_csll_SinglyLinkedList_double*,FILE*,const char*,bool(*)());
extern bool cutils_csll_SinglyLinkedList_double_format(const double*,char**,size_t*);
extern bool cutils_csll_SinglyLinkedList_double_compare(const void*,const void*,size_t);
extern bool cutils_csll_SinglyLinkedList_double_new_default1(cutils_csll_SinglyLinkedList_double**);
extern void cutils_csll_SinglyLinkedList_double_truncate_default1(cutils_csll_SinglyLinkedList_double*);
extern bool cutils_csll_SinglyLinkedList_double_swap_default3(cutils_csll_SinglyLinkedList_double*,size_t,size_t);
extern bool cutils_csll_SinglyLinkedList_double_append_default2(cutils_csll_SinglyLinkedList_double*,double*);
extern bool cutils_csll_SinglyLinkedList_double_push_default3(cutils_csll_SinglyLinkedList_double*,size_t,double*);
extern size_t cutils_csll_SinglyLinkedList_double_pull_default2(cutils_csll_SinglyLinkedList_double*,size_t);
extern bool cutils_csll_SinglyLinkedList_double_set_default3(cutils_csll_SinglyLinkedList_double*,size_t,double*);
extern bool cutils_csll_SinglyLinkedList_double_pop_default3(cutils_csll_SinglyLinkedList_double*,size_t,double*);
extern bool cutils_csll_SinglyLinkedList_double_sub_default3(cutils_csll_SinglyLinkedList_double*,size_t,double*);
extern void cutils_csll_SinglyLinkedList_double_map_default3(cutils_csll_SinglyLinkedList_double*,size_t,void(*)());
extern bool cutils_csll_SinglyLinkedList_double_find_default3(cutils_csll_SinglyLinkedList_double*,double*,size_t*);
extern size_t cutils_csll_SinglyLinkedList_double_findall_default3(cutils_csll_SinglyLinkedList_double*,double*,size_t*);
extern void cutils_csll_SinglyLinkedList_double_print_default1(cutils_csll_SinglyLinkedList_double*);
/*----------------------------------------------------------------------------*/
typedef struct {} cutils_csll_SinglyLinkedList_long_double;
typedef struct {} cutils_csll_SinglyLinkedList_long_double_iterator;
extern bool cutils_csll_SinglyLinkedList_long_double_new(cutils_csll_SinglyLinkedList_long_double**,size_t,long double*);
extern void(*cutils_csll_SinglyLinkedList_long_double_del)(cutils_csll_SinglyLinkedList_long_double*);
extern size_t(*cutils_csll_SinglyLinkedList_long_double_len)(cutils_csll_SinglyLinkedList_long_double*);
extern void(*cutils_csll_SinglyLinkedList_long_double_truncate)(cutils_csll_SinglyLinkedList_long_double*,size_t);
extern void(*cutils_csll_SinglyLinkedList_long_double_clear)(cutils_csll_SinglyLinkedList_long_double*);
extern cutils_csll_SinglyLinkedList_long_double_iterator* cutils_csll_SinglyLinkedList_long_double_iter(cutils_csll_SinglyLinkedList_long_double*);
extern void cutils_csll_SinglyLinkedList_long_double_iterator_del(cutils_csll_SinglyLinkedList_long_double_iterator*);
extern bool cutils_csll_SinglyLinkedList_long_double_iterator_next(cutils_csll_SinglyLinkedList_long_double_iterator*,long double**);
extern void cutils_csll_SinglyLinkedList_long_double_iterator_pull(cutils_csll_SinglyLinkedList_long_double_iterator*);
extern bool(*cutils_csll_SinglyLinkedList_long_double_swap)(cutils_csll_SinglyLinkedList_long_double*,size_t,size_t,size_t);
extern bool(*cutils_csll_SinglyLinkedList_long_double_reverse)(cutils_csll_SinglyLinkedList_long_double*);
extern bool cutils_csll_SinglyLinkedList_long_double_append(cutils_csll_SinglyLinkedList_long_double*,size_t,long double*);
extern bool cutils_csll_SinglyLinkedList_long_double_push(cutils_csll_SinglyLinkedList_long_double*,size_t,size_t,long double*);
extern size_t(*cutils_csll_SinglyLinkedList_long_double_pull)(cutils_csll_SinglyLinkedList_long_double*,size_t,size_t);
extern bool cutils_csll_SinglyLinkedList_long_double_set(cutils_csll_SinglyLinkedList_long_double*,size_t,size_t,long double*);
extern bool cutils_csll_SinglyLinkedList_long_double_pop(cutils_csll_SinglyLinkedList_long_double*,size_t,size_t,long double*);
extern long double cutils_csll_SinglyLinkedList_long_double_get(cutils_csll_SinglyLinkedList_long_double*,size_t);
extern bool cutils_csll_SinglyLinkedList_long_double_sub(cutils_csll_SinglyLinkedList_long_double*,size_t,size_t,long double*);
extern void(*cutils_csll_SinglyLinkedList_long_double_map)(cutils_csll_SinglyLinkedList_long_double*,size_t,size_t,void(*)());
extern bool cutils_csll_SinglyLinkedList_long_double_find(cutils_csll_SinglyLinkedList_long_double*,bool(*)(const void*,const void*,size_t),long double*,size_t*);
extern size_t cutils_csll_SinglyLinkedList_long_double_findall(cutils_csll_SinglyLinkedList_long_double*,bool(*)(const void*,const void*,size_t),long double*,size_t*);
extern void(*cutils_csll_SinglyLinkedList_long_double_print)(cutils_csll_SinglyLinkedList_long_double*,FILE*,const char*,bool(*)());
extern bool cutils_csll_SinglyLinkedList_long_double_format(const long double*,char**,size_t*);
extern bool cutils_csll_SinglyLinkedList_long_double_compare(const void*,const void*,size_t);
extern bool cutils_csll_SinglyLinkedList_long_double_new_default1(cutils_csll_SinglyLinkedList_long_double**);
extern void cutils_csll_SinglyLinkedList_long_double_truncate_default1(cutils_csll_SinglyLinkedList_long_double*);
extern bool cutils_csll_SinglyLinkedList_long_double_swap_default3(cutils_csll_SinglyLinkedList_long_double*,size_t,size_t);
extern bool cutils_csll_SinglyLinkedList_long_double_append_default2(cutils_csll_SinglyLinkedList_long_double*,long double*);
extern bool cutils_csll_SinglyLinkedList_long_double_push_default3(cutils_csll_SinglyLinkedList_long_double*,size_t,long double*);
extern size_t cutils_csll_SinglyLinkedList_long_double_pull_default2(cutils_csll_SinglyLinkedList_long_double*,size_t);
extern bool cutils_csll_SinglyLinkedList_long_double_set_default3(cutils_csll_SinglyLinkedList_long_double*,size_t,long double*);
extern bool cutils_csll_SinglyLinkedList_long_double_pop_default3(cutils_csll_SinglyLinkedList_long_double*,size_t,long double*);
extern bool cutils_csll_SinglyLinkedList_long_double_sub_default3(cutils_csll_SinglyLinkedList_long_double*,size_t,long double*);
extern void cutils_csll_SinglyLinkedList_long_double_map_default3(cutils_csll_SinglyLinkedList_long_double*,size_t,void(*)());
extern bool cutils_csll_SinglyLinkedList_long_double_find_default3(cutils_csll_SinglyLinkedList_long_double*,long double*,size_t*);
extern size_t cutils_csll_SinglyLinkedList_long_double_findall_default3(cutils_csll_SinglyLinkedList_long_double*,long double*,size_t*);
extern void cutils_csll_SinglyLinkedList_long_double_print_default1(cutils_csll_SinglyLinkedList_long_double*);
/*----------------------------------------------------------------------------*/
typedef struct {} cutils_csll_SinglyLinkedList_bool;
typedef struct {} cutils_csll_SinglyLinkedList_bool_iterator;
extern bool cutils_csll_SinglyLinkedList_bool_new(cutils_csll_SinglyLinkedList_bool**,size_t,bool*);
extern void(*cutils_csll_SinglyLinkedList_bool_del)(cutils_csll_SinglyLinkedList_bool*);
extern size_t(*cutils_csll_SinglyLinkedList_bool_len)(cutils_csll_SinglyLinkedList_bool*);
extern void(*cutils_csll_SinglyLinkedList_bool_truncate)(cutils_csll_SinglyLinkedList_bool*,size_t);
extern void(*cutils_csll_SinglyLinkedList_bool_clear)(cutils_csll_SinglyLinkedList_bool*);
extern cutils_csll_SinglyLinkedList_bool_iterator* cutils_csll_SinglyLinkedList_bool_iter(cutils_csll_SinglyLinkedList_bool*);
extern void cutils_csll_SinglyLinkedList_bool_iterator_del(cutils_csll_SinglyLinkedList_bool_iterator*);
extern bool cutils_csll_SinglyLinkedList_bool_iterator_next(cutils_csll_SinglyLinkedList_bool_iterator*,bool**);
extern void cutils_csll_SinglyLinkedList_bool_iterator_pull(cutils_csll_SinglyLinkedList_bool_iterator*);
extern bool(*cutils_csll_SinglyLinkedList_bool_swap)(cutils_csll_SinglyLinkedList_bool*,size_t,size_t,size_t);
extern bool(*cutils_csll_SinglyLinkedList_bool_reverse)(cutils_csll_SinglyLinkedList_bool*);
extern bool cutils_csll_SinglyLinkedList_bool_append(cutils_csll_SinglyLinkedList_bool*,size_t,bool*);
extern bool cutils_csll_SinglyLinkedList_bool_push(cutils_csll_SinglyLinkedList_bool*,size_t,size_t,bool*);
extern size_t(*cutils_csll_SinglyLinkedList_bool_pull)(cutils_csll_SinglyLinkedList_bool*,size_t,size_t);
extern bool cutils_csll_SinglyLinkedList_bool_set(cutils_csll_SinglyLinkedList_bool*,size_t,size_t,bool*);
extern bool cutils_csll_SinglyLinkedList_bool_pop(cutils_csll_SinglyLinkedList_bool*,size_t,size_t,bool*);
extern bool cutils_csll_SinglyLinkedList_bool_get(cutils_csll_SinglyLinkedList_bool*,size_t);
extern bool cutils_csll_SinglyLinkedList_bool_sub(cutils_csll_SinglyLinkedList_bool*,size_t,size_t,bool*);
extern void(*cutils_csll_SinglyLinkedList_bool_map)(cutils_csll_SinglyLinkedList_bool*,size_t,size_t,void(*)());
extern bool cutils_csll_SinglyLinkedList_bool_find(cutils_csll_SinglyLinkedList_bool*,bool(*)(const void*,const void*,size_t),bool*,size_t*);
extern size_t cutils_csll_SinglyLinkedList_bool_findall(cutils_csll_SinglyLinkedList_bool*,bool(*)(const void*,const void*,size_t),bool*,size_t*);
extern void(*cutils_csll_SinglyLinkedList_bool_print)(cutils_csll_SinglyLinkedList_bool*,FILE*,const char*,bool(*)());
extern bool cutils_csll_SinglyLinkedList_bool_format(const bool*,char**,size_t*);
extern bool cutils_csll_SinglyLinkedList_bool_compare(const void*,const void*,size_t);
extern bool cutils_csll_SinglyLinkedList_bool_new_default1(cutils_csll_SinglyLinkedList_bool**);
extern void cutils_csll_SinglyLinkedList_bool_truncate_default1(cutils_csll_SinglyLinkedList_bool*);
extern bool cutils_csll_SinglyLinkedList_bool_swap_default3(cutils_csll_SinglyLinkedList_bool*,size_t,size_t);
extern bool cutils_csll_SinglyLinkedList_bool_append_default2(cutils_csll_SinglyLinkedList_bool*,bool*);
extern bool cutils_csll_SinglyLinkedList_bool_push_default3(cutils_csll_SinglyLinkedList_bool*,size_t,bool*);
extern size_t cutils_csll_SinglyLinkedList_bool_pull_default2(cutils_csll_SinglyLinkedList_bool*,size_t);
extern bool cutils_csll_SinglyLinkedList_bool_set_default3(cutils_csll_SinglyLinkedList_bool*,size_t,bool*);
extern bool cutils_csll_SinglyLinkedList_bool_pop_default3(cutils_csll_SinglyLinkedList_bool*,size_t,bool*);
extern bool cutils_csll_SinglyLinkedList_bool_sub_default3(cutils_csll_SinglyLinkedList_bool*,size_t,bool*);
extern void cutils_csll_SinglyLinkedList_bool_map_default3(cutils_csll_SinglyLinkedList_bool*,size_t,void(*)());
extern bool cutils_csll_SinglyLinkedList_bool_find_default3(cutils_csll_SinglyLinkedList_bool*,bool*,size_t*);
extern size_t cutils_csll_SinglyLinkedList_bool_findall_default3(cutils_csll_SinglyLinkedList_bool*,bool*,size_t*);
extern void cutils_csll_SinglyLinkedList_bool_print_default1(cutils_csll_SinglyLinkedList_bool*);
/*----------------------------------------------------------------------------*/
typedef struct {} cutils_csll_SinglyLinkedList_size_t;
typedef struct {} cutils_csll_SinglyLinkedList_size_t_iterator;
extern bool cutils_csll_SinglyLinkedList_size_t_new(cutils_csll_SinglyLinkedList_size_t**,size_t,size_t*);
extern void(*cutils_csll_SinglyLinkedList_size_t_del)(cutils_csll_SinglyLinkedList_size_t*);
extern size_t(*cutils_csll_SinglyLinkedList_size_t_len)(cutils_csll_SinglyLinkedList_size_t*);
extern void(*cutils_csll_SinglyLinkedList_size_t_truncate)(cutils_csll_SinglyLinkedList_size_t*,size_t);
extern void(*cutils_csll_SinglyLinkedList_size_t_clear)(cutils_csll_SinglyLinkedList_size_t*);
extern cutils_csll_SinglyLinkedList_size_t_iterator* cutils_csll_SinglyLinkedList_size_t_iter(cutils_csll_SinglyLinkedList_size_t*);
extern void cutils_csll_SinglyLinkedList_size_t_iterator_del(cutils_csll_SinglyLinkedList_size_t_iterator*);
extern bool cutils_csll_SinglyLinkedList_size_t_iterator_next(cutils_csll_SinglyLinkedList_size_t_iterator*,size_t**);
extern void cutils_csll_SinglyLinkedList_size_t_iterator_pull(cutils_csll_SinglyLinkedList_size_t_iterator*);
extern bool(*cutils_csll_SinglyLinkedList_size_t_swap)(cutils_csll_SinglyLinkedList_size_t*,size_t,size_t,size_t);
extern bool(*cutils_csll_SinglyLinkedList_size_t_reverse)(cutils_csll_SinglyLinkedList_size_t*);
extern bool cutils_csll_SinglyLinkedList_size_t_append(cutils_csll_SinglyLinkedList_size_t*,size_t,size_t*);
extern bool cutils_csll_SinglyLinkedList_size_t_push(cutils_csll_SinglyLinkedList_size_t*,size_t,size_t,size_t*);
extern size_t(*cutils_csll_SinglyLinkedList_size_t_pull)(cutils_csll_SinglyLinkedList_size_t*,size_t,size_t);
extern bool cutils_csll_SinglyLinkedList_size_t_set(cutils_csll_SinglyLinkedList_size_t*,size_t,size_t,size_t*);
extern bool cutils_csll_SinglyLinkedList_size_t_pop(cutils_csll_SinglyLinkedList_size_t*,size_t,size_t,size_t*);
extern size_t cutils_csll_SinglyLinkedList_size_t_get(cutils_csll_SinglyLinkedList_size_t*,size_t);
extern bool cutils_csll_SinglyLinkedList_size_t_sub(cutils_csll_SinglyLinkedList_size_t*,size_t,size_t,size_t*);
extern void(*cutils_csll_SinglyLinkedList_size_t_map)(cutils_csll_SinglyLinkedList_size_t*,size_t,size_t,void(*)());
extern bool cutils_csll_SinglyLinkedList_size_t_find(cutils_csll_SinglyLinkedList_size_t*,bool(*)(const void*,const void*,size_t),size_t*,size_t*);
extern size_t cutils_csll_SinglyLinkedList_size_t_findall(cutils_csll_SinglyLinkedList_size_t*,bool(*)(const void*,const void*,size_t),size_t*,size_t*);
extern void(*cutils_csll_SinglyLinkedList_size_t_print)(cutils_csll_SinglyLinkedList_size_t*,FILE*,const char*,bool(*)());
extern bool cutils_csll_SinglyLinkedList_size_t_format(const size_t*,char**,size_t*);
extern bool cutils_csll_SinglyLinkedList_size_t_compare(const void*,const void*,size_t);
extern bool cutils_csll_SinglyLinkedList_size_t_new_default1(cutils_csll_SinglyLinkedList_size_t**);
extern void cutils_csll_SinglyLinkedList_size_t_truncate_default1(cutils_csll_SinglyLinkedList_size_t*);
extern bool cutils_csll_SinglyLinkedList_size_t_swap_default3(cutils_csll_SinglyLinkedList_size_t*,size_t,size_t);
extern bool cutils_csll_SinglyLinkedList_size_t_append_default2(cutils_csll_SinglyLinkedList_size_t*,size_t*);
extern bool cutils_csll_SinglyLinkedList_size_t_push_default3(cutils_csll_SinglyLinkedList_size_t*,size_t,size_t*);
extern size_t cutils_csll_SinglyLinkedList_size_t_pull_default2(cutils_csll_SinglyLinkedList_size_t*,size_t);
extern bool cutils_csll_SinglyLinkedList_size_t_set_default3(cutils_csll_SinglyLinkedList_size_t*,size_t,size_t*);
extern bool cutils_csll_SinglyLinkedList_size_t_pop_default3(cutils_csll_SinglyLinkedList_size_t*,size_t,size_t*);
extern bool cutils_csll_SinglyLinkedList_size_t_sub_default3(cutils_csll_SinglyLinkedList_size_t*,size_t,size_t*);
extern void cutils_csll_SinglyLinkedList_size_t_map_default3(cutils_csll_SinglyLinkedList_size_t*,size_t,void(*)());
extern bool cutils_csll_SinglyLinkedList_size_t_find_default3(cutils_csll_SinglyLinkedList_size_t*,size_t*,size_t*);
extern size_t cutils_csll_SinglyLinkedList_size_t_findall_default3(cutils_csll_SinglyLinkedList_size_t*,size_t*,size_t*);
extern void cutils_csll_SinglyLinkedList_size_t_print_default1(cutils_csll_SinglyLinkedList_size_t*);
/*----------------------------------------------------------------------------*/
typedef struct {} cutils_csll_SinglyLinkedList_ptrdiff_t;
typedef struct {} cutils_csll_SinglyLinkedList_ptrdiff_t_iterator;
extern bool cutils_csll_SinglyLinkedList_ptrdiff_t_new(cutils_csll_SinglyLinkedList_ptrdiff_t**,size_t,ptrdiff_t*);
extern void(*cutils_csll_SinglyLinkedList_ptrdiff_t_del)(cutils_csll_SinglyLinkedList_ptrdiff_t*);
extern size_t(*cutils_csll_SinglyLinkedList_ptrdiff_t_len)(cutils_csll_SinglyLinkedList_ptrdiff_t*);
extern void(*cutils_csll_SinglyLinkedList_ptrdiff_t_truncate)(cutils_csll_SinglyLinkedList_ptrdiff_t*,size_t);
extern void(*cutils_csll_SinglyLinkedList_ptrdiff_t_clear)(cutils_csll_SinglyLinkedList_ptrdiff_t*);
extern cutils_csll_SinglyLinkedList_ptrdiff_t_iterator* cutils_csll_SinglyLinkedList_ptrdiff_t_iter(cutils_csll_SinglyLinkedList_ptrdiff_t*);
extern void cutils_csll_SinglyLinkedList_ptrdiff_t_iterator_del(cutils_csll_SinglyLinkedList_ptrdiff_t_iterator*);
extern bool cutils_csll_SinglyLinkedList_ptrdiff_t_iterator_next(cutils_csll_SinglyLinkedList_ptrdiff_t_iterator*,ptrdiff_t**);
extern void cutils_csll_SinglyLinkedList_ptrdiff_t_iterator_pull(cutils_csll_SinglyLinkedList_ptrdiff_t_iterator*);
extern bool(*cutils_csll_SinglyLinkedList_ptrdiff_t_swap)(cutils_csll_SinglyLinkedList_ptrdiff_t*,size_t,size_t,size_t);
extern bool(*cutils_csll_SinglyLinkedList_ptrdiff_t_reverse)(cutils_csll_SinglyLinkedList_ptrdiff_t*);
extern bool cutils_csll_SinglyLinkedList_ptrdiff_t_append(cutils_csll_SinglyLinkedList_ptrdiff_t*,size_t,ptrdiff_t*);
extern bool cutils_csll_SinglyLinkedList_ptrdiff_t_push(cutils_csll_SinglyLinkedList_ptrdiff_t*,size_t,size_t,ptrdiff_t*);
extern size_t(*cutils_csll_SinglyLinkedList_ptrdiff_t_pull)(cutils_csll_SinglyLinkedList_ptrdiff_t*,size_t,size_t);
extern bool cutils_csll_SinglyLinkedList_ptrdiff_t_set(cutils_csll_SinglyLinkedList_ptrdiff_t*,size_t,size_t,ptrdiff_t*);
extern bool cutils_csll_SinglyLinkedList_ptrdiff_t_pop(cutils_csll_SinglyLinkedList_ptrdiff_t*,size_t,size_t,ptrdiff_t*);
extern ptrdiff_t cutils_csll_SinglyLinkedList_ptrdiff_t_get(cutils_csll_SinglyLinkedList_ptrdiff_t*,size_t);
extern bool cutils_csll_SinglyLinkedList_ptrdiff_t_sub(cutils_csll_SinglyLinkedList_ptrdiff_t*,size_t,size_t,ptrdiff_t*);
extern void(*cutils_csll_SinglyLinkedList_ptrdiff_t_map)(cutils_csll_SinglyLinkedList_ptrdiff_t*,size_t,size_t,void(*)());
extern bool cutils_csll_SinglyLinkedList_ptrdiff_t_find(cutils_csll_SinglyLinkedList_ptrdiff_t*,bool(*)(const void*,const void*,size_t),ptrdiff_t*,size_t*);
extern size_t cutils_csll_SinglyLinkedList_ptrdiff_t_findall(cutils_csll_SinglyLinkedList_ptrdiff_t*,bool(*)(const void*,const void*,size_t),ptrdiff_t*,size_t*);
extern void(*cutils_csll_SinglyLinkedList_ptrdiff_t_print)(cutils_csll_SinglyLinkedList_ptrdiff_t*,FILE*,const char*,bool(*)());
extern bool cutils_csll_SinglyLinkedList_ptrdiff_t_format(const ptrdiff_t*,char**,size_t*);
extern bool cutils_csll_SinglyLinkedList_ptrdiff_t_compare(const void*,const void*,size_t);
extern bool cutils_csll_SinglyLinkedList_ptrdiff_t_new_default1(cutils_csll_SinglyLinkedList_ptrdiff_t**);
extern void cutils_csll_SinglyLinkedList_ptrdiff_t_truncate_default1(cutils_csll_SinglyLinkedList_ptrdiff_t*);
extern bool cutils_csll_SinglyLinkedList_ptrdiff_t_swap_default3(cutils_csll_SinglyLinkedList_ptrdiff_t*,size_t,size_t);
extern bool cutils_csll_SinglyLinkedList_ptrdiff_t_append_default2(cutils_csll_SinglyLinkedList_ptrdiff_t*,ptrdiff_t*);
extern bool cutils_csll_SinglyLinkedList_ptrdiff_t_push_default3(cutils_csll_SinglyLinkedList_ptrdiff_t*,size_t,ptrdiff_t*);
extern size_t cutils_csll_SinglyLinkedList_ptrdiff_t_pull_default2(cutils_csll_SinglyLinkedList_ptrdiff_t*,size_t);
extern bool cutils_csll_SinglyLinkedList_ptrdiff_t_set_default3(cutils_csll_SinglyLinkedList_ptrdiff_t*,size_t,ptrdiff_t*);
extern bool cutils_csll_SinglyLinkedList_ptrdiff_t_pop_default3(cutils_csll_SinglyLinkedList_ptrdiff_t*,size_t,ptrdiff_t*);
extern bool cutils_csll_SinglyLinkedList_ptrdiff_t_sub_default3(cutils_csll_SinglyLinkedList_ptrdiff_t*,size_t,ptrdiff_t*);
extern void cutils_csll_SinglyLinkedList_ptrdiff_t_map_default3(cutils_csll_SinglyLinkedList_ptrdiff_t*,size_t,void(*)());
extern bool cutils_csll_SinglyLinkedList_ptrdiff_t_find_default3(cutils_csll_SinglyLinkedList_ptrdiff_t*,ptrdiff_t*,size_t*);
extern size_t cutils_csll_SinglyLinkedList_ptrdiff_t_findall_default3(cutils_csll_SinglyLinkedList_ptrdiff_t*,ptrdiff_t*,size_t*);
extern void cutils_csll_SinglyLinkedList_ptrdiff_t_print_default1(cutils_csll_SinglyLinkedList_ptrdiff_t*);

#endif /* _C_SINGLY_LINKED_LIST_H_35118355245711974_ */
