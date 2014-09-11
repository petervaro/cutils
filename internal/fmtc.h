/* INFO ************************************************************************
**                                                                            **
**                                   cutils                                   **
**                                   ======                                   **
**                                                                            **
**                     Modern and Lightweight C Utilities                     **
**                       Version: 0.8.90.563 (20140820)                       **
**                                                                            **
**                           File: internal/fmtc.h                            **
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

#ifndef _FORMAT_CHAR_H_9923035070629016_
#define _FORMAT_CHAR_H_9923035070629016_

#include <stdlib.h>   /* size_t */

static inline void
cutils_fmtc_repr(char *buffer,
                 size_t buffer_size,
                 const char *string,
                 size_t string_size)
{
    #undef SPECIAL_CHARS
    #undef ESCAPED_CHARS
    #define SPECIAL_CHARS(...) \
        {'\\',   '\n' , '\t' , '\r' , '\v' , '\a' , '\b' , '\f' , ## __VA_ARGS__}
    #define ESCAPED_CHARS(...) \
        {"\\\\", "\\n", "\\t", "\\r", "\\v", "\\a", "\\b", "\\f", ## __VA_ARGS__}

    static const char  special_chr[] = SPECIAL_CHARS('\'' , '\0');
    static const char *escaped_chr[] = ESCAPED_CHARS("\\'", "\\0");
    static const char  special_str[] = SPECIAL_CHARS('"');
    static const char *escaped_str[] = ESCAPED_CHARS("\\\"");
    static const size_t spec_chr_len = sizeof special_chr;
    static const size_t spec_str_len = sizeof special_str;

    /* If buffer is smaller than an escaped character representation,
       the quotes and a null character at the end */
    if (buffer_size < 5)
        return;

    char chr;
    size_t i, j;
    /* If string is a pointer to a single char */
    if (string_size == 1)
    {
        j = 0;
        chr = *string;
        buffer[j++] = '\'';
        for (i=0; i<spec_chr_len; i++)
            /* If character is a special character */
            if (chr == special_chr[i])
            {
                buffer[j++] = escaped_chr[i][0];
                buffer[j++] = escaped_chr[i][1];
                goto Close_Quote;
            }
        /* If character is a regular character */
        buffer[j++] = chr;
        Close_Quote:
            buffer[j++] = '\'';
            buffer[j] ='\0';
    }
    /* If string is a pointer to a character sequence */
    else
    {
        size_t k = 0;
        buffer[k++] = '"';
        /* If k is smaller than buffer_size - (escaped character representation,
           closing quote, and null character at the end) */
        for (i=0; i<string_size && k<(buffer_size - 4); i++)
        {
            chr = string[i];
            for (j=0; j<spec_str_len; j++)
                /* If character is a special character */
                if (chr == special_str[j])
                {
                    buffer[k++] = escaped_str[j][0];
                    buffer[k++] = escaped_str[j][1];
                    goto Next_Char;
                }
            /* If character is a regular character */
            buffer[k++] = chr;
            Next_Char:;
        }
        buffer[k++] = '"';
        buffer[k] = '\0';
    }
}

#endif /* _FORMAT_CHAR_H_9923035070629016_ */
