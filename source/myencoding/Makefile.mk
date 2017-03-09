myencoding_dirs := .
myencoding_objs := $(call MODEST_UTILS_OBJS,myencoding,$(myencoding_dirs))

myencoding_all: $(myencoding_objs)

myencoding_clean: 
	rm -f $(myencoding_objs)

myencoding_clone: 
	$(call MODEST_UTILS_HDRS_CLONE,myencoding,$(myencoding_dirs))
