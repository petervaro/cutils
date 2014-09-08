## INFO ########################################################################
##                                                                            ##
##                                   cutils                                   ##
##                                   ======                                   ##
##                                                                            ##
##                     Modern and Lightweight C Utilities                     ##
##                       Version: 0.8.96.140 (20140907)                       ##
##                                                                            ##
##                     File: internal/static_hash_map.py                      ##
##                                                                            ##
##           Designed and written by Peter Varo. Copyright (c) 2014           ##
##             License agreement is provided in the LICENSE file              ##
##                 For more info visit: http://www.cutils.org                 ##
##                                                                            ##
######################################################################## INFO ##

# Import Python modules
import os.path
import itertools

# Import cutils modules
from types import C_TYPES
from generator import methods, Function

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
GUARD  = 'STATIC_HASH_MAP', '18841687438603127'
PROTO = 'void*', 'void*'
HASHM  = 'StaticHashMap'
PREFIX = 'cutils_cshm'

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
SUPPORTS = (('iterator', 'SHMIterator'),)

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
INCLUDES_H = ('<stddef.h>   /* size_t */',)
INCLUDES_C = ('<stddef.h>         /* size_t, ptrdiff_t */',
              '<string.h>         /* memcmp() */',
              '"internal/fcmp.h"  /* cutils_fcmp_compare */')

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
_RETURN_DEF = 'return {ORIGINAL}({ARGUMENTS});'



#------------------------------------------------------------------------------#
new_ = Function('new', 'bool', ('{MAINTYPE}**', 'h'),
                               ('size_t',       'c'))
new_.wrapping = _RETURN_DEF
new_.original = 2

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
del_ = Function('del', 'void', ('{MAINTYPE}*', 'h'))
del_.pointing = '{ORIGINAL}'
del_.original = 1

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
add_ = Function('add', 'bool', ('{MAINTYPE}*',      'h'),
                               Function('f', 'bool', ('const void*', 'p1'),
                                                     ('const void*', 'p2'),
                                                     ('size_t',      's')),
                               ('const {SUBTYPE_1}*', 'k'),
                               ('const {SUBTYPE_2}*', 'v'))
add_.wrapping = 'return {ORIGINAL}(h,f,sizeof({SUBTYPE_1}),sizeof({SUBTYPE_2}),k,v);'
add_.defaults = {'_default3': ('f', 'return {WRAPPED}(h,{MAINTYPE}_compare,'
                                    'sizeof({SUBTYPE_1}),sizeof({SUBTYPE_2}),k,v);')}
add_.original = 6
add_.original_defaults = {'_default5': 5}

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
get_ = Function('get', '{SUBTYPE_2}', ('{MAINTYPE}*',      'h'),
                                       Function('f', 'bool', ('const void*', 'p1'),
                                                             ('const void*', 'p2'),
                                                             ('size_t',      's')),
                                      ('size_t',           's'),
                                      ('const {SUBTYPE_1}*', 'k'))
get_.wrapping = 'return *({SUBTYPE_2}*){ORIGINAL}({ARGUMENTS});'
get_.defaults = {'_default3': ('f', 'return *({SUBTYPE_2}*){WRAPPED}(h,'
                                    '{MAINTYPE}_compare,s,k);')}
get_.original = 4
get_.original_defaults = {'_default3': 3}

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
iter_ = Function('iter', '{SUPPORT_TYPE_1}*', ('{MAINTYPE}*', 'h'))
iter_.wrapping = _RETURN_DEF
iter_.original = 1

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
iter_del_ = Function('del', 'void', ('{SUPPORT_TYPE_1}*', 'i'), supported='{SUPPORT_1}')
iter_del_.pointing = '{ORIGINAL}'
iter_del_.original = 1

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
iter_next_ = Function('next', 'bool', ('{SUPPORT_TYPE_1}*',  'i'),
                                      ('{SUBTYPE_1}**', 'k'), supported='{SUPPORT_1}')
iter_next_.wrapping = _RETURN_DEF
iter_next_.original = 2

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
iter_values_ = Function('values', 'bool', ('{SUPPORT_TYPE_1}*',  'i'),
                                          ('{SUBTYPE_2}**', 'v'), supported='{SUPPORT_1}')
iter_values_.wrapping = _RETURN_DEF
iter_values_.original = 2

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
iter_items_ = Function('items', 'bool', ('{SUPPORT_TYPE_1}*',  'i'),
                                        ('{SUBTYPE_1}**', 'k'),
                                        ('{SUBTYPE_2}**', 'v'), supported='{SUPPORT_1}')
iter_items_.wrapping = _RETURN_DEF
iter_items_.original = 3

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
compare_ = Function('compare', 'bool', ('const void*', 'p1'),
                                       ('const void*', 'p2'),
                                       ('size_t',      's'))
compare_.wrapping = {'float': 'return cutils_fcmp_float_compare(*(float*)p1,*(float*)p2);',
                     'double': 'return cutils_fcmp_double_compare(*(double*)p1,*(double*)p2);',
                     'long double': 'return cutils_fcmp_long_double_compare('
                                    '*(long double*)p1,*(long double*)p2);',
                     'default': 'return !memcmp(p1,p2,s);'}
compare_.generics = NotImplemented

#------------------------------------------------------------------------------#
def generate(folder, macros_dict):
    methods(base_name=HASHM,
            base_type=PROTO,
            module_prefix=PREFIX,
            sub_types=C_TYPES,
            combine_sub_types=lambda t: itertools.product(t, repeat=2),
            support_types=SUPPORTS,
            guard=GUARD,
            base_header='static_hash_map.h',
            base_source='static_hash_map.c',
            output_header=os.path.join(folder, 'cshm.h'),
            output_source=os.path.join(folder, 'cshm.c'),
            macros_dict=macros_dict,
            includes_header=INCLUDES_H,
            includes_source=INCLUDES_C,
            functions=(new_, del_, add_, get_, iter_, iter_del_, iter_next_,
                       iter_values_, iter_items_, compare_))
