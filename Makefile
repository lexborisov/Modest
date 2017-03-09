TARGET := source
SRCDIR := source

CC ?= gcc

# ARGS
#
# MODEST_OPTIMIZATION_LEVEL, default -O2
# MODEST_BUILD_WITHOUT_THREADS, YES or (NO or undefined), default undefined
# MODEST_BUILD_DEBUG, default undefined
#

.DEFAULT_GOAL := all

#********************
# Flags
#***************
MODEST_CFLAGS ?= -Wall -Werror
MODEST_LFLAGS ?=

#********************
# Include
#***************
# include dirs
INCLUDE_DIR := $(TARGET)
INCLUDE_DIR_API := include

#********************
# Libraries
#***************
# lib name
LIB_NAME := modest
LIB_NAME_SUFFIX := .so
LIB_NAME_SUFFIX_STATIC := _static.a

# lib dirs
LIB_DIR_BASE := lib

#********************
# Binaries
#***************
# binaries dirs
BIN_DIR_BASE := bin

IMP_FLAG :=
BIN_TMP := bin

#********************
# other Makefile
#***************
include Makefile.cfg

#********************
# Build
#***************
MODEST_BUILD_MODULES ?= $(dir $(wildcard $(SRCDIR)/*/))
MODEST_BUILD_MODULES := $(patsubst %myport/,%myport/$(strip $(MODEST_PORT_NAME))/,$(MODEST_BUILD_MODULES))
MODEST_BUILD_MODULES_LIST := $(foreach dir,$(MODEST_BUILD_MODULES),$(word 2, $(subst $(MODEST_DIR_SEPARATOR), , $(dir))) )
MODEST_BUILD_MODULES_MAKEFILES_LIST := $(foreach dir,$(MODEST_BUILD_MODULES),$(dir)Makefile.mk)

#********************
# Targets
#***************
MODEST_BUILD_MODULES_TARGET       := $(MODEST_BUILD_MODULES_LIST)
MODEST_BUILD_MODULES_TARGET_ALL   := $(foreach dir,$(MODEST_BUILD_MODULES_TARGET),$(dir)_all)
MODEST_BUILD_MODULES_TARGET_CLEAN := $(foreach dir,$(MODEST_BUILD_MODULES_TARGET),$(dir)_clean)
MODEST_BUILD_MODULES_TARGET_CLONE := $(foreach dir,$(MODEST_BUILD_MODULES_TARGET),$(dir)_clone)

#********************
# Utils
#***************
define MODEST_UTILS_NEW_LINE


endef
MODEST_UTILS_HDRS = $(foreach dir,$2,$(wildcard $(SRCDIR)/$1/$(dir)/*.h))
MODEST_UTILS_OBJS = $(patsubst %.c,%.o,$(foreach dir,$2,$(wildcard $(SRCDIR)/$1/$(dir)/*.c)))
MODEST_UTILS_HDRS_CLONE_CMND = $(foreach path,$(foreach dir,$2,$(wildcard $(SRCDIR)/$1/$(dir)/*.h)), cp $(path) $(patsubst $(SRCDIR)%,$(INCLUDE_DIR_API)%,$(path)) $(MODEST_UTILS_NEW_LINE))
MODEST_UTILS_HDRS_CLONE_GDIR = $(foreach dir,$2,$(INCLUDE_DIR_API)/$1/$(dir)/)
MODEST_UTILS_HDRS_CLONE_DIRS = $(foreach dir,$(strip $(patsubst %./,%,$(foreach path,$(call MODEST_UTILS_HDRS_CLONE_GDIR,$1,$2),$(dir $(path))))),mkdir -p $(dir) $(MODEST_UTILS_NEW_LINE))
MODEST_UTILS_HDRS_CLONE = $(info Clone for $1) $(call MODEST_UTILS_HDRS_CLONE_DIRS,$1,$2) $(MODEST_UTILS_NEW_LINE) $(call MODEST_UTILS_HDRS_CLONE_CMND,$1,$2)

#********************
# Include all modules Makefile.mk
#***************
include $(MODEST_BUILD_MODULES_MAKEFILES_LIST)

#********************
# Set ARGS for flags
#***************
CFLAGS += $(MODEST_CFLAGS)

#********************
# Objects
#***************
MODEST_BUILD_OBJECT_SHARED  ?= $(CC) -shared $(IMP_FLAG) $(LDFLAGS) $1 -o $2
MODEST_BUILD_OBJECT_MODULES := $(foreach dir,$(MODEST_BUILD_MODULES_TARGET),$($(dir)_objs))

#********************
# Target options
#***************
all: $(MODEST_BUILD_MODULES_TARGET_ALL)
	$(call MODEST_BUILD_OBJECT_SHARED,$(MODEST_BUILD_OBJECT_MODULES),$(MODEST_LIBRARY))

clean: $(MODEST_BUILD_MODULES_TARGET_CLEAN)
clone: $(MODEST_BUILD_MODULES_TARGET_CLONE)

.PHONY: all clean clone $(MODEST_BUILD_MODULES_TARGET_ALL)

# SRCS := 
# HDRS := 
# EXTDIRS := examples test

# all: create shared static
# 	for f in $(EXTDIRS); do $(MAKE) -C $$f all; done

# include $(TARGET)/mycore/Makefile.mk
# include $(TARGET)/myencoding/Makefile.mk
# include $(TARGET)/myhtml/Makefile.mk
# include $(TARGET)/mycss/Makefile.mk
# include $(TARGET)/myfont/Makefile.mk
# include $(TARGET)/myurl/Makefile.mk
# include $(TARGET)/modest/Makefile.mk

# OBJS := $(patsubst %.c,%.o,$(SRCS))

# shared: $(OBJS)
# 	$(CC) -shared $(IMP_FLAG) $(LDFLAGS) $(OBJS) -o $(LIB_TMP)/lib$(LIBNAME)$(LIBPOSTFIX)

# static: shared
# 	$(AR) crus $(LIB_TMP)/lib$(LIBNAME)$(LIBSTATIC_POSTFIX).a $(OBJS) 

# create:
# 	mkdir -p lib bin

# clean:
# 	for f in $(EXTDIRS); do $(MAKE) -C $$f clean; done
# 	rm -f $(OBJS)
# 	rm -f $(LIB_TMP)/*
# 	rm -f $(BIN_TMP)/*

# clean_include:
# 	rm -rf $(INCLUDE_TMP)

# clone: create clean_include myhtml_clone mycss_clone modest_clone myfont_clone myurl_clone mycore_clone myencoding_clone
# 	find include -name "*.h" -exec sed -i '.bak' -E 's/^[ \t]*#[ \t]*include[ \t]*"([^"]+)"/#include <\1>/g' {} \;
# 	find include -name "*.h.bak" -exec rm -f {} \;

# test:
# 	test/mycss/declaration test/mycss/data/declaration
# 	test/myhtml/utils/avl_tree
# 	test/myhtml/encoding_detect_meta test/myhtml/data/encoding/detect_meta.html
# 	test/myurl/url test/myurl/data

# .PHONY: all clean clone test
