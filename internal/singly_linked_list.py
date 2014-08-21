## INFO ########################################################################
##                                                                            ##
##                                   cutils                                   ##
##                                   ======                                   ##
##                                                                            ##
##                     Modern and Lightweight C Utilities                     ##
##                       Version: 0.8.90.618 (20140820)                       ##
##                                                                            ##
##                    File: internal/singly_linked_list.py                    ##
##                                                                            ##
##           Designed and written by Peter Varo. Copyright (c) 2014           ##
##             License agreement is provided in the LICENSE file              ##
##                 For more info visit: http://www.cutils.org                 ##
##                                                                            ##
######################################################################## INFO ##

# Import Python modules
from os.path import join as os_path_join

# Import cutils modules
from generator import fp, args, methods

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
GUARD = 'SINGLY_LINKED_LIST', '35118355245711974'
PROTO = 'void_ptr'
LLIST = 'cutils_csll_SinglyLinkedList'

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
TYPES = (('char'              , 'c'  ),
         ('signed char'       , 'd'  ),
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
SUPPORTS = ('{0}_{1}_iterator', 'SLLNode'),

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
ARG1_T = '{0}_{1}*'
ARG1_N = 'l'

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
_RETURN = 'return {0}_{4}_{6}({7.names});'
WRAPPERS = (
    # new
    ('bool', 'new',
     args(ARG1_T + '*', ARG1_N, 'size_t', 'c', '{2}*', 'a'),
     'return {0}_{4}_{6}(l,sizeof({2}),c,a);'),

    # iter
    (SUPPORTS[0][0] + '*', 'iter',
     args(ARG1_T, ARG1_N),
     _RETURN),

    # next
    ('bool', 'next',
     args(SUPPORTS[0][0] + '*', 'i', '{2}**', 'p'),
     _RETURN),

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
    # FIXME: try to make both find and findall type-safe
    #        by replacing the const void* to type specific pointer
    #        the main problem is, cannot pass
    #        bool(*)(const type*,...) --> bool(*)(const void*,...)
     args(ARG1_T, ARG1_N, fp('bool', 'f', 'const void*', 'const void*', 'size_t'),
          'const void*', 'p', 'size_t*', 'i'),
     _RETURN,
    # singles: 0:object_type_name
    # doubles: 0:base_name, 1:sub_type_name, 2:func_name
     '{0}:{{0}}_{{1}}_{{2}}(\\\n'
     '        ({0})object,\\\n'
     '        {{0}}_{{1}}_compare,##__VA_ARGS__)'),

    # findall
    ('size_t', 'findall',
     args(ARG1_T, ARG1_N, fp('bool', 'f', 'const void*', 'const void*', 'size_t'),
          'const void*', 'p', 'size_t*', 'i'),
     _RETURN,
    # singles: 0:object_type_name
    # doubles: 0:base_name, 1:sub_type_name, 2:func_name
     '{0}:{{0}}_{{1}}_{{2}}(\\\n'
     '        ({0})object,\\\n'
     '        {{0}}_{{1}}_compare,##__VA_ARGS__)'),

    # format
    # TODO: is there a way to make this inline?
    ('bool', 'format',
    # TODO: change this const void* --> const {2}* ?
     args('const {2}*', 'i', 'char**', 'b', 'size_t*', 's'),
    # TODO: add all suffixes of numbers (eg.: unsigned long long 1ull)
    #       and update the examples of the documentation
     {'bool': 'snprintf(*b,*s,"%s",*i?"true":"false");return true;',
      'char': 'cutils_fmtc_repr(*b,*s,i,1);return true;',
      'char*': 'size_t l=strlen(*i);if(*s<l+3)if(!(*b=realloc(*b,(*s=l*2+3))))\n'
               'return false;cutils_fmtc_repr(*b,*s,*i,l);return true;',
      'default': 'snprintf(*b,*s,"%{3}",*i);return true;'},
     NotImplemented),

    # compare
    # TODO: is there a way to make this inline?
    ('bool', 'compare',
     args('const void*', 'p1', 'const void*', 'p2', 'size_t', 's'),
     {'float': 'return cutils_fcmp_float_compare(*(float*)p1,*(float*)p2);',
      'double': 'return cutils_fcmp_double_compare(*(double*)p1,*(double*)p2);',
      'long double': 'return cutils_fcmp_long_double_compare('
                     '*(long double*)p1,*(long double*)p2);',
      'default': 'return !memcmp(p1,p2,s);'},
     NotImplemented),
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


    # map
    ('void', 'map',
     args(ARG1_T, ARG1_N, 'size_t', 'i', 'size_t', 'c',
          fp('void', 'f', 'size_t', '{2}*')),
     _FUNCTION),

    # print
    # TODO: is there a way to make this inline?
    ('void', 'print',
     args(ARG1_T, ARG1_N, 'FILE*', 's', 'const char*', 'n',
          fp('bool', 'f')),
     _FUNCTION,
    # singles: 0:object_type_name
    # doubles: 0:base_name, 1:sub_type_name, 2:func_name
     '{0}:{{0}}_{{1}}_{{2}}(\\\n'
     '        ({0})object,stdout,"{{1}}",\\\n'
     '        {{0}}_{{1}}_format,##__VA_ARGS__)')
)


#------------------------------------------------------------------------------#
def generate(folder, macros_dict):
    methods(types=TYPES,
            guard=GUARD,
            sub_typed=True,
            base_name=LLIST,
            prototype=PROTO,
            supports=SUPPORTS,
            wrappers=WRAPPERS,
            pointers=POINTERS,
            proto_header='singly_linked_list.h',
            proto_source='singly_linked_list.c',
            output_header=os_path_join(folder, 'csll.h'),
            output_source=os_path_join(folder, 'csll.c'),
            includes=('<stddef.h>         /* ptrdiff_t */',
                      '<string.h>         /* strlen(), strncpy() */',
                      '"internal/fmtc.h"  /* cutils_fmtc_repr */',
                      '"internal/fcmp.h"  /* cutils_fcmp_compare */'),
            macros_dict=macros_dict)
