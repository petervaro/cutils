#!/usr/bin/env python3
## INFO ########################################################################
##                                                                            ##
##                                   cutils                                   ##
##                                   ======                                   ##
##                                                                            ##
##                     Modern and Lightweight C Utilities                     ##
##                       Version: 0.8.90.762 (20140822)                       ##
##                                                                            ##
##                       File: pycutils/cutils/cenv.py                        ##
##                                                                            ##
##           Designed and written by Peter Varo. Copyright (c) 2014           ##
##             License agreement is provided in the LICENSE file              ##
##                 For more info visit: http://www.cutils.org                 ##
##                                                                            ##
######################################################################## INFO ##

# Import python modules
from sys import argv
from os import makedirs
from os.path import join
from errno import EEXIST
from traceback import extract_stack

#------------------------------------------------------------------------------#
# Module level constants
MAKE = """
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
CFLAGS+=-std=c11 $(foreach dir, $(app_INCLUDE_DIRS), -I$(dir))
LDFLAGS=$(foreach libdir, $(app_LIBRARY_DIRS), -L$(libdir))
LDFLAGS+=$(foreach library, $(app_LIBRARIES), -l$(library))

# Rules
.PHONY: all clean makedirs

ifdef USE_CUTILS
all: call_cutils makedirs $(app_NAME)

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
\trm -f $(app_BUILD_TMP_DIR)/*.o
\trm -f $(app_BUILD_OUT_DIR)/$(app_NAME)
"""

C = """
/* INFO *
 * INFO */

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
        script, folder, app, *options = argv
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

    # Parse specified options
    use_cutils = 'cutils' if '-cutils' in options else ''

    # Create makefile
    make = join(folder_name, 'makefile')
    with open(make, 'w', encoding='utf-8') as make_file:
        make_file.write(MAKE.format(APP_NAME=app, CUTILS_LIB=use_cutils))
    print('Place {!r}'.format(make))

    # Create c file
    source = join(folder_name, app if app.endswith('.c') else app + '.c')
    with open(source, 'w', encoding='utf-8') as source_file:
        source_file.write(C)
    print('Place {!r}'.format(source))

    # End script
    print('Environment is ready')
