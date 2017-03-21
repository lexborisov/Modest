myunicode_dirs := .
myunicode_objs := $(call MODEST_UTILS_OBJS,myunicode,$(myunicode_dirs))

myunicode_description := unicode normalization, case work and other
myunicode_dependencies := mycore myport

myunicode_all: $(myunicode_objs)

myunicode_clean: 
	rm -f $(myunicode_objs)

myunicode_clone: 
	$(call MODEST_UTILS_HDRS_CLONE,myunicode,$(myunicode_dirs))
