#!/usr/bin/env python3
## INFO ########################################################################
##                                                                            ##
##                                   cutils                                   ##
##                                   ======                                   ##
##                                                                            ##
##                     Modern and Lightweight C Utilities                     ##
##                       Version: 0.8.90.725 (20140821)                       ##
##                                                                            ##
##                       File: pycutils/cutils/ccom.py                        ##
##                                                                            ##
##           Designed and written by Peter Varo. Copyright (c) 2014           ##
##             License agreement is provided in the LICENSE file              ##
##                 For more info visit: http://www.cutils.org                 ##
##                                                                            ##
######################################################################## INFO ##

# Import Python modules
from os import walk as os_walk
from sys import argv as sys_argv
from collections import OrderedDict
from itertools import chain as itertools_chain
from os.path import (join as os_path_join,
                     splitext as os_path_splitext,
                     isfile as os_path_isfile)
from re import (IGNORECASE as re_IGNORECASE,
                MULTILINE as re_MULTILINE,
                DOTALL as re_DOTALL,
                VERBOSE as re_VERBOSE,
                split as re_split,
                finditer as re_finditer,
                compile as re_compile)
from pickle import (dump as pickle_dump,
                    load as pickle_load,
                    HIGHEST_PROTOCOL as pickle_HIGHEST_PROTOCOL)

# Import cutils modules
from cutils.internal.table import Table as table_Table
from cutils.internal.check import Checker as check_Checker
from cutils.internal.comment import (LINE as comment_LINE,
                               BLOCK as comment_BLOCK,
                               escape as comment_escape,
                               block_comments as comment_block_comments)

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
# Special tags to look for
WORDS = r'fixme', r'todo', r'bug', r'hack', r'note', r'xxx'
MARKS = OrderedDict([(r'!'*3, 'alert'), (r'?'*3, 'question')])
# Extension of files to look in
EXTENSIONS = '.h', '.c', '.py', '.fs', '.vs', '.yaml'
EXCEPTIONS = ('.ccom_cache', '.ccom_todo',
              '.cdoc_cache', '.cdoc_toc',
              '.clic_cache')

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
    # Remove all data of file if exists
    del collected[filepath]
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
        # Store data
        collected.setdefault(filepath, tag, []).append((line, content))
    print('CCOM: processed {!r}'.format(filepath))

#------------------------------------------------------------------------------#
def collect(infolder,
            line  = comment_LINE,
            block = comment_BLOCK,
            tags  = WORDS,
            marks = MARKS,
            extensions=EXTENSIONS,
            exceptions=EXCEPTIONS):
    # Process block comment marks
    blocks_open, blocks_close = comment_block_comments(block)

    # TODO: Make hidden files OS independent, probably using
    #       https://docs.python.org/3.4/library/tempfile.html ?

    # FIXME: for some reason, if a comment-type ever existed in the TODO
    #        file, but after a while its posts are all gone, the keyword
    #        still remains there, according to the current TODO file,
    #        which still have the "QUESTIONS" keyword, and comment

    # TODO: Add explicit-remove/browsing capabilities of the .*_cache files
    #       (for example: if git reverted changes --> remove hash from cache file)
    #       The best solution would be a complete CLI tool, to read and manage
    #       and use the cutils command line tools

    # Compile regular expression patterns
    pattern1 = re_compile(_COMMENT.format(r'|'.join(map(comment_escape, line)),
                                          blocks_open,
                                          r'|'.join(map(comment_escape, tags)),
                                          r'|'.join(map(comment_escape, marks)),
                                          blocks_close),
                         flags=re_IGNORECASE | re_DOTALL | re_MULTILINE | re_VERBOSE)
    pattern2 = re_compile(r'\n')

    # Get previously generated collection of all posts
    COLLECTED = os_path_join(infolder, '.ccom_todo')
    try:
        with open(COLLECTED, 'rb') as file:
            collected = pickle_load(file)
    except (FileNotFoundError, EOFError):
        collected = table_Table(row=OrderedDict)

    # Clear cache -- remove all non-existing files
    for filepath in collected.rows():
        if not os_path_isfile(filepath):
            del collected[filepath]

    # Scan through all files and folders
    with check_Checker(infolder, file='.ccom_cache') as checker:
        for root, dirs, filenames in os_walk(infolder):
            for filename in filenames:
                name, extension = os_path_splitext(filename)
                if not extension:
                    extension = name
                if (filename not in exceptions and
                    extension in extensions and
                    extension not in exceptions):
                    filepath = os_path_join(root, filename)[2:]
                    if checker.ischanged(filepath):
                        with open(filepath, encoding='utf-8') as file:
                            _search(collected, pattern1, pattern2,
                                    file.read(), filepath, marks)

    # Save collection of all posts
    with open(COLLECTED, 'wb') as file:
        pickle_dump(collected, file, pickle_HIGHEST_PROTOCOL)

    # Open the todo file and write out the results
    with open('TODO', 'w', encoding='utf-8') as todo:
        # Make it compatible with cver.py
        todo.write('## INFO ##\n'*2)
        # Format TODO file as yaml
        for key in itertools_chain(tags, marks.values()):
            KEY = key.upper()
            try:
                types = collected[KEY].items()
                len_pos = todo.tell()
                # Offset for separator comment and
                # leading and trailing new lines
                todo.write(' '*82)
                todo.write('{}:\n'.format(KEY))
                index = 1
                for filename, posts in types:
                    for i, (linenumber, content) in enumerate(posts, start=index):
                        todo.write(_ITEM.format(msg='\n'.join(content),
                                                index=i,
                                                short=_SHORT,
                                                long=_SHORT*2,
                                                sep='- '*38,
                                                file=filename,
                                                line=linenumber))
                    index = i + 1
                todo.write('\n')
                # Move back to tag separator comment
                todo.seek(len_pos)
                todo.write('\n#{:-^78}#\n'.format(
                    ' {} POSTS IN {} FILES '.format(index - 1, len(types))))
                # Move back to the end
                todo.seek(0, 2)
            except KeyError:
                continue
        print('CCOM: placed {!r}'.format(os_path_join(infolder, 'TODO')))

#------------------------------------------------------------------------------#
if __name__ == '__main__':
    print('- '*40)
    try:
        script, folder, *rest = sys_argv
        collect(folder)
        print('='*80)
        print('CCOM: All special-comments has been successfully collected.\n')
    except ValueError:
        print('CCOM: !!! WARNING !!! No folder provided\n')
