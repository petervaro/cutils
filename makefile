## INFO ########################################################################
##                                                                            ##
##                                   cutils                                   ##
##                                   ======                                   ##
##                                                                            ##
##                     Modern and Lightweight C Utilities                     ##
##                       Version: 0.8.96.177 (20140907)                       ##
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
USE_JEMALLOC=true
EXCEPTION_LOG=true
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

cutils_DEVELOPER_CHECK=

# Filename of library
cutils_NAME=libcutils

# Output dirs
cutils_BUILD_OUT_DIR=build
cutils_BUILD_TMP_DIR=$(cutils_BUILD_OUT_DIR)/tmp

# Resources in current library
cutils_C_SOURCES=$(wildcard *.c) internal/xxhash.c
cutils_C_OBJECTS=$(addprefix $(cutils_BUILD_TMP_DIR)/, $(notdir $(cutils_C_SOURCES:.c=.o)))

cutils_H_SOURCES=$(wildcard *.h)
cutils_INTERNALS=$(addprefix internal/, defs.h fcmp.h fmtc.h xxhash.h)

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
CFLAGS+=$(addprefix -D, CDAR_JEM CSLL_JEM)
endif

# Flags
ifdef IS_OPTIMISED
CFLAGS+=-O3 $(addprefix -D, CDAR_OPT CSLL_OPT)
else
CFLAGS+=-Wall -v -g
endif

ifdef cutils_DEVELOPER_CHECK
CFLAGS+=-Wextra
endif

# If compiler is clang
ifeq ($(CC), clang)
CFLAGS+=-fmacro-backtrace-limit=0
endif

ifdef EXCEPTION_LOG
CFLAGS+=-D CEXC_LOG
endif

CFLAGS+=-std=c11 $(addprefix -I, $(cutils_INCLUDE_DIRS))
CFLAGS+=$(foreach framework, $(cutils_FRAMEWORKS), -framework $(framework))
LDFLAGS=$(addprefix -L, $(cutils_LIBRARY_DIRS))
LDFLAGS+=$(addprefix -l, $(cutils_LIBRARIES))

# Rules
.PHONY: all clean install
.PHONY: make_build_dirs make_install_dirs
.PHONY: build_generic build_static

all: make_build_dirs build_generic build_static

# Build rule for sources in the root-dir
$(cutils_BUILD_TMP_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Build rule for sources in the internal-dir
$(cutils_BUILD_TMP_DIR)/%.o: internal/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

build_generic:
	# HACK:
	cp -f internal/static_hash_map.h cshm.h
	cp -f internal/static_hash_map.c cshm.c
	$(PYTHON) dev/proj.py

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
