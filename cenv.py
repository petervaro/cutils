## INFO ########################################################################
##                                                                            ##
##                                   cutils                                   ##
##                                   ======                                   ##
##                                                                            ##
##                     Modern and Lightweight C Utilities                     ##
##                       Version: 0.8.72.004 (20140703)                       ##
##                                                                            ##
##                               File: cenv.py                                ##
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
# TODO: Add cdep, ccom, cver and clic support to makefile
MAKE = """
## INFO ##
## INFO ##

# Toggle switch
IS_PRODUCTION=

# Filename of binary
app_NAME={}

# Output dirs
app_BUILD_OUT_DIR=build
app_BUILD_TMP_DIR=$(app_BUILD_OUT_DIR)/tmp

# Sources
app_C_SOURCES=$(wildcard *.c)
app_C_OBJECTS=$(addprefix $(app_BUILD_TMP_DIR)/, $(notdir $(app_C_SOURCES:.c=.o)))
app_INCLUDES=/usr/local/include
app_LIBRARY_DIRS=/usr/local/lib
app_LIBRARIES=
app_FRAMEWORKS=

# Flags
ifdef IS_PRODUCTION
CFLAGS+=-O3
else
CFLAGS+=-Wall -v -g
endif
CFLAGS+=-std=c11 $(foreach dir, $(app_INCLUDES), -I$(dir))
LDFLAGS=$(foreach libdir, $(app_LIBRARY_DIRS), -L$(libdir))
LDFLAGS+=$(foreach library, $(app_LIBRARIES), -l$(library))

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
\trm -f $(app_BUILD_TMP_DIR)/*.o
\trm -f $(app_BUILD_OUT_DIR)/$(app_NAME)
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
