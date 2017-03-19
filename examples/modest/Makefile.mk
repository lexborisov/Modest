modest_dirs := .
modest_objs := $(call BINARY_UTILS_OBJS,modest,$(modest_dirs))

modest_all: $(modest_objs)

modest_clean: 
	rm -f $(modest_objs)
