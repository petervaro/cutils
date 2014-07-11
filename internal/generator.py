## INFO ########################################################################
##                                                                            ##
##                                   cutils                                   ##
##                                   ======                                   ##
##                                                                            ##
##                     Modern and Lightweight C Utilities                     ##
##                       Version: 0.8.72.365 (20140711)                       ##
##                                                                            ##
##                        File: internal/generator.py                         ##
##                                                                            ##
##           Designed and written by Peter Varo. Copyright (c) 2014           ##
##             License agreement is provided in the LICENSE file              ##
##                 For more info visit: http://www.cutils.org                 ##
##                                                                            ##
######################################################################## INFO ##

# Import python modules
from itertools import chain, repeat
from string import punctuation as P
from collections import OrderedDict

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
_INFO = '/* INFO *\n * INFO */\n\n'
#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
_GUARD_HEAD = ('#ifndef _C_{0}_H_2427147457128005_\n'
              '#define _C_{0}_H_2427147457128005_\n\n')
_GUARD_FOOT = '\n#endif /* _C_{0}_H_2427147457128005_ */\n'
#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
_WRAPPED_HEADER = 'extern {1} {0}_{{1}}_{2}({3.types});'
_WRAPPED_SOURCE = '{1} {0}_{{1}}_{2}({3.full}){{{{{4}}}}}'
#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
_POINTER_HEADER = 'extern {1}(*{0}_{{1}}_{2})({3.types});'
_POINTER_SOURCE = '{1}(*{0}_{{1}}_{2})({3.types})={4};'
#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
_COMMENT = '\n/*{:-<76}*/\n'.format('')
#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
_GENERIC = ('#undef __cutils_generic_{0}\n'
            '#define __cutils_generic_{0}(object, ...) _Generic((object),'
            '\\\n    {1})\\\n    (object, ## __VA_ARGS__)')
#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
_ASSOC = ':{0}_{1}_{2}'
_START = 'FILE_STARTS_HERE\n'
_LEN_S = len(_START)

#------------------------------------------------------------------------------#
class args(tuple):
    @property
    def full(self):
        iself = iter(self)
        return ','.join(t+n if t[-1] in P else t+' '+n for t, n in zip(iself, iself))
    @property
    def names(self):
        iself = iter(self)
        return ','.join(n for t, n in zip(iself, iself))
    @property
    def types(self):
        iself = iter(self)
        return ','.join(t for t, n in zip(iself, iself))

#------------------------------------------------------------------------------#
def methods(types, guard, base_name, prototype, wrappers, pointers,
            proto_header, proto_source, output_header, output_source,
            includes=(), print_generic=False):
    methods_header = []
    methods_source = []
    tgfuncs = OrderedDict()
    # For each standard type generate type specific functions
    for name, specifier in types:
        # Format with word-like only characters
        word = name.replace(' ', '_').replace('*', '_ptr')
        # Add base types
        headers = ['typedef struct {{}} {}_{};'.format(base_name, word)]
        sources = ['typedef {} {}_{};'.format(prototype, base_name, word)]
        # Create function wrappers and pointers
        for f, h, s in chain(zip(wrappers, repeat(_WRAPPED_HEADER), repeat(_WRAPPED_SOURCE)),
                             zip(pointers, repeat(_POINTER_HEADER), repeat(_POINTER_SOURCE))):
            headers.append(h.format(base_name, *f).format(base_name, word, name, prototype, *f))
            sources.append(s.format(base_name, *f).format(base_name, word, name, prototype, *f))
            tgfuncs.setdefault(f[1], []).append((f[2][0], word))

        methods_header.append('\n'.join(headers))
        methods_source.append('\n'.join(sources))

    if print_generic:
        generics = []
        for func, types in tgfuncs.items():
            assoc = map(lambda t, b=base_name, f=func: (t[0]+_ASSOC).format(b, t[1], f), types)
            generics.append(_GENERIC.format(func, ',\\\n    '.join(assoc)))
        print(_COMMENT.join(generics))

    with open(output_header, 'w') as h_file:
        h_file.write(_INFO)
        h_file.write(_GUARD_HEAD.format(guard))
        h_file.write(''.join('#include {}\n'.format(i) for i in includes))
        with open(proto_header) as h_proto:
            code = h_proto.read()
            h_file.write(code[code.find(_START) + _LEN_S:])
        h_file.write(_COMMENT)
        h_file.write(_COMMENT.join(methods_header))
        h_file.write(_GUARD_FOOT.format(guard))

    with open(output_source, 'w') as c_file:
        c_file.write(_INFO)
        c_file.write(''.join('#include {}\n'.format(i) for i in includes))
        with open(proto_source) as c_proto:
            code = c_proto.read()
            c_file.write(code[code.find(_START) + _LEN_S:])
        c_file.write(_COMMENT)
        c_file.write(_COMMENT.join(methods_source))
