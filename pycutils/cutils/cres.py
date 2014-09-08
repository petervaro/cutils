## INFO ########################################################################
##                                                                            ##
##                                   cutils                                   ##
##                                   ======                                   ##
##                                                                            ##
##                     Modern and Lightweight C Utilities                     ##
##                       Version: 0.8.95.804 (20140827)                       ##
##                                                                            ##
##                       File: pycutils/cutils/cres.py                        ##
##                                                                            ##
##           Designed and written by Peter Varo. Copyright (c) 2014           ##
##             License agreement is provided in the LICENSE file              ##
##                 For more info visit: http://www.cutils.org                 ##
##                                                                            ##
######################################################################## INFO ##

# Import Python modules
from os import makedirs
from os.path import dirname

# Module level constants
_TAB = ' '*4
_GUARD = '#ifndef {0}\n#define {0}\n\n'

_CHAR = 'static const char *{} =\n{};\n\n'
_CHAR_LINE = _TAB + '"{}\\n"'
_CHAR_SEP  = '\n'

_ARRAY = 'static const char *{}[] =\n{{\n{}\n}};\n\n'
_ARRAY_LINE = _TAB + '[{}] =\n{}'
_ARRAY_SEP  = ',\n\n'

_ENUM = 'enum\n{{\n{}\n}};\n\n'
_ENUM_LINE = _TAB + '{}'
_ENUM_SEP  = ',\n'



#------------------------------------------------------------------------------#
class ResourcePackingFinished(Exception): pass



#------------------------------------------------------------------------------#
def _file_to_string(file_path):
    with open(file_path, encoding='utf-8') as file:
        return _CHAR_SEP.join(_CHAR_LINE.format(line.strip('\n')) for line in file)



#------------------------------------------------------------------------------#
def _generate_content(stream, resource):
    # Write header comment or anything stored in 'header' key (optional)
    stream.write(resource.get('header', ''))

    # Open guard
    try:
        guard = resource['guard']
        stream.write(_GUARD.format(guard))
    except KeyError:
        raise KeyError("CRES: Resource file needs a 'guard' variable") from None

    try:
        inputs = resource['inputs']
    # If object does not contain 'inputs'
    except KeyError:
        raise KeyError("CRES: Resource file needs 'inputs' values") from None

    try:
        # If store values as items in array with regular indices
        array_name = resource.get('array_by_index', '')
        if array_name:
            # Create array
            stream.write(_ARRAY.format(
                array_name,
                _ARRAY_SEP.join(map(_file_to_string, inputs.values()))))
            # Finish
            raise ResourcePackingFinished

        # If store values as items in array with enum
        # variable names as designated initialisers
        array_name = resource.get('array_by_enum', '')
        if array_name:
            # Create enum
            stream.write(_ENUM.format(
                _ENUM_SEP.join(map(_ENUM_LINE.format, inputs.keys()))))
            # Create array
            stream.write(_ARRAY.format(
                array_name,
                _ARRAY_SEP.join(
                    _ARRAY_LINE.format(k, _file_to_string(v)) for k, v in inputs.items())))
            # Finish
            raise ResourcePackingFinished

        # If store each value as a separated variable
        for variable_name, input_path in inputs.items():
            stream.write(_CHAR.format(variable_name, _file_to_string(input_path)))
        raise ResourcePackingFinished

    # If object is not a dict-like object
    except AttributeError:
        raise AttributeError("CRES: Resource file 'inputs' values have"
                             " to be dictionary-like object") from None
    # If finished packing
    except ResourcePackingFinished:
        # Close guard
        stream.write('#endif /* {} */\n'.format(guard))



#------------------------------------------------------------------------------#
def pack(*resources):
    # Create file
    for resource in resources:
        try:
            # Get full output path
            output_path = resource['output']
            # Create output folders if they don't exist yet
            makedirs(dirname(output_path), exist_ok=True)
            # Generate and write out file
            with open(resource['output'], 'w', encoding='utf-8') as file:
                _generate_content(file, resource)
        except KeyError:
            raise KeyError("CRES: Resource file does not"
                           " have 'output' path") from None
