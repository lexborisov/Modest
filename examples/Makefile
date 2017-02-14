TARGET := examples
SRCDIR := examples

CC ?= gcc
LIBS := ../lib/libmodest_static.a
LDLIBS := $(LIBS)

INCLUDE_TMP := include

MODEST_OPTIMIZATION_LEVEL ?= -O2

CFLAGS ?= -Wall -Werror
CFLAGS += $(MODEST_OPTIMIZATION_LEVEL) -Wno-unused-variable -fPIC --std=c99 -I../include

MODEST_BUILD_WITHOUT_THREADS ?= NO
ifeq ($(MODEST_BUILD_WITHOUT_THREADS),YES)
    $(info Build Examples without POSIX Threads)
else
    $(info Build Examples with POSIX Threads)
	CFLAGS += -pthread
endif

ifeq ($(OS),Windows_NT)
else
	UNAM := $(shell uname -s)
	ifeq ($(UNAM),Darwin)
	else
		CFLAGS += -D_POSIX_C_SOURCE=199309L
	endif
endif

find_files_h = $(wildcard $(dir)/*.h)
find_files_c = $(wildcard $(dir)/*.c)

SUBDIRS := selectors declarations myfont modest mycss myhtml
HDRS += $(foreach dir,$(SUBDIRS),$(find_files_h))
SRCS += $(foreach dir,$(SUBDIRS),$(find_files_c))

OBJS := $(patsubst %.c,%,$(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	cp -r $(OBJS) ../bin/

clean:
	rm -f $(OBJS)

.PHONY: all