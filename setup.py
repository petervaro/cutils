#!/usr/bin/env python3
## INFO ########################################################################
##                                                                            ##
##                                   cutils                                   ##
##                                   ======                                   ##
##                                                                            ##
##                     Modern and Lightweight C Utilities                     ##
##                       Version: 0.8.90.767 (20140822)                       ##
##                                                                            ##
##                               File: setup.py                               ##
##                                                                            ##
##           Designed and written by Peter Varo. Copyright (c) 2014           ##
##             License agreement is provided in the LICENSE file              ##
##                 For more info visit: http://www.cutils.org                 ##
##                                                                            ##
######################################################################## INFO ##

import sys
from os.path import join
from stat import S_IEXEC
from os import stat, chmod, symlink
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
          license='MIT',
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
            symlink(src, dst)
            print(src, '=>', dst)
        except FileExistsError:
            print(dst, 'already exists')
        chmod(dst, stat(dst).st_mode | S_IEXEC)

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
