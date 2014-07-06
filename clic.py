## INFO ########################################################################
##                                                                            ##
##                                   cutils                                   ##
##                                   ======                                   ##
##                                                                            ##
##                     Modern and Lightweight C Utilities                     ##
##                       Version: 0.8.72.026 (20140706)                       ##
##                                                                            ##
##                               File: clic.py                                ##
##                                                                            ##
##           Designed and written by Peter Varo. Copyright (c) 2014           ##
##             License agreement is provided in the LICENSE file              ##
##                 For more info visit: http://www.cutils.org                 ##
##                                                                            ##
######################################################################## INFO ##

# Import python modules
from datetime import datetime
from os import walk as os_walk
from sys import argv as sys_argv
from os.path import (join as os_path_join,
                     getsize as os_path_getsize,
                     splitext as os_path_splitext)
from re import (DOTALL  as re_DOTALL,
                VERBOSE as re_VERBOSE,
                MULTILINE as re_MULTILINE,
                compile as re_compile,
                match as re_match)

# Import cutils modules
# FIXME: if modules cannot be found?
from internal.check import Checker as check_Checker
from internal.comment import (LINE as comment_LINE,
                              BLOCK as comment_BLOCK,
                              escape as comment_escape,
                              block_comments as comment_block_comments)

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
# Comment symbols
EXTENSIONS = ('.h', '.c', '.fs', '.vs', '.py', '.yaml',
              'make', 'makefile', 'todo', 'readme')

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
_FORMAT = {'CENTER': '^', 'LEFT':'<', 'RIGHT': '>'}
_FILES = 'VERSION', 'LICENSE'
_COMMENT = r"""
# Capture opening block
(?P<opening>
    ((?P<line>{})+|({}))
        \s*INFO\s*(?P<pad>.))
    .*? # previous content of comment
# Capture closing block
(?P<closing>
    (?P=pad)\s*INFO\s*
        # if line comment:
        (?(line)
            # capture line closing
            (?P=line)+
        |# else:
            # capture block closing
            ({})))
"""
_OPENING = '{{:{}<{}}}\n'
_CONTENT = '{{0}}{{0}} {{1:{}{}}} {{0}}{{0}}\n'
_CLOSING = '{{:{}>{}}}'

#------------------------------------------------------------------------------#
def _size(byte):
    # Convert and format byte-size
    K, M, G = 1024, 1024**2, 1024**3
    if byte >= G:
        return '{:.2f} GB'.format(byte/G)
    elif byte >= M:
        return '{:.2f} MB'.format(byte/M)
    elif byte >= K:
        return '{:.2f} KB'.format(byte/K)
    return '{} B'.format(byte)

#------------------------------------------------------------------------------#
def _comment(header, filepath, pattern, align, width):
    # Generate header-comment and place it into the file
    with open(filepath, 'r+', encoding='utf-8') as file:
        # Capture INFO comments
        try:
            stream = file.read()
            match = re_match(pattern, stream)
            # If there was a match
            if match:
                opening, pad, closing = match.group('opening', 'pad', 'closing')
                file.seek(0)
                file.write(_OPENING.format(pad, width).format(opening))
                # Substitute variables with values
                for line in header.split('\n'):
                    file.write(_CONTENT.format(align, width - 6).format(pad, line))
                file.write(_CLOSING.format(pad, width).format(closing))
                 # Write back content of file
                file.write(stream[match.end():])
                file.truncate()
                return True
        except UnicodeDecodeError:
            pass
        return False

#------------------------------------------------------------------------------#
def header(path,
           line=comment_LINE,
           block=comment_BLOCK,
           extensions=EXTENSIONS):
    # Compile regular expression pattern to match in scanned files
    pattern = re_compile(_COMMENT.format(r'|'.join(map(comment_escape, line)),
                                         *comment_block_comments(block)),
                         flags=re_DOTALL | re_VERBOSE | re_MULTILINE)
    # Define default values
    align = _FORMAT['CENTER']
    width = 80
    # Update values based on INFO file
    values = {}
    with open(os_path_join(path, 'INFO'), 'r', encoding='utf-8') as file:
        header = file.read()
        match = re_match(r'\s*#\s*format\s+'
                         r'((?P<align>CENTER|LEFT|RIGHT)\s+)?'
                         r'(?P<width>\d+)?', header)
        if match:
            align, width = match.group('align', 'width')
            align = _FORMAT.get(align, _FORMAT['CENTER'])
            try:
                width = int(width)
            except TypeError:
                pass
        # Add leading and trailing empty line
        header = '\n{}\n'.format(header[match.end():].strip())

    # Get file contents of special files
    for filename in _FILES:
        try:
            with open(os_path_join(path, filename), 'r', encoding='utf-8') as file:
                values[filename] = file.read().strip()
        except FileNotFoundError:
            values[filename] = ''

    # Get special values
    values['DATE'] = datetime.now().strftime('%Y.%m.%d')

    # Walk through all files and folders in the passed folder
    # FIXME: what if none of the files changed only INFO has been updated?
    with check_Checker(path) as checker:
        for root, dirs, files in os_walk(path):
            for file in files:
                # TODO: reconsider: if somethign like:
                #           if extension in extensions
                #       is better ot not -> profile it!
                for extension in extensions:
                    # If file has the proper extension
                    if file.lower().endswith(extension):
                        filepath = os_path_join(root, file)
                        # If file has been changed since last check
                        if checker.ischanged(filepath):
                            values['SIZE'] = _size(os_path_getsize(filepath))
                            # FIXME: make it more generic than ./ -- what if ../../?
                            values['FILE'] = filepath[2:] if filepath.startswith('./') else filepath
                            values['FILE_NAME'] = file
                            values['FILE_BASE'] = os_path_splitext(file)
                            if _comment(header.format(**values), filepath, pattern, align, width):
                                # Update checker after the file has been modified
                                checker.update()
                                # Report
                                print('CLIC: processed {!r}'.format(filepath))

#------------------------------------------------------------------------------#
if __name__ == '__main__':
    print('- '*40)
    try:
        script, folder, *rest = sys_argv
        header(folder)
        print('='*80)
        print('CLIC: All header-comments has been successfully generated.\n')
    except ValueError:
        print('CLIC: !!! WARNING !!! No folder provided\n')
