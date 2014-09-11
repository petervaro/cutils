/* INFO ************************************************************************
**                                                                            **
**                                   cutils                                   **
**                                   ======                                   **
**                                                                            **
**                     Modern and Lightweight C Utilities                     **
**                       Version: 0.8.96.149 (20140907)                       **
**                                                                            **
**                                File: capi.h                                **
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

#ifndef _C_APPLICATION_PROGRAMMING_INTERFACE_H_27277619327951796_
#define _C_APPLICATION_PROGRAMMING_INTERFACE_H_27277619327951796_

#include <stdio.h>  /* stdout */
#include "carg.h"

/*----------------------------------------------------------------------------*/
/* Functions and methods called with default values */
#undef  __cutils_vargs_new
#define __cutils_vargs_new(...) cutils_carg_vargs(__VA_ARGS__)(5)(__VA_ARGS__,\
    /* 0 args */ __cutils_generic_new_args1,\
    /* 4 args */ __cutils_generic_new_args4,\
    /* 3 args */ __cutils_generic_new_args3,\
    /* 2 args */ __cutils_generic_new_args2,\
    /* 1 args */ __cutils_generic_new_args1)(__VA_ARGS__)

#undef  __cutils_vargs_truncate
#define __cutils_vargs_truncate(...) cutils_carg_vargs(__VA_ARGS__)(3)(__VA_ARGS__,\
    /* 0 args */ __cutils_generic_truncate_args1,\
    /* 2 args */ __cutils_generic_truncate_args2,\
    /* 1 args */ __cutils_generic_truncate_args1)(__VA_ARGS__)

#undef  __cutils_vargs_swap
#define __cutils_vargs_swap(...) cutils_carg_vargs(__VA_ARGS__)(5)(__VA_ARGS__,\
    /* 0 args */ __cutils_generic_swap_args3,\
    /* 4 args */ __cutils_generic_swap_args4,\
    /* 3 args */ __cutils_generic_swap_args3,\
    /* 2 args */ __cutils_generic_swap_args3,\
    /* 1 args */ __cutils_generic_swap_args3)(__VA_ARGS__)

#undef  __cutils_vargs_append
#define __cutils_vargs_append(...) cutils_carg_vargs(__VA_ARGS__)(5)(__VA_ARGS__,\
    /* 0 args */ __cutils_generic_append_args2,\
    /* 4 args */ __cutils_generic_append_args4,\
    /* 3 args */ __cutils_generic_append_args3,\
    /* 2 args */ __cutils_generic_append_args2,\
    /* 1 args */ __cutils_generic_append_args2)(__VA_ARGS__)

#undef  __cutils_vargs_add
#define __cutils_vargs_add(...) cutils_carg_vargs(__VA_ARGS__)(6)(__VA_ARGS__,\
    /* 0 args */ __cutils_generic_add_args4,\
    /* 5 args */ __cutils_generic_add_args5,\
    /* 4 args */ __cutils_generic_add_args4,\
    /* 3 args */ __cutils_generic_add_args4,\
    /* 2 args */ __cutils_generic_add_args4,\
    /* 1 args */ __cutils_generic_add_args4)(__VA_ARGS__)

#undef  __cutils_vargs_push
#define __cutils_vargs_push(...) cutils_carg_vargs(__VA_ARGS__)(6)(__VA_ARGS__,\
    /* 0 args */ __cutils_generic_push_args3,\
    /* 5 args */ __cutils_generic_push_args5,\
    /* 4 args */ __cutils_generic_push_args4,\
    /* 3 args */ __cutils_generic_push_args3,\
    /* 2 args */ __cutils_generic_push_args3,\
    /* 1 args */ __cutils_generic_push_args3)(__VA_ARGS__)

#undef  __cutils_vargs_pull
#define __cutils_vargs_pull(...) cutils_carg_vargs(__VA_ARGS__)(4)(__VA_ARGS__,\
    /* 0 args */ __cutils_generic_pull_args1,\
    /* 3 args */ __cutils_generic_pull_args3,\
    /* 2 args */ __cutils_generic_pull_args2,\
    /* 1 args */ __cutils_generic_pull_args1)(__VA_ARGS__)

#undef  __cutils_vargs_set
#define __cutils_vargs_set(...) cutils_carg_vargs(__VA_ARGS__)(6)(__VA_ARGS__,\
    /* 0 args */ __cutils_generic_set_args3,\
    /* 5 args */ __cutils_generic_set_args5,\
    /* 4 args */ __cutils_generic_set_args4,\
    /* 3 args */ __cutils_generic_set_args3,\
    /* 2 args */ __cutils_generic_set_args3,\
    /* 1 args */ __cutils_generic_set_args3)(__VA_ARGS__)

// #undef  __cutils_vargs_get
// #define __cutils_vargs_get(...) cutils_carg_vargs(__VA_ARGS__)(5)(__VA_ARGS__,\
    /* 0 args */ __cutils_generic_get_args2,\
    /* 4 args */ __cutils_generic_get_args4,\
    /* 3 args */ __cutils_generic_get_args3,\
    /* 2 args */ __cutils_generic_get_args2,\
    /* 1 args */ __cutils_generic_get_args2)(__VA_ARGS__)

#undef  __cutils_vargs_pop
#define __cutils_vargs_pop(...) cutils_carg_vargs(__VA_ARGS__)(6)(__VA_ARGS__,\
    /* 0 args */ __cutils_generic_pop_args3,\
    /* 5 args */ __cutils_generic_pop_args5,\
    /* 4 args */ __cutils_generic_pop_args4,\
    /* 3 args */ __cutils_generic_pop_args3,\
    /* 2 args */ __cutils_generic_pop_args3,\
    /* 1 args */ __cutils_generic_pop_args3)(__VA_ARGS__)

#undef  __cutils_vargs_sub
#define __cutils_vargs_sub(...) cutils_carg_vargs(__VA_ARGS__)(6)(__VA_ARGS__,\
    /* 0 args */ __cutils_generic_sub_args3,\
    /* 5 args */ __cutils_generic_sub_args5,\
    /* 4 args */ __cutils_generic_sub_args4,\
    /* 3 args */ __cutils_generic_sub_args3,\
    /* 2 args */ __cutils_generic_sub_args3,\
    /* 1 args */ __cutils_generic_sub_args3)(__VA_ARGS__)

#undef  __cutils_vargs_map
#define __cutils_vargs_map(...) cutils_carg_vargs(__VA_ARGS__)(5)(__VA_ARGS__,\
    /* 0 args */ __cutils_generic_map_args3,\
    /* 4 args */ __cutils_generic_map_args4,\
    /* 3 args */ __cutils_generic_map_args3,\
    /* 2 args */ __cutils_generic_map_args3,\
    /* 1 args */ __cutils_generic_map_args3)(__VA_ARGS__)

#undef  __cutils_vargs_find
#define __cutils_vargs_find(...) cutils_carg_vargs(__VA_ARGS__)(6)(__VA_ARGS__, \
    /* 0 args */ __cutils_generic_find_args3,\
    /* 4 args */ __cutils_generic_find_args5,\
    /* 4 args */ __cutils_generic_find_args4,\
    /* 3 args */ __cutils_generic_find_args3,\
    /* 2 args */ __cutils_generic_find_args3,\
    /* 1 args */ __cutils_generic_find_args3)(__VA_ARGS__)

#undef  __cutils_vargs_findall
#define __cutils_vargs_findall(...) cutils_carg_vargs(__VA_ARGS__)(6)(__VA_ARGS__, \
    /* 0 args */ __cutils_generic_findall_args3,\
    /* 4 args */ __cutils_generic_findall_args5,\
    /* 4 args */ __cutils_generic_findall_args4,\
    /* 3 args */ __cutils_generic_findall_args3,\
    /* 2 args */ __cutils_generic_findall_args3,\
    /* 1 args */ __cutils_generic_findall_args3)(__VA_ARGS__)

#undef  __cutils_vargs_print
#define __cutils_vargs_print(...) cutils_carg_vargs(__VA_ARGS__)(5)(__VA_ARGS__, \
    /* 0 args */ __cutils_generic_print_args1,\
    /* 4 args */ __cutils_generic_print_args4,\
    /* 3 args */ __cutils_generic_print_args2,\
    /* 2 args */ __cutils_generic_print_args2,\
    /* 1 args */ __cutils_generic_print_args1)(__VA_ARGS__)



/*----------------------------------------------------------------------------*/
#ifndef CUTILS_NAMESPACE /* use bare token names */

#undef new
#undef data
#undef raw
#undef append
#undef push
#undef set
#undef pop
#undef sub
#undef get
#undef iter
#undef next
#undef keys
#undef values
#undef items
#undef find
#undef findall
#undef del
#undef len
#undef size
#undef resize
#undef swap
#undef reverse
#undef pull
#undef truncate
#undef clear
#undef map
#undef print

#define new(...) __cutils_vargs_new(__VA_ARGS__)
#define data(...) __cutils_generic_data(__VA_ARGS__)
#define raw(...) __cutils_generic_raw(__VA_ARGS__)
#define append(...) __cutils_vargs_append(__VA_ARGS__)
#define add(...) __cutils_vargs_add(__VA_ARGS__)
#define push(...) __cutils_vargs_push(__VA_ARGS__)
#define set(...) __cutils_vargs_set(__VA_ARGS__)
#define pop(...) __cutils_vargs_pop(__VA_ARGS__)
#define sub(...) __cutils_vargs_sub(__VA_ARGS__)
#define get(...) __cutils_generic_get(__VA_ARGS__)
#define iter(...) __cutils_generic_iter(__VA_ARGS__)
#define next(...) __cutils_generic_next(__VA_ARGS__)
#define values(...) __cutils_generic_values(__VA_ARGS__)
#define items(...) __cutils_generic_items(__VA_ARGS__)
#define find(...) __cutils_vargs_find(__VA_ARGS__)
#define findall(...) __cutils_vargs_findall(__VA_ARGS__)
#define del(...) __cutils_generic_del(__VA_ARGS__)
#define len(...) __cutils_generic_len(__VA_ARGS__)
#define size(...) __cutils_generic_size(__VA_ARGS__)
#define resize(...) __cutils_generic_resize(__VA_ARGS__)
#define swap(...) __cutils_vargs_swap(__VA_ARGS__)
#define reverse(...) __cutils_generic_reverse(__VA_ARGS__)
#define pull(...) __cutils_vargs_pull(__VA_ARGS__)
#define truncate(...) __cutils_vargs_truncate(__VA_ARGS__)
#define clear(...) __cutils_generic_clear(__VA_ARGS__)
#define map(...) __cutils_vargs_map(__VA_ARGS__)
#define print(...) __cutils_vargs_print(__VA_ARGS__)

/* Macro-aliases */
#define keys(...) __cutils_generic_next(__VA_ARGS__)

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* C Arguments */
#undef zero
#undef vargs
#define zero(...) cutils_carg_zero(__VA_ARGS__)
#define vargs(...) cutils_carg_vargs(__VA_ARGS__)

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* C Debug */
#undef debug
#undef boolean
#define debug(...) cutils_cbug_debug(__VA_ARGS__)
#define boolean(...) cutils_cbug_boolean(__VA_ARGS__)

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* C FRame Per Second */
#undef getfps
#undef printfps
#define getfps(...) cutils_cfps_getfps(__VA_ARGS__)
#define printfps(...) cutils_cfps_printfps(__VA_ARGS__)

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* C Profile */
#undef  profile
#define profile(...) cutils_cpro_profile(__VA_ARGS__)

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* C Exceptions */
#undef start_exception_handling
#undef stop_exception_handling
#undef set_exception_handling_pointer
#undef set_exception_handling_custom_raise
#undef set_exception_handling_custom_catch
#undef raise
#undef catch
#undef craise
#undef ccatch

#define start_exception_handling(...) \
    cutils_cexc_start_exception_handling(__VA_ARGS__)
#define stop_exception_handling(...) \
    cutils_cexc_stop_exception_handling(__VA_ARGS__)
#define set_exception_handling_pointer(...) \
    cutils_cexc_set_exception_handling_pointer(__VA_ARGS__)
#define set_exception_handling_custom_raise(...) \
    cutils_cexc_set_exception_handling_custom_raise(__VA_ARGS__)
#define set_exception_handling_custom_catch(...) \
    cutils_cexc_set_exception_handling_custom_catch(__VA_ARGS__)
#define raise(...) cutils_cexc_raise(__VA_ARGS__)
#define catch(...) cutils_cexc_catch(__VA_ARGS__)
#define craise(...) cutils_cexc_craise(__VA_ARGS__)
#define ccatch(...) cutils_cexc_ccatch(__VA_ARGS__)

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* C Unit Test */
typedef cutils_cutt_Tester Tester;
#undef try
#undef report
#define try(...) cutils_cutt_Tester_try(__VA_ARGS__)
#define report(...) cutils_cutt_Tester_report(__VA_ARGS__)

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* C Dynamic Array */
  /* Base types */
typedef cutils_cdar_DynamicArray_void_ptr DynamicArray_void_ptr;
typedef cutils_cdar_DynamicArray_char DynamicArray_char;
typedef cutils_cdar_DynamicArray_signed_char DynamicArray_signed_char;
typedef cutils_cdar_DynamicArray_unsigned_char DynamicArray_unsigned_char;
typedef cutils_cdar_DynamicArray_char_ptr DynamicArray_char_ptr;
typedef cutils_cdar_DynamicArray_short DynamicArray_short;
typedef cutils_cdar_DynamicArray_unsigned_short DynamicArray_unsigned_short;
typedef cutils_cdar_DynamicArray_int DynamicArray_int;
typedef cutils_cdar_DynamicArray_unsigned_int DynamicArray_unsigned_int;
typedef cutils_cdar_DynamicArray_long DynamicArray_long;
typedef cutils_cdar_DynamicArray_unsigned_long DynamicArray_unsigned_long;
typedef cutils_cdar_DynamicArray_long_long DynamicArray_long_long;
typedef cutils_cdar_DynamicArray_unsigned_long_long DynamicArray_unsigned_long_long;
typedef cutils_cdar_DynamicArray_float DynamicArray_float;
typedef cutils_cdar_DynamicArray_double DynamicArray_double;
typedef cutils_cdar_DynamicArray_long_double DynamicArray_long_double;
typedef cutils_cdar_DynamicArray_bool DynamicArray_bool;
typedef cutils_cdar_DynamicArray_size_t DynamicArray_size_t;
typedef cutils_cdar_DynamicArray_ptrdiff_t DynamicArray_ptrdiff_t;

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* C Singly Linked List */
/* Base types */
typedef cutils_csll_SinglyLinkedList_void_ptr SinglyLinkedList_void_ptr;
typedef cutils_csll_SinglyLinkedList_char SinglyLinkedList_char;
typedef cutils_csll_SinglyLinkedList_signed_char SinglyLinkedList_signed_char;
typedef cutils_csll_SinglyLinkedList_unsigned_char SinglyLinkedList_unsigned_char;
typedef cutils_csll_SinglyLinkedList_char_ptr SinglyLinkedList_char_ptr;
typedef cutils_csll_SinglyLinkedList_short SinglyLinkedList_short;
typedef cutils_csll_SinglyLinkedList_unsigned_short SinglyLinkedList_unsigned_short;
typedef cutils_csll_SinglyLinkedList_int SinglyLinkedList_int;
typedef cutils_csll_SinglyLinkedList_unsigned_int SinglyLinkedList_unsigned_int;
typedef cutils_csll_SinglyLinkedList_long SinglyLinkedList_long;
typedef cutils_csll_SinglyLinkedList_unsigned_long SinglyLinkedList_unsigned_long;
typedef cutils_csll_SinglyLinkedList_long_long SinglyLinkedList_long_long;
typedef cutils_csll_SinglyLinkedList_unsigned_long_long SinglyLinkedList_unsigned_long_long;
typedef cutils_csll_SinglyLinkedList_float SinglyLinkedList_float;
typedef cutils_csll_SinglyLinkedList_double SinglyLinkedList_double;
typedef cutils_csll_SinglyLinkedList_long_double SinglyLinkedList_long_double;
typedef cutils_csll_SinglyLinkedList_bool SinglyLinkedList_bool;
typedef cutils_csll_SinglyLinkedList_size_t SinglyLinkedList_size_t;
typedef cutils_csll_SinglyLinkedList_ptrdiff_t SinglyLinkedList_ptrdiff_t;
/* Support types */
typedef cutils_csll_SinglyLinkedList_void_ptr_iterator SinglyLinkedList_void_ptr_iterator;
typedef cutils_csll_SinglyLinkedList_char_iterator SinglyLinkedList_char_iterator;
typedef cutils_csll_SinglyLinkedList_signed_char_iterator SinglyLinkedList_signed_char_iterator;
typedef cutils_csll_SinglyLinkedList_unsigned_char_iterator SinglyLinkedList_unsigned_char_iterator;
typedef cutils_csll_SinglyLinkedList_char_ptr_iterator SinglyLinkedList_char_ptr_iterator;
typedef cutils_csll_SinglyLinkedList_short_iterator SinglyLinkedList_short_iterator;
typedef cutils_csll_SinglyLinkedList_unsigned_short_iterator SinglyLinkedList_unsigned_short_iterator;
typedef cutils_csll_SinglyLinkedList_int_iterator SinglyLinkedList_int_iterator;
typedef cutils_csll_SinglyLinkedList_unsigned_int_iterator SinglyLinkedList_unsigned_int_iterator;
typedef cutils_csll_SinglyLinkedList_long_iterator SinglyLinkedList_long_iterator;
typedef cutils_csll_SinglyLinkedList_unsigned_long_iterator SinglyLinkedList_unsigned_long_iterator;
typedef cutils_csll_SinglyLinkedList_long_long_iterator SinglyLinkedList_long_long_iterator;
typedef cutils_csll_SinglyLinkedList_unsigned_long_long_iterator SinglyLinkedList_unsigned_long_long_iterator;
typedef cutils_csll_SinglyLinkedList_float_iterator SinglyLinkedList_float_iterator;
typedef cutils_csll_SinglyLinkedList_double_iterator SinglyLinkedList_double_iterator;
typedef cutils_csll_SinglyLinkedList_long_double_iterator SinglyLinkedList_long_double_iterator;
typedef cutils_csll_SinglyLinkedList_bool_iterator SinglyLinkedList_bool_iterator;
typedef cutils_csll_SinglyLinkedList_size_t_iterator SinglyLinkedList_size_t_iterator;
typedef cutils_csll_SinglyLinkedList_ptrdiff_t_iterator SinglyLinkedList_ptrdiff_t_iterator;

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* C Static Hash Map */
/*
typedef cutils_cshm_StaticHashMap_void_ptr StaticHashMap_void_ptr;
typedef cutils_cshm_StaticHashMap_char StaticHashMap_char;
typedef cutils_cshm_StaticHashMap_signed_char StaticHashMap_signed_char;
typedef cutils_cshm_StaticHashMap_unsigned_char StaticHashMap_unsigned_char;
typedef cutils_cshm_StaticHashMap_char_ptr StaticHashMap_char_ptr;
typedef cutils_cshm_StaticHashMap_short StaticHashMap_short;
typedef cutils_cshm_StaticHashMap_unsigned_short StaticHashMap_unsigned_short;
typedef cutils_cshm_StaticHashMap_int StaticHashMap_int;
typedef cutils_cshm_StaticHashMap_unsigned_int StaticHashMap_unsigned_int;
typedef cutils_cshm_StaticHashMap_long StaticHashMap_long;
typedef cutils_cshm_StaticHashMap_unsigned_long StaticHashMap_unsigned_long;
typedef cutils_cshm_StaticHashMap_long_long StaticHashMap_long_long;
typedef cutils_cshm_StaticHashMap_unsigned_long_long StaticHashMap_unsigned_long_long;
typedef cutils_cshm_StaticHashMap_float StaticHashMap_float;
typedef cutils_cshm_StaticHashMap_double StaticHashMap_double;
typedef cutils_cshm_StaticHashMap_long_double StaticHashMap_long_double;
typedef cutils_cshm_StaticHashMap_bool StaticHashMap_bool;
typedef cutils_cshm_StaticHashMap_size_t StaticHashMap_size_t;
typedef cutils_cshm_StaticHashMap_ptrdiff_t StaticHashMap_ptrdiff_t;

typedef cutils_cshm_StaticHashMap_void_ptr_iterator StaticHashMap_void_ptr_iterator;
typedef cutils_cshm_StaticHashMap_char_iterator StaticHashMap_char_iterator;
typedef cutils_cshm_StaticHashMap_signed_char_iterator StaticHashMap_signed_char_iterator;
typedef cutils_cshm_StaticHashMap_unsigned_char_iterator StaticHashMap_unsigned_char_iterator;
typedef cutils_cshm_StaticHashMap_char_ptr_iterator StaticHashMap_char_ptr_iterator;
typedef cutils_cshm_StaticHashMap_short_iterator StaticHashMap_short_iterator;
typedef cutils_cshm_StaticHashMap_unsigned_short_iterator StaticHashMap_unsigned_short_iterator;
typedef cutils_cshm_StaticHashMap_int_iterator StaticHashMap_int_iterator;
typedef cutils_cshm_StaticHashMap_unsigned_int_iterator StaticHashMap_unsigned_int_iterator;
typedef cutils_cshm_StaticHashMap_long_iterator StaticHashMap_long_iterator;
typedef cutils_cshm_StaticHashMap_unsigned_long_iterator StaticHashMap_unsigned_long_iterator;
typedef cutils_cshm_StaticHashMap_long_long_iterator StaticHashMap_long_long_iterator;
typedef cutils_cshm_StaticHashMap_unsigned_long_long_iterator StaticHashMap_unsigned_long_long_iterator;
typedef cutils_cshm_StaticHashMap_float_iterator StaticHashMap_float_iterator;
typedef cutils_cshm_StaticHashMap_double_iterator StaticHashMap_double_iterator;
typedef cutils_cshm_StaticHashMap_long_double_iterator StaticHashMap_long_double_iterator;
typedef cutils_cshm_StaticHashMap_bool_iterator StaticHashMap_bool_iterator;
typedef cutils_cshm_StaticHashMap_size_t_iterator StaticHashMap_size_t_iterator;
typedef cutils_cshm_StaticHashMap_ptrdiff_t_iterator StaticHashMap_ptrdiff_t_iterator;
*/

/*----------------------------------------------------------------------------*/
#else /* use prefixed token names */

#undef cutils_new
#undef cutils_data
#undef cutils_raw
#undef cutils_append
#undef cutils_push
#undef cutils_set
#undef cutils_pop
#undef cutils_sub
#undef cutils_get
#undef cutils_iter
#undef cutils_next
#undef cutils_keys
#undef cutils_values
#undef cutils_items
#undef cutils_find
#undef cutils_findall
#undef cutils_del
#undef cutils_len
#undef cutils_size
#undef cutils_resize
#undef cutils_swap
#undef cutils_reverse
#undef cutils_pull
#undef cutils_truncate
#undef cutils_clear
#undef cutils_print

#define cutils_new(...) __cutils_vargs_new(__VA_ARGS__)
#define cutils_data(...) __cutils_generic_data(__VA_ARGS__)
#define cutils_raw(...) __cutils_generic_raw(__VA_ARGS__)
#define cutils_append(...) __cutils_vargs_append(__VA_ARGS__)
#define cutils_add(...) __cutils_vargs_add(__VA_ARGS__)
#define cutils_push(...) __cutils_vargs_push(__VA_ARGS__)
#define cutils_set(...) __cutils_vargs_set(__VA_ARGS__)
#define cutils_pop(...) __cutils_vargs_pop(__VA_ARGS__)
#define cutils_sub(...) __cutils_vargs_sub(__VA_ARGS__)
#define cutils_get(...) __cutils_generic_get(__VA_ARGS__)
#define cutils_iter(...) __cutils_generic_iter(__VA_ARGS__)
#define cutils_next(...) __cutils_generic_next(__VA_ARGS__)
#define cutils_values(...) __cutils_generic_values(__VA_ARGS__)
#define cutils_items(...) __cutils_generic_items(__VA_ARGS__)
#define cutils_find(...) __cutils_vargs_find(__VA_ARGS__)
#define cutils_findall(...) __cutils_vargs_findall(__VA_ARGS__)
#define cutils_del(...) __cutils_generic_del(__VA_ARGS__)
#define cutils_len(...) __cutils_generic_len(__VA_ARGS__)
#define cutils_size(...) __cutils_generic_size(__VA_ARGS__)
#define cutils_resize(...) __cutils_generic_resize(__VA_ARGS__)
#define cutils_swap(...) __cutils_vargs_swap(__VA_ARGS__)
#define cutils_reverse(...) __cutils_generic_reverse(__VA_ARGS__)
#define cutils_pull(...) __cutils_vargs_pull(__VA_ARGS__)
#define cutils_truncate(...) __cutils_vargs_truncate(__VA_ARGS__)
#define cutils_clear(...) __cutils_generic_clear(__VA_ARGS__)
#define cutils_map(...) __cutils_vargs_map(__VA_ARGS__)
#define cutils_print(...) __cutils_vargs_print(__VA_ARGS__)

/* Macro-aliases */
#define cutils_keys(...) __cutils_generic_next(__VA_ARGS__)

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* C Arguments */
#undef cutils_zero
#undef cutils_vargs
#define cutils_zero(...) cutils_carg_zero(__VA_ARGS__)
#define cutils_vargs(...) cutils_carg_vargs(__VA_ARGS__)

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* C Debug */
#undef cutils_debug
#undef cutils_boolean
#define cutils_debug(...) cutils_cbug_debug(__VA_ARGS__)
#define cutils_boolean(...) cutils_cbug_boolean(__VA_ARGS__)

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* C Frame Per Second */
#undef cutils_getfps
#undef cutils_printfps
#define cutils_getfps(...) cutils_cfps_getfps(__VA_ARGS__)
#define cutils_printfps(...) cutils_cfps_printfps(__VA_ARGS__)

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* C Profile */
#undef  cutils_profile
#define cutils_profile(...) cutils_cpro_profile(__VA_ARGS__)

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* C Exceptions */
#undef cutils_start_exception_handling
#undef cutils_stop_exception_handling
#undef cutils_set_exception_handling_pointer
#undef cutils_set_exception_handling_custom_raise
#undef cutils_set_exception_handling_custom_catch
#undef cutils_raise
#undef cutils_catch
#undef cutils_craise
#undef cutils_ccatch

#define cutils_start_exception_handling(...) \
    cutils_cexc_start_exception_handling(__VA_ARGS__)
#define cutils_stop_exception_handling(...) \
    cutils_cexc_stop_exception_handling(__VA_ARGS__)
#define cutils_set_exception_handling_pointer(...) \
    cutils_cexc_set_exception_handling_pointer(__VA_ARGS__)
#define cutils_set_exception_handling_custom_raise(...) \
    cutils_cexc_set_exception_handling_custom_raise(__VA_ARGS__)
#define cutils_set_exception_handling_custom_catch(...) \
    cutils_cexc_set_exception_handling_custom_catch(__VA_ARGS__)
#define cutils_raise(...) cutils_cexc_raise(__VA_ARGS__)
#define cutils_catch(...) cutils_cexc_catch(__VA_ARGS__)
#define cutils_craise(...) cutils_cexc_craise(__VA_ARGS__)
#define cutils_ccatch(...) cutils_cexc_ccatch(__VA_ARGS__)

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* C Unit Testing */
typedef cutils_cutt_Tester cutils_Tester;
#undef cutils_try
#undef cutils_report
#define cutils_try(...) cutils_cutt_Tester_try(__VA_ARGS__)
#define cutils_report(...) cutils_cutt_Tester_report(__VA_ARGS__)

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* C Dynamic Array */
/* Base types */
typedef cutils_cdar_DynamicArray_void_ptr cutils_DynamicArray_void_ptr;
typedef cutils_cdar_DynamicArray_char cutils_DynamicArray_char;
typedef cutils_cdar_DynamicArray_signed_char cutils_DynamicArray_signed_char;
typedef cutils_cdar_DynamicArray_unsigned_char cutils_DynamicArray_unsigned_char;
typedef cutils_cdar_DynamicArray_char_ptr cutils_DynamicArray_char_ptr;
typedef cutils_cdar_DynamicArray_short cutils_DynamicArray_short;
typedef cutils_cdar_DynamicArray_unsigned_short cutils_DynamicArray_unsigned_short;
typedef cutils_cdar_DynamicArray_int cutils_DynamicArray_int;
typedef cutils_cdar_DynamicArray_unsigned_int cutils_DynamicArray_unsigned_int;
typedef cutils_cdar_DynamicArray_long cutils_DynamicArray_long;
typedef cutils_cdar_DynamicArray_unsigned_long cutils_DynamicArray_unsigned_long;
typedef cutils_cdar_DynamicArray_long_long cutils_DynamicArray_long_long;
typedef cutils_cdar_DynamicArray_unsigned_long_long cutils_DynamicArray_unsigned_long_long;
typedef cutils_cdar_DynamicArray_float cutils_DynamicArray_float;
typedef cutils_cdar_DynamicArray_double cutils_DynamicArray_double;
typedef cutils_cdar_DynamicArray_long_double cutils_DynamicArray_long_double;
typedef cutils_cdar_DynamicArray_bool cutils_DynamicArray_bool;
typedef cutils_cdar_DynamicArray_size_t cutils_DynamicArray_size_t;
typedef cutils_cdar_DynamicArray_ptrdiff_t cutils_DynamicArray_ptrdiff_t;

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* C Singly Linked List */
/* Base types */
typedef cutils_csll_SinglyLinkedList_void_ptr cutils_SinglyLinkedList_void_ptr;
typedef cutils_csll_SinglyLinkedList_char cutils_SinglyLinkedList_char;
typedef cutils_csll_SinglyLinkedList_signed_char cutils_SinglyLinkedList_signed_char;
typedef cutils_csll_SinglyLinkedList_unsigned_char cutils_SinglyLinkedList_unsigned_char;
typedef cutils_csll_SinglyLinkedList_char_ptr cutils_SinglyLinkedList_char_ptr;
typedef cutils_csll_SinglyLinkedList_short cutils_SinglyLinkedList_short;
typedef cutils_csll_SinglyLinkedList_unsigned_short cutils_SinglyLinkedList_unsigned_short;
typedef cutils_csll_SinglyLinkedList_int cutils_SinglyLinkedList_int;
typedef cutils_csll_SinglyLinkedList_unsigned_int cutils_SinglyLinkedList_unsigned_int;
typedef cutils_csll_SinglyLinkedList_long cutils_SinglyLinkedList_long;
typedef cutils_csll_SinglyLinkedList_unsigned_long cutils_SinglyLinkedList_unsigned_long;
typedef cutils_csll_SinglyLinkedList_long_long cutils_SinglyLinkedList_long_long;
typedef cutils_csll_SinglyLinkedList_unsigned_long_long cutils_SinglyLinkedList_unsigned_long_long;
typedef cutils_csll_SinglyLinkedList_float cutils_SinglyLinkedList_float;
typedef cutils_csll_SinglyLinkedList_double cutils_SinglyLinkedList_double;
typedef cutils_csll_SinglyLinkedList_long_double cutils_SinglyLinkedList_long_double;
typedef cutils_csll_SinglyLinkedList_bool cutils_SinglyLinkedList_bool;
typedef cutils_csll_SinglyLinkedList_size_t cutils_SinglyLinkedList_size_t;
typedef cutils_csll_SinglyLinkedList_ptrdiff_t cutils_SinglyLinkedList_ptrdiff_t;
/* Support types */
typedef cutils_csll_SinglyLinkedList_void_ptr_iterator cutils_SinglyLinkedList_void_ptr_iterator;
typedef cutils_csll_SinglyLinkedList_char_iterator cutils_SinglyLinkedList_char_iterator;
typedef cutils_csll_SinglyLinkedList_signed_char_iterator cutils_SinglyLinkedList_signed_char_iterator;
typedef cutils_csll_SinglyLinkedList_unsigned_char_iterator cutils_SinglyLinkedList_unsigned_char_iterator;
typedef cutils_csll_SinglyLinkedList_char_ptr_iterator cutils_SinglyLinkedList_char_ptr_iterator;
typedef cutils_csll_SinglyLinkedList_short_iterator cutils_SinglyLinkedList_short_iterator;
typedef cutils_csll_SinglyLinkedList_unsigned_short_iterator cutils_SinglyLinkedList_unsigned_short_iterator;
typedef cutils_csll_SinglyLinkedList_int_iterator cutils_SinglyLinkedList_int_iterator;
typedef cutils_csll_SinglyLinkedList_unsigned_int_iterator cutils_SinglyLinkedList_unsigned_int_iterator;
typedef cutils_csll_SinglyLinkedList_long_iterator cutils_SinglyLinkedList_long_iterator;
typedef cutils_csll_SinglyLinkedList_unsigned_long_iterator cutils_SinglyLinkedList_unsigned_long_iterator;
typedef cutils_csll_SinglyLinkedList_long_long_iterator cutils_SinglyLinkedList_long_long_iterator;
typedef cutils_csll_SinglyLinkedList_unsigned_long_long_iterator cutils_SinglyLinkedList_unsigned_long_long_iterator;
typedef cutils_csll_SinglyLinkedList_float_iterator cutils_SinglyLinkedList_float_iterator;
typedef cutils_csll_SinglyLinkedList_double_iterator cutils_SinglyLinkedList_double_iterator;
typedef cutils_csll_SinglyLinkedList_long_double_iterator cutils_SinglyLinkedList_long_double_iterator;
typedef cutils_csll_SinglyLinkedList_bool_iterator cutils_SinglyLinkedList_bool_iterator;
typedef cutils_csll_SinglyLinkedList_size_t_iterator cutils_SinglyLinkedList_size_t_iterator;
typedef cutils_csll_SinglyLinkedList_ptrdiff_t_iterator cutils_SinglyLinkedList_ptrdiff_t_iterator;

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* C Static Hash Map */
/*
typedef cutils_cshm_StaticHashMap_void_ptr cutils_StaticHashMap_void_ptr;
typedef cutils_cshm_StaticHashMap_char cutils_StaticHashMap_char;
typedef cutils_cshm_StaticHashMap_signed_char cutils_StaticHashMap_signed_char;
typedef cutils_cshm_StaticHashMap_unsigned_char cutils_StaticHashMap_unsigned_char;
typedef cutils_cshm_StaticHashMap_char_ptr cutils_StaticHashMap_char_ptr;
typedef cutils_cshm_StaticHashMap_short cutils_StaticHashMap_short;
typedef cutils_cshm_StaticHashMap_unsigned_short cutils_StaticHashMap_unsigned_short;
typedef cutils_cshm_StaticHashMap_int cutils_StaticHashMap_int;
typedef cutils_cshm_StaticHashMap_unsigned_int cutils_StaticHashMap_unsigned_int;
typedef cutils_cshm_StaticHashMap_long cutils_StaticHashMap_long;
typedef cutils_cshm_StaticHashMap_unsigned_long cutils_StaticHashMap_unsigned_long;
typedef cutils_cshm_StaticHashMap_long_long cutils_StaticHashMap_long_long;
typedef cutils_cshm_StaticHashMap_unsigned_long_long cutils_StaticHashMap_unsigned_long_long;
typedef cutils_cshm_StaticHashMap_float cutils_StaticHashMap_float;
typedef cutils_cshm_StaticHashMap_double cutils_StaticHashMap_double;
typedef cutils_cshm_StaticHashMap_long_double cutils_StaticHashMap_long_double;
typedef cutils_cshm_StaticHashMap_bool cutils_StaticHashMap_bool;
typedef cutils_cshm_StaticHashMap_size_t cutils_StaticHashMap_size_t;
typedef cutils_cshm_StaticHashMap_ptrdiff_t cutils_StaticHashMap_ptrdiff_t;

typedef cutils_cshm_StaticHashMap_void_ptr_iterator cutils_StaticHashMap_void_ptr_iterator;
typedef cutils_cshm_StaticHashMap_char_iterator cutils_StaticHashMap_char_iterator;
typedef cutils_cshm_StaticHashMap_signed_char_iterator cutils_StaticHashMap_signed_char_iterator;
typedef cutils_cshm_StaticHashMap_unsigned_char_iterator cutils_StaticHashMap_unsigned_char_iterator;
typedef cutils_cshm_StaticHashMap_char_ptr_iterator cutils_StaticHashMap_char_ptr_iterator;
typedef cutils_cshm_StaticHashMap_short_iterator cutils_StaticHashMap_short_iterator;
typedef cutils_cshm_StaticHashMap_unsigned_short_iterator cutils_StaticHashMap_unsigned_short_iterator;
typedef cutils_cshm_StaticHashMap_int_iterator cutils_StaticHashMap_int_iterator;
typedef cutils_cshm_StaticHashMap_unsigned_int_iterator cutils_StaticHashMap_unsigned_int_iterator;
typedef cutils_cshm_StaticHashMap_long_iterator cutils_StaticHashMap_long_iterator;
typedef cutils_cshm_StaticHashMap_unsigned_long_iterator cutils_StaticHashMap_unsigned_long_iterator;
typedef cutils_cshm_StaticHashMap_long_long_iterator cutils_StaticHashMap_long_long_iterator;
typedef cutils_cshm_StaticHashMap_unsigned_long_long_iterator cutils_StaticHashMap_unsigned_long_long_iterator;
typedef cutils_cshm_StaticHashMap_float_iterator cutils_StaticHashMap_float_iterator;
typedef cutils_cshm_StaticHashMap_double_iterator cutils_StaticHashMap_double_iterator;
typedef cutils_cshm_StaticHashMap_long_double_iterator cutils_StaticHashMap_long_double_iterator;
typedef cutils_cshm_StaticHashMap_bool_iterator cutils_StaticHashMap_bool_iterator;
typedef cutils_cshm_StaticHashMap_size_t_iterator cutils_StaticHashMap_size_t_iterator;
typedef cutils_cshm_StaticHashMap_ptrdiff_t_iterator cutils_StaticHashMap_ptrdiff_t_iterator;
*/
#endif /* CUTILS_NAMESPACE */


/*----------------------------------------------------------------------------*/
/* !!! D O N ' T   R E M O V E   T H E   N E X T   C O M M E N T !!! */
/* AUTOMATICALLY GENERATED GENERIC MACROS */


#undef  __cutils_generic_new_args4
#define __cutils_generic_new_args4(object,...) _Generic((object),\
    cutils_cdar_DynamicArray_void_ptr**:cutils_cdar_DynamicArray_void_ptr_new,\
    cutils_csll_SinglyLinkedList_void_ptr**:cutils_csll_SinglyLinkedList_void_ptr_new)\
    (object,##__VA_ARGS__)
/*----------------------------------------------------------------------------*/
#undef  __cutils_generic_new_args3
#define __cutils_generic_new_args3(object,...) _Generic((object),\
    cutils_cdar_DynamicArray_char**:cutils_cdar_DynamicArray_char_new,\
    cutils_cdar_DynamicArray_void_ptr**:cutils_cdar_DynamicArray_void_ptr_new_default3,\
    cutils_cdar_DynamicArray_signed_char**:cutils_cdar_DynamicArray_signed_char_new,\
    cutils_cdar_DynamicArray_unsigned_char**:cutils_cdar_DynamicArray_unsigned_char_new,\
    cutils_cdar_DynamicArray_char_ptr**:cutils_cdar_DynamicArray_char_ptr_new,\
    cutils_cdar_DynamicArray_short**:cutils_cdar_DynamicArray_short_new,\
    cutils_cdar_DynamicArray_unsigned_short**:cutils_cdar_DynamicArray_unsigned_short_new,\
    cutils_cdar_DynamicArray_int**:cutils_cdar_DynamicArray_int_new,\
    cutils_cdar_DynamicArray_unsigned_int**:cutils_cdar_DynamicArray_unsigned_int_new,\
    cutils_cdar_DynamicArray_long**:cutils_cdar_DynamicArray_long_new,\
    cutils_cdar_DynamicArray_unsigned_long**:cutils_cdar_DynamicArray_unsigned_long_new,\
    cutils_cdar_DynamicArray_long_long**:cutils_cdar_DynamicArray_long_long_new,\
    cutils_cdar_DynamicArray_unsigned_long_long**:cutils_cdar_DynamicArray_unsigned_long_long_new,\
    cutils_cdar_DynamicArray_float**:cutils_cdar_DynamicArray_float_new,\
    cutils_cdar_DynamicArray_double**:cutils_cdar_DynamicArray_double_new,\
    cutils_cdar_DynamicArray_long_double**:cutils_cdar_DynamicArray_long_double_new,\
    cutils_cdar_DynamicArray_bool**:cutils_cdar_DynamicArray_bool_new,\
    cutils_cdar_DynamicArray_size_t**:cutils_cdar_DynamicArray_size_t_new,\
    cutils_cdar_DynamicArray_ptrdiff_t**:cutils_cdar_DynamicArray_ptrdiff_t_new,\
    cutils_csll_SinglyLinkedList_char**:cutils_csll_SinglyLinkedList_char_new,\
    cutils_csll_SinglyLinkedList_signed_char**:cutils_csll_SinglyLinkedList_signed_char_new,\
    cutils_csll_SinglyLinkedList_unsigned_char**:cutils_csll_SinglyLinkedList_unsigned_char_new,\
    cutils_csll_SinglyLinkedList_char_ptr**:cutils_csll_SinglyLinkedList_char_ptr_new,\
    cutils_csll_SinglyLinkedList_short**:cutils_csll_SinglyLinkedList_short_new,\
    cutils_csll_SinglyLinkedList_unsigned_short**:cutils_csll_SinglyLinkedList_unsigned_short_new,\
    cutils_csll_SinglyLinkedList_int**:cutils_csll_SinglyLinkedList_int_new,\
    cutils_csll_SinglyLinkedList_unsigned_int**:cutils_csll_SinglyLinkedList_unsigned_int_new,\
    cutils_csll_SinglyLinkedList_long**:cutils_csll_SinglyLinkedList_long_new,\
    cutils_csll_SinglyLinkedList_unsigned_long**:cutils_csll_SinglyLinkedList_unsigned_long_new,\
    cutils_csll_SinglyLinkedList_long_long**:cutils_csll_SinglyLinkedList_long_long_new,\
    cutils_csll_SinglyLinkedList_unsigned_long_long**:cutils_csll_SinglyLinkedList_unsigned_long_long_new,\
    cutils_csll_SinglyLinkedList_float**:cutils_csll_SinglyLinkedList_float_new,\
    cutils_csll_SinglyLinkedList_double**:cutils_csll_SinglyLinkedList_double_new,\
    cutils_csll_SinglyLinkedList_long_double**:cutils_csll_SinglyLinkedList_long_double_new,\
    cutils_csll_SinglyLinkedList_bool**:cutils_csll_SinglyLinkedList_bool_new,\
    cutils_csll_SinglyLinkedList_size_t**:cutils_csll_SinglyLinkedList_size_t_new,\
    cutils_csll_SinglyLinkedList_ptrdiff_t**:cutils_csll_SinglyLinkedList_ptrdiff_t_new)\
    (object,##__VA_ARGS__)
/*----------------------------------------------------------------------------*/
#undef  __cutils_generic_new_args2
#define __cutils_generic_new_args2(object,...) _Generic((object),\
    cutils_cdar_DynamicArray_char**:cutils_cdar_DynamicArray_char_new_default2,\
    cutils_cdar_DynamicArray_void_ptr**:cutils_cdar_DynamicArray_void_ptr_new_default2,\
    cutils_cdar_DynamicArray_signed_char**:cutils_cdar_DynamicArray_signed_char_new_default2,\
    cutils_cdar_DynamicArray_unsigned_char**:cutils_cdar_DynamicArray_unsigned_char_new_default2,\
    cutils_cdar_DynamicArray_char_ptr**:cutils_cdar_DynamicArray_char_ptr_new_default2,\
    cutils_cdar_DynamicArray_short**:cutils_cdar_DynamicArray_short_new_default2,\
    cutils_cdar_DynamicArray_unsigned_short**:cutils_cdar_DynamicArray_unsigned_short_new_default2,\
    cutils_cdar_DynamicArray_int**:cutils_cdar_DynamicArray_int_new_default2,\
    cutils_cdar_DynamicArray_unsigned_int**:cutils_cdar_DynamicArray_unsigned_int_new_default2,\
    cutils_cdar_DynamicArray_long**:cutils_cdar_DynamicArray_long_new_default2,\
    cutils_cdar_DynamicArray_unsigned_long**:cutils_cdar_DynamicArray_unsigned_long_new_default2,\
    cutils_cdar_DynamicArray_long_long**:cutils_cdar_DynamicArray_long_long_new_default2,\
    cutils_cdar_DynamicArray_unsigned_long_long**:cutils_cdar_DynamicArray_unsigned_long_long_new_default2,\
    cutils_cdar_DynamicArray_float**:cutils_cdar_DynamicArray_float_new_default2,\
    cutils_cdar_DynamicArray_double**:cutils_cdar_DynamicArray_double_new_default2,\
    cutils_cdar_DynamicArray_long_double**:cutils_cdar_DynamicArray_long_double_new_default2,\
    cutils_cdar_DynamicArray_bool**:cutils_cdar_DynamicArray_bool_new_default2,\
    cutils_cdar_DynamicArray_size_t**:cutils_cdar_DynamicArray_size_t_new_default2,\
    cutils_cdar_DynamicArray_ptrdiff_t**:cutils_cdar_DynamicArray_ptrdiff_t_new_default2,\
    cutils_cutt_Tester**:cutils_cutt_Tester_new)\
    (object,##__VA_ARGS__)
/*----------------------------------------------------------------------------*/
#undef  __cutils_generic_new_args1
#define __cutils_generic_new_args1(object,...) _Generic((object),\
    cutils_cdar_DynamicArray_char**:cutils_cdar_DynamicArray_char_new_default1,\
    cutils_cdar_DynamicArray_signed_char**:cutils_cdar_DynamicArray_signed_char_new_default1,\
    cutils_cdar_DynamicArray_unsigned_char**:cutils_cdar_DynamicArray_unsigned_char_new_default1,\
    cutils_cdar_DynamicArray_char_ptr**:cutils_cdar_DynamicArray_char_ptr_new_default1,\
    cutils_cdar_DynamicArray_short**:cutils_cdar_DynamicArray_short_new_default1,\
    cutils_cdar_DynamicArray_unsigned_short**:cutils_cdar_DynamicArray_unsigned_short_new_default1,\
    cutils_cdar_DynamicArray_int**:cutils_cdar_DynamicArray_int_new_default1,\
    cutils_cdar_DynamicArray_unsigned_int**:cutils_cdar_DynamicArray_unsigned_int_new_default1,\
    cutils_cdar_DynamicArray_long**:cutils_cdar_DynamicArray_long_new_default1,\
    cutils_cdar_DynamicArray_unsigned_long**:cutils_cdar_DynamicArray_unsigned_long_new_default1,\
    cutils_cdar_DynamicArray_long_long**:cutils_cdar_DynamicArray_long_long_new_default1,\
    cutils_cdar_DynamicArray_unsigned_long_long**:cutils_cdar_DynamicArray_unsigned_long_long_new_default1,\
    cutils_cdar_DynamicArray_float**:cutils_cdar_DynamicArray_float_new_default1,\
    cutils_cdar_DynamicArray_double**:cutils_cdar_DynamicArray_double_new_default1,\
    cutils_cdar_DynamicArray_long_double**:cutils_cdar_DynamicArray_long_double_new_default1,\
    cutils_cdar_DynamicArray_bool**:cutils_cdar_DynamicArray_bool_new_default1,\
    cutils_cdar_DynamicArray_size_t**:cutils_cdar_DynamicArray_size_t_new_default1,\
    cutils_cdar_DynamicArray_ptrdiff_t**:cutils_cdar_DynamicArray_ptrdiff_t_new_default1,\
    cutils_csll_SinglyLinkedList_char**:cutils_csll_SinglyLinkedList_char_new_default1,\
    cutils_csll_SinglyLinkedList_void_ptr**:cutils_csll_SinglyLinkedList_void_ptr_new_default1,\
    cutils_csll_SinglyLinkedList_signed_char**:cutils_csll_SinglyLinkedList_signed_char_new_default1,\
    cutils_csll_SinglyLinkedList_unsigned_char**:cutils_csll_SinglyLinkedList_unsigned_char_new_default1,\
    cutils_csll_SinglyLinkedList_char_ptr**:cutils_csll_SinglyLinkedList_char_ptr_new_default1,\
    cutils_csll_SinglyLinkedList_short**:cutils_csll_SinglyLinkedList_short_new_default1,\
    cutils_csll_SinglyLinkedList_unsigned_short**:cutils_csll_SinglyLinkedList_unsigned_short_new_default1,\
    cutils_csll_SinglyLinkedList_int**:cutils_csll_SinglyLinkedList_int_new_default1,\
    cutils_csll_SinglyLinkedList_unsigned_int**:cutils_csll_SinglyLinkedList_unsigned_int_new_default1,\
    cutils_csll_SinglyLinkedList_long**:cutils_csll_SinglyLinkedList_long_new_default1,\
    cutils_csll_SinglyLinkedList_unsigned_long**:cutils_csll_SinglyLinkedList_unsigned_long_new_default1,\
    cutils_csll_SinglyLinkedList_long_long**:cutils_csll_SinglyLinkedList_long_long_new_default1,\
    cutils_csll_SinglyLinkedList_unsigned_long_long**:cutils_csll_SinglyLinkedList_unsigned_long_long_new_default1,\
    cutils_csll_SinglyLinkedList_float**:cutils_csll_SinglyLinkedList_float_new_default1,\
    cutils_csll_SinglyLinkedList_double**:cutils_csll_SinglyLinkedList_double_new_default1,\
    cutils_csll_SinglyLinkedList_long_double**:cutils_csll_SinglyLinkedList_long_double_new_default1,\
    cutils_csll_SinglyLinkedList_bool**:cutils_csll_SinglyLinkedList_bool_new_default1,\
    cutils_csll_SinglyLinkedList_size_t**:cutils_csll_SinglyLinkedList_size_t_new_default1,\
    cutils_csll_SinglyLinkedList_ptrdiff_t**:cutils_csll_SinglyLinkedList_ptrdiff_t_new_default1)\
    (object,##__VA_ARGS__)
/*----------------------------------------------------------------------------*/
#undef  __cutils_generic_del
#define __cutils_generic_del(object,...) _Generic((object),\
    cutils_cdar_DynamicArray_char*:cutils_cdar_DynamicArray_char_del,\
    cutils_cdar_DynamicArray_void_ptr*:cutils_cdar_DynamicArray_void_ptr_del,\
    cutils_cdar_DynamicArray_signed_char*:cutils_cdar_DynamicArray_signed_char_del,\
    cutils_cdar_DynamicArray_unsigned_char*:cutils_cdar_DynamicArray_unsigned_char_del,\
    cutils_cdar_DynamicArray_char_ptr*:cutils_cdar_DynamicArray_char_ptr_del,\
    cutils_cdar_DynamicArray_short*:cutils_cdar_DynamicArray_short_del,\
    cutils_cdar_DynamicArray_unsigned_short*:cutils_cdar_DynamicArray_unsigned_short_del,\
    cutils_cdar_DynamicArray_int*:cutils_cdar_DynamicArray_int_del,\
    cutils_cdar_DynamicArray_unsigned_int*:cutils_cdar_DynamicArray_unsigned_int_del,\
    cutils_cdar_DynamicArray_long*:cutils_cdar_DynamicArray_long_del,\
    cutils_cdar_DynamicArray_unsigned_long*:cutils_cdar_DynamicArray_unsigned_long_del,\
    cutils_cdar_DynamicArray_long_long*:cutils_cdar_DynamicArray_long_long_del,\
    cutils_cdar_DynamicArray_unsigned_long_long*:cutils_cdar_DynamicArray_unsigned_long_long_del,\
    cutils_cdar_DynamicArray_float*:cutils_cdar_DynamicArray_float_del,\
    cutils_cdar_DynamicArray_double*:cutils_cdar_DynamicArray_double_del,\
    cutils_cdar_DynamicArray_long_double*:cutils_cdar_DynamicArray_long_double_del,\
    cutils_cdar_DynamicArray_bool*:cutils_cdar_DynamicArray_bool_del,\
    cutils_cdar_DynamicArray_size_t*:cutils_cdar_DynamicArray_size_t_del,\
    cutils_cdar_DynamicArray_ptrdiff_t*:cutils_cdar_DynamicArray_ptrdiff_t_del,\
    cutils_csll_SinglyLinkedList_char*:cutils_csll_SinglyLinkedList_char_del,\
    cutils_csll_SinglyLinkedList_char_iterator*:cutils_csll_SinglyLinkedList_char_iterator_del,\
    cutils_csll_SinglyLinkedList_void_ptr*:cutils_csll_SinglyLinkedList_void_ptr_del,\
    cutils_csll_SinglyLinkedList_void_ptr_iterator:cutils_csll_SinglyLinkedList_void_ptr_iterator_del,\
    cutils_csll_SinglyLinkedList_signed_char*:cutils_csll_SinglyLinkedList_signed_char_del,\
    cutils_csll_SinglyLinkedList_signed_char_iterator*:cutils_csll_SinglyLinkedList_signed_char_iterator_del,\
    cutils_csll_SinglyLinkedList_unsigned_char*:cutils_csll_SinglyLinkedList_unsigned_char_del,\
    cutils_csll_SinglyLinkedList_unsigned_char_iterator*:cutils_csll_SinglyLinkedList_unsigned_char_iterator_del,\
    cutils_csll_SinglyLinkedList_char_ptr*:cutils_csll_SinglyLinkedList_char_ptr_del,\
    cutils_csll_SinglyLinkedList_char_ptr_iterator*:cutils_csll_SinglyLinkedList_char_ptr_iterator_del,\
    cutils_csll_SinglyLinkedList_short*:cutils_csll_SinglyLinkedList_short_del,\
    cutils_csll_SinglyLinkedList_short_iterator*:cutils_csll_SinglyLinkedList_short_iterator_del,\
    cutils_csll_SinglyLinkedList_unsigned_short*:cutils_csll_SinglyLinkedList_unsigned_short_del,\
    cutils_csll_SinglyLinkedList_unsigned_short_iterator*:cutils_csll_SinglyLinkedList_unsigned_short_iterator_del,\
    cutils_csll_SinglyLinkedList_int*:cutils_csll_SinglyLinkedList_int_del,\
    cutils_csll_SinglyLinkedList_int_iterator*:cutils_csll_SinglyLinkedList_int_iterator_del,\
    cutils_csll_SinglyLinkedList_unsigned_int*:cutils_csll_SinglyLinkedList_unsigned_int_del,\
    cutils_csll_SinglyLinkedList_unsigned_int_iterator*:cutils_csll_SinglyLinkedList_unsigned_int_iterator_del,\
    cutils_csll_SinglyLinkedList_long*:cutils_csll_SinglyLinkedList_long_del,\
    cutils_csll_SinglyLinkedList_long_iterator*:cutils_csll_SinglyLinkedList_long_iterator_del,\
    cutils_csll_SinglyLinkedList_unsigned_long*:cutils_csll_SinglyLinkedList_unsigned_long_del,\
    cutils_csll_SinglyLinkedList_unsigned_long_iterator*:cutils_csll_SinglyLinkedList_unsigned_long_iterator_del,\
    cutils_csll_SinglyLinkedList_long_long*:cutils_csll_SinglyLinkedList_long_long_del,\
    cutils_csll_SinglyLinkedList_long_long_iterator*:cutils_csll_SinglyLinkedList_long_long_iterator_del,\
    cutils_csll_SinglyLinkedList_unsigned_long_long*:cutils_csll_SinglyLinkedList_unsigned_long_long_del,\
    cutils_csll_SinglyLinkedList_unsigned_long_long_iterator*:cutils_csll_SinglyLinkedList_unsigned_long_long_iterator_del,\
    cutils_csll_SinglyLinkedList_float*:cutils_csll_SinglyLinkedList_float_del,\
    cutils_csll_SinglyLinkedList_float_iterator*:cutils_csll_SinglyLinkedList_float_iterator_del,\
    cutils_csll_SinglyLinkedList_double*:cutils_csll_SinglyLinkedList_double_del,\
    cutils_csll_SinglyLinkedList_double_iterator*:cutils_csll_SinglyLinkedList_double_iterator_del,\
    cutils_csll_SinglyLinkedList_long_double*:cutils_csll_SinglyLinkedList_long_double_del,\
    cutils_csll_SinglyLinkedList_long_double_iterator*:cutils_csll_SinglyLinkedList_long_double_iterator_del,\
    cutils_csll_SinglyLinkedList_bool*:cutils_csll_SinglyLinkedList_bool_del,\
    cutils_csll_SinglyLinkedList_bool_iterator*:cutils_csll_SinglyLinkedList_bool_iterator_del,\
    cutils_csll_SinglyLinkedList_size_t*:cutils_csll_SinglyLinkedList_size_t_del,\
    cutils_csll_SinglyLinkedList_size_t_iterator*:cutils_csll_SinglyLinkedList_size_t_iterator_del,\
    cutils_csll_SinglyLinkedList_ptrdiff_t*:cutils_csll_SinglyLinkedList_ptrdiff_t_del,\
    cutils_csll_SinglyLinkedList_ptrdiff_t_iterator*:cutils_csll_SinglyLinkedList_ptrdiff_t_iterator_del,\
    cutils_cutt_Tester*:cutils_cutt_Tester_del)\
    (object,##__VA_ARGS__)
/*----------------------------------------------------------------------------*/
#undef  __cutils_generic_data
#define __cutils_generic_data(object,...) _Generic((object),\
    cutils_cdar_DynamicArray_char*:cutils_cdar_DynamicArray_char_data,\
    cutils_cdar_DynamicArray_void_ptr*:cutils_cdar_DynamicArray_void_ptr_data,\
    cutils_cdar_DynamicArray_signed_char*:cutils_cdar_DynamicArray_signed_char_data,\
    cutils_cdar_DynamicArray_unsigned_char*:cutils_cdar_DynamicArray_unsigned_char_data,\
    cutils_cdar_DynamicArray_char_ptr*:cutils_cdar_DynamicArray_char_ptr_data,\
    cutils_cdar_DynamicArray_short*:cutils_cdar_DynamicArray_short_data,\
    cutils_cdar_DynamicArray_unsigned_short*:cutils_cdar_DynamicArray_unsigned_short_data,\
    cutils_cdar_DynamicArray_int*:cutils_cdar_DynamicArray_int_data,\
    cutils_cdar_DynamicArray_unsigned_int*:cutils_cdar_DynamicArray_unsigned_int_data,\
    cutils_cdar_DynamicArray_long*:cutils_cdar_DynamicArray_long_data,\
    cutils_cdar_DynamicArray_unsigned_long*:cutils_cdar_DynamicArray_unsigned_long_data,\
    cutils_cdar_DynamicArray_long_long*:cutils_cdar_DynamicArray_long_long_data,\
    cutils_cdar_DynamicArray_unsigned_long_long*:cutils_cdar_DynamicArray_unsigned_long_long_data,\
    cutils_cdar_DynamicArray_float*:cutils_cdar_DynamicArray_float_data,\
    cutils_cdar_DynamicArray_double*:cutils_cdar_DynamicArray_double_data,\
    cutils_cdar_DynamicArray_long_double*:cutils_cdar_DynamicArray_long_double_data,\
    cutils_cdar_DynamicArray_bool*:cutils_cdar_DynamicArray_bool_data,\
    cutils_cdar_DynamicArray_size_t*:cutils_cdar_DynamicArray_size_t_data,\
    cutils_cdar_DynamicArray_ptrdiff_t*:cutils_cdar_DynamicArray_ptrdiff_t_data)\
    (object,##__VA_ARGS__)
/*----------------------------------------------------------------------------*/
#undef  __cutils_generic_len
#define __cutils_generic_len(object,...) _Generic((object),\
    cutils_cdar_DynamicArray_char*:cutils_cdar_DynamicArray_char_len,\
    cutils_cdar_DynamicArray_void_ptr*:cutils_cdar_DynamicArray_void_ptr_len,\
    cutils_cdar_DynamicArray_signed_char*:cutils_cdar_DynamicArray_signed_char_len,\
    cutils_cdar_DynamicArray_unsigned_char*:cutils_cdar_DynamicArray_unsigned_char_len,\
    cutils_cdar_DynamicArray_char_ptr*:cutils_cdar_DynamicArray_char_ptr_len,\
    cutils_cdar_DynamicArray_short*:cutils_cdar_DynamicArray_short_len,\
    cutils_cdar_DynamicArray_unsigned_short*:cutils_cdar_DynamicArray_unsigned_short_len,\
    cutils_cdar_DynamicArray_int*:cutils_cdar_DynamicArray_int_len,\
    cutils_cdar_DynamicArray_unsigned_int*:cutils_cdar_DynamicArray_unsigned_int_len,\
    cutils_cdar_DynamicArray_long*:cutils_cdar_DynamicArray_long_len,\
    cutils_cdar_DynamicArray_unsigned_long*:cutils_cdar_DynamicArray_unsigned_long_len,\
    cutils_cdar_DynamicArray_long_long*:cutils_cdar_DynamicArray_long_long_len,\
    cutils_cdar_DynamicArray_unsigned_long_long*:cutils_cdar_DynamicArray_unsigned_long_long_len,\
    cutils_cdar_DynamicArray_float*:cutils_cdar_DynamicArray_float_len,\
    cutils_cdar_DynamicArray_double*:cutils_cdar_DynamicArray_double_len,\
    cutils_cdar_DynamicArray_long_double*:cutils_cdar_DynamicArray_long_double_len,\
    cutils_cdar_DynamicArray_bool*:cutils_cdar_DynamicArray_bool_len,\
    cutils_cdar_DynamicArray_size_t*:cutils_cdar_DynamicArray_size_t_len,\
    cutils_cdar_DynamicArray_ptrdiff_t*:cutils_cdar_DynamicArray_ptrdiff_t_len,\
    cutils_csll_SinglyLinkedList_char*:cutils_csll_SinglyLinkedList_char_len,\
    cutils_csll_SinglyLinkedList_void_ptr*:cutils_csll_SinglyLinkedList_void_ptr_len,\
    cutils_csll_SinglyLinkedList_signed_char*:cutils_csll_SinglyLinkedList_signed_char_len,\
    cutils_csll_SinglyLinkedList_unsigned_char*:cutils_csll_SinglyLinkedList_unsigned_char_len,\
    cutils_csll_SinglyLinkedList_char_ptr*:cutils_csll_SinglyLinkedList_char_ptr_len,\
    cutils_csll_SinglyLinkedList_short*:cutils_csll_SinglyLinkedList_short_len,\
    cutils_csll_SinglyLinkedList_unsigned_short*:cutils_csll_SinglyLinkedList_unsigned_short_len,\
    cutils_csll_SinglyLinkedList_int*:cutils_csll_SinglyLinkedList_int_len,\
    cutils_csll_SinglyLinkedList_unsigned_int*:cutils_csll_SinglyLinkedList_unsigned_int_len,\
    cutils_csll_SinglyLinkedList_long*:cutils_csll_SinglyLinkedList_long_len,\
    cutils_csll_SinglyLinkedList_unsigned_long*:cutils_csll_SinglyLinkedList_unsigned_long_len,\
    cutils_csll_SinglyLinkedList_long_long*:cutils_csll_SinglyLinkedList_long_long_len,\
    cutils_csll_SinglyLinkedList_unsigned_long_long*:cutils_csll_SinglyLinkedList_unsigned_long_long_len,\
    cutils_csll_SinglyLinkedList_float*:cutils_csll_SinglyLinkedList_float_len,\
    cutils_csll_SinglyLinkedList_double*:cutils_csll_SinglyLinkedList_double_len,\
    cutils_csll_SinglyLinkedList_long_double*:cutils_csll_SinglyLinkedList_long_double_len,\
    cutils_csll_SinglyLinkedList_bool*:cutils_csll_SinglyLinkedList_bool_len,\
    cutils_csll_SinglyLinkedList_size_t*:cutils_csll_SinglyLinkedList_size_t_len,\
    cutils_csll_SinglyLinkedList_ptrdiff_t*:cutils_csll_SinglyLinkedList_ptrdiff_t_len)\
    (object,##__VA_ARGS__)
/*----------------------------------------------------------------------------*/
#undef  __cutils_generic_size
#define __cutils_generic_size(object,...) _Generic((object),\
    cutils_cdar_DynamicArray_char*:cutils_cdar_DynamicArray_char_size,\
    cutils_cdar_DynamicArray_void_ptr*:cutils_cdar_DynamicArray_void_ptr_size,\
    cutils_cdar_DynamicArray_signed_char*:cutils_cdar_DynamicArray_signed_char_size,\
    cutils_cdar_DynamicArray_unsigned_char*:cutils_cdar_DynamicArray_unsigned_char_size,\
    cutils_cdar_DynamicArray_char_ptr*:cutils_cdar_DynamicArray_char_ptr_size,\
    cutils_cdar_DynamicArray_short*:cutils_cdar_DynamicArray_short_size,\
    cutils_cdar_DynamicArray_unsigned_short*:cutils_cdar_DynamicArray_unsigned_short_size,\
    cutils_cdar_DynamicArray_int*:cutils_cdar_DynamicArray_int_size,\
    cutils_cdar_DynamicArray_unsigned_int*:cutils_cdar_DynamicArray_unsigned_int_size,\
    cutils_cdar_DynamicArray_long*:cutils_cdar_DynamicArray_long_size,\
    cutils_cdar_DynamicArray_unsigned_long*:cutils_cdar_DynamicArray_unsigned_long_size,\
    cutils_cdar_DynamicArray_long_long*:cutils_cdar_DynamicArray_long_long_size,\
    cutils_cdar_DynamicArray_unsigned_long_long*:cutils_cdar_DynamicArray_unsigned_long_long_size,\
    cutils_cdar_DynamicArray_float*:cutils_cdar_DynamicArray_float_size,\
    cutils_cdar_DynamicArray_double*:cutils_cdar_DynamicArray_double_size,\
    cutils_cdar_DynamicArray_long_double*:cutils_cdar_DynamicArray_long_double_size,\
    cutils_cdar_DynamicArray_bool*:cutils_cdar_DynamicArray_bool_size,\
    cutils_cdar_DynamicArray_size_t*:cutils_cdar_DynamicArray_size_t_size,\
    cutils_cdar_DynamicArray_ptrdiff_t*:cutils_cdar_DynamicArray_ptrdiff_t_size)\
    (object,##__VA_ARGS__)
/*----------------------------------------------------------------------------*/
#undef  __cutils_generic_raw
#define __cutils_generic_raw(object,...) _Generic((object),\
    cutils_cdar_DynamicArray_char*:cutils_cdar_DynamicArray_char_raw,\
    cutils_cdar_DynamicArray_void_ptr*:cutils_cdar_DynamicArray_void_ptr_raw,\
    cutils_cdar_DynamicArray_signed_char*:cutils_cdar_DynamicArray_signed_char_raw,\
    cutils_cdar_DynamicArray_unsigned_char*:cutils_cdar_DynamicArray_unsigned_char_raw,\
    cutils_cdar_DynamicArray_char_ptr*:cutils_cdar_DynamicArray_char_ptr_raw,\
    cutils_cdar_DynamicArray_short*:cutils_cdar_DynamicArray_short_raw,\
    cutils_cdar_DynamicArray_unsigned_short*:cutils_cdar_DynamicArray_unsigned_short_raw,\
    cutils_cdar_DynamicArray_int*:cutils_cdar_DynamicArray_int_raw,\
    cutils_cdar_DynamicArray_unsigned_int*:cutils_cdar_DynamicArray_unsigned_int_raw,\
    cutils_cdar_DynamicArray_long*:cutils_cdar_DynamicArray_long_raw,\
    cutils_cdar_DynamicArray_unsigned_long*:cutils_cdar_DynamicArray_unsigned_long_raw,\
    cutils_cdar_DynamicArray_long_long*:cutils_cdar_DynamicArray_long_long_raw,\
    cutils_cdar_DynamicArray_unsigned_long_long*:cutils_cdar_DynamicArray_unsigned_long_long_raw,\
    cutils_cdar_DynamicArray_float*:cutils_cdar_DynamicArray_float_raw,\
    cutils_cdar_DynamicArray_double*:cutils_cdar_DynamicArray_double_raw,\
    cutils_cdar_DynamicArray_long_double*:cutils_cdar_DynamicArray_long_double_raw,\
    cutils_cdar_DynamicArray_bool*:cutils_cdar_DynamicArray_bool_raw,\
    cutils_cdar_DynamicArray_size_t*:cutils_cdar_DynamicArray_size_t_raw,\
    cutils_cdar_DynamicArray_ptrdiff_t*:cutils_cdar_DynamicArray_ptrdiff_t_raw)\
    (object,##__VA_ARGS__)
/*----------------------------------------------------------------------------*/
#undef  __cutils_generic_resize
#define __cutils_generic_resize(object,...) _Generic((object),\
    cutils_cdar_DynamicArray_char*:cutils_cdar_DynamicArray_char_resize,\
    cutils_cdar_DynamicArray_void_ptr*:cutils_cdar_DynamicArray_void_ptr_resize,\
    cutils_cdar_DynamicArray_signed_char*:cutils_cdar_DynamicArray_signed_char_resize,\
    cutils_cdar_DynamicArray_unsigned_char*:cutils_cdar_DynamicArray_unsigned_char_resize,\
    cutils_cdar_DynamicArray_char_ptr*:cutils_cdar_DynamicArray_char_ptr_resize,\
    cutils_cdar_DynamicArray_short*:cutils_cdar_DynamicArray_short_resize,\
    cutils_cdar_DynamicArray_unsigned_short*:cutils_cdar_DynamicArray_unsigned_short_resize,\
    cutils_cdar_DynamicArray_int*:cutils_cdar_DynamicArray_int_resize,\
    cutils_cdar_DynamicArray_unsigned_int*:cutils_cdar_DynamicArray_unsigned_int_resize,\
    cutils_cdar_DynamicArray_long*:cutils_cdar_DynamicArray_long_resize,\
    cutils_cdar_DynamicArray_unsigned_long*:cutils_cdar_DynamicArray_unsigned_long_resize,\
    cutils_cdar_DynamicArray_long_long*:cutils_cdar_DynamicArray_long_long_resize,\
    cutils_cdar_DynamicArray_unsigned_long_long*:cutils_cdar_DynamicArray_unsigned_long_long_resize,\
    cutils_cdar_DynamicArray_float*:cutils_cdar_DynamicArray_float_resize,\
    cutils_cdar_DynamicArray_double*:cutils_cdar_DynamicArray_double_resize,\
    cutils_cdar_DynamicArray_long_double*:cutils_cdar_DynamicArray_long_double_resize,\
    cutils_cdar_DynamicArray_bool*:cutils_cdar_DynamicArray_bool_resize,\
    cutils_cdar_DynamicArray_size_t*:cutils_cdar_DynamicArray_size_t_resize,\
    cutils_cdar_DynamicArray_ptrdiff_t*:cutils_cdar_DynamicArray_ptrdiff_t_resize)\
    (object,##__VA_ARGS__)
/*----------------------------------------------------------------------------*/
#undef  __cutils_generic_truncate_args2
#define __cutils_generic_truncate_args2(object,...) _Generic((object),\
    cutils_cdar_DynamicArray_char*:cutils_cdar_DynamicArray_char_truncate,\
    cutils_cdar_DynamicArray_void_ptr*:cutils_cdar_DynamicArray_void_ptr_truncate,\
    cutils_cdar_DynamicArray_signed_char*:cutils_cdar_DynamicArray_signed_char_truncate,\
    cutils_cdar_DynamicArray_unsigned_char*:cutils_cdar_DynamicArray_unsigned_char_truncate,\
    cutils_cdar_DynamicArray_char_ptr*:cutils_cdar_DynamicArray_char_ptr_truncate,\
    cutils_cdar_DynamicArray_short*:cutils_cdar_DynamicArray_short_truncate,\
    cutils_cdar_DynamicArray_unsigned_short*:cutils_cdar_DynamicArray_unsigned_short_truncate,\
    cutils_cdar_DynamicArray_int*:cutils_cdar_DynamicArray_int_truncate,\
    cutils_cdar_DynamicArray_unsigned_int*:cutils_cdar_DynamicArray_unsigned_int_truncate,\
    cutils_cdar_DynamicArray_long*:cutils_cdar_DynamicArray_long_truncate,\
    cutils_cdar_DynamicArray_unsigned_long*:cutils_cdar_DynamicArray_unsigned_long_truncate,\
    cutils_cdar_DynamicArray_long_long*:cutils_cdar_DynamicArray_long_long_truncate,\
    cutils_cdar_DynamicArray_unsigned_long_long*:cutils_cdar_DynamicArray_unsigned_long_long_truncate,\
    cutils_cdar_DynamicArray_float*:cutils_cdar_DynamicArray_float_truncate,\
    cutils_cdar_DynamicArray_double*:cutils_cdar_DynamicArray_double_truncate,\
    cutils_cdar_DynamicArray_long_double*:cutils_cdar_DynamicArray_long_double_truncate,\
    cutils_cdar_DynamicArray_bool*:cutils_cdar_DynamicArray_bool_truncate,\
    cutils_cdar_DynamicArray_size_t*:cutils_cdar_DynamicArray_size_t_truncate,\
    cutils_cdar_DynamicArray_ptrdiff_t*:cutils_cdar_DynamicArray_ptrdiff_t_truncate,\
    cutils_csll_SinglyLinkedList_char*:cutils_csll_SinglyLinkedList_char_truncate,\
    cutils_csll_SinglyLinkedList_void_ptr*:cutils_csll_SinglyLinkedList_void_ptr_truncate,\
    cutils_csll_SinglyLinkedList_signed_char*:cutils_csll_SinglyLinkedList_signed_char_truncate,\
    cutils_csll_SinglyLinkedList_unsigned_char*:cutils_csll_SinglyLinkedList_unsigned_char_truncate,\
    cutils_csll_SinglyLinkedList_char_ptr*:cutils_csll_SinglyLinkedList_char_ptr_truncate,\
    cutils_csll_SinglyLinkedList_short*:cutils_csll_SinglyLinkedList_short_truncate,\
    cutils_csll_SinglyLinkedList_unsigned_short*:cutils_csll_SinglyLinkedList_unsigned_short_truncate,\
    cutils_csll_SinglyLinkedList_int*:cutils_csll_SinglyLinkedList_int_truncate,\
    cutils_csll_SinglyLinkedList_unsigned_int*:cutils_csll_SinglyLinkedList_unsigned_int_truncate,\
    cutils_csll_SinglyLinkedList_long*:cutils_csll_SinglyLinkedList_long_truncate,\
    cutils_csll_SinglyLinkedList_unsigned_long*:cutils_csll_SinglyLinkedList_unsigned_long_truncate,\
    cutils_csll_SinglyLinkedList_long_long*:cutils_csll_SinglyLinkedList_long_long_truncate,\
    cutils_csll_SinglyLinkedList_unsigned_long_long*:cutils_csll_SinglyLinkedList_unsigned_long_long_truncate,\
    cutils_csll_SinglyLinkedList_float*:cutils_csll_SinglyLinkedList_float_truncate,\
    cutils_csll_SinglyLinkedList_double*:cutils_csll_SinglyLinkedList_double_truncate,\
    cutils_csll_SinglyLinkedList_long_double*:cutils_csll_SinglyLinkedList_long_double_truncate,\
    cutils_csll_SinglyLinkedList_bool*:cutils_csll_SinglyLinkedList_bool_truncate,\
    cutils_csll_SinglyLinkedList_size_t*:cutils_csll_SinglyLinkedList_size_t_truncate,\
    cutils_csll_SinglyLinkedList_ptrdiff_t*:cutils_csll_SinglyLinkedList_ptrdiff_t_truncate)\
    (object,##__VA_ARGS__)
/*----------------------------------------------------------------------------*/
#undef  __cutils_generic_truncate_args1
#define __cutils_generic_truncate_args1(object,...) _Generic((object),\
    cutils_cdar_DynamicArray_char*:cutils_cdar_DynamicArray_char_truncate_default1,\
    cutils_cdar_DynamicArray_void_ptr*:cutils_cdar_DynamicArray_void_ptr_truncate_default1,\
    cutils_cdar_DynamicArray_signed_char*:cutils_cdar_DynamicArray_signed_char_truncate_default1,\
    cutils_cdar_DynamicArray_unsigned_char*:cutils_cdar_DynamicArray_unsigned_char_truncate_default1,\
    cutils_cdar_DynamicArray_char_ptr*:cutils_cdar_DynamicArray_char_ptr_truncate_default1,\
    cutils_cdar_DynamicArray_short*:cutils_cdar_DynamicArray_short_truncate_default1,\
    cutils_cdar_DynamicArray_unsigned_short*:cutils_cdar_DynamicArray_unsigned_short_truncate_default1,\
    cutils_cdar_DynamicArray_int*:cutils_cdar_DynamicArray_int_truncate_default1,\
    cutils_cdar_DynamicArray_unsigned_int*:cutils_cdar_DynamicArray_unsigned_int_truncate_default1,\
    cutils_cdar_DynamicArray_long*:cutils_cdar_DynamicArray_long_truncate_default1,\
    cutils_cdar_DynamicArray_unsigned_long*:cutils_cdar_DynamicArray_unsigned_long_truncate_default1,\
    cutils_cdar_DynamicArray_long_long*:cutils_cdar_DynamicArray_long_long_truncate_default1,\
    cutils_cdar_DynamicArray_unsigned_long_long*:cutils_cdar_DynamicArray_unsigned_long_long_truncate_default1,\
    cutils_cdar_DynamicArray_float*:cutils_cdar_DynamicArray_float_truncate_default1,\
    cutils_cdar_DynamicArray_double*:cutils_cdar_DynamicArray_double_truncate_default1,\
    cutils_cdar_DynamicArray_long_double*:cutils_cdar_DynamicArray_long_double_truncate_default1,\
    cutils_cdar_DynamicArray_bool*:cutils_cdar_DynamicArray_bool_truncate_default1,\
    cutils_cdar_DynamicArray_size_t*:cutils_cdar_DynamicArray_size_t_truncate_default1,\
    cutils_cdar_DynamicArray_ptrdiff_t*:cutils_cdar_DynamicArray_ptrdiff_t_truncate_default1,\
    cutils_csll_SinglyLinkedList_char*:cutils_csll_SinglyLinkedList_char_truncate_default1,\
    cutils_csll_SinglyLinkedList_signed_char*:cutils_csll_SinglyLinkedList_signed_char_truncate_default1,\
    cutils_csll_SinglyLinkedList_unsigned_char*:cutils_csll_SinglyLinkedList_unsigned_char_truncate_default1,\
    cutils_csll_SinglyLinkedList_char_ptr*:cutils_csll_SinglyLinkedList_char_ptr_truncate_default1,\
    cutils_csll_SinglyLinkedList_short*:cutils_csll_SinglyLinkedList_short_truncate_default1,\
    cutils_csll_SinglyLinkedList_unsigned_short*:cutils_csll_SinglyLinkedList_unsigned_short_truncate_default1,\
    cutils_csll_SinglyLinkedList_int*:cutils_csll_SinglyLinkedList_int_truncate_default1,\
    cutils_csll_SinglyLinkedList_unsigned_int*:cutils_csll_SinglyLinkedList_unsigned_int_truncate_default1,\
    cutils_csll_SinglyLinkedList_long*:cutils_csll_SinglyLinkedList_long_truncate_default1,\
    cutils_csll_SinglyLinkedList_unsigned_long*:cutils_csll_SinglyLinkedList_unsigned_long_truncate_default1,\
    cutils_csll_SinglyLinkedList_long_long*:cutils_csll_SinglyLinkedList_long_long_truncate_default1,\
    cutils_csll_SinglyLinkedList_unsigned_long_long*:cutils_csll_SinglyLinkedList_unsigned_long_long_truncate_default1,\
    cutils_csll_SinglyLinkedList_float*:cutils_csll_SinglyLinkedList_float_truncate_default1,\
    cutils_csll_SinglyLinkedList_double*:cutils_csll_SinglyLinkedList_double_truncate_default1,\
    cutils_csll_SinglyLinkedList_long_double*:cutils_csll_SinglyLinkedList_long_double_truncate_default1,\
    cutils_csll_SinglyLinkedList_bool*:cutils_csll_SinglyLinkedList_bool_truncate_default1,\
    cutils_csll_SinglyLinkedList_size_t*:cutils_csll_SinglyLinkedList_size_t_truncate_default1,\
    cutils_csll_SinglyLinkedList_ptrdiff_t*:cutils_csll_SinglyLinkedList_ptrdiff_t_truncate_default1)\
    (object,##__VA_ARGS__)
/*----------------------------------------------------------------------------*/
#undef  __cutils_generic_clear
#define __cutils_generic_clear(object,...) _Generic((object),\
    cutils_cdar_DynamicArray_char*:cutils_cdar_DynamicArray_char_clear,\
    cutils_cdar_DynamicArray_void_ptr*:cutils_cdar_DynamicArray_void_ptr_clear,\
    cutils_cdar_DynamicArray_signed_char*:cutils_cdar_DynamicArray_signed_char_clear,\
    cutils_cdar_DynamicArray_unsigned_char*:cutils_cdar_DynamicArray_unsigned_char_clear,\
    cutils_cdar_DynamicArray_char_ptr*:cutils_cdar_DynamicArray_char_ptr_clear,\
    cutils_cdar_DynamicArray_short*:cutils_cdar_DynamicArray_short_clear,\
    cutils_cdar_DynamicArray_unsigned_short*:cutils_cdar_DynamicArray_unsigned_short_clear,\
    cutils_cdar_DynamicArray_int*:cutils_cdar_DynamicArray_int_clear,\
    cutils_cdar_DynamicArray_unsigned_int*:cutils_cdar_DynamicArray_unsigned_int_clear,\
    cutils_cdar_DynamicArray_long*:cutils_cdar_DynamicArray_long_clear,\
    cutils_cdar_DynamicArray_unsigned_long*:cutils_cdar_DynamicArray_unsigned_long_clear,\
    cutils_cdar_DynamicArray_long_long*:cutils_cdar_DynamicArray_long_long_clear,\
    cutils_cdar_DynamicArray_unsigned_long_long*:cutils_cdar_DynamicArray_unsigned_long_long_clear,\
    cutils_cdar_DynamicArray_float*:cutils_cdar_DynamicArray_float_clear,\
    cutils_cdar_DynamicArray_double*:cutils_cdar_DynamicArray_double_clear,\
    cutils_cdar_DynamicArray_long_double*:cutils_cdar_DynamicArray_long_double_clear,\
    cutils_cdar_DynamicArray_bool*:cutils_cdar_DynamicArray_bool_clear,\
    cutils_cdar_DynamicArray_size_t*:cutils_cdar_DynamicArray_size_t_clear,\
    cutils_cdar_DynamicArray_ptrdiff_t*:cutils_cdar_DynamicArray_ptrdiff_t_clear,\
    cutils_csll_SinglyLinkedList_char*:cutils_csll_SinglyLinkedList_char_clear,\
    cutils_csll_SinglyLinkedList_void_ptr*:cutils_csll_SinglyLinkedList_void_ptr_clear,\
    cutils_csll_SinglyLinkedList_signed_char*:cutils_csll_SinglyLinkedList_signed_char_clear,\
    cutils_csll_SinglyLinkedList_unsigned_char*:cutils_csll_SinglyLinkedList_unsigned_char_clear,\
    cutils_csll_SinglyLinkedList_char_ptr*:cutils_csll_SinglyLinkedList_char_ptr_clear,\
    cutils_csll_SinglyLinkedList_short*:cutils_csll_SinglyLinkedList_short_clear,\
    cutils_csll_SinglyLinkedList_unsigned_short*:cutils_csll_SinglyLinkedList_unsigned_short_clear,\
    cutils_csll_SinglyLinkedList_int*:cutils_csll_SinglyLinkedList_int_clear,\
    cutils_csll_SinglyLinkedList_unsigned_int*:cutils_csll_SinglyLinkedList_unsigned_int_clear,\
    cutils_csll_SinglyLinkedList_long*:cutils_csll_SinglyLinkedList_long_clear,\
    cutils_csll_SinglyLinkedList_unsigned_long*:cutils_csll_SinglyLinkedList_unsigned_long_clear,\
    cutils_csll_SinglyLinkedList_long_long*:cutils_csll_SinglyLinkedList_long_long_clear,\
    cutils_csll_SinglyLinkedList_unsigned_long_long*:cutils_csll_SinglyLinkedList_unsigned_long_long_clear,\
    cutils_csll_SinglyLinkedList_float*:cutils_csll_SinglyLinkedList_float_clear,\
    cutils_csll_SinglyLinkedList_double*:cutils_csll_SinglyLinkedList_double_clear,\
    cutils_csll_SinglyLinkedList_long_double*:cutils_csll_SinglyLinkedList_long_double_clear,\
    cutils_csll_SinglyLinkedList_bool*:cutils_csll_SinglyLinkedList_bool_clear,\
    cutils_csll_SinglyLinkedList_size_t*:cutils_csll_SinglyLinkedList_size_t_clear,\
    cutils_csll_SinglyLinkedList_ptrdiff_t*:cutils_csll_SinglyLinkedList_ptrdiff_t_clear)\
    (object,##__VA_ARGS__)
/*----------------------------------------------------------------------------*/
#undef  __cutils_generic_swap_args4
#define __cutils_generic_swap_args4(object,...) _Generic((object),\
    cutils_cdar_DynamicArray_char*:cutils_cdar_DynamicArray_char_swap,\
    cutils_cdar_DynamicArray_void_ptr*:cutils_cdar_DynamicArray_void_ptr_swap,\
    cutils_cdar_DynamicArray_signed_char*:cutils_cdar_DynamicArray_signed_char_swap,\
    cutils_cdar_DynamicArray_unsigned_char*:cutils_cdar_DynamicArray_unsigned_char_swap,\
    cutils_cdar_DynamicArray_char_ptr*:cutils_cdar_DynamicArray_char_ptr_swap,\
    cutils_cdar_DynamicArray_short*:cutils_cdar_DynamicArray_short_swap,\
    cutils_cdar_DynamicArray_unsigned_short*:cutils_cdar_DynamicArray_unsigned_short_swap,\
    cutils_cdar_DynamicArray_int*:cutils_cdar_DynamicArray_int_swap,\
    cutils_cdar_DynamicArray_unsigned_int*:cutils_cdar_DynamicArray_unsigned_int_swap,\
    cutils_cdar_DynamicArray_long*:cutils_cdar_DynamicArray_long_swap,\
    cutils_cdar_DynamicArray_unsigned_long*:cutils_cdar_DynamicArray_unsigned_long_swap,\
    cutils_cdar_DynamicArray_long_long*:cutils_cdar_DynamicArray_long_long_swap,\
    cutils_cdar_DynamicArray_unsigned_long_long*:cutils_cdar_DynamicArray_unsigned_long_long_swap,\
    cutils_cdar_DynamicArray_float*:cutils_cdar_DynamicArray_float_swap,\
    cutils_cdar_DynamicArray_double*:cutils_cdar_DynamicArray_double_swap,\
    cutils_cdar_DynamicArray_long_double*:cutils_cdar_DynamicArray_long_double_swap,\
    cutils_cdar_DynamicArray_bool*:cutils_cdar_DynamicArray_bool_swap,\
    cutils_cdar_DynamicArray_size_t*:cutils_cdar_DynamicArray_size_t_swap,\
    cutils_cdar_DynamicArray_ptrdiff_t*:cutils_cdar_DynamicArray_ptrdiff_t_swap,\
    cutils_csll_SinglyLinkedList_char*:cutils_csll_SinglyLinkedList_char_swap,\
    cutils_csll_SinglyLinkedList_void_ptr*:cutils_csll_SinglyLinkedList_void_ptr_swap,\
    cutils_csll_SinglyLinkedList_signed_char*:cutils_csll_SinglyLinkedList_signed_char_swap,\
    cutils_csll_SinglyLinkedList_unsigned_char*:cutils_csll_SinglyLinkedList_unsigned_char_swap,\
    cutils_csll_SinglyLinkedList_char_ptr*:cutils_csll_SinglyLinkedList_char_ptr_swap,\
    cutils_csll_SinglyLinkedList_short*:cutils_csll_SinglyLinkedList_short_swap,\
    cutils_csll_SinglyLinkedList_unsigned_short*:cutils_csll_SinglyLinkedList_unsigned_short_swap,\
    cutils_csll_SinglyLinkedList_int*:cutils_csll_SinglyLinkedList_int_swap,\
    cutils_csll_SinglyLinkedList_unsigned_int*:cutils_csll_SinglyLinkedList_unsigned_int_swap,\
    cutils_csll_SinglyLinkedList_long*:cutils_csll_SinglyLinkedList_long_swap,\
    cutils_csll_SinglyLinkedList_unsigned_long*:cutils_csll_SinglyLinkedList_unsigned_long_swap,\
    cutils_csll_SinglyLinkedList_long_long*:cutils_csll_SinglyLinkedList_long_long_swap,\
    cutils_csll_SinglyLinkedList_unsigned_long_long*:cutils_csll_SinglyLinkedList_unsigned_long_long_swap,\
    cutils_csll_SinglyLinkedList_float*:cutils_csll_SinglyLinkedList_float_swap,\
    cutils_csll_SinglyLinkedList_double*:cutils_csll_SinglyLinkedList_double_swap,\
    cutils_csll_SinglyLinkedList_long_double*:cutils_csll_SinglyLinkedList_long_double_swap,\
    cutils_csll_SinglyLinkedList_bool*:cutils_csll_SinglyLinkedList_bool_swap,\
    cutils_csll_SinglyLinkedList_size_t*:cutils_csll_SinglyLinkedList_size_t_swap,\
    cutils_csll_SinglyLinkedList_ptrdiff_t*:cutils_csll_SinglyLinkedList_ptrdiff_t_swap)\
    (object,##__VA_ARGS__)
/*----------------------------------------------------------------------------*/
#undef  __cutils_generic_swap_args3
#define __cutils_generic_swap_args3(object,...) _Generic((object),\
    cutils_cdar_DynamicArray_char*:cutils_cdar_DynamicArray_char_swap_default3,\
    cutils_cdar_DynamicArray_void_ptr*:cutils_cdar_DynamicArray_void_ptr_swap_default3,\
    cutils_cdar_DynamicArray_signed_char*:cutils_cdar_DynamicArray_signed_char_swap_default3,\
    cutils_cdar_DynamicArray_unsigned_char*:cutils_cdar_DynamicArray_unsigned_char_swap_default3,\
    cutils_cdar_DynamicArray_char_ptr*:cutils_cdar_DynamicArray_char_ptr_swap_default3,\
    cutils_cdar_DynamicArray_short*:cutils_cdar_DynamicArray_short_swap_default3,\
    cutils_cdar_DynamicArray_unsigned_short*:cutils_cdar_DynamicArray_unsigned_short_swap_default3,\
    cutils_cdar_DynamicArray_int*:cutils_cdar_DynamicArray_int_swap_default3,\
    cutils_cdar_DynamicArray_unsigned_int*:cutils_cdar_DynamicArray_unsigned_int_swap_default3,\
    cutils_cdar_DynamicArray_long*:cutils_cdar_DynamicArray_long_swap_default3,\
    cutils_cdar_DynamicArray_unsigned_long*:cutils_cdar_DynamicArray_unsigned_long_swap_default3,\
    cutils_cdar_DynamicArray_long_long*:cutils_cdar_DynamicArray_long_long_swap_default3,\
    cutils_cdar_DynamicArray_unsigned_long_long*:cutils_cdar_DynamicArray_unsigned_long_long_swap_default3,\
    cutils_cdar_DynamicArray_float*:cutils_cdar_DynamicArray_float_swap_default3,\
    cutils_cdar_DynamicArray_double*:cutils_cdar_DynamicArray_double_swap_default3,\
    cutils_cdar_DynamicArray_long_double*:cutils_cdar_DynamicArray_long_double_swap_default3,\
    cutils_cdar_DynamicArray_bool*:cutils_cdar_DynamicArray_bool_swap_default3,\
    cutils_cdar_DynamicArray_size_t*:cutils_cdar_DynamicArray_size_t_swap_default3,\
    cutils_cdar_DynamicArray_ptrdiff_t*:cutils_cdar_DynamicArray_ptrdiff_t_swap_default3,\
    cutils_csll_SinglyLinkedList_char*:cutils_csll_SinglyLinkedList_char_swap_default3,\
    cutils_csll_SinglyLinkedList_void_ptr*:cutils_csll_SinglyLinkedList_void_ptr_swap_default3,\
    cutils_csll_SinglyLinkedList_signed_char*:cutils_csll_SinglyLinkedList_signed_char_swap_default3,\
    cutils_csll_SinglyLinkedList_unsigned_char*:cutils_csll_SinglyLinkedList_unsigned_char_swap_default3,\
    cutils_csll_SinglyLinkedList_char_ptr*:cutils_csll_SinglyLinkedList_char_ptr_swap_default3,\
    cutils_csll_SinglyLinkedList_short*:cutils_csll_SinglyLinkedList_short_swap_default3,\
    cutils_csll_SinglyLinkedList_unsigned_short*:cutils_csll_SinglyLinkedList_unsigned_short_swap_default3,\
    cutils_csll_SinglyLinkedList_int*:cutils_csll_SinglyLinkedList_int_swap_default3,\
    cutils_csll_SinglyLinkedList_unsigned_int*:cutils_csll_SinglyLinkedList_unsigned_int_swap_default3,\
    cutils_csll_SinglyLinkedList_long*:cutils_csll_SinglyLinkedList_long_swap_default3,\
    cutils_csll_SinglyLinkedList_unsigned_long*:cutils_csll_SinglyLinkedList_unsigned_long_swap_default3,\
    cutils_csll_SinglyLinkedList_long_long*:cutils_csll_SinglyLinkedList_long_long_swap_default3,\
    cutils_csll_SinglyLinkedList_unsigned_long_long*:cutils_csll_SinglyLinkedList_unsigned_long_long_swap_default3,\
    cutils_csll_SinglyLinkedList_float*:cutils_csll_SinglyLinkedList_float_swap_default3,\
    cutils_csll_SinglyLinkedList_double*:cutils_csll_SinglyLinkedList_double_swap_default3,\
    cutils_csll_SinglyLinkedList_long_double*:cutils_csll_SinglyLinkedList_long_double_swap_default3,\
    cutils_csll_SinglyLinkedList_bool*:cutils_csll_SinglyLinkedList_bool_swap_default3,\
    cutils_csll_SinglyLinkedList_size_t*:cutils_csll_SinglyLinkedList_size_t_swap_default3,\
    cutils_csll_SinglyLinkedList_ptrdiff_t*:cutils_csll_SinglyLinkedList_ptrdiff_t_swap_default3)\
    (object,##__VA_ARGS__)
/*----------------------------------------------------------------------------*/
#undef  __cutils_generic_reverse
#define __cutils_generic_reverse(object,...) _Generic((object),\
    cutils_cdar_DynamicArray_char*:cutils_cdar_DynamicArray_char_reverse,\
    cutils_cdar_DynamicArray_void_ptr*:cutils_cdar_DynamicArray_void_ptr_reverse,\
    cutils_cdar_DynamicArray_signed_char*:cutils_cdar_DynamicArray_signed_char_reverse,\
    cutils_cdar_DynamicArray_unsigned_char*:cutils_cdar_DynamicArray_unsigned_char_reverse,\
    cutils_cdar_DynamicArray_char_ptr*:cutils_cdar_DynamicArray_char_ptr_reverse,\
    cutils_cdar_DynamicArray_short*:cutils_cdar_DynamicArray_short_reverse,\
    cutils_cdar_DynamicArray_unsigned_short*:cutils_cdar_DynamicArray_unsigned_short_reverse,\
    cutils_cdar_DynamicArray_int*:cutils_cdar_DynamicArray_int_reverse,\
    cutils_cdar_DynamicArray_unsigned_int*:cutils_cdar_DynamicArray_unsigned_int_reverse,\
    cutils_cdar_DynamicArray_long*:cutils_cdar_DynamicArray_long_reverse,\
    cutils_cdar_DynamicArray_unsigned_long*:cutils_cdar_DynamicArray_unsigned_long_reverse,\
    cutils_cdar_DynamicArray_long_long*:cutils_cdar_DynamicArray_long_long_reverse,\
    cutils_cdar_DynamicArray_unsigned_long_long*:cutils_cdar_DynamicArray_unsigned_long_long_reverse,\
    cutils_cdar_DynamicArray_float*:cutils_cdar_DynamicArray_float_reverse,\
    cutils_cdar_DynamicArray_double*:cutils_cdar_DynamicArray_double_reverse,\
    cutils_cdar_DynamicArray_long_double*:cutils_cdar_DynamicArray_long_double_reverse,\
    cutils_cdar_DynamicArray_bool*:cutils_cdar_DynamicArray_bool_reverse,\
    cutils_cdar_DynamicArray_size_t*:cutils_cdar_DynamicArray_size_t_reverse,\
    cutils_cdar_DynamicArray_ptrdiff_t*:cutils_cdar_DynamicArray_ptrdiff_t_reverse,\
    cutils_csll_SinglyLinkedList_char*:cutils_csll_SinglyLinkedList_char_reverse,\
    cutils_csll_SinglyLinkedList_void_ptr*:cutils_csll_SinglyLinkedList_void_ptr_reverse,\
    cutils_csll_SinglyLinkedList_signed_char*:cutils_csll_SinglyLinkedList_signed_char_reverse,\
    cutils_csll_SinglyLinkedList_unsigned_char*:cutils_csll_SinglyLinkedList_unsigned_char_reverse,\
    cutils_csll_SinglyLinkedList_char_ptr*:cutils_csll_SinglyLinkedList_char_ptr_reverse,\
    cutils_csll_SinglyLinkedList_short*:cutils_csll_SinglyLinkedList_short_reverse,\
    cutils_csll_SinglyLinkedList_unsigned_short*:cutils_csll_SinglyLinkedList_unsigned_short_reverse,\
    cutils_csll_SinglyLinkedList_int*:cutils_csll_SinglyLinkedList_int_reverse,\
    cutils_csll_SinglyLinkedList_unsigned_int*:cutils_csll_SinglyLinkedList_unsigned_int_reverse,\
    cutils_csll_SinglyLinkedList_long*:cutils_csll_SinglyLinkedList_long_reverse,\
    cutils_csll_SinglyLinkedList_unsigned_long*:cutils_csll_SinglyLinkedList_unsigned_long_reverse,\
    cutils_csll_SinglyLinkedList_long_long*:cutils_csll_SinglyLinkedList_long_long_reverse,\
    cutils_csll_SinglyLinkedList_unsigned_long_long*:cutils_csll_SinglyLinkedList_unsigned_long_long_reverse,\
    cutils_csll_SinglyLinkedList_float*:cutils_csll_SinglyLinkedList_float_reverse,\
    cutils_csll_SinglyLinkedList_double*:cutils_csll_SinglyLinkedList_double_reverse,\
    cutils_csll_SinglyLinkedList_long_double*:cutils_csll_SinglyLinkedList_long_double_reverse,\
    cutils_csll_SinglyLinkedList_bool*:cutils_csll_SinglyLinkedList_bool_reverse,\
    cutils_csll_SinglyLinkedList_size_t*:cutils_csll_SinglyLinkedList_size_t_reverse,\
    cutils_csll_SinglyLinkedList_ptrdiff_t*:cutils_csll_SinglyLinkedList_ptrdiff_t_reverse)\
    (object,##__VA_ARGS__)
/*----------------------------------------------------------------------------*/
#undef  __cutils_generic_append_args4
#define __cutils_generic_append_args4(object,...) _Generic((object),\
    cutils_csll_SinglyLinkedList_void_ptr*:cutils_csll_SinglyLinkedList_void_ptr_append)\
    (object,##__VA_ARGS__)
/*----------------------------------------------------------------------------*/
#undef  __cutils_generic_append_args3
#define __cutils_generic_append_args3(object,...) _Generic((object),\
    cutils_cdar_DynamicArray_char*:cutils_cdar_DynamicArray_char_append,\
    cutils_cdar_DynamicArray_void_ptr*:cutils_cdar_DynamicArray_void_ptr_append,\
    cutils_cdar_DynamicArray_signed_char*:cutils_cdar_DynamicArray_signed_char_append,\
    cutils_cdar_DynamicArray_unsigned_char*:cutils_cdar_DynamicArray_unsigned_char_append,\
    cutils_cdar_DynamicArray_char_ptr*:cutils_cdar_DynamicArray_char_ptr_append,\
    cutils_cdar_DynamicArray_short*:cutils_cdar_DynamicArray_short_append,\
    cutils_cdar_DynamicArray_unsigned_short*:cutils_cdar_DynamicArray_unsigned_short_append,\
    cutils_cdar_DynamicArray_int*:cutils_cdar_DynamicArray_int_append,\
    cutils_cdar_DynamicArray_unsigned_int*:cutils_cdar_DynamicArray_unsigned_int_append,\
    cutils_cdar_DynamicArray_long*:cutils_cdar_DynamicArray_long_append,\
    cutils_cdar_DynamicArray_unsigned_long*:cutils_cdar_DynamicArray_unsigned_long_append,\
    cutils_cdar_DynamicArray_long_long*:cutils_cdar_DynamicArray_long_long_append,\
    cutils_cdar_DynamicArray_unsigned_long_long*:cutils_cdar_DynamicArray_unsigned_long_long_append,\
    cutils_cdar_DynamicArray_float*:cutils_cdar_DynamicArray_float_append,\
    cutils_cdar_DynamicArray_double*:cutils_cdar_DynamicArray_double_append,\
    cutils_cdar_DynamicArray_long_double*:cutils_cdar_DynamicArray_long_double_append,\
    cutils_cdar_DynamicArray_bool*:cutils_cdar_DynamicArray_bool_append,\
    cutils_cdar_DynamicArray_size_t*:cutils_cdar_DynamicArray_size_t_append,\
    cutils_cdar_DynamicArray_ptrdiff_t*:cutils_cdar_DynamicArray_ptrdiff_t_append,\
    cutils_csll_SinglyLinkedList_char*:cutils_csll_SinglyLinkedList_char_append,\
    cutils_csll_SinglyLinkedList_void_ptr*:cutils_csll_SinglyLinkedList_void_ptr_append_default3,\
    cutils_csll_SinglyLinkedList_signed_char*:cutils_csll_SinglyLinkedList_signed_char_append,\
    cutils_csll_SinglyLinkedList_unsigned_char*:cutils_csll_SinglyLinkedList_unsigned_char_append,\
    cutils_csll_SinglyLinkedList_char_ptr*:cutils_csll_SinglyLinkedList_char_ptr_append,\
    cutils_csll_SinglyLinkedList_short*:cutils_csll_SinglyLinkedList_short_append,\
    cutils_csll_SinglyLinkedList_unsigned_short*:cutils_csll_SinglyLinkedList_unsigned_short_append,\
    cutils_csll_SinglyLinkedList_int*:cutils_csll_SinglyLinkedList_int_append,\
    cutils_csll_SinglyLinkedList_unsigned_int*:cutils_csll_SinglyLinkedList_unsigned_int_append,\
    cutils_csll_SinglyLinkedList_long*:cutils_csll_SinglyLinkedList_long_append,\
    cutils_csll_SinglyLinkedList_unsigned_long*:cutils_csll_SinglyLinkedList_unsigned_long_append,\
    cutils_csll_SinglyLinkedList_long_long*:cutils_csll_SinglyLinkedList_long_long_append,\
    cutils_csll_SinglyLinkedList_unsigned_long_long*:cutils_csll_SinglyLinkedList_unsigned_long_long_append,\
    cutils_csll_SinglyLinkedList_float*:cutils_csll_SinglyLinkedList_float_append,\
    cutils_csll_SinglyLinkedList_double*:cutils_csll_SinglyLinkedList_double_append,\
    cutils_csll_SinglyLinkedList_long_double*:cutils_csll_SinglyLinkedList_long_double_append,\
    cutils_csll_SinglyLinkedList_bool*:cutils_csll_SinglyLinkedList_bool_append,\
    cutils_csll_SinglyLinkedList_size_t*:cutils_csll_SinglyLinkedList_size_t_append,\
    cutils_csll_SinglyLinkedList_ptrdiff_t*:cutils_csll_SinglyLinkedList_ptrdiff_t_append)\
    (object,##__VA_ARGS__)
/*----------------------------------------------------------------------------*/
#undef  __cutils_generic_append_args2
#define __cutils_generic_append_args2(object,...) _Generic((object),\
    cutils_cdar_DynamicArray_char*:cutils_cdar_DynamicArray_char_append_default2,\
    cutils_cdar_DynamicArray_void_ptr*:cutils_cdar_DynamicArray_void_ptr_append_default2,\
    cutils_cdar_DynamicArray_signed_char*:cutils_cdar_DynamicArray_signed_char_append_default2,\
    cutils_cdar_DynamicArray_unsigned_char*:cutils_cdar_DynamicArray_unsigned_char_append_default2,\
    cutils_cdar_DynamicArray_char_ptr*:cutils_cdar_DynamicArray_char_ptr_append_default2,\
    cutils_cdar_DynamicArray_short*:cutils_cdar_DynamicArray_short_append_default2,\
    cutils_cdar_DynamicArray_unsigned_short*:cutils_cdar_DynamicArray_unsigned_short_append_default2,\
    cutils_cdar_DynamicArray_int*:cutils_cdar_DynamicArray_int_append_default2,\
    cutils_cdar_DynamicArray_unsigned_int*:cutils_cdar_DynamicArray_unsigned_int_append_default2,\
    cutils_cdar_DynamicArray_long*:cutils_cdar_DynamicArray_long_append_default2,\
    cutils_cdar_DynamicArray_unsigned_long*:cutils_cdar_DynamicArray_unsigned_long_append_default2,\
    cutils_cdar_DynamicArray_long_long*:cutils_cdar_DynamicArray_long_long_append_default2,\
    cutils_cdar_DynamicArray_unsigned_long_long*:cutils_cdar_DynamicArray_unsigned_long_long_append_default2,\
    cutils_cdar_DynamicArray_float*:cutils_cdar_DynamicArray_float_append_default2,\
    cutils_cdar_DynamicArray_double*:cutils_cdar_DynamicArray_double_append_default2,\
    cutils_cdar_DynamicArray_long_double*:cutils_cdar_DynamicArray_long_double_append_default2,\
    cutils_cdar_DynamicArray_bool*:cutils_cdar_DynamicArray_bool_append_default2,\
    cutils_cdar_DynamicArray_size_t*:cutils_cdar_DynamicArray_size_t_append_default2,\
    cutils_cdar_DynamicArray_ptrdiff_t*:cutils_cdar_DynamicArray_ptrdiff_t_append_default2,\
    cutils_csll_SinglyLinkedList_char*:cutils_csll_SinglyLinkedList_char_append_default2,\
    cutils_csll_SinglyLinkedList_signed_char*:cutils_csll_SinglyLinkedList_signed_char_append_default2,\
    cutils_csll_SinglyLinkedList_unsigned_char*:cutils_csll_SinglyLinkedList_unsigned_char_append_default2,\
    cutils_csll_SinglyLinkedList_char_ptr*:cutils_csll_SinglyLinkedList_char_ptr_append_default2,\
    cutils_csll_SinglyLinkedList_short*:cutils_csll_SinglyLinkedList_short_append_default2,\
    cutils_csll_SinglyLinkedList_unsigned_short*:cutils_csll_SinglyLinkedList_unsigned_short_append_default2,\
    cutils_csll_SinglyLinkedList_int*:cutils_csll_SinglyLinkedList_int_append_default2,\
    cutils_csll_SinglyLinkedList_unsigned_int*:cutils_csll_SinglyLinkedList_unsigned_int_append_default2,\
    cutils_csll_SinglyLinkedList_long*:cutils_csll_SinglyLinkedList_long_append_default2,\
    cutils_csll_SinglyLinkedList_unsigned_long*:cutils_csll_SinglyLinkedList_unsigned_long_append_default2,\
    cutils_csll_SinglyLinkedList_long_long*:cutils_csll_SinglyLinkedList_long_long_append_default2,\
    cutils_csll_SinglyLinkedList_unsigned_long_long*:cutils_csll_SinglyLinkedList_unsigned_long_long_append_default2,\
    cutils_csll_SinglyLinkedList_float*:cutils_csll_SinglyLinkedList_float_append_default2,\
    cutils_csll_SinglyLinkedList_double*:cutils_csll_SinglyLinkedList_double_append_default2,\
    cutils_csll_SinglyLinkedList_long_double*:cutils_csll_SinglyLinkedList_long_double_append_default2,\
    cutils_csll_SinglyLinkedList_bool*:cutils_csll_SinglyLinkedList_bool_append_default2,\
    cutils_csll_SinglyLinkedList_size_t*:cutils_csll_SinglyLinkedList_size_t_append_default2,\
    cutils_csll_SinglyLinkedList_ptrdiff_t*:cutils_csll_SinglyLinkedList_ptrdiff_t_append_default2)\
    (object,##__VA_ARGS__)
/*----------------------------------------------------------------------------*/
#undef  __cutils_generic_push_args5
#define __cutils_generic_push_args5(object,...) _Generic((object),\
    cutils_csll_SinglyLinkedList_void_ptr*:cutils_csll_SinglyLinkedList_void_ptr_push)\
    (object,##__VA_ARGS__)
/*----------------------------------------------------------------------------*/
#undef  __cutils_generic_push_args4
#define __cutils_generic_push_args4(object,...) _Generic((object),\
    cutils_cdar_DynamicArray_char*:cutils_cdar_DynamicArray_char_push,\
    cutils_cdar_DynamicArray_void_ptr*:cutils_cdar_DynamicArray_void_ptr_push,\
    cutils_cdar_DynamicArray_signed_char*:cutils_cdar_DynamicArray_signed_char_push,\
    cutils_cdar_DynamicArray_unsigned_char*:cutils_cdar_DynamicArray_unsigned_char_push,\
    cutils_cdar_DynamicArray_char_ptr*:cutils_cdar_DynamicArray_char_ptr_push,\
    cutils_cdar_DynamicArray_short*:cutils_cdar_DynamicArray_short_push,\
    cutils_cdar_DynamicArray_unsigned_short*:cutils_cdar_DynamicArray_unsigned_short_push,\
    cutils_cdar_DynamicArray_int*:cutils_cdar_DynamicArray_int_push,\
    cutils_cdar_DynamicArray_unsigned_int*:cutils_cdar_DynamicArray_unsigned_int_push,\
    cutils_cdar_DynamicArray_long*:cutils_cdar_DynamicArray_long_push,\
    cutils_cdar_DynamicArray_unsigned_long*:cutils_cdar_DynamicArray_unsigned_long_push,\
    cutils_cdar_DynamicArray_long_long*:cutils_cdar_DynamicArray_long_long_push,\
    cutils_cdar_DynamicArray_unsigned_long_long*:cutils_cdar_DynamicArray_unsigned_long_long_push,\
    cutils_cdar_DynamicArray_float*:cutils_cdar_DynamicArray_float_push,\
    cutils_cdar_DynamicArray_double*:cutils_cdar_DynamicArray_double_push,\
    cutils_cdar_DynamicArray_long_double*:cutils_cdar_DynamicArray_long_double_push,\
    cutils_cdar_DynamicArray_bool*:cutils_cdar_DynamicArray_bool_push,\
    cutils_cdar_DynamicArray_size_t*:cutils_cdar_DynamicArray_size_t_push,\
    cutils_cdar_DynamicArray_ptrdiff_t*:cutils_cdar_DynamicArray_ptrdiff_t_push,\
    cutils_csll_SinglyLinkedList_char*:cutils_csll_SinglyLinkedList_char_push,\
    cutils_csll_SinglyLinkedList_void_ptr*:cutils_csll_SinglyLinkedList_void_ptr_push_default4,\
    cutils_csll_SinglyLinkedList_signed_char*:cutils_csll_SinglyLinkedList_signed_char_push,\
    cutils_csll_SinglyLinkedList_unsigned_char*:cutils_csll_SinglyLinkedList_unsigned_char_push,\
    cutils_csll_SinglyLinkedList_char_ptr*:cutils_csll_SinglyLinkedList_char_ptr_push,\
    cutils_csll_SinglyLinkedList_short*:cutils_csll_SinglyLinkedList_short_push,\
    cutils_csll_SinglyLinkedList_unsigned_short*:cutils_csll_SinglyLinkedList_unsigned_short_push,\
    cutils_csll_SinglyLinkedList_int*:cutils_csll_SinglyLinkedList_int_push,\
    cutils_csll_SinglyLinkedList_unsigned_int*:cutils_csll_SinglyLinkedList_unsigned_int_push,\
    cutils_csll_SinglyLinkedList_long*:cutils_csll_SinglyLinkedList_long_push,\
    cutils_csll_SinglyLinkedList_unsigned_long*:cutils_csll_SinglyLinkedList_unsigned_long_push,\
    cutils_csll_SinglyLinkedList_long_long*:cutils_csll_SinglyLinkedList_long_long_push,\
    cutils_csll_SinglyLinkedList_unsigned_long_long*:cutils_csll_SinglyLinkedList_unsigned_long_long_push,\
    cutils_csll_SinglyLinkedList_float*:cutils_csll_SinglyLinkedList_float_push,\
    cutils_csll_SinglyLinkedList_double*:cutils_csll_SinglyLinkedList_double_push,\
    cutils_csll_SinglyLinkedList_long_double*:cutils_csll_SinglyLinkedList_long_double_push,\
    cutils_csll_SinglyLinkedList_bool*:cutils_csll_SinglyLinkedList_bool_push,\
    cutils_csll_SinglyLinkedList_size_t*:cutils_csll_SinglyLinkedList_size_t_push,\
    cutils_csll_SinglyLinkedList_ptrdiff_t*:cutils_csll_SinglyLinkedList_ptrdiff_t_push)\
    (object,##__VA_ARGS__)
/*----------------------------------------------------------------------------*/
#undef  __cutils_generic_push_args3
#define __cutils_generic_push_args3(object,...) _Generic((object),\
    cutils_cdar_DynamicArray_char*:cutils_cdar_DynamicArray_char_push_default3,\
    cutils_cdar_DynamicArray_void_ptr*:cutils_cdar_DynamicArray_void_ptr_push_default3,\
    cutils_cdar_DynamicArray_signed_char*:cutils_cdar_DynamicArray_signed_char_push_default3,\
    cutils_cdar_DynamicArray_unsigned_char*:cutils_cdar_DynamicArray_unsigned_char_push_default3,\
    cutils_cdar_DynamicArray_char_ptr*:cutils_cdar_DynamicArray_char_ptr_push_default3,\
    cutils_cdar_DynamicArray_short*:cutils_cdar_DynamicArray_short_push_default3,\
    cutils_cdar_DynamicArray_unsigned_short*:cutils_cdar_DynamicArray_unsigned_short_push_default3,\
    cutils_cdar_DynamicArray_int*:cutils_cdar_DynamicArray_int_push_default3,\
    cutils_cdar_DynamicArray_unsigned_int*:cutils_cdar_DynamicArray_unsigned_int_push_default3,\
    cutils_cdar_DynamicArray_long*:cutils_cdar_DynamicArray_long_push_default3,\
    cutils_cdar_DynamicArray_unsigned_long*:cutils_cdar_DynamicArray_unsigned_long_push_default3,\
    cutils_cdar_DynamicArray_long_long*:cutils_cdar_DynamicArray_long_long_push_default3,\
    cutils_cdar_DynamicArray_unsigned_long_long*:cutils_cdar_DynamicArray_unsigned_long_long_push_default3,\
    cutils_cdar_DynamicArray_float*:cutils_cdar_DynamicArray_float_push_default3,\
    cutils_cdar_DynamicArray_double*:cutils_cdar_DynamicArray_double_push_default3,\
    cutils_cdar_DynamicArray_long_double*:cutils_cdar_DynamicArray_long_double_push_default3,\
    cutils_cdar_DynamicArray_bool*:cutils_cdar_DynamicArray_bool_push_default3,\
    cutils_cdar_DynamicArray_size_t*:cutils_cdar_DynamicArray_size_t_push_default3,\
    cutils_cdar_DynamicArray_ptrdiff_t*:cutils_cdar_DynamicArray_ptrdiff_t_push_default3,\
    cutils_csll_SinglyLinkedList_char*:cutils_csll_SinglyLinkedList_char_push_default3,\
    cutils_csll_SinglyLinkedList_signed_char*:cutils_csll_SinglyLinkedList_signed_char_push_default3,\
    cutils_csll_SinglyLinkedList_unsigned_char*:cutils_csll_SinglyLinkedList_unsigned_char_push_default3,\
    cutils_csll_SinglyLinkedList_char_ptr*:cutils_csll_SinglyLinkedList_char_ptr_push_default3,\
    cutils_csll_SinglyLinkedList_short*:cutils_csll_SinglyLinkedList_short_push_default3,\
    cutils_csll_SinglyLinkedList_unsigned_short*:cutils_csll_SinglyLinkedList_unsigned_short_push_default3,\
    cutils_csll_SinglyLinkedList_int*:cutils_csll_SinglyLinkedList_int_push_default3,\
    cutils_csll_SinglyLinkedList_unsigned_int*:cutils_csll_SinglyLinkedList_unsigned_int_push_default3,\
    cutils_csll_SinglyLinkedList_long*:cutils_csll_SinglyLinkedList_long_push_default3,\
    cutils_csll_SinglyLinkedList_unsigned_long*:cutils_csll_SinglyLinkedList_unsigned_long_push_default3,\
    cutils_csll_SinglyLinkedList_long_long*:cutils_csll_SinglyLinkedList_long_long_push_default3,\
    cutils_csll_SinglyLinkedList_unsigned_long_long*:cutils_csll_SinglyLinkedList_unsigned_long_long_push_default3,\
    cutils_csll_SinglyLinkedList_float*:cutils_csll_SinglyLinkedList_float_push_default3,\
    cutils_csll_SinglyLinkedList_double*:cutils_csll_SinglyLinkedList_double_push_default3,\
    cutils_csll_SinglyLinkedList_long_double*:cutils_csll_SinglyLinkedList_long_double_push_default3,\
    cutils_csll_SinglyLinkedList_bool*:cutils_csll_SinglyLinkedList_bool_push_default3,\
    cutils_csll_SinglyLinkedList_size_t*:cutils_csll_SinglyLinkedList_size_t_push_default3,\
    cutils_csll_SinglyLinkedList_ptrdiff_t*:cutils_csll_SinglyLinkedList_ptrdiff_t_push_default3)\
    (object,##__VA_ARGS__)
/*----------------------------------------------------------------------------*/
#undef  __cutils_generic_pull_args3
#define __cutils_generic_pull_args3(object,...) _Generic((object),\
    cutils_cdar_DynamicArray_char*:cutils_cdar_DynamicArray_char_pull,\
    cutils_cdar_DynamicArray_void_ptr*:cutils_cdar_DynamicArray_void_ptr_pull,\
    cutils_cdar_DynamicArray_signed_char*:cutils_cdar_DynamicArray_signed_char_pull,\
    cutils_cdar_DynamicArray_unsigned_char*:cutils_cdar_DynamicArray_unsigned_char_pull,\
    cutils_cdar_DynamicArray_char_ptr*:cutils_cdar_DynamicArray_char_ptr_pull,\
    cutils_cdar_DynamicArray_short*:cutils_cdar_DynamicArray_short_pull,\
    cutils_cdar_DynamicArray_unsigned_short*:cutils_cdar_DynamicArray_unsigned_short_pull,\
    cutils_cdar_DynamicArray_int*:cutils_cdar_DynamicArray_int_pull,\
    cutils_cdar_DynamicArray_unsigned_int*:cutils_cdar_DynamicArray_unsigned_int_pull,\
    cutils_cdar_DynamicArray_long*:cutils_cdar_DynamicArray_long_pull,\
    cutils_cdar_DynamicArray_unsigned_long*:cutils_cdar_DynamicArray_unsigned_long_pull,\
    cutils_cdar_DynamicArray_long_long*:cutils_cdar_DynamicArray_long_long_pull,\
    cutils_cdar_DynamicArray_unsigned_long_long*:cutils_cdar_DynamicArray_unsigned_long_long_pull,\
    cutils_cdar_DynamicArray_float*:cutils_cdar_DynamicArray_float_pull,\
    cutils_cdar_DynamicArray_double*:cutils_cdar_DynamicArray_double_pull,\
    cutils_cdar_DynamicArray_long_double*:cutils_cdar_DynamicArray_long_double_pull,\
    cutils_cdar_DynamicArray_bool*:cutils_cdar_DynamicArray_bool_pull,\
    cutils_cdar_DynamicArray_size_t*:cutils_cdar_DynamicArray_size_t_pull,\
    cutils_cdar_DynamicArray_ptrdiff_t*:cutils_cdar_DynamicArray_ptrdiff_t_pull,\
    cutils_csll_SinglyLinkedList_char*:cutils_csll_SinglyLinkedList_char_pull,\
    cutils_csll_SinglyLinkedList_void_ptr*:cutils_csll_SinglyLinkedList_void_ptr_pull,\
    cutils_csll_SinglyLinkedList_signed_char*:cutils_csll_SinglyLinkedList_signed_char_pull,\
    cutils_csll_SinglyLinkedList_unsigned_char*:cutils_csll_SinglyLinkedList_unsigned_char_pull,\
    cutils_csll_SinglyLinkedList_char_ptr*:cutils_csll_SinglyLinkedList_char_ptr_pull,\
    cutils_csll_SinglyLinkedList_short*:cutils_csll_SinglyLinkedList_short_pull,\
    cutils_csll_SinglyLinkedList_unsigned_short*:cutils_csll_SinglyLinkedList_unsigned_short_pull,\
    cutils_csll_SinglyLinkedList_int*:cutils_csll_SinglyLinkedList_int_pull,\
    cutils_csll_SinglyLinkedList_unsigned_int*:cutils_csll_SinglyLinkedList_unsigned_int_pull,\
    cutils_csll_SinglyLinkedList_long*:cutils_csll_SinglyLinkedList_long_pull,\
    cutils_csll_SinglyLinkedList_unsigned_long*:cutils_csll_SinglyLinkedList_unsigned_long_pull,\
    cutils_csll_SinglyLinkedList_long_long*:cutils_csll_SinglyLinkedList_long_long_pull,\
    cutils_csll_SinglyLinkedList_unsigned_long_long*:cutils_csll_SinglyLinkedList_unsigned_long_long_pull,\
    cutils_csll_SinglyLinkedList_float*:cutils_csll_SinglyLinkedList_float_pull,\
    cutils_csll_SinglyLinkedList_double*:cutils_csll_SinglyLinkedList_double_pull,\
    cutils_csll_SinglyLinkedList_long_double*:cutils_csll_SinglyLinkedList_long_double_pull,\
    cutils_csll_SinglyLinkedList_bool*:cutils_csll_SinglyLinkedList_bool_pull,\
    cutils_csll_SinglyLinkedList_size_t*:cutils_csll_SinglyLinkedList_size_t_pull,\
    cutils_csll_SinglyLinkedList_ptrdiff_t*:cutils_csll_SinglyLinkedList_ptrdiff_t_pull)\
    (object,##__VA_ARGS__)
/*----------------------------------------------------------------------------*/
#undef  __cutils_generic_pull_args2
#define __cutils_generic_pull_args2(object,...) _Generic((object),\
    cutils_cdar_DynamicArray_char*:cutils_cdar_DynamicArray_char_pull_default2,\
    cutils_cdar_DynamicArray_void_ptr*:cutils_cdar_DynamicArray_void_ptr_pull_default2,\
    cutils_cdar_DynamicArray_signed_char*:cutils_cdar_DynamicArray_signed_char_pull_default2,\
    cutils_cdar_DynamicArray_unsigned_char*:cutils_cdar_DynamicArray_unsigned_char_pull_default2,\
    cutils_cdar_DynamicArray_char_ptr*:cutils_cdar_DynamicArray_char_ptr_pull_default2,\
    cutils_cdar_DynamicArray_short*:cutils_cdar_DynamicArray_short_pull_default2,\
    cutils_cdar_DynamicArray_unsigned_short*:cutils_cdar_DynamicArray_unsigned_short_pull_default2,\
    cutils_cdar_DynamicArray_int*:cutils_cdar_DynamicArray_int_pull_default2,\
    cutils_cdar_DynamicArray_unsigned_int*:cutils_cdar_DynamicArray_unsigned_int_pull_default2,\
    cutils_cdar_DynamicArray_long*:cutils_cdar_DynamicArray_long_pull_default2,\
    cutils_cdar_DynamicArray_unsigned_long*:cutils_cdar_DynamicArray_unsigned_long_pull_default2,\
    cutils_cdar_DynamicArray_long_long*:cutils_cdar_DynamicArray_long_long_pull_default2,\
    cutils_cdar_DynamicArray_unsigned_long_long*:cutils_cdar_DynamicArray_unsigned_long_long_pull_default2,\
    cutils_cdar_DynamicArray_float*:cutils_cdar_DynamicArray_float_pull_default2,\
    cutils_cdar_DynamicArray_double*:cutils_cdar_DynamicArray_double_pull_default2,\
    cutils_cdar_DynamicArray_long_double*:cutils_cdar_DynamicArray_long_double_pull_default2,\
    cutils_cdar_DynamicArray_bool*:cutils_cdar_DynamicArray_bool_pull_default2,\
    cutils_cdar_DynamicArray_size_t*:cutils_cdar_DynamicArray_size_t_pull_default2,\
    cutils_cdar_DynamicArray_ptrdiff_t*:cutils_cdar_DynamicArray_ptrdiff_t_pull_default2,\
    cutils_csll_SinglyLinkedList_char*:cutils_csll_SinglyLinkedList_char_pull_default2,\
    cutils_csll_SinglyLinkedList_void_ptr*:cutils_csll_SinglyLinkedList_void_ptr_pull_default2,\
    cutils_csll_SinglyLinkedList_signed_char*:cutils_csll_SinglyLinkedList_signed_char_pull_default2,\
    cutils_csll_SinglyLinkedList_unsigned_char*:cutils_csll_SinglyLinkedList_unsigned_char_pull_default2,\
    cutils_csll_SinglyLinkedList_char_ptr*:cutils_csll_SinglyLinkedList_char_ptr_pull_default2,\
    cutils_csll_SinglyLinkedList_short*:cutils_csll_SinglyLinkedList_short_pull_default2,\
    cutils_csll_SinglyLinkedList_unsigned_short*:cutils_csll_SinglyLinkedList_unsigned_short_pull_default2,\
    cutils_csll_SinglyLinkedList_int*:cutils_csll_SinglyLinkedList_int_pull_default2,\
    cutils_csll_SinglyLinkedList_unsigned_int*:cutils_csll_SinglyLinkedList_unsigned_int_pull_default2,\
    cutils_csll_SinglyLinkedList_long*:cutils_csll_SinglyLinkedList_long_pull_default2,\
    cutils_csll_SinglyLinkedList_unsigned_long*:cutils_csll_SinglyLinkedList_unsigned_long_pull_default2,\
    cutils_csll_SinglyLinkedList_long_long*:cutils_csll_SinglyLinkedList_long_long_pull_default2,\
    cutils_csll_SinglyLinkedList_unsigned_long_long*:cutils_csll_SinglyLinkedList_unsigned_long_long_pull_default2,\
    cutils_csll_SinglyLinkedList_float*:cutils_csll_SinglyLinkedList_float_pull_default2,\
    cutils_csll_SinglyLinkedList_double*:cutils_csll_SinglyLinkedList_double_pull_default2,\
    cutils_csll_SinglyLinkedList_long_double*:cutils_csll_SinglyLinkedList_long_double_pull_default2,\
    cutils_csll_SinglyLinkedList_bool*:cutils_csll_SinglyLinkedList_bool_pull_default2,\
    cutils_csll_SinglyLinkedList_size_t*:cutils_csll_SinglyLinkedList_size_t_pull_default2,\
    cutils_csll_SinglyLinkedList_ptrdiff_t*:cutils_csll_SinglyLinkedList_ptrdiff_t_pull_default2)\
    (object,##__VA_ARGS__)
/*----------------------------------------------------------------------------*/
#undef  __cutils_generic_pull_args1
#define __cutils_generic_pull_args1(object,...) _Generic((object),\
    cutils_csll_SinglyLinkedList_char_iterator*:cutils_csll_SinglyLinkedList_char_iterator_pull,\
    cutils_csll_SinglyLinkedList_void_ptr_iterator:cutils_csll_SinglyLinkedList_void_ptr_iterator_pull,\
    cutils_csll_SinglyLinkedList_signed_char_iterator*:cutils_csll_SinglyLinkedList_signed_char_iterator_pull,\
    cutils_csll_SinglyLinkedList_unsigned_char_iterator*:cutils_csll_SinglyLinkedList_unsigned_char_iterator_pull,\
    cutils_csll_SinglyLinkedList_char_ptr_iterator*:cutils_csll_SinglyLinkedList_char_ptr_iterator_pull,\
    cutils_csll_SinglyLinkedList_short_iterator*:cutils_csll_SinglyLinkedList_short_iterator_pull,\
    cutils_csll_SinglyLinkedList_unsigned_short_iterator*:cutils_csll_SinglyLinkedList_unsigned_short_iterator_pull,\
    cutils_csll_SinglyLinkedList_int_iterator*:cutils_csll_SinglyLinkedList_int_iterator_pull,\
    cutils_csll_SinglyLinkedList_unsigned_int_iterator*:cutils_csll_SinglyLinkedList_unsigned_int_iterator_pull,\
    cutils_csll_SinglyLinkedList_long_iterator*:cutils_csll_SinglyLinkedList_long_iterator_pull,\
    cutils_csll_SinglyLinkedList_unsigned_long_iterator*:cutils_csll_SinglyLinkedList_unsigned_long_iterator_pull,\
    cutils_csll_SinglyLinkedList_long_long_iterator*:cutils_csll_SinglyLinkedList_long_long_iterator_pull,\
    cutils_csll_SinglyLinkedList_unsigned_long_long_iterator*:cutils_csll_SinglyLinkedList_unsigned_long_long_iterator_pull,\
    cutils_csll_SinglyLinkedList_float_iterator*:cutils_csll_SinglyLinkedList_float_iterator_pull,\
    cutils_csll_SinglyLinkedList_double_iterator*:cutils_csll_SinglyLinkedList_double_iterator_pull,\
    cutils_csll_SinglyLinkedList_long_double_iterator*:cutils_csll_SinglyLinkedList_long_double_iterator_pull,\
    cutils_csll_SinglyLinkedList_bool_iterator*:cutils_csll_SinglyLinkedList_bool_iterator_pull,\
    cutils_csll_SinglyLinkedList_size_t_iterator*:cutils_csll_SinglyLinkedList_size_t_iterator_pull,\
    cutils_csll_SinglyLinkedList_ptrdiff_t_iterator*:cutils_csll_SinglyLinkedList_ptrdiff_t_iterator_pull)\
    (object,##__VA_ARGS__)
/*----------------------------------------------------------------------------*/
#undef  __cutils_generic_set_args5
#define __cutils_generic_set_args5(object,...) _Generic((object),\
    cutils_csll_SinglyLinkedList_void_ptr*:cutils_csll_SinglyLinkedList_void_ptr_set)\
    (object,##__VA_ARGS__)
/*----------------------------------------------------------------------------*/
#undef  __cutils_generic_set_args4
#define __cutils_generic_set_args4(object,...) _Generic((object),\
    cutils_cdar_DynamicArray_char*:cutils_cdar_DynamicArray_char_set,\
    cutils_cdar_DynamicArray_void_ptr*:cutils_cdar_DynamicArray_void_ptr_set,\
    cutils_cdar_DynamicArray_signed_char*:cutils_cdar_DynamicArray_signed_char_set,\
    cutils_cdar_DynamicArray_unsigned_char*:cutils_cdar_DynamicArray_unsigned_char_set,\
    cutils_cdar_DynamicArray_char_ptr*:cutils_cdar_DynamicArray_char_ptr_set,\
    cutils_cdar_DynamicArray_short*:cutils_cdar_DynamicArray_short_set,\
    cutils_cdar_DynamicArray_unsigned_short*:cutils_cdar_DynamicArray_unsigned_short_set,\
    cutils_cdar_DynamicArray_int*:cutils_cdar_DynamicArray_int_set,\
    cutils_cdar_DynamicArray_unsigned_int*:cutils_cdar_DynamicArray_unsigned_int_set,\
    cutils_cdar_DynamicArray_long*:cutils_cdar_DynamicArray_long_set,\
    cutils_cdar_DynamicArray_unsigned_long*:cutils_cdar_DynamicArray_unsigned_long_set,\
    cutils_cdar_DynamicArray_long_long*:cutils_cdar_DynamicArray_long_long_set,\
    cutils_cdar_DynamicArray_unsigned_long_long*:cutils_cdar_DynamicArray_unsigned_long_long_set,\
    cutils_cdar_DynamicArray_float*:cutils_cdar_DynamicArray_float_set,\
    cutils_cdar_DynamicArray_double*:cutils_cdar_DynamicArray_double_set,\
    cutils_cdar_DynamicArray_long_double*:cutils_cdar_DynamicArray_long_double_set,\
    cutils_cdar_DynamicArray_bool*:cutils_cdar_DynamicArray_bool_set,\
    cutils_cdar_DynamicArray_size_t*:cutils_cdar_DynamicArray_size_t_set,\
    cutils_cdar_DynamicArray_ptrdiff_t*:cutils_cdar_DynamicArray_ptrdiff_t_set,\
    cutils_csll_SinglyLinkedList_char*:cutils_csll_SinglyLinkedList_char_set,\
    cutils_csll_SinglyLinkedList_void_ptr*:cutils_csll_SinglyLinkedList_void_ptr_set_default4,\
    cutils_csll_SinglyLinkedList_signed_char*:cutils_csll_SinglyLinkedList_signed_char_set,\
    cutils_csll_SinglyLinkedList_unsigned_char*:cutils_csll_SinglyLinkedList_unsigned_char_set,\
    cutils_csll_SinglyLinkedList_char_ptr*:cutils_csll_SinglyLinkedList_char_ptr_set,\
    cutils_csll_SinglyLinkedList_short*:cutils_csll_SinglyLinkedList_short_set,\
    cutils_csll_SinglyLinkedList_unsigned_short*:cutils_csll_SinglyLinkedList_unsigned_short_set,\
    cutils_csll_SinglyLinkedList_int*:cutils_csll_SinglyLinkedList_int_set,\
    cutils_csll_SinglyLinkedList_unsigned_int*:cutils_csll_SinglyLinkedList_unsigned_int_set,\
    cutils_csll_SinglyLinkedList_long*:cutils_csll_SinglyLinkedList_long_set,\
    cutils_csll_SinglyLinkedList_unsigned_long*:cutils_csll_SinglyLinkedList_unsigned_long_set,\
    cutils_csll_SinglyLinkedList_long_long*:cutils_csll_SinglyLinkedList_long_long_set,\
    cutils_csll_SinglyLinkedList_unsigned_long_long*:cutils_csll_SinglyLinkedList_unsigned_long_long_set,\
    cutils_csll_SinglyLinkedList_float*:cutils_csll_SinglyLinkedList_float_set,\
    cutils_csll_SinglyLinkedList_double*:cutils_csll_SinglyLinkedList_double_set,\
    cutils_csll_SinglyLinkedList_long_double*:cutils_csll_SinglyLinkedList_long_double_set,\
    cutils_csll_SinglyLinkedList_bool*:cutils_csll_SinglyLinkedList_bool_set,\
    cutils_csll_SinglyLinkedList_size_t*:cutils_csll_SinglyLinkedList_size_t_set,\
    cutils_csll_SinglyLinkedList_ptrdiff_t*:cutils_csll_SinglyLinkedList_ptrdiff_t_set)\
    (object,##__VA_ARGS__)
/*----------------------------------------------------------------------------*/
#undef  __cutils_generic_set_args3
#define __cutils_generic_set_args3(object,...) _Generic((object),\
    cutils_cdar_DynamicArray_char*:cutils_cdar_DynamicArray_char_set_default3,\
    cutils_cdar_DynamicArray_void_ptr*:cutils_cdar_DynamicArray_void_ptr_set_default3,\
    cutils_cdar_DynamicArray_signed_char*:cutils_cdar_DynamicArray_signed_char_set_default3,\
    cutils_cdar_DynamicArray_unsigned_char*:cutils_cdar_DynamicArray_unsigned_char_set_default3,\
    cutils_cdar_DynamicArray_char_ptr*:cutils_cdar_DynamicArray_char_ptr_set_default3,\
    cutils_cdar_DynamicArray_short*:cutils_cdar_DynamicArray_short_set_default3,\
    cutils_cdar_DynamicArray_unsigned_short*:cutils_cdar_DynamicArray_unsigned_short_set_default3,\
    cutils_cdar_DynamicArray_int*:cutils_cdar_DynamicArray_int_set_default3,\
    cutils_cdar_DynamicArray_unsigned_int*:cutils_cdar_DynamicArray_unsigned_int_set_default3,\
    cutils_cdar_DynamicArray_long*:cutils_cdar_DynamicArray_long_set_default3,\
    cutils_cdar_DynamicArray_unsigned_long*:cutils_cdar_DynamicArray_unsigned_long_set_default3,\
    cutils_cdar_DynamicArray_long_long*:cutils_cdar_DynamicArray_long_long_set_default3,\
    cutils_cdar_DynamicArray_unsigned_long_long*:cutils_cdar_DynamicArray_unsigned_long_long_set_default3,\
    cutils_cdar_DynamicArray_float*:cutils_cdar_DynamicArray_float_set_default3,\
    cutils_cdar_DynamicArray_double*:cutils_cdar_DynamicArray_double_set_default3,\
    cutils_cdar_DynamicArray_long_double*:cutils_cdar_DynamicArray_long_double_set_default3,\
    cutils_cdar_DynamicArray_bool*:cutils_cdar_DynamicArray_bool_set_default3,\
    cutils_cdar_DynamicArray_size_t*:cutils_cdar_DynamicArray_size_t_set_default3,\
    cutils_cdar_DynamicArray_ptrdiff_t*:cutils_cdar_DynamicArray_ptrdiff_t_set_default3,\
    cutils_csll_SinglyLinkedList_char*:cutils_csll_SinglyLinkedList_char_set_default3,\
    cutils_csll_SinglyLinkedList_signed_char*:cutils_csll_SinglyLinkedList_signed_char_set_default3,\
    cutils_csll_SinglyLinkedList_unsigned_char*:cutils_csll_SinglyLinkedList_unsigned_char_set_default3,\
    cutils_csll_SinglyLinkedList_char_ptr*:cutils_csll_SinglyLinkedList_char_ptr_set_default3,\
    cutils_csll_SinglyLinkedList_short*:cutils_csll_SinglyLinkedList_short_set_default3,\
    cutils_csll_SinglyLinkedList_unsigned_short*:cutils_csll_SinglyLinkedList_unsigned_short_set_default3,\
    cutils_csll_SinglyLinkedList_int*:cutils_csll_SinglyLinkedList_int_set_default3,\
    cutils_csll_SinglyLinkedList_unsigned_int*:cutils_csll_SinglyLinkedList_unsigned_int_set_default3,\
    cutils_csll_SinglyLinkedList_long*:cutils_csll_SinglyLinkedList_long_set_default3,\
    cutils_csll_SinglyLinkedList_unsigned_long*:cutils_csll_SinglyLinkedList_unsigned_long_set_default3,\
    cutils_csll_SinglyLinkedList_long_long*:cutils_csll_SinglyLinkedList_long_long_set_default3,\
    cutils_csll_SinglyLinkedList_unsigned_long_long*:cutils_csll_SinglyLinkedList_unsigned_long_long_set_default3,\
    cutils_csll_SinglyLinkedList_float*:cutils_csll_SinglyLinkedList_float_set_default3,\
    cutils_csll_SinglyLinkedList_double*:cutils_csll_SinglyLinkedList_double_set_default3,\
    cutils_csll_SinglyLinkedList_long_double*:cutils_csll_SinglyLinkedList_long_double_set_default3,\
    cutils_csll_SinglyLinkedList_bool*:cutils_csll_SinglyLinkedList_bool_set_default3,\
    cutils_csll_SinglyLinkedList_size_t*:cutils_csll_SinglyLinkedList_size_t_set_default3,\
    cutils_csll_SinglyLinkedList_ptrdiff_t*:cutils_csll_SinglyLinkedList_ptrdiff_t_set_default3)\
    (object,##__VA_ARGS__)
/*----------------------------------------------------------------------------*/
#undef  __cutils_generic_pop_args5
#define __cutils_generic_pop_args5(object,...) _Generic((object),\
    cutils_csll_SinglyLinkedList_void_ptr*:cutils_csll_SinglyLinkedList_void_ptr_pop)\
    (object,##__VA_ARGS__)
/*----------------------------------------------------------------------------*/
#undef  __cutils_generic_pop_args4
#define __cutils_generic_pop_args4(object,...) _Generic((object),\
    cutils_cdar_DynamicArray_char*:cutils_cdar_DynamicArray_char_pop,\
    cutils_cdar_DynamicArray_void_ptr*:cutils_cdar_DynamicArray_void_ptr_pop,\
    cutils_cdar_DynamicArray_signed_char*:cutils_cdar_DynamicArray_signed_char_pop,\
    cutils_cdar_DynamicArray_unsigned_char*:cutils_cdar_DynamicArray_unsigned_char_pop,\
    cutils_cdar_DynamicArray_char_ptr*:cutils_cdar_DynamicArray_char_ptr_pop,\
    cutils_cdar_DynamicArray_short*:cutils_cdar_DynamicArray_short_pop,\
    cutils_cdar_DynamicArray_unsigned_short*:cutils_cdar_DynamicArray_unsigned_short_pop,\
    cutils_cdar_DynamicArray_int*:cutils_cdar_DynamicArray_int_pop,\
    cutils_cdar_DynamicArray_unsigned_int*:cutils_cdar_DynamicArray_unsigned_int_pop,\
    cutils_cdar_DynamicArray_long*:cutils_cdar_DynamicArray_long_pop,\
    cutils_cdar_DynamicArray_unsigned_long*:cutils_cdar_DynamicArray_unsigned_long_pop,\
    cutils_cdar_DynamicArray_long_long*:cutils_cdar_DynamicArray_long_long_pop,\
    cutils_cdar_DynamicArray_unsigned_long_long*:cutils_cdar_DynamicArray_unsigned_long_long_pop,\
    cutils_cdar_DynamicArray_float*:cutils_cdar_DynamicArray_float_pop,\
    cutils_cdar_DynamicArray_double*:cutils_cdar_DynamicArray_double_pop,\
    cutils_cdar_DynamicArray_long_double*:cutils_cdar_DynamicArray_long_double_pop,\
    cutils_cdar_DynamicArray_bool*:cutils_cdar_DynamicArray_bool_pop,\
    cutils_cdar_DynamicArray_size_t*:cutils_cdar_DynamicArray_size_t_pop,\
    cutils_cdar_DynamicArray_ptrdiff_t*:cutils_cdar_DynamicArray_ptrdiff_t_pop,\
    cutils_csll_SinglyLinkedList_char*:cutils_csll_SinglyLinkedList_char_pop,\
    cutils_csll_SinglyLinkedList_void_ptr*:cutils_csll_SinglyLinkedList_void_ptr_pop_default4,\
    cutils_csll_SinglyLinkedList_signed_char*:cutils_csll_SinglyLinkedList_signed_char_pop,\
    cutils_csll_SinglyLinkedList_unsigned_char*:cutils_csll_SinglyLinkedList_unsigned_char_pop,\
    cutils_csll_SinglyLinkedList_char_ptr*:cutils_csll_SinglyLinkedList_char_ptr_pop,\
    cutils_csll_SinglyLinkedList_short*:cutils_csll_SinglyLinkedList_short_pop,\
    cutils_csll_SinglyLinkedList_unsigned_short*:cutils_csll_SinglyLinkedList_unsigned_short_pop,\
    cutils_csll_SinglyLinkedList_int*:cutils_csll_SinglyLinkedList_int_pop,\
    cutils_csll_SinglyLinkedList_unsigned_int*:cutils_csll_SinglyLinkedList_unsigned_int_pop,\
    cutils_csll_SinglyLinkedList_long*:cutils_csll_SinglyLinkedList_long_pop,\
    cutils_csll_SinglyLinkedList_unsigned_long*:cutils_csll_SinglyLinkedList_unsigned_long_pop,\
    cutils_csll_SinglyLinkedList_long_long*:cutils_csll_SinglyLinkedList_long_long_pop,\
    cutils_csll_SinglyLinkedList_unsigned_long_long*:cutils_csll_SinglyLinkedList_unsigned_long_long_pop,\
    cutils_csll_SinglyLinkedList_float*:cutils_csll_SinglyLinkedList_float_pop,\
    cutils_csll_SinglyLinkedList_double*:cutils_csll_SinglyLinkedList_double_pop,\
    cutils_csll_SinglyLinkedList_long_double*:cutils_csll_SinglyLinkedList_long_double_pop,\
    cutils_csll_SinglyLinkedList_bool*:cutils_csll_SinglyLinkedList_bool_pop,\
    cutils_csll_SinglyLinkedList_size_t*:cutils_csll_SinglyLinkedList_size_t_pop,\
    cutils_csll_SinglyLinkedList_ptrdiff_t*:cutils_csll_SinglyLinkedList_ptrdiff_t_pop)\
    (object,##__VA_ARGS__)
/*----------------------------------------------------------------------------*/
#undef  __cutils_generic_pop_args3
#define __cutils_generic_pop_args3(object,...) _Generic((object),\
    cutils_cdar_DynamicArray_char*:cutils_cdar_DynamicArray_char_pop_default3,\
    cutils_cdar_DynamicArray_void_ptr*:cutils_cdar_DynamicArray_void_ptr_pop_default3,\
    cutils_cdar_DynamicArray_signed_char*:cutils_cdar_DynamicArray_signed_char_pop_default3,\
    cutils_cdar_DynamicArray_unsigned_char*:cutils_cdar_DynamicArray_unsigned_char_pop_default3,\
    cutils_cdar_DynamicArray_char_ptr*:cutils_cdar_DynamicArray_char_ptr_pop_default3,\
    cutils_cdar_DynamicArray_short*:cutils_cdar_DynamicArray_short_pop_default3,\
    cutils_cdar_DynamicArray_unsigned_short*:cutils_cdar_DynamicArray_unsigned_short_pop_default3,\
    cutils_cdar_DynamicArray_int*:cutils_cdar_DynamicArray_int_pop_default3,\
    cutils_cdar_DynamicArray_unsigned_int*:cutils_cdar_DynamicArray_unsigned_int_pop_default3,\
    cutils_cdar_DynamicArray_long*:cutils_cdar_DynamicArray_long_pop_default3,\
    cutils_cdar_DynamicArray_unsigned_long*:cutils_cdar_DynamicArray_unsigned_long_pop_default3,\
    cutils_cdar_DynamicArray_long_long*:cutils_cdar_DynamicArray_long_long_pop_default3,\
    cutils_cdar_DynamicArray_unsigned_long_long*:cutils_cdar_DynamicArray_unsigned_long_long_pop_default3,\
    cutils_cdar_DynamicArray_float*:cutils_cdar_DynamicArray_float_pop_default3,\
    cutils_cdar_DynamicArray_double*:cutils_cdar_DynamicArray_double_pop_default3,\
    cutils_cdar_DynamicArray_long_double*:cutils_cdar_DynamicArray_long_double_pop_default3,\
    cutils_cdar_DynamicArray_bool*:cutils_cdar_DynamicArray_bool_pop_default3,\
    cutils_cdar_DynamicArray_size_t*:cutils_cdar_DynamicArray_size_t_pop_default3,\
    cutils_cdar_DynamicArray_ptrdiff_t*:cutils_cdar_DynamicArray_ptrdiff_t_pop_default3,\
    cutils_csll_SinglyLinkedList_char*:cutils_csll_SinglyLinkedList_char_pop_default3,\
    cutils_csll_SinglyLinkedList_signed_char*:cutils_csll_SinglyLinkedList_signed_char_pop_default3,\
    cutils_csll_SinglyLinkedList_unsigned_char*:cutils_csll_SinglyLinkedList_unsigned_char_pop_default3,\
    cutils_csll_SinglyLinkedList_char_ptr*:cutils_csll_SinglyLinkedList_char_ptr_pop_default3,\
    cutils_csll_SinglyLinkedList_short*:cutils_csll_SinglyLinkedList_short_pop_default3,\
    cutils_csll_SinglyLinkedList_unsigned_short*:cutils_csll_SinglyLinkedList_unsigned_short_pop_default3,\
    cutils_csll_SinglyLinkedList_int*:cutils_csll_SinglyLinkedList_int_pop_default3,\
    cutils_csll_SinglyLinkedList_unsigned_int*:cutils_csll_SinglyLinkedList_unsigned_int_pop_default3,\
    cutils_csll_SinglyLinkedList_long*:cutils_csll_SinglyLinkedList_long_pop_default3,\
    cutils_csll_SinglyLinkedList_unsigned_long*:cutils_csll_SinglyLinkedList_unsigned_long_pop_default3,\
    cutils_csll_SinglyLinkedList_long_long*:cutils_csll_SinglyLinkedList_long_long_pop_default3,\
    cutils_csll_SinglyLinkedList_unsigned_long_long*:cutils_csll_SinglyLinkedList_unsigned_long_long_pop_default3,\
    cutils_csll_SinglyLinkedList_float*:cutils_csll_SinglyLinkedList_float_pop_default3,\
    cutils_csll_SinglyLinkedList_double*:cutils_csll_SinglyLinkedList_double_pop_default3,\
    cutils_csll_SinglyLinkedList_long_double*:cutils_csll_SinglyLinkedList_long_double_pop_default3,\
    cutils_csll_SinglyLinkedList_bool*:cutils_csll_SinglyLinkedList_bool_pop_default3,\
    cutils_csll_SinglyLinkedList_size_t*:cutils_csll_SinglyLinkedList_size_t_pop_default3,\
    cutils_csll_SinglyLinkedList_ptrdiff_t*:cutils_csll_SinglyLinkedList_ptrdiff_t_pop_default3)\
    (object,##__VA_ARGS__)
/*----------------------------------------------------------------------------*/
#undef  __cutils_generic_get
#define __cutils_generic_get(object,...) _Generic((object),\
    cutils_cdar_DynamicArray_char*:cutils_cdar_DynamicArray_char_get,\
    cutils_cdar_DynamicArray_void_ptr*:cutils_cdar_DynamicArray_void_ptr_get,\
    cutils_cdar_DynamicArray_signed_char*:cutils_cdar_DynamicArray_signed_char_get,\
    cutils_cdar_DynamicArray_unsigned_char*:cutils_cdar_DynamicArray_unsigned_char_get,\
    cutils_cdar_DynamicArray_char_ptr*:cutils_cdar_DynamicArray_char_ptr_get,\
    cutils_cdar_DynamicArray_short*:cutils_cdar_DynamicArray_short_get,\
    cutils_cdar_DynamicArray_unsigned_short*:cutils_cdar_DynamicArray_unsigned_short_get,\
    cutils_cdar_DynamicArray_int*:cutils_cdar_DynamicArray_int_get,\
    cutils_cdar_DynamicArray_unsigned_int*:cutils_cdar_DynamicArray_unsigned_int_get,\
    cutils_cdar_DynamicArray_long*:cutils_cdar_DynamicArray_long_get,\
    cutils_cdar_DynamicArray_unsigned_long*:cutils_cdar_DynamicArray_unsigned_long_get,\
    cutils_cdar_DynamicArray_long_long*:cutils_cdar_DynamicArray_long_long_get,\
    cutils_cdar_DynamicArray_unsigned_long_long*:cutils_cdar_DynamicArray_unsigned_long_long_get,\
    cutils_cdar_DynamicArray_float*:cutils_cdar_DynamicArray_float_get,\
    cutils_cdar_DynamicArray_double*:cutils_cdar_DynamicArray_double_get,\
    cutils_cdar_DynamicArray_long_double*:cutils_cdar_DynamicArray_long_double_get,\
    cutils_cdar_DynamicArray_bool*:cutils_cdar_DynamicArray_bool_get,\
    cutils_cdar_DynamicArray_size_t*:cutils_cdar_DynamicArray_size_t_get,\
    cutils_cdar_DynamicArray_ptrdiff_t*:cutils_cdar_DynamicArray_ptrdiff_t_get,\
    cutils_csll_SinglyLinkedList_char*:cutils_csll_SinglyLinkedList_char_get,\
    cutils_csll_SinglyLinkedList_void_ptr*:cutils_csll_SinglyLinkedList_void_ptr_get,\
    cutils_csll_SinglyLinkedList_signed_char*:cutils_csll_SinglyLinkedList_signed_char_get,\
    cutils_csll_SinglyLinkedList_unsigned_char*:cutils_csll_SinglyLinkedList_unsigned_char_get,\
    cutils_csll_SinglyLinkedList_char_ptr*:cutils_csll_SinglyLinkedList_char_ptr_get,\
    cutils_csll_SinglyLinkedList_short*:cutils_csll_SinglyLinkedList_short_get,\
    cutils_csll_SinglyLinkedList_unsigned_short*:cutils_csll_SinglyLinkedList_unsigned_short_get,\
    cutils_csll_SinglyLinkedList_int*:cutils_csll_SinglyLinkedList_int_get,\
    cutils_csll_SinglyLinkedList_unsigned_int*:cutils_csll_SinglyLinkedList_unsigned_int_get,\
    cutils_csll_SinglyLinkedList_long*:cutils_csll_SinglyLinkedList_long_get,\
    cutils_csll_SinglyLinkedList_unsigned_long*:cutils_csll_SinglyLinkedList_unsigned_long_get,\
    cutils_csll_SinglyLinkedList_long_long*:cutils_csll_SinglyLinkedList_long_long_get,\
    cutils_csll_SinglyLinkedList_unsigned_long_long*:cutils_csll_SinglyLinkedList_unsigned_long_long_get,\
    cutils_csll_SinglyLinkedList_float*:cutils_csll_SinglyLinkedList_float_get,\
    cutils_csll_SinglyLinkedList_double*:cutils_csll_SinglyLinkedList_double_get,\
    cutils_csll_SinglyLinkedList_long_double*:cutils_csll_SinglyLinkedList_long_double_get,\
    cutils_csll_SinglyLinkedList_bool*:cutils_csll_SinglyLinkedList_bool_get,\
    cutils_csll_SinglyLinkedList_size_t*:cutils_csll_SinglyLinkedList_size_t_get,\
    cutils_csll_SinglyLinkedList_ptrdiff_t*:cutils_csll_SinglyLinkedList_ptrdiff_t_get)\
    (object,##__VA_ARGS__)
/*----------------------------------------------------------------------------*/
#undef  __cutils_generic_sub_args5
#define __cutils_generic_sub_args5(object,...) _Generic((object),\
    cutils_csll_SinglyLinkedList_void_ptr*:cutils_csll_SinglyLinkedList_void_ptr_sub)\
    (object,##__VA_ARGS__)
/*----------------------------------------------------------------------------*/
#undef  __cutils_generic_sub_args4
#define __cutils_generic_sub_args4(object,...) _Generic((object),\
    cutils_cdar_DynamicArray_char*:cutils_cdar_DynamicArray_char_sub,\
    cutils_cdar_DynamicArray_void_ptr*:cutils_cdar_DynamicArray_void_ptr_sub,\
    cutils_cdar_DynamicArray_signed_char*:cutils_cdar_DynamicArray_signed_char_sub,\
    cutils_cdar_DynamicArray_unsigned_char*:cutils_cdar_DynamicArray_unsigned_char_sub,\
    cutils_cdar_DynamicArray_char_ptr*:cutils_cdar_DynamicArray_char_ptr_sub,\
    cutils_cdar_DynamicArray_short*:cutils_cdar_DynamicArray_short_sub,\
    cutils_cdar_DynamicArray_unsigned_short*:cutils_cdar_DynamicArray_unsigned_short_sub,\
    cutils_cdar_DynamicArray_int*:cutils_cdar_DynamicArray_int_sub,\
    cutils_cdar_DynamicArray_unsigned_int*:cutils_cdar_DynamicArray_unsigned_int_sub,\
    cutils_cdar_DynamicArray_long*:cutils_cdar_DynamicArray_long_sub,\
    cutils_cdar_DynamicArray_unsigned_long*:cutils_cdar_DynamicArray_unsigned_long_sub,\
    cutils_cdar_DynamicArray_long_long*:cutils_cdar_DynamicArray_long_long_sub,\
    cutils_cdar_DynamicArray_unsigned_long_long*:cutils_cdar_DynamicArray_unsigned_long_long_sub,\
    cutils_cdar_DynamicArray_float*:cutils_cdar_DynamicArray_float_sub,\
    cutils_cdar_DynamicArray_double*:cutils_cdar_DynamicArray_double_sub,\
    cutils_cdar_DynamicArray_long_double*:cutils_cdar_DynamicArray_long_double_sub,\
    cutils_cdar_DynamicArray_bool*:cutils_cdar_DynamicArray_bool_sub,\
    cutils_cdar_DynamicArray_size_t*:cutils_cdar_DynamicArray_size_t_sub,\
    cutils_cdar_DynamicArray_ptrdiff_t*:cutils_cdar_DynamicArray_ptrdiff_t_sub,\
    cutils_csll_SinglyLinkedList_char*:cutils_csll_SinglyLinkedList_char_sub,\
    cutils_csll_SinglyLinkedList_void_ptr*:cutils_csll_SinglyLinkedList_void_ptr_sub_default4,\
    cutils_csll_SinglyLinkedList_signed_char*:cutils_csll_SinglyLinkedList_signed_char_sub,\
    cutils_csll_SinglyLinkedList_unsigned_char*:cutils_csll_SinglyLinkedList_unsigned_char_sub,\
    cutils_csll_SinglyLinkedList_char_ptr*:cutils_csll_SinglyLinkedList_char_ptr_sub,\
    cutils_csll_SinglyLinkedList_short*:cutils_csll_SinglyLinkedList_short_sub,\
    cutils_csll_SinglyLinkedList_unsigned_short*:cutils_csll_SinglyLinkedList_unsigned_short_sub,\
    cutils_csll_SinglyLinkedList_int*:cutils_csll_SinglyLinkedList_int_sub,\
    cutils_csll_SinglyLinkedList_unsigned_int*:cutils_csll_SinglyLinkedList_unsigned_int_sub,\
    cutils_csll_SinglyLinkedList_long*:cutils_csll_SinglyLinkedList_long_sub,\
    cutils_csll_SinglyLinkedList_unsigned_long*:cutils_csll_SinglyLinkedList_unsigned_long_sub,\
    cutils_csll_SinglyLinkedList_long_long*:cutils_csll_SinglyLinkedList_long_long_sub,\
    cutils_csll_SinglyLinkedList_unsigned_long_long*:cutils_csll_SinglyLinkedList_unsigned_long_long_sub,\
    cutils_csll_SinglyLinkedList_float*:cutils_csll_SinglyLinkedList_float_sub,\
    cutils_csll_SinglyLinkedList_double*:cutils_csll_SinglyLinkedList_double_sub,\
    cutils_csll_SinglyLinkedList_long_double*:cutils_csll_SinglyLinkedList_long_double_sub,\
    cutils_csll_SinglyLinkedList_bool*:cutils_csll_SinglyLinkedList_bool_sub,\
    cutils_csll_SinglyLinkedList_size_t*:cutils_csll_SinglyLinkedList_size_t_sub,\
    cutils_csll_SinglyLinkedList_ptrdiff_t*:cutils_csll_SinglyLinkedList_ptrdiff_t_sub)\
    (object,##__VA_ARGS__)
/*----------------------------------------------------------------------------*/
#undef  __cutils_generic_sub_args3
#define __cutils_generic_sub_args3(object,...) _Generic((object),\
    cutils_cdar_DynamicArray_char*:cutils_cdar_DynamicArray_char_sub_default3,\
    cutils_cdar_DynamicArray_void_ptr*:cutils_cdar_DynamicArray_void_ptr_sub_default3,\
    cutils_cdar_DynamicArray_signed_char*:cutils_cdar_DynamicArray_signed_char_sub_default3,\
    cutils_cdar_DynamicArray_unsigned_char*:cutils_cdar_DynamicArray_unsigned_char_sub_default3,\
    cutils_cdar_DynamicArray_char_ptr*:cutils_cdar_DynamicArray_char_ptr_sub_default3,\
    cutils_cdar_DynamicArray_short*:cutils_cdar_DynamicArray_short_sub_default3,\
    cutils_cdar_DynamicArray_unsigned_short*:cutils_cdar_DynamicArray_unsigned_short_sub_default3,\
    cutils_cdar_DynamicArray_int*:cutils_cdar_DynamicArray_int_sub_default3,\
    cutils_cdar_DynamicArray_unsigned_int*:cutils_cdar_DynamicArray_unsigned_int_sub_default3,\
    cutils_cdar_DynamicArray_long*:cutils_cdar_DynamicArray_long_sub_default3,\
    cutils_cdar_DynamicArray_unsigned_long*:cutils_cdar_DynamicArray_unsigned_long_sub_default3,\
    cutils_cdar_DynamicArray_long_long*:cutils_cdar_DynamicArray_long_long_sub_default3,\
    cutils_cdar_DynamicArray_unsigned_long_long*:cutils_cdar_DynamicArray_unsigned_long_long_sub_default3,\
    cutils_cdar_DynamicArray_float*:cutils_cdar_DynamicArray_float_sub_default3,\
    cutils_cdar_DynamicArray_double*:cutils_cdar_DynamicArray_double_sub_default3,\
    cutils_cdar_DynamicArray_long_double*:cutils_cdar_DynamicArray_long_double_sub_default3,\
    cutils_cdar_DynamicArray_bool*:cutils_cdar_DynamicArray_bool_sub_default3,\
    cutils_cdar_DynamicArray_size_t*:cutils_cdar_DynamicArray_size_t_sub_default3,\
    cutils_cdar_DynamicArray_ptrdiff_t*:cutils_cdar_DynamicArray_ptrdiff_t_sub_default3,\
    cutils_csll_SinglyLinkedList_char*:cutils_csll_SinglyLinkedList_char_sub_default3,\
    cutils_csll_SinglyLinkedList_signed_char*:cutils_csll_SinglyLinkedList_signed_char_sub_default3,\
    cutils_csll_SinglyLinkedList_unsigned_char*:cutils_csll_SinglyLinkedList_unsigned_char_sub_default3,\
    cutils_csll_SinglyLinkedList_char_ptr*:cutils_csll_SinglyLinkedList_char_ptr_sub_default3,\
    cutils_csll_SinglyLinkedList_short*:cutils_csll_SinglyLinkedList_short_sub_default3,\
    cutils_csll_SinglyLinkedList_unsigned_short*:cutils_csll_SinglyLinkedList_unsigned_short_sub_default3,\
    cutils_csll_SinglyLinkedList_int*:cutils_csll_SinglyLinkedList_int_sub_default3,\
    cutils_csll_SinglyLinkedList_unsigned_int*:cutils_csll_SinglyLinkedList_unsigned_int_sub_default3,\
    cutils_csll_SinglyLinkedList_long*:cutils_csll_SinglyLinkedList_long_sub_default3,\
    cutils_csll_SinglyLinkedList_unsigned_long*:cutils_csll_SinglyLinkedList_unsigned_long_sub_default3,\
    cutils_csll_SinglyLinkedList_long_long*:cutils_csll_SinglyLinkedList_long_long_sub_default3,\
    cutils_csll_SinglyLinkedList_unsigned_long_long*:cutils_csll_SinglyLinkedList_unsigned_long_long_sub_default3,\
    cutils_csll_SinglyLinkedList_float*:cutils_csll_SinglyLinkedList_float_sub_default3,\
    cutils_csll_SinglyLinkedList_double*:cutils_csll_SinglyLinkedList_double_sub_default3,\
    cutils_csll_SinglyLinkedList_long_double*:cutils_csll_SinglyLinkedList_long_double_sub_default3,\
    cutils_csll_SinglyLinkedList_bool*:cutils_csll_SinglyLinkedList_bool_sub_default3,\
    cutils_csll_SinglyLinkedList_size_t*:cutils_csll_SinglyLinkedList_size_t_sub_default3,\
    cutils_csll_SinglyLinkedList_ptrdiff_t*:cutils_csll_SinglyLinkedList_ptrdiff_t_sub_default3)\
    (object,##__VA_ARGS__)
/*----------------------------------------------------------------------------*/
#undef  __cutils_generic_map_args4
#define __cutils_generic_map_args4(object,...) _Generic((object),\
    cutils_cdar_DynamicArray_char*:cutils_cdar_DynamicArray_char_map,\
    cutils_cdar_DynamicArray_void_ptr*:cutils_cdar_DynamicArray_void_ptr_map,\
    cutils_cdar_DynamicArray_signed_char*:cutils_cdar_DynamicArray_signed_char_map,\
    cutils_cdar_DynamicArray_unsigned_char*:cutils_cdar_DynamicArray_unsigned_char_map,\
    cutils_cdar_DynamicArray_char_ptr*:cutils_cdar_DynamicArray_char_ptr_map,\
    cutils_cdar_DynamicArray_short*:cutils_cdar_DynamicArray_short_map,\
    cutils_cdar_DynamicArray_unsigned_short*:cutils_cdar_DynamicArray_unsigned_short_map,\
    cutils_cdar_DynamicArray_int*:cutils_cdar_DynamicArray_int_map,\
    cutils_cdar_DynamicArray_unsigned_int*:cutils_cdar_DynamicArray_unsigned_int_map,\
    cutils_cdar_DynamicArray_long*:cutils_cdar_DynamicArray_long_map,\
    cutils_cdar_DynamicArray_unsigned_long*:cutils_cdar_DynamicArray_unsigned_long_map,\
    cutils_cdar_DynamicArray_long_long*:cutils_cdar_DynamicArray_long_long_map,\
    cutils_cdar_DynamicArray_unsigned_long_long*:cutils_cdar_DynamicArray_unsigned_long_long_map,\
    cutils_cdar_DynamicArray_float*:cutils_cdar_DynamicArray_float_map,\
    cutils_cdar_DynamicArray_double*:cutils_cdar_DynamicArray_double_map,\
    cutils_cdar_DynamicArray_long_double*:cutils_cdar_DynamicArray_long_double_map,\
    cutils_cdar_DynamicArray_bool*:cutils_cdar_DynamicArray_bool_map,\
    cutils_cdar_DynamicArray_size_t*:cutils_cdar_DynamicArray_size_t_map,\
    cutils_cdar_DynamicArray_ptrdiff_t*:cutils_cdar_DynamicArray_ptrdiff_t_map,\
    cutils_csll_SinglyLinkedList_char*:cutils_csll_SinglyLinkedList_char_map,\
    cutils_csll_SinglyLinkedList_void_ptr*:cutils_csll_SinglyLinkedList_void_ptr_map,\
    cutils_csll_SinglyLinkedList_signed_char*:cutils_csll_SinglyLinkedList_signed_char_map,\
    cutils_csll_SinglyLinkedList_unsigned_char*:cutils_csll_SinglyLinkedList_unsigned_char_map,\
    cutils_csll_SinglyLinkedList_char_ptr*:cutils_csll_SinglyLinkedList_char_ptr_map,\
    cutils_csll_SinglyLinkedList_short*:cutils_csll_SinglyLinkedList_short_map,\
    cutils_csll_SinglyLinkedList_unsigned_short*:cutils_csll_SinglyLinkedList_unsigned_short_map,\
    cutils_csll_SinglyLinkedList_int*:cutils_csll_SinglyLinkedList_int_map,\
    cutils_csll_SinglyLinkedList_unsigned_int*:cutils_csll_SinglyLinkedList_unsigned_int_map,\
    cutils_csll_SinglyLinkedList_long*:cutils_csll_SinglyLinkedList_long_map,\
    cutils_csll_SinglyLinkedList_unsigned_long*:cutils_csll_SinglyLinkedList_unsigned_long_map,\
    cutils_csll_SinglyLinkedList_long_long*:cutils_csll_SinglyLinkedList_long_long_map,\
    cutils_csll_SinglyLinkedList_unsigned_long_long*:cutils_csll_SinglyLinkedList_unsigned_long_long_map,\
    cutils_csll_SinglyLinkedList_float*:cutils_csll_SinglyLinkedList_float_map,\
    cutils_csll_SinglyLinkedList_double*:cutils_csll_SinglyLinkedList_double_map,\
    cutils_csll_SinglyLinkedList_long_double*:cutils_csll_SinglyLinkedList_long_double_map,\
    cutils_csll_SinglyLinkedList_bool*:cutils_csll_SinglyLinkedList_bool_map,\
    cutils_csll_SinglyLinkedList_size_t*:cutils_csll_SinglyLinkedList_size_t_map,\
    cutils_csll_SinglyLinkedList_ptrdiff_t*:cutils_csll_SinglyLinkedList_ptrdiff_t_map)\
    (object,##__VA_ARGS__)
/*----------------------------------------------------------------------------*/
#undef  __cutils_generic_map_args3
#define __cutils_generic_map_args3(object,...) _Generic((object),\
    cutils_cdar_DynamicArray_char*:cutils_cdar_DynamicArray_char_map_default3,\
    cutils_cdar_DynamicArray_void_ptr*:cutils_cdar_DynamicArray_void_ptr_map_default3,\
    cutils_cdar_DynamicArray_signed_char*:cutils_cdar_DynamicArray_signed_char_map_default3,\
    cutils_cdar_DynamicArray_unsigned_char*:cutils_cdar_DynamicArray_unsigned_char_map_default3,\
    cutils_cdar_DynamicArray_char_ptr*:cutils_cdar_DynamicArray_char_ptr_map_default3,\
    cutils_cdar_DynamicArray_short*:cutils_cdar_DynamicArray_short_map_default3,\
    cutils_cdar_DynamicArray_unsigned_short*:cutils_cdar_DynamicArray_unsigned_short_map_default3,\
    cutils_cdar_DynamicArray_int*:cutils_cdar_DynamicArray_int_map_default3,\
    cutils_cdar_DynamicArray_unsigned_int*:cutils_cdar_DynamicArray_unsigned_int_map_default3,\
    cutils_cdar_DynamicArray_long*:cutils_cdar_DynamicArray_long_map_default3,\
    cutils_cdar_DynamicArray_unsigned_long*:cutils_cdar_DynamicArray_unsigned_long_map_default3,\
    cutils_cdar_DynamicArray_long_long*:cutils_cdar_DynamicArray_long_long_map_default3,\
    cutils_cdar_DynamicArray_unsigned_long_long*:cutils_cdar_DynamicArray_unsigned_long_long_map_default3,\
    cutils_cdar_DynamicArray_float*:cutils_cdar_DynamicArray_float_map_default3,\
    cutils_cdar_DynamicArray_double*:cutils_cdar_DynamicArray_double_map_default3,\
    cutils_cdar_DynamicArray_long_double*:cutils_cdar_DynamicArray_long_double_map_default3,\
    cutils_cdar_DynamicArray_bool*:cutils_cdar_DynamicArray_bool_map_default3,\
    cutils_cdar_DynamicArray_size_t*:cutils_cdar_DynamicArray_size_t_map_default3,\
    cutils_cdar_DynamicArray_ptrdiff_t*:cutils_cdar_DynamicArray_ptrdiff_t_map_default3,\
    cutils_csll_SinglyLinkedList_char*:cutils_csll_SinglyLinkedList_char_map_default3,\
    cutils_csll_SinglyLinkedList_void_ptr*:cutils_csll_SinglyLinkedList_void_ptr_map_default3,\
    cutils_csll_SinglyLinkedList_signed_char*:cutils_csll_SinglyLinkedList_signed_char_map_default3,\
    cutils_csll_SinglyLinkedList_unsigned_char*:cutils_csll_SinglyLinkedList_unsigned_char_map_default3,\
    cutils_csll_SinglyLinkedList_char_ptr*:cutils_csll_SinglyLinkedList_char_ptr_map_default3,\
    cutils_csll_SinglyLinkedList_short*:cutils_csll_SinglyLinkedList_short_map_default3,\
    cutils_csll_SinglyLinkedList_unsigned_short*:cutils_csll_SinglyLinkedList_unsigned_short_map_default3,\
    cutils_csll_SinglyLinkedList_int*:cutils_csll_SinglyLinkedList_int_map_default3,\
    cutils_csll_SinglyLinkedList_unsigned_int*:cutils_csll_SinglyLinkedList_unsigned_int_map_default3,\
    cutils_csll_SinglyLinkedList_long*:cutils_csll_SinglyLinkedList_long_map_default3,\
    cutils_csll_SinglyLinkedList_unsigned_long*:cutils_csll_SinglyLinkedList_unsigned_long_map_default3,\
    cutils_csll_SinglyLinkedList_long_long*:cutils_csll_SinglyLinkedList_long_long_map_default3,\
    cutils_csll_SinglyLinkedList_unsigned_long_long*:cutils_csll_SinglyLinkedList_unsigned_long_long_map_default3,\
    cutils_csll_SinglyLinkedList_float*:cutils_csll_SinglyLinkedList_float_map_default3,\
    cutils_csll_SinglyLinkedList_double*:cutils_csll_SinglyLinkedList_double_map_default3,\
    cutils_csll_SinglyLinkedList_long_double*:cutils_csll_SinglyLinkedList_long_double_map_default3,\
    cutils_csll_SinglyLinkedList_bool*:cutils_csll_SinglyLinkedList_bool_map_default3,\
    cutils_csll_SinglyLinkedList_size_t*:cutils_csll_SinglyLinkedList_size_t_map_default3,\
    cutils_csll_SinglyLinkedList_ptrdiff_t*:cutils_csll_SinglyLinkedList_ptrdiff_t_map_default3)\
    (object,##__VA_ARGS__)
/*----------------------------------------------------------------------------*/
#undef  __cutils_generic_find_args5
#define __cutils_generic_find_args5(object,...) _Generic((object),\
    cutils_csll_SinglyLinkedList_void_ptr*:cutils_csll_SinglyLinkedList_void_ptr_find)\
    (object,##__VA_ARGS__)
/*----------------------------------------------------------------------------*/
#undef  __cutils_generic_find_args4
#define __cutils_generic_find_args4(object,...) _Generic((object),\
    cutils_cdar_DynamicArray_char*:cutils_cdar_DynamicArray_char_find,\
    cutils_cdar_DynamicArray_void_ptr*:cutils_cdar_DynamicArray_void_ptr_find,\
    cutils_cdar_DynamicArray_signed_char*:cutils_cdar_DynamicArray_signed_char_find,\
    cutils_cdar_DynamicArray_unsigned_char*:cutils_cdar_DynamicArray_unsigned_char_find,\
    cutils_cdar_DynamicArray_char_ptr*:cutils_cdar_DynamicArray_char_ptr_find,\
    cutils_cdar_DynamicArray_short*:cutils_cdar_DynamicArray_short_find,\
    cutils_cdar_DynamicArray_unsigned_short*:cutils_cdar_DynamicArray_unsigned_short_find,\
    cutils_cdar_DynamicArray_int*:cutils_cdar_DynamicArray_int_find,\
    cutils_cdar_DynamicArray_unsigned_int*:cutils_cdar_DynamicArray_unsigned_int_find,\
    cutils_cdar_DynamicArray_long*:cutils_cdar_DynamicArray_long_find,\
    cutils_cdar_DynamicArray_unsigned_long*:cutils_cdar_DynamicArray_unsigned_long_find,\
    cutils_cdar_DynamicArray_long_long*:cutils_cdar_DynamicArray_long_long_find,\
    cutils_cdar_DynamicArray_unsigned_long_long*:cutils_cdar_DynamicArray_unsigned_long_long_find,\
    cutils_cdar_DynamicArray_float*:cutils_cdar_DynamicArray_float_find,\
    cutils_cdar_DynamicArray_double*:cutils_cdar_DynamicArray_double_find,\
    cutils_cdar_DynamicArray_long_double*:cutils_cdar_DynamicArray_long_double_find,\
    cutils_cdar_DynamicArray_bool*:cutils_cdar_DynamicArray_bool_find,\
    cutils_cdar_DynamicArray_size_t*:cutils_cdar_DynamicArray_size_t_find,\
    cutils_cdar_DynamicArray_ptrdiff_t*:cutils_cdar_DynamicArray_ptrdiff_t_find,\
    cutils_csll_SinglyLinkedList_char*:cutils_csll_SinglyLinkedList_char_find,\
    cutils_csll_SinglyLinkedList_void_ptr*:cutils_csll_SinglyLinkedList_void_ptr_find_default4,\
    cutils_csll_SinglyLinkedList_signed_char*:cutils_csll_SinglyLinkedList_signed_char_find,\
    cutils_csll_SinglyLinkedList_unsigned_char*:cutils_csll_SinglyLinkedList_unsigned_char_find,\
    cutils_csll_SinglyLinkedList_char_ptr*:cutils_csll_SinglyLinkedList_char_ptr_find,\
    cutils_csll_SinglyLinkedList_short*:cutils_csll_SinglyLinkedList_short_find,\
    cutils_csll_SinglyLinkedList_unsigned_short*:cutils_csll_SinglyLinkedList_unsigned_short_find,\
    cutils_csll_SinglyLinkedList_int*:cutils_csll_SinglyLinkedList_int_find,\
    cutils_csll_SinglyLinkedList_unsigned_int*:cutils_csll_SinglyLinkedList_unsigned_int_find,\
    cutils_csll_SinglyLinkedList_long*:cutils_csll_SinglyLinkedList_long_find,\
    cutils_csll_SinglyLinkedList_unsigned_long*:cutils_csll_SinglyLinkedList_unsigned_long_find,\
    cutils_csll_SinglyLinkedList_long_long*:cutils_csll_SinglyLinkedList_long_long_find,\
    cutils_csll_SinglyLinkedList_unsigned_long_long*:cutils_csll_SinglyLinkedList_unsigned_long_long_find,\
    cutils_csll_SinglyLinkedList_float*:cutils_csll_SinglyLinkedList_float_find,\
    cutils_csll_SinglyLinkedList_double*:cutils_csll_SinglyLinkedList_double_find,\
    cutils_csll_SinglyLinkedList_long_double*:cutils_csll_SinglyLinkedList_long_double_find,\
    cutils_csll_SinglyLinkedList_bool*:cutils_csll_SinglyLinkedList_bool_find,\
    cutils_csll_SinglyLinkedList_size_t*:cutils_csll_SinglyLinkedList_size_t_find,\
    cutils_csll_SinglyLinkedList_ptrdiff_t*:cutils_csll_SinglyLinkedList_ptrdiff_t_find)\
    (object,##__VA_ARGS__)
/*----------------------------------------------------------------------------*/
#undef  __cutils_generic_find_args3
#define __cutils_generic_find_args3(object,...) _Generic((object),\
    cutils_cdar_DynamicArray_char*:cutils_cdar_DynamicArray_char_find_default3,\
    cutils_cdar_DynamicArray_void_ptr*:cutils_cdar_DynamicArray_void_ptr_find_default3,\
    cutils_cdar_DynamicArray_signed_char*:cutils_cdar_DynamicArray_signed_char_find_default3,\
    cutils_cdar_DynamicArray_unsigned_char*:cutils_cdar_DynamicArray_unsigned_char_find_default3,\
    cutils_cdar_DynamicArray_char_ptr*:cutils_cdar_DynamicArray_char_ptr_find_default3,\
    cutils_cdar_DynamicArray_short*:cutils_cdar_DynamicArray_short_find_default3,\
    cutils_cdar_DynamicArray_unsigned_short*:cutils_cdar_DynamicArray_unsigned_short_find_default3,\
    cutils_cdar_DynamicArray_int*:cutils_cdar_DynamicArray_int_find_default3,\
    cutils_cdar_DynamicArray_unsigned_int*:cutils_cdar_DynamicArray_unsigned_int_find_default3,\
    cutils_cdar_DynamicArray_long*:cutils_cdar_DynamicArray_long_find_default3,\
    cutils_cdar_DynamicArray_unsigned_long*:cutils_cdar_DynamicArray_unsigned_long_find_default3,\
    cutils_cdar_DynamicArray_long_long*:cutils_cdar_DynamicArray_long_long_find_default3,\
    cutils_cdar_DynamicArray_unsigned_long_long*:cutils_cdar_DynamicArray_unsigned_long_long_find_default3,\
    cutils_cdar_DynamicArray_float*:cutils_cdar_DynamicArray_float_find_default3,\
    cutils_cdar_DynamicArray_double*:cutils_cdar_DynamicArray_double_find_default3,\
    cutils_cdar_DynamicArray_long_double*:cutils_cdar_DynamicArray_long_double_find_default3,\
    cutils_cdar_DynamicArray_bool*:cutils_cdar_DynamicArray_bool_find_default3,\
    cutils_cdar_DynamicArray_size_t*:cutils_cdar_DynamicArray_size_t_find_default3,\
    cutils_cdar_DynamicArray_ptrdiff_t*:cutils_cdar_DynamicArray_ptrdiff_t_find_default3,\
    cutils_csll_SinglyLinkedList_char*:cutils_csll_SinglyLinkedList_char_find_default3,\
    cutils_csll_SinglyLinkedList_signed_char*:cutils_csll_SinglyLinkedList_signed_char_find_default3,\
    cutils_csll_SinglyLinkedList_unsigned_char*:cutils_csll_SinglyLinkedList_unsigned_char_find_default3,\
    cutils_csll_SinglyLinkedList_char_ptr*:cutils_csll_SinglyLinkedList_char_ptr_find_default3,\
    cutils_csll_SinglyLinkedList_short*:cutils_csll_SinglyLinkedList_short_find_default3,\
    cutils_csll_SinglyLinkedList_unsigned_short*:cutils_csll_SinglyLinkedList_unsigned_short_find_default3,\
    cutils_csll_SinglyLinkedList_int*:cutils_csll_SinglyLinkedList_int_find_default3,\
    cutils_csll_SinglyLinkedList_unsigned_int*:cutils_csll_SinglyLinkedList_unsigned_int_find_default3,\
    cutils_csll_SinglyLinkedList_long*:cutils_csll_SinglyLinkedList_long_find_default3,\
    cutils_csll_SinglyLinkedList_unsigned_long*:cutils_csll_SinglyLinkedList_unsigned_long_find_default3,\
    cutils_csll_SinglyLinkedList_long_long*:cutils_csll_SinglyLinkedList_long_long_find_default3,\
    cutils_csll_SinglyLinkedList_unsigned_long_long*:cutils_csll_SinglyLinkedList_unsigned_long_long_find_default3,\
    cutils_csll_SinglyLinkedList_float*:cutils_csll_SinglyLinkedList_float_find_default3,\
    cutils_csll_SinglyLinkedList_double*:cutils_csll_SinglyLinkedList_double_find_default3,\
    cutils_csll_SinglyLinkedList_long_double*:cutils_csll_SinglyLinkedList_long_double_find_default3,\
    cutils_csll_SinglyLinkedList_bool*:cutils_csll_SinglyLinkedList_bool_find_default3,\
    cutils_csll_SinglyLinkedList_size_t*:cutils_csll_SinglyLinkedList_size_t_find_default3,\
    cutils_csll_SinglyLinkedList_ptrdiff_t*:cutils_csll_SinglyLinkedList_ptrdiff_t_find_default3)\
    (object,##__VA_ARGS__)
/*----------------------------------------------------------------------------*/
#undef  __cutils_generic_findall_args5
#define __cutils_generic_findall_args5(object,...) _Generic((object),\
    cutils_csll_SinglyLinkedList_void_ptr*:cutils_csll_SinglyLinkedList_void_ptr_findall)\
    (object,##__VA_ARGS__)
/*----------------------------------------------------------------------------*/
#undef  __cutils_generic_findall_args4
#define __cutils_generic_findall_args4(object,...) _Generic((object),\
    cutils_cdar_DynamicArray_char*:cutils_cdar_DynamicArray_char_findall,\
    cutils_cdar_DynamicArray_void_ptr*:cutils_cdar_DynamicArray_void_ptr_findall,\
    cutils_cdar_DynamicArray_signed_char*:cutils_cdar_DynamicArray_signed_char_findall,\
    cutils_cdar_DynamicArray_unsigned_char*:cutils_cdar_DynamicArray_unsigned_char_findall,\
    cutils_cdar_DynamicArray_char_ptr*:cutils_cdar_DynamicArray_char_ptr_findall,\
    cutils_cdar_DynamicArray_short*:cutils_cdar_DynamicArray_short_findall,\
    cutils_cdar_DynamicArray_unsigned_short*:cutils_cdar_DynamicArray_unsigned_short_findall,\
    cutils_cdar_DynamicArray_int*:cutils_cdar_DynamicArray_int_findall,\
    cutils_cdar_DynamicArray_unsigned_int*:cutils_cdar_DynamicArray_unsigned_int_findall,\
    cutils_cdar_DynamicArray_long*:cutils_cdar_DynamicArray_long_findall,\
    cutils_cdar_DynamicArray_unsigned_long*:cutils_cdar_DynamicArray_unsigned_long_findall,\
    cutils_cdar_DynamicArray_long_long*:cutils_cdar_DynamicArray_long_long_findall,\
    cutils_cdar_DynamicArray_unsigned_long_long*:cutils_cdar_DynamicArray_unsigned_long_long_findall,\
    cutils_cdar_DynamicArray_float*:cutils_cdar_DynamicArray_float_findall,\
    cutils_cdar_DynamicArray_double*:cutils_cdar_DynamicArray_double_findall,\
    cutils_cdar_DynamicArray_long_double*:cutils_cdar_DynamicArray_long_double_findall,\
    cutils_cdar_DynamicArray_bool*:cutils_cdar_DynamicArray_bool_findall,\
    cutils_cdar_DynamicArray_size_t*:cutils_cdar_DynamicArray_size_t_findall,\
    cutils_cdar_DynamicArray_ptrdiff_t*:cutils_cdar_DynamicArray_ptrdiff_t_findall,\
    cutils_csll_SinglyLinkedList_char*:cutils_csll_SinglyLinkedList_char_findall,\
    cutils_csll_SinglyLinkedList_void_ptr*:cutils_csll_SinglyLinkedList_void_ptr_findall_default4,\
    cutils_csll_SinglyLinkedList_signed_char*:cutils_csll_SinglyLinkedList_signed_char_findall,\
    cutils_csll_SinglyLinkedList_unsigned_char*:cutils_csll_SinglyLinkedList_unsigned_char_findall,\
    cutils_csll_SinglyLinkedList_char_ptr*:cutils_csll_SinglyLinkedList_char_ptr_findall,\
    cutils_csll_SinglyLinkedList_short*:cutils_csll_SinglyLinkedList_short_findall,\
    cutils_csll_SinglyLinkedList_unsigned_short*:cutils_csll_SinglyLinkedList_unsigned_short_findall,\
    cutils_csll_SinglyLinkedList_int*:cutils_csll_SinglyLinkedList_int_findall,\
    cutils_csll_SinglyLinkedList_unsigned_int*:cutils_csll_SinglyLinkedList_unsigned_int_findall,\
    cutils_csll_SinglyLinkedList_long*:cutils_csll_SinglyLinkedList_long_findall,\
    cutils_csll_SinglyLinkedList_unsigned_long*:cutils_csll_SinglyLinkedList_unsigned_long_findall,\
    cutils_csll_SinglyLinkedList_long_long*:cutils_csll_SinglyLinkedList_long_long_findall,\
    cutils_csll_SinglyLinkedList_unsigned_long_long*:cutils_csll_SinglyLinkedList_unsigned_long_long_findall,\
    cutils_csll_SinglyLinkedList_float*:cutils_csll_SinglyLinkedList_float_findall,\
    cutils_csll_SinglyLinkedList_double*:cutils_csll_SinglyLinkedList_double_findall,\
    cutils_csll_SinglyLinkedList_long_double*:cutils_csll_SinglyLinkedList_long_double_findall,\
    cutils_csll_SinglyLinkedList_bool*:cutils_csll_SinglyLinkedList_bool_findall,\
    cutils_csll_SinglyLinkedList_size_t*:cutils_csll_SinglyLinkedList_size_t_findall,\
    cutils_csll_SinglyLinkedList_ptrdiff_t*:cutils_csll_SinglyLinkedList_ptrdiff_t_findall)\
    (object,##__VA_ARGS__)
/*----------------------------------------------------------------------------*/
#undef  __cutils_generic_findall_args3
#define __cutils_generic_findall_args3(object,...) _Generic((object),\
    cutils_cdar_DynamicArray_char*:cutils_cdar_DynamicArray_char_findall_default3,\
    cutils_cdar_DynamicArray_void_ptr*:cutils_cdar_DynamicArray_void_ptr_findall_default3,\
    cutils_cdar_DynamicArray_signed_char*:cutils_cdar_DynamicArray_signed_char_findall_default3,\
    cutils_cdar_DynamicArray_unsigned_char*:cutils_cdar_DynamicArray_unsigned_char_findall_default3,\
    cutils_cdar_DynamicArray_char_ptr*:cutils_cdar_DynamicArray_char_ptr_findall_default3,\
    cutils_cdar_DynamicArray_short*:cutils_cdar_DynamicArray_short_findall_default3,\
    cutils_cdar_DynamicArray_unsigned_short*:cutils_cdar_DynamicArray_unsigned_short_findall_default3,\
    cutils_cdar_DynamicArray_int*:cutils_cdar_DynamicArray_int_findall_default3,\
    cutils_cdar_DynamicArray_unsigned_int*:cutils_cdar_DynamicArray_unsigned_int_findall_default3,\
    cutils_cdar_DynamicArray_long*:cutils_cdar_DynamicArray_long_findall_default3,\
    cutils_cdar_DynamicArray_unsigned_long*:cutils_cdar_DynamicArray_unsigned_long_findall_default3,\
    cutils_cdar_DynamicArray_long_long*:cutils_cdar_DynamicArray_long_long_findall_default3,\
    cutils_cdar_DynamicArray_unsigned_long_long*:cutils_cdar_DynamicArray_unsigned_long_long_findall_default3,\
    cutils_cdar_DynamicArray_float*:cutils_cdar_DynamicArray_float_findall_default3,\
    cutils_cdar_DynamicArray_double*:cutils_cdar_DynamicArray_double_findall_default3,\
    cutils_cdar_DynamicArray_long_double*:cutils_cdar_DynamicArray_long_double_findall_default3,\
    cutils_cdar_DynamicArray_bool*:cutils_cdar_DynamicArray_bool_findall_default3,\
    cutils_cdar_DynamicArray_size_t*:cutils_cdar_DynamicArray_size_t_findall_default3,\
    cutils_cdar_DynamicArray_ptrdiff_t*:cutils_cdar_DynamicArray_ptrdiff_t_findall_default3,\
    cutils_csll_SinglyLinkedList_char*:cutils_csll_SinglyLinkedList_char_findall_default3,\
    cutils_csll_SinglyLinkedList_signed_char*:cutils_csll_SinglyLinkedList_signed_char_findall_default3,\
    cutils_csll_SinglyLinkedList_unsigned_char*:cutils_csll_SinglyLinkedList_unsigned_char_findall_default3,\
    cutils_csll_SinglyLinkedList_char_ptr*:cutils_csll_SinglyLinkedList_char_ptr_findall_default3,\
    cutils_csll_SinglyLinkedList_short*:cutils_csll_SinglyLinkedList_short_findall_default3,\
    cutils_csll_SinglyLinkedList_unsigned_short*:cutils_csll_SinglyLinkedList_unsigned_short_findall_default3,\
    cutils_csll_SinglyLinkedList_int*:cutils_csll_SinglyLinkedList_int_findall_default3,\
    cutils_csll_SinglyLinkedList_unsigned_int*:cutils_csll_SinglyLinkedList_unsigned_int_findall_default3,\
    cutils_csll_SinglyLinkedList_long*:cutils_csll_SinglyLinkedList_long_findall_default3,\
    cutils_csll_SinglyLinkedList_unsigned_long*:cutils_csll_SinglyLinkedList_unsigned_long_findall_default3,\
    cutils_csll_SinglyLinkedList_long_long*:cutils_csll_SinglyLinkedList_long_long_findall_default3,\
    cutils_csll_SinglyLinkedList_unsigned_long_long*:cutils_csll_SinglyLinkedList_unsigned_long_long_findall_default3,\
    cutils_csll_SinglyLinkedList_float*:cutils_csll_SinglyLinkedList_float_findall_default3,\
    cutils_csll_SinglyLinkedList_double*:cutils_csll_SinglyLinkedList_double_findall_default3,\
    cutils_csll_SinglyLinkedList_long_double*:cutils_csll_SinglyLinkedList_long_double_findall_default3,\
    cutils_csll_SinglyLinkedList_bool*:cutils_csll_SinglyLinkedList_bool_findall_default3,\
    cutils_csll_SinglyLinkedList_size_t*:cutils_csll_SinglyLinkedList_size_t_findall_default3,\
    cutils_csll_SinglyLinkedList_ptrdiff_t*:cutils_csll_SinglyLinkedList_ptrdiff_t_findall_default3)\
    (object,##__VA_ARGS__)
/*----------------------------------------------------------------------------*/
#undef  __cutils_generic_print_args4
#define __cutils_generic_print_args4(object,...) _Generic((object),\
    cutils_cdar_DynamicArray_char*:cutils_cdar_DynamicArray_char_print,\
    cutils_cdar_DynamicArray_void_ptr*:cutils_cdar_DynamicArray_void_ptr_print,\
    cutils_cdar_DynamicArray_signed_char*:cutils_cdar_DynamicArray_signed_char_print,\
    cutils_cdar_DynamicArray_unsigned_char*:cutils_cdar_DynamicArray_unsigned_char_print,\
    cutils_cdar_DynamicArray_char_ptr*:cutils_cdar_DynamicArray_char_ptr_print,\
    cutils_cdar_DynamicArray_short*:cutils_cdar_DynamicArray_short_print,\
    cutils_cdar_DynamicArray_unsigned_short*:cutils_cdar_DynamicArray_unsigned_short_print,\
    cutils_cdar_DynamicArray_int*:cutils_cdar_DynamicArray_int_print,\
    cutils_cdar_DynamicArray_unsigned_int*:cutils_cdar_DynamicArray_unsigned_int_print,\
    cutils_cdar_DynamicArray_long*:cutils_cdar_DynamicArray_long_print,\
    cutils_cdar_DynamicArray_unsigned_long*:cutils_cdar_DynamicArray_unsigned_long_print,\
    cutils_cdar_DynamicArray_long_long*:cutils_cdar_DynamicArray_long_long_print,\
    cutils_cdar_DynamicArray_unsigned_long_long*:cutils_cdar_DynamicArray_unsigned_long_long_print,\
    cutils_cdar_DynamicArray_float*:cutils_cdar_DynamicArray_float_print,\
    cutils_cdar_DynamicArray_double*:cutils_cdar_DynamicArray_double_print,\
    cutils_cdar_DynamicArray_long_double*:cutils_cdar_DynamicArray_long_double_print,\
    cutils_cdar_DynamicArray_bool*:cutils_cdar_DynamicArray_bool_print,\
    cutils_cdar_DynamicArray_size_t*:cutils_cdar_DynamicArray_size_t_print,\
    cutils_cdar_DynamicArray_ptrdiff_t*:cutils_cdar_DynamicArray_ptrdiff_t_print,\
    cutils_csll_SinglyLinkedList_char*:cutils_csll_SinglyLinkedList_char_print,\
    cutils_csll_SinglyLinkedList_void_ptr*:cutils_csll_SinglyLinkedList_void_ptr_print,\
    cutils_csll_SinglyLinkedList_signed_char*:cutils_csll_SinglyLinkedList_signed_char_print,\
    cutils_csll_SinglyLinkedList_unsigned_char*:cutils_csll_SinglyLinkedList_unsigned_char_print,\
    cutils_csll_SinglyLinkedList_char_ptr*:cutils_csll_SinglyLinkedList_char_ptr_print,\
    cutils_csll_SinglyLinkedList_short*:cutils_csll_SinglyLinkedList_short_print,\
    cutils_csll_SinglyLinkedList_unsigned_short*:cutils_csll_SinglyLinkedList_unsigned_short_print,\
    cutils_csll_SinglyLinkedList_int*:cutils_csll_SinglyLinkedList_int_print,\
    cutils_csll_SinglyLinkedList_unsigned_int*:cutils_csll_SinglyLinkedList_unsigned_int_print,\
    cutils_csll_SinglyLinkedList_long*:cutils_csll_SinglyLinkedList_long_print,\
    cutils_csll_SinglyLinkedList_unsigned_long*:cutils_csll_SinglyLinkedList_unsigned_long_print,\
    cutils_csll_SinglyLinkedList_long_long*:cutils_csll_SinglyLinkedList_long_long_print,\
    cutils_csll_SinglyLinkedList_unsigned_long_long*:cutils_csll_SinglyLinkedList_unsigned_long_long_print,\
    cutils_csll_SinglyLinkedList_float*:cutils_csll_SinglyLinkedList_float_print,\
    cutils_csll_SinglyLinkedList_double*:cutils_csll_SinglyLinkedList_double_print,\
    cutils_csll_SinglyLinkedList_long_double*:cutils_csll_SinglyLinkedList_long_double_print,\
    cutils_csll_SinglyLinkedList_bool*:cutils_csll_SinglyLinkedList_bool_print,\
    cutils_csll_SinglyLinkedList_size_t*:cutils_csll_SinglyLinkedList_size_t_print,\
    cutils_csll_SinglyLinkedList_ptrdiff_t*:cutils_csll_SinglyLinkedList_ptrdiff_t_print)\
    (object,##__VA_ARGS__)
/*----------------------------------------------------------------------------*/
#undef  __cutils_generic_print_args2
#define __cutils_generic_print_args2(object,...) _Generic((object),\
    cutils_cdar_DynamicArray_void_ptr*:cutils_cdar_DynamicArray_void_ptr_print_default2,\
    cutils_csll_SinglyLinkedList_void_ptr*:cutils_csll_SinglyLinkedList_void_ptr_print_default2)\
    (object,##__VA_ARGS__)
/*----------------------------------------------------------------------------*/
#undef  __cutils_generic_print_args1
#define __cutils_generic_print_args1(object,...) _Generic((object),\
    cutils_cdar_DynamicArray_char*:cutils_cdar_DynamicArray_char_print_default1,\
    cutils_cdar_DynamicArray_void_ptr*:cutils_cdar_DynamicArray_void_ptr_print_default1,\
    cutils_cdar_DynamicArray_signed_char*:cutils_cdar_DynamicArray_signed_char_print_default1,\
    cutils_cdar_DynamicArray_unsigned_char*:cutils_cdar_DynamicArray_unsigned_char_print_default1,\
    cutils_cdar_DynamicArray_char_ptr*:cutils_cdar_DynamicArray_char_ptr_print_default1,\
    cutils_cdar_DynamicArray_short*:cutils_cdar_DynamicArray_short_print_default1,\
    cutils_cdar_DynamicArray_unsigned_short*:cutils_cdar_DynamicArray_unsigned_short_print_default1,\
    cutils_cdar_DynamicArray_int*:cutils_cdar_DynamicArray_int_print_default1,\
    cutils_cdar_DynamicArray_unsigned_int*:cutils_cdar_DynamicArray_unsigned_int_print_default1,\
    cutils_cdar_DynamicArray_long*:cutils_cdar_DynamicArray_long_print_default1,\
    cutils_cdar_DynamicArray_unsigned_long*:cutils_cdar_DynamicArray_unsigned_long_print_default1,\
    cutils_cdar_DynamicArray_long_long*:cutils_cdar_DynamicArray_long_long_print_default1,\
    cutils_cdar_DynamicArray_unsigned_long_long*:cutils_cdar_DynamicArray_unsigned_long_long_print_default1,\
    cutils_cdar_DynamicArray_float*:cutils_cdar_DynamicArray_float_print_default1,\
    cutils_cdar_DynamicArray_double*:cutils_cdar_DynamicArray_double_print_default1,\
    cutils_cdar_DynamicArray_long_double*:cutils_cdar_DynamicArray_long_double_print_default1,\
    cutils_cdar_DynamicArray_bool*:cutils_cdar_DynamicArray_bool_print_default1,\
    cutils_cdar_DynamicArray_size_t*:cutils_cdar_DynamicArray_size_t_print_default1,\
    cutils_cdar_DynamicArray_ptrdiff_t*:cutils_cdar_DynamicArray_ptrdiff_t_print_default1,\
    cutils_csll_SinglyLinkedList_char*:cutils_csll_SinglyLinkedList_char_print_default1,\
    cutils_csll_SinglyLinkedList_void_ptr*:cutils_csll_SinglyLinkedList_void_ptr_print_default1,\
    cutils_csll_SinglyLinkedList_signed_char*:cutils_csll_SinglyLinkedList_signed_char_print_default1,\
    cutils_csll_SinglyLinkedList_unsigned_char*:cutils_csll_SinglyLinkedList_unsigned_char_print_default1,\
    cutils_csll_SinglyLinkedList_char_ptr*:cutils_csll_SinglyLinkedList_char_ptr_print_default1,\
    cutils_csll_SinglyLinkedList_short*:cutils_csll_SinglyLinkedList_short_print_default1,\
    cutils_csll_SinglyLinkedList_unsigned_short*:cutils_csll_SinglyLinkedList_unsigned_short_print_default1,\
    cutils_csll_SinglyLinkedList_int*:cutils_csll_SinglyLinkedList_int_print_default1,\
    cutils_csll_SinglyLinkedList_unsigned_int*:cutils_csll_SinglyLinkedList_unsigned_int_print_default1,\
    cutils_csll_SinglyLinkedList_long*:cutils_csll_SinglyLinkedList_long_print_default1,\
    cutils_csll_SinglyLinkedList_unsigned_long*:cutils_csll_SinglyLinkedList_unsigned_long_print_default1,\
    cutils_csll_SinglyLinkedList_long_long*:cutils_csll_SinglyLinkedList_long_long_print_default1,\
    cutils_csll_SinglyLinkedList_unsigned_long_long*:cutils_csll_SinglyLinkedList_unsigned_long_long_print_default1,\
    cutils_csll_SinglyLinkedList_float*:cutils_csll_SinglyLinkedList_float_print_default1,\
    cutils_csll_SinglyLinkedList_double*:cutils_csll_SinglyLinkedList_double_print_default1,\
    cutils_csll_SinglyLinkedList_long_double*:cutils_csll_SinglyLinkedList_long_double_print_default1,\
    cutils_csll_SinglyLinkedList_bool*:cutils_csll_SinglyLinkedList_bool_print_default1,\
    cutils_csll_SinglyLinkedList_size_t*:cutils_csll_SinglyLinkedList_size_t_print_default1,\
    cutils_csll_SinglyLinkedList_ptrdiff_t*:cutils_csll_SinglyLinkedList_ptrdiff_t_print_default1,\
    char:cutils_cout_char_print,\
    signed char:cutils_cout_signed_char_print,\
    unsigned char:cutils_cout_unsigned_char_print,\
    char*:cutils_cout_char_ptr_print,\
    short:cutils_cout_short_print,\
    unsigned short:cutils_cout_unsigned_short_print,\
    int:cutils_cout_int_print,\
    unsigned int:cutils_cout_unsigned_int_print,\
    long:cutils_cout_long_print,\
    unsigned long:cutils_cout_unsigned_long_print,\
    long long:cutils_cout_long_long_print,\
    unsigned long long:cutils_cout_unsigned_long_long_print,\
    float:cutils_cout_float_print,\
    double:cutils_cout_double_print,\
    long double:cutils_cout_long_double_print,\
    bool:cutils_cout_bool_print,\
    void*:cutils_cout_void_ptr_print)\
    (object,##__VA_ARGS__)
/*----------------------------------------------------------------------------*/
#undef  __cutils_generic_iter
#define __cutils_generic_iter(object,...) _Generic((object),\
    cutils_csll_SinglyLinkedList_char*:cutils_csll_SinglyLinkedList_char_iter,\
    cutils_csll_SinglyLinkedList_void_ptr*:cutils_csll_SinglyLinkedList_void_ptr_iter,\
    cutils_csll_SinglyLinkedList_signed_char*:cutils_csll_SinglyLinkedList_signed_char_iter,\
    cutils_csll_SinglyLinkedList_unsigned_char*:cutils_csll_SinglyLinkedList_unsigned_char_iter,\
    cutils_csll_SinglyLinkedList_char_ptr*:cutils_csll_SinglyLinkedList_char_ptr_iter,\
    cutils_csll_SinglyLinkedList_short*:cutils_csll_SinglyLinkedList_short_iter,\
    cutils_csll_SinglyLinkedList_unsigned_short*:cutils_csll_SinglyLinkedList_unsigned_short_iter,\
    cutils_csll_SinglyLinkedList_int*:cutils_csll_SinglyLinkedList_int_iter,\
    cutils_csll_SinglyLinkedList_unsigned_int*:cutils_csll_SinglyLinkedList_unsigned_int_iter,\
    cutils_csll_SinglyLinkedList_long*:cutils_csll_SinglyLinkedList_long_iter,\
    cutils_csll_SinglyLinkedList_unsigned_long*:cutils_csll_SinglyLinkedList_unsigned_long_iter,\
    cutils_csll_SinglyLinkedList_long_long*:cutils_csll_SinglyLinkedList_long_long_iter,\
    cutils_csll_SinglyLinkedList_unsigned_long_long*:cutils_csll_SinglyLinkedList_unsigned_long_long_iter,\
    cutils_csll_SinglyLinkedList_float*:cutils_csll_SinglyLinkedList_float_iter,\
    cutils_csll_SinglyLinkedList_double*:cutils_csll_SinglyLinkedList_double_iter,\
    cutils_csll_SinglyLinkedList_long_double*:cutils_csll_SinglyLinkedList_long_double_iter,\
    cutils_csll_SinglyLinkedList_bool*:cutils_csll_SinglyLinkedList_bool_iter,\
    cutils_csll_SinglyLinkedList_size_t*:cutils_csll_SinglyLinkedList_size_t_iter,\
    cutils_csll_SinglyLinkedList_ptrdiff_t*:cutils_csll_SinglyLinkedList_ptrdiff_t_iter)\
    (object,##__VA_ARGS__)
/*----------------------------------------------------------------------------*/
#undef  __cutils_generic_next
#define __cutils_generic_next(object,...) _Generic((object),\
    cutils_csll_SinglyLinkedList_char_iterator*:cutils_csll_SinglyLinkedList_char_iterator_next,\
    cutils_csll_SinglyLinkedList_void_ptr_iterator:cutils_csll_SinglyLinkedList_void_ptr_iterator_next,\
    cutils_csll_SinglyLinkedList_signed_char_iterator*:cutils_csll_SinglyLinkedList_signed_char_iterator_next,\
    cutils_csll_SinglyLinkedList_unsigned_char_iterator*:cutils_csll_SinglyLinkedList_unsigned_char_iterator_next,\
    cutils_csll_SinglyLinkedList_char_ptr_iterator*:cutils_csll_SinglyLinkedList_char_ptr_iterator_next,\
    cutils_csll_SinglyLinkedList_short_iterator*:cutils_csll_SinglyLinkedList_short_iterator_next,\
    cutils_csll_SinglyLinkedList_unsigned_short_iterator*:cutils_csll_SinglyLinkedList_unsigned_short_iterator_next,\
    cutils_csll_SinglyLinkedList_int_iterator*:cutils_csll_SinglyLinkedList_int_iterator_next,\
    cutils_csll_SinglyLinkedList_unsigned_int_iterator*:cutils_csll_SinglyLinkedList_unsigned_int_iterator_next,\
    cutils_csll_SinglyLinkedList_long_iterator*:cutils_csll_SinglyLinkedList_long_iterator_next,\
    cutils_csll_SinglyLinkedList_unsigned_long_iterator*:cutils_csll_SinglyLinkedList_unsigned_long_iterator_next,\
    cutils_csll_SinglyLinkedList_long_long_iterator*:cutils_csll_SinglyLinkedList_long_long_iterator_next,\
    cutils_csll_SinglyLinkedList_unsigned_long_long_iterator*:cutils_csll_SinglyLinkedList_unsigned_long_long_iterator_next,\
    cutils_csll_SinglyLinkedList_float_iterator*:cutils_csll_SinglyLinkedList_float_iterator_next,\
    cutils_csll_SinglyLinkedList_double_iterator*:cutils_csll_SinglyLinkedList_double_iterator_next,\
    cutils_csll_SinglyLinkedList_long_double_iterator*:cutils_csll_SinglyLinkedList_long_double_iterator_next,\
    cutils_csll_SinglyLinkedList_bool_iterator*:cutils_csll_SinglyLinkedList_bool_iterator_next,\
    cutils_csll_SinglyLinkedList_size_t_iterator*:cutils_csll_SinglyLinkedList_size_t_iterator_next,\
    cutils_csll_SinglyLinkedList_ptrdiff_t_iterator*:cutils_csll_SinglyLinkedList_ptrdiff_t_iterator_next)\
    (object,##__VA_ARGS__)

#endif /* guard */
