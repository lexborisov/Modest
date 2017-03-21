myurl_dirs := .
myurl_objs := $(call MODEST_UTILS_OBJS,myurl,$(myurl_dirs))

myurl_description := URL parser by https://url.spec.whatwg.org/
myurl_dependencies := mycore myport

myurl_all: $(myurl_objs)

myurl_clean: 
	rm -f $(myurl_objs)

myurl_clone: 
	$(call MODEST_UTILS_HDRS_CLONE,myurl,$(myurl_dirs))
