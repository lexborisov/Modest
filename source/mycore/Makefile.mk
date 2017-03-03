find_files_h = $(wildcard $(SRCDIR)/mycore/$(dir)/*.h)
find_files_c = $(wildcard $(SRCDIR)/mycore/$(dir)/*.c)

SUBDIRS := . utils
HDRS += $(foreach dir,$(SUBDIRS),$(find_files_h))
SRCS += $(foreach dir,$(SUBDIRS),$(find_files_c))

mycore_clone: MyCORE_DIR_$(SUBDIRS)
	mkdir -p $(INCLUDE_TMP)/mycore/utils
	cp $(SRCDIR)/mycore/utils/*.h $(INCLUDE_TMP)/mycore/utils

MyCORE_DIR_$(SUBDIRS):
	mkdir -p $(INCLUDE_TMP)/mycore/$(patsubst MyCORE_DIR_%,%,$@)
	cp $(SRCDIR)/mycore/$(patsubst MyCORE_DIR_%,%,$@)/*.h $(INCLUDE_TMP)/mycore/$(patsubst MyCORE_DIR_%,%,$@)/
