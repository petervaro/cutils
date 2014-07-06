## INFO ########################################################################
##                                                                            ##
##                                   cutils                                   ##
##                                   ======                                   ##
##                                                                            ##
##                     Modern and Lightweight C Utilities                     ##
##                       Version: 0.8.72.075 (20140706)                       ##
##                                                                            ##
##                               File: makefile                               ##
##                                                                            ##
##           Designed and written by Peter Varo. Copyright (c) 2014           ##
##             License agreement is provided in the LICENSE file              ##
##                 For more info visit: http://www.cutils.org                 ##
##                                                                            ##
######################################################################## INFO ##

# Toggle switch
IS_PRODUCTION=
CEXC_PREFS=USE LOG

# Filename of binary
app_NAME=main

app_NAME_DAR=libcdar

# Output dirs
app_BUILD_OUT_DIR=cdar/build
app_BUILD_LIB_DIR=$(app_BUILD_OUT_DIR)/lib
app_BUILD_SRC_DIR=$(app_BUILD_OUT_DIR)/src
app_BUILD_TMP_DIR=$(app_BUILD_OUT_DIR)/tmp

# DynamicArray sources
app_C_SOURCES_DAR=$(wildcard $(app_BUILD_SRC_DIR)/*.c)
app_C_OBJECTS_DAR=$(addprefix $(app_BUILD_TMP_DIR)/, $(notdir $(app_C_SOURCES_DAR:.c=.o)))

app_INCLUDES=/usr/local/include
app_LIBRARY_DIRS=/usr/local/lib
app_LIBRARIES=jemalloc
app_FRAMEWORKS=

# Flags
ifdef IS_PRODUCTION
CFLAGS+=-O3
else
CFLAGS+=-Wall -v -g
CFLAGS+=$(foreach act, $(CEXC_PREFS), -DCEXC_$(act))
endif
CFLAGS+=-std=c11 $(foreach dir, $(app_INCLUDES), -I$(dir))
LDFLAGS=$(foreach libdir, $(app_LIBRARY_DIRS), -L$(libdir))
LDFLAGS+=$(foreach library, $(app_LIBRARIES), -l$(library))

app_PYTHON=/usr/local/bin/python3

# Rules
.PHONY: all clean

all: makedirs $(app_NAME_DAR)

# $(app_NAME): $(app_C_OBJECTS)
# 	$(LINK.c) $(app_C_OBJECTS) -o $(app_BUILD_OUT_DIR)/$(app_NAME)

$(app_NAME_DAR): $(app_C_OBJECTS_DAR)
	$(LINK.c) $(app_C_OBJECTS_DAR) -shared -o $(app_BUILD_LIB_DIR)/$(app_NAME_DAR).so

$(app_BUILD_TMP_DIR)/%.o: $(app_BUILD_SRC_DIR)/%.c
	$(CC) $(CFLAGS) -fPIC -c -o $@ $<

makedirs:
	mkdir -p $(app_BUILD_TMP_DIR)

clean:
	rm -f $(app_BUILD_SRC_DIR)/*.c
	rm -f $(app_BUILD_TMP_DIR)/*.o
	rm -f $(app_BUILD_OUT_DIR)/$(app_NAME_DAR)
