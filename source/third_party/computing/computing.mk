ifneq ($(TP_COMPUTING_MK_INC),Y)
    TP_COMPUTING_MK_INC=Y

    MCAL_OPT += -DHAS_COMPUTING
    TP_COMPUTING_DIR = $(THIRD_PARTY_DIR)/computing
    #@echo $(error TP_COMPUTING_DIR= $(TP_COMPUTING_DIR))
    INCDIR += -I$(TP_COMPUTING_DIR)

    ifeq ($(DSP),Y)
        include $(TP_COMPUTING_DIR)/dsp/dsp.mk
    endif
endif