$(info TP_FFT_MK_INC=$(TP_FFT_MK_INC))

ifneq ($(TP_FFT_MK_INC),Y)
    TP_FFT_MK_INC=Y

    TP_FFT_DIR=$(TP_DSP_DIR)/fft

    INCDIR += -I$(TP_FFT_DIR)
    MCAL_OPT += -DHAS_FFT

    SOURCES_THIRD_PARTY_C += $(TP_FFT_DIR)/fft.c
endif
