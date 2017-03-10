myport_selected_port := myport/$(strip $(MODEST_PORT_NAME))

myport_dirs := mycore/. mycore/utils
myport_objs := $(call MODEST_UTILS_OBJS,$(myport_selected_port),$(myport_dirs))

myport_all: $(myport_objs)

myport_clean: 
	rm -f $(myport_objs)

myport_clone:
