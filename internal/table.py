## INFO ########################################################################
##                                                                            ##
##                                   cutils                                   ##
##                                   ======                                   ##
##                                                                            ##
##                     Modern and Lightweight C Utilities                     ##
##                       Version: 0.8.72.413 (20140713)                       ##
##                                                                            ##
##                          File: internal/table.py                           ##
##                                                                            ##
##           Designed and written by Peter Varo. Copyright (c) 2014           ##
##             License agreement is provided in the LICENSE file              ##
##                 For more info visit: http://www.cutils.org                 ##
##                                                                            ##
######################################################################## INFO ##

#------------------------------------------------------------------------------#
# Dictionary to get access to the same object with two keys
#
# Dict2D[A:a] = [1, 2, 3]
# Dict2D[A] ==> [1, 2, 3]
# Dict2D[A].append(4)
# Dict2D[a] ==> [1, 2, 3, 4]
#
# BOTH KEYS HAS TO BE UNIQUE !
class Dict2D:

    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def __init__(self):
        self._data = []
        self._link = {}
        self._keys = []

    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def __getitem__(self, key):
        return self._data[self._link[key]]

    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def __setitem__(self, key, value):
        # If key is a slice object
        try:
            key1 = key.start
            key2 = key.stop
        except AttributeError:
            raise AttributeError('Dict2D key has to be a slice object') from None
        self._data.append(value)
        self._link[key1] = self._link[key2] = len(self._data) - 1
        self._keys.append((key1, key2))

    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def __delitem__(self, key):
        # If key is a slice object
        try:
            key1 = key.start
            key2 = key.stop
        except AttributeError:
            raise AttributeError('Dict2D key has to be a slice object') from None
        index = self._link[key1]
        self._data.pop(index)
        self._keys.pop(index)
        del self._link[key1]
        del self._link[key2]

    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def __repr__(self):
        return '{{{}}}'.format(', '.join('({}:{}): {}'.format(k1, k2, v)
                                         for (k1, k2), v in self.items()))

    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def __len__(self):
        return len(self._keys)

    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def keys(self):
        yield from self._keys

    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def values(self):
        return self._data

    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def items(self):
        yield from zip(self._keys, self._data)

    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def get(self, key, default):
        try:
            return self[key]
        except KeyError:
            return default

    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def setdefault(self, key1, key2, default):
        try:
            return self[key1]
        except KeyError:
            self[key1:key2] = default
            return default



#------------------------------------------------------------------------------#
# Table like dictionary implementation to
# get access from row to all columns or
# from column to all row value
#
#        +---+---+---+
#        | a | b | c |
#    +---+---+---+---+
#    | A | 1 | 4 |   |
#    +---+---+---+---+
#    | B |   | 5 | 9 |
#    +---+---+---+---+
#
# Table[A:a] = 1
# Table[A:b] = 4
#
# Table[A] ==> {a: 1, b: 4}
# Table[B] ==> {b: 5, c: 9}
# Table[a] ==> {A: 1}
# Table[b] ==> {A: 4, B: 5}
# Table[c] ==> {B: 9}
class Table:

    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def __init__(self, row=dict, column=dict):
        # Store base types of row and column
        self._row_type = row
        self._col_type = column
        # Set row and column
        self._row = row()
        self._col = column()

    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def __getitem__(self, key):
        # Try to find it in row or column
        try:
            return self._row[key]
        except KeyError:
            return self._col[key]

    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def __setitem__(self, key, value):
        # If key is a slice object
        try:
            row = key.start
            col = key.stop
        except AttributeError:
            raise AttributeError('Table key has to be a slice object') from None
        # Set data to be accessible from row
        self._row.setdefault(row, self._col_type())[col] = value
        # Set data to be accessible from column
        self._col.setdefault(col, self._row_type())[row] = value

    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def __delitem__(self, key):
        try:
            for col in self._row[key]:
                del self._col[col][key]
            del self._row[key]
        except KeyError:
            for row in self._col.pop(key, ()):
                del self._row[row][key]

    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def get(self, key, default=None):
        try:
            return self[key]
        except KeyError:
            return default

    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def setdefault(self, row, col, default=None):
        try:
            return self[row][col]
        except KeyError:
            self[row:col] = default
            return default

    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def rows(self):
        return self._row.keys()

    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
    def columns(self):
        return self._col.keys()
