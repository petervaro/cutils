## INFO ##
## INFO ##

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

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
# Comment symbols
LINE = r'[#]', r'//'
BLOCK  = r'/\*', r'\*/'
# Special tags to look for
WORDS = r'fixme', r'note', r'bug', r'todo', r'hack', r'xxx'
MARKS = {r'!'*3: 'alert', r'?'*3: 'question'}
# Extension of files to look in
EXTENSIONS = '.h', '.c', '.py', '.fs', '.vs', '.yaml'

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
_SHORT = ' '*2
_LONG  = 10
# Yaml notation of a post
_ITEM = ('{short}#{sep}#\n'
         '{short}- file: {file}\n'
            '{long}line: {line}\n'
            '{long}note: |\n'
                        '{msg}\n')

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
# Regex of comment blocks
_COMMENT = r"""
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
# Regex escape sequence
_ESCAPE = {'.' : r'\.',    '^' : r'\^',    '$' : r'\$',    '*' : r'\*',
           '+' : r'\+',    '?' : r'\?',    '{' : r'\{',    '}' : r'\}',
           '\\': r'\\',    '[' : r'\[',    ']' : r'\]',    '|' : r'\|',
           '(' : r'\(',    ')' : r'\)',    '#' : r'[#]'}

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
def _escape(string):
    return r''.join(_ESCAPE.get(char, char) for char in string)

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
def _search(collected, content_pattern, newline_pattern, string, filepath):
    # Collect all locations of new lines in string
    line = 0
    newlines = [match.start() for match in re_finditer(newline_pattern, string)]
    # For each match in
    for match in re_finditer(content_pattern, string):
        # Character-index where teh match starts
        start = match.start()
        # Create space before comment lines
        wsf = _LONG*' '                                      # white-space-first
        wsr = (_LONG - (match.start('content') - start))*' ' # white-space-rest
        # Get matching groups
        ml, mb, mc = match.group('line', 'block', 'content')
        # If match line-comment
        if ml:
            br = re_compile(r'\n\s*(?:{})+'.format(ml))
            ws = wsr + len(ml)*' '
            content = [ws+s if i else wsf+s for i, s in enumerate(re_split(br, mc))]
        # If match block-comment
        else:
            content = [wsr+s if i else wsf+s for i, s in enumerate(mc[:-len(mb)].split('\n'))]

        # If last line of comment has no new line at the end, append one
        if not content[-1].endswith('\n'):
            content[-1] += '\n'

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
def collect(path,
            line  = LINE,
            block = BLOCK,
            tags  = WORDS,
            marks = MARKS,
            extensions=EXTENSIONS):
    # Collection of all posts
    collected = {}
    # Compile regular expression patterns
    pattern1 = re_compile(_COMMENT.format(r'|'.join(line),
                                          block[0],
                                          r'|'.join(tags),
                                          r'|'.join(_escape(key) for key in marks),
                                          block[1]),
                         flags=re_IGNORECASE | re_DOTALL | re_MULTILINE | re_VERBOSE)
    pattern2 = re_compile(r'\n')
    # Scan through all files and folders
    for root, dirs, filenames in os_walk(path):
        for filename in filenames:
            for extension in extensions:
                if filename.endswith(extension):
                    filepath = os_path_join(root, filename)[2:]
                    with open(filepath, encoding='utf-8') as file:
                        _search(collected, pattern1, pattern2, file.read(), filepath)
    # Open the todo file and write out the results
    with open('todo', 'w', encoding='utf-8') as todo:
        # Format TODO file as yaml
        for key in itertools_chain(tags, marks.values()):
            KEY = key.upper()
            try:
                comment = collected[KEY]
                todo.write('#{}#\n'.format('-'*78))
                todo.write(KEY + ':\n')
                todo.write('  - POSTS: {}\n'.format(len(comment)))
                for filename, linenumber, content in comment:
                    todo.write(_ITEM.format(msg='\n'.join(content),
                                            short=_SHORT,
                                            long=_SHORT*2,
                                            sep='- '*38,
                                            file=filename,
                                            line=linenumber))
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
