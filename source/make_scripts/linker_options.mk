

ifeq ($(GCC), Y)
    include $(WORKSPACE_LOC)/make_scripts/linker_gcc_options.mk
endif


ifeq ($(IAR), Y)
    include $(WORKSPACE_LOC)/make_scripts/linker_iar_options.mk
endif

