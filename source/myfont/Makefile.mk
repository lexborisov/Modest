myfont_dirs := .
myfont_objs := $(call MODEST_UTILS_OBJS,myfont,$(myfont_dirs))

myfont_description := work with font, metrics, calculating size and more by https://www.microsoft.com/en-us/Typography/SpecificationsOverview.aspx
myfont_dependencies := mycore myport

myfont_all: $(myfont_objs)

myfont_clean: 
	rm -f $(myfont_objs)

myfont_clone: 
	$(call MODEST_UTILS_HDRS_CLONE,myfont,$(myfont_dirs))
