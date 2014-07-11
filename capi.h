/* INFO ************************************************************************
**                                                                            **
**                                   cutils                                   **
**                                   ======                                   **
**                                                                            **
**                     Modern and Lightweight C Utilities                     **
**                       Version: 0.8.72.365 (20140711)                       **
**                                                                            **
**                                File: capi.h                                **
**                                                                            **
**           Designed and written by Peter Varo. Copyright (c) 2014           **
**             License agreement is provided in the LICENSE file              **
**                 For more info visit: http://www.cutils.org                 **
**                                                                            **
************************************************************************ INFO */

#ifndef _C_APPLICATION_PROGRAMMING_INTERFACE_H_27277619327951796_
#define _C_APPLICATION_PROGRAMMING_INTERFACE_H_27277619327951796_

#include "carg.h"

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

#define new(...) __cutils_generic_new(__VA_ARGS__)
#define data(...) __cutils_generic_data(__VA_ARGS__)
#define raw(...) __cutils_generic_raw(__VA_ARGS__)
#define append(...) __cutils_generic_append(__VA_ARGS__)
#define push(...) __cutils_generic_push(__VA_ARGS__)
#define set(...) __cutils_generic_set(__VA_ARGS__)
#define pop(...) __cutils_generic_pop(__VA_ARGS__)
#define sub(...) __cutils_generic_sub(__VA_ARGS__)
#define get(...) __cutils_generic_get(__VA_ARGS__)
#define find(...) __cutils_generic_find(__VA_ARGS__)
#define findall(...) __cutils_generic_findall(__VA_ARGS__)
#define del(...) __cutils_generic_del(__VA_ARGS__)
#define len(...) __cutils_generic_len(__VA_ARGS__)
#define size(...) __cutils_generic_size(__VA_ARGS__)
#define resize(...) __cutils_generic_resize(__VA_ARGS__)
#define swap(...) __cutils_generic_swap(__VA_ARGS__)
#define reverse(...) __cutils_generic_reverse(__VA_ARGS__)
#define pull(...) __cutils_generic_pull(__VA_ARGS__)
#define truncate(...) __cutils_generic_truncate(__VA_ARGS__)
#define clear(...) __cutils_generic_clear(__VA_ARGS__)

#ifdef _C_ARGUMENTS_H_19836769466709525_
  #undef zero
  #undef vargs
  #define zero(...) cutils_carg_zero(__VA_ARGS__)
  #define vargs(...) cutils_carg_vargs(__VA_ARGS__)
#endif /* _C_ARGUMENTS_H_19836769466709525_ */

#ifdef _C_DEBUG_H_10629572188582681_
  #undef debug
  #define debug(...) cutils_cbug_debug(__VA_ARGS__)
#endif /* _C_DEBUG_H_10629572188582681_ */

#ifdef _C_FRAME_PER_SECOND_H_2834550704086395_
  #undef getfps
  #undef printfps
  #define getfps(...) cutils_cfps_getfps(__VA_ARGS__)
  #define printfps(...) cutils_cfps_printfps(__VA_ARGS__)
#endif /* _C_FRAME_PER_SECOND_H_2834550704086395_ */

#ifdef _C_PROFILER_H_6503982333617538_
  #undef  profile
  #define profile(...) cutils_cpro_profile(__VA_ARGS__)
#endif /* _C_PROFILER_H_6503982333617538_ */

#ifdef _C_EXCEPTIONS_H_5362957038900146_
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
#endif /* _C_EXCEPTIONS_H_5362957038900146_ */

#ifdef _C_UNIT_TEST_TOOLS_H_3818217702141947_
  typedef cutils_cutt_Tester Tester;
  #undef try
  #undef report
  #define try(...) cutils_cutt_try(__VA_ARGS__)
  #define report(...) cutils_cutt_report(__VA_ARGS__)
#else
  /* HACK: Define type to make _Generic() work */
  typedef struct {} cutils_cutt_Tester;
#endif /* _C_UNIT_TEST_TOOLS_H_3818217702141947_ */

#ifdef _C_DYNAMIC_ARRAY_H_2427147457128005_
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
  typedef cutils_cdar_DynamicArray_void_ptr DynamicArray_void_ptr;
#else
  #error "Where the hell is CDAR?"
#endif /* _C_DYNAMIC_ARRAY_H_2427147457128005_ */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
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

#define cutils_new(...) __cutils_generic_new(__VA_ARGS__)
#define cutils_data(...) __cutils_generic_data(__VA_ARGS__)
#define cutils_raw(...) __cutils_generic_raw(__VA_ARGS__)
#define cutils_append(...) __cutils_generic_append(__VA_ARGS__)
#define cutils_push(...) __cutils_generic_push(__VA_ARGS__)
#define cutils_set(...) __cutils_generic_set(__VA_ARGS__)
#define cutils_pop(...) __cutils_generic_pop(__VA_ARGS__)
#define cutils_sub(...) __cutils_generic_sub(__VA_ARGS__)
#define cutils_get(...) __cutils_generic_get(__VA_ARGS__)
#define cutils_find(...) __cutils_generic_find(__VA_ARGS__)
#define cutils_findall(...) __cutils_generic_findall(__VA_ARGS__)
#define cutils_del(...) __cutils_generic_del(__VA_ARGS__)
#define cutils_len(...) __cutils_generic_len(__VA_ARGS__)
#define cutils_size(...) __cutils_generic_size(__VA_ARGS__)
#define cutils_resize(...) __cutils_generic_resize(__VA_ARGS__)
#define cutils_swap(...) __cutils_generic_swap(__VA_ARGS__)
#define cutils_reverse(...) __cutils_generic_reverse(__VA_ARGS__)
#define cutils_pull(...) __cutils_generic_pull(__VA_ARGS__)
#define cutils_truncate(...) __cutils_generic_truncate(__VA_ARGS__)
#define cutils_clear(...) __cutils_generic_clear(__VA_ARGS__)

#ifdef _C_ARGUMENTS_H_19836769466709525_
  #undef cutils_zero
  #undef cutils_vargs
  #define cutils_zero(...) cutils_carg_zero(__VA_ARGS__)
  #define cutils_vargs(...) cutils_carg_vargs(__VA_ARGS__)
#endif /* _C_ARGUMENTS_H_19836769466709525_ */

#ifdef _C_DEBUG_H_10629572188582681_
  #undef cutils_debug
  #define cutils_debug(...) cutils_cbug_debug(__VA_ARGS__)
#endif /* _C_DEBUG_H_10629572188582681_ */

#ifdef _C_FRAME_PER_SECOND_H_2834550704086395_
  #undef cutils_getfps
  #undef cutils_printfps
  #define cutils_getfps(...) cutils_cfps_getfps(__VA_ARGS__)
  #define cutils_printfps(...) cutils_cfps_printfps(__VA_ARGS__)
#endif /* _C_FRAME_PER_SECOND_H_2834550704086395_ */

#ifdef _C_PROFILER_H_6503982333617538_
  #undef  cutils_profile
  #define cutils_profile(...) cutils_cpro_profile(__VA_ARGS__)
#endif /* _C_PROFILER_H_6503982333617538_ */

#ifdef _C_EXCEPTIONS_H_5362957038900146_
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
#endif /* _C_EXCEPTIONS_H_5362957038900146_ */

#ifdef _C_UNIT_TEST_TOOLS_H_3818217702141947_
  typedef cutils_cutt_Tester cutils_Tester;
  #undef cutils_try
  #undef cutils_report
  #define cutils_try(...) cutils_cutt_try(__VA_ARGS__)
  #define cutils_report(...) cutils_cutt_report(__VA_ARGS__)
#else
  /* HACK: Define type to make _Generic() work */
  typedef struct {} cutils_cutt_Tester;
#endif /* _C_UNIT_TEST_TOOLS_H_3818217702141947_ */

#endif /* CUTILS_NAMESPACE */

/*----------------------------------------------------------------------------*/
/* TODO: Figure out how to dispatch to a macro (for default values) inside
         a _Generic macro dispatcher...

         #define new(...) cutils_carg_vargs(__VA_ARGS__)(4)(__VA_ARGS__, \
             cutils_carg_zero, __cutils_generic_new3, __cutils_generic_new3, \
             __cutils_generic_new1)(__VA_ARGS__)  */

/*----------------------------------------------------------------------------*/
#undef __cutils_generic_new
#define __cutils_generic_new(object, ...) _Generic((object),\
    cutils_cdar_DynamicArray_char**:cutils_cdar_DynamicArray_char_new,\
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
    cutils_cdar_DynamicArray_void_ptr**:cutils_cdar_DynamicArray_void_ptr_new,\
    cutils_cutt_Tester**: cutils_cutt_new)\
    (object, ## __VA_ARGS__)
/*----------------------------------------------------------------------------*/
#undef __cutils_generic_data
#define __cutils_generic_data(object, ...) _Generic((object),\
    cutils_cdar_DynamicArray_char*:cutils_cdar_DynamicArray_char_data,\
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
    cutils_cdar_DynamicArray_ptrdiff_t*:cutils_cdar_DynamicArray_ptrdiff_t_data,\
    cutils_cdar_DynamicArray_void_ptr*:cutils_cdar_DynamicArray_void_ptr_data)\
    (object, ## __VA_ARGS__)
/*----------------------------------------------------------------------------*/
#undef __cutils_generic_raw
#define __cutils_generic_raw(object, ...) _Generic((object),\
    cutils_cdar_DynamicArray_char*:cutils_cdar_DynamicArray_char_raw,\
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
    cutils_cdar_DynamicArray_ptrdiff_t*:cutils_cdar_DynamicArray_ptrdiff_t_raw,\
    cutils_cdar_DynamicArray_void_ptr*:cutils_cdar_DynamicArray_void_ptr_raw)\
    (object, ## __VA_ARGS__)
/*----------------------------------------------------------------------------*/
#undef __cutils_generic_append
#define __cutils_generic_append(object, ...) _Generic((object),\
    cutils_cdar_DynamicArray_char*:cutils_cdar_DynamicArray_char_append,\
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
    cutils_cdar_DynamicArray_void_ptr*:cutils_cdar_DynamicArray_void_ptr_append)\
    (object, ## __VA_ARGS__)
/*----------------------------------------------------------------------------*/
#undef __cutils_generic_push
#define __cutils_generic_push(object, ...) _Generic((object),\
    cutils_cdar_DynamicArray_char*:cutils_cdar_DynamicArray_char_push,\
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
    cutils_cdar_DynamicArray_void_ptr*:cutils_cdar_DynamicArray_void_ptr_push)\
    (object, ## __VA_ARGS__)
/*----------------------------------------------------------------------------*/
#undef __cutils_generic_set
#define __cutils_generic_set(object, ...) _Generic((object),\
    cutils_cdar_DynamicArray_char*:cutils_cdar_DynamicArray_char_set,\
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
    cutils_cdar_DynamicArray_void_ptr*:cutils_cdar_DynamicArray_void_ptr_set)\
    (object, ## __VA_ARGS__)
/*----------------------------------------------------------------------------*/
#undef __cutils_generic_pop
#define __cutils_generic_pop(object, ...) _Generic((object),\
    cutils_cdar_DynamicArray_char*:cutils_cdar_DynamicArray_char_pop,\
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
    cutils_cdar_DynamicArray_void_ptr*:cutils_cdar_DynamicArray_void_ptr_pop)\
    (object, ## __VA_ARGS__)
/*----------------------------------------------------------------------------*/
#undef __cutils_generic_sub
#define __cutils_generic_sub(object, ...) _Generic((object),\
    cutils_cdar_DynamicArray_char*:cutils_cdar_DynamicArray_char_sub,\
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
    cutils_cdar_DynamicArray_void_ptr*:cutils_cdar_DynamicArray_void_ptr_sub)\
    (object, ## __VA_ARGS__)
/*----------------------------------------------------------------------------*/
#undef __cutils_generic_get
#define __cutils_generic_get(object, ...) _Generic((object),\
    cutils_cdar_DynamicArray_char*:cutils_cdar_DynamicArray_char_get,\
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
    cutils_cdar_DynamicArray_void_ptr*:cutils_cdar_DynamicArray_void_ptr_get)\
    (object, ## __VA_ARGS__)
/*----------------------------------------------------------------------------*/
#undef __cutils_generic_find
#define __cutils_generic_find(object, ...) _Generic((object),\
    cutils_cdar_DynamicArray_char*:cutils_cdar_DynamicArray_char_find,\
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
    cutils_cdar_DynamicArray_void_ptr*:cutils_cdar_DynamicArray_void_ptr_find)\
    (object, ## __VA_ARGS__)
/*----------------------------------------------------------------------------*/
#undef __cutils_generic_findall
#define __cutils_generic_findall(object, ...) _Generic((object),\
    cutils_cdar_DynamicArray_char*:cutils_cdar_DynamicArray_char_findall,\
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
    cutils_cdar_DynamicArray_void_ptr*:cutils_cdar_DynamicArray_void_ptr_findall)\
    (object, ## __VA_ARGS__)
/*----------------------------------------------------------------------------*/
#undef __cutils_generic_del
#define __cutils_generic_del(object, ...) _Generic((object),\
    cutils_cdar_DynamicArray_char*:cutils_cdar_DynamicArray_char_del,\
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
    cutils_cdar_DynamicArray_void_ptr*:cutils_cdar_DynamicArray_void_ptr_del,\
    cutils_cutt_Tester*: cutils_cutt_del)\
    (object, ## __VA_ARGS__)
/*----------------------------------------------------------------------------*/
#undef __cutils_generic_len
#define __cutils_generic_len(object, ...) _Generic((object),\
    cutils_cdar_DynamicArray_char*:cutils_cdar_DynamicArray_char_len,\
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
    cutils_cdar_DynamicArray_void_ptr*:cutils_cdar_DynamicArray_void_ptr_len)\
    (object, ## __VA_ARGS__)
/*----------------------------------------------------------------------------*/
#undef __cutils_generic_size
#define __cutils_generic_size(object, ...) _Generic((object),\
    cutils_cdar_DynamicArray_char*:cutils_cdar_DynamicArray_char_size,\
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
    cutils_cdar_DynamicArray_ptrdiff_t*:cutils_cdar_DynamicArray_ptrdiff_t_size,\
    cutils_cdar_DynamicArray_void_ptr*:cutils_cdar_DynamicArray_void_ptr_size)\
    (object, ## __VA_ARGS__)
/*----------------------------------------------------------------------------*/
#undef __cutils_generic_resize
#define __cutils_generic_resize(object, ...) _Generic((object),\
    cutils_cdar_DynamicArray_char*:cutils_cdar_DynamicArray_char_resize,\
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
    cutils_cdar_DynamicArray_ptrdiff_t*:cutils_cdar_DynamicArray_ptrdiff_t_resize,\
    cutils_cdar_DynamicArray_void_ptr*:cutils_cdar_DynamicArray_void_ptr_resize)\
    (object, ## __VA_ARGS__)
/*----------------------------------------------------------------------------*/
#undef __cutils_generic_swap
#define __cutils_generic_swap(object, ...) _Generic((object),\
    cutils_cdar_DynamicArray_char*:cutils_cdar_DynamicArray_char_swap,\
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
    cutils_cdar_DynamicArray_void_ptr*:cutils_cdar_DynamicArray_void_ptr_swap)\
    (object, ## __VA_ARGS__)
/*----------------------------------------------------------------------------*/
#undef __cutils_generic_reverse
#define __cutils_generic_reverse(object, ...) _Generic((object),\
    cutils_cdar_DynamicArray_char*:cutils_cdar_DynamicArray_char_reverse,\
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
    cutils_cdar_DynamicArray_void_ptr*:cutils_cdar_DynamicArray_void_ptr_reverse)\
    (object, ## __VA_ARGS__)
/*----------------------------------------------------------------------------*/
#undef __cutils_generic_pull
#define __cutils_generic_pull(object, ...) _Generic((object),\
    cutils_cdar_DynamicArray_char*:cutils_cdar_DynamicArray_char_pull,\
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
    cutils_cdar_DynamicArray_void_ptr*:cutils_cdar_DynamicArray_void_ptr_pull)\
    (object, ## __VA_ARGS__)
/*----------------------------------------------------------------------------*/
#undef __cutils_generic_truncate
#define __cutils_generic_truncate(object, ...) _Generic((object),\
    cutils_cdar_DynamicArray_char*:cutils_cdar_DynamicArray_char_truncate,\
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
    cutils_cdar_DynamicArray_void_ptr*:cutils_cdar_DynamicArray_void_ptr_truncate)\
    (object, ## __VA_ARGS__)
/*----------------------------------------------------------------------------*/
#undef __cutils_generic_clear
#define __cutils_generic_clear(object, ...) _Generic((object),\
    cutils_cdar_DynamicArray_char*:cutils_cdar_DynamicArray_char_clear,\
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
    cutils_cdar_DynamicArray_void_ptr*:cutils_cdar_DynamicArray_void_ptr_clear)\
    (object, ## __VA_ARGS__)

#endif /* _C_APPLICATION_PROGRAMMING_INTERFACE_H_27277619327951796_ */
