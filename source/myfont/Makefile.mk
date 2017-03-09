myfont_dirs := .
myfont_objs := $(call MODEST_UTILS_OBJS,myfont,$(myfont_dirs))

myfont_all: $(myfont_objs)

myfont_clean: 
	rm -f $(myfont_objs)

myfont_clone: 
	$(call MODEST_UTILS_HDRS_CLONE,myfont,$(myfont_dirs))
