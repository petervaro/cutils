/* INFO ************************************************************************
**                                                                            **
**                                   cutils                                   **
**                                   ======                                   **
**                                                                            **
**                     Modern and Lightweight C Utilities                     **
**                       Version: 0.8.72.026 (20140706)                       **
**                                                                            **
**                             File: cdar/cdar.h                              **
**                                                                            **
**           Designed and written by Peter Varo. Copyright (c) 2014           **
**             License agreement is provided in the LICENSE file              **
**                 For more info visit: http://www.cutils.org                 **
**                                                                            **
************************************************************************ INFO */

#ifndef _DYNAMIC_ARRAY_INTERFACE_H_
#define _DYNAMIC_ARRAY_INTERFACE_H_

#include "darv.h"

/*----------------------------------------------------------------------------*/
// Base type alias
typedef struct {} DynamicArrayi;

/*----------------------------------------------------------------------------*/
// Wrapped functions:
extern bool dari_new(DynamicArrayi**d,size_t c,int*a);
extern int*dari_data(DynamicArrayi*d,size_t*s,size_t*c);
extern int*dari_raw(DynamicArrayi*d);
extern bool dari_append(DynamicArrayi*d,size_t c,int*a);
extern bool dari_insert(DynamicArrayi*d,size_t i,size_t c,int*a);
extern bool dari_set(DynamicArrayi*d,size_t i,size_t c,int*s);
extern size_t dari_pop(DynamicArrayi*d,size_t i,size_t c,int*a);
extern size_t dari_sub(DynamicArrayi*d,size_t i,size_t c,int*a);
extern int dari_get(DynamicArrayi*d,size_t i);
extern bool dari_find(DynamicArrayi*d,const int*p,size_t*i);
extern size_t dari_findall(DynamicArrayi*d,const int*p,size_t*i);
extern void dari_print(DynamicArrayi*d);

/*----------------------------------------------------------------------------*/
// Function pointer aliases
extern void(*dari_del)(DynamicArrayi*d);
extern size_t(*dari_len)(DynamicArrayi*d);
extern size_t(*dari_size)(DynamicArrayi*d);
extern bool(*dari_resize)(DynamicArrayi*d,size_t c);
extern bool(*dari_swap)(DynamicArrayi*d,size_t i1,size_t i2, size_t c);
extern bool(*dari_reverse)(DynamicArrayi*d);
extern size_t(*dari_remove)(DynamicArrayi*d,size_t i,size_t c);
extern void(*dari_truncate)(DynamicArrayi*d,size_t i);
extern void(*dari_clear)(DynamicArrayi*d);


/*----------------------------------------------------------------------------*/
// Base type alias
typedef struct {} DynamicArrayli;

/*----------------------------------------------------------------------------*/
// Wrapped functions:
extern bool darli_new(DynamicArrayli**d,size_t c,long*a);
extern long*darli_data(DynamicArrayli*d,size_t*s,size_t*c);
extern long*darli_raw(DynamicArrayli*d);
extern bool darli_append(DynamicArrayli*d,size_t c,long*a);
extern bool darli_insert(DynamicArrayli*d,size_t i,size_t c,long*a);
extern bool darli_set(DynamicArrayli*d,size_t i,size_t c,long*s);
extern size_t darli_pop(DynamicArrayli*d,size_t i,size_t c,long*a);
extern size_t darli_sub(DynamicArrayli*d,size_t i,size_t c,long*a);
extern long darli_get(DynamicArrayli*d,size_t i);
extern bool darli_find(DynamicArrayli*d,const long*p,size_t*i);
extern size_t darli_findall(DynamicArrayli*d,const long*p,size_t*i);
extern void darli_print(DynamicArrayli*d);

/*----------------------------------------------------------------------------*/
// Function pointer aliases
extern void(*darli_del)(DynamicArrayli*d);
extern size_t(*darli_len)(DynamicArrayli*d);
extern size_t(*darli_size)(DynamicArrayli*d);
extern bool(*darli_resize)(DynamicArrayli*d,size_t c);
extern bool(*darli_swap)(DynamicArrayli*d,size_t i1,size_t i2, size_t c);
extern bool(*darli_reverse)(DynamicArrayli*d);
extern size_t(*darli_remove)(DynamicArrayli*d,size_t i,size_t c);
extern void(*darli_truncate)(DynamicArrayli*d,size_t i);
extern void(*darli_clear)(DynamicArrayli*d);


/*----------------------------------------------------------------------------*/
// Base type alias
typedef struct {} DynamicArraylli;

/*----------------------------------------------------------------------------*/
// Wrapped functions:
extern bool darlli_new(DynamicArraylli**d,size_t c,long long*a);
extern long long*darlli_data(DynamicArraylli*d,size_t*s,size_t*c);
extern long long*darlli_raw(DynamicArraylli*d);
extern bool darlli_append(DynamicArraylli*d,size_t c,long long*a);
extern bool darlli_insert(DynamicArraylli*d,size_t i,size_t c,long long*a);
extern bool darlli_set(DynamicArraylli*d,size_t i,size_t c,long long*s);
extern size_t darlli_pop(DynamicArraylli*d,size_t i,size_t c,long long*a);
extern size_t darlli_sub(DynamicArraylli*d,size_t i,size_t c,long long*a);
extern long long darlli_get(DynamicArraylli*d,size_t i);
extern bool darlli_find(DynamicArraylli*d,const long long*p,size_t*i);
extern size_t darlli_findall(DynamicArraylli*d,const long long*p,size_t*i);
extern void darlli_print(DynamicArraylli*d);

/*----------------------------------------------------------------------------*/
// Function pointer aliases
extern void(*darlli_del)(DynamicArraylli*d);
extern size_t(*darlli_len)(DynamicArraylli*d);
extern size_t(*darlli_size)(DynamicArraylli*d);
extern bool(*darlli_resize)(DynamicArraylli*d,size_t c);
extern bool(*darlli_swap)(DynamicArraylli*d,size_t i1,size_t i2, size_t c);
extern bool(*darlli_reverse)(DynamicArraylli*d);
extern size_t(*darlli_remove)(DynamicArraylli*d,size_t i,size_t c);
extern void(*darlli_truncate)(DynamicArraylli*d,size_t i);
extern void(*darlli_clear)(DynamicArraylli*d);


/*----------------------------------------------------------------------------*/
// Base type alias
typedef struct {} DynamicArrayu;

/*----------------------------------------------------------------------------*/
// Wrapped functions:
extern bool daru_new(DynamicArrayu**d,size_t c,unsigned int*a);
extern unsigned int*daru_data(DynamicArrayu*d,size_t*s,size_t*c);
extern unsigned int*daru_raw(DynamicArrayu*d);
extern bool daru_append(DynamicArrayu*d,size_t c,unsigned int*a);
extern bool daru_insert(DynamicArrayu*d,size_t i,size_t c,unsigned int*a);
extern bool daru_set(DynamicArrayu*d,size_t i,size_t c,unsigned int*s);
extern size_t daru_pop(DynamicArrayu*d,size_t i,size_t c,unsigned int*a);
extern size_t daru_sub(DynamicArrayu*d,size_t i,size_t c,unsigned int*a);
extern unsigned int daru_get(DynamicArrayu*d,size_t i);
extern bool daru_find(DynamicArrayu*d,const unsigned int*p,size_t*i);
extern size_t daru_findall(DynamicArrayu*d,const unsigned int*p,size_t*i);
extern void daru_print(DynamicArrayu*d);

/*----------------------------------------------------------------------------*/
// Function pointer aliases
extern void(*daru_del)(DynamicArrayu*d);
extern size_t(*daru_len)(DynamicArrayu*d);
extern size_t(*daru_size)(DynamicArrayu*d);
extern bool(*daru_resize)(DynamicArrayu*d,size_t c);
extern bool(*daru_swap)(DynamicArrayu*d,size_t i1,size_t i2, size_t c);
extern bool(*daru_reverse)(DynamicArrayu*d);
extern size_t(*daru_remove)(DynamicArrayu*d,size_t i,size_t c);
extern void(*daru_truncate)(DynamicArrayu*d,size_t i);
extern void(*daru_clear)(DynamicArrayu*d);


/*----------------------------------------------------------------------------*/
// Base type alias
typedef struct {} DynamicArraylu;

/*----------------------------------------------------------------------------*/
// Wrapped functions:
extern bool darlu_new(DynamicArraylu**d,size_t c,unsigned long*a);
extern unsigned long*darlu_data(DynamicArraylu*d,size_t*s,size_t*c);
extern unsigned long*darlu_raw(DynamicArraylu*d);
extern bool darlu_append(DynamicArraylu*d,size_t c,unsigned long*a);
extern bool darlu_insert(DynamicArraylu*d,size_t i,size_t c,unsigned long*a);
extern bool darlu_set(DynamicArraylu*d,size_t i,size_t c,unsigned long*s);
extern size_t darlu_pop(DynamicArraylu*d,size_t i,size_t c,unsigned long*a);
extern size_t darlu_sub(DynamicArraylu*d,size_t i,size_t c,unsigned long*a);
extern unsigned long darlu_get(DynamicArraylu*d,size_t i);
extern bool darlu_find(DynamicArraylu*d,const unsigned long*p,size_t*i);
extern size_t darlu_findall(DynamicArraylu*d,const unsigned long*p,size_t*i);
extern void darlu_print(DynamicArraylu*d);

/*----------------------------------------------------------------------------*/
// Function pointer aliases
extern void(*darlu_del)(DynamicArraylu*d);
extern size_t(*darlu_len)(DynamicArraylu*d);
extern size_t(*darlu_size)(DynamicArraylu*d);
extern bool(*darlu_resize)(DynamicArraylu*d,size_t c);
extern bool(*darlu_swap)(DynamicArraylu*d,size_t i1,size_t i2, size_t c);
extern bool(*darlu_reverse)(DynamicArraylu*d);
extern size_t(*darlu_remove)(DynamicArraylu*d,size_t i,size_t c);
extern void(*darlu_truncate)(DynamicArraylu*d,size_t i);
extern void(*darlu_clear)(DynamicArraylu*d);


/*----------------------------------------------------------------------------*/
// Base type alias
typedef struct {} DynamicArrayllu;

/*----------------------------------------------------------------------------*/
// Wrapped functions:
extern bool darllu_new(DynamicArrayllu**d,size_t c,unsigned long long*a);
extern unsigned long long*darllu_data(DynamicArrayllu*d,size_t*s,size_t*c);
extern unsigned long long*darllu_raw(DynamicArrayllu*d);
extern bool darllu_append(DynamicArrayllu*d,size_t c,unsigned long long*a);
extern bool darllu_insert(DynamicArrayllu*d,size_t i,size_t c,unsigned long long*a);
extern bool darllu_set(DynamicArrayllu*d,size_t i,size_t c,unsigned long long*s);
extern size_t darllu_pop(DynamicArrayllu*d,size_t i,size_t c,unsigned long long*a);
extern size_t darllu_sub(DynamicArrayllu*d,size_t i,size_t c,unsigned long long*a);
extern unsigned long long darllu_get(DynamicArrayllu*d,size_t i);
extern bool darllu_find(DynamicArrayllu*d,const unsigned long long*p,size_t*i);
extern size_t darllu_findall(DynamicArrayllu*d,const unsigned long long*p,size_t*i);
extern void darllu_print(DynamicArrayllu*d);

/*----------------------------------------------------------------------------*/
// Function pointer aliases
extern void(*darllu_del)(DynamicArrayllu*d);
extern size_t(*darllu_len)(DynamicArrayllu*d);
extern size_t(*darllu_size)(DynamicArrayllu*d);
extern bool(*darllu_resize)(DynamicArrayllu*d,size_t c);
extern bool(*darllu_swap)(DynamicArrayllu*d,size_t i1,size_t i2, size_t c);
extern bool(*darllu_reverse)(DynamicArrayllu*d);
extern size_t(*darllu_remove)(DynamicArrayllu*d,size_t i,size_t c);
extern void(*darllu_truncate)(DynamicArrayllu*d,size_t i);
extern void(*darllu_clear)(DynamicArrayllu*d);


/*----------------------------------------------------------------------------*/
// Base type alias
typedef struct {} DynamicArrayc;

/*----------------------------------------------------------------------------*/
// Wrapped functions:
extern bool darc_new(DynamicArrayc**d,size_t c,char*a);
extern char*darc_data(DynamicArrayc*d,size_t*s,size_t*c);
extern char*darc_raw(DynamicArrayc*d);
extern bool darc_append(DynamicArrayc*d,size_t c,char*a);
extern bool darc_insert(DynamicArrayc*d,size_t i,size_t c,char*a);
extern bool darc_set(DynamicArrayc*d,size_t i,size_t c,char*s);
extern size_t darc_pop(DynamicArrayc*d,size_t i,size_t c,char*a);
extern size_t darc_sub(DynamicArrayc*d,size_t i,size_t c,char*a);
extern char darc_get(DynamicArrayc*d,size_t i);
extern bool darc_find(DynamicArrayc*d,const char*p,size_t*i);
extern size_t darc_findall(DynamicArrayc*d,const char*p,size_t*i);
extern void darc_print(DynamicArrayc*d);

/*----------------------------------------------------------------------------*/
// Function pointer aliases
extern void(*darc_del)(DynamicArrayc*d);
extern size_t(*darc_len)(DynamicArrayc*d);
extern size_t(*darc_size)(DynamicArrayc*d);
extern bool(*darc_resize)(DynamicArrayc*d,size_t c);
extern bool(*darc_swap)(DynamicArrayc*d,size_t i1,size_t i2, size_t c);
extern bool(*darc_reverse)(DynamicArrayc*d);
extern size_t(*darc_remove)(DynamicArrayc*d,size_t i,size_t c);
extern void(*darc_truncate)(DynamicArrayc*d,size_t i);
extern void(*darc_clear)(DynamicArrayc*d);


/*----------------------------------------------------------------------------*/
// Base type alias
typedef struct {} DynamicArrays;

/*----------------------------------------------------------------------------*/
// Wrapped functions:
extern bool dars_new(DynamicArrays**d,size_t c,char**a);
extern char**dars_data(DynamicArrays*d,size_t*s,size_t*c);
extern char**dars_raw(DynamicArrays*d);
extern bool dars_append(DynamicArrays*d,size_t c,char**a);
extern bool dars_insert(DynamicArrays*d,size_t i,size_t c,char**a);
extern bool dars_set(DynamicArrays*d,size_t i,size_t c,char**s);
extern size_t dars_pop(DynamicArrays*d,size_t i,size_t c,char**a);
extern size_t dars_sub(DynamicArrays*d,size_t i,size_t c,char**a);
extern char* dars_get(DynamicArrays*d,size_t i);
extern bool dars_find(DynamicArrays*d,const char**p,size_t*i);
extern size_t dars_findall(DynamicArrays*d,const char**p,size_t*i);
extern void dars_print(DynamicArrays*d);

/*----------------------------------------------------------------------------*/
// Function pointer aliases
extern void(*dars_del)(DynamicArrays*d);
extern size_t(*dars_len)(DynamicArrays*d);
extern size_t(*dars_size)(DynamicArrays*d);
extern bool(*dars_resize)(DynamicArrays*d,size_t c);
extern bool(*dars_swap)(DynamicArrays*d,size_t i1,size_t i2, size_t c);
extern bool(*dars_reverse)(DynamicArrays*d);
extern size_t(*dars_remove)(DynamicArrays*d,size_t i,size_t c);
extern void(*dars_truncate)(DynamicArrays*d,size_t i);
extern void(*dars_clear)(DynamicArrays*d);


/*----------------------------------------------------------------------------*/
// Base type alias
typedef struct {} DynamicArrayf;

/*----------------------------------------------------------------------------*/
// Wrapped functions:
extern bool darf_new(DynamicArrayf**d,size_t c,float*a);
extern float*darf_data(DynamicArrayf*d,size_t*s,size_t*c);
extern float*darf_raw(DynamicArrayf*d);
extern bool darf_append(DynamicArrayf*d,size_t c,float*a);
extern bool darf_insert(DynamicArrayf*d,size_t i,size_t c,float*a);
extern bool darf_set(DynamicArrayf*d,size_t i,size_t c,float*s);
extern size_t darf_pop(DynamicArrayf*d,size_t i,size_t c,float*a);
extern size_t darf_sub(DynamicArrayf*d,size_t i,size_t c,float*a);
extern float darf_get(DynamicArrayf*d,size_t i);
extern bool darf_find(DynamicArrayf*d,const float*p,size_t*i);
extern size_t darf_findall(DynamicArrayf*d,const float*p,size_t*i);
extern void darf_print(DynamicArrayf*d);

/*----------------------------------------------------------------------------*/
// Function pointer aliases
extern void(*darf_del)(DynamicArrayf*d);
extern size_t(*darf_len)(DynamicArrayf*d);
extern size_t(*darf_size)(DynamicArrayf*d);
extern bool(*darf_resize)(DynamicArrayf*d,size_t c);
extern bool(*darf_swap)(DynamicArrayf*d,size_t i1,size_t i2, size_t c);
extern bool(*darf_reverse)(DynamicArrayf*d);
extern size_t(*darf_remove)(DynamicArrayf*d,size_t i,size_t c);
extern void(*darf_truncate)(DynamicArrayf*d,size_t i);
extern void(*darf_clear)(DynamicArrayf*d);


/*----------------------------------------------------------------------------*/
// Base type alias
typedef struct {} DynamicArrayd;

/*----------------------------------------------------------------------------*/
// Wrapped functions:
extern bool dard_new(DynamicArrayd**d,size_t c,double*a);
extern double*dard_data(DynamicArrayd*d,size_t*s,size_t*c);
extern double*dard_raw(DynamicArrayd*d);
extern bool dard_append(DynamicArrayd*d,size_t c,double*a);
extern bool dard_insert(DynamicArrayd*d,size_t i,size_t c,double*a);
extern bool dard_set(DynamicArrayd*d,size_t i,size_t c,double*s);
extern size_t dard_pop(DynamicArrayd*d,size_t i,size_t c,double*a);
extern size_t dard_sub(DynamicArrayd*d,size_t i,size_t c,double*a);
extern double dard_get(DynamicArrayd*d,size_t i);
extern bool dard_find(DynamicArrayd*d,const double*p,size_t*i);
extern size_t dard_findall(DynamicArrayd*d,const double*p,size_t*i);
extern void dard_print(DynamicArrayd*d);

/*----------------------------------------------------------------------------*/
// Function pointer aliases
extern void(*dard_del)(DynamicArrayd*d);
extern size_t(*dard_len)(DynamicArrayd*d);
extern size_t(*dard_size)(DynamicArrayd*d);
extern bool(*dard_resize)(DynamicArrayd*d,size_t c);
extern bool(*dard_swap)(DynamicArrayd*d,size_t i1,size_t i2, size_t c);
extern bool(*dard_reverse)(DynamicArrayd*d);
extern size_t(*dard_remove)(DynamicArrayd*d,size_t i,size_t c);
extern void(*dard_truncate)(DynamicArrayd*d,size_t i);
extern void(*dard_clear)(DynamicArrayd*d);


/*----------------------------------------------------------------------------*/
// Base type alias
typedef struct {} DynamicArrayld;

/*----------------------------------------------------------------------------*/
// Wrapped functions:
extern bool darld_new(DynamicArrayld**d,size_t c,long double*a);
extern long double*darld_data(DynamicArrayld*d,size_t*s,size_t*c);
extern long double*darld_raw(DynamicArrayld*d);
extern bool darld_append(DynamicArrayld*d,size_t c,long double*a);
extern bool darld_insert(DynamicArrayld*d,size_t i,size_t c,long double*a);
extern bool darld_set(DynamicArrayld*d,size_t i,size_t c,long double*s);
extern size_t darld_pop(DynamicArrayld*d,size_t i,size_t c,long double*a);
extern size_t darld_sub(DynamicArrayld*d,size_t i,size_t c,long double*a);
extern long double darld_get(DynamicArrayld*d,size_t i);
extern bool darld_find(DynamicArrayld*d,const long double*p,size_t*i);
extern size_t darld_findall(DynamicArrayld*d,const long double*p,size_t*i);
extern void darld_print(DynamicArrayld*d);

/*----------------------------------------------------------------------------*/
// Function pointer aliases
extern void(*darld_del)(DynamicArrayld*d);
extern size_t(*darld_len)(DynamicArrayld*d);
extern size_t(*darld_size)(DynamicArrayld*d);
extern bool(*darld_resize)(DynamicArrayld*d,size_t c);
extern bool(*darld_swap)(DynamicArrayld*d,size_t i1,size_t i2, size_t c);
extern bool(*darld_reverse)(DynamicArrayld*d);
extern size_t(*darld_remove)(DynamicArrayld*d,size_t i,size_t c);
extern void(*darld_truncate)(DynamicArrayld*d,size_t i);
extern void(*darld_clear)(DynamicArrayld*d);

/*----------------------------------------------------------------------------*/
// Interfaces
#define new3(ptr_dar_ptr, count, data_ptr) _Generic((ptr_dar_ptr),             \
    DynamicArrayi**  : dari_new,                                               \
    DynamicArrayli** : darli_new,                                              \
    DynamicArraylli**: darlli_new,                                             \
    DynamicArrayu**  : daru_new,                                               \
    DynamicArraylu** : darlu_new,                                              \
    DynamicArrayllu**: darllu_new,                                             \
    DynamicArrayc**  : darc_new,                                               \
    DynamicArrays**  : dars_new,                                               \
    DynamicArrayf**  : darf_new,                                               \
    DynamicArrayd**  : dard_new,                                               \
    DynamicArrayld** : darld_new,                                              \
    DynamicArray**   : darv_new)(ptr_dar_ptr, count, data_ptr)


#define del1(dar_ptr) _Generic((dar_ptr),                                      \
    DynamicArrayi*   : dari_del,                                               \
    DynamicArrayli*  : darli_del,                                              \
    DynamicArraylli* : darlli_del,                                             \
    DynamicArrayu*   : daru_del,                                               \
    DynamicArraylu*  : darlu_del,                                              \
    DynamicArrayllu* : darllu_del,                                             \
    DynamicArrayc*   : darc_del,                                               \
    DynamicArrays*   : dars_del,                                               \
    DynamicArrayf*   : darf_del,                                               \
    DynamicArrayd*   : dard_del,                                               \
    DynamicArrayld*  : darld_del,                                              \
    DynamicArray*    : darv_del)(dar_ptr)


#define data3(dar_ptr, size_ptr, count_ptr) _Generic((dar_ptr),                \
    DynamicArrayi*   : dari_data,                                              \
    DynamicArrayli*  : darli_data,                                             \
    DynamicArraylli* : darlli_data,                                            \
    DynamicArrayu*   : daru_data,                                              \
    DynamicArraylu*  : darlu_data,                                             \
    DynamicArrayllu* : darllu_data,                                            \
    DynamicArrayc*   : darc_data,                                              \
    DynamicArrays*   : dars_data,                                              \
    DynamicArrayf*   : darf_data,                                              \
    DynamicArrayd*   : dard_data,                                              \
    DynamicArrayld*  : darld_data,                                             \
    DynamicArray*    : darv_data)(dar_ptr, size_ptr, count_ptr)


#define raw1(dar_ptr) _Generic((dar_ptr),                                      \
    DynamicArrayi*   : dari_raw,                                               \
    DynamicArrayli*  : darli_raw,                                              \
    DynamicArraylli* : darlli_raw,                                             \
    DynamicArrayu*   : daru_raw,                                               \
    DynamicArraylu*  : darlu_raw,                                              \
    DynamicArrayllu* : darllu_raw,                                             \
    DynamicArrayc*   : darc_raw,                                               \
    DynamicArrays*   : dars_raw,                                               \
    DynamicArrayf*   : darf_raw,                                               \
    DynamicArrayd*   : dard_raw,                                               \
    DynamicArrayld*  : darld_raw,                                              \
    DynamicArray*    : darv_raw)(dar_ptr)


#define len1(dar_ptr) _Generic((dar_ptr),                                      \
    DynamicArrayi*   : dari_len,                                               \
    DynamicArrayli*  : darli_len,                                              \
    DynamicArraylli* : darlli_len,                                             \
    DynamicArrayu*   : daru_len,                                               \
    DynamicArraylu*  : darlu_len,                                              \
    DynamicArrayllu* : darllu_len,                                             \
    DynamicArrayc*   : darc_len,                                               \
    DynamicArrays*   : dars_len,                                               \
    DynamicArrayf*   : darf_len,                                               \
    DynamicArrayd*   : dard_len,                                               \
    DynamicArrayld*  : darld_len,                                              \
    DynamicArray*    : darv_len)(dar_ptr)


#define size1(dar_ptr) _Generic((dar_ptr),                                     \
    DynamicArrayi*   : dari_size,                                              \
    DynamicArrayli*  : darli_size,                                             \
    DynamicArraylli* : darlli_size,                                            \
    DynamicArrayu*   : daru_size,                                              \
    DynamicArraylu*  : darlu_size,                                             \
    DynamicArrayllu* : darllu_size,                                            \
    DynamicArrayc*   : darc_size,                                              \
    DynamicArrays*   : dars_size,                                              \
    DynamicArrayf*   : darf_size,                                              \
    DynamicArrayd*   : dard_size,                                              \
    DynamicArrayld*  : darld_size,                                             \
    DynamicArray*    : darv_size)(dar_ptr)


#define resize2(dar_ptr, count) _Generic((dar_ptr),                            \
    DynamicArrayi*   : dari_resize,                                            \
    DynamicArrayli*  : darli_resize,                                           \
    DynamicArraylli* : darlli_resize,                                          \
    DynamicArrayu*   : daru_resize,                                            \
    DynamicArraylu*  : darlu_resize,                                           \
    DynamicArrayllu* : darllu_resize,                                          \
    DynamicArrayc*   : darc_resize,                                            \
    DynamicArrays*   : dars_resize,                                            \
    DynamicArrayf*   : darf_resize,                                            \
    DynamicArrayd*   : dard_resize,                                            \
    DynamicArrayld*  : darld_resize,                                           \
    DynamicArray*    : darv_resize)(dar_ptr, count)


#define swap4(dar_ptr, index1, index2, count) _Generic((dar_ptr),              \
    DynamicArrayi*   : dari_swap,                                              \
    DynamicArrayli*  : darli_swap,                                             \
    DynamicArraylli* : darlli_swap,                                            \
    DynamicArrayu*   : daru_swap,                                              \
    DynamicArraylu*  : darlu_swap,                                             \
    DynamicArrayllu* : darllu_swap,                                            \
    DynamicArrayc*   : darc_swap,                                              \
    DynamicArrays*   : dars_swap,                                              \
    DynamicArrayf*   : darf_swap,                                              \
    DynamicArrayd*   : dard_swap,                                              \
    DynamicArrayld*  : darld_swap,                                             \
    DynamicArray*    : darv_swap)(dar_ptr, index1, index2, count)


#define reverse1(dar_ptr) _Generic((dar_ptr),                                  \
    DynamicArrayi*   : dari_reverse,                                           \
    DynamicArrayli*  : darli_reverse,                                          \
    DynamicArraylli* : darlli_reverse,                                         \
    DynamicArrayu*   : daru_reverse,                                           \
    DynamicArraylu*  : darlu_reverse,                                          \
    DynamicArrayllu* : darllu_reverse,                                         \
    DynamicArrayc*   : darc_reverse,                                           \
    DynamicArrays*   : dars_reverse,                                           \
    DynamicArrayf*   : darf_reverse,                                           \
    DynamicArrayd*   : dard_reverse,                                           \
    DynamicArrayld*  : darld_reverse,                                          \
    DynamicArray*    : darv_reverse)(dar_ptr)


#define append3(dar_ptr, count, data_ptr) _Generic((dar_ptr),                  \
    DynamicArrayi*   : dari_append,                                            \
    DynamicArrayli*  : darli_append,                                           \
    DynamicArraylli* : darlli_append,                                          \
    DynamicArrayu*   : daru_append,                                            \
    DynamicArraylu*  : darlu_append,                                           \
    DynamicArrayllu* : darllu_append,                                          \
    DynamicArrayc*   : darc_append,                                            \
    DynamicArrays*   : dars_append,                                            \
    DynamicArrayf*   : darf_append,                                            \
    DynamicArrayd*   : dard_append,                                            \
    DynamicArrayld*  : darld_append,                                           \
    DynamicArray*    : darv_append)(dar_ptr, count, data_ptr)


#define insert4(dar_ptr, index, count, data_ptr) _Generic((dar_ptr),           \
    DynamicArrayi*   : dari_insert,                                            \
    DynamicArrayli*  : darli_insert,                                           \
    DynamicArraylli* : darlli_insert,                                          \
    DynamicArrayu*   : daru_insert,                                            \
    DynamicArraylu*  : darlu_insert,                                           \
    DynamicArrayllu* : darllu_insert,                                          \
    DynamicArrayc*   : darc_insert,                                            \
    DynamicArrays*   : dars_insert,                                            \
    DynamicArrayf*   : darf_insert,                                            \
    DynamicArrayd*   : dard_insert,                                            \
    DynamicArrayld*  : darld_insert,                                           \
    DynamicArray*    : darv_insert)(dar_ptr, index, count, data_ptr)


#define remove3(dar_ptr, index, count) _Generic((dar_ptr),                     \
    DynamicArrayi*   : dari_remove,                                            \
    DynamicArrayli*  : darli_remove,                                           \
    DynamicArraylli* : darlli_remove,                                          \
    DynamicArrayu*   : daru_remove,                                            \
    DynamicArraylu*  : darlu_remove,                                           \
    DynamicArrayllu* : darllu_remove,                                          \
    DynamicArrayc*   : darc_remove,                                            \
    DynamicArrays*   : dars_remove,                                            \
    DynamicArrayf*   : darf_remove,                                            \
    DynamicArrayd*   : dard_remove,                                            \
    DynamicArrayld*  : darld_remove,                                           \
    DynamicArray*    : darv_remove)(dar_ptr, index, count)


#define pop4(dar_ptr, index, count, dest_ptr) _Generic((dar_ptr),              \
    DynamicArrayi*   : dari_pop,                                               \
    DynamicArrayli*  : darli_pop,                                              \
    DynamicArraylli* : darlli_pop,                                             \
    DynamicArrayu*   : daru_pop,                                               \
    DynamicArraylu*  : darlu_pop,                                              \
    DynamicArrayllu* : darllu_pop,                                             \
    DynamicArrayc*   : darc_pop,                                               \
    DynamicArrays*   : dars_pop,                                               \
    DynamicArrayf*   : darf_pop,                                               \
    DynamicArrayd*   : dard_pop,                                               \
    DynamicArrayld*  : darld_pop,                                              \
    DynamicArray*    : darv_pop)(dar_ptr, index, count, dest_ptr)


#define sub4(dar_ptr, index, count, dest_ptr) _Generic((dar_ptr),              \
    DynamicArrayi*   : dari_sub,                                               \
    DynamicArrayli*  : darli_sub,                                              \
    DynamicArraylli* : darlli_sub,                                             \
    DynamicArrayu*   : daru_sub,                                               \
    DynamicArraylu*  : darlu_sub,                                              \
    DynamicArrayllu* : darllu_sub,                                             \
    DynamicArrayc*   : darc_sub,                                               \
    DynamicArrays*   : dars_sub,                                               \
    DynamicArrayf*   : darf_sub,                                               \
    DynamicArrayd*   : dard_sub,                                               \
    DynamicArrayld*  : darld_sub,                                              \
    DynamicArray*    : darv_sub)(dar_ptr, index, count, dest_ptr)


#define truncate2(dar_ptr, index) _Generic((dar_ptr),                          \
    DynamicArrayi*   : dari_truncate,                                          \
    DynamicArrayli*  : darli_truncate,                                         \
    DynamicArraylli* : darlli_truncate,                                        \
    DynamicArrayu*   : daru_truncate,                                          \
    DynamicArraylu*  : darlu_truncate,                                         \
    DynamicArrayllu* : darllu_truncate,                                        \
    DynamicArrayc*   : darc_truncate,                                          \
    DynamicArrays*   : dars_truncate,                                          \
    DynamicArrayf*   : darf_truncate,                                          \
    DynamicArrayd*   : dard_truncate,                                          \
    DynamicArrayld*  : darld_truncate,                                         \
    DynamicArray*    : darv_truncate)(dar_ptr, index)


#define set4(dar_ptr, index, count, data_ptr) _Generic((dar_ptr),              \
    DynamicArrayi*   : dari_set,                                               \
    DynamicArrayli*  : darli_set,                                              \
    DynamicArraylli* : darlli_set,                                             \
    DynamicArrayu*   : daru_set,                                               \
    DynamicArraylu*  : darlu_set,                                              \
    DynamicArrayllu* : darllu_set,                                             \
    DynamicArrayc*   : darc_set,                                               \
    DynamicArrays*   : dars_set,                                               \
    DynamicArrayf*   : darf_set,                                               \
    DynamicArrayd*   : dard_set,                                               \
    DynamicArrayld*  : darld_set,                                              \
    DynamicArray*    : darv_set)(dar_ptr, index, count, data_ptr)


#define get2(dar_ptr, index) _Generic((dar_ptr),                               \
    DynamicArrayi*   : dari_get,                                               \
    DynamicArrayli*  : darli_get,                                              \
    DynamicArraylli* : darlli_get,                                             \
    DynamicArrayu*   : daru_get,                                               \
    DynamicArraylu*  : darlu_get,                                              \
    DynamicArrayllu* : darllu_get,                                             \
    DynamicArrayc*   : darc_get,                                               \
    DynamicArrays*   : dars_get,                                               \
    DynamicArrayf*   : darf_get,                                               \
    DynamicArrayd*   : dard_get,                                               \
    DynamicArrayld*  : darld_get,                                              \
    DynamicArray*    : darv_get)(dar_ptr, index)


#define clear1(dar_ptr) _Generic((dar_ptr),                                    \
    DynamicArrayi*   : dari_clear,                                             \
    DynamicArrayli*  : darli_clear,                                            \
    DynamicArraylli* : darlli_clear,                                           \
    DynamicArrayu*   : daru_clear,                                             \
    DynamicArraylu*  : darlu_clear,                                            \
    DynamicArrayllu* : darllu_clear,                                           \
    DynamicArrayc*   : darc_clear,                                             \
    DynamicArrays*   : dars_clear,                                             \
    DynamicArrayf*   : darf_clear,                                             \
    DynamicArrayd*   : dard_clear,                                             \
    DynamicArrayld*  : darld_clear,                                            \
    DynamicArray*    : darv_clear)(dar_ptr)


#define find3(dar_ptr, item_ptr, index_ptr) _Generic((dar_ptr),                \
    DynamicArrayi*   : dari_find,                                              \
    DynamicArrayli*  : darli_find,                                             \
    DynamicArraylli* : darlli_find,                                            \
    DynamicArrayu*   : daru_find,                                              \
    DynamicArraylu*  : darlu_find,                                             \
    DynamicArrayllu* : darllu_find,                                            \
    DynamicArrayc*   : darc_find,                                              \
    DynamicArrays*   : dars_find,                                              \
    DynamicArrayf*   : darf_find,                                              \
    DynamicArrayd*   : dard_find,                                              \
    DynamicArrayld*  : darld_find,                                             \
    DynamicArray*    : darv_find)(dar_ptr, item_ptr, index_ptr)


#define findall3(dar_ptr, item_ptr, indices_ptr) _Generic((dar_ptr),           \
    DynamicArrayi*   : dari_findall,                                           \
    DynamicArrayli*  : darli_findall,                                          \
    DynamicArraylli* : darlli_findall,                                         \
    DynamicArrayu*   : daru_findall,                                           \
    DynamicArraylu*  : darlu_findall,                                          \
    DynamicArrayllu* : darllu_findall,                                         \
    DynamicArrayc*   : darc_findall,                                           \
    DynamicArrays*   : dars_findall,                                           \
    DynamicArrayf*   : darf_findall,                                           \
    DynamicArrayd*   : dard_findall,                                           \
    DynamicArrayld*  : darld_findall,                                          \
    DynamicArray*    : darv_findall)(dar_ptr, item_ptr, indices_ptr)


#define sort2(dar_ptr, cmp_func) _Generic((dar_ptr),                           \
    DynamicArrayi*   : dari_sort,                                              \
    DynamicArrayli*  : darli_sort,                                             \
    DynamicArraylli* : darlli_sort,                                            \
    DynamicArrayu*   : daru_sort,                                              \
    DynamicArraylu*  : darlu_sort,                                             \
    DynamicArrayllu* : darllu_sort,                                            \
    DynamicArrayc*   : darc_sort,                                              \
    DynamicArrays*   : dars_sort,                                              \
    DynamicArrayf*   : darf_sort,                                              \
    DynamicArrayd*   : dard_sort,                                              \
    DynamicArrayld*  : darld_sort,                                             \
    DynamicArray*    : darv_sort)(dar_ptr, cmp_func)


#define sortsub4(dar_ptr, index, count, cmp_func) _Generic((dar_ptr),          \
    DynamicArrayi*   : dari_sortsub,                                           \
    DynamicArrayli*  : darli_sortsub,                                          \
    DynamicArraylli* : darlli_sortsub,                                         \
    DynamicArrayu*   : daru_sortsub,                                           \
    DynamicArraylu*  : darlu_sortsub,                                          \
    DynamicArrayllu* : darllu_sortsub,                                         \
    DynamicArrayc*   : darc_sortsub,                                           \
    DynamicArrays*   : dars_sortsub,                                           \
    DynamicArrayf*   : darf_sortsub,                                           \
    DynamicArrayd*   : dard_sortsub,                                           \
    DynamicArrayld*  : darld_sortsub,                                          \
    DynamicArray*    : darv_sortsub)(dar_ptr, index, count, cmp_func)


#define print1(dar_ptr) _Generic((dar_ptr),                                    \
    DynamicArrayi*   : dari_print,                                             \
    DynamicArrayli*  : darli_print,                                            \
    DynamicArraylli* : darlli_print,                                           \
    DynamicArrayu*   : daru_print,                                             \
    DynamicArraylu*  : darlu_print,                                            \
    DynamicArrayllu* : darllu_print,                                           \
    DynamicArrayc*   : darc_print,                                             \
    DynamicArrays*   : dars_print,                                             \
    DynamicArrayf*   : darf_print,                                             \
    DynamicArrayd*   : dard_print,                                             \
    DynamicArrayld*  : darld_print,                                            \
    DynamicArray*    : darv_print)(dar_ptr)


#define GET_MACRO_BY_ARG1_COUNT(_1, MACRO_NAME, ...) MACRO_NAME

#define GET_MACRO_BY_ARG2_COUNT(_1, _2, MACRO_NAME, ...) MACRO_NAME

#define GET_MACRO_BY_ARG3_COUNT(_1, _2, _3, MACRO_NAME, ...) MACRO_NAME

#define GET_MACRO_BY_ARG4_COUNT(_1, _2, _3, _4, MACRO_NAME, ...) MACRO_NAME

#define GET_MACRO_BY_ARG5_COUNT(_1, _2, _3, _4, _5, MACRO_NAME, ...) MACRO_NAME

#define new(...) GET_MACRO_BY_ARG3_COUNT(__VA_ARGS__, new3, new2, new1)(__VA_ARGS__)
#define del(...) GET_MACRO_BY_ARG1_COUNT(__VA_ARGS__, del1)(__VA_ARGS__)
#define data(...) GET_MACRO_BY_ARG3_COUNT(__VA_ARGS__, data3, data2, data1)(__VA_ARGS__)
#define raw(...) GET_MACRO_BY_ARG1_COUNT(__VA_ARGS__, raw1)(__VA_ARGS__)
#define len(...) GET_MACRO_BY_ARG1_COUNT(__VA_ARGS__, len1)(__VA_ARGS__)
#define size(...) GET_MACRO_BY_ARG1_COUNT(__VA_ARGS__, size1)(__VA_ARGS__)
#define resize(...) GET_MACRO_BY_ARG2_COUNT(__VA_ARGS__, resize2, resize1)(__VA_ARGS__)
#define swap(...) GET_MACRO_BY_ARG4_COUNT(__VA_ARGS__, swap4, swap3, swap2, swap1)(__VA_ARGS__)
#define reverse(...) GET_MACRO_BY_ARG1_COUNT(__VA_ARGS__, reverse1)(__VA_ARGS__)
#define append(...) GET_MACRO_BY_ARG3_COUNT(__VA_ARGS__, append3, append2, append1)(__VA_ARGS__)
#define insert(...) GET_MACRO_BY_ARG4_COUNT(__VA_ARGS__, insert4, insert3, insert2, insert1)(__VA_ARGS__)
#define remove(...) GET_MACRO_BY_ARG3_COUNT(__VA_ARGS__, remove3, remove2, remove1)(__VA_ARGS__)
#define pop(...) GET_MACRO_BY_ARG4_COUNT(__VA_ARGS__, pop4, pop3, pop2, pop1)(__VA_ARGS__)
#define sub(...) GET_MACRO_BY_ARG4_COUNT(__VA_ARGS__, sub4, sub3, sub2, sub1)(__VA_ARGS__)
#define truncate(...) GET_MACRO_BY_ARG2_COUNT(__VA_ARGS__, truncate2, truncate1)(__VA_ARGS__)
#define set(...) GET_MACRO_BY_ARG4_COUNT(__VA_ARGS__, set4, set3, set2, set1)(__VA_ARGS__)
#define get(...) GET_MACRO_BY_ARG2_COUNT(__VA_ARGS__, get2, get1)(__VA_ARGS__)
#define clear(...) GET_MACRO_BY_ARG1_COUNT(__VA_ARGS__, clear1)(__VA_ARGS__)
#define find(...) GET_MACRO_BY_ARG3_COUNT(__VA_ARGS__, find3, find2, find1)(__VA_ARGS__)
#define findall(...) GET_MACRO_BY_ARG3_COUNT(__VA_ARGS__, findall3, findall2, findall1)(__VA_ARGS__)
#define sort(...) GET_MACRO_BY_ARG2_COUNT(__VA_ARGS__, sort2, sort1)(__VA_ARGS__)
#define sortsub(...) GET_MACRO_BY_ARG4_COUNT(__VA_ARGS__, sortsub4, sortsub3, sortsub2, sortsub1)(__VA_ARGS__)
#define print(...) GET_MACRO_BY_ARG2_COUNT(__VA_ARGS__, dartg_printcb, print1)(__VA_ARGS__)

#endif // _DYNAMIC_ARRAY_INTERFACE_H_
