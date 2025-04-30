$(info FFT_MK_INC=$(FFT_MK_INC))

ifneq ($(FFT_MK_INC),Y)
    FFT_MK_INC=Y

    FFT_DIR=$(DSP_DIR)/fft

    INCDIR += -I$(FFT_DIR)
    OPT += -DHAS_FFT

    SOURCES_C += $(FFT_DIR)/fft_mcal.c
endif
