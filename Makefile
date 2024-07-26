include makefile_mini.mk

$(call mm_add_start_parameters_t,a)
$(call mm_start,a)

$(call mm_add_library_parameters_t,b)
b.h:=clock_mini.h
$(call mm_add_library,clock-mini,b)

$(call mm_stop_parameters_t,b)
$(call mm_stop,b)
