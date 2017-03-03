TARGET := source
SRCDIR := source
TSTDIR := test

CC ?= gcc

LIBNAME := modest
LIBPOSTFIX := .so
LIBSTATIC_POSTFIX  := _static
IMP_FLAG :=
LIB_TMP := lib
INCLUDE_TMP := include
BIN_TMP := bin

MODEST_OPTIMIZATION_LEVEL ?= -O2

CFLAGS ?= -Wall -Werror
CFLAGS += $(MODEST_OPTIMIZATION_LEVEL) -Wno-unused-variable --std=c99 -I$(SRCDIR)

ifneq ($(OS),Windows_NT)
    CFLAGS += -fPIC
endif

ifdef MODEST_BUILD_DEBUG
	CFLAGS += -g
endif

MODEST_BUILD_WITHOUT_THREADS ?= NO
ifeq ($(MODEST_BUILD_WITHOUT_THREADS),YES)
    $(info Build without POSIX Threads)
	CFLAGS += -DMODEST_BUILD_WITHOUT_THREADS -DMyHTML_BUILD_WITHOUT_THREADS
else
    $(info Build with POSIX Threads)
	CFLAGS += -pthread
endif

ifeq ($(OS),Windows_NT)
    LIBPOSTFIX := .dll
    IMP_FLAG := -Wl,--out-implib,$(LIB_TMP)/lib$(LIBNAME).dll.a
else
	UNAM := $(shell uname -s)
	ifeq ($(UNAM),Darwin)
		LIBPOSTFIX := .dylib
	else
		CFLAGS += -D_POSIX_C_SOURCE=199309L
	endif
endif

SRCS := 
HDRS := 
EXTDIRS := examples test

all: create shared static
	for f in $(EXTDIRS); do $(MAKE) -C $$f all; done

include $(TARGET)/mycore/Makefile.mk
include $(TARGET)/myencoding/Makefile.mk
include $(TARGET)/myhtml/Makefile.mk
include $(TARGET)/mycss/Makefile.mk
include $(TARGET)/myfont/Makefile.mk
include $(TARGET)/myurl/Makefile.mk
include $(TARGET)/modest/Makefile.mk

OBJS := $(patsubst %.c,%.o,$(SRCS))

shared: $(OBJS)
	$(CC) -shared $(IMP_FLAG) $(LDFLAGS) $(OBJS) -o $(LIB_TMP)/lib$(LIBNAME)$(LIBPOSTFIX)

static: shared
	$(AR) crus $(LIB_TMP)/lib$(LIBNAME)$(LIBSTATIC_POSTFIX).a $(OBJS) 

create:
	mkdir -p lib bin

clean:
	for f in $(EXTDIRS); do $(MAKE) -C $$f clean; done
	rm -f $(OBJS)
	rm -f $(LIB_TMP)/*
	rm -f $(BIN_TMP)/*

clean_include:
	rm -rf $(INCLUDE_TMP)

clone: create clean_include myhtml_clone mycss_clone modest_clone myfont_clone myurl_clone mycore_clone myencoding_clone
	find include -name "*.h" -exec sed -i '.bak' -E 's/^[ \t]*#[ \t]*include[ \t]*"([^"]+)"/#include <\1>/g' {} \;
	find include -name "*.h.bak" -exec rm -f {} \;

test:
	test/mycss/declaration test/mycss/data/declaration
	test/myhtml/utils/avl_tree
	test/myhtml/encoding_detect_meta test/myhtml/data/encoding/detect_meta.html
	test/myurl/url test/myurl/data

.PHONY: all clean clone test
