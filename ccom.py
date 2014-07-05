## INFO ########################################################################
##                                                                            ##
##                                   cutils                                   ##
##                                   ======                                   ##
##                                                                            ##
##                     Modern and Lightweight C Utilities                     ##
##                       Version: 0.8.72.004 (20140703)                       ##
##                                                                            ##
##                               File: ccom.py                                ##
##                                                                            ##
##           Designed and written by Peter Varo. Copyright (c) 2014           ##
##             License agreement is provided in the LICENSE file              ##
##                 For more info visit: http://www.cutils.org                 ##
##                                                                            ##
######################################################################## INFO ##

# Import Python modules
from os import walk as os_walk
from sys import argv as sys_argv
from os.path import join as os_path_join
from itertools import chain as itertools_chain
from re import (IGNORECASE as re_IGNORECASE,
                MULTILINE as re_MULTILINE,
                DOTALL as re_DOTALL,
                VERBOSE as re_VERBOSE,
                split as re_split,
                finditer as re_finditer,
                compile as re_compile)

# Import cutils modules
import comment

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
# Special tags to look for
WORDS = r'fixme', r'todo', r'bug', r'hack', r'note', r'xxx'
MARKS = {r'!'*3: 'alert', r'?'*3: 'question'}
# Extension of files to look in
EXTENSIONS = '.h', '.c', '.py', '.fs', '.vs', '.yaml'

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
_SHORT = ' '*2
_LONG  = 10
_BREAK = re_compile(r'\n([^\S\n]*)')
# Yaml notation of a post
_ITEM = ('{short}#{sep}#\n'
         '{short}# {index}\n'
         '{short}- file: {file}\n'
            '{long}line: {line}\n'
            '{long}note: |\n'
                        '{msg}\n')

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
# Regex of comment blocks
# TODO: consider: can <space> be anything?
#       Like this example:
#       some line of code # tag: starts here
#                         #      another line goes here
#                         #      and the third here..
#       the code goes on...
_COMMENT = r"""
# Capture space before except new line
(?P<space>^[^\S\n]*)
# Capture line and block comments
((?P<line>{})|(?P<block>{}))\s*
    # Comment followed by either word or special mark
    (((?P<word>{})\s*:\s*(?P=line)*)|(?P<mark>{}))\s*
    (?P<content>
        # if line comment:
        (?(line)
            # capture lines until first non-commented line
            (.*?\n(?![^\S\n]*(?P=line)))
        |# else:
            # capture until the end of block comment
            (.*?(?P<end>{}))))
"""

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
def _format(storage, string, pattern, padding):
    # Split content by lines and leading indentation
    linedata = iter(re_split(pattern, string))
    # Add first line to content
    storage.append(_LONG*' ' + next(linedata))
    # For each padding and content of line
    for space, data in zip(linedata, linedata):
        # Normalise leading padding if necessary
        indent = len(space) - padding
        storage.append((_LONG + (indent if indent > 0 else 0))*' ' + data)
    # If last line of comment has no new line at the end, append one
    if not storage[-1].endswith('\n'):
        storage[-1] += '\n'

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
def _search(collected, content_pattern, newline_pattern, string, filepath, marks):
    # Collect all locations of new lines in string
    line = 0
    newlines = [match.start() for match in re_finditer(newline_pattern, string)]
    # For each match in
    for match in re_finditer(content_pattern, string):
        # Character-index where the match starts
        start = match.start()
        # Get matching groups
        ml, mb, mc = match.group('line', 'block', 'content')

        content = []
        space = len(match.group('space'))
        msc = match.start('content')
        # If match line-comment
        if ml:
            _format(storage = content,
                    string  = mc,
                    pattern = re_compile(r'\n([^\S\n]*{}[^\S\n]*)'.format(ml)),
                    padding = space + (msc - match.start('line')))
        # If match block-comment
        else:
            _format(storage = content,
                    string  = mc[:-len(mb)],
                    pattern = _BREAK,
                    padding = space + (msc - match.start('block')))

        # Format uppercase tag
        word, mark = match.group('word', 'mark')
        tag = (word or marks[mark]).upper()
        # Get line-number
        line = next(l for l, c in enumerate(newlines[line:], start=line + 1) if c > start)

        # If post type already exits
        try:
            collected[tag].append((filepath, line, content))
        # If not create new post type
        except KeyError:
            collected[tag] = [(filepath, line, content)]

#------------------------------------------------------------------------------#
# TODO: add 'exceptions' argument
def collect(path,
            line  = comment.LINE,
            block = comment.BLOCK,
            tags  = WORDS,
            marks = MARKS,
            extensions=EXTENSIONS):
    # Process block comment marks
    blocks_open, blocks_close = comment.block_comments(block)

    # Collection of all posts
    collected = {}
    # Compile regular expression patterns
    pattern1 = re_compile(_COMMENT.format(r'|'.join(map(comment.escape, line)),
                                          blocks_open,
                                          r'|'.join(map(comment.escape, tags)),
                                          r'|'.join(map(comment.escape, marks)),
                                          blocks_close),
                         flags=re_IGNORECASE | re_DOTALL | re_MULTILINE | re_VERBOSE)
    pattern2 = re_compile(r'\n')

    # TODO: Improve performance by using the check.py module's Checker
    #       1) read back the previously generated TODO file
    #       2) _search should extend the parsed data structure
    #       3) when loading keep the order if necessary
    #       4) when loading or when writing make both structure compatible
    #          to each other: right now the collected is a tuple with three
    #          items, while the parsed YAML doc is a dictionary. Also: the
    #          list of line in collected has indentation, while the loaded
    #          lines doesn't have one

    # Scan through all files and folders
    for root, dirs, filenames in os_walk(path):
        for filename in filenames:
            for extension in extensions:
                if filename.endswith(extension):
                    filepath = os_path_join(root, filename)[2:]
                    with open(filepath, encoding='utf-8') as file:
                        _search(collected, pattern1, pattern2,
                                file.read(), filepath, marks)
    # Open the todo file and write out the results
    with open('TODO', 'w', encoding='utf-8') as todo:
        # Make it compatible with cver.py
        todo.write('## INFO ##\n'*2)
        # Format TODO file as yaml
        for key in itertools_chain(tags, marks.values()):
            KEY = key.upper()
            try:
                post = collected[KEY]
                todo.write('\n#{}#\n'.format('-'*78))
                todo.write('{}: # POSTS: {}\n'.format(KEY, len(post)))
                for i, (filename, linenumber, content) in enumerate(post, start=1):
                    todo.write(_ITEM.format(msg='\n'.join(content),
                                            index=i,
                                            short=_SHORT,
                                            long=_SHORT*2,
                                            sep='- '*38,
                                            file=filename,
                                            line=linenumber))
                todo.write('\n')
            except KeyError:
                continue
        print('TODO file {!r} has been '
              'successfully generated.'.format(os_path_join(path, 'todo')))

#------------------------------------------------------------------------------#
if __name__ == '__main__':
    try:
        script, folder, *rest = sys_argv
        collect(folder)
    except ValueError:
        print('Warning: No folder provided')
