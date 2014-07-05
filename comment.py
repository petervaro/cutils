## INFO ########################################################################
##                                                                            ##
##                                   cutils                                   ##
##                                   ======                                   ##
##                                                                            ##
##                     Modern and Lightweight C Utilities                     ##
##                       Version: 0.8.72.004 (20140703)                       ##
##                                                                            ##
##                              File: comment.py                              ##
##                                                                            ##
##           Designed and written by Peter Varo. Copyright (c) 2014           ##
##             License agreement is provided in the LICENSE file              ##
##                 For more info visit: http://www.cutils.org                 ##
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
