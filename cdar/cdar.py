## INFO ########################################################################
##                                                                            ##
##                                   cutils                                   ##
##                                   ======                                   ##
##                                                                            ##
##                     Modern and Lightweight C Utilities                     ##
##                       Version: 0.8.72.026 (20140706)                       ##
##                                                                            ##
##                             File: cdar/cdar.py                             ##
##                                                                            ##
##           Designed and written by Peter Varo. Copyright (c) 2014           ##
##             License agreement is provided in the LICENSE file              ##
##                 For more info visit: http://www.cutils.org                 ##
##                                                                            ##
######################################################################## INFO ##

# Import Python modules
from sys import argv
from os import symlink
from shutil import copy




#------------------------------------------------------------------------------#
INFO = """
// INFO //
// Automatically Generated Type Specific
// Function Wrappers and Pointers
// For The Type Generic Dynamic Array (cdar)
// INFO //
"""

#------------------------------------------------------------------------------#
header = """
/*----------------------------------------------------------------------------*/
// Base type alias
typedef struct {{}} DynamicArray{1};

/*----------------------------------------------------------------------------*/
// Wrapped functions:
extern bool dar{1}_new(DynamicArray{1}**d,size_t c,{0}*a);
extern {0}*dar{1}_data(DynamicArray{1}*d,size_t*s,size_t*c);
extern {0}*dar{1}_raw(DynamicArray{1}*d);
extern bool dar{1}_append(DynamicArray{1}*d,size_t c,{0}*a);
extern bool dar{1}_insert(DynamicArray{1}*d,size_t i,size_t c,{0}*a);
extern bool dar{1}_set(DynamicArray{1}*d,size_t i,size_t c,{0}*s);
extern size_t dar{1}_pop(DynamicArray{1}*d,size_t i,size_t c,{0}*a);
extern size_t dar{1}_sub(DynamicArray{1}*d,size_t i,size_t c,{0}*a);
extern {0} dar{1}_get(DynamicArray{1}*d,size_t i);
extern bool dar{1}_find(DynamicArray{1}*d,const {0}*p,size_t*i);
extern size_t dar{1}_findall(DynamicArray{1}*d,const {0}*p,size_t*i);
extern void dar{1}_print(DynamicArray{1}*d);

/*----------------------------------------------------------------------------*/
// Function pointer aliases
extern void(*dar{1}_del)(DynamicArray{1}*d);
extern size_t(*dar{1}_len)(DynamicArray{1}*d);
extern size_t(*dar{1}_size)(DynamicArray{1}*d);
extern bool(*dar{1}_resize)(DynamicArray{1}*d,size_t c);
extern bool(*dar{1}_swap)(DynamicArray{1}*d,size_t i1,size_t i2, size_t c);
extern bool(*dar{1}_reverse)(DynamicArray{1}*d);
extern size_t(*dar{1}_remove)(DynamicArray{1}*d,size_t i,size_t c);
extern void(*dar{1}_truncate)(DynamicArray{1}*d,size_t i);
extern void(*dar{1}_clear)(DynamicArray{1}*d);
"""

#------------------------------------------------------------------------------#
source = """
/*----------------------------------------------------------------------------*/
// Base type alias
typedef DynamicArray DynamicArray{1};

/*----------------------------------------------------------------------------*/
// Wrapped functions:
bool dar{1}_new(DynamicArray{1}**d,size_t c,{0}*a){{return dartg_new(d,c,sizeof({0}),a);}}
{0}*dar{1}_data(DynamicArray{1}*d,size_t*s,size_t*c){{return ({0}*)darv_data(d,s,c);}}
{0}*dar{1}_raw(DynamicArray{1}*d){{return ({0}*)darv_raw(d);}}
bool dar{1}_append(DynamicArray{1}*d,size_t c,{0}*a){{return darv_append(d,c,a);}}
bool dar{1}_insert(DynamicArray{1}*d,size_t i,size_t c,{0}*a){{return darv_insert(d,i,c,a);}}
bool dar{1}_set(DynamicArray{1}*d,size_t i,size_t c,{0}*s){{return darv_set(d,i,c,s);}}
size_t dar{1}_pop(DynamicArray{1}*d,size_t i,size_t c,{0}*a){{return darv_pop(d,i,c,a);}}
size_t dar{1}_sub(DynamicArray{1}*d,size_t i,size_t c,{0}*a){{return darv_sub(d,i,c,a);}}
{0} dar{1}_get(DynamicArray{1}*d,size_t i){{return *({0}*)darv_get(d,i);}}
bool dar{1}_find(DynamicArray{1}*d,const {0}*p,size_t*i){{return darv_find(d,p,i);}}
size_t dar{1}_findall(DynamicArray{1}*d,const {0}*p,size_t*i){{return darv_findall(d,p,i);}}
void dar{1}_print(DynamicArray{1}*d){{dartg_print(d,{0},"{1}","%{2}");}}

/*----------------------------------------------------------------------------*/
// Function pointer aliases
void(*dar{1}_del)(DynamicArray{1}*)=darv_del;
size_t(*dar{1}_len)(DynamicArray{1}*)=darv_len;
size_t(*dar{1}_size)(DynamicArray{1}*)=darv_size;
bool(*dar{1}_resize)(DynamicArray{1}*, size_t)=darv_resize;
bool(*dar{1}_swap)(DynamicArray{1}*, size_t, size_t, size_t)=darv_swap;
bool(*dar{1}_reverse)(DynamicArray{1}*)=darv_reverse;
size_t(*dar{1}_remove)(DynamicArray{1}*, size_t, size_t)=darv_remove;
void(*dar{1}_truncate)(DynamicArray{1}*, size_t)=darv_truncate;
void(*dar{1}_clear)(DynamicArray{1}*)=darv_clear;
"""

#------------------------------------------------------------------------------#
types = (('int'               , 'i'  , 'd'  ),
         ('long'              , 'li' , 'li' ),
         ('long long'         , 'lli', 'lld'),
         ('unsigned int'      , 'u'  , 'u'  ),
         ('unsigned long'     , 'lu' , 'lu' ),
         ('unsigned long long', 'llu', 'llu'),
         ('char'              , 'c'  , 'c'  ),
         ('char*'             , 's'  , 's'  ),
         ('float'             , 'f'  , 'f'  ),
         ('double'            , 'd'  , 'f'  ),
         ('long double'       , 'ld' ,  'Lf'))

#------------------------------------------------------------------------------#
NEWLINE = '{:<79}\\'
METHOD = 'dar{}_{}'
DEFINE = '#define {}{} _Generic(({}),'
ARGS = '({})'

methods = (('new'        , ('ptr_dar_ptr', 'count', 'data_ptr')     ),
           ('del'        , ('dar_ptr',)                             ),
           ('data'       , ('dar_ptr', 'size_ptr', 'count_ptr')     ),
           ('raw'        , ('dar_ptr',)                             ),
           ('len'        , ('dar_ptr',)                             ),
           ('size'       , ('dar_ptr',)                             ),
           ('resize'     , ('dar_ptr', 'count')                     ),
           ('swap'       , ('dar_ptr', 'index1', 'index2', 'count') ),
           ('reverse'    , ('dar_ptr',)                             ),
           ('append'     , ('dar_ptr', 'count', 'data_ptr')         ),
           ('insert'     , ('dar_ptr', 'index', 'count', 'data_ptr')),
           ('remove'     , ('dar_ptr', 'index', 'count')            ),
           ('pop'        , ('dar_ptr', 'index', 'count', 'dest_ptr')),
           ('sub'        , ('dar_ptr', 'index', 'count', 'dest_ptr')),
           ('truncate'   , ('dar_ptr', 'index')                     ),
           ('set'        , ('dar_ptr', 'index', 'count', 'data_ptr')),
           ('get'        , ('dar_ptr', 'index')                     ),
           ('clear'      , ('dar_ptr',)                             ),
           # ('reversesub' , '(dar_ptr, index, count, data_ptr)' ),
           ('find'       , ('dar_ptr', 'item_ptr', 'index_ptr')     ),
           ('findall'    , ('dar_ptr', 'item_ptr', 'indices_ptr')   ),
           ('sort'       , ('dar_ptr', 'cmp_func')                  ),
           ('sortsub'    , ('dar_ptr', 'index', 'count', 'cmp_func')),
           ('print'      , ('dar_ptr', 'callback')                  ),
           ('print'      , ('dar_ptr',)                            ))

_GENERIC = """
#define {macro}({args}) _Generic(({check}),
    {types})({args})
"""

#------------------------------------------------------------------------------#
if __name__ == '__main__':
    GUARD = '_DYNAMIC_ARRAY_INTERFACE_H_'
    # Lists for lines
    definition = [INFO,
                  '#include "darv.h"',
                  """
/*----------------------------------------------------------------------------*/
// Wrapped function:
bool darv_new(DynamicArray**d,size_t c,void*a){return dartg_new(d,c,sizeof(void*),a);}
void darv_print(DynamicArray*d){dartg_print(d,char*,"","%p");}
"""]
    interface  = [INFO,
                  '#ifndef ' + GUARD,
                  '#define ' + GUARD,
                  '\n#include "darv.h"']

    # Build source
    for full, suff, form in types:
        interface.append(header.format(full, suff))
        definition.append(source.format(full, suff, form))

    # Build header
    interface.append("""\
/*----------------------------------------------------------------------------*/
// Interfaces""")
    DYNARR = '{}DynamicArray'.format(' '*4)
    asteriks = '*'
    ARGCOUNT = '#define GET_MACRO_BY_ARG{}_COUNT({}, MACRO_NAME, ...) MACRO_NAME\n'
    COUNTED  = '#define {}(...) GET_MACRO_BY_ARG{}_COUNT(__VA_ARGS__, {})(__VA_ARGS__)'
    method_args = {}
    for method, args in methods:
        try:
            l = len(args)
            method_args[method].update(l)
        except:
            method_args[method] = {l}
        arguments = ARGS.format(', '.join(args))
        ptr = asteriks + '*' if method == 'new' else asteriks
        default = METHOD.format('v', method)
        interface.append(NEWLINE.format(DEFINE.format(method + str(l), arguments, args[0])))
        for full, suff, form in types:
            name = METHOD.format(suff, method)
            interface.append(NEWLINE.format('{}{:<5}: {},'.format(DYNARR, suff + ptr, name)))
        interface.append('{}{:<5}: {}){}\n\n'.format(DYNARR, ptr, default, arguments))
    maxargs = 5
    for i in range(1, maxargs + 1):
        interface.append(ARGCOUNT.format(i, ', '.join('_' + str(i) for i in range(1, i + 1))))
    for method, args in methods:
        x = max(method_args[method])
        interface.append(COUNTED.format(method, x, ', '.join(method + str(i) for i in range(x, 0, -1))))
    interface.append('\n#endif // ' + GUARD + '\n')

    # Write files
    with open('cdar.h', 'w') as h:
        h.write('\n'.join(interface))
    with open('cdar.c', 'w') as c:
        c.write('\n'.join(definition))
