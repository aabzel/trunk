ifneq ($(TP_DSP_MK_INC),Y)
    TP_DSP_MK_INC=Y

    TP_DSP_DIR = $(TP_COMPUTING_DIR)/dsp
    #@echo $(error TP_DSP_DIR= $(TP_DSP_DIR))

    INCDIR += -I$(TP_DSP_DIR)

    ifeq ($(FFT),Y)
        include $(TP_DSP_DIR)/fft/fft.mk
    endif
endif