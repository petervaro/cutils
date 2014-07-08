/* INFO ************************************************************************
**                                                                            **
**                                   cutils                                   **
**                                   ======                                   **
**                                                                            **
**                     Modern and Lightweight C Utilities                     **
**                       Version: 0.8.72.222 (20140708)                       **
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

/*----------------------------------------------------------------------------*/
#ifndef CUTILS_NAMESPACE /* use bare token names */

#undef new
#undef del
#define new(...) __cutils_generic_new(__VA_ARGS__)
#define del(...) __cutils_generic_del(__VA_ARGS__)

#ifdef _C_ARGUMENTS_19836769466709525_
  #undef zero
  #undef vargs
  #define zero(...) cutils_carg_zero(__VA_ARGS__)
  #define vargs(...) cutils_carg_vargs(__VA_ARGS__)
#endif /* _C_ARGUMENTS_19836769466709525_ */

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
#else /* Define type to make _Generic() work */
  typedef struct {} cutils_cutt_Tester;
#endif /* _C_UNIT_TEST_TOOLS_H_3818217702141947_ */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#else /* use prefixed token names */

#undef cutils_new
#undef cutils_del
#define cutils_new(...) __cutils_generic_new(__VA_ARGS__)
#define cutils_del(...) __cutils_generic_del(__VA_ARGS__)

#ifdef _C_ARGUMENTS_19836769466709525_
  #undef cutils_zero
  #undef cutils_vargs
  #define cutils_zero(...) cutils_carg_zero(__VA_ARGS__)
  #define cutils_vargs(...) cutils_carg_vargs(__VA_ARGS__)
#endif /* _C_ARGUMENTS_19836769466709525_ */

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
#else /* Define type to make _Generic() work */
  typedef struct {} cutils_cutt_Tester;
#endif /* _C_UNIT_TEST_TOOLS_H_3818217702141947_ */

#endif /* CUTILS_NAMESPACE */



/*----------------------------------------------------------------------------*/
#undef __cutils_generic_new
#define __cutils_generic_new(object, ...) _Generic((object), \
    cutils_cutt_Tester **: cutils_cutt_new)(object, ## __VA_ARGS__)

/*----------------------------------------------------------------------------*/
#undef __cutils_generic_del
#define __cutils_generic_del(object, ...) _Generic((object), \
    cutils_cutt_Tester *: cutils_cutt_del)(object, ## __VA_ARGS__)

#endif /* _C_APPLICATION_PROGRAMMING_INTERFACE_H_27277619327951796_ */
