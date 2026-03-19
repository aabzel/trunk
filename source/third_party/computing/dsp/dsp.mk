ifneq ($(TP_DIGITAL_SIGNAL_PROCESSING_MK_INC),Y)
    TP_DIGITAL_SIGNAL_PROCESSING_MK_INC=Y

    DIGITAL_SIGNAL_PROCESSING_DIR = $(COMPUTING_DIRECTORY)/dsp
    #@echo $(error TP_DSP_DIR= $(TP_DSP_DIR))
    OPT += -DHAS_DSP
    INCDIR += -I$(DIGITAL_SIGNAL_PROCESSING_DIR)

    ifeq ($(DFT),Y)
        include $(DIGITAL_SIGNAL_PROCESSING_DIR)/discrete_fourier_transform/discrete_fourier_transform.mk
    endif
endif