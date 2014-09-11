#!/usr/bin/env python3
## INFO ########################################################################
##                                                                            ##
##                                   cutils                                   ##
##                                   ======                                   ##
##                                                                            ##
##                     Modern and Lightweight C Utilities                     ##
##                       Version: 0.8.95.809 (20140828)                       ##
##                                                                            ##
##                       File: pycutils/cutils/cenv.py                        ##
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

# Import python modules
from sys import argv
from os import makedirs
from os.path import join
from errno import EEXIST
from traceback import extract_stack

# TODO: Add makefile variable naming option:
#       -prefix=myapp => myapp_NAME, myapp_C_SOURCES, etc.

#------------------------------------------------------------------------------#
# Module level constants
MAKE = """\
## INFO ##
## INFO ##

#------------------------------------------------------------------------------#
# User flags
IS_PRODUCTION=
USE_CUTILS=
PYTHON=/usr/local/bin/python3
#------------------------------------------------------------------------------#

# Filename of binary
app_NAME={APP_NAME}

# Output dirs
app_BUILD_OUT_DIR=build
app_BUILD_TMP_DIR=$(app_BUILD_OUT_DIR)/tmp

# Sources
app_C_SOURCES=$(wildcard *.c)
app_C_OBJECTS=$(addprefix $(app_BUILD_TMP_DIR)/, $(notdir $(app_C_SOURCES:.c=.o)))
app_INCLUDE_DIRS=__INCLUDE_DIR__
app_LIBRARY_DIRS=__LIBRARY_DIR__
app_LIBRARIES={CUTILS_LIB}
app_FRAMEWORKS=

# Flags
ifdef IS_PRODUCTION
CFLAGS+=-O3
else
CFLAGS+=-Wall -v -g
endif
CFLAGS+=-std=c11 $(addprefix -I, $(app_INCLUDE_DIRS))
LDFLAGS=$(addprefix -L, $(app_LIBRARY_DIRS))
LDFLAGS+=$(addprefix -l, $(app_LIBRARIES))

# Rules
.PHONY: all clean make_dirs

ifdef USE_CUTILS
.PHONY: call_cutils
all: call_cutils make_dirs $(app_NAME)

call_cutils:
    $(PYTHON) cver.py .
    $(PYTHON) cdoc.py . doc
    $(PYTHON) ccom.py .
    $(PYTHON) clic.py .
else
all: make_dirs $(app_NAME)
endif

$(app_NAME): $(app_C_OBJECTS)
\t$(LINK.c) $(app_C_OBJECTS) -o $(app_BUILD_OUT_DIR)/$(app_NAME)

$(app_BUILD_TMP_DIR)/%.o: %.c
\t$(CC) $(CFLAGS) -c -o $@ $<

make_dirs:
\tmkdir -p $(app_BUILD_TMP_DIR)

clean:
\trm -f -r $(app_BUILD_OUT_DIR)
"""

C = """\
/* INFO **
** INFO */

/* Include standard headers */
#include <stdio.h>
#include <stdlib.h>
{INCLUDE_CUTILS}
int main(void)
{{
    printf("\\n*** NEW ENVIRONMENT ***\\n\\n");
    return 0;
}}
"""

#------------------------------------------------------------------------------#
class NoAvailableDirectoryName(Exception): pass

#------------------------------------------------------------------------------#
if __name__ == '__main__':
    # Get name of folder and app
    try:
        script, folder, app, *options = argv
    except ValueError:
        # Get/set folder name
        try:
            folder = argv[1]
        except IndexError:
            folder = 'testenv'
        # Get/set app name
        try:
            app = argv[2]
        except IndexError:
            app = 'main'
        # Create empty options
        options = ()

    folder_name= folder
    for i in range(1, 1000):
        try:
            # Create folder if not exists
            makedirs(folder_name)
            print('Create environment in folder {!r}'.format(folder_name))
            break
        except OSError as e:
            if e.errno != EEXIST:
                # If other error appears than "dir already exists" reraise
                # the caught error again and print out the traceback
                raise OSError('\n'.join(extract_stack())) from None
            folder_name = '{}_{:0>3}'.format(folder, i)
    else:
        raise NoAvailableDirectoryName('Choose a different directory name')

    # Parse specified options
    if '-cutils' in options:
        use_cutils = 'cutils'
        include_cutils = '#include <cutils/call.h>\n'
    else:
        use_cutils = include_cutils = ''

    # Create makefile
    make = join(folder_name, 'makefile')
    with open(make, 'w', encoding='utf-8') as make_file:
        make_file.write(MAKE.format(APP_NAME=app,
                                    CUTILS_LIB=use_cutils))
    print('Place {!r}'.format(make))

    # Create c file
    source = join(folder_name, app if app.endswith('.c') else app + '.c')
    with open(source, 'w', encoding='utf-8') as source_file:
        source_file.write(C.format(INCLUDE_CUTILS=include_cutils))
    print('Place {!r}'.format(source))

    # End script
    print('Environment is ready')
