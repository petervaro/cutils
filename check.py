## INFO ########################################################################
##                                                                            ##
##                                   cutils                                   ##
##                                   ======                                   ##
##                                                                            ##
##                     Modern and Lightweight C Utilities                     ##
##                       Version: 0.8.72.004 (20140703)                       ##
##                                                                            ##
##                               File: check.py                               ##
##                                                                            ##
##           Designed and written by Peter Varo. Copyright (c) 2014           ##
##             License agreement is provided in the LICENSE file              ##
##                 For more info visit: http://www.cutils.org                 ##
##                                                                            ##
######################################################################## INFO ##

from contextlib import ContextDecorator
from re import (compile as re_compile,
                finditer as re_finditer,
                MULTILINE as re_MULTILINE)
from os.path import (getmtime as os_path_getmtime,
                     join as os_path_join)

#------------------------------------------------------------------------------#
class Checker:

    # Class level constant
    FILE = '.cutils_filescache'
    FORMAT = '{!r} {}\n'
    REGEXP = re_compile(r"^\s*(?P<quote>'|\")(?P<path>.+)(?P=quote)"
                        r"\s*(?P<time>\d+.\d)+\s*$", flags=re_MULTILINE)

    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def __init__(self, folder):
        REGEXP = self.REGEXP
        self.file = os_path_join(folder, self.FILE)
        self.root = folder
        self.cache = cache = {}
        # If cache file already exists
        try:
            with open(self.file, 'r') as file:
                for match in re_finditer(REGEXP, file.read()):
                    try:
                        filepath, mtime = match.group('path', 'time')
                        cache[filepath] = float(mtime)
                    except TypeError:
                        pass
        except FileNotFoundError:
            pass

    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def __enter__(self):
        return self

    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def __exit__(self, *exceptions):
        FORMAT = self.FORMAT
        # If the context was exited without an exceptio
        if not all(exceptions):
            with open(self.file, 'w') as file:
                for key, value in self.cache.items():
                    file.write(FORMAT.format(key, value))

    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def ischanged(self, filepath, absolute_path=False):
        # Get local references
        cache = self.cache
        self.last = last = filepath if absolute_path else os_path_join(self.root, filepath)
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
