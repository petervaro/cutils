#include <header.h>

// Comment: one-liner

//\
  Comment: two-lines one-liner

/* Comment:
   multi-liner */

{
    0x00; 0X00; 077;

      .01;  .01f;   .01F;   .01l;   .01L;
     .1e6;  .1E6;  .1e-6;  .1E-6;  .1e+6;  .1E+6;
    .1e6f; .1E6f; .1e-6f; .1E-6f; .1e+6f; .1E+6f;
    .1e6F; .1E6F; .1e-6F; .1E-6F; .1e+6F; .1E+6F;
    .1e6l; .1E6l; .1e-6l; .1E-6l; .1e+6l; .1E+6l;
    .1e6L; .1E6L; .1e-6L; .1E-6L; .1e+6L; .1E+6L;

        1.;    1.0;
       1.f;    1.F;    1.0f;    1.0F;
       1.l;    1.L;    1.0l;    1.0L;
      11e2;   11E2;   11e-6;   11E-6;   11e+6;   11E+6;
     1.1e6;  1.1E6;  1.1e-6;  1.1E-6;  1.1e+6;  1.1E+6;
    1.1e6f; 1.1E6f; 1.1e-6f; 1.1E-6f; 1.1e+6f; 1.1E+6f;
    1.1e6F; 1.1E6F; 1.1e-6F; 1.1E-6F; 1.1e+6F; 1.1E+6F;
    1.1e6l; 1.1E6l; 1.1e-6l; 1.1E-6l; 1.1e+6l; 1.1E+6l;
    1.1e6L; 1.1E6L; 1.1e-6L; 1.1E-6L; 1.1e+6L; 1.1E+6L;

    0x0.1p+12F;

       0;    1;
      0u;   1U;   0l;   1L;
     0ul;  1Ul;  0uL;  1UL;
    0ull; 1Ull; 0uLL; 1ULL;

      ...;
      EOF;
     NULL;
     true;  false;
    stdin; stdout; stderr;

       'a';   L'b';     u'a';   U'a';
      '\'';   '\\';   '\x88';   '\0';   '\017';   '\n';   '\uffaa';   '\Uaabbccdd';
     L'\'';  L'\\';  L'\x88';  L'\0';  L'\017';  L'\n';  L'\uffaa';  L'\Uaabbccdd';
     u'\'';  u'\\';  u'\x88';  u'\0';  u'\017';  u'\n';  u'\uffaa';  u'\Uaabbccdd';
     U'\'';  U'\\';  U'\x88';  U'\0';  U'\017';  U'\n';  U'\uffaa';  U'\Uaabbccdd';
     '??=';  '??(';    '??)';  '??/';    '??'';  '??<';      '??>';  '??!';  '??-';
    L'??='; L'??(';   L'??)'; L'??/';   L'??''; L'??<';     L'??>'; L'??!'; L'??-';
    u'??='; u'??(';   u'??)'; u'??/';   u'??''; u'??<';     u'??>'; u'??!'; u'??-';
    U'??='; U'??(';   U'??)'; U'??/';   U'??''; U'??<';     U'??>'; U'??!'; U'??-';
       ''';    '\';     'ab';  'n\0';     L''';   L'\';      L'ab'; L'n\0';
      u''';   u'\';    u'ab'; u'n\0';     U''';   U'\';      U'ab'; U'n\0';

      "";   "a";   "abc";
     L"";  L"a";  L"abc";
     u"";  u"a";  u"abc";
    u8""; u8"a"; u8"abc";
     U"";  U"a";  U"abc";
    "%"
    "\"; """;

    void x;
    char x; signed char x; unsigned char x;
    short x; signed short x; short int x; signed short int x;
    unsigned short x; unsigned short int x;
    int x; signed x; signed int x;
    unsigned x; unsigned int x;
    long x; signed long x; long int x; signed long int x;
    unsigned long x; unsigned long int x;
    long long x; signed long long x; long long int x; signed long long int x;
    unsigned long long x; unsigned long long int x;
    float x;
    double x;
    long double x;
    _Bool x; bool x;
    float _Complex x;
    double _Complex x;
    long double _Complex x;
    float _Imaginary x;
    double _Imaginary x;
    long double _Imaginary x;

    unsigned void float x;
    unsigned void char _Complex signed double x;
    void void void x;
    void bool x;
    char void x;
    char int void x;
    signed signed _Imaginary char x;
}

enum {};
enum{hello,world};
enum
{
    hello}

NDEBUG CHAR_BIT SCHAR_MIN SCHAR_MAX UCHAR_MAX CHAR_MIN CHAR_MAX MB_LEN_MAX
SHRT_MIN SHRT_MAX USHRT_MAX INT_MIN INT_MAX UINT_MAX LONG_MIN LONG_MAX ULONG_MAX
LLONG_MIN LLONG_MAX ULLONG_MAX

#define PRINT(token) printf(#token "is %d", token)

type: auto|char|double|float|int|long|short|signed|struct|union|unsigned|void|

STORAGE_CLASS_SPECIFIERS: typedef|extern|static|_Thread_local|auto|register
TYPE_QUALIFIERS: const|restrict|volatile|_Atomic
FUNCTION_SPECIFIERS: inline|_Noreturn
STATIC_ASSERTION: _Static_assert
JUMP_STATEMENTS: break|continue|goto|return
ITERATION_STATEMENTS: do|while|for
SWITCH_STATEMENT: switch|case|default
IF_STATEMENT: if|else

x: _Alignas|_Alignof|_Atomic|_Generic|_Noreturn|_Static_assert|_Thread_local

support types:

    wchar_t
    char16_t
    char32_t
    size_t
    fpos_t
