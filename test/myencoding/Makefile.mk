myencoding_dirs := .
myencoding_objs := $(call BINARY_UTILS_OBJS,myencoding,$(myencoding_dirs))

myencoding_all: $(myencoding_objs)

myencoding_clean: 
	rm -f $(myencoding_objs)

myencoding_encoding_detect_meta := $(TEST_DIR_RELATIVE)/myencoding/data/encoding/detect_meta.html
