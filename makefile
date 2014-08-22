## INFO ########################################################################
##                                                                            ##
##                                   cutils                                   ##
##                                   ======                                   ##
##                                                                            ##
##                     Modern and Lightweight C Utilities                     ##
##                       Version: 0.8.90.762 (20140822)                       ##
##                                                                            ##
##                               File: makefile                               ##
##                                                                            ##
##           Designed and written by Peter Varo. Copyright (c) 2014           ##
##             License agreement is provided in the LICENSE file              ##
##                 For more info visit: http://www.cutils.org                 ##
##                                                                            ##
######################################################################## INFO ##

#------------------------------------------------------------------------------#
# User flags
IS_OPTIMISED=
USE_JEMALLOC=
EXCEPTION_LOG=
DYNAMIC_LIB=

# Location 'prefix'
LOCATION=/usr/local

# Locations
INCLUDE_FOLDER=$(LOCATION)/include
LIBRARY_FOLDER=$(LOCATION)/lib
BINARY_FOLDER=$(LOCATION)/bin
PYTHON=$(LOCATION)/bin/python3

# Compiler
CC=clang
#------------------------------------------------------------------------------#

# Filename of library
cutils_NAME=libcutils

# Output dirs
cutils_BUILD_OUT_DIR=build
cutils_BUILD_TMP_DIR=$(cutils_BUILD_OUT_DIR)/tmp

# Resources in current library
cutils_C_SOURCES=$(wildcard *.c)
cutils_C_OBJECTS=$(addprefix $(cutils_BUILD_TMP_DIR)/, $(notdir $(cutils_C_SOURCES:.c=.o)))

cutils_H_SOURCES=$(wildcard *.h)
cutils_INTERNALS=$(addprefix internal/, defs.h fcmp.h fmtc.h)

# Includes, libs and frameworks
cutils_INCLUDE_DIRS=/usr/local/include .
cutils_LIBRARY_DIRS=/usr/local/lib
cutils_LIBRARIES=
cutils_FRAMEWORKS=

# Operating system
UNAME=$(shell uname)

# If use the jemalloc library
ifdef USE_JEMALLOC
cutils_LIBRARIES+=jemalloc
CFLAGS+=-D CDAR_JEM -D CSLL_JEM
endif

# Flags
ifdef IS_OPTIMISED
CFLAGS+=-O3 -DCDAR_OPT -D CSLL_OPT
else
CFLAGS+=-Wall -v -g
endif

# If compiler is gcc
ifeq ($(CC), clang)
CFLAGS+=-fmacro-backtrace-limit=0
endif

ifdef EXCEPTION_LOG
CFLAGS+=-D CEXC_LOG
endif

CFLAGS+=-std=c11 $(foreach dir, $(cutils_INCLUDE_DIRS), -I$(dir))
LDFLAGS=$(foreach libdir, $(cutils_LIBRARY_DIRS), -L$(libdir))
LDFLAGS+=$(foreach library, $(cutils_LIBRARIES), -l$(library))

# Rules
.PHONY: all clean install make_build_dirs make_install_dirs build_static

all: make_build_dirs build_static

$(cutils_BUILD_TMP_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

build_static: $(cutils_C_OBJECTS)
	ar -c -r -s -v $(cutils_BUILD_OUT_DIR)/$(cutils_NAME).a $(cutils_C_OBJECTS)

# $(cutils_BUILD_TMP_DIR)/%.o: %.c
# 	$(CC) $(CFLAGS) -fPIC -c -o $@ $<

# build_shared: $(cutils_NAME)
# 	$(CC) -shared -Wl -soname -o $(cutils_BUILD_OUT_DIR)/$(cutils_NAME).so

install: all make_install_dirs
	$(PYTHON) setup.py install $(INCLUDE_FOLDER) $(LIBRARY_FOLDER) $(BINARY_FOLDER)
	cp -Rf $(cutils_BUILD_OUT_DIR)/$(cutils_NAME).a $(LIBRARY_FOLDER)/$(cutils_NAME).a
	cp -Rf $(cutils_H_SOURCES) $(INCLUDE_FOLDER)/cutils
	cp -Rf $(cutils_INTERNALS) $(INCLUDE_FOLDER)/cutils/internal

# Create build dir and tmp dir inside it
make_build_dirs:
	mkdir -p $(cutils_BUILD_TMP_DIR)

make_install_dirs:
	mkdir -p $(INCLUDE_FOLDER)/cutils/internal

# Remove build dir and all dirs and files inside
clean:
	rm -f -r $(cutils_BUILD_OUT_DIR)
