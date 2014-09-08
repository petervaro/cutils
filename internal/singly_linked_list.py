## INFO ########################################################################
##                                                                            ##
##                                   cutils                                   ##
##                                   ======                                   ##
##                                                                            ##
##                     Modern and Lightweight C Utilities                     ##
##                       Version: 0.8.96.129 (20140907)                       ##
##                                                                            ##
##                    File: internal/singly_linked_list.py                    ##
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
GUARD  = 'SINGLY_LINKED_LIST', '35118355245711974'
PROTO  = 'void*'
LLIST  = 'SinglyLinkedList'
PREFIX = 'cutils_csll'

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
SUPPORTS = (('iterator', 'SLLIterator'),)

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
INCLUDES_H = ('<stdio.h>    /* FILE */',
              '<stddef.h>   /* ptrdiff_t */')
INCLUDES_C = ('<stddef.h>         /* ptrdiff_t */',
              '<string.h>         /* strlen() */',
              '"internal/fmtc.h"  /* cutils_fmtc_repr */',
              '"internal/fcmp.h"  /* cutils_fcmp_compare */')

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
_RETURN_DEF = 'return {ORIGINAL}({ARGUMENTS});'
_RETURN_EXT = 'return {ORIGINAL}(l,i,sizeof({SUBTYPE}),c,a);'



#------------------------------------------------------------------------------#
new_ = Function('new', 'bool', ('{MAINTYPE}**', 'l'),
                               ('size_t',       'c'),
                               ('{SUBTYPE}*',   'a'))
new_.wrapping = 'return {ORIGINAL}(l,sizeof({SUBTYPE}),c,a);'
new_.defaults = {'_default1': ('c', 'a', 'return {WRAPPED}(l,sizeof({SUBTYPE}),0,NULL);')}
new_.original = 4
new_.original_defaults = {'_default1': 1}

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
del_ = Function('del', 'void', ('{MAINTYPE}*', 'l'))
del_.pointing = '{ORIGINAL}'
del_.original = 1

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
len_ = Function('len', 'size_t', ('{MAINTYPE}*', 'l'))
len_.pointing = '{ORIGINAL}'
len_.original = 1

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
clear_ = Function('clear', 'void', ('{MAINTYPE}*', 'l'))
clear_.pointing = '{ORIGINAL}'
clear_.original = 1

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
truncate_ = Function('truncate', 'void', ('{MAINTYPE}*', 'l'),
                                         ('size_t',      'i'))
truncate_.pointing = '{ORIGINAL}'
truncate_.defaults = {'_default1': ('i', 'return {WRAPPED}(l,0);')}
truncate_.original = 2

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
iter_ = Function('iter', '{SUPPORT_TYPE_1}*', ('{MAINTYPE}*', 'l'))
iter_.wrapping = _RETURN_DEF
iter_.original = 1

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
iter_del_ = Function('del', 'void', ('{SUPPORT_TYPE_1}*', 'i'), supported='{SUPPORT_1}')
iter_del_.wrapping = _RETURN_DEF
iter_del_.original = 1

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
iter_next_ = Function('next', 'bool', ('{SUPPORT_TYPE_1}*', 'i'),
                                      ('{SUBTYPE}**',  'p'), supported='{SUPPORT_1}')
iter_next_.wrapping = _RETURN_DEF
iter_next_.original = 2

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
iter_pull_ = Function('pull', 'void', ('{SUPPORT_TYPE_1}*', 'i'), supported='{SUPPORT_1}')
iter_pull_.wrapping = _RETURN_DEF
iter_pull_.original = 1

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
swap_ = Function('swap', 'bool', ('{MAINTYPE}*', 'l'),
                                 ('size_t',      'i1'),
                                 ('size_t',      'i2'),
                                 ('size_t',      'c'))
swap_.pointing = '{ORIGINAL}'
swap_.defaults = {'_default3': ('c', 'return {WRAPPED}(l,i1,i2,1);')}
swap_.original = 4
swap_.original_defaults = {'_default3': 3}

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
reverse_ = Function('reverse', 'bool', ('{MAINTYPE}*', 'l'))
reverse_.pointing = '{ORIGINAL}'
reverse_.original = 1

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
append_ = Function('append', 'bool', ('{MAINTYPE}*', 'l'),
                                     ('size_t',      'c'),
                                     ('{SUBTYPE}*',  'a'))
append_.wrapping = 'return {ORIGINAL}(l,sizeof({SUBTYPE}),c,a);'
append_.defaults = {'_default2': ('c', 'return {WRAPPED}(l,sizeof({SUBTYPE}),1,a);')}
append_.original = 4
append_.original_defaults = {'_default3': 3}

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
push_ = Function('push', 'bool', ('{MAINTYPE}*', 'l'),
                                 ('size_t',      'i'),
                                 ('size_t',      'c'),
                                 ('{SUBTYPE}*',  'a'))
push_.wrapping = _RETURN_EXT
push_.defaults = {'_default3': ('c', 'return {WRAPPED}(l,i,sizeof({SUBTYPE}),1,a);')}
push_.original = 5
push_.original_defaults = {'_default4': 4}

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
pull_ = Function('pull', 'size_t', ('{MAINTYPE}*', 'l'),
                                   ('size_t',      'i'),
                                   ('size_t',      'c'))
pull_.pointing = '{ORIGINAL}'
pull_.defaults = {'_default2': ('c', 'return {WRAPPED}(l,i,1);')}
pull_.original = 3
pull_.original_defaults = {'_default2': 2}

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
set_ = Function('set', 'bool', ('{MAINTYPE}*', 'l'),
                               ('size_t',      'i'),
                               ('size_t',      'c'),
                               ('{SUBTYPE}*',  'a'))
set_.wrapping = _RETURN_EXT
set_.defaults = {'_default3': ('c', 'return {WRAPPED}(l,i,sizeof({SUBTYPE}),1,a);')}
set_.original = 5
set_.original_defaults = {'_default4': 4}

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
pop_ = Function('pop', 'bool', ('{MAINTYPE}*', 'l'),
                               ('size_t',      'i'),
                               ('size_t',      'c'),
                               ('{SUBTYPE}*',  'a'))
pop_.wrapping = _RETURN_EXT
pop_.defaults = {'_default3': ('c', 'return {WRAPPED}(l,i,sizeof({SUBTYPE}),1,a);')}
pop_.original = 5
pop_.original_defaults = {'_default4': 4}

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
get_ = Function('get', '{SUBTYPE}', ('{MAINTYPE}*', 'l'),
                                    ('size_t',      'i'))
get_.wrapping = 'return *({SUBTYPE}*){ORIGINAL}({ARGUMENTS});'
get_.original = 2

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
sub_ = Function('sub', 'bool', ('{MAINTYPE}*', 'l'),
                               ('size_t',      'i'),
                               ('size_t',      'c'),
                               ('{SUBTYPE}*',  'a'))
sub_.wrapping = _RETURN_EXT
sub_.defaults = {'_default3': ('c', 'return {WRAPPED}(l,i,sizeof({SUBTYPE}),1,a);')}
sub_.original = 5
sub_.original_defaults = {'_default4': 4}

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
map_ = Function('map', 'void', ('{MAINTYPE}*', 'l'),
                               ('size_t',      'i'),
                               ('size_t',      'c'),
                               Function('f', 'void'))
map_.pointing = '{ORIGINAL}'
map_.defaults = {'_default3': ('i', 'return {WRAPPED}(l,0,c,f);')}
map_.original = 4
map_.original_defaults = {'_default3': 3}


#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
# FIXME: try to make both find and findall type-safe
#        by replacing the const void* to type specific pointer
#        the main problem is, cannot pass
#        bool(*)(const type*,...) --> bool(*)(const void*,...)
find_ = Function('find', 'bool', ('{MAINTYPE}*', 'l'),
                                 Function('f', 'bool', ('const void*', 'p1'),
                                                       ('const void*', 'p2'),
                                                       ('size_t',      's')),
                                 ('{SUBTYPE}*',  'p'),
                                 ('size_t*',     'i'))
find_.wrapping = 'return {ORIGINAL}(l,f,sizeof({SUBTYPE}),p,i);'
find_.defaults = {'_default3': ('f', 'return {WRAPPED}(l,{MAINTYPE}_compare,'
                                     'sizeof({SUBTYPE}),p,i);')}
find_.original = 5
find_.original_defaults = {'_default4': 4}

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
findall_ = Function('findall', 'size_t', ('{MAINTYPE}*', 'l'),
                                         Function('f', 'bool', ('const void*', 'p1'),
                                                               ('const void*', 'p2'),
                                                               ('size_t',      's')),
                                         ('{SUBTYPE}*',  'p'),
                                         ('size_t*',     'i'))
findall_.wrapping = 'return {ORIGINAL}(l,f,sizeof({SUBTYPE}),p,i);'
findall_.defaults = {'_default3': ('f', 'return {WRAPPED}(l,{MAINTYPE}_compare,'
                                        'sizeof({SUBTYPE}),p,i);')}
findall_.original = 5
findall_.original_defaults = {'_default4': 4}

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
# TODO: is there a way to make this inline?
print_ = Function('print', 'void', ('{MAINTYPE}*', 'l'),
                                   ('FILE*',       's'),
                                   ('const char*', 'n'),
                                   Function('f', 'bool'))
print_.pointing = '{ORIGINAL}'
print_.defaults = {'_default1': ('s', 'n', 'f', 'return {WRAPPED}(l,stdout,'
                                                '"{SUBWORD}",{MAINTYPE}_format);')}
print_.original = 4
print_.original_defaults = {'_default2': 2,
                            '_default1': 1}

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
# TODO: is there a way to make this inline?
format_ = Function('format', 'bool', ('const {SUBTYPE}*', 'i'),
                                     ('char**',           'b'),
                                     ('size_t*',          's'))
format_.wrapping = {'bool': 'snprintf(*b,*s,"%s",*i?"true":"false");return true;',
                    'char': 'cutils_fmtc_repr(*b,*s,i,1);return true;',
                    'char*': 'size_t l=strlen(*i);if(*s<l+3)if(!(*b=realloc(*b,(*s=l*2+3))))'
                             'return false;cutils_fmtc_repr(*b,*s,*i,l);return true;',
                    'default': 'snprintf(*b,*s,"%{FORMAT}",*i);return true;'}
format_.generics = NotImplemented

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
# TODO: is there a way to make this inline?
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
    methods(base_name=LLIST,
            base_type=PROTO,
            module_prefix=PREFIX,
            sub_types=C_TYPES,
            support_types=SUPPORTS,
            guard=GUARD,
            base_header='singly_linked_list.h',
            base_source='singly_linked_list.c',
            output_header=os.path.join(folder, 'csll.h'),
            output_source=os.path.join(folder, 'csll.c'),
            macros_dict=macros_dict,
            includes_header=INCLUDES_H,
            includes_source=INCLUDES_C,
            functions=(new_, del_, len_, truncate_, clear_, iter_, iter_del_,
                       iter_next_, iter_pull_, swap_, reverse_, append_, push_,
                       pull_, set_, pop_, get_, sub_, map_, find_, findall_,
                       print_, format_, compare_))
