#!/usr/bin/env python3
## INFO ########################################################################
##                                                                            ##
##                                   cutils                                   ##
##                                   ======                                   ##
##                                                                            ##
##                     Modern and Lightweight C Utilities                     ##
##                       Version: 0.8.96.268 (20141023)                       ##
##                                                                            ##
##                               File: setup.py                               ##
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

import sys
from os.path import join
from os import stat, chmod, symlink, remove
from distutils.core import setup
from distutils.sysconfig import get_python_lib

#------------------------------------------------------------------------------#
# Get command-line input
script, option, *folders = sys.argv

# If binary folder passed
try:
    # Installation path
    PKG_PATH = get_python_lib()
    INC_PATH, LIB_PATH, BIN_PATH = folders
    # Set argv back to normal, so that setup() can handle it
    sys.argv = script, option
except IndexError:
    pass

# Open version file and read back the most recent version info
with open('VERSION') as version:
    # Setup python package
    setup(name='cutils',
          version='.'.join(version.read().split('.')[:-1]),
          description='Modern and Lightweight C Utilities',
          author='Peter Varo',
          author_email='petervaro@sketchandprototype.com',
          license='GPLv3',
          platforms='Any',
          url='http://www.cutils.org',
          package_dir={'': 'pycutils'},
          packages=['cutils', 'cutils.internal'])

# Create the command-line tools
try:
    for file in ('ccom', 'cdoc', 'clic', 'cver', 'cenv'):
        dst = join(BIN_PATH, file)
        src = join(PKG_PATH, 'cutils', file + '.py')
        # If symlink already exists
        try:
            remove(dst)
        except FileNotFoundError:
            pass
        # Create symlink
        symlink(src, dst)
        # Change ownership (make it executable for everyone)
        chmod(dst, stat(dst).st_mode | 0o111)
        print(src, '=>', dst)

    # Because 'cenv' was the last one, the 'dst' is related to it
    with open(dst, 'r+') as cenv:
        # Set include and library locations based on teh makefile
        source = cenv.read()
        source = source.replace('__INCLUDE_DIR__', INC_PATH)
        source = source.replace('__LIBRARY_DIR__', LIB_PATH)
        cenv.seek(0)
        cenv.write(source)
        cenv.truncate()
except NameError as e:
    pass
