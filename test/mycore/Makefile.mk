mycore_dirs := utils
mycore_objs := $(call BINARY_UTILS_OBJS,mycore,$(mycore_dirs))

mycore_all: $(mycore_objs)

mycore_clean: 
	rm -f $(mycore_objs)
