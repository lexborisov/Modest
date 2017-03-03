find_files_h = $(wildcard $(SRCDIR)/myencoding/$(dir)/*.h)
find_files_c = $(wildcard $(SRCDIR)/myencoding/$(dir)/*.c)

SUBDIRS := .
HDRS += $(foreach dir,$(SUBDIRS),$(find_files_h))
SRCS += $(foreach dir,$(SUBDIRS),$(find_files_c))

myencoding_clone: MyENCODING_DIR_$(SUBDIRS)

MyENCODING_DIR_$(SUBDIRS):
	mkdir -p $(INCLUDE_TMP)/myencoding/$(patsubst MyENCODING_DIR_%,%,$@)
	cp $(SRCDIR)/myencoding/$(patsubst MyENCODING_DIR_%,%,$@)/*.h $(INCLUDE_TMP)/myencoding/$(patsubst MyENCODING_DIR_%,%,$@)/
