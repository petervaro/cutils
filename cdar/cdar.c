/* INFO ************************************************************************
**                                                                            **
**                                   cutils                                   **
**                                   ======                                   **
**                                                                            **
**                     Modern and Lightweight C Utilities                     **
**                       Version: 0.8.72.195 (20140707)                       **
**                                                                            **
**                             File: cdar/cdar.c                              **
**                                                                            **
**           Designed and written by Peter Varo. Copyright (c) 2014           **
**             License agreement is provided in the LICENSE file              **
**                 For more info visit: http://www.cutils.org                 **
**                                                                            **
************************************************************************ INFO */

#include "darv.h"

/*----------------------------------------------------------------------------*/
// Wrapped function:
bool darv_new(DynamicArray**d,size_t c,void*a){return dartg_new(d,c,sizeof(void*),a);}
void darv_print(DynamicArray*d){dartg_print(d,char*,"","%p");}


/*----------------------------------------------------------------------------*/
// Base type alias
typedef DynamicArray DynamicArrayi;

/*----------------------------------------------------------------------------*/
// Wrapped functions:
bool dari_new(DynamicArrayi**d,size_t c,int*a){return dartg_new(d,c,sizeof(int),a);}
int*dari_data(DynamicArrayi*d,size_t*s,size_t*c){return (int*)darv_data(d,s,c);}
int*dari_raw(DynamicArrayi*d){return (int*)darv_raw(d);}
bool dari_append(DynamicArrayi*d,size_t c,int*a){return darv_append(d,c,a);}
bool dari_insert(DynamicArrayi*d,size_t i,size_t c,int*a){return darv_insert(d,i,c,a);}
bool dari_set(DynamicArrayi*d,size_t i,size_t c,int*s){return darv_set(d,i,c,s);}
size_t dari_pop(DynamicArrayi*d,size_t i,size_t c,int*a){return darv_pop(d,i,c,a);}
size_t dari_sub(DynamicArrayi*d,size_t i,size_t c,int*a){return darv_sub(d,i,c,a);}
int dari_get(DynamicArrayi*d,size_t i){return *(int*)darv_get(d,i);}
bool dari_find(DynamicArrayi*d,const int*p,size_t*i){return darv_find(d,p,i);}
size_t dari_findall(DynamicArrayi*d,const int*p,size_t*i){return darv_findall(d,p,i);}
void dari_print(DynamicArrayi*d){dartg_print(d,int,"i","%d");}

/*----------------------------------------------------------------------------*/
// Function pointer aliases
void(*dari_del)(DynamicArrayi*)=darv_del;
size_t(*dari_len)(DynamicArrayi*)=darv_len;
size_t(*dari_size)(DynamicArrayi*)=darv_size;
bool(*dari_resize)(DynamicArrayi*, size_t)=darv_resize;
bool(*dari_swap)(DynamicArrayi*, size_t, size_t, size_t)=darv_swap;
bool(*dari_reverse)(DynamicArrayi*)=darv_reverse;
size_t(*dari_remove)(DynamicArrayi*, size_t, size_t)=darv_remove;
void(*dari_truncate)(DynamicArrayi*, size_t)=darv_truncate;
void(*dari_clear)(DynamicArrayi*)=darv_clear;


/*----------------------------------------------------------------------------*/
// Base type alias
typedef DynamicArray DynamicArrayli;

/*----------------------------------------------------------------------------*/
// Wrapped functions:
bool darli_new(DynamicArrayli**d,size_t c,long*a){return dartg_new(d,c,sizeof(long),a);}
long*darli_data(DynamicArrayli*d,size_t*s,size_t*c){return (long*)darv_data(d,s,c);}
long*darli_raw(DynamicArrayli*d){return (long*)darv_raw(d);}
bool darli_append(DynamicArrayli*d,size_t c,long*a){return darv_append(d,c,a);}
bool darli_insert(DynamicArrayli*d,size_t i,size_t c,long*a){return darv_insert(d,i,c,a);}
bool darli_set(DynamicArrayli*d,size_t i,size_t c,long*s){return darv_set(d,i,c,s);}
size_t darli_pop(DynamicArrayli*d,size_t i,size_t c,long*a){return darv_pop(d,i,c,a);}
size_t darli_sub(DynamicArrayli*d,size_t i,size_t c,long*a){return darv_sub(d,i,c,a);}
long darli_get(DynamicArrayli*d,size_t i){return *(long*)darv_get(d,i);}
bool darli_find(DynamicArrayli*d,const long*p,size_t*i){return darv_find(d,p,i);}
size_t darli_findall(DynamicArrayli*d,const long*p,size_t*i){return darv_findall(d,p,i);}
void darli_print(DynamicArrayli*d){dartg_print(d,long,"li","%li");}

/*----------------------------------------------------------------------------*/
// Function pointer aliases
void(*darli_del)(DynamicArrayli*)=darv_del;
size_t(*darli_len)(DynamicArrayli*)=darv_len;
size_t(*darli_size)(DynamicArrayli*)=darv_size;
bool(*darli_resize)(DynamicArrayli*, size_t)=darv_resize;
bool(*darli_swap)(DynamicArrayli*, size_t, size_t, size_t)=darv_swap;
bool(*darli_reverse)(DynamicArrayli*)=darv_reverse;
size_t(*darli_remove)(DynamicArrayli*, size_t, size_t)=darv_remove;
void(*darli_truncate)(DynamicArrayli*, size_t)=darv_truncate;
void(*darli_clear)(DynamicArrayli*)=darv_clear;


/*----------------------------------------------------------------------------*/
// Base type alias
typedef DynamicArray DynamicArraylli;

/*----------------------------------------------------------------------------*/
// Wrapped functions:
bool darlli_new(DynamicArraylli**d,size_t c,long long*a){return dartg_new(d,c,sizeof(long long),a);}
long long*darlli_data(DynamicArraylli*d,size_t*s,size_t*c){return (long long*)darv_data(d,s,c);}
long long*darlli_raw(DynamicArraylli*d){return (long long*)darv_raw(d);}
bool darlli_append(DynamicArraylli*d,size_t c,long long*a){return darv_append(d,c,a);}
bool darlli_insert(DynamicArraylli*d,size_t i,size_t c,long long*a){return darv_insert(d,i,c,a);}
bool darlli_set(DynamicArraylli*d,size_t i,size_t c,long long*s){return darv_set(d,i,c,s);}
size_t darlli_pop(DynamicArraylli*d,size_t i,size_t c,long long*a){return darv_pop(d,i,c,a);}
size_t darlli_sub(DynamicArraylli*d,size_t i,size_t c,long long*a){return darv_sub(d,i,c,a);}
long long darlli_get(DynamicArraylli*d,size_t i){return *(long long*)darv_get(d,i);}
bool darlli_find(DynamicArraylli*d,const long long*p,size_t*i){return darv_find(d,p,i);}
size_t darlli_findall(DynamicArraylli*d,const long long*p,size_t*i){return darv_findall(d,p,i);}
void darlli_print(DynamicArraylli*d){dartg_print(d,long long,"lli","%lld");}

/*----------------------------------------------------------------------------*/
// Function pointer aliases
void(*darlli_del)(DynamicArraylli*)=darv_del;
size_t(*darlli_len)(DynamicArraylli*)=darv_len;
size_t(*darlli_size)(DynamicArraylli*)=darv_size;
bool(*darlli_resize)(DynamicArraylli*, size_t)=darv_resize;
bool(*darlli_swap)(DynamicArraylli*, size_t, size_t, size_t)=darv_swap;
bool(*darlli_reverse)(DynamicArraylli*)=darv_reverse;
size_t(*darlli_remove)(DynamicArraylli*, size_t, size_t)=darv_remove;
void(*darlli_truncate)(DynamicArraylli*, size_t)=darv_truncate;
void(*darlli_clear)(DynamicArraylli*)=darv_clear;


/*----------------------------------------------------------------------------*/
// Base type alias
typedef DynamicArray DynamicArrayu;

/*----------------------------------------------------------------------------*/
// Wrapped functions:
bool daru_new(DynamicArrayu**d,size_t c,unsigned int*a){return dartg_new(d,c,sizeof(unsigned int),a);}
unsigned int*daru_data(DynamicArrayu*d,size_t*s,size_t*c){return (unsigned int*)darv_data(d,s,c);}
unsigned int*daru_raw(DynamicArrayu*d){return (unsigned int*)darv_raw(d);}
bool daru_append(DynamicArrayu*d,size_t c,unsigned int*a){return darv_append(d,c,a);}
bool daru_insert(DynamicArrayu*d,size_t i,size_t c,unsigned int*a){return darv_insert(d,i,c,a);}
bool daru_set(DynamicArrayu*d,size_t i,size_t c,unsigned int*s){return darv_set(d,i,c,s);}
size_t daru_pop(DynamicArrayu*d,size_t i,size_t c,unsigned int*a){return darv_pop(d,i,c,a);}
size_t daru_sub(DynamicArrayu*d,size_t i,size_t c,unsigned int*a){return darv_sub(d,i,c,a);}
unsigned int daru_get(DynamicArrayu*d,size_t i){return *(unsigned int*)darv_get(d,i);}
bool daru_find(DynamicArrayu*d,const unsigned int*p,size_t*i){return darv_find(d,p,i);}
size_t daru_findall(DynamicArrayu*d,const unsigned int*p,size_t*i){return darv_findall(d,p,i);}
void daru_print(DynamicArrayu*d){dartg_print(d,unsigned int,"u","%u");}

/*----------------------------------------------------------------------------*/
// Function pointer aliases
void(*daru_del)(DynamicArrayu*)=darv_del;
size_t(*daru_len)(DynamicArrayu*)=darv_len;
size_t(*daru_size)(DynamicArrayu*)=darv_size;
bool(*daru_resize)(DynamicArrayu*, size_t)=darv_resize;
bool(*daru_swap)(DynamicArrayu*, size_t, size_t, size_t)=darv_swap;
bool(*daru_reverse)(DynamicArrayu*)=darv_reverse;
size_t(*daru_remove)(DynamicArrayu*, size_t, size_t)=darv_remove;
void(*daru_truncate)(DynamicArrayu*, size_t)=darv_truncate;
void(*daru_clear)(DynamicArrayu*)=darv_clear;


/*----------------------------------------------------------------------------*/
// Base type alias
typedef DynamicArray DynamicArraylu;

/*----------------------------------------------------------------------------*/
// Wrapped functions:
bool darlu_new(DynamicArraylu**d,size_t c,unsigned long*a){return dartg_new(d,c,sizeof(unsigned long),a);}
unsigned long*darlu_data(DynamicArraylu*d,size_t*s,size_t*c){return (unsigned long*)darv_data(d,s,c);}
unsigned long*darlu_raw(DynamicArraylu*d){return (unsigned long*)darv_raw(d);}
bool darlu_append(DynamicArraylu*d,size_t c,unsigned long*a){return darv_append(d,c,a);}
bool darlu_insert(DynamicArraylu*d,size_t i,size_t c,unsigned long*a){return darv_insert(d,i,c,a);}
bool darlu_set(DynamicArraylu*d,size_t i,size_t c,unsigned long*s){return darv_set(d,i,c,s);}
size_t darlu_pop(DynamicArraylu*d,size_t i,size_t c,unsigned long*a){return darv_pop(d,i,c,a);}
size_t darlu_sub(DynamicArraylu*d,size_t i,size_t c,unsigned long*a){return darv_sub(d,i,c,a);}
unsigned long darlu_get(DynamicArraylu*d,size_t i){return *(unsigned long*)darv_get(d,i);}
bool darlu_find(DynamicArraylu*d,const unsigned long*p,size_t*i){return darv_find(d,p,i);}
size_t darlu_findall(DynamicArraylu*d,const unsigned long*p,size_t*i){return darv_findall(d,p,i);}
void darlu_print(DynamicArraylu*d){dartg_print(d,unsigned long,"lu","%lu");}

/*----------------------------------------------------------------------------*/
// Function pointer aliases
void(*darlu_del)(DynamicArraylu*)=darv_del;
size_t(*darlu_len)(DynamicArraylu*)=darv_len;
size_t(*darlu_size)(DynamicArraylu*)=darv_size;
bool(*darlu_resize)(DynamicArraylu*, size_t)=darv_resize;
bool(*darlu_swap)(DynamicArraylu*, size_t, size_t, size_t)=darv_swap;
bool(*darlu_reverse)(DynamicArraylu*)=darv_reverse;
size_t(*darlu_remove)(DynamicArraylu*, size_t, size_t)=darv_remove;
void(*darlu_truncate)(DynamicArraylu*, size_t)=darv_truncate;
void(*darlu_clear)(DynamicArraylu*)=darv_clear;


/*----------------------------------------------------------------------------*/
// Base type alias
typedef DynamicArray DynamicArrayllu;

/*----------------------------------------------------------------------------*/
// Wrapped functions:
bool darllu_new(DynamicArrayllu**d,size_t c,unsigned long long*a){return dartg_new(d,c,sizeof(unsigned long long),a);}
unsigned long long*darllu_data(DynamicArrayllu*d,size_t*s,size_t*c){return (unsigned long long*)darv_data(d,s,c);}
unsigned long long*darllu_raw(DynamicArrayllu*d){return (unsigned long long*)darv_raw(d);}
bool darllu_append(DynamicArrayllu*d,size_t c,unsigned long long*a){return darv_append(d,c,a);}
bool darllu_insert(DynamicArrayllu*d,size_t i,size_t c,unsigned long long*a){return darv_insert(d,i,c,a);}
bool darllu_set(DynamicArrayllu*d,size_t i,size_t c,unsigned long long*s){return darv_set(d,i,c,s);}
size_t darllu_pop(DynamicArrayllu*d,size_t i,size_t c,unsigned long long*a){return darv_pop(d,i,c,a);}
size_t darllu_sub(DynamicArrayllu*d,size_t i,size_t c,unsigned long long*a){return darv_sub(d,i,c,a);}
unsigned long long darllu_get(DynamicArrayllu*d,size_t i){return *(unsigned long long*)darv_get(d,i);}
bool darllu_find(DynamicArrayllu*d,const unsigned long long*p,size_t*i){return darv_find(d,p,i);}
size_t darllu_findall(DynamicArrayllu*d,const unsigned long long*p,size_t*i){return darv_findall(d,p,i);}
void darllu_print(DynamicArrayllu*d){dartg_print(d,unsigned long long,"llu","%llu");}

/*----------------------------------------------------------------------------*/
// Function pointer aliases
void(*darllu_del)(DynamicArrayllu*)=darv_del;
size_t(*darllu_len)(DynamicArrayllu*)=darv_len;
size_t(*darllu_size)(DynamicArrayllu*)=darv_size;
bool(*darllu_resize)(DynamicArrayllu*, size_t)=darv_resize;
bool(*darllu_swap)(DynamicArrayllu*, size_t, size_t, size_t)=darv_swap;
bool(*darllu_reverse)(DynamicArrayllu*)=darv_reverse;
size_t(*darllu_remove)(DynamicArrayllu*, size_t, size_t)=darv_remove;
void(*darllu_truncate)(DynamicArrayllu*, size_t)=darv_truncate;
void(*darllu_clear)(DynamicArrayllu*)=darv_clear;


/*----------------------------------------------------------------------------*/
// Base type alias
typedef DynamicArray DynamicArrayc;

/*----------------------------------------------------------------------------*/
// Wrapped functions:
bool darc_new(DynamicArrayc**d,size_t c,char*a){return dartg_new(d,c,sizeof(char),a);}
char*darc_data(DynamicArrayc*d,size_t*s,size_t*c){return (char*)darv_data(d,s,c);}
char*darc_raw(DynamicArrayc*d){return (char*)darv_raw(d);}
bool darc_append(DynamicArrayc*d,size_t c,char*a){return darv_append(d,c,a);}
bool darc_insert(DynamicArrayc*d,size_t i,size_t c,char*a){return darv_insert(d,i,c,a);}
bool darc_set(DynamicArrayc*d,size_t i,size_t c,char*s){return darv_set(d,i,c,s);}
size_t darc_pop(DynamicArrayc*d,size_t i,size_t c,char*a){return darv_pop(d,i,c,a);}
size_t darc_sub(DynamicArrayc*d,size_t i,size_t c,char*a){return darv_sub(d,i,c,a);}
char darc_get(DynamicArrayc*d,size_t i){return *(char*)darv_get(d,i);}
bool darc_find(DynamicArrayc*d,const char*p,size_t*i){return darv_find(d,p,i);}
size_t darc_findall(DynamicArrayc*d,const char*p,size_t*i){return darv_findall(d,p,i);}
void darc_print(DynamicArrayc*d){dartg_print(d,char,"c","%c");}

/*----------------------------------------------------------------------------*/
// Function pointer aliases
void(*darc_del)(DynamicArrayc*)=darv_del;
size_t(*darc_len)(DynamicArrayc*)=darv_len;
size_t(*darc_size)(DynamicArrayc*)=darv_size;
bool(*darc_resize)(DynamicArrayc*, size_t)=darv_resize;
bool(*darc_swap)(DynamicArrayc*, size_t, size_t, size_t)=darv_swap;
bool(*darc_reverse)(DynamicArrayc*)=darv_reverse;
size_t(*darc_remove)(DynamicArrayc*, size_t, size_t)=darv_remove;
void(*darc_truncate)(DynamicArrayc*, size_t)=darv_truncate;
void(*darc_clear)(DynamicArrayc*)=darv_clear;


/*----------------------------------------------------------------------------*/
// Base type alias
typedef DynamicArray DynamicArrays;

/*----------------------------------------------------------------------------*/
// Wrapped functions:
bool dars_new(DynamicArrays**d,size_t c,char**a){return dartg_new(d,c,sizeof(char*),a);}
char**dars_data(DynamicArrays*d,size_t*s,size_t*c){return (char**)darv_data(d,s,c);}
char**dars_raw(DynamicArrays*d){return (char**)darv_raw(d);}
bool dars_append(DynamicArrays*d,size_t c,char**a){return darv_append(d,c,a);}
bool dars_insert(DynamicArrays*d,size_t i,size_t c,char**a){return darv_insert(d,i,c,a);}
bool dars_set(DynamicArrays*d,size_t i,size_t c,char**s){return darv_set(d,i,c,s);}
size_t dars_pop(DynamicArrays*d,size_t i,size_t c,char**a){return darv_pop(d,i,c,a);}
size_t dars_sub(DynamicArrays*d,size_t i,size_t c,char**a){return darv_sub(d,i,c,a);}
char* dars_get(DynamicArrays*d,size_t i){return *(char**)darv_get(d,i);}
bool dars_find(DynamicArrays*d,const char**p,size_t*i){return darv_find(d,p,i);}
size_t dars_findall(DynamicArrays*d,const char**p,size_t*i){return darv_findall(d,p,i);}
void dars_print(DynamicArrays*d){dartg_print(d,char*,"s","%s");}

/*----------------------------------------------------------------------------*/
// Function pointer aliases
void(*dars_del)(DynamicArrays*)=darv_del;
size_t(*dars_len)(DynamicArrays*)=darv_len;
size_t(*dars_size)(DynamicArrays*)=darv_size;
bool(*dars_resize)(DynamicArrays*, size_t)=darv_resize;
bool(*dars_swap)(DynamicArrays*, size_t, size_t, size_t)=darv_swap;
bool(*dars_reverse)(DynamicArrays*)=darv_reverse;
size_t(*dars_remove)(DynamicArrays*, size_t, size_t)=darv_remove;
void(*dars_truncate)(DynamicArrays*, size_t)=darv_truncate;
void(*dars_clear)(DynamicArrays*)=darv_clear;


/*----------------------------------------------------------------------------*/
// Base type alias
typedef DynamicArray DynamicArrayf;

/*----------------------------------------------------------------------------*/
// Wrapped functions:
bool darf_new(DynamicArrayf**d,size_t c,float*a){return dartg_new(d,c,sizeof(float),a);}
float*darf_data(DynamicArrayf*d,size_t*s,size_t*c){return (float*)darv_data(d,s,c);}
float*darf_raw(DynamicArrayf*d){return (float*)darv_raw(d);}
bool darf_append(DynamicArrayf*d,size_t c,float*a){return darv_append(d,c,a);}
bool darf_insert(DynamicArrayf*d,size_t i,size_t c,float*a){return darv_insert(d,i,c,a);}
bool darf_set(DynamicArrayf*d,size_t i,size_t c,float*s){return darv_set(d,i,c,s);}
size_t darf_pop(DynamicArrayf*d,size_t i,size_t c,float*a){return darv_pop(d,i,c,a);}
size_t darf_sub(DynamicArrayf*d,size_t i,size_t c,float*a){return darv_sub(d,i,c,a);}
float darf_get(DynamicArrayf*d,size_t i){return *(float*)darv_get(d,i);}
bool darf_find(DynamicArrayf*d,const float*p,size_t*i){return darv_find(d,p,i);}
size_t darf_findall(DynamicArrayf*d,const float*p,size_t*i){return darv_findall(d,p,i);}
void darf_print(DynamicArrayf*d){dartg_print(d,float,"f","%f");}

/*----------------------------------------------------------------------------*/
// Function pointer aliases
void(*darf_del)(DynamicArrayf*)=darv_del;
size_t(*darf_len)(DynamicArrayf*)=darv_len;
size_t(*darf_size)(DynamicArrayf*)=darv_size;
bool(*darf_resize)(DynamicArrayf*, size_t)=darv_resize;
bool(*darf_swap)(DynamicArrayf*, size_t, size_t, size_t)=darv_swap;
bool(*darf_reverse)(DynamicArrayf*)=darv_reverse;
size_t(*darf_remove)(DynamicArrayf*, size_t, size_t)=darv_remove;
void(*darf_truncate)(DynamicArrayf*, size_t)=darv_truncate;
void(*darf_clear)(DynamicArrayf*)=darv_clear;


/*----------------------------------------------------------------------------*/
// Base type alias
typedef DynamicArray DynamicArrayd;

/*----------------------------------------------------------------------------*/
// Wrapped functions:
bool dard_new(DynamicArrayd**d,size_t c,double*a){return dartg_new(d,c,sizeof(double),a);}
double*dard_data(DynamicArrayd*d,size_t*s,size_t*c){return (double*)darv_data(d,s,c);}
double*dard_raw(DynamicArrayd*d){return (double*)darv_raw(d);}
bool dard_append(DynamicArrayd*d,size_t c,double*a){return darv_append(d,c,a);}
bool dard_insert(DynamicArrayd*d,size_t i,size_t c,double*a){return darv_insert(d,i,c,a);}
bool dard_set(DynamicArrayd*d,size_t i,size_t c,double*s){return darv_set(d,i,c,s);}
size_t dard_pop(DynamicArrayd*d,size_t i,size_t c,double*a){return darv_pop(d,i,c,a);}
size_t dard_sub(DynamicArrayd*d,size_t i,size_t c,double*a){return darv_sub(d,i,c,a);}
double dard_get(DynamicArrayd*d,size_t i){return *(double*)darv_get(d,i);}
bool dard_find(DynamicArrayd*d,const double*p,size_t*i){return darv_find(d,p,i);}
size_t dard_findall(DynamicArrayd*d,const double*p,size_t*i){return darv_findall(d,p,i);}
void dard_print(DynamicArrayd*d){dartg_print(d,double,"d","%f");}

/*----------------------------------------------------------------------------*/
// Function pointer aliases
void(*dard_del)(DynamicArrayd*)=darv_del;
size_t(*dard_len)(DynamicArrayd*)=darv_len;
size_t(*dard_size)(DynamicArrayd*)=darv_size;
bool(*dard_resize)(DynamicArrayd*, size_t)=darv_resize;
bool(*dard_swap)(DynamicArrayd*, size_t, size_t, size_t)=darv_swap;
bool(*dard_reverse)(DynamicArrayd*)=darv_reverse;
size_t(*dard_remove)(DynamicArrayd*, size_t, size_t)=darv_remove;
void(*dard_truncate)(DynamicArrayd*, size_t)=darv_truncate;
void(*dard_clear)(DynamicArrayd*)=darv_clear;


/*----------------------------------------------------------------------------*/
// Base type alias
typedef DynamicArray DynamicArrayld;

/*----------------------------------------------------------------------------*/
// Wrapped functions:
bool darld_new(DynamicArrayld**d,size_t c,long double*a){return dartg_new(d,c,sizeof(long double),a);}
long double*darld_data(DynamicArrayld*d,size_t*s,size_t*c){return (long double*)darv_data(d,s,c);}
long double*darld_raw(DynamicArrayld*d){return (long double*)darv_raw(d);}
bool darld_append(DynamicArrayld*d,size_t c,long double*a){return darv_append(d,c,a);}
bool darld_insert(DynamicArrayld*d,size_t i,size_t c,long double*a){return darv_insert(d,i,c,a);}
bool darld_set(DynamicArrayld*d,size_t i,size_t c,long double*s){return darv_set(d,i,c,s);}
size_t darld_pop(DynamicArrayld*d,size_t i,size_t c,long double*a){return darv_pop(d,i,c,a);}
size_t darld_sub(DynamicArrayld*d,size_t i,size_t c,long double*a){return darv_sub(d,i,c,a);}
long double darld_get(DynamicArrayld*d,size_t i){return *(long double*)darv_get(d,i);}
bool darld_find(DynamicArrayld*d,const long double*p,size_t*i){return darv_find(d,p,i);}
size_t darld_findall(DynamicArrayld*d,const long double*p,size_t*i){return darv_findall(d,p,i);}
void darld_print(DynamicArrayld*d){dartg_print(d,long double,"ld","%Lf");}

/*----------------------------------------------------------------------------*/
// Function pointer aliases
void(*darld_del)(DynamicArrayld*)=darv_del;
size_t(*darld_len)(DynamicArrayld*)=darv_len;
size_t(*darld_size)(DynamicArrayld*)=darv_size;
bool(*darld_resize)(DynamicArrayld*, size_t)=darv_resize;
bool(*darld_swap)(DynamicArrayld*, size_t, size_t, size_t)=darv_swap;
bool(*darld_reverse)(DynamicArrayld*)=darv_reverse;
size_t(*darld_remove)(DynamicArrayld*, size_t, size_t)=darv_remove;
void(*darld_truncate)(DynamicArrayld*, size_t)=darv_truncate;
void(*darld_clear)(DynamicArrayld*)=darv_clear;
