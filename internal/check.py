## INFO ########################################################################
##                                                                            ##
##                                   cutils                                   ##
##                                   ======                                   ##
##                                                                            ##
##                     Modern and Lightweight C Utilities                     ##
##                       Version: 0.8.72.453 (20140713)                       ##
##                                                                            ##
##                          File: internal/check.py                           ##
##                                                                            ##
##           Designed and written by Peter Varo. Copyright (c) 2014           ##
##             License agreement is provided in the LICENSE file              ##
##                 For more info visit: http://www.cutils.org                 ##
##                                                                            ##
######################################################################## INFO ##

from sys import (exit as sys_exit,
                 argv as sys_argv)
try:
    from pyhashxx import Hashxx as Hash
except ImportError:
    # https://code.google.com/p/xxhash
    print("CUTILS: please install pyhashxx for faster file "
          "checking, by runring 'pip3 install pyhashxx'")
    from hashlib import sha1 as Hash
from os.path import (getmtime as os_path_getmtime,
                     join as os_path_join,
                     isfile as os_path_isfile,
                     abspath as os_path_abspath)
from pickle import (dump as pickle_dump,
                    load as pickle_load,
                    HIGHEST_PROTOCOL as pickle_HIGHEST_PROTOCOL)

#------------------------------------------------------------------------------#
class Checker:

    BLOCK_SIZE = 65536

    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    # reset => regenerate cache files
    # lazy_update => the file checksums will only update on Checker's exit.
    #                this makes it easy to process all files which are depending
    #                on the same file(s). That/Those file(s)'s checksum won't be
    #                updated until all the other files depend on it/them updated
    def __init__(self, folder, file, reset=False, lazy_update=False):
        self._file = os_path_join(folder, file)
        self._cache = cache = {}
        self._lazy_update = lazy_update
        self._last = None
        if reset:
            return
        # If cache file already exists
        try:
            with open(self._file, 'rb') as file:
                for filepath, checksum in pickle_load(file).items():
                    # If file still exists
                    if os_path_isfile(filepath):
                        cache[filepath] = checksum
                if lazy_update:
                    self._lcache = cache.copy()
        except (FileNotFoundError, EOFError):
            pass

    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def __enter__(self):
        return self

    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def __exit__(self, *exceptions):
        cache = self._lcache if self._lazy_update else self._cache
        # If the context was exited without an exception
        if not all(exceptions):
            with open(self._file, 'wb') as file:
                pickle_dump(cache, file, pickle_HIGHEST_PROTOCOL)

    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def _hash(self, filepath, block_size):
        checksum = Hash()
        with open(filepath, 'rb') as file:
            buffer = file.read(block_size)
            while buffer:
                checksum.update(buffer)
                buffer = file.read(block_size)
        return checksum.digest()

    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def ischanged(self, filepath, update=True):
        # Get local references
        cache = self._cache
        self._last = last = os_path_abspath(filepath)
        checksum = self._hash(last, self.BLOCK_SIZE)
        # If file didn't change
        if cache.get(last, -1.0) == checksum:
            return False
        # If file changed
        (self._lcache if self._lazy_update else cache)[last] = checksum
        return True

    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    # If the caller updating the file based if it has been chenged before last
    # check the cache needs to be updated after the modification, otherwise
    # ischanged() will always return True
    def update(self):
        last  = self._last
        cache = self._cache
        # If this method accidentally called before the ischanged method
        if cache.get(last, None):
            # Update checksum
            checksum = self._hash(last, self.BLOCK_SIZE)
            (self._lcache if self._lazy_update else cache)[last] = checksum
