#!/usr/bin/env python3
## INFO ########################################################################
##                                                                            ##
##                                   cutils                                   ##
##                                   ======                                   ##
##                                                                            ##
##                     Modern and Lightweight C Utilities                     ##
##                       Version: 0.8.96.244 (20140911)                       ##
##                                                                            ##
##                             File: dev/proj.py                              ##
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

# Import yaml modules
from yaml import load as yaml_load
try:
    from yaml import CLoader as yaml_Loader
except ImportError:
    from yaml import yaml_Loader

# Import cutils modules
from cutils.cver import version
from cutils.cdoc import document
from cutils.ccom import collect
from cutils.clic import header

# Module level constants
OVERWRITE=0

# TODO: generate documentation to some better place, maybe /tmp ?
#       after committed, change the branch copy the content and
#       then commit changed to the gh-pages branch and switch
#       back to master branch

# TODO: Make error messages and reports of cver/cdoc/ccom/clic similar!

#------------------------------------------------------------------------------#
# Increase version number
version(infolder='.',
        sub_max=9,
        rev_max=99,
        build_max=999)

# Process documents
document(infolder='./doc/src',
         outfolder='../../../temporary_stuffs/cutils',
         extension='.yaml',
         overwrite=OVERWRITE,
         loader=lambda s: yaml_load(s, Loader=yaml_Loader))

# Collect special comments
collect('.', overwrite=OVERWRITE)

# Generate license headers
header('.', overwrite=OVERWRITE)

# Feedback
print('cutils: project is up to date', end='\n'*2)
