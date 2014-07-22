/* INFO ************************************************************************
**                                                                            **
**                                   cutils                                   **
**                                   ======                                   **
**                                                                            **
**                     Modern and Lightweight C Utilities                     **
**                       Version: 0.8.80.068 (20140721)                       **
**                                                                            **
**                           File: internal/fmtc.h                            **
**                                                                            **
**           Designed and written by Peter Varo. Copyright (c) 2014           **
**             License agreement is provided in the LICENSE file              **
**                 For more info visit: http://www.cutils.org                 **
**                                                                            **
************************************************************************ INFO */

#ifndef _FORMAT_CHAR_H_9923035070629016_
#define _FORMAT_CHAR_H_9923035070629016_

#include <stdlib.h>   /* size_t */

static inline void
cutils_fmtc_repr(char *buffer,
                 size_t buffer_size,
                 char *string,
                 size_t string_size)
{
    #undef SPECIAL_CHARS
    #undef ESCAPED_CHARS
    #define SPECIAL_CHARS(S) {S, '\n' , '\t' , '\r' , '\v' , '\a' , '\b' , '\f' }
    #define ESCAPED_CHARS(S) {S, "\\n", "\\t", "\\r", "\\v", "\\a", "\\b", "\\f"}

    static const char  special_chr[] = SPECIAL_CHARS('\'');
    static const char *escaped_chr[] = ESCAPED_CHARS("\\'");
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
