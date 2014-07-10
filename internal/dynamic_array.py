## INFO ########################################################################
##                                                                            ##
##                                   cutils                                   ##
##                                   ======                                   ##
##                                                                            ##
##                     Modern and Lightweight C Utilities                     ##
##                       Version: 0.8.72.310 (20140710)                       ##
##                                                                            ##
##                      File: internal/dynamic_array.py                       ##
##                                                                            ##
##           Designed and written by Peter Varo. Copyright (c) 2014           ##
##             License agreement is provided in the LICENSE file              ##
##                 For more info visit: http://www.cutils.org                 ##
##                                                                            ##
######################################################################## INFO ##

# Import Python modules
from os.path import (dirname as os_path_dirname,
                     join as os_path_join)

# Import cutils modules
from generator import args, methods

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
GUARD = 'DYNAMIC_ARRAY'
# ??? Can't this be like just: cutils_cdar_void_ptr_(new|del|data|...) ???
PROTO = 'cutils_cdar_DynamicArray_void_ptr'
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
         # ('void*'             , 'p'  ))

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
WRAPPERS = (
    # new
    ('bool', 'new',
     args(('{0}_{1}**', 'd', 'size_t', 'c', '{2}*', 'a')),
     'return {3}_{5}(d,c,sizeof({2}),a);'),

    # data
    ('{2}*', 'data',
     args(('{0}_{1}*', 'd', 'size_t*', 's', 'size_t*', 'c')),
     'return {3}_{5}({6.names});'),

    # raw
    ('{2}*', 'raw',
     args(('{0}_{1}*', 'd')),
     'return ({2}*){3}_{5}({6.names});'),

    # append
    ('bool', 'append',
     args(('{0}_{1}*', 'd', 'size_t', 'c', '{2}*', 'a')),
     'return {3}_{5}({6.names});'),

    # push
    ('bool', 'push',
     args(('{0}_{1}*', 'd', 'size_t', 'i', 'size_t', 'c', '{2}*', 'a')),
     'return {3}_{5}({6.names});'),

    # set
    ('bool', 'set',
     args(('{0}_{1}*', 'd', 'size_t', 'i', 'size_t', 'c', '{2}*', 's')),
     'return {3}_{5}({6.names});'),

    # pop
    ('size_t', 'pop',
     args(('{0}_{1}*', 'd', 'size_t', 'i', 'size_t', 'c', '{2}*', 'a')),
     'return {3}_{5}({6.names});'),

    # sub
    ('size_t', 'sub',
     args(('{0}_{1}*', 'd', 'size_t', 'i', 'size_t', 'c', '{2}*', 'a')),
     'return {3}_{5}({6.names});'),

    # get
    ('{2}', 'get',
     args(('{0}_{1}*', 'd', 'size_t', 'i')),
     'return *({2}*){3}_{5}({6.names});'),

    # find
    ('bool', 'find',
     args(('{0}_{1}*', 'd', 'const {2}*', 'p', 'size_t*', 'i')),
     'return {3}_{5}({6.names});'),

    # findall
    ('size_t', 'findall',
     args(('{0}_{1}*', 'd', 'const {2}*', 'p', 'size_t*', 'i')),
     'return {3}_{5}({6.names});'),

    # # print
    # ('void', 'print',args(('{0}_{1}*', 'd')),
    #  'return {3}_{5}(d);'),
)

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
POINTERS = (
    # del
    ('void', 'del',
     args(('{0}_{1}*', 'd')),
     '{3}_{5}'),

    # len
    ('size_t', 'len',
     args(('{0}_{1}*', 'd')),
     '{3}_{5}'),

    # size
    ('size_t', 'size',
     args(('{0}_{1}*', 'd')),
     '{3}_{5}'),

    # resize
    ('bool', 'resize',
     args(('{0}_{1}*', 'd', 'size_t', 's')),
     '{3}_{5}'),

    # swap
    ('bool', 'swap',
     args(('{0}_{1}*', 'd', 'size_t', 'i1', 'size_t', 'i2', 'size_t', 'c')),
     '{3}_{5}'),

    # reverse
    ('bool', 'reverse',
     args(('{0}_{1}*', 'd')),
     '{3}_{5}'),

    # pull
    ('size_t', 'pull',
     args(('{0}_{1}*', 'd', 'size_t', 'i', 'size_t', 'c')),
     '{3}_{5}'),

    # truncate
    ('void', 'truncate',
     args(('{0}_{1}*', 'd', 'size_t', 'i')),
     '{3}_{5}'),

    # clear
    ('void', 'clear',
     args(('{0}_{1}*', 'd')),
     '{3}_{5}'),
)

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
PRINTERS = (
)
"""
void dar{1}_print(DynamicArray{1}*d){{dartg_print(d,{0},"{1}","%{2}");}}
"""

#------------------------------------------------------------------------------#
if __name__ == '__main__':
    folder = os_path_dirname(os_path_dirname(__file__))
    methods(types=TYPES,
            guard=GUARD,
            base_name=ARRAY,
            prototype=PROTO,
            wrappers=WRAPPERS,
            pointers=POINTERS,
            proto_header='dynamic_array.h',
            proto_source='dynamic_array.c',
            output_header=os_path_join(folder, 'cdar.h'),
            output_source=os_path_join(folder, 'cdar.c'),
            includes=('<stddef.h>   /* ptrdiff_t */',))
            # ,print_generic=True)
