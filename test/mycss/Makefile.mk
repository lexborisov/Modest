mycss_dirs := .
mycss_objs := $(call BINARY_UTILS_OBJS,mycss,$(mycss_dirs))

mycss_all: $(mycss_objs)

mycss_clean: 
	rm -f $(mycss_objs)

mycss_declaration := $(TEST_DIR_RELATIVE)/mycss/data/declaration
