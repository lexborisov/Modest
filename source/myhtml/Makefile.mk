find_files_h = $(wildcard $(SRCDIR)/myhtml/$(dir)/*.h)
find_files_c = $(wildcard $(SRCDIR)/myhtml/$(dir)/*.c)

SUBDIRS := .
HDRS += $(foreach dir,$(SUBDIRS),$(find_files_h))
SRCS += $(foreach dir,$(SUBDIRS),$(find_files_c))

myhtml_clone: MyHTML_DIR_$(SUBDIRS)

MyHTML_DIR_$(SUBDIRS):
	mkdir -p $(INCLUDE_TMP)/myhtml/$(patsubst MyHTML_DIR_%,%,$@)
	cp $(SRCDIR)/myhtml/$(patsubst MyHTML_DIR_%,%,$@)/*.h $(INCLUDE_TMP)/myhtml/$(patsubst MyHTML_DIR_%,%,$@)/
