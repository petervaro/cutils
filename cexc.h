
// INFO //
// INFO //

#ifndef _C_EXCEPTIONS_H_
#define _C_EXCEPTIONS_H_

#include <stdio.h>   // size_t, fprintf(), stderr
#include <stdlib.h>  // malloc(), realloc(), free()
#include <string.h>  // strncpy()

/*
MACRO FLAGS:

    CEXC_OFF:
        If defined all the exception handler functions will be removed.

    CEXC_LOG:
        If defined all the catch() functions will be removed and the exception
        will be written by the raise() functions directly to the file pointer
        specified at the call of the start_exception_handling()
*/

#ifdef CEXC_OFF
  #define start_exception_handling(out)
  #define stop_exception_handling()
  #define raise(msg, len)
  #define catch()
  #define set_exception_handling_pointer(ptr)
  #define set_exception_handling_custom_raise(func)
  #define set_exception_handling_custom_catch(func)
  #define craise(msg, len)
  #define ccatch()
#else
  #undef  CEXC_MSG_LEN
  #define CEXC_MSG_LEN 9
  #undef  CEXC_PREFIX
  #define CEXC_PREFIX "EXCEPTION: "
  #undef  CEXC_NO_ERR
  #define CEXC_NO_ERR "NO ERROR"
  #undef  CEXC_ALLOC_ERR
  #define CEXC_ALLOC_ERR "INTERNAL"

/*----------------------------------------------------------------------------*/
typedef struct
{
    // Essential values
    char *buffer;
    size_t chars;
    size_t error;
    FILE *output;

    // Custom values
    void *custom;
    void (*raisecb)(void*);
    void (*catchcb)(void*);

} ExceptionHandler;


/*----------------------------------------------------------------------------*/
#ifdef _CEXC_EXCEPTION_HANDLER_STRUCT_
  extern ExceptionHandler *__CEXC_Exception_Handler__;
#else
  #define _CEXC_EXCEPTION_HANDLER_STRUCT_
  ExceptionHandler *__CEXC_Exception_Handler__;
#endif // _CEXC_EXCEPTION_HANDLER_STRUCT_

/*----------------------------------------------------------------------------*/
static inline void __cexc_handler_init_cb__(void *ptr) { return; }

/*----------------------------------------------------------------------------*/
static inline void
start_exception_handling(FILE *output)
{
    // Set essential values
    __CEXC_Exception_Handler__ = malloc(sizeof(ExceptionHandler));
    if (!__CEXC_Exception_Handler__)
    {
        fprintf(stderr, "Failed to allocate memory for ExceptionHandler\n");
        return;
    }
    __CEXC_Exception_Handler__->buffer = malloc(CEXC_MSG_LEN * sizeof(char));
    if (!__CEXC_Exception_Handler__->buffer)
    {
        fprintf(stderr, "Failed to allocate memory for"
                        "ExceptionHandler's buffer\n");
        return;
    }
    __CEXC_Exception_Handler__->chars  = CEXC_MSG_LEN;
    strncpy(__CEXC_Exception_Handler__->buffer, CEXC_NO_ERR, CEXC_MSG_LEN);
    __CEXC_Exception_Handler__->output = output;
    __CEXC_Exception_Handler__->error = 0;

    //Set custom values
    __CEXC_Exception_Handler__->custom = (void *)NULL;
    __CEXC_Exception_Handler__->raisecb = __cexc_handler_init_cb__;
    __CEXC_Exception_Handler__->catchcb = __cexc_handler_init_cb__;
}


/*----------------------------------------------------------------------------*/
static inline void
stop_exception_handling(void)
{
    free(__CEXC_Exception_Handler__->buffer);
    free(__CEXC_Exception_Handler__);
}


/*----------------------------------------------------------------------------*/
static inline void
set_exception_handling_pointer(void *pointer)
{
    __CEXC_Exception_Handler__->custom = pointer;
}


/*----------------------------------------------------------------------------*/
static inline void
set_exception_handling_custom_catch(void (*callback)(void*))
{
    __CEXC_Exception_Handler__->catchcb = callback;
}


/*----------------------------------------------------------------------------*/
static inline void
set_exception_handling_custom_raise(void (*callback)(void*))
{
    __CEXC_Exception_Handler__->raisecb = callback;
}


/*----------------------------------------------------------------------------*/
// TODO: OPTION 1: catch returns 1 if error, else 0, CON: if func removed by macro?
//       OPTION 2: use ccatch for that? (the callback does what the
//                 `if (catch())` would have done)
#ifdef CEXC_LOG
  #define catch()
#else
static inline void
catch(void)
{
    // Write buffer data to output
    fprintf(__CEXC_Exception_Handler__->output,
            CEXC_PREFIX "%s\n",
            __CEXC_Exception_Handler__->buffer);
    // Clear buffer
    strncpy(__CEXC_Exception_Handler__->buffer, CEXC_NO_ERR, CEXC_MSG_LEN);
    __CEXC_Exception_Handler__->error = 0;
}
#endif // CEXC_LOG


/*----------------------------------------------------------------------------*/
static inline void
raise(const char *message,
      size_t length)
{
#ifdef CEXC_LOG
    fprintf(__CEXC_Exception_Handler__->output, CEXC_PREFIX "%s\n", message);
#else
    /* Raise new error only, if no previous error raised */
    if (__CEXC_Exception_Handler__->error) return;
    /* Switch error flag */
    __CEXC_Exception_Handler__->error = 1;
    // Check if buffer has enough size
    if (length > __CEXC_Exception_Handler__->chars)
    {
        // If buffer is too small resize it
        char *buffer = realloc(__CEXC_Exception_Handler__->buffer,
                               2 * length * sizeof(char));
        if (!buffer)
        {
            strncpy(__CEXC_Exception_Handler__->buffer,
                    CEXC_ALLOC_ERR, CEXC_MSG_LEN);
            return;
        }
        __CEXC_Exception_Handler__->buffer = buffer;
        // Update size information
        __CEXC_Exception_Handler__->chars = length;
    }
    // Set exception buffer
    strncpy(__CEXC_Exception_Handler__->buffer, message, length);
    // Stop it
    if (length < __CEXC_Exception_Handler__->chars)
        __CEXC_Exception_Handler__->buffer[length] = '\0';
#endif // CEXC_LOG
}

/*----------------------------------------------------------------------------*/
static inline void
ccatch(void)
{
    catch();
    __CEXC_Exception_Handler__->catchcb(__CEXC_Exception_Handler__->custom);
}


/*----------------------------------------------------------------------------*/
static inline void
craise(const char *message,
       size_t length)
{
    raise(message, length);
    __CEXC_Exception_Handler__->raisecb(__CEXC_Exception_Handler__->custom);
}

  #undef CEXC_MSG_LEN
  #undef CEXC_PREFIX
  #undef CEXC_NO_ERR
  #undef CEXC_ALLOC_ERR
#endif // CEXC_OFF
#endif // _C_EXCEPTIONS_H_
