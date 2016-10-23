TARGET := source
SRCDIR := source

CC ?= gcc

LIBNAME := modest
LIBPOSTFIX := .so
LIBSTATIC_POSTFIX  := _static
LIB_TMP := lib
INCLUDE_TMP := include
BIN_TMP := bin

MODEST_OPTIMIZATION_LEVEL ?= -O2

CFLAGS ?= -Wall -Werror
CFLAGS += $(MODEST_OPTIMIZATION_LEVEL) -fPIC --std=c99 -I$(SRCDIR)

ifdef MODEST_BUILD_DEBUG
	CFLAGS += -g
endif

MODEST_BUILD_WITHOUT_THREADS ?= NO
ifeq ($(MODEST_BUILD_WITHOUT_THREADS),YES)
    $(info Build without POSIX Threads)
	CFLAGS += -DMODEST_BUILD_WITHOUT_THREADS
else
    $(info Build with POSIX Threads)
	CFLAGS += -pthread
endif

ifeq ($(OS),Windows_NT)
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
EXTDIRS := examples

all: create shared static
	for f in $(EXTDIRS); do $(MAKE) -C $$f all; done

include $(TARGET)/myhtml/Makefile.mk
include $(TARGET)/mycss/Makefile.mk
include $(TARGET)/myfont/Makefile.mk
include $(TARGET)/modest/Makefile.mk

OBJS := $(patsubst %.c,%.o,$(SRCS))

shared: $(OBJS)
	$(CC) -shared $(LDFLAGS) $(OBJS) -o $(LIB_TMP)/lib$(LIBNAME)$(LIBPOSTFIX)

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

clone: create clean_include myhtml_clone mycss_clone modest_clone
	find include -name "*.h" -exec sed -i '.bak' -E 's/^[ \t]*#[ \t]*include[ \t]*"([^"]+)"/#include <\1>/g' {} \;
	find include -name "*.h.bak" -exec rm -f {} \;

.PHONY: all clean clone