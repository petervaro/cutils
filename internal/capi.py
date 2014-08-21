## INFO ########################################################################
##                                                                            ##
##                                   cutils                                   ##
##                                   ======                                   ##
##                                                                            ##
##                     Modern and Lightweight C Utilities                     ##
##                       Version: 0.8.90.423 (20140817)                       ##
##                                                                            ##
##                           File: internal/capi.py                           ##
##                                                                            ##
##           Designed and written by Peter Varo. Copyright (c) 2014           ##
##             License agreement is provided in the LICENSE file              ##
##                 For more info visit: http://www.cutils.org                 ##
##                                                                            ##
######################################################################## INFO ##

# Import python modules
import os.path
from collections import OrderedDict

# Import cutils modules
from generator import auto_api
# Import cutils modules
import unit_testing
import dynamic_array
import singly_linked_list

#------------------------------------------------------------------------------#
FOLDER = os.path.dirname(os.path.dirname(__file__))

# It is ordered, to change as less in the file as possible
collected = OrderedDict()
for module in (dynamic_array, singly_linked_list, unit_testing):
    module.generate(FOLDER, collected)

# Generate _Generics
auto_api(os.path.join(FOLDER, 'capi.h'), collected)
