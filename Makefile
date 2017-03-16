TARGET := source
SRCDIR := source

CC ?= gcc

# ARGS
#
# MODEST_OPTIMIZATION_LEVEL, default -O2
# MyCORE_BUILD_WITHOUT_THREADS, YES or (NO or undefined), default undefined
# MyCORE_BUILD_DEBUG, default undefined
#

.DEFAULT_GOAL := all

DESCRIPTION := Modest is a fast HTML renderer implemented as a pure C99 library with no outside dependencies

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
MODEST_BUILD_MODULES_LIST_WITHOUT_PORT := $(strip $(foreach dir,$(MODEST_BUILD_MODULES_LIST),$(patsubst myport,,$(dir))))
MODEST_BUILD_MODULES_MAKEFILES_LIST := $(foreach dir,$(MODEST_BUILD_MODULES),$(dir)Makefile.mk)

#********************
# Targets
#***************
MODEST_BUILD_MODULES_TARGET       := $(MODEST_BUILD_MODULES_LIST)
MODEST_BUILD_MODULES_TARGET_ALL   := $(foreach dir,$(MODEST_BUILD_MODULES_TARGET),$(dir)_all)
MODEST_BUILD_MODULES_TARGET_CLEAN := $(foreach dir,$(MODEST_BUILD_MODULES_TARGET),$(dir)_clean) $(myport_clean)
MODEST_BUILD_MODULES_TARGET_CLONE := $(foreach dir,$(MODEST_BUILD_MODULES_TARGET),$(dir)_clone)

#********************
# Utils
#***************
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
MODEST_CFLAGS += -DMODEST_BUILD_OS=$(MODEST_BUILD_OS)
MODEST_CFLAGS += -DMODEST_PORT_NAME=$(MODEST_PORT_NAME)
MODEST_CFLAGS += $(call MODEST_UTILS_TO_UPCASE,-DMyCORE_OS_$(MODEST_BUILD_OS))

override CFLAGS += $(MODEST_CFLAGS)
override LDFLAGS += $(MODEST_LDFLAGS)

#********************
# Objects
#***************
MODEST_BUILD_OBJECT_SHARED  ?= $(CC) -shared $(LDFLAGS) $(MODEST_LDFLAGS) $1 -o $2
MODEST_BUILD_OBJECT_STATIC  ?= $(AR) crus $2 $1
MODEST_BUILD_OBJECT_MODULES := $(foreach dir,$(MODEST_BUILD_MODULES_TARGET),$($(dir)_objs))
MODEST_BUILD_OBJECT_MODULES := $(foreach dir,$(MODEST_BUILD_MODULES_TARGET),$($(dir)_objs))

#********************
# Sub Directories
#***************
BUILD_SUB_DIRS := examples $(TEST_DIR)

#********************
# Install
#***************
MODEST_INSTALL_LIBRARY := lib
MODEST_INSTALL_HEADER  := include

libdir     ?= $(prefix)/$(MODEST_INSTALL_LIBRARY)
includedir ?= $(prefix)/$(MODEST_INSTALL_HEADER)

MODEST_INSTALL_CREATE_DIR := mkdir -p $(prefix)/$(MODEST_INSTALL_HEADER) $(prefix)/$(MODEST_INSTALL_LIBRARY) 
MODEST_INSTALL_COMMAND := $(MODEST_INSTALL_CREATE_DIR) $(MODEST_UTILS_NEW_LINE) cp -av $(LIB_DIR_BASE)/* $(libdir) $(MODEST_UTILS_NEW_LINE) cp -r $(INCLUDE_DIR_API)/* $(includedir)

#********************
# Uninstall
#***************
MODEST_UNINSTALL_MK_COMMAND :=
MODEST_UNINSTALL_FILE    := uninstal.mk
MODEST_UNINSTALL_HEADERS := $(foreach name,$(MODEST_BUILD_MODULES_LIST_WITHOUT_PORT),rm -rf $(includedir)/$(name) \$$(MODEST_UTILS_NEW_LINE))
MODEST_UNINSTALL_LIBRARY := $(foreach path,$(wildcard $(LIB_DIR_BASE)/lib*),rm -rf $(libdir)/$(notdir $(path)) \$$(MODEST_UTILS_NEW_LINE))
MODEST_UNINSTALL_COMMAND = echo "MODEST_UNINSTALL_MK_COMMAND = $(MODEST_UNINSTALL_HEADERS) $(MODEST_UNINSTALL_LIBRARY)" > $(MODEST_UNINSTALL_FILE)

-include $(MODEST_UNINSTALL_FILE)

#********************
# PKG-CONFIG
#***************
MODEST_PKG_CONFIG_FILE := modest.pc
MODEST_PKG_CONFIG_CFLAGS := $(foreach name,$(MODEST_BUILD_MODULES_LIST_WITHOUT_PORT),-I$\{includedir}/$(name))
MODEST_PKG_CONFIG_PROCESS = \
$(SED) \
-e 's,@version\@,$(MODEST_VERSION_STRING),g' \
-e 's,@prefix\@,$(prefix),g' \
-e 's,@exec_prefix\@,$(exec_prefix),g' \
-e 's,@libdir\@,$(MODEST_INSTALL_LIBRARY),g' \
-e 's,@includedir\@,$(MODEST_INSTALL_HEADER),g' \
-e 's,@cflags\@,$(MODEST_PKG_CONFIG_CFLAGS),g' \
-e 's,@libname\@,$(LIB_NAME),g' \
-e 's,@description\@,$(DESCRIPTION),g' \
$1 > $2

#********************
# Target options
#***************
all: library
	for f in $(BUILD_SUB_DIRS); do $(MAKE) -C $$f all; done

library: shared static

shared: create $(MODEST_BUILD_MODULES_TARGET_ALL)
	$(call MODEST_BUILD_OBJECT_SHARED,$(MODEST_BUILD_OBJECT_MODULES),$(call MODEST_LIBRARY_WITH_VERSION))
	$(call MODEST_BUILD_SHARED_AFTER)

static: create $(MODEST_BUILD_MODULES_TARGET_ALL)
	$(call MODEST_BUILD_OBJECT_STATIC,$(MODEST_BUILD_OBJECT_MODULES),$(call MODEST_LIBRARY_STATIC))
	$(call MODEST_BUILD_STATIC_AFTER)

clean: $(MODEST_BUILD_MODULES_TARGET_CLEAN)
	rm -f $(call MODEST_LIBRARY_WITH_VERSION) && rm -f $(call MODEST_LIBRARY_STATIC)
	rm -rf $(TEST_DIR_BASE)
	$(call MODEST_BUILD_CLEAN_AFTER)
	for f in $(BUILD_SUB_DIRS); do $(MAKE) -C $$f clean; done

clone: clean_api $(MODEST_BUILD_MODULES_TARGET_CLONE)
	find $(INCLUDE_DIR_API) -name "*.h" -exec sed -i '.bak' -E 's/^[ \t]*#[ \t]*include[ \t]*"([^"]+)"/#include <\1>/g' {} \;
	find $(INCLUDE_DIR_API) -name "*.h.bak" -exec rm -f {} \;

clean_api:
	rm -rf $(INCLUDE_DIR_API)

create:
	mkdir -p $(BINARY_DIR_BASE) $(LIB_DIR_BASE) $(TEST_DIR_BASE)

install: 
	$(MODEST_INSTALL_COMMAND)
	$(MODEST_UNINSTALL_COMMAND)

uninstall: 
	$(MODEST_UNINSTALL_MK_COMMAND)

test: library
	$(MAKE) -C $(TEST_DIR) run

make-pc-file:
	$(call MODEST_PKG_CONFIG_PROCESS,$(MODEST_PKG_CONFIG_FILE).in, $(MODEST_PKG_CONFIG_FILE))

.PHONY: all clean clone test $(MODEST_BUILD_MODULES_TARGET_ALL)
