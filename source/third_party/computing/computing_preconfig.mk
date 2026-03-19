ifneq ($(TP_COMPUTING_PRECONFIG_MK_INC),Y)
    TP_COMPUTING_PRECONFIG_MK_INC=Y

    COMPUTING_DIRECTORYECTORY = $(WORKSPACE_LOC)computing
    #@echo $(error COMPUTING_DIRECTORY= $(COMPUTING_DIRECTORY))

    ifeq ($(DSP),Y)
        include $(COMPUTING_DIRECTORY)/dsp/dsp_preconfig.mk
    endif

endif