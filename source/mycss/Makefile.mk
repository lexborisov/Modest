mycss_dirs := . selectors namespace media values property declaration
mycss_objs := $(call MODEST_UTILS_OBJS,mycss,$(mycss_dirs))

mycss_description := CSS parser and modules by https://drafts.csswg.org/
mycss_dependencies := mycore myencoding myport

mycss_all: $(mycss_objs)

mycss_clean: 
	rm -f $(mycss_objs)

mycss_clone: 
	$(call MODEST_UTILS_HDRS_CLONE,mycss,$(mycss_dirs))
