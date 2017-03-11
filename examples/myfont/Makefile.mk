myfont_dirs := .
myfont_objs := $(call BINARY_UTILS_OBJS,myfont,$(myfont_dirs))

myfont_all: $(myfont_objs)

myfont_clean: 
	rm -f $(myfont_objs)
