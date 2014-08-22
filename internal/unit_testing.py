## INFO ########################################################################
##                                                                            ##
##                                   cutils                                   ##
##                                   ======                                   ##
##                                                                            ##
##                     Modern and Lightweight C Utilities                     ##
##                       Version: 0.8.90.749 (20140821)                       ##
##                                                                            ##
##                       File: internal/unit_testing.py                       ##
##                                                                            ##
##           Designed and written by Peter Varo. Copyright (c) 2014           ##
##             License agreement is provided in the LICENSE file              ##
##                 For more info visit: http://www.cutils.org                 ##
##                                                                            ##
######################################################################## INFO ##

# Import cutils modules
from generator import args, methods

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
ARG1_T = '{0}*'
ARG1_N = 't'

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
_RETURN = ''
WRAPPERS = (
    # new
    ('void', 'new',
    args(ARG1_T + '*', ARG1_N, 'size_t', 'c'),
    _RETURN),

    # del
    ('void', 'del',
    args(ARG1_T, ARG1_N),
    _RETURN)
)

#------------------------------------------------------------------------------#
def generate(folder, macros_dict):
    methods(types=((ARG1_N, 'p', ''),),
            base_name='cutils_cutt_Tester',
            wrappers=WRAPPERS,
            macros_dict=macros_dict)
