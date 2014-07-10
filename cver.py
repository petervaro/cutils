#!/usr/bin/env python3
## INFO ########################################################################
##                                                                            ##
##                                   cutils                                   ##
##                                   ======                                   ##
##                                                                            ##
##                     Modern and Lightweight C Utilities                     ##
##                       Version: 0.8.72.331 (20140710)                       ##
##                                                                            ##
##                               File: cver.py                                ##
##                                                                            ##
##           Designed and written by Peter Varo. Copyright (c) 2014           ##
##             License agreement is provided in the LICENSE file              ##
##                 For more info visit: http://www.cutils.org                 ##
##                                                                            ##
######################################################################## INFO ##

# Import Python modules
from datetime import datetime
from re import (findall as re_findall,
                compile as re_compile)

# Module level constants
_VERSION  = 'VERSION'

#------------------------------------------------------------------------------#
def version(sub_max, rev_max, build_max, main=0, sub=1, rev=0, build=0):
    # Funtion level constants
    DATETIME = datetime.now().strftime('%Y%m%d')
    REGEXP   = re_compile(r'^\s*(\d+)\.(\d+)\.(\d+)\.(\d+)\s*\(\d+\)\s*$')
    FORMAT   = '{{}}.{{:0{}d}}.{{:0{}d}}.{{:0{}d}} ({{}})'.format(
                    *map(lambda v: len(str(v)), (sub_max, rev_max, build_max)))
    # If file already exists open it
    try:
        with open(_VERSION, 'r+') as file:
            try:
                # Parse file and get values
                main, sub, rev, build = map(int, re_findall(REGEXP, file.read())[0])
                # Increase values if necessary
                build += 1
                if build > build_max:
                    rev += 1
                    if rev > rev_max:
                        sub += 1
                        if sub > sub_max:
                            main += 1
                # Write changes back to file
                file.seek(0)
                file.write(FORMAT.format(main, sub, rev, build, DATETIME))
                file.truncate()
            # If version format in file is invalid
            except IndexError:
                raise Exception('Invalid version format '
                                'in {!r} file'.format(_VERSION)) from None
    # Create a new file to store version data
    # and write intial values
    except FileNotFoundError:
        with open(_VERSION, 'w') as file:
            file.write(FORMAT.format(main, sub, rev, build, DATETIME))

#------------------------------------------------------------------------------#
if __name__ == '__main__':
    # TODO: ask for folder or file input
    version(sub_max=9,
            rev_max=99,
            build_max=999)
    print('='*80)
    print('CVER: Version informations successfully updated.\n')
