
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
    char *buffer;
    size_t chars;
    FILE *output;

} ExceptionHandler;


/*----------------------------------------------------------------------------*/
#ifdef _CEXC_EXCEPTION_HANDLER_STRUCT_
  extern ExceptionHandler *__CEXC_Exception_Handler__;
#else
  #define _CEXC_EXCEPTION_HANDLER_STRUCT_
  ExceptionHandler *__CEXC_Exception_Handler__;
#endif // _CEXC_EXCEPTION_HANDLER_STRUCT_


/*----------------------------------------------------------------------------*/
static inline void
start_exception_handling(FILE *output)
{
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
}


/*----------------------------------------------------------------------------*/
static inline void
stop_exception_handling(void)
{
    free(__CEXC_Exception_Handler__->buffer);
    free(__CEXC_Exception_Handler__);
}


/*----------------------------------------------------------------------------*/
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
    // Check if buffer has enough size
    if (length > __CEXC_Exception_Handler__->chars)
    {
        // If buffer is too small resize it
        char *buffer = realloc(__CEXC_Exception_Handler__->buffer,
                               length * sizeof(char));
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
  #undef CEXC_MSG_LEN
  #undef CEXC_PREFIX
  #undef CEXC_NO_ERR
  #undef CEXC_ALLOC_ERR
#endif // CEXC_OFF
#endif // _C_EXCEPTIONS_H_
