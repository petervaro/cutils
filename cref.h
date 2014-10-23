/* INFO ************************************************************************
**                                                                            **
**                                   cutils                                   **
**                                   ======                                   **
**                                                                            **
**                     Modern and Lightweight C Utilities                     **
**                       Version: 0.8.96.247 (20141023)                       **
**                                                                            **
**                                File: cref.h                                **
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

/* Inspired by:
    Jospeh H. Silverman
    http://www.tutorialspoint.com
    http://www.stackoverflow.com
    http://en.cppreference.com
    http://en.wikipedia.org */

/*----------------------------------------------------------------------------*/
// The macro language
#ifdef __CREF_NEVER_DEFINE_THIS_OR_CUTE_LITTLE_KITTENS_WILL_DIE__
#error "Variable '__CREF_NEVER_DEFINE_THIS_OR_CUTE_LITTLE_KITTENS_WILL_DIE__'"\
       "should never be defined, because 'cref.c' is not a valid C file!"

#define NDEBUG
#undef NDEBUG

#ifndef NDEBUG
  #if defined NDEBUG
    int i = 0;
  #elif 10
    int i = 1;
  #else
    int i = -1;
  #endif // defined NDEBUG
#endif // NDEBUG


/*----------------------------------------------------------------------------*/
#include <assert.h>

// Makes assert to be ignored if defined before header is included
#define NDEBUG

// Issues a compile-time diagnostic if the
// value of a constant expression is false
#define static_assert _Static_assert

// If expression is false, writes info and terminate program
void
assert(int expr);


/*----------------------------------------------------------------------------*/
#include <errno.h>

#define EDOM        // Mathematics argument out of domain of function
#define EILSEQ      // Illegal byte sequence
#define ERANGE      // Result too large

// the type of errno value
typedef int errno_t;

// Global variable error number is readable and writeable
extern errno_t errno;

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
// Checks whether chr is a blank character in the current C locale
// In the default C locale this is only \s (0x20) \t (0x09)
int
isblank(int chr);
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
// Compares the first n bytes of str1 and str2, returns negative if str1 is
// lesser than, 0 if equal to and positive if str1 is greater than str2
int
memcmp(const void *str1,
       const void *str2,
       size_t n);
// Copies n characters from src to dst
void *
memcpy(void *dst,
       const void *src,
       size_t n);
// Checks for overlapping and copy n characters from src to dst
void *
memmove(void *dst,
        const void *src,
        size_t n);
// Copies the chr to the first n characters of str
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
// Copies no more than s1max bytes to s1
errno_t
strcat_s(char *restrict dst,
         rsize_t dstmax,
         const char *restrict src);
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

// file handle, this is a structure containing the information about a
// file or text stream needed to perform input or output operations on it
typedef struct {} FILE;

typedef unsigned int size_t;
typedef /* non array */ fpos_t;

// a pointer to a FILE which refers to the standard input stream
FILE *stdin;
// a pointer to a FILE which refers to the standard output stream
FILE *stdout;
// a pointer to a FILE which refers to the standard error stream
FILE *stderr;

// a negative integer of type int used to indicate end-of-file conditions
#define EOF (-1)
// an integer which is the size of the buffer used by the setbuf() function
#define BUFSIZ
// the size of a char array which is large enough to
// store the name of any file that can be opened
#define FILENAME_MAX
// the number of files that may be open simultaneously; will be at least 8
#define FOPEN_MAX
// an abbreviation for "input/output fully buffered"; it is an integer
// which may be passed to the setvbuf() function to request block
// buffered input and output for an open stream
#define _IOFBF
// an abbreviation for "input/output line buffered"; it is an integer
// which may be passed to the setvbuf() function to request line
// buffered input and output for an open stream
#define _IOLBF
// an abbreviation for "input/output not buffered"; it is an integer
// which may be passed to the setvbuf() function to request
// unbuffered input and output for an open stream
#define _IONBF
// the size of a char array which is large enough to store a
// temporary filename generated by the tmpnam() function
#define L_tmpnam
// a macro expanding to the null pointer constant; that is, a
// constant representing a pointer value which is guaranteed
// not to be a valid address of an object in memory
#define NULL
// an integer which may be passed to the fseek() function to
// request positioning relative to the current file position
#define SEEK_CUR
// an integer which may be passed to the fseek() function to
// request positioning relative to the end of the file
#define SEEK_END
// an integer which may be passed to the fseek() function to
//request positioning relative to the beginning of the file
#define SEEK_SET
// the maximum number of unique filenames generable
// by the tmpnam() function; will be at least 25
#define TMP_MAX

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
"%ld or %li"    /* long integer */
"%lld or %lli"  /* long long integer */
"%u"            /* unsigned integer */
"%lu"           /* unsigned long integer */
"%llu"          /* unsigned long long integer */
"%c"            /* single character */
"%s"            /* string */
"%f"            /* double */
"%Lf"           /* long double */
"%a"            /* hexadecimal floating point */
"%e or %E"      /* expontial */
"%o"            /* octal */
"%x or %X"      /* hexadecimal */
"%p"            /* pointer */
"%n"            /* number of characters written */
"%g or %G"      /* same as f or e, E depending exponent */
"\n";

// TODO: %ju and %lf and %td and %hd and %hu
//       http://www.mekong.net/tech/printf.htm

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
fread(void *ptr,        /* output buffer */
      size_t size,      /* size of items */
      size_t nmemb,     /* number of items */
      FILE *stream);    /* input stream */
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
fwrite(const void *ptr, /* input data */
       size_t size,     /* size of items */
       size_t nmemb,    /* number of items */
       FILE *stream);   /* output stream */
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
// Composes a string with the same text that would be printed if format was used
// on printf, but instead of being printed, the content is stored as a C string
// in the buffer pointed by s (taking n as the maximum buffer capacity to fill)
int
snprintf(char *str,
         size_t n,
         const char *format,
         ...);


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
// \n is read or when the end-of-file is reached, whichever comes first but
// at most n characters
char *
gets_s(char *restrict buffer,
       size_t n);
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
typedef void* va_list;

// Initialization of argument pointer, lastarg is last named argument
void va_start(va_list name,
              lastarg);
// Access next unamed arg, update pointer
type va_arg(va_list name,
            type);
// Call before exiting function
void va_end(va_list name);
// Copies the (previously initialized) variable argument list src to dst
void va_copy(va_list dst,
             va_list src);


/*----------------------------------------------------------------------------*/
#include <stddef.h>

// Integer constant expression of type size_t, the value of
// which is the offset in bytes to the structure member
// (member-designator), from the beginning of its structure (type)
#define offsetof(type, member)

#define size_t
#define ptrdiff_t


/*----------------------------------------------------------------------------*/
#include <stdbool.h>

typedef int _Bool;

#define bool _Bool
#define true  1
#define false 0


/*----------------------------------------------------------------------------*/
#include <stdlib.h>

#define EXIT_FAILURE
#define EXIT_SUCCESS

/* Terminates program */
_Noreturn void exit(int exit_code);

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
// Attempts to resize the previously allocated memory block at ptr,
// if succeseded returns the new memory address, else a NULL ptr
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
// Causes the program to terminate normally with cleaning up
void
exit(int code);
// Causes the program to terminate normally without cleaning up
void
_Exit(int code);
// Causes the program to terminate normally without cleaning up
// but with IO buffers flushed
void
quick_exit(int code);
// Registers a function to be called on quick_exit() invocation
int
at_quick_exit(void (*func)());
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

#define CLOCKS_PER_SEC

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

#define FP_ILOGB0
#define FP_ILOGBNAN

// Computes the absolute value of an integer number
int
abs(int x);
long
labs(long x);
long long
llabs(long long x);
intmax_t
imaxabs(intmax_t x);
// Returns the absolute value of a float number
float
fabsf(float x);
double
fabs(double x);
long double
fabsl(long double x);

// Return values of div functions
struct div_t { int quot; int rem; };
struct ldiv_t { long quot; long rem; };
struct lldiv_t { long long quot; long long rem; };
struct imaxdiv_t { intmax_t quot; intmax_t rem; };
// Computes the quotient (the result of the expression x/y) and
// remainder (the result of the expression x%y) simultaneously
div_t
div(int x,
    int y);
ldiv_t
ldiv(long x,
     long y);
lldiv_t
lldiv(long long x,
      long long y);
imaxdiv_t
imaxdiv(intmax_t x,
        intmax_t y);

// Computes the remainder of the division operation x/y
float
fmodf(float x,
      float y);
double
fmod(double x,
     double y);
long double
fmodl(long double x,
      long double y);

// Computes the signed remainder of the floating point division
// operation x/y. In contrast to fmod(), the returned value is
// not guaranteed to have the same sign as x
float
remainderf(float x,
           float y);
double
remainder(double x,
          double y);
long double
remainderl(long double x,
           long double y);

// Computes the remainder of the floating point division operation
// x/y as the remainder() function does. Additionally, the sign and
// at least the three of the last bits of x/y will be stored in quo
float
remquof(float x,
        float y,
        int *quo);
double
remquo(double x,
       double y,
       int *quo);
long double
remquol(long double x,
        long double y,
        int *quo);

// The fma functions compute (x*y) + z, rounded as one ternary operation,
// according to the rounding mode characterized by the value of FLT_ROUNDS
float
fmaf(float x,
     float y,
     float z);
double
fma(double x,
    double y,
    double z);
long double
fmal(long double x,
     long double y,
     long double z);

// Returns the larger of two floating point arguments. If one of the arguments
// is NaN, this function returns the other argument. If both arguments are NaNs,
// the function returns NaN
float
fmaxf(float x,
      float y);
double
fmax(double x,
     double y);
long double
fmaxl(long double x,
      long double y);

// Returns the smaller of two floating point arguments. If one of the arguments
// is NaN, this function returns the other argument. If both arguments are NaNs,
// the function returns NaN
float
fminf(float x,
      float y);
double
fmin(double x,
     double y);
long double
fminl(long double x,
      long double y);

// Returns the positive difference between x and y. This could be
// implemented as fmax (x - y, 0), so if x ≤ y, the result is always
// equals to 0, otherwise it is x - y.
float
fdimf(float x,
      float y);
double
fdim(double x,
     double y);
long double
fdiml(long double x,
      long double y);

// Converts the implementation-defined character string str into the
// corresponding quiet NaN value. The call nan("string") is equivalent to the
// call strtod("NAN(string)", (char**)NULL);
float
nanf(const char* str);
double
nan(const char* str);
long double
nanl(const char* str);

// Computes the e (Euler's number, 2.7182818) raised to the given power x
float
expf(float x);
double
exp(double x);
long double
expl(long double x);

// Computes 2 raised to the given power x
float
exp2f(float x);
double
exp2(double x);
long double
exp2l(long double x);

// Computes the e (Euler's number, 2.7182818) raised to the
// given power x, minus 1. This function is more accurate
// than the expression exp(x)-1 if x is close to zero
float
expm1f(float x);
double
expm1(double x);
long double
expm1l(long double x);

// Computes the natural (base e) logarithm of x
float
logf(float x);
double
log(double x);
long double
logl(long double x);

// Computes the base 2 logarithm of x
float
log2f(float x);
double
log2(double x);
long double
log2l(long double x);

// Computes the common (base 10) logarithm of x
float
log10f(float x);
double
log10(double x);
long double
log10l(long double x);

// Computes the natural (base e) logarithm of 1+x. This function is more
// precise than the expression log(1+x) if x is close to zero
float
log1pf(float x);
double
log1p(double x);
long double
log1pl(long double x);

// Extracts the value of the exponent from the floating-point
// argument x, and returns it as a signed integer value. Formally,
// the result is the integral part of log r|x| as a signed integral
// value, for non-zero x, where r is FLT_RADIX
int
ilogbf(float x);
int
ilogb(double x);
int
ilogbl(long double x);

// Extracts the value of the exponent from the floating-point argument x, and
// returns it as a floating-point value. Formally, the result is the integral
// part of log r|x| as a signed floating-point value, for non-zero x, where
// r is FLT_RADIX. If x is subnormal, it is treated as though it was normalized.
float
logbf(float x);
double
logb(double x);
long double
logbl(long double x);

// Computes square root of x
float
sqrtf(float x);
double
sqrt(double x);
long double
sqrtl(long double x);

// Computes the cubic root of x
float
cbrtf(float x);
double
cbrt(double x);
long double
cbrtl(long double x);

// Computes the square root of the sum of the squares of x and y, without
// undue overflow or underflow at intermediate stages of the computation
float
hypotf(float x,
       float y);
double
hypot(double x,
      double y);
long double
hypotl(long double x,
       long double y);

// Computes the value of base raised to the power exp.
float
powf(float base,
     float exp);
double
pow(double base,
    double exp);
long double
powl(long double base,
     long double exp);

// Computes the sine of a
float
sinf(float a);
double
sin(double a);
long double
sinl(long double a);

// Computes the cosine of a
float
cosf(float a);
double
cos(double a);
long double
cosl(long double a);

// Computes tangent of a
float
tanf(float a);
double
tan(double a);
long double
tanl(long double a);

// Computes arc sine of a
float
asinf(float a);
double
asin(double a);
long double
asinl(long double a);

// Computes arc cosine of a
float
acosf(float a);
double
acos(double a);
long double
acosl(long double a);

// Computes arc tangent of a
float
atanf(float a);
double
atan(double a);
long double
atanl(long double a);

// Computes the inverse tangent of y/x using the signs
// of arguments to correctly determine quadrant
float
atan2f(float y,
       float x);
double
atan2(double y,
      double x);
long double
atan2l(long double y,
       long double x);

// Computes hyperbolic sine of a
float
sinhf(float a);
double
sinh(double a);
long double
sinhl(long double a);

// Computes hyperbolic cosine of a
float
coshf(float a);
double
cosh(double a);
long double
coshl(long double a);

// Computes hyperbolic tangent of a
float
tanhf(float a);
double
tanh(double a);
long double
tanhl(long double a);

// Computes area hyperbolic sine of a
float
asinhf(float a);
double
asinh(double a);
long double
asinhl(long double a);

// Computes hyperbolic area cosine of a
float
acoshf(float a);
double
acosh(double a);
long double
acoshl(long double a);

// Computes area hyperbolic tangent of a
float
atanhf(float a);
double
atanh(double a);
long double
atanhl(long double a);

// Computes the error function of x
float
erff(float x);
double
erf(double x);
long double
erfl(long double x);

// Computes the complementary error function of x
float
erfcf(float x);
double
erfc(double x);
long double
erfcl(long double x);

// Computes the natural logarithm of the absolute
// value of the gamma function of x
float
lgammaf(float x);
double
lgamma(double x);
long double
lgammal(long double x);

// Computes the gamma function of x
float
tgammaf(float x);
double
tgamma(double x);
long double
tgammal(long double x);

// Computes nearest integer not less than x
float
ceilf(float x);
double
ceil(double x);
long double
ceill(long double x);

// Computes nearest integer not greater than x
float
floorf(float x);
double
floor(double x);
long double
floorl(long double x);

// Computes nearest integer not greater in magnitude than x
float
truncf(float x);
double
trunc(double x);
long double
truncl(long double x);

// Computes nearest integer to x. Number is rounded away from zero in halfway cases
float
roundf(float x);
double
round(double x);
long double
roundl(long double x);
long
lroundf(float x);
long
lround(double x);
long
lroundl(long double x);
long long
llroundf(float x);
long long
llround(double x);
long long
llroundl(long double x);

// Rounds the floating-point argument x to an integer value in
// floating-point format, using the current rounding mode
float
nearbyintf(float x);
double
nearbyint(double x);
long double
nearbyintl(long double x);

// Rounds the floating-point argument x to an integer value in
// floating-point format, using the current rounding mode. If the
// result differs from x (i.e., x was not an integer value already),
// the floating-point exception FE_INEXACT is raised
float
rintf(float x);
double
rint(double x);
long double
rintl(long double x);
long
lrintf(float x);
long
lrint(double x);
long
lrintl(long double x);
long long
llrintf(float x);
long long
llrint(double x);
long long
llrintl(long double x);

// Decomposes given floating point value x to significand and exponent
float
frexpf(float x,
       int* exp);
double
frexp(double x,
      int* exp);
long double
frexpl(long double x,
       int* exp);

// Multiplies a floating point value x by 2 raised to power exp
float
ldexpf(float x,
       int exp);
double
ldexp(double x,
      int exp);
long double
ldexpl(long double x,
       int exp);

// Decomposes given floating point value x into integral and fractional
// parts, each having the same type and sign as x. The integral part
// (in floating-point format) is stored in the object pointed to by iptr
float
modff(float x,
      float* iptr);
double
modf(double x,
     double* iptr);
long double
modfl(long double x,
      long double* iptr);

// Multiplies a floating point value x by FLT_RADIX raised to power exp.
// On binary systems it is equivalent to ldexp()
float
scalbnf(float x,
        int exp);
double
scalbn(double x,
       int exp);
long double
scalbnl(long double x,
        int exp);
float
scalblnf(float x,
         long exp);
double
scalbln(double x,
        long exp);
long double
scalblnl(long double x,
         long exp);

// Returns the next representable value of from in the direction of to
// If from equals to to, to is returned
float
nextafterf(float from,
           float to);
double
nextafter(double from,
          double to);
long double
nextafterl(long double from,
           long double to);
// If from equals to to, to is returned, converted from long double to
// the return type of the function without loss of range or precision
float
nexttowardf(float from,
            long double to);
double
nexttoward(double from,
           long double to);
long double
nexttowardl(long double from,
            long double to);

// Composes a floating point value with the magnitude of x and the sign of y
float
copysignf(float x,
          float y);
double
copysign(double x,
         double y);
long double
copysignl(long double x,
          long double y);

// Categorizes floating point value arg into the following categories:
// zero, subnormal, normal, infinite, NAN, or implementation-defined category.
// The macro returns an integral value
#define fpclassify(arg)

// Determines if the given floating point number arg has finite value i.e.
// it is normal, subnormal or zero, but not infinite or NAN.
// The macro returns an integral value
#define isfinite(arg)

// Determines if the given floating point number arg is positive or negative
// infinity. The macro returns an integral value
#define isinf(arg)

// Determines if the given floating point number arg is not-a-number (NaN).
// The macro returns an integral value
#define isnan(arg)

// Determines if the given floating point number arg is normal, i.e.
// is neither zero, subnormal, infinite, nor NaN.
// The macro returns an integral value
#define isnormal(arg)

// Determines if the given floating point number arg is negative.
// The macro returns an integral value
#define signbit(arg)

// Attempts to clear the floating-point exceptions that are
// listed in the bitmask argument excepts, which is a bitwise
// OR of the floating point exception macros
int
feclearexcept(int excepts);

// Attempts to store the status of the floating-point
// environment in the object pointed to by envp
int
fegetenv(fenv_t* envp);
// Attempts to establish the floating-point environment from the object pointed
// to by envp. The value of that object must be previously obtained by a call to
// feholdexcept or fegetenv or be a floating-point macro constant. If any of the
// floating-point status flags are set in envp, they become set in the
// environment (and are then testable with fetestexcept), but the corresponding
// floating-point exceptions are not raised (execution continues uninterrupted)
int
fesetenv(const fenv_t* envp);

// Attempts to obtain the full contents of the floating-point exception flags
// that are listed in the bitmask argument excepts, which is a bitwise OR
// of the floating point exception macros
int
fegetexceptflag(fexcept_t* flagp,
                int excepts);
// Attempts to copy the full contents of the floating-point exception flags that
// are listed in excepts from flagp into the floating-point environment. Does
// not raise any exceptions, only modifies the flags. The full contents of a
// floating-point exception flag is not necessarily a boolean value indicating
// whether the exception is raised or cleared. For example, it may be a struct
// which includes the boolean status and the address of the code that triggered
// the exception. These functions obtain all such content and obtain/store it in
// flagp in implementation-defined format
int
fesetexceptflag(const fexcept_t* flagp,
                int excepts);

// Attempts to establish the floating-point rounding direction
// equal to the argument argument round, which is expected to be
// one of the floating point rounding macros
int
fesetround(int round);
// Returns the value of the floating point rounding macro
// that corresponds to the current rounding direction
int
fegetround(void);

// First, saves the current floating-point environment to the object pointed
// to by envp (similar to fegetenv), then clears all floating-point status
// flags, and then installs the non-stop mode: future floating-point exceptions
// will not interrupt execution (will not trap), until the floating-point
// environment is restored by feupdateenv or fesetenv. This function may be
// used in the beginning of a subroutine that must hide the floating-point
// exceptions it may raise from the caller. If only some exceptions must be
// suppressed, while others must be reported, the non-stop mode is usually
// ended with a call to feupdateenv after clearing the unwanted exceptions.
int
feholdexcept(fenv_t* envp);

// Attempts to raise all floating point exceptions listed in excepts (a bitwise
// OR of the floating point exception macros). If one of the exceptions is
// FE_OVERFLOW or FE_UNDERFLOW, this function may additionally raise FE_INEXACT.
// The order in which the exceptions are raised is unspecified, except that
// FE_OVERFLOW and FE_UNDERFLOW are always raised before FE_INEXACT
int
feraiseexcept(int excepts);

// Attempts to obtain the full contents of the floating-point exception
// flags that are listed in the bitmask argument excepts, which is a
// bitwise OR of the floating point exception macros
int
fegetexceptflag(fexcept_t* flagp,
                int excepts);
// Attempts to copy the full contents of the floating-point exception flags that
// are listed in excepts from flagp into the floating-point environment. Does
// not raise any exceptions, only modifies the flags. The full contents of a
// floating-point exception flag is not necessarily a boolean value indicating
// whether the exception is raised or cleared. For example, it may be a struct
// which includes the boolean status and the address of the code that triggered
// the exception. These functions obtain all such content and obtain/store it in
// flagp in implementation-defined format
int
fesetexceptflag(const fexcept_t* flagp,
                int excepts);

// Attempts to establish the floating-point rounding direction
// equal to the argument argument round, which is expected to
// be one of the floating point rounding macros
int
fesetround(int round);
// Returns the value of the floating point rounding macro
// that corresponds to the current rounding direction
int
fegetround();

// Determines which of the specified subset of the floating point
// exceptions are currently set. The argument excepts is a bitwise
// OR of the floating point exception macros
int
fetestexcept(int excepts);

// First, remembers the currently raised floating-point exceptions, then
// restores the floating-point environment from the object pointed to by envp
// (similar to fesetenv), then raises the floating-point exceptions that were
// saved. This function may be used to end the non-stop mode established by
// an earlier call to feholdexcept.
int
feupdateenv(const fenv_t* envp);

/*----------------------------------------------------------------------------*/
#include <fenv.h>

// Pole error occurred in an earlier floating-point operation
#define FE_DIVBYZERO  /* implementation defined power of 2 */
// Inexact result: rounding was necessary to store the
// result of an earlier floating-point operation
#define FE_INEXACT    /* implementation defined power of 2 */
// Domain error occurred in an earlier floating-point operation
#define FE_INVALID    /* implementation defined power of 2 */
// The result of an earlier floating-point operation
// was too large to be representable
#define FE_OVERFLOW   /* implementation defined power of 2 */
// The result of an earlier floating-point operation
// was subnormal with a loss of precision
#define FE_UNDERFLOW  /* implementation defined power of 2 */
// Bitwise OR of all supported floating-point exceptions
#define FE_ALL_EXCEPT FE_DIVBYZERO | FE_INEXACT  | \
                      FE_INVALID   | FE_OVERFLOW | \
                      FE_UNDERFLOW

// Rounding towards negative infinity
#define FE_DOWNWARD   /* implementation defined */
// Rounding towards nearest integer
#define FE_TONEAREST  /* implementation defined */
// Rounding towards zero
#define FE_TOWARDZERO /* implementation defined */
// Rounding towards positive infinity
#define FE_UPWARD     /* implementation defined */

// The macro constant FE_DFL_ENV expands to an expression of type const fenv_t*,
// which points to a full copy of the default floating-point environment, that
// is, the environment as loaded at program startup
#define FE_DFL_ENV  /*implementation defined*/

// The type representing the entire floating-point environment
typedef struct {} fenv_t;
// The type representing all floating-point status flags collectively
typedef int fexcept_t;

// Attempts to clear the floating-point exceptions that are
// listed in the bitmask argument excepts, which is a bitwise
// OR of the floating point exception macros
int
feclearexcept(int excepts);

// Determines which of the specified subset of the floating point
// exceptions are currently set. The argument excepts is a bitwise
// OR of the floating point exception macros
int
fetestexcept(int excepts);

// Attempts to raise all floating point exceptions listed in excepts
// (a bitwise OR of the floating point exception macros). If one of
// the exceptions is FE_OVERFLOW or FE_UNDERFLOW, this function may
// additionally raise FE_INEXACT. The order in which the exceptions
// are raised is unspecified, except that FE_OVERFLOW and FE_UNDERFLOW
// are always raised before FE_INEXACT
int
feraiseexcept(int excepts);

// Attempts to obtain the full contents of the floating-point exception
// flags that are listed in the bitmask argument excepts, which is a bitwise
// OR of the floating point exception macros
int
fegetexceptflag(fexcept_t* flagp,
                int excepts);
// Attempts to copy the full contents of the floating-point exception flags
// that are listed in excepts from flagp into the floating-point environment.
// Does not raise any exceptions, only modifies the flags
int
fesetexceptflag(const fexcept_t* flagp,
                int excepts);

// Attempts to establish the floating-point rounding direction
// equal to the argument argument round, which is expected to
// be one of the floating point rounding macros
int fesetround(int round);

// Returns the value of the floating point rounding macro
// that corresponds to the current rounding direction
int fegetround();

// Attempts to store the status of the floating-point
// environment in the object pointed to by envp
int fegetenv(fenv_t* envp);

// Attempts to establish the floating-point environment from the object pointed
// to by envp. The value of that object must be previously obtained by a call to
// feholdexcept or fegetenv or be a floating-point macro constant. If any of the
// floating-point status flags are set in envp, they become set in the
// environment (and are then testable with fetestexcept), but the corresponding
// floating-point exceptions are not raised (execution continues uninterrupted)
int fesetenv(const fenv_t* envp);

// First, saves the current floating-point environment to the object pointed to
// by envp (similar to fegetenv), then clears all floating-point status flags,
// and then installs the non-stop mode: future floating-point exceptions will
// not interrupt execution (will not trap), until the floating-point environment
// is restored by feupdateenv or fesetenv.
int feholdexcept(fenv_t* envp);

// First, remembers the currently raised floating-point exceptions, then
// restores the floating-point environment from the object pointed to by envp
// (similar to fesetenv), then raises the floating-point exceptions that were
// saved. This function may be used to end the non-stop mode established by an
// earlier call to feholdexcept
int feupdateenv(const fenv_t* envp);

/*----------------------------------------------------------------------------*/
#include <complex.h>

// If this macro constant is defined by the compiler, the header
// <complex.h> and all of the names listed here are not provided.
#define __STDC_NO_COMPLEX__

#define imaginary _Imaginary
#define complex _Complex

// Computes the complex absolute value of z
float
cabsf(float complex z);
double
cabs(double complex z);
long double
cabsl(long double complex z);

// Computes the argument (also called phase angle) of z,
// with a branch cut along the negative real axis
float
cargf(float complex z );
double
carg(double complex z);
long double
cargl(long double complex z);

// Returns the imaginary part of z
float
cimagf(float complex z);
double
cimag(double complex z);
long double
cimagl(long double complex z);

// Returns the real part of z
float
crealf(float complex z);
double
creal(double complex z);
long double
creall(long double complex z);

// Returns the complex conjugate value of z
float complex
conjf(float complex z);
double complex
conj(double complex z);
long double complex
conjl(long double complex z);

// Computes the projection of z on the Riemann sphere
float
cprojf(float complex z);
double
cproj(double complex z);
long double
cprojl(long double complex z);

// Computes the complex base-e exponential of z
float complex
cexpf(float complex z);
double complex
cexp(double complex z);
long double complex
cexpl(long double complex z);

// Computes the complex natural (base-e) logarithm of z
// with branch cut along the negative real axis
float complex
clogf(float complex z);
double complex
clog(double complex z);
long double complex
clogl(long double complex z);

// Computes the complex square root of z with
// branch cut along the negative real axis
float complex
csqrtf(float complex z);
double complex
csqrt(double complex z);
long double complex
csqrtl(long double complex z);

// Computes the complex power function x^y, with branch cut
// for the first parameter along the negative real axis
float complex
cpowf(float complex x,
      float complex y);
double complex
cpow(double complex x,
     double complex y);
long double complex
cpowl(long double complex x,
      long double complex y);

// Computes the complex sine of z
float complex
csinf(float complex z);
double complex
csin(double complex z);
long double complex
csinl(long double complex z);

// Computes the complex cosine of z
float complex
ccosf(float complex z);
double complex
ccos(double complex z);
long double complex
ccosl(long double complex z);

// Computes the complex tangent of z
float complex
ctanf(float complex z);
double complex
ctan(double complex z);
long double complex
ctanl(long double complex z);

// Computes the complex arc sine of z with branch cuts
// outside the interval [−1,+1] along the real axi
float complex
casinf(float complex z0);
double complex
casin(double complex z);
long double complex
casinl(long double complex z);

// Computes the complex arc cosine of z with branch cuts
// outside the interval [−1,+1] along the real axis
float complex
cacosf(float complex z);
double complex
cacos(double complex z);
long double complex
cacosl(long double complex z);

// Computes the complex arc tangent of z with branch cuts
// outside the interval [−i,+i] along the real axis
float complex
catanf(float complex z);
double complex
catan(double complex z);
long double complex
catanl(long double complex z);

// Computes the complex hyperbolic sine of z
float complex
csinhf(float complex z);
double complex
csinh(double complex z);
long double complex
csinhl(long double complex z);

// Computes the complex hyperbolic cosine of z
float complex
ccoshf(float complex z);
double complex
ccosh(double complex z);
long double complex
ccoshl(long double complex z);

// Computes the complex hyperbolic tangent of z
float complex
ctanhf(float complex z);
double complex
ctanh(double complex z);
long double complex
ctanhl(long double complex z);

// Computes the complex arc hyperbolic sine of z with branch cuts
// outside the interval [−i; +i] along the imaginary axis
float complex
casinhf(float complex z);
double complex
casinh(double complex z);
long double complex
casinhl(long double complex z);

// Computes the complex arc hyperbolic cosine of z with branch cuts
// outside the values less than 1 along the real axis
float complex
cacoshf(float complex z);
double complex
cacosh(double complex z);
long double complex
cacoshl(long double complex z);

// Computes the complex arc hyperbolic tangent of z with branch cuts
// outside the interval [−1; +1] along the real axis
float complex
catanhf(float complex z);
double complex
catanh(double complex z);
long double complex
catanhl(long double complex z);


/*----------------------------------------------------------------------------*/
#include <tgmath.h>

// Type-generic macro: If any argument has type long double, sqrtl is called.
// Otherwise, if any argument has type double, sqrt is called. Otherwise,
// sqrtf is called. If at least one argument is complex, then the macro invokes
// the corresponding complex function (csqrtf, csqrt, csqrtl)
#define sqrt(n)

// Type-generic macro: If any argument has type long double,
// cbrtl is called. Otherwise, if any argument has type double,
// cbrt is called. Otherwise, cbrtf is called
#define cbrt(n)

// Type-generic macro: If any argument has type long double, the long double
// version of the function is called. Otherwise, if any argument has type
// double, the double version of the function is called. Otherwise, the float
// version of the function is called
#define hypot(x, y)

// Type-generic macro: If any argument has type long double, powl is called.
// Otherwise, if any argument has type double, pow is called. Otherwise, powf
// is called. If at least one argument is complex, then the macro invokes the
// corresponding complex function (cpowf, cpow, cpowl)
#define pow(base, exp)

// Type-generic macro: If the argument has type long double, sinl is called.
// Otherwise, if the argument has type double, sin is called. Otherwise, sinf is
// called. If the argument is complex, then the macro invokes the corresponding
// complex function (csinf, csin, csinl)
#define sin(a)

// Type-generic macro: If the argument has type long double, cosl is called.
// Otherwise, if the argument has type double, cos is called. Otherwise, cosf is
// called. If the argument is complex, then the macro invokes the corresponding
// complex function (ccosf, ccos, ccosl)
#define cos(a)

// Type-generic macro: If any argument has type long double, the long
// double version of the function is called. Otherwise, if any argument
// has type double, the double version of the function is called. Otherwise,
// the float version of the function is called
#define nextafter(from, to)
#define nexttoward(from, to)

/*----------------------------------------------------------------------------*/
#include <stdalign.h>

max_align_t ma;
// The keyword specifies the requested alignment for a type or an object
#define alignas _Alignas
// The operator reports the alignment of its operand
#define alignof _Alignof
// Allocates size bytes of memory with alignment algn
// and returns a pointer to the allocated memory
void *
aligned_alloc(size_t algn,
              size_t size);


/*----------------------------------------------------------------------------*/
#include <uchar.h>


/*----------------------------------------------------------------------------*/
#include <stdnoreturn.h>

// Special attribute for functions those not return to their caller
#define noreturn _Noreturn


/*----------------------------------------------------------------------------*/
#include <locale.h>

// Selects the entire C locale
// (implementation defined)
#define LC_ALL
// Selects the collation category of the C locale
// (implementation defined)
#define LC_COLLATE
// Selects the character classification category of the C locale
// (implementation defined)
#define LC_CTYPE
// Selects the monetary formatting category of the C locale
// (implementation defined)
#define LC_MONETARY
// Selects the numeric formatting category of the C locale
// (implementation defined)
#define LC_NUMERIC
// Selects the time formatting category of the C locale
// (implementation defined)
#define LC_TIME

// The struct lconv contains numeric and monetary formatting rules as defined by
// a C locale. Objects of this struct may be obtained with localeconv. The
// members of lconv are values of type char and of type char*. Each char* member
// except decimal_point may be pointing at a null character (that is, at an
// empty C-string). The members of type char are all non-negative numbers, any
// of which may be CHAR_MAX if the corresponding value is not available in the
// current C locale
struct lconv;

// The setlocale function installs the specified system locale or its portion as
// the new C locale. The modifications remain in effect and influences the
// execution of all locale-sensitive C library functions until the next call to
// setlocale. If locale is a null pointer, setlocale queries the current C
// locale without modifying it
char *
setlocale(int category,
          const char *locale);

// The localeconv function obtains a pointer to a static object of type lconv,
// which represents numeric and monetary formatting rules of the current locale
lconv *
localeconv();


/*----------------------------------------------------------------------------*/
#include <limits.h>

// Number for bits in a byte
#define CHAR_BIT     8
// Minimum value for signed char
#define SCHAR_MIN   -127
// Maximum value for a signed char
#define SCHAR_MAX    127
// Maximum value for an unsigned char
#define UCHAR_MAX    255
// Minimum value for type char and its value will be equal to SCHAR_MIN
// if char represents negative values otherwise zero.
#define CHAR_MIN     0
// Maximum value for type char and its value will be equal to SCHAR_MAX
// if char represents negative values otherwise UCHAR_MAX
#define CHAR_MAX     127
// Maximum number for bytes in a multibyte character
#define MB_LEN_MAX   1
// Minimum value for a short int
#define SHRT_MIN    -32767
// Maximum value for a short int
#define SHRT_MAX    +32767
// Maximum value for an unsigned short int
#define USHRT_MAX    65535
// Minimum value for an int
#define INT_MIN     -32767
// Maximum value for an int
#define INT_MAX     +32767
// Maximum value for an unsigned int
#define UINT_MAX     65535
// Minimum value for a long int
#define LONG_MIN    -2147483647
// Maximum value for a long int
#define LONG_MAX    +2147483647
// Maximum value for an unsigned long int
#define ULONG_MAX    4294967295
// Minimum value for long long int
#define LLONG_MIN   -9223372036854775807
// Maximum value for long long int
#define LLONG_MAX    9223372036854775807
// Maximum value for long long unsigned int
#define ULLONG_MAX   18446744073709551615


/*----------------------------------------------------------------------------*/
#include <float.h>

/*
 * Defines the use of evaluation formats:
 *     -1 : indeterminable
 *      0 : evaluate all operations and constants just to
 *          the range and precision of the type
 *      1 : evaluate operations and constants of type float and double to the
 *          range and precision of the double type, evaluate long double operations
 *          and constants to the range and precision of the long double type
 *      2 : evaluate all operations and constants to the range and
 *          precision of the long double type
 */
#define FLT_EVAL_METHOD

/*
 * Defines the presence or absence of subnormal numbers:
 *     -1 : indeterminable
 *      0 : absent (type does not support subnormal numbers)
 *      1 : present (type does support subnormal numbers)
 */
#define FLT_HAS_SUBNORM
#define DBL_HAS_SUBNORM
#define LDBL_HAS_SUBNORM

/*
 * Defines the rounding mode for floating point addition and it
 * can have any of the following values:
 *     -1 : indeterminable
 *      0 : toward zero
 *      1 : to nearest
 *      2 : toward positive infinity
 *      3 : toward negative infinity
 */
#define FLT_ROUNDS

// This defines the base radix representation of the exponent. A base-2 is
// binary, base-10 is the normal decimal representation, base-16 is hexadecimal
#define FLT_RADIX         2

// These macros define the number of base-FLT_RADIX
// digits in the ﬂoating-point signiﬁcand
#define FLT_MANT_DIG
#define DBL_MANT_DIG
#define LDBL_MANT_DIG

// These macros define the number of decimal digits, n, such that any
// ﬂoating-point number with p radix b digits can be rounded to a ﬂoating-point
// number with n decimal digits and back again without change to the value
#define FLT_DECIMAL_DIG   6
#define DBL_DECIMAL_DIG  10
#define LDBL_DECIMAL_DIG 10

// This macros defines the number of decimal digits, n, such that any
// ﬂoating-point number in the widest supported ﬂoating type with pmax radix b
// digits can be rounded to a ﬂoating-point number with n decimal digits and
// back again without change to the value
#define DECIMAL_DIG

// These macros define the maximum number decimal digits (base-10) that
// can be represented without change after rounding.
#define FLT_DIG           6
#define DBL_DIG          10
#define LDBL_DIG         10

// These macros define the minimum negative integer
// value for an exponent in base FLT_RADIX
#define FLT_MIN_EXP
#define DBL_MIN_EXP
#define LDBL_MIN_EXP

// These macros define the minimum negative integer
// value for an exponent in base 10
#define FLT_MIN_10_EXP  -37
#define DBL_MIN_10_EXP  -37
#define LDBL_MIN_10_EXP -37

// These macros define the maximum integer value for an exponent in base FLT_RADIX
#define FLT_MAX_EXP
#define DBL_MAX_EXP
#define LDBL_MAX_EXP

// These macros define the maximum integer value for an exponent in base 10
#define FLT_MAX_10_EXP  +37
#define DBL_MAX_10_EXP  +37
#define LDBL_MAX_10_EXP +37

// These macros define the maximum finite floating-point value
#define FLT_MAX          1E+37
#define DBL_MAX          1E+37
#define LDBL_MAX         1E+37

// These macros define the least significant digit representable
#define FLT_EPSILON      1E-5
#define DBL_EPSILON      1E-9
#define LDBL_EPSILON     1E-9

// These macros define the minimum normalized floating-point value
#define FLT_MIN          1E-37
#define DBL_MIN          1E-37
#define LDBL_MIN         1E-37

// These macros define the minimum positive floating-point number
#define FLT_TRUE_MIN     1E-37
#define DBL_TRUE_MIN     1E-37
#define LDBL_TRUE_MIN    1E-37

#endif // __CREF_NEVER_DEFINE_THIS_OR_CUTE_LITTLE_KITTENS_WILL_DIE__
