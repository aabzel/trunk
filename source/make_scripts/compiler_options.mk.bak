

ifeq ($(GCC),Y)
    #$(error GCC=$(GCC))
    include $(WORKSPACE_LOC)/make_scripts/compiler_gcc_options.mk
endif


ifeq ($(IAR),Y)
    include $(WORKSPACE_LOC)/make_scripts/compiler_iar_options.mk
endif


CFLAGS += $(INCDIR)