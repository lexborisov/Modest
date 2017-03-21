myurl_dirs := .
myurl_objs := $(call BINARY_UTILS_OBJS,myurl,$(myurl_dirs))

myurl_all: $(myurl_objs)

myurl_clean: 
	rm -f $(myurl_objs)

myurl_url := $(TEST_DIR_RELATIVE)/myurl/data
