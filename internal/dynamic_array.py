## INFO ########################################################################
##                                                                            ##
##                                   cutils                                   ##
##                                   ======                                   ##
##                                                                            ##
##                     Modern and Lightweight C Utilities                     ##
##                       Version: 0.8.72.577 (20140719)                       ##
##                                                                            ##
##                      File: internal/dynamic_array.py                       ##
##                                                                            ##
##           Designed and written by Peter Varo. Copyright (c) 2014           ##
##             License agreement is provided in the LICENSE file              ##
##                 For more info visit: http://www.cutils.org                 ##
##                                                                            ##
######################################################################## INFO ##

# Import Python modules
from os.path import join as os_path_join

# Import cutils modules
from generator import fp, args, methods, VARGS

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
GUARD = 'DYNAMIC_ARRAY'
# ??? Can't this be like just: cutils_cdar_void_ptr_(new|del|data|...) ???
PROTO = 'void_ptr'
ARRAY = 'cutils_cdar_DynamicArray'

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
TYPES = (('char'              , 'c'  ),
         ('signed char'       , 'c'  ),
         ('unsigned char'     , 'u'  ),
         ('char*'             , 's'  ),
         ('short'             , 'hd' ),
         ('unsigned short'    , 'hu' ),
         ('int'               , 'd'  ),
         ('unsigned int'      , 'u'  ),
         ('long'              , 'ld' ),
         ('unsigned long'     , 'lu' ),
         ('long long'         , 'lld'),
         ('unsigned long long', 'llu'),
         ('float'             , 'f'  ),
         ('double'            , 'lf' ),
         ('long double'       , 'Lf' ),
         ('bool'              , 'd'  ),
         ('size_t'            , 'zu' ),
         ('ptrdiff_t'         , 'td' ))

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
ARG1_T = '{0}_{1}*'
ARG1_N = 'd'

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
_RETURN = 'return {0}_{4}_{6}({7.names});'
WRAPPERS = (
    # new
    ('bool', 'new',
     args(ARG1_T + '*', ARG1_N, 'size_t', 'c', '{2}*', 'a'),
     'return {0}_{4}_{6}(d,sizeof({2}),c,a);'),

    # data
    ('{2}*', 'data',
     args(ARG1_T, ARG1_N, 'size_t*', 's', 'size_t*', 'c'),
     _RETURN),

    # raw
    ('{2}*', 'raw',
     args(ARG1_T, ARG1_N),
     'return ({2}*){0}_{4}_{6}({7.names});'),

    # append
    ('bool', 'append',
     args(ARG1_T, ARG1_N, 'size_t', 'c', '{2}*', 'a'),
     _RETURN),

    # push
    ('bool', 'push',
     args(ARG1_T, ARG1_N, 'size_t', 'i', 'size_t', 'c', '{2}*', 'a'),
     _RETURN),

    # set
    ('bool', 'set',
     args(ARG1_T, ARG1_N, 'size_t', 'i', 'size_t', 'c', '{2}*', 's'),
     _RETURN),

    # pop
    ('size_t', 'pop',
     args(ARG1_T, ARG1_N, 'size_t', 'i', 'size_t', 'c', '{2}*', 'a'),
     _RETURN),

    # sub
    ('size_t', 'sub',
     args(ARG1_T, ARG1_N, 'size_t', 'i', 'size_t', 'c', '{2}*', 'a'),
     _RETURN),

    # get
    ('{2}', 'get',
     args(ARG1_T, ARG1_N, 'size_t', 'i'),
     'return *({2}*){0}_{4}_{6}({7.names});'),

    # find
    ('bool', 'find',
     args(ARG1_T, ARG1_N, 'const {2}*', 'p', 'size_t*', 'i'),
     _RETURN),

    # findall
    ('size_t', 'findall',
     args(ARG1_T, ARG1_N, 'const {2}*', 'p', 'size_t*', 'i'),
     _RETURN),

    # format
    # TODO: how make it inline?
    ('char*', 'format',
     args('const void*', 'i', 'char**', 'b', 'size_t*', 's'),
     {'bool': 'snprintf(*b,*s,"%s",(*({2}*)i)?"true":"false");return *b;',
      'char': 'snprintf(*b,*s,"\'%{3}\'",*({2}*)i);return *b;',
      'char*': 'snprintf(*b,*s,"\\"%{3}\\"",*({2}*)i);return *b;',
      'default': 'snprintf(*b,*s,"%{3}",*({2}*)i);return *b;'},
      NotImplemented)
)


#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
_FUNCTION = '{0}_{4}_{6}'
POINTERS = (
    # del
    ('void', 'del',
     args(ARG1_T, ARG1_N),
     _FUNCTION),

    # len
    ('size_t', 'len',
     args(ARG1_T, ARG1_N),
     _FUNCTION),

    # size
    ('size_t', 'size',
     args(ARG1_T, ARG1_N),
     _FUNCTION),

    # resize
    ('bool', 'resize',
     args(ARG1_T, ARG1_N, 'size_t', 's'),
     _FUNCTION),

    # swap
    ('bool', 'swap',
     args(ARG1_T, ARG1_N, 'size_t', 'i1', 'size_t', 'i2', 'size_t', 'c'),
     _FUNCTION),

    # reverse
    ('bool', 'reverse',
     args(ARG1_T, ARG1_N),
     _FUNCTION),

    # pull
    ('size_t', 'pull',
     args(ARG1_T, ARG1_N, 'size_t', 'i', 'size_t', 'c'),
     _FUNCTION),

    # truncate
    ('void', 'truncate',
     args(ARG1_T, ARG1_N, 'size_t', 'i'),
     _FUNCTION),

    # clear
    ('void', 'clear',
     args(ARG1_T, ARG1_N),
     _FUNCTION),

    # print
    # TODO: how make it inline?
    ('void', 'print',
     args(ARG1_T, ARG1_N, 'FILE*', 's', 'const char*', 'n',
          fp('char*', 'f', 'const void*', 'char**', 'size_t*')),
     _FUNCTION,
    # singles: 0:object_type_name
    # doubles: 0:base_name, 1:sub_type_name, 2:func_name
     '{0}:{{0}}_{{1}}_{{2}}(\\\n'
     '        ({0})object,stdout,"DynamicArray_{{1}}",\\\n'
     '        {{0}}_{{1}}_format,##__VA_ARGS__)')
)


#------------------------------------------------------------------------------#
def generate(folder, macros_dict):
    methods(types=TYPES,
            guard=GUARD,
            sub_typed=True,
            base_name=ARRAY,
            prototype=PROTO,
            wrappers=WRAPPERS,
            pointers=POINTERS,
            proto_header='dynamic_array.h',
            proto_source='dynamic_array.c',
            output_header=os_path_join(folder, 'cdar.h'),
            output_source=os_path_join(folder, 'cdar.c'),
            includes=('<stddef.h>   /* ptrdiff_t */',),
            macros_dict=macros_dict)
