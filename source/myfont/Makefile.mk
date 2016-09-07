find_files_h = $(wildcard $(SRCDIR)/myfont/$(dir)/*.h)
find_files_c = $(wildcard $(SRCDIR)/myfont/$(dir)/*.c)

SUBDIRS := .
HDRS += $(foreach dir,$(SUBDIRS),$(find_files_h))
SRCS += $(foreach dir,$(SUBDIRS),$(find_files_c))

modest_clone: MyFONT_DIR_$(SUBDIRS)
	mkdir -p $(INCLUDE_TMP)/myfont
	cp $(SRCDIR)/myfont/*.h $(INCLUDE_TMP)/myfont

MyFONT_DIR_$(SUBDIRS):
	mkdir -p $(INCLUDE_TMP)/myfont/$(patsubst MyFONT_DIR_%,%,$@)
	cp $(SRCDIR)/myfont/$(patsubst MyFONT_DIR_%,%,$@)/*.h $(INCLUDE_TMP)/myfont/$(patsubst MyFONT_DIR_%,%,$@)/
