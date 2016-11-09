find_files_h = $(wildcard $(SRCDIR)/modest/$(dir)/*.h)
find_files_c = $(wildcard $(SRCDIR)/modest/$(dir)/*.c)

SUBDIRS := . finder style node layer render
HDRS += $(foreach dir,$(SUBDIRS),$(find_files_h))
SRCS += $(foreach dir,$(SUBDIRS),$(find_files_c))

modest_clone: MODEST_DIR_$(SUBDIRS)
	mkdir -p $(INCLUDE_TMP)/modest
	cp $(SRCDIR)/modest/*.h $(INCLUDE_TMP)/modest

MODEST_DIR_$(SUBDIRS):
	mkdir -p $(INCLUDE_TMP)/modest/$(patsubst MODEST_DIR_%,%,$@)
	cp $(SRCDIR)/modest/$(patsubst MODEST_DIR_%,%,$@)/*.h $(INCLUDE_TMP)/modest/$(patsubst MODEST_DIR_%,%,$@)/
