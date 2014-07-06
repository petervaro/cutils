## INFO ########################################################################
##                                                                            ##
##                                   cutils                                   ##
##                                   ======                                   ##
##                                                                            ##
##                     Modern and Lightweight C Utilities                     ##
##                       Version: 0.8.72.026 (20140706)                       ##
##                                                                            ##
##                        File: internal/pre_commit.py                        ##
##                                                                            ##
##           Designed and written by Peter Varo. Copyright (c) 2014           ##
##             License agreement is provided in the LICENSE file              ##
##                 For more info visit: http://www.cutils.org                 ##
##                                                                            ##
######################################################################## INFO ##

from os import system

# TODO: generate documentation to some better place, maybe /tmp ?
#       after committed, change the branch copy the content and
#       then commit changed to the gh-pages branch and switch
#       back to master branch

# TODO: Make error messages and reports of cver/cdoc/ccom/clic similar!

system('python3 cver.py')
system('python3 cdoc.py doc/src ../../../temporary_stuffs/git_shit')
system('python3 ccom.py .')
system('python3 clic.py .')

