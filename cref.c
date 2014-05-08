/*
 * C Standard Library Reference
 *
 * Collected and implemented by
 * Peter Varo Copyright (C) 2014
 *
 * Version: 1.0.0
 *
 * Based on Jospeh H. Silverman,
 *          http://www.tutorialspoint.com
 *          http://www.stackoverflow.com
 */

/*----------------------------------------------------------------------------*/
// The macro language

#define
#undef
#ifdef
#ifndef
#if
#elif
#else
#endif


/*----------------------------------------------------------------------------*/
#include <assert.h>

// Makes assert to be ignored if defined before header is included
#define NDEBUG
// If expression is false, writes info and terminate program
void
assert(int expr);


/*----------------------------------------------------------------------------*/
#include <errno.h>

// Global variable error number is readable and writeable
extern int errno;

/*----------------------------------------------------------------------------*/
#include <ctype.h>

/* Character classes
 * -----------------
 * Digits                                                                  [0-9]
 * Hexadecimal digits                                        <Digits> + [A-Fa-f]
 * Lowercase letters                                                       [a-z]
 * Uppercase letters                                                       [A-Z]
 * Letters                             <Lowercase letters> + <Uppercase letters>
 * Alphanumeric characters                                  <Digits> + <Letters>
 * Punctuation characters                     [!"#$%&'()*+,-./:;<=>?@[\]^_`{|}~]
 * Graphical characters     <Alphanumeric characters> + <Punctuation characters>
 * Space characters                                               [\t\n\v\f\r\s]
 * Printable characters              <Graphical characters> + <Space characters>
 * Control characters                                     [\0\a\b\t\n\v\f\r\e^?]
 * Blank characters                                                       [\s\t]
 * Alphabetic characters               <Lowercase letters> + <Uppercase letters>
 */

// Checks whether chr is alphanumeric
int
isalnum(int chr);
// Checks whether chr is alphabetic
int
isalpha(int chr);
// Checks whether chr is control character
int
iscntrl(int chr);
// Checks whether chr is decimal digit
int
isdigit(int chr);
// Checks whether chr has graphical representation using locale
int
isgraph(int chr);
// Checks whether chr is lowercase letter
int
islower(int chr);
// Checks whether chr is printable
int
isprint(int chr);
// Checks whether chr is punctuation character
int
ispunct(int chr);
// Checks whether chr is white-space
int
isspace(int chr);
// Checks whether chr is uppercase letter
int
isupper(int chr);
// Checks whether chr is hexadecimal digit
int
isxdigit(int chr);
// Converts uppercase letter to lowercase
int
tolower(int chr);
// Converts lowercase letter to uppercase
int
toupper(int chr);


/*----------------------------------------------------------------------------*/
#include <string.h>

// Searches for the first occurrence of the chr in the first n bytes of the str
void *
memchr(const void *str,
       int chr,
       size_t n);
// Compares the first n bytes of str1 and str2
int
memcmp(const void *str1,
       const void *str2,
       size_t n);
// Copies n characters from src to dst
void *
memcpy(void *dst,
       const void *src,
       size_t n);
// Checks for overlapping and copy n characters from str2 to str1
void *
memmove(void *dest,
        const void *src,
        size_t n);
// Copies the character c to the first n characters of the str
void *
memset(void *str,
       int chr,
       size_t n);


// Copies src to dst.
char *
strcpy(char *dst,
       const char *src);
// Copies up to n characters from src to dst
char *
strncpy(char *dst,
        const char *src,
        size_t n);


// Appends src to the end of dst
char *
strcat(char *dst,
       const char *src);
// Appends the src to the end of dst up to n characters long
char *
strncat(char *dst,
        const char *src,
        size_t n);


// Searches for the first occurrence of chr in str
char *
strchr(const char *str,
       int chr);
// Searches for the last occurrence of the character in str
char *
strrchr(const char *str,
        int chr);
// Compares str1 to str2
int
strcmp(const char *str1,
       const char *str2);
// Compares at most the first n bytes of str1 and str2
int
strncmp(const char *str1,
        const char *str2,
        size_t n);
// Compares str1 to str2, the result depends on the <location.h>'s LC_COLLATE
int
strcoll(const char *str1,
        const char *str2);
size_t
// calculates the length of the initial segment of
// str1 which consists entirely of characters in str2
strspn(const char *str1,
       const char *str2);
// Calculates the length of the initial segment of
// str1 which consists entirely of characters not in str2
size_t
strcspn(const char *str1,
        const char *str2);


// Computes the length of str up to but not including the '\0' character
size_t
strlen(const char *str);
// Finds the first character in str1 that matches any character specified in str2
char *
strpbrk(const char *str1,
        const char *str2);
// Finds the first occurrence of the entire string needle
// (not including '\0') which appears in the string haystack
char *
strstr(const char *haystack,
       const char *needle);
// Breaks str into a series of tokens separated by delim
char *
strtok(char *str,
       const char *delim);
// Transforms src according to the current locale and copies the first n
// characters of the transformed string to dst, returning its length
size_t
strxfrm(char *dst,
        const char *src,
        size_t n);


// Searches an internal array for the error number errno
// and returns a pointer to an error message string.
char *
strerror(int errno);


/*----------------------------------------------------------------------------*/
#include <stdio.h>
EOF;        /* end of file */
NULL;       /* constant with value of 0 */
stdin;      /* standard input stream */
stdout;     /* standard output stream */
stderr;     /* standard error stream */

char *format =
"%%"            /* escape percent sign */
"%-+ 0w.pmc"    /* prefixes: -      left justify
                             +      print with sign
                                    print space if no sign
                             0      pad with leading zero
                             w      minimum field width
                             .p     precision
                             m      conversion character: h   short,
                                                          l   long,
                                                          L   long double
                             c      conversion character: */
"%d or %i"      /* integer */
"%u"            /* unsigned integer */
"%c"            /* single character */
"%s"            /* string */
"%f"            /* double */
"%e or %E"      /* expontial */
"%o"            /* octal */
"%x or %X"      /* hexadecimal */
"%p"            /* pointer */
"%n"            /* number of characters written */
"%g or %G"      /* same as f or e, E depending exponent */
"\n";

// Closes the stream. All buffers are flushed
int
fclose(FILE *stream);
// Clears the end-of-file and error indicators for the given stream
void
clearerr(FILE *stream);
// Tests the end-of-file indicator for the given stream
int
feof(FILE *stream);
// Tests the error indicator for the given stream
int
ferror(FILE *stream);
// Flushes the output buffer of a stream
int
fflush(FILE *stream);
// Gets the current file position of the stream and writes it to pos
int
fgetpos(FILE *stream,
        fpos_t *pos);
// Opens the filename using the given mode
FILE *
fopen(const char *fname,
      const char *mode);
// Reads data from the given stream into the array pointed to by ptr
size_t
fread(void *ptr,
      size_t size,
      size_t nmemb,
      FILE *stream);
// Associates a new filename with the given open stream and
// same time closing the old file in stream
FILE *
freopen(const char *fname,
        const char *mode,
        FILE *stream);
// Sets the file position of the stream to the given offset. The argument
// offset signifies the number of bytes to seek from the given whence position
int
fseek(FILE *stream,
      long int offset,
      int whence);
// Sets the file position of the given stream to the given position. The
// argument pos is a position given by the function fgetpos
int
fsetpos(FILE *stream,
        const fpos_t *pos);
// Returns the current file position of the given stream
long int
ftell(FILE *stream);
// Writes data from the array pointed to by ptr to the given stream
size_t
fwrite(const void *ptr,
       size_t size,
       size_t nmemb,
       FILE *stream);
// Deletes the given filename so that it is no longer accessible
int
remove(const char *fname);
// Causes the filename referred to by old_fname to be changed to new_fname
int
rename(const char *old_fname,
       const char *new_fname);
// Sets the file position to the beginning of the file of the given stream
void
rewind(FILE *stream);
// Defines how a stream should be buffered
void
setbuf(FILE *stream,
       char *buffer);
// Another function to define how a stream should be buffered
int
setvbuf(FILE *stream,
        char *buffer,
        int mode,
        size_t size);


// Creates a temporary file in binary update mode (wb+)
FILE *
tmpfile(void);
// Generates and returns a valid temporary filename which does not exist
char *
tmpnam(char *str);


// Sends formatted output to a stream
int
fprintf(FILE *stream,
       const char *format,
       ...);
// Sends formatted output to stdout
int
printf(const char *format,
       ...);
// Sends formatted output to a string
int
sprintf(char *str,
        const char *format,
        ...);
// Sends formatted output to a stream using an argument list
int
vfprintf(FILE *stream,
         const char *format,
         va_list arg);
// Sends formatted output to stdout using an argument list
int
vprintf(const char *format,
        va_list arg);
// Sends formatted output to a string using an argument list
int
vsprintf(char *str,
         const char *format,
         va_list arg);


// Reads formatted input from a stream
int
fscanf(FILE *stream,
       const char *format,
       ...);
// Reads formatted input from stdin
int
scanf(const char *format,
      ...);
// Reads formatted input from a string
int
sscanf(const char *str,
       const char *format,
       ...);


// Gets the next character from the specified stream
// and advances the position indicator for the stream
int
fgetc(FILE *stream);
// Reads a line from the specified stream and stores it into str. It stops when
// either (n-1) characters are read, the \n character is read, or the
// end-of-file is reached, whichever comes first
char *
fgets(char *str,
      int n,
      FILE *stream);
// Writes a character to the specified stream and
// advances the position indicator for the stream
int
fputc(int chr,
      FILE *stream);
// Writes a string to the specified stream up to but not including '\0'
int
fputs(const char *str,
      FILE *stream);
// Gets the next character from the specified stream and
// advances the position indicator for the stream
int
getc(FILE *stream);
// Gets a character from stdin
int
getchar(void);
// Reads a line from stdin and stores it into str. It stops when either the
// \n is read or when the end-of-file is reached, whichever comes first
char *
gets(char *str);
// Writes a character to the specified stream and
// advances the position indicator for the stream
int
putc(int char,
     FILE *stream);
// Writes a character to stdout
int
putchar(int char);
// Writes a string to stdout up to but not including '\0'.
// A \n character is appended to the output
int
puts(const char *str);
// Pushes the character onto the specified stream
// so that the this is the next character read
int
ungetc(int char,
       FILE *stream);


// Prints a descriptive error message to stderr.
// First str is printed followed by a colon then a space
void
perror(const char *str);


/*----------------------------------------------------------------------------*/
#include <stdarg.h>

// Declaration of pointer to arguments
va_list name;

// Initialization of argument pointer, lastarg is last named argument
va_start(name, lastarg);
// Access next unamed arg, update pointer
va_arg(name, type);
// Call before exiting function
va_end(name);


/*----------------------------------------------------------------------------*/
#include <stdbool.h>

bool b;  /* typdef */
true;    /* constant value of 1 */
false;   /* constant value of 0 */


/*----------------------------------------------------------------------------*/
#include <stdlib.h>

// Converts s to double
double
atof(const char *str);
// Converts str to int
int
atoi(const char *str);
// Converts str to long integer
long int
atol(const char *str);
// Converts str to double from its start to end pointer
double
strtod(const char *str,
       char **end);
// Converts str to long integer with base (binary, octal, hexa, decimal)
long int
strtol(const char *str,
       char **end,
       int base);
// Converts str to unsigned long integer with base (binary, octal, hexa, decimal)
unsigned long int
strtoul(const char *str,
        char **end,
        int base);


// Allocates the requested memory and returns a pointer to it
void *
malloc(size_t size);
// Allocates the requested memory, initializes it, and returns a pointer to it
void *
calloc(size_t nitems,
       size_t size);
// Attempts to resize the previously allocated memory block at ptr
void *
realloc(void *ptr,
        size_t size);
// Deallocates the previously allocated memory
void
free(void *ptr);


// Causes an abnormal program termination.
void
abort(void);
// Causes the function to be called when the program terminates normally
int
atexit(void (*func)(void));
// Causes the program to terminate normally
void
exit(int status);
// Searches for name in the environment string and returns the associated value
char *
getenv(const char *name);
// The command is passed to the host environment to be executed
int
system(const char *cmd);


// Performs a binary search
void *
bsearch(const void *key,
        const void *base,
        size_t nitems,
        size_t size,
        int (*compar)(const void *, const void *));
// Sorts an array
void
qsort(void *base,
      size_t nitems,
      size_t size,
      int (*compar)(const void *, const void*));


// Returns the absolute value of x
int
abs(int x);
// Divides numer (numerator) by denom (denominator)
div_t
div(int numer,
    int denom);
// Returns the absolute value of x
long int
labs(long int x);
// Divides numer (numerator) by denom (denominator)
ldiv_t
ldiv(long int numer,
     long int denom);
// Returns a pseudo-random number in the range of 0 to RAND_MAX
int
rand(void);
// This function seeds the random number generator used by rand()
void
srand(unsigned int seed);
// Returns the length of a multibyte character str
int
mblen(const char *str,
      size_t n);
// Converts the multibyte character str to the pwcs array
size_t
mbstowcs(wchar_t *pwcs,
         const char *str,
         size_t n);
// Examines the multibyte str
int
mbtowc(wchar_t *pwc,
       const char *str,
       size_t n);
// Converts the codes stored in the array pwcs to multibyte character str
size_t
wcstombs(char *str,
         const wchar_t *pwcs,
         size_t n);
// Examines the code which corresponds to a multibyte character wchar
int
wctomb(char *str,
       wchar_t wchar);

/*----------------------------------------------------------------------------*/
#include <time.h>

struct tm {
   int tm_sec;         /* seconds, range 0 to 59           */
   int tm_min;         /* minutes, range 0 to 59           */
   int tm_hour;        /* hours, range 0 to 23             */
   int tm_mday;        /* day of the month, range 1 to 31  */
   int tm_mon;         /* month, range 0 to 11             */
   int tm_year;        /* The number of years since 1900   */
   int tm_wday;        /* day of the week, range 0 to 6    */
   int tm_yday;        /* day in the year, range 0 to 365  */
   int tm_isdst;       /* daylight saving time             */
};

// Returns a pointer to a string which represents
// the day and time of the structure timeptr
char *
asctime(const struct tm *timeptr);
// Returns the processor clock time used since the beginning of
// an implementation-defined era (normally the beginning of the program)
clock_t
clock(void);
// Returns a string representing the localtime based on the argument timer
char *
ctime(const time_t *timer);
// Returns the difference of seconds between time1 and time2 (time1-time2)
double
difftime(time_t time1,
         time_t time2);
// The value of timer is broken up into the structure tm and expressed in
// Coordinated Universal Time (UTC) also known as Greenwich Mean Time (GMT)
struct tm *
gmtime(const time_t *timer);
// The value of timer is broken up into the structure tm
// and expressed in the local time zone
struct tm *
localtime(const time_t *timer);
// Converts the structure pointed to by timeptr into
// a time_t value according to the local time zone
time_t
mktime(struct tm *timeptr);
// Formats the time represented in the structure timeptr according
// to the formatting rules defined in format and stored into str
size_t
strftime(char *str,
         size_t maxsize,
         const char *format,
         const struct tm *timeptr);
// Calculates the current calender time and encodes it into time_t format
time_t
time(time_t *timer);


/*----------------------------------------------------------------------------*/
#include <math.h>

// Returns the arc cosine of x in radians
double
acos(double x);
// Returns the arc sine of x in radians
double
asin(double x);
// Returns the arc tangent of x in radians
double
atan(double x);
// Returns the arc tangent in radians of y/x based on the
// signs of both values to determine the correct quadrant
double
atan2(double y,
      double x);
// Returns the cosine of a radian angle x
double
cos(double x);
// Returns the hyperbolic cosine of x
double
cosh(double x);
// Returns the sine of a radian angle x
double
sin(double x);
// Returns the hyperbolic sine of x
double
sinh(double x);
// Returns the hyperbolic tangent of x
double
tanh(double x);


// Returns the value of e raised to the xth power
double
exp(double x);
// The resultant value is x = mantissa * 2 ^ exponent
double
frexp(double x,
      int *exponent);
// Returns x multiplied by 2 raised to the power of exponent
double
ldexp(double x,
      int exponent);
// Returns the natural logarithm (base-e logarithm) of x
double
log(double x);
// Returns the common logarithm (base-10 logarithm) of x
double
log10(double x);


// Returns the fraction component, and sets integer to the integer component
double
modf(double x,
     double *integer);
// Returns x raised to the power of y
double
pow(double x,
    double y);
// Returns the square root of x
double
sqrt(double x);
// Returns the smallest integer value greater than or equal to x
double
ceil(double x);
// Returns the absolute value of x
double
fabs(double x);
// Returns the largest integer value less than or equal to x
double
floor(double x);
// Returns the remainder of x divided by y
double
fmod(double x,
     double y);
