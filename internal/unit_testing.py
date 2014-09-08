## INFO ########################################################################
##                                                                            ##
##                                   cutils                                   ##
##                                   ======                                   ##
##                                                                            ##
##                     Modern and Lightweight C Utilities                     ##
##                       Version: 0.8.95.875 (20140901)                       ##
##                                                                            ##
##                       File: internal/unit_testing.py                       ##
##                                                                            ##
##           Designed and written by Peter Varo. Copyright (c) 2014           ##
##             License agreement is provided in the LICENSE file              ##
##                 For more info visit: http://www.cutils.org                 ##
##                                                                            ##
######################################################################## INFO ##

# Import cutils modules
from generator import methods, Function

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
NAME = 'Tester'
PREFIX = 'cutils_cutt'

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
_RETURN_DEF = ''



#------------------------------------------------------------------------------#
new_ = Function('new', 'void', ('{MAINTYPE}**', 't'),
                               ('size_t',      'c'))
new_.wrapping = _RETURN_DEF

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
del_ = Function('del', 'void', ('{MAINTYPE}*', 't'))
del_.wrapping = _RETURN_DEF



#------------------------------------------------------------------------------#
def generate(folder, macros_dict):
    methods(base_name=NAME,
            module_prefix=PREFIX,
            macros_dict=macros_dict,
            functions=(new_, del_))
