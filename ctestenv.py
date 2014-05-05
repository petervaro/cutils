################################################################################
##                                                                            ##
##   testenv.py                                                               ##
##   ==========                                                               ##
##                                                                            ##
##   Generate a simple C test environment, with a basic but expandable        ##
##   'makefile' and a minimal C file, ready to test ideas.                    ##
##                                                                            ##
##   Requirements: Python 3.2+                                                ##
##   Version: 1.0.0                                                           ##
##   Usage:                                                                   ##
##                                                                            ##
##       $ python3 ctestenv.py <dirname> <filename>                           ##
##       $ cd <dirname>                                                       ##
##       $ make                                                               ##
##       $ ./build/<filename>                                                 ##
##                                                                            ##
##   Copyright (C) 2014 Peter Varo                                            ##
##                                                                            ##
##   Permission is hereby granted, free of charge, to any person obtaining    ##
##   a copy of this software and associated documentation files (the          ##
##   "Software"), to deal in the Software without restriction, including      ##
##   without limitation the rights to use, copy, modify, merge, publish,      ##
##   distribute, sublicense, and/or sell copies of the Software, and to       ##
##   permit persons to whom the Software is furnished to do so, subject to    ##
##   the following conditions:                                                ##
##                                                                            ##
##   The above copyright notice and this permission notice shall be           ##
##   included in all copies or substantial portions of the Software.          ##
##                                                                            ##
##   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,          ##
##   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF       ##
##   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.   ##
##   IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY     ##
##   CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,     ##
##   TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE        ##
##   SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                   ##
##                                                                            ##
################################################################################

# Import python modules
from sys import argv
from os import makedirs
from os.path import join
from errno import EEXIST
from traceback import extract_stack

#------------------------------------------------------------------------------#
# Module level constants
MAKE = """
# Filename of binary
app_NAME={}

# Output dirs
app_BUILD_OUT_DIR=build
app_BUILD_TMP_DIR=$(app_BUILD_OUT_DIR)/tmp

# Sources
app_C_SOURCES=$(app_NAME).c
app_C_OBJECTS=$(addprefix $(app_BUILD_TMP_DIR)/, $(notdir $(app_C_SOURCES:.c=.o)))
app_INCLUDES=/usr/local/include

# Flags
CFLAGS+=-Wall -v -g -std=c11 $(foreach dir, $(app_INCLUDES), -I$(dir))

# Rules
.PHONY: all clean

all: makedirs $(app_NAME)

$(app_NAME): $(app_C_OBJECTS)
\t$(LINK.c) $(app_C_OBJECTS) -o $(app_BUILD_OUT_DIR)/$(app_NAME)

$(app_BUILD_TMP_DIR)/%.o: %.c
\t$(CC) $(CFLAGS) -c -o $@ $<

makedirs:
\tmkdir -p $(app_BUILD_TMP_DIR)

clean:
\trm -f $(app_NAME).o
"""

C = """
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    printf("*** TEST ENVIRONMENT ***\\n");
    printf("...\\n");
    return 0;
}
"""

#------------------------------------------------------------------------------#
class NoAvailableDirectoryName(Exception): pass

#------------------------------------------------------------------------------#
if __name__ == '__main__':
    # Get name of folder and app
    try:
        script, folder, app, *rest = argv
    except ValueError:
        folder = 'testenv'
        app    = 'main'

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

    # Create makefile
    make = join(folder_name, 'makefile')
    with open(make, 'w', encoding='utf-8') as make_file:
        make_file.write(MAKE.format(app))
    print('Place {!r}'.format(make))

    # Create c file
    source = join(folder_name, app if app.endswith('.c') else app + '.c')
    with open(source, 'w', encoding='utf-8') as source_file:
        source_file.write(C)
    print('Place {!r}'.format(source))

    # End script
    print('Environment is ready')
