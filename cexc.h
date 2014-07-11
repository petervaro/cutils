/* INFO ************************************************************************
**                                                                            **
**                                   cutils                                   **
**                                   ======                                   **
**                                                                            **
**                     Modern and Lightweight C Utilities                     **
**                       Version: 0.8.72.365 (20140711)                       **
**                                                                            **
**                                File: cexc.h                                **
**                                                                            **
**           Designed and written by Peter Varo. Copyright (c) 2014           **
**             License agreement is provided in the LICENSE file              **
**                 For more info visit: http://www.cutils.org                 **
**                                                                            **
************************************************************************ INFO */

#ifndef _C_EXCEPTIONS_H_5362957038900146_
#define _C_EXCEPTIONS_H_5362957038900146_

#include <stdio.h>    /* size_t, stdout, stderr, fprintf() */
#include <stdlib.h>   /* malloc(), realloc(), free() */
#include <string.h>   /* strncpy() */
#include <stdbool.h>  /* bool, true, false */

#undef cutils_cexc_start_exception_handling
#undef cutils_cexc_stop_exception_handling
#undef cutils_cexc_set_exception_handling_pointer
#undef cutils_cexc_set_exception_handling_custom_raise
#undef cutils_cexc_set_exception_handling_custom_catch
#undef cutils_cexc_raise
#undef cutils_cexc_catch
#undef cutils_cexc_craise
#undef cutils_cexc_ccatch

#ifdef CEXC_OFF
  #define cutils_cexc_start_exception_handling(out)
  #define cutils_cexc_stop_exception_handling()
  #define cutils_cexc_raise(msg, len)
  #define cutils_cexc_catch()
  #define cutils_cexc_set_exception_handling_pointer(ptr)
  #define cutils_cexc_set_exception_handling_custom_raise(func)
  #define cutils_cexc_set_exception_handling_custom_catch(func)
  #define cutils_cexc_craise(msg, len)
  #define cutils_cexc_ccatch()
#else
  #undef __CEXC_PREFIX
  #undef __CEXC_NO_ERROR
  #undef __CEXC_INTERNAL
  #define __CEXC_PREFIX "EXCEPTION: "
  #define __CEXC_NO_ERROR "NO ERROR"
  #define __CEXC_INTERNAL "INTERNAL"

/*----------------------------------------------------------------------------*/
typedef struct
{
    // Essential values
    char *buffer;
    size_t chars;
    bool error;
    FILE *output;

    // Custom values
    void *custom;
    void (*raisecb)(void*);
    void (*catchcb)(void*);

} __cexc_ExceptionHandler;


#ifdef CEXC_SET
/*----------------------------------------------------------------------------*/
static inline void __cexc_callback(void *ptr){return;}
static char __CUTILS_CEXC_EXCEPTION_HANDLER_BUFFER[] = __CEXC_NO_ERROR;

/*----------------------------------------------------------------------------*/
__cexc_ExceptionHandler __CUTILS_CEXC_EXCEPTION_HANDLER = {
    .chars   = sizeof __CEXC_NO_ERROR,
    .error   = false,
    .buffer  = __CUTILS_CEXC_EXCEPTION_HANDLER_BUFFER,
    .custom  = (void *)NULL,
    .raisecb = __cexc_callback,
    .catchcb = __cexc_callback
};
#else
extern __cexc_ExceptionHandler __CUTILS_CEXC_EXCEPTION_HANDLER;
#endif /* CEXC_SET */


/*----------------------------------------------------------------------------*/
static inline void
cutils_cexc_start_exception_handling(FILE *output)
{
    __CUTILS_CEXC_EXCEPTION_HANDLER.output = output;
    /* Try to dynamically allocate space for buffer */
    char *buffer = malloc(sizeof __CEXC_NO_ERROR);
    if (!buffer)
    {
        __CUTILS_CEXC_EXCEPTION_HANDLER.error  = true;
        __CUTILS_CEXC_EXCEPTION_HANDLER.buffer = __CEXC_INTERNAL;
        return;
    }
    /* Reset error message and set newly allocated space */
    strncpy(buffer, __CEXC_NO_ERROR, sizeof __CEXC_NO_ERROR);
    __CUTILS_CEXC_EXCEPTION_HANDLER.buffer = buffer;
}


/*----------------------------------------------------------------------------*/
static inline void
cutils_cexc_stop_exception_handling(void)
{
    /* If the initialisation was successful */
    if (strncmp(__CUTILS_CEXC_EXCEPTION_HANDLER.buffer,
                __CEXC_INTERNAL,
                sizeof __CEXC_INTERNAL))
        free(__CUTILS_CEXC_EXCEPTION_HANDLER.buffer);
}


/*----------------------------------------------------------------------------*/
static inline void
cutils_cesc_set_exception_handling_pointer(void *pointer)
{
    __CUTILS_CEXC_EXCEPTION_HANDLER.custom = pointer;
}


/*----------------------------------------------------------------------------*/
static inline void
cutils_cexc_set_exception_handling_custom_catch(void (*callback)(void*))
{
    __CUTILS_CEXC_EXCEPTION_HANDLER.catchcb = callback;
}


/*----------------------------------------------------------------------------*/
static inline void
cutils_cexc_set_exception_handling_custom_raise(void (*callback)(void*))
{
    __CUTILS_CEXC_EXCEPTION_HANDLER.raisecb = callback;
}


/*----------------------------------------------------------------------------*/
/* TODO: OPTION 1: catch returns 1 if error, else 0, CON: if func removed by macro?
         OPTION 2: use ccatch for that? (the callback does what the
                   `if (catch())` would have done) */
#ifdef CEXC_LOG
  #define cutils_cexc_catch()
#else
static inline void
cutils_cexc_catch(void)
{
    /* Write buffer data to output */
    fprintf(__CUTILS_CEXC_EXCEPTION_HANDLER.output,
            __CEXC_PREFIX "%s\n",
            __CUTILS_CEXC_EXCEPTION_HANDLER.buffer);
    /* Clear buffer */
    strncpy(__CUTILS_CEXC_EXCEPTION_HANDLER.buffer,
            __CEXC_NO_ERROR,
            sizeof __CEXC_NO_ERROR);
    __CUTILS_CEXC_EXCEPTION_HANDLER.error = false;
}
#endif /* CEXC_LOG */


/*----------------------------------------------------------------------------*/
static inline void
cutils_cexc_raise(const char *message,
                  size_t length)
{
#ifdef CEXC_LOG
    fprintf(__CUTILS_CEXC_EXCEPTION_HANDLER.output,
            __CEXC_PREFIX "%s\n",
            message);
#else
    /* Raise new error only, if no previous error raised */
    if (__CUTILS_CEXC_EXCEPTION_HANDLER.error) return;
    /* Switch error flag */
    __CUTILS_CEXC_EXCEPTION_HANDLER.error = true;
    /* Check if buffer has enough size */
    if ((length + 1) > __CUTILS_CEXC_EXCEPTION_HANDLER.chars)
    {
        /* If buffer is too small resize it */
        char *buffer = realloc(__CUTILS_CEXC_EXCEPTION_HANDLER.buffer,
                               2 * length * sizeof(char));
        if (!buffer)
        {
            strncpy(__CUTILS_CEXC_EXCEPTION_HANDLER.buffer,
                    __CEXC_INTERNAL, sizeof __CEXC_INTERNAL);
            return;
        }
        /* Update size information and point at new memory block */
        __CUTILS_CEXC_EXCEPTION_HANDLER.chars  = length;
        __CUTILS_CEXC_EXCEPTION_HANDLER.buffer = buffer;
    }
    /* Set exception buffer */
    strncpy(__CUTILS_CEXC_EXCEPTION_HANDLER.buffer, message, length);
    /* Make sure it is null-terminated */
    if (length < __CUTILS_CEXC_EXCEPTION_HANDLER.chars)
        __CUTILS_CEXC_EXCEPTION_HANDLER.buffer[length] = '\0';
#endif /* CEXC_LOG */
}

/*----------------------------------------------------------------------------*/
#ifdef CEXC_LOG
  #define cutils_cexc_ccatch()
#else
static inline void
cutils_cexc_ccatch(void)
{
    cutils_cexc_catch();
    __CUTILS_CEXC_EXCEPTION_HANDLER.catchcb(__CUTILS_CEXC_EXCEPTION_HANDLER.custom);
}
#endif /* CEXC_LOG */

/*----------------------------------------------------------------------------*/
static inline void
cutils_cexc_craise(const char *message,
                   size_t length)
{
    cutils_cexc_raise(message, length);
    __CUTILS_CEXC_EXCEPTION_HANDLER.raisecb(__CUTILS_CEXC_EXCEPTION_HANDLER.custom);
}
#endif /* CEXC_OFF */
#endif /* _C_EXCEPTIONS_H_5362957038900146_ */
