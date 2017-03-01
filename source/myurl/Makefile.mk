find_files_h = $(wildcard $(SRCDIR)/myurl/$(dir)/*.h)
find_files_c = $(wildcard $(SRCDIR)/myurl/$(dir)/*.c)

SUBDIRS := .
HDRS += $(foreach dir,$(SUBDIRS),$(find_files_h))
SRCS += $(foreach dir,$(SUBDIRS),$(find_files_c))

myurl_clone: MyURL_DIR_$(SUBDIRS)
	mkdir -p $(INCLUDE_TMP)/myurl
	cp $(SRCDIR)/myurl/*.h $(INCLUDE_TMP)/myurl

MyURL_DIR_$(SUBDIRS):
	mkdir -p $(INCLUDE_TMP)/myurl/$(patsubst MyURL_DIR_%,%,$@)
	cp $(SRCDIR)/myurl/$(patsubst MyURL_DIR_%,%,$@)/*.h $(INCLUDE_TMP)/myurl/$(patsubst MyURL_DIR_%,%,$@)/
