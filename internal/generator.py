## INFO ########################################################################
##                                                                            ##
##                                   cutils                                   ##
##                                   ======                                   ##
##                                                                            ##
##                     Modern and Lightweight C Utilities                     ##
##                       Version: 0.8.85.326 (20140727)                       ##
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
from random import random

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
_INFO = '/* INFO *\n * INFO */\n\n'
#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
_GUARD_HEAD = ('#ifndef _C_{0}_H_{1}_\n'
              '#define _C_{0}_H_{1}_\n\n')
_GUARD_FOOT = '\n#endif /* _C_{0}_H_{1}_ */\n'
#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
_WRAPPED_HEADER = 'extern {1} {0}_{{1}}_{2}({3.types});'
_WRAPPED_SOURCE = '{1} {0}_{{1}}_{2}({3.fulls}){{{{{4}}}}}'
#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
_POINTER_HEADER = 'extern {1}(*{0}_{{1}}_{2})({3.types});'
_POINTER_SOURCE = '{1}(*{0}_{{1}}_{2})({3.types})={4};'
#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
_COMMENT = '\n/*{:-<76}*/\n'.format('')
#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
_GENERIC = ('#undef __cutils_generic_{0}\n'
            '#define __cutils_generic_{0}(object, ...) _Generic((object),'
            '\\\n    {1})')
_CALLING = '\\\n    (object,##__VA_ARGS__)'
#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
_ASSOC_SUBTYPE = '{}:{{0}}_{{1}}_{{2}}'
_ASSOC_KEYTYPE = '{}:{{0}}_{{2}}'
_START = 'FILE_STARTS_HERE\n'
_LEN_S = len(_START)
_AUTO  = '/* AUTOMATICALLY GENERATED GENERICS MACROS */'
_LEN_A = len(_AUTO) + 1



#------------------------------------------------------------------------------#
class args:

    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def __init__(self, *args):
        self._data = args
        # Sort and format arguments
        fulls = []
        names = []
        types = []
        t = None
        for arg in args:
            # If argument is a function pointer
            try:
                fulls.append(arg.full)
                names.append(arg.name)
                types.append(arg.type)
                t = None
            # If argument is a regular argument
            except AttributeError:
                if t:
                    names.append(arg)
                    fulls.append(t+arg if t[-1] in P else t+' '+arg)
                    t = None
                else:
                    types.append(arg)
                    t = arg
        # Store arguments as public string properties
        self.fulls = ','.join(fulls)
        self.names = ','.join(names)
        self.types = ','.join(types)

    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def __getitem__(self, index):
        return self._data[index]



#------------------------------------------------------------------------------#
class vargs:

    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def __init__(self):
        self.name = self.type = self.full = '...'
#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
VARGS = vargs()



#------------------------------------------------------------------------------#
class fp:

    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def __init__(self, _return, name, *args):
        args = ','.join(args)
        self.name = name
        self.type = '{}(*)({})'.format(_return, args)
        self.full = '{}(*{})({})'.format(_return, name, args)

#------------------------------------------------------------------------------#
def _format(format_string, base_name, type_name, data):
    try:
        data = data[:3] + (data[3].get(type_name, data[3]['default']),)
    except AttributeError:
        pass
    return format_string.format(base_name, *data)


#------------------------------------------------------------------------------#
def auto_api(macro_header, macros_dict):
    generics = []
    for func, (types, calling) in macros_dict.items():
        assoc = ',\\\n    '.join(map(lambda t, f=func: t[2].format(t[0]).format(t[3], t[1], f), types))
        if assoc:
            generics.append(_GENERIC.format(func, assoc) + calling)
    # Write generic macros to header file
    with open(macro_header, 'r+', encoding='utf-8') as h_macro:
        h_macro.seek(h_macro.read().find(_AUTO) + _LEN_A)
        h_macro.write('\n'*3)
        h_macro.write(_COMMENT.join(generics))
        # FIXME: better guard ending and meaningful comment
        h_macro.write('\n#endif /* guard */\n')
        h_macro.truncate()
    print(macro_header, 'generated.')


#------------------------------------------------------------------------------#
def methods(types, base_name, sub_typed=False, guard=None,
            prototype=None, supports=(), wrappers=(), pointers=(),
            proto_header=None, proto_source=None,
            output_header=None, output_source=None,
            macros_dict={}, includes=()):
    ASSOC = _ASSOC_SUBTYPE if sub_typed else _ASSOC_KEYTYPE
    methods_header = []
    methods_source = []
    proto_added = set()
    # For each standard type generate type specific functions
    for name, fmt in types:
        # Format with word-like only characters
        # FIXME: strip whitespaces
        word = name.replace(' ', '_').replace('*', '_ptr')
        # Add base types
        headers = ['typedef struct {{}} {}_{};'.format(base_name, word)]
        sources = ['typedef {0}_{1} {0}_{2};'.format(base_name, prototype, word)]
        # HACK: make the supporter types way more generic
        #       create a better definition-structure!
        for alias, real in supports:
            headers.append(('typedef struct {{}} ' + alias + ';').format(base_name, word))
            sources.append(('typedef {2} ' + alias + ';').format(base_name, word, real))
        # Create function wrappers and pointers
        for f, h, s in chain(zip(wrappers, repeat(_WRAPPED_HEADER), repeat(_WRAPPED_SOURCE)),
                             zip(pointers, repeat(_POINTER_HEADER), repeat(_POINTER_SOURCE))):
            headers.append(h.format(base_name, *f).format(base_name, word, name, fmt, prototype, *f))
            sources.append(_format(s, base_name, name, f).format(base_name, word, name, fmt, prototype, *f))
            # Store the values of the type generic expression
            func_name = f[1]
            generics = macros_dict.setdefault(func_name, [[], _CALLING])
            try:
                # If there is a fifth element (special assignment expression)
                assign_expr = f[4]
                if assign_expr is NotImplemented:
                    continue
                generics[1] = ''
            except IndexError:
                # If no special assignemnt expression
                assign_expr = ASSOC
            # Add prototype to generics if it is not in already
            if prototype and func_name not in proto_added:
                proto_added.add(func_name)
                generics[0].append((f[2][0], prototype, assign_expr, base_name))
            # Add type specific expression to generics
            generics[0].append((f[2][0], word, assign_expr, base_name))

        methods_header.append('\n'.join(headers))
        methods_source.append('\n'.join(sources))

    if output_header:
        with open(output_header, 'w', encoding='utf-8') as h_file:
            h_file.write(_INFO)
            h_file.write(_GUARD_HEAD.format(*guard))
            h_file.write(''.join('#include {}\n'.format(i) for i in includes))
            with open(proto_header, encoding='utf-8') as h_proto:
                code = h_proto.read()
                h_file.write(code[code.find(_START) + _LEN_S:])
            h_file.write(_COMMENT)
            h_file.write(_COMMENT.join(methods_header))
            h_file.write(_GUARD_FOOT.format(*guard))
        print(output_header, 'generated.')

    if output_source:
        with open(output_source, 'w', encoding='utf-8') as c_file:
            c_file.write(_INFO)
            c_file.write(''.join('#include {}\n'.format(i) for i in includes))
            with open(proto_source, encoding='utf-8') as c_proto:
                code = c_proto.read()
                c_file.write(code[code.find(_START) + _LEN_S:])
            c_file.write(_COMMENT)
            c_file.write(_COMMENT.join(methods_source))
        print(output_source, 'generated.')
