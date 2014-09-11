## INFO ########################################################################
##                                                                            ##
##                                   cutils                                   ##
##                                   ======                                   ##
##                                                                            ##
##                     Modern and Lightweight C Utilities                     ##
##                       Version: 0.8.90.725 (20140821)                       ##
##                                                                            ##
##                 File: pycutils/cutils/internal/comment.py                  ##
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

# Comment symbols
LINE   = '#', '//'
BLOCK  = {'/*': '*/'}

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
# Regex escape sequence
_ESCAPE = {'.' : r'\.',    '^' : r'\^',    '$' : r'\$',    '*' : r'\*',
           '+' : r'\+',    '?' : r'\?',    '{' : r'\{',    '}' : r'\}',
           '\\': r'\\',    '[' : r'\[',    ']' : r'\]',    '|' : r'\|',
           '(' : r'\(',    ')' : r'\)',    '#' : r'[#]'}

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
def escape(string):
    return r''.join(_ESCAPE.get(char, char) for char in string)

#------------------------------------------------------------------------------#
def block_comments(block):
    # Number of opening and closing symbols
    length = len(block)
    # Process block comment marks
    for index, (opening, closing) in enumerate(block.items()):
        # Make sure all regex chars are escaped
        opening = escape(opening)
        closing = escape(closing)
        # Except first
        if index:
            blocks_open  = r'{}|(?P<b{}>{})'.format(blocks_open, index, opening)
            blocks_close = r'(?(b{}){}|{})'.format(index, closing, blocks_close)
        # First
        else:
            blocks_open  = r'(?P<b0>{})'.format(opening) if length > 1 else opening
            blocks_close = closing
    # Return processed strings
    return blocks_open, blocks_close
