## INFO ########################################################################
##                                                                            ##
##                                   cutils                                   ##
##                                   ======                                   ##
##                                                                            ##
##                     Modern and Lightweight C Utilities                     ##
##                       Version: 0.8.72.365 (20140711)                       ##
##                                                                            ##
##                          File: internal/table.py                           ##
##                                                                            ##
##           Designed and written by Peter Varo. Copyright (c) 2014           ##
##             License agreement is provided in the LICENSE file              ##
##                 For more info visit: http://www.cutils.org                 ##
##                                                                            ##
######################################################################## INFO ##

#------------------------------------------------------------------------------#
# Table like dictionary implementation to get access
# to the same data with two different keys (row and column)
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