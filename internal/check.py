## INFO ########################################################################
##                                                                            ##
##                                   cutils                                   ##
##                                   ======                                   ##
##                                                                            ##
##                     Modern and Lightweight C Utilities                     ##
##                       Version: 0.8.72.359 (20140711)                       ##
##                                                                            ##
##                          File: internal/check.py                           ##
##                                                                            ##
##           Designed and written by Peter Varo. Copyright (c) 2014           ##
##             License agreement is provided in the LICENSE file              ##
##                 For more info visit: http://www.cutils.org                 ##
##                                                                            ##
######################################################################## INFO ##

try:
    from pyhashxx import Hashxx as Hash
except ImportError:
    # https://code.google.com/p/xxhash/
    print("CUTILS: run 'pip3 install pyhashxx' for faster file checking")
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
    # TODO: remove folder argument
    def __init__(self, folder, file, reset=False):
        self.file = os_path_join(folder, file)
        self.cache = cache = {}
        if reset:
            return
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
    def _hash(self, filepath, block_size):
        checksum = Hash()
        with open(filepath, 'rb') as file:
            buffer = file.read(block_size)
            while buffer:
                checksum.update(buffer)
                buffer = file.read(block_size)
        return checksum.digest()

    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def ischanged(self, filepath):
        # Get local references
        cache = self.cache
        self.last = last = os_path_abspath(filepath)
        checksum = self._hash(last, self.BLOCK_SIZE)

        # 1) Generate HASH
        # 2) Copy cache files and check.py and VERSION
        # 3) Discard all changes
        # 4) Paste back files
        # 5) Run hash again
        # pip3 install pyhashxx

        # If file didn't change
        if cache.get(last, -1.0) == checksum:
            return False
        # If file changed
        cache[last] = checksum
        return True

    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    # If the caller updating the file based if it has been chenged before last
    # check the cache needs to be updated after the modification, otherwise
    # ischanged() will always return True
    def update(self):
        last  = self.last
        cache = self.cache
        if cache.get(last, None):
            cache[last] = self._hash(last, self.BLOCK_SIZE)
