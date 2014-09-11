/* INFO ************************************************************************
**                                                                            **
**                                   cutils                                   **
**                                   ======                                   **
**                                                                            **
**                     Modern and Lightweight C Utilities                     **
**                       Version: 0.8.95.968 (20140904)                       **
**                                                                            **
**                                File: cout.c                                **
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

/* Include standard headers */
#include <stdio.h>    /* stdout, fprintf(), snprintf() */
#include <stdbool.h>  /* bool */

/* Include cutils headers */
#include "internal/fmtc.h"

/* TODO: - add arrays (eg. char[]) => _Generic sees char* and char[] differently
         - add pointers (eg. int*)
         - add qualifiers (eg. const void*) */

/*----------------------------------------------------------------------------*/
void
cutils_cout_char_print(char character)
{
    #define BUFFER_SIZE 8
    char buffer[BUFFER_SIZE];
    cutils_fmtc_repr(buffer, BUFFER_SIZE, &character, 1);
    fprintf(stdout, "%s\n", buffer);
}


/*----------------------------------------------------------------------------*/
void
cutils_cout_signed_char_print(signed char character)
{
    fprintf(stdout, "%d\n", character);
}


/*----------------------------------------------------------------------------*/
void
cutils_cout_unsigned_char_print(unsigned char character)
{
    fprintf(stdout, "%u\n", character);
}


/*----------------------------------------------------------------------------*/
void
cutils_cout_char_ptr_print(char *string)
{
    size_t string_size = snprintf(NULL, 0, "%s", string);
    size_t buffer_size = string_size*2;
    char *buffer = malloc(buffer_size);
    cutils_fmtc_repr(buffer, buffer_size, string, string_size);
    fprintf(stdout, "%s\n", buffer);
}


/*----------------------------------------------------------------------------*/
void
cutils_cout_short_print(short number)
{
    fprintf(stdout, "%hd\n", number);
}


/*----------------------------------------------------------------------------*/
void
cutils_cout_unsigned_short_print(unsigned short number)
{
    fprintf(stdout, "%hu\n", number);
}


/*----------------------------------------------------------------------------*/
void
cutils_cout_int_print(int number)
{
    fprintf(stdout, "%d\n", number);
}


/*----------------------------------------------------------------------------*/
void
cutils_cout_unsigned_int_print(unsigned int number)
{
    fprintf(stdout, "%uu\n", number);
}


/*----------------------------------------------------------------------------*/
void
cutils_cout_long_print(long number)
{
    fprintf(stdout, "%ldl\n", number);
}


/*----------------------------------------------------------------------------*/
void
cutils_cout_unsigned_long_print(unsigned long number)
{
    fprintf(stdout, "%luul\n", number);
}


/*----------------------------------------------------------------------------*/
void
cutils_cout_long_long_print(long long number)
{
    fprintf(stdout, "%lldll\n", number);
}


/*----------------------------------------------------------------------------*/
void
cutils_cout_unsigned_long_long_print(unsigned long long number)
{
    fprintf(stdout, "%lluull\n", number);
}


/*----------------------------------------------------------------------------*/
void
cutils_cout_float_print(float number)
{
    fprintf(stdout, "%ff\n", number);
}


/*----------------------------------------------------------------------------*/
void
cutils_cout_double_print(double number)
{
    fprintf(stdout, "%lf\n", number);
}


/*----------------------------------------------------------------------------*/
void
cutils_cout_long_double_print(long double number)
{
    fprintf(stdout, "%Lf\n", number);
}


/*----------------------------------------------------------------------------*/
void
cutils_cout_bool_print(bool boolean)
{
    fprintf(stdout, "%s\n", boolean ? "true" : "false");
}


/*----------------------------------------------------------------------------*/
void
cutils_cout_void_ptr_print(void *pointer)
{
    fprintf(stdout, "<pointer to %p>\n", pointer);
}
