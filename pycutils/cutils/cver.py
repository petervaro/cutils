#!/usr/bin/env python3
## INFO ########################################################################
##                                                                            ##
##                                   cutils                                   ##
##                                   ======                                   ##
##                                                                            ##
##                     Modern and Lightweight C Utilities                     ##
##                       Version: 0.8.90.752 (20140822)                       ##
##                                                                            ##
##                       File: pycutils/cutils/cver.py                        ##
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

# Import Python modules
from os.path import join
from datetime import datetime
from re import (findall as re_findall,
                compile as re_compile)

# Module level constants
_VERSION  = 'VERSION'

#------------------------------------------------------------------------------#
def version(infolder, sub_max, rev_max, build_max, main=0, sub=1, rev=0, build=0):
    # Funtion level constants
    DATETIME = datetime.now().strftime('%Y%m%d')
    REGEXP   = re_compile(r'^\s*(\d+)\.(\d+)\.(\d+)\.(\d+)\s*\(\d+\)\s*$')
    FORMAT   = '{{}}.{{:0{}d}}.{{:0{}d}}.{{:0{}d}} ({{}})'.format(
                    *map(lambda v: len(str(v)), (sub_max, rev_max, build_max)))
    # Create filepath
    filepath = join(infolder, _VERSION)
    # If file already exists open it
    try:
        with open(filepath, 'r+') as file:
            try:
                # Parse file and get values
                main, sub, rev, build = map(int, re_findall(REGEXP, file.read())[0])
                # Increase values if necessary
                build += 1
                if build > build_max:
                    build = 0
                    rev += 1
                    if rev > rev_max:
                        rev = 0
                        sub += 1
                        if sub > sub_max:
                            sub = 0
                            main += 1
                # Write changes back to file
                file.seek(0)
                file.write(FORMAT.format(main, sub, rev, build, DATETIME))
                file.truncate()
            # If version format in file is invalid
            except IndexError:
                raise Exception('Invalid version format '
                                'in {!r} file'.format(filepath)) from None
    # Create a new file to store version data
    # and write intial values
    except FileNotFoundError:
        with open(filepath, 'w') as file:
            file.write(FORMAT.format(main, sub, rev, build, DATETIME))
    # Return current version
    return main, sub, rev, build, DATETIME

#------------------------------------------------------------------------------#
if __name__ == '__main__':
    from sys import argv
    script, folder, *rest = argv
    version(infolder=fodler,
            sub_max=9,
            rev_max=99,
            build_max=999)
    print('='*80)
    print('CVER: Version informations successfully updated.\n')
