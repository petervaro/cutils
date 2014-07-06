## INFO ########################################################################
##                                                                            ##
##                                   cutils                                   ##
##                                   ======                                   ##
##                                                                            ##
##                     Modern and Lightweight C Utilities                     ##
##                       Version: 0.8.72.028 (20140706)                       ##
##                                                                            ##
##                          File: internal/check.py                           ##
##                                                                            ##
##           Designed and written by Peter Varo. Copyright (c) 2014           ##
##             License agreement is provided in the LICENSE file              ##
##                 For more info visit: http://www.cutils.org                 ##
##                                                                            ##
######################################################################## INFO ##

from os.path import (getmtime as os_path_getmtime,
                     join as os_path_join,
                     isfile as os_path_isfile,
                     abspath as os_path_abspath)
from pickle import (dump as pickle_dump,
                    load as pickle_load,
                    HIGHEST_PROTOCOL as pickle_HIGHEST_PROTOCOL)

#------------------------------------------------------------------------------#
class Checker:

    # Class level constant
    FILE = '.cutils_filescache'

    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def __init__(self, folder):
        self.file = os_path_join(folder, self.FILE)
        self.cache = cache = {}
        # If cache file already exists
        try:
            with open(self.file, 'rb') as file:
                for filepath, mtime in pickle_load(file).items():
                    # If file still exists
                    if os_path_isfile(filepath):
                        cache[filepath] = mtime
        except (FileNotFoundError, EOFError):
            pass

    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def __enter__(self):
        return self

    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def __exit__(self, *exceptions):
        # If the context was exited without an exception
        if not all(exceptions):
            with open(self.file, 'wb') as file:
                pickle_dump(self.cache, file, pickle_HIGHEST_PROTOCOL)

    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def ischanged(self, filepath):
        # Get local references
        cache = self.cache
        self.last = last = os_path_abspath(filepath)
        mtime = os_path_getmtime(last)
        # If file didn't change
        if cache.get(last, -1.0) == mtime:
            return False
        # If file changed
        cache[last] = mtime
        return True

    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    # If the caller updating the file based if it has been chenged before last
    # check the cache needs to be updated after the modification, otherwise
    # ischanged() will always return True
    def update(self):
        last  = self.last
        cache = self.cache
        if cache.get(last, None):
            cache[last] = os_path_getmtime(last)
