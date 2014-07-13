#!/usr/bin/env python3
## INFO ########################################################################
##                                                                            ##
##                                   cutils                                   ##
##                                   ======                                   ##
##                                                                            ##
##                     Modern and Lightweight C Utilities                     ##
##                       Version: 0.8.72.453 (20140713)                       ##
##                                                                            ##
##                        File: internal/pre_commit.py                        ##
##                                                                            ##
##           Designed and written by Peter Varo. Copyright (c) 2014           ##
##             License agreement is provided in the LICENSE file              ##
##                 For more info visit: http://www.cutils.org                 ##
##                                                                            ##
######################################################################## INFO ##

from os import system
from sys import exit as sys_exit

# TODO: generate documentation to some better place, maybe /tmp ?
#       after committed, change the branch copy the content and
#       then commit changed to the gh-pages branch and switch
#       back to master branch

# TODO: Make error messages and reports of cver/cdoc/ccom/clic similar!

system('./cver.py')
system('./cdoc.py doc/src ../../../temporary_stuffs/cutils')
system('./ccom.py .')
system('./clic.py .')
sys_exit('pre-commit: success\n')
