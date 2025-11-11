ifneq ($(DSP_PRECONFIG_MK_INC),Y)
    DSP_PRECONFIG_MK_INC=Y

    DSP_DIR = $(COMPUTING_DIR)/dsp
    #@echo $(error DSP_DIR= $(DSP_DIR))

    ifeq ($(FOURIER_SERIES),Y)
        include $(DSP_DIR)/fourier_series/fourier_series_preconfig.mk
    endif

    ifeq ($(DFT),Y)
        include $(DSP_DIR)/dft/dft_preconfig.mk
    endif

    ifeq ($(FIR),Y)
        #@echo $(error FIR=$(FIR))
        include $(DSP_DIR)/fir/fir_preconfig.mk
    endif

    ifeq ($(IIR),Y)
        #@echo $(error IIR=$(IIR))
        include $(DSP_DIR)/iir/iir_preconfig.mk
    endif
endif