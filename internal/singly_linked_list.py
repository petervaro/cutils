## INFO ########################################################################
##                                                                            ##
##                                   cutils                                   ##
##                                   ======                                   ##
##                                                                            ##
##                     Modern and Lightweight C Utilities                     ##
##                       Version: 0.8.80.182 (20140722)                       ##
##                                                                            ##
##                    File: internal/singly_linked_list.py                    ##
##                                                                            ##
##           Designed and written by Peter Varo. Copyright (c) 2014           ##
##             License agreement is provided in the LICENSE file              ##
##                 For more info visit: http://www.cutils.org                 ##
##                                                                            ##
######################################################################## INFO ##

# Import cutils modules
from generator import args, methods

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
GUARD = 'SINGLY_LINKED_LIST'
LLIST = 'cutils_csll_SinglyLinkedList'

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
TYPES = ((),)

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
ARG1_T = '{0}*'
ARG1_N = 't'

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
_RETURN = ''
WRAPPERS = (
    # new
    ('void', 'new',
    args(ARG1_T + '*', ARG1_N),
    _RETURN),

    # del
    ('void', 'del',
    args(ARG1_T, ARG1_N),
    _RETURN)
)

#------------------------------------------------------------------------------#
def generate(folder, macros_dict):
    methods(types=TYPES,
            base_name=LLIST,
            wrappers=WRAPPERS,
            macros_dict=macros_dict)
