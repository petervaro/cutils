## INFO ########################################################################
##                                                                            ##
##                                   cutils                                   ##
##                                   ======                                   ##
##                                                                            ##
##                     Modern and Lightweight C Utilities                     ##
##                       Version: 0.8.96.144 (20140907)                       ##
##                                                                            ##
##                           File: internal/capi.py                           ##
##                                                                            ##
##   For more information about the project, visit <http://www.cutils.org>.   ##
##                       Copyright (C) 2014 Peter Varo                        ##
##                                                                            ##
##  This program is free software: you can redistribute it and/or modify it   ##
##   under the terms of the GNU General Public License as published by the    ##
##       Free Software Foundation, either version 3 of the License, or        ##
##                    (at your option) any later version.                     ##
##                                                                            ##
##    This program is distributed in the hope that it will be useful, but     ##
##         WITHOUT ANY WARRANTY; without even the implied warranty of         ##
##            MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.            ##
##            See the GNU General Public License for more details.            ##
##                                                                            ##
##     You should have received a copy of the GNU General Public License      ##
##     along with this program, most likely a file in the root directory,     ##
##        called 'LICENSE'. If not, see <http://www.gnu.org/licenses>.        ##
##                                                                            ##
######################################################################## INFO ##

# Import python modules
import os.path
from collections import OrderedDict

# Import cutils modules
from generator import auto_api
# Import cutils modules
import output
import unit_testing
import dynamic_array
import singly_linked_list
import static_hash_map

#------------------------------------------------------------------------------#
FOLDER = os.path.dirname(os.path.dirname(__file__))

# It is ordered, to change as less in the file as possible
collected = OrderedDict()
for module in (dynamic_array, singly_linked_list, #static_hash_map,
               unit_testing,
               output):
    module.generate(FOLDER, collected)

# Generate _Generics
auto_api(os.path.join(FOLDER, 'capi.h'), collected)
