find_files_h = $(wildcard $(SRCDIR)/mycss/$(dir)/*.h)
find_files_c = $(wildcard $(SRCDIR)/mycss/$(dir)/*.c)

SUBDIRS := . selectors namespace media values property declaration
HDRS += $(foreach dir,$(SUBDIRS),$(find_files_h))
SRCS += $(foreach dir,$(SUBDIRS),$(find_files_c))

mycss_clone: MyCSS_DIR_$(SUBDIRS)
	mkdir -p $(INCLUDE_TMP)/mycss
	cp $(SRCDIR)/mycss/*.h $(INCLUDE_TMP)/mycss

MyCSS_DIR_$(SUBDIRS):
	mkdir -p $(INCLUDE_TMP)/mycss/$(patsubst MyCSS_DIR_%,%,$@)
	cp $(SRCDIR)/mycss/$(patsubst MyCSS_DIR_%,%,$@)/*.h $(INCLUDE_TMP)/mycss/$(patsubst MyCSS_DIR_%,%,$@)/
