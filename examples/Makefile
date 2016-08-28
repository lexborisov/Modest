TARGET := examples
SRCDIR := examples

CC ?= gcc
LIBS := ../lib/libmodest_static.a
LDLIBS := $(LIBS)

INCLUDE_TMP := include

MODEST_OPTIMIZATION_LEVEL ?= -O2

CFLAGS ?= -Wall -Werror
CFLAGS += $(MODEST_OPTIMIZATION_LEVEL) -fPIC --std=c99 -I../include

find_files_h = $(wildcard $(dir)/*.h)
find_files_c = $(wildcard $(dir)/*.c)

SUBDIRS := selectors
HDRS += $(foreach dir,$(SUBDIRS),$(find_files_h))
SRCS += $(foreach dir,$(SUBDIRS),$(find_files_c))

OBJS := $(patsubst %.c,%,$(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	cp -r $(OBJS) ../bin/

clean:
	rm -f $(OBJS)

.PHONY: all