/* INFO ************************************************************************
**                                                                            **
**                                   cutils                                   **
**                                   ======                                   **
**                                                                            **
**                     Modern and Lightweight C Utilities                     **
**                       Version: 0.8.90.488 (20140819)                       **
**                                                                            **
**                           File: internal/defs.h                            **
**                                                                            **
**           Designed and written by Peter Varo. Copyright (c) 2014           **
**             License agreement is provided in the LICENSE file              **
**                 For more info visit: http://www.cutils.org                 **
**                                                                            **
************************************************************************ INFO */

#ifndef _DEFINITIONS_H_9146952840353706_
#define _DEFINITIONS_H_9146952840353706_

/*----------------------------------------------------------------------------*/
/* Pointer representation */
#undef __pointer_repr
#undef REPRESENTATION_OF_NULL_POINTERS
#undef REPRESENTATION_OF_REAL_POINTERS

#define __pointer_repr(fmt) "<pointer to " fmt ">"
#define REPRESENTATION_OF_NULL_POINTERS __pointer_repr("NULL")
#define REPRESENTATION_OF_REAL_POINTERS __pointer_repr("%p")

/*----------------------------------------------------------------------------*/
/* Exception messages */
#undef __format_exception
#undef EXCEPTION_MESSAGE_EMPTY
#undef EXCEPTION_MESSAGE_OVERLAP
#undef EXCEPTION_MESSAGE_ALLOC_FAIL
#undef EXCEPTION_MESSAGE_NULL_POINTER
#undef EXCEPTION_MESSAGE_ARGUMENT_NULL
#undef EXCEPTION_MESSAGE_ARGUMENT_OUTOF

#define __format_exception(type, func, note) type ", " func ": " note
#define EXCEPTION_MESSAGE_ARGUMENT_NULL(type, func, idx, arg) \
        __format_exception(type, func, idx " argument '" #arg "' is NULL")
#define EXCEPTION_MESSAGE_ARGUMENT_OUTOF(type, func, idx, arg) \
        __format_exception(type, func, idx " argument '" #arg "' is out of range")
#define EXCEPTION_MESSAGE_NULL_POINTER(type, func) \
        __format_exception(type, func, "object is a " REPRESENTATION_OF_NULL_POINTERS)
#define EXCEPTION_MESSAGE_EMPTY(type, func) \
        __format_exception(type, func, "object is empty")
#define EXCEPTION_MESSAGE_ALLOC_FAIL(type, func) \
        __format_exception(type, func, "internal allocation failed")
#define EXCEPTION_MESSAGE_REALLOC_FAIL(type, func) \
        __format_exception(type, func, "internal reallocation failed")
#define EXCEPTION_MESSAGE_OVERLAP(type, func) \
        __format_exception(type, func, "blocks are overlapping")

#endif /* _DEFINITIONS_H_9146952840353706_ */
