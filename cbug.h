
#ifndef _CBUG_H_
#define _CBUG_H_

#ifndef CBUG_OFF

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

static inline void
__cbug_debug(const char *file_name,
             unsigned int line_number,
             const char *function_name)
{
    static unsigned int counter = 0;
    fprintf(stderr, "%03u\tFile: '%s', line: %d, function: '%s'\n",
            counter++, file_name, line_number, function_name);
}

// Generic debug information
#define debug() (__cbug_debug(__FILE__, __LINE__, __func__))

// Generic debug information + simple string
#define debugs(str) \
    do { debug(); fprintf(stderr, "\t\t" #str "\n\n"); } while(0)

// Generic debug information + formatted string
#define debugf(fmt, ...) \
    do { debug(); fprintf(stderr, "\t\t" #fmt "\n\n", __VA_ARGS__); } while (0)

#else
  #define debug()
  #define debugs(...)
  #define debugf(...)
#endif  /* CBUG_OFF */
#endif  /* _CBUG_H_ */
