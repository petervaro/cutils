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
