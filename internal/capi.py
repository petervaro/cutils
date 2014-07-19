## INFO ########################################################################
##                                                                            ##
##                                   cutils                                   ##
##                                   ======                                   ##
##                                                                            ##
##                     Modern and Lightweight C Utilities                     ##
##                       Version: 0.8.72.580 (20140719)                       ##
##                                                                            ##
##                           File: internal/capi.py                           ##
##                                                                            ##
##           Designed and written by Peter Varo. Copyright (c) 2014           ##
##             License agreement is provided in the LICENSE file              ##
##                 For more info visit: http://www.cutils.org                 ##
##                                                                            ##
######################################################################## INFO ##

# Import python modules
from collections import OrderedDict
from os.path import (join as os_path_join,
                     dirname as os_path_dirname)

# Import cutils modules
from generator import auto_api
# Import cutils modules
import dynamic_array
import unit_testing

#------------------------------------------------------------------------------#
FOLDER = os_path_dirname(os_path_dirname(__file__))

# It is ordered, to change as less in the file as possible
collected = OrderedDict()
for module in (dynamic_array, unit_testing):
    module.generate(FOLDER, collected)

# Generate _Generics
auto_api(os_path_join(FOLDER, 'capi.h'), collected)
