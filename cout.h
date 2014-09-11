/* INFO ************************************************************************
**                                                                            **
**                                   cutils                                   **
**                                   ======                                   **
**                                                                            **
**                     Modern and Lightweight C Utilities                     **
**                       Version: 0.8.95.959 (20140902)                       **
**                                                                            **
**                                File: cout.h                                **
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

#ifndef _C_OUTPUT_H_8918146128868265_
#define _C_OUTPUT_H_8918146128868265_

/* Include standard headers */
#include <stdbool.h>  /* bool */

/*----------------------------------------------------------------------------*/
extern void
cutils_cout_char_print(char character);
/*----------------------------------------------------------------------------*/
extern void
cutils_cout_signed_char_print(signed char character);
/*----------------------------------------------------------------------------*/
extern void
cutils_cout_unsigned_char_print(unsigned char character);
/*----------------------------------------------------------------------------*/
extern void
cutils_cout_char_ptr_print(char *string);
/*----------------------------------------------------------------------------*/
extern void
cutils_cout_short_print(short number);
/*----------------------------------------------------------------------------*/
extern void
cutils_cout_unsigned_short_print(unsigned short number);
/*----------------------------------------------------------------------------*/
extern void
cutils_cout_int_print(int number);
/*----------------------------------------------------------------------------*/
extern void
cutils_cout_unsigned_int_print(unsigned int number);
/*----------------------------------------------------------------------------*/
extern void
cutils_cout_long_print(long number);
/*----------------------------------------------------------------------------*/
extern void
cutils_cout_unsigned_long_print(unsigned long number);
/*----------------------------------------------------------------------------*/
extern void
cutils_cout_long_long_print(long long number);
/*----------------------------------------------------------------------------*/
extern void
cutils_cout_unsigned_long_long_print(unsigned long long number);
/*----------------------------------------------------------------------------*/
extern void
cutils_cout_float_print(float number);
/*----------------------------------------------------------------------------*/
extern void
cutils_cout_double_print(double number);
/*----------------------------------------------------------------------------*/
extern void
cutils_cout_long_double_print(long double number);
/*----------------------------------------------------------------------------*/
extern void
cutils_cout_bool_print(bool boolean);
/*----------------------------------------------------------------------------*/
extern void
cutils_cout_void_ptr_print(void *pointer);

#endif /* _C_OUTPUT_H_8918146128868265_ */
