modest_dirs := . finder style node layer render utils
modest_objs := $(call MODEST_UTILS_OBJS,modest,$(modest_dirs))

modest_all: $(modest_objs)

modest_clean:
	rm -f $(modest_objs)

modest_clone:
	$(call MODEST_UTILS_HDRS_CLONE,modest,$(modest_dirs))
