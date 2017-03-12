TARGET := examples
SRCDIR := .

CC ?= gcc

# ARGS
#
# BINARY_OPTIMIZATION_LEVEL, default -O2
# MODEST_BUILD_WITHOUT_THREADS, YES or (NO or undefined), default undefined
#

.DEFAULT_GOAL := all

#********************
# other Makefile
#***************
BINARY_PATH_RELATIVE := ..
include $(BINARY_PATH_RELATIVE)/Makefile.bin.cfg

BINARY_TO_DIR := $(BINARY_PATH_RELATIVE)/$(BINARY_DIR_BASE)

#********************
# Build
#***************
BINARY_BUILD_MODULES ?= $(dir $(wildcard $(SRCDIR)/*/))
BINARY_BUILD_MODULES_LIST := $(strip $(foreach dir,$(BINARY_BUILD_MODULES),$(word 2, $(subst $(MODEST_DIR_SEPARATOR), , $(dir))) ))
BINARY_BUILD_MODULES_MAKEFILES_LIST := $(foreach dir,$(BINARY_BUILD_MODULES_LIST),$(dir)/Makefile.mk)

#********************
# Targets
#***************
BINARY_BUILD_MODULES_TARGET       := $(BINARY_BUILD_MODULES_LIST)
BINARY_BUILD_MODULES_TARGET_ALL   := $(foreach dir,$(BINARY_BUILD_MODULES_TARGET),$(dir)_all)
BINARY_BUILD_MODULES_TARGET_CLEAN := $(foreach dir,$(BINARY_BUILD_MODULES_TARGET),$(dir)_clean)

#********************
# Utils
#***************
define BYNARY_UTILS_NEW_LINE


endef
BINARY_UTILS_OBJS = $(patsubst %.c,%,$(foreach dir,$2,$(wildcard $(SRCDIR)/$1/$(dir)/*.c)))
BINARY_UTILS_CREATE_DIRS = $(foreach dir,$(BINARY_BUILD_MODULES_LIST),mkdir -p $(BINARY_TO_DIR)/$(dir) $(BYNARY_UTILS_NEW_LINE))

#********************
# Include all modules Makefile.mk
#***************
include $(BINARY_BUILD_MODULES_MAKEFILES_LIST)

#********************
# Set ARGS for flags
#***************
override CFLAGS  += $(BINARY_CFLAGS)
override LDFLAGS += $(BINARY_LDFLAGS)
override LDLIBS  += $(BINARY_LIBRARIES)

#********************
# Objects
#***************
BINARY_BUILD_EXECUTE ?= $(foreach dir,$(BINARY_BUILD_MODULES_TARGET),$($(dir)_objs))
BINARY_BUILD_EXECUTE_CLEAN := $(foreach path,$(BINARY_BUILD_EXECUTE),$(subst ./,,$(path)))
BINARY_BUILD_EXECUTE_TO_CLEAN := $(foreach path,$(BINARY_BUILD_EXECUTE_CLEAN),rm -f $(BINARY_TO_DIR)/$(path) $(BYNARY_UTILS_NEW_LINE))
BINARY_BUILD_DIRS_TO_CLEAN := $(foreach path,$(BINARY_BUILD_MODULES_LIST),rm -rf $(BINARY_TO_DIR)/$(path) $(BYNARY_UTILS_NEW_LINE))
BINARY_BUILD_EXECUTE_COPY := $(foreach path,$(BINARY_BUILD_EXECUTE_CLEAN),cp $(path) $(BINARY_TO_DIR)/$(dir $(path)) $(BYNARY_UTILS_NEW_LINE))
BINARY_BUILD_EXECUTE_COPY_ALL := $(BINARY_UTILS_CREATE_DIRS) $(BINARY_BUILD_EXECUTE_COPY) cp $(BINARY_PATH_RELATIVE)/$(call MODEST_LIBRARY_WITH_VERSION) $(BINARY_TO_DIR)

#********************
# Target options
#***************
all: build
	$(BINARY_BUILD_EXECUTE_COPY_ALL)

build: $(BINARY_BUILD_EXECUTE_CLEAN)

clean: $(BINARY_BUILD_MODULES_TARGET_CLEAN)
	$(BINARY_BUILD_EXECUTE_TO_CLEAN)
	$(BINARY_BUILD_DIRS_TO_CLEAN)
	rm -f $(BINARY_TO_DIR)/$(call MODEST_LIBRARY_NAME_WITH_VERSION)

copy:
	$(BINARY_BUILD_EXECUTE_COPY_ALL)

.PHONY: all copy clean $(BINARY_BUILD_MODULES_TARGET_ALL)
