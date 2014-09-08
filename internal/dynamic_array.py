## INFO ########################################################################
##                                                                            ##
##                                   cutils                                   ##
##                                   ======                                   ##
##                                                                            ##
##                     Modern and Lightweight C Utilities                     ##
##                       Version: 0.8.95.968 (20140904)                       ##
##                                                                            ##
##                      File: internal/dynamic_array.py                       ##
##                                                                            ##
##           Designed and written by Peter Varo. Copyright (c) 2014           ##
##             License agreement is provided in the LICENSE file              ##
##                 For more info visit: http://www.cutils.org                 ##
##                                                                            ##
######################################################################## INFO ##

# Import Python modules
import os.path

# Import cutils modules
from types import C_TYPES
from generator import methods, Function

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
GUARD = 'DYNAMIC_ARRAY', '2427147457128005'
PROTO = 'void*'
ARRAY = 'DynamicArray'
PREFIX = 'cutils_cdar'

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
INCLUDES_H = ('<stddef.h>   /* ptrdiff_t */',)
INCLUDES_C = ('<stddef.h>         /* ptrdiff_t */',
              '<string.h>         /* strlen() */',
              '"internal/fmtc.h"  /* cutils_fmtc_repr */',
              '"internal/fcmp.h"  /* cutils_fcmp_compare */')

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
_RETURN_DEF = 'return {ORIGINAL}({ARGUMENTS});'



#------------------------------------------------------------------------------#
new_ = Function('new', 'bool', ('{MAINTYPE}**', 'd'),
                               ('size_t',       'c'),
                               ('{SUBTYPE}*',   'a'))
new_.wrapping = 'return {ORIGINAL}(d,sizeof({SUBTYPE}),c,a);'
new_.defaults = {'_default2': ('a', 'return {WRAPPED}(d,sizeof({SUBTYPE}),c,NULL);'),
                 '_default1': ('c', 'a', 'return {WRAPPED}(d,sizeof({SUBTYPE}),0,NULL);')}
new_.original = 4
new_.original_defaults = {'_default2': 2,
                          '_default3': 3}

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
del_ = Function('del', 'void', ('{MAINTYPE}*', 'd'))
del_.pointing = '{ORIGINAL}'
del_.original = 1

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
data_ = Function('data', '{SUBTYPE}*', ('{MAINTYPE}*', 'd'),
                                       ('size_t*',     's'),
                                       ('size_t*',     'c'))
data_.wrapping = _RETURN_DEF
data_.original = 3

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
len_ = Function('len', 'size_t', ('{MAINTYPE}*', 'd'))
len_.pointing = '{ORIGINAL}'
len_.original = 1

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
size_ = Function('size', 'size_t', ('{MAINTYPE}*', 'd'))
size_.pointing = '{ORIGINAL}'
size_.original = 1

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
raw_ = Function('raw', '{SUBTYPE}*', ('{MAINTYPE}*', 'd'))
raw_.wrapping = 'return ({SUBTYPE}*){ORIGINAL}({ARGUMENTS});'
raw_.original = 1

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
resize_ = Function('resize', 'bool', ('{MAINTYPE}*', 'd'),
                                     ('size_t',      'c'))
resize_.pointing = '{ORIGINAL}'
resize_.original = 2

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
truncate_ = Function('truncate', 'void', ('{MAINTYPE}*', 'd'),
                                         ('size_t',      'i'))
truncate_.pointing = '{ORIGINAL}'
truncate_.defaults = {'_default1': ('i', 'return {WRAPPED}(d,0);')}
truncate_.original = 2
truncate_.original_defaults = {'_default1': 1}

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
clear_ = Function('clear', 'void', ('{MAINTYPE}*', 'd'))
clear_.pointing = '{ORIGINAL}'
clear_.original = 1

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
swap_ = Function('swap', 'bool', ('{MAINTYPE}*', 'd'),
                                 ('size_t',      'i1'),
                                 ('size_t',      'i2'),
                                 ('size_t',      'c'))
swap_.pointing = '{ORIGINAL}'
swap_.defaults = {'_default3': ('c', 'return {WRAPPED}(d,i1,i2,1);')}
swap_.original = 4
swap_.original_defaults = {'_default3': 3}

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
reverse_ = Function('reverse', 'bool', ('{MAINTYPE}*', 'd'))
reverse_.pointing = '{ORIGINAL}'
reverse_.original = 1

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
append_ = Function('append', 'bool', ('{MAINTYPE}*', 'd'),
                                     ('size_t',      'c'),
                                     ('{SUBTYPE}*',  'a'))
append_.wrapping = _RETURN_DEF
append_.defaults = {'_default2': ('c', 'return {WRAPPED}(d,1,a);')}
append_.original = 3
append_.original_defaults = {'_default2': 2}

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
push_ = Function('push', 'bool', ('{MAINTYPE}*', 'd'),
                                 ('size_t',      'i'),
                                 ('size_t',      'c'),
                                 ('{SUBTYPE}*',  'a'))
push_.wrapping = _RETURN_DEF
push_.defaults = {'_default3': ('c', 'return {WRAPPED}(d,i,1,a);')}
push_.original = 4
push_.original_defaults = {'_default3': 3}

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
pull_ = Function('pull', 'size_t', ('{MAINTYPE}*', 'd'),
                                   ('size_t',      'i'),
                                   ('size_t',      'c'))
pull_.pointing = '{ORIGINAL}'
pull_.defaults = {'_default2': ('c', 'return {WRAPPED}(d,i,1);')}
pull_.original = 3
pull_.original_defaults = {'_default2': 2}

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
set_ = Function('set', 'bool', ('{MAINTYPE}*', 'd'),
                               ('size_t',      'i'),
                               ('size_t',      'c'),
                               ('{SUBTYPE}*',  'a'))
set_.wrapping = _RETURN_DEF
set_.defaults = {'_default3': ('c', 'return {WRAPPED}(d,i,1,a);')}
set_.original = 4
set_.original_defaults = {'_default3': 3}

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
pop_ = Function('pop', 'size_t', ('{MAINTYPE}*', 'd'),
                                 ('size_t',      'i'),
                                 ('size_t',      'c'),
                                 ('{SUBTYPE}*',  'a'))
pop_.wrapping = _RETURN_DEF
pop_.defaults = {'_default3': ('c', 'return {WRAPPED}(d,i,1,a);')}
pop_.original = 4
pop_.original_defaults = {'_default3': 3}

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
get_ = Function('get', '{SUBTYPE}', ('{MAINTYPE}*', 'd'),
                                    ('size_t',      'i'))
get_.wrapping = 'return *({SUBTYPE}*){ORIGINAL}({ARGUMENTS});'
get_.original = 2

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
sub_ = Function('sub', 'size_t', ('{MAINTYPE}*', 'd'),
                                 ('size_t',      'i'),
                                 ('size_t',      'c'),
                                 ('{SUBTYPE}*',  'a'))
sub_.wrapping = _RETURN_DEF
sub_.defaults = {'_default3': ('c', 'return {WRAPPED}(d,i,1,a);')}
sub_.original = 4
sub_.original_defaults = {'_default3': 3}

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
map_ = Function('map', 'void', ('{MAINTYPE}*', 'd'),
                               ('size_t',      'i'),
                               ('size_t',      'c'),
                               Function('f', 'void'))
map_.pointing = '{ORIGINAL}'
map_.defaults = {'_default3': ('i', 'return {WRAPPED}(d,0,c,f);')}
map_.original = 4
map_.original_defaults = {'_default3': 3}

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
find_ = Function('find', 'bool', ('{MAINTYPE}*', 'd'),
                                 Function('f', 'bool', ('const void*', 'p1'),
                                                       ('const void*', 'p2'),
                                                       ('size_t',      's')),
                                 ('{SUBTYPE}*',  'p'),
                                 ('size_t*',     'i'))
find_.wrapping = _RETURN_DEF
find_.defaults = {'_default3': ('f', 'return {WRAPPED}(d,{MAINTYPE}_compare,p,i);')}
find_.original = 4
find_.original_defaults = {'_default3': 3}

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
findall_ = Function('findall', 'size_t', ('{MAINTYPE}*', 'd'),
                                          Function('f', 'bool', ('const void*', 'p1'),
                                                                ('const void*', 'p2'),
                                                                ('size_t',      's')),
                                         ('{SUBTYPE}*',  'p'),
                                         ('size_t*',     'i'))
findall_.wrapping = _RETURN_DEF
findall_.defaults = {'_default3': ('f', 'return {WRAPPED}(d,{MAINTYPE}_compare,p,i);')}
findall_.original = 4
findall_.original_defaults = {'_default3': 3}

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
print_ = Function('print', 'void', ('{MAINTYPE}*', 'd'),
                                   ('FILE*',       's'),
                                   ('const char*', 'n'),
                                   Function('f', 'bool'))
print_.pointing = '{ORIGINAL}'
print_.defaults = {'_default1': ('s', 'n', 'f', 'return {WRAPPED}(d,stdout,'
                                                '"{SUBWORD}",{MAINTYPE}_format);')}
print_.original = 4
print_.original_defaults = {'_default2': 2,
                            '_default1': 1}

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
format_ = Function('format', 'bool', ('const {SUBTYPE}*', 'i'),
                                     ('char **',          'b'),
                                     ('size_t*',          's'))
format_.wrapping = {'bool': 'snprintf(*b,*s,"%s",*i?"true":"false");return true;',
                    'char': 'cutils_fmtc_repr(*b,*s,i,1);return true;',
                    'char*': 'size_t l=strlen(*i);if(*s<l+3)if(!(*b=realloc(*b,(*s=l*2+3))))'
                             'return false;cutils_fmtc_repr(*b,*s,*i,l);return true;',
                    'default': 'snprintf(*b,*s,"%{FORMAT}",*i);return true;'}
format_.generics = NotImplemented

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
    methods(base_name=ARRAY,
            base_type=PROTO,
            module_prefix=PREFIX,
            sub_types=C_TYPES,
            guard=GUARD,
            base_header='dynamic_array.h',
            base_source='dynamic_array.c',
            output_header=os.path.join(folder, 'cdar.h'),
            output_source=os.path.join(folder, 'cdar.c'),
            macros_dict=macros_dict,
            includes_header=INCLUDES_H,
            includes_source=INCLUDES_C,
            functions=(new_, del_, data_, len_, size_, raw_, resize_, truncate_,
                       clear_, swap_, reverse_, append_, push_, pull_, set_,
                       pop_, get_, sub_, map_, find_, findall_, print_, format_,
                       compare_))
