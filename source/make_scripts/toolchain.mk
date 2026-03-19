

ifeq ($(RISC_V_GCC), Y)
    # $(error RISC_V_GCC=$(RISC_V_GCC))
    include $(WORKSPACE_LOC)/make_scripts/toolchain_arm_gcc.mk
endif

ifeq ($(GCC), Y)
    #$(error GCC=$(GCC))
    #include $(WORKSPACE_LOC)/make_scripts/toolchain_gcc.mk
endif

ifeq ($(GHS), Y)
    include $(WORKSPACE_LOC)/make_scripts/toolchain_ghs.mk
endif

ifeq ($(CLANG), Y)
    include $(WORKSPACE_LOC)/make_scripts/toolchain_clang.mk
endif

ifeq ($(TCC), Y)
    include $(WORKSPACE_LOC)/make_scripts/toolchain_tcc.mk
endif

ifeq ($(MINGW), Y)
    #$(error MINGW=$(MINGW))
    include $(WORKSPACE_LOC)/make_scripts/toolchain_mingw.mk
endif

ifeq ($(IAR), Y)
    #$(error IAR=$(IAR))
    include $(WORKSPACE_LOC)/make_scripts/toolchain_iar.mk
endif
    
ifeq ($(ARM_GCC), Y)
    # $(error ARM_GCC=$(ARM_GCC))
    include $(WORKSPACE_LOC)/make_scripts/toolchain_arm_gcc.mk
endif