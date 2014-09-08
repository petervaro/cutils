## INFO ########################################################################
##                                                                            ##
##                                   cutils                                   ##
##                                   ======                                   ##
##                                                                            ##
##                     Modern and Lightweight C Utilities                     ##
##                       Version: 0.8.96.142 (20140907)                       ##
##                                                                            ##
##                        File: internal/generator.py                         ##
##                                                                            ##
##           Designed and written by Peter Varo. Copyright (c) 2014           ##
##             License agreement is provided in the LICENSE file              ##
##                 For more info visit: http://www.cutils.org                 ##
##                                                                            ##
######################################################################## INFO ##

# Import python modules
import itertools

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
_INFO = '/* INFO **\n** INFO */\n\n'
#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
_GUARD_HEAD = '#ifndef _C_{0}_H_{1}_\n#define _C_{0}_H_{1}_\n\n'
_GUARD_FOOT = '\n\n#endif /* _C_{0}_H_{1}_ */\n'
#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
_WRAPPED_HEADER = 'extern {RETURN} {FUNCTION}({ARGUMENT_TYPES});'
_WRAPPED_SOURCE = '{RETURN} {FUNCTION}({ARGUMENT_FULLS}){OPEN}{CONTENT}{CLOSE}'
#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
_POINTER_HEADER = 'extern {RETURN}(*{FUNCTION})({ARGUMENT_TYPES});'
_POINTER_SOURCE = '{RETURN}(*{FUNCTION})({ARGUMENT_TYPES})={CONTENT};'
#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
_TYPEDEF_HEADER = 'typedef struct {EMPTY} {MAINTYPE};'
_TYPEDEF_SOURCE = 'typedef {BASEMAINTYPE} {MAINTYPE};'
#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
_COMMENT = '\n/*{:-<76}*/\n'.format('')
#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
# TODO: make generic naming available to user
_GENERIC = ('#undef  __cutils_generic_{NAME}\n'
            '#define __cutils_generic_{NAME}(object,...) _Generic((object),'
            '\\\n    {ASSOCLIST})\\\n    (object,##__VA_ARGS__)')
#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
_ASSOC = '{ASSOCTYPE}:{FUNCTION}'
_START = 'FILE_STARTS_HERE\n'
_LEN_S = len(_START)
_AUTO  = '/* AUTOMATICALLY GENERATED GENERIC MACROS */'
_LEN_A = len(_AUTO) + 1
#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
_OPEN  = '{OPEN}'
OPEN_  = '{'
_CLOSE = '{CLOSE}'
CLOSE_ = '}'
_EMPTY = '{EMPTY}'
EMPTY_ = '{}'


#------------------------------------------------------------------------------#
class PseudoFunction:

    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def __init__(self, name, arg_count, first_arg, *, wrapped=None, supported=None):
        self.name = name
        self.wrapped = name if wrapped is None else wrapped
        self.supported = supported
        self.arg_count = arg_count
        self.defaults = ()
        self.originals = ()
        self.full_args = self.arg_names = self.arg_types = \
        self.type_repr = self.full_repr = self.returns = ''
        # HACK: Make this 'first_arg' type detection smarter...
        self.first_arg = first_arg.replace('MAINTYPE', 'BASEMAINTYPE')


#------------------------------------------------------------------------------#
class Function:

    # Constant values
    _REPR = '{}(*{})({})'
    _VARGS_REPR = '...'
    VARGS = Ellipsis

    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def __init__(self, name, returns, *arguments, wrapped=None, supported=None):
        """
        Public properties of Function:
            Function.wrapping          : str or dict
            Function.pointing          : str
            Function.generics          : str or NotImplemented
            Function.defaults          : dict
            Function.original          : int
            Function.original_defaults : dict

        Special format variables:
            {MAINTYPE}  : Type of object the method is working on
            {SUPPORT_n} : Nth support type if there is any
            {SUBTYPE}   : C representation of subtype
            {SUBTYPE_n} : C representation of nth subtype if subtypes are combined
            {SUBWORD}   : Word representation of subtype
            {SUBWORD_n} : Word representation of nth subtype if subtypes are combined
            {ORIGINAL}  : Original function derived from the name of function
            {WRAPPED}   : Original function defined by the 'wrapped' keyword
            {ARGUMENTS} : Variable names of all arguments
            {FORMAT}    : Format string of subtype
            {FUNCTION}  : Name of current function
        """
        # Store static values
        self.name = name
        self.wrapped = name if wrapped is None else wrapped
        self.returns = returns
        self.supported = supported
        self._arguments = arguments

        # Set storages
        self._defaults = []
        self.originals = []

        # Format this function as a function pointer argument
        processed_arguments = []
        # Sort and format arguments
        fulls = []
        names = []
        types = []
        # Go through all arguments
        for argument in arguments:
            # If argument is a function pointer
            try:
                processed_arguments.append(argument.type_repr)
                names.append(argument.name)
                types.append(argument.type_repr)
                fulls.append(argument.full_repr)
            # If argument is a regular argument
            except AttributeError:
                # If argument is a variable argument
                if argument is self.VARGS:
                    processed_arguments.append(self._VARGS_REPR)
                    names.append(self._VARGS_REPR)
                    types.append(self._VARGS_REPR)
                    fulls.append(self._VARGS_REPR)
                # If argument is a regular type-varname argument
                else:
                    processed_arguments.append(argument[0])
                    type, name = argument
                    names.append(name)
                    types.append(type)
                    fulls.append(type+name if type[-1] == '*' else type+' '+name)

        # Create string of arguments
        stringified_arguments = ','.join(processed_arguments)

        # Store representations
        self.type_repr = self._REPR.format(self.returns, '', stringified_arguments)
        self.full_repr = self._REPR.format(self.returns, self.name, stringified_arguments)

        # Store arguments as public string properties
        try:
            self.first_arg = types[0]
        except IndexError:
            self.first_arg = None

        # Store different "views" of formatted arguments
        self.full_args = ','.join(fulls)
        self.arg_names = ','.join(names)
        self.arg_types = ','.join(types)

        # Store number of arguments
        self.arg_count = len(arguments)

    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    @property
    def defaults(self):
        # Return list of defaults
        return self._defaults

    @defaults.setter
    def defaults(self, default_values):
        # Get local references
        defaults  = self._defaults
        arguments = self._arguments

        # Process all default values in dictionary
        for suffix, (*default_arguments, wrapping) in sorted(default_values.items()):
            # Construct new function's argument list
            argument_list = []
            for argument in arguments:
                # If argument is a function pointer
                try:
                    argument_name = argument.name
                # If argument is a regular variable
                except AttributeError:
                    argument_name = argument[1]

                # Populate argument list
                if argument_name not in default_arguments:
                    argument_list.append(argument)

            # Create new 'default' function based on the current one (self)
            function = Function(self.name + suffix,
                                self.returns,
                                *argument_list,
                                wrapped=self.name)
            function.wrapping = wrapping

            # Add function to defaults
            defaults.append(function)

    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    @property
    def original(self):
        raise AttributeError('Function.original is a write only attribute')

    @original.setter
    def original(self, arg_count):
        function = PseudoFunction(self.name,
                                  arg_count,
                                  self.first_arg,
                                  supported=self.supported)
        # HACK: even uglier, dirtier and filthier then the other hack below..
        if self.supported:
            function.generics = '{{BASEMAINTYPE}}_{}:{{WRAPPED}}'.format(self.supported)
        else:
            function.generics = '{ASSOCTYPE}:{WRAPPED}'
        self.originals.append(function)

    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    @property
    def original_defaults(self):
        raise AttributeError('Function.original_defaults is a write only attribute')

    @original_defaults.setter
    def original_defaults(self, default_values):
        # Get local references
        name = self.name
        first_arg = self.first_arg
        originals = self.originals
        supported = self.supported
        for suffix, arg_count in default_values.items():
            function = PseudoFunction(name + suffix,
                                      arg_count,
                                      first_arg,
                                      wrapped=name,
                                      supported=supported)
            function.generics = '{ASSOCTYPE}:{ORIGINAL}'
            originals.append(function)



#------------------------------------------------------------------------------#
# Format string to contain word-like characters only
def _wordify(string):
    target = ' ', '_', '*', '_ptr'
    string = string.strip()
    for replacement in zip(*(iter(target),)*2):
        string = string.replace(*replacement)
    return string



#------------------------------------------------------------------------------#
# The default-combiner doesn't combine any of the types
def _do_not_combine(types):
    if types:
        yield from ((type,) for type in types)
    else:
        yield from ((),)



#------------------------------------------------------------------------------#
def auto_api(macro_header, macros_dict):
    generics = []
    for name, groups in macros_dict.items():
        NAME = '{n}_args{c}' if len(groups) > 1 else '{n}'
        for arg_count, assoc in sorted(groups.items(), reverse=True):
            generics.append(_GENERIC.format(NAME=NAME.format(n=name, c=arg_count),
                                            ASSOCLIST=',\\\n    '.join(assoc)))
    # I/O
    with open(macro_header, 'r+', encoding='utf-8') as h_macro:
        # Find leading comment
        h_macro.seek(h_macro.read().find(_AUTO) + _LEN_A)
        h_macro.write('\n'*3)
        # Write generics to file
        h_macro.write(_COMMENT.join(generics))
        # FIXME: better guard ending and meaningful comment
        h_macro.write('\n\n#endif /* guard */\n')
        h_macro.truncate()
    print('{!r} generated.'.format(macro_header))



#------------------------------------------------------------------------------#
def methods(base_name, base_type='', module_prefix='', sub_types=(),
            combine_sub_types=_do_not_combine, support_types=(),
            functions=(), guard=None, base_header=None, base_source=None,
            output_header=None, output_source=None, macros_dict={},
            includes_header=(), includes_source=()):

    # TODO: Reduce the levels of formatting from 3
    #       to at most 2 with an elegant solution...

    if isinstance(base_type, tuple):
        BASETYPE = '_and_'.join(map(_wordify, base_type))
    else:
        BASETYPE = _wordify(base_type)

    # Create formatting dictionary
    format_dict = {'BASETYPE'    : BASETYPE,
                   'BASENAME'    : base_name,
                   'BASEMAINTYPE': '{PREFIX}_{BASENAME}_{BASETYPE}',
                   'PREFIX'      : module_prefix}

    # Storages for code snippets
    methods_header = []
    methods_source = []

    # Main type name without suffixes
    MAINTYPE = '{PREFIX}_{BASENAME}'

    # This flag is for the first "round" of generation. Because the base-type
    # specific code has already been written, it doesn't need header and source
    # generation, it only needs to be part of the generic API and the needs
    # the default-value wrappers
    is_base_type = True

    # Generate all functions for each subtype-combination
    for combined_sub_types in combine_sub_types(sub_types):
        # If there is more than one sub-type (combined)
        if len(combined_sub_types) > 1:
            SUBTYPE = 'SUBTYPE_{}'
            SUBWORD = 'SUBWORD_{}'
            FORMAT  = 'FORMAT_{}'
        # If there is a single sub-type
        else:
            SUBTYPE = 'SUBTYPE'
            SUBWORD = 'SUBWORD'
            FORMAT  = 'FORMAT'

        # Update type related values in format dictionary
        MAIN_SUFFIX = ''
        for i, (subtype_name, subtype_fmt, subtype_sym) in enumerate(combined_sub_types,
                                                                     start=1):
            # Add subtype to full-name
            SUBWORD_N = SUBWORD.format(i)
            if i - 1:
                MAIN_SUFFIX += '_and'
            MAIN_SUFFIX += '_{' + SUBWORD_N + '}'
            # Add sub-types to
            format_dict[SUBTYPE.format(i)] = subtype_name
            format_dict[SUBWORD_N] = _wordify(subtype_name)
            format_dict[FORMAT.format(i)]  = subtype_fmt + subtype_sym

        # Set the sub-typed main-type
        format_dict['MAINTYPE'] = MAINTYPE + MAIN_SUFFIX

        # Resolve inner-references
        for key, value in format_dict.items():
            format_dict[key] = value.format(EMPTY=_EMPTY, **format_dict)

        # Temporary storages + add base types
        headers = [_TYPEDEF_HEADER]
        sources = [_TYPEDEF_SOURCE]

        # Add support types
        for i, (support_alias, support_base) in enumerate(support_types, start=1):
            # Add support type to format-dict
            format_dict['SUPPORT_{}'.format(i)] = support_alias
            # HACK: this is a dirty and filthy hack, just to make this
            #       supported-method system work. fixit ASAP!
            format_dict['SUPPORT_TYPE_{}'.format(i)] = ALIAS = '{MAINTYPE}_' + support_alias
            # Create header and source typedefs
            headers.append(_TYPEDEF_HEADER.format(MAINTYPE=ALIAS,
                                                  EMPTY=_EMPTY))
            sources.append(_TYPEDEF_SOURCE.format(MAINTYPE=ALIAS,
                                                  BASEMAINTYPE=support_base,
                                                  EMPTY=_EMPTY))
        # Format type definitions
        for storage in (headers, sources):
            for i, typedef in enumerate(storage):
                typedef = typedef.format(EMPTY=_EMPTY, **format_dict)
                storage[i] = typedef.format(EMPTY=EMPTY_, **format_dict)

        # ...
        default_functions = []
        # Create function wrappers and pointers
        for function in itertools.chain(functions, default_functions):
            # If function has default-values (default-wrappers) add them to functions
            default_functions.extend(function.defaults)

            # If this is the first time iterating throught functions, if function
            # has details of the ortiginal functions, add them to the function list
            if is_base_type:
                default_functions.extend(function.originals)

            # If function is a method of the main-type
            if function.supported is None:
                format_dict['WRAPPED']  = '{BASEMAINTYPE}_{ALTERNATE}'
                format_dict['FUNCTION'] = '{MAINTYPE}_{NAME}'
                format_dict['ORIGINAL'] = '{BASEMAINTYPE}_{NAME}'
            # If function is a method of a support type
            else:
                # HACK: Because of the unordered nature of a dictionary, if
                #       'SUPPORTED' will be processed first and 'SUPPORT_n'
                #       (function.supported) later, then the output will never
                #       be formatted properly. To solve this undeterministic bug,
                #       'SUPPORTED' is formatted directly here. Solve this!!!
                format_dict['SUPPORTED'] = function.supported.format(**format_dict)
                format_dict['WRAPPED']   = '{BASEMAINTYPE}_{SUPPORTED}_{ALTERNATE}'
                format_dict['FUNCTION']  = '{MAINTYPE}_{SUPPORTED}_{NAME}'
                format_dict['ORIGINAL']  = '{BASEMAINTYPE}_{SUPPORTED}_{NAME}'

            # Update function-related values in format dictionary
            format_dict['NAME']           = function.name
            format_dict['RETURN']         = function.returns
            format_dict['ALTERNATE']      = function.wrapped
            format_dict['ASSOCTYPE']      = function.first_arg
            format_dict['ASSOCWORD']      = _wordify(function.first_arg)
            format_dict['ARGUMENTS']      = function.arg_names
            format_dict['ARGUMENT_TYPES'] = function.arg_types
            format_dict['ARGUMENT_FULLS'] = function.full_args

            # Resolve inner-references
            for key, value in format_dict.items():
                format_dict[key] = value.format(OPEN=_OPEN, CLOSE=_CLOSE, **format_dict)

            # If generics value is defined
            try:
                # If function has special generic macro need
                try:
                    func_generics = function.generics
                    # If that need indicates function does not require generics
                    if func_generics is NotImplemented:
                        raise NotImplementedError
                # If function has regular generic macro need
                except AttributeError:
                    func_generics = _ASSOC

                # If function-object doesn't have argument list
                if function.first_arg is None:
                    raise ValueError('Generics cannot be generated with '
                                     'empty argument list of Function') from None

                # Append new function to association list of generic macro
                generics = macros_dict.setdefault(function.wrapped,
                                                  {}).setdefault(function.arg_count, [])
                # Add sub-typed function to generic assoc-list
                generics.append(func_generics.format(**format_dict))

            # If function does not have generics
            except NotImplementedError:
                pass

            # If this item is just an indicator of the original function
            if isinstance(function, PseudoFunction):
                continue

            # If function is a wrapper
            try:
                func_wrapping = function.wrapping
                # If wrapper act differently on some types
                try:
                    # FIXME: getting 'default' key will raise KeyError even if
                    #        'subtype_name' is in 'func_wrapping' !!!
                    format_dict['CONTENT'] = func_wrapping.get(subtype_name,
                                                               func_wrapping['default'])
                # If warpper is a uniform wrapper
                except AttributeError:
                    format_dict['CONTENT'] = func_wrapping
                except KeyError:
                    error = ("Function.wrapping dictionary: missing "
                             "{!r} or 'default' key".format(subtype_name))
                    raise KeyError(error) from None

                header = _WRAPPED_HEADER
                source = _WRAPPED_SOURCE
            # If function is function pointer
            except AttributeError:
                try:
                    format_dict['CONTENT'] = function.pointing
                    header = _POINTER_HEADER
                    source = _POINTER_SOURCE
                except AttributeError:
                    error = ('Function object {!r} missing .wrapping '
                             'or .pointing property'.format(function.name))
                    raise AttributeError(error) from None

            # Format twice, to make sure, all levels of formatting is gone
            header = header.format(OPEN=_OPEN, CLOSE=_CLOSE, **format_dict)
            headers.append(header.format(OPEN=OPEN_, CLOSE=CLOSE_, **format_dict))
            source = source.format(OPEN=_OPEN, CLOSE=_CLOSE, **format_dict)
            sources.append(source.format(OPEN=OPEN_, CLOSE=CLOSE_, **format_dict))

        # Extend final headers with the freshly generated data
        methods_header.append('\n'.join(headers))
        methods_source.append('\n'.join(sources))

        # There can only be one base_type, so if control
        # reaches this point => the next will be a sub-type
        is_base_type = False

    # I/O
    if output_header:
        with open(output_header, 'w', encoding='utf-8') as h_file:
            h_file.write(_INFO)
            h_file.write(_GUARD_HEAD.format(*guard))
            h_file.write(''.join('#include {}\n'.format(i) for i in includes_header))
            if base_header:
                with open(base_header, encoding='utf-8') as h_base:
                    code = h_base.read()
                    h_file.write(code[code.find(_START) + _LEN_S:])
            h_file.write(_COMMENT)
            h_file.write(_COMMENT.join(methods_header))
            h_file.write(_GUARD_FOOT.format(*guard))
        print('{!r} generated.'.format(output_header))

    if output_source:
        with open(output_source, 'w', encoding='utf-8') as c_file:
            c_file.write(_INFO)
            c_file.write(''.join('#include {}\n'.format(i) for i in includes_source))
            if base_source:
                with open(base_source, encoding='utf-8') as c_base:
                    code = c_base.read()
                    c_file.write(code[code.find(_START) + _LEN_S:])
            c_file.write(_COMMENT)
            c_file.write(_COMMENT.join(methods_source))
        print('{!r} generated.'.format(output_source))
