ifneq ($(DSP_PRECONFIG_MK_INC),Y)
    DSP_PRECONFIG_MK_INC=Y

    DSP_DIR = $(COMPUTING_DIR)/dsp
    #  $(error DSP_DIR= $(DSP_DIR))

    ifeq ($(DFT),Y)
        include $(DSP_DIR)/dft/dft_preconfig.mk
    endif

    ifeq ($(SLIDING_INTEGRAL),Y)
        include $(DSP_DIR)/sliding_integral/sliding_integral_preconfig.mk
    endif

    ifeq ($(DC_CUT_FILTER),Y)
        #  $(error QUAD_MIX_4FS=$(QUAD_MIX_4FS))
        include $(DSP_DIR)/dc_cut_filter/dc_cut_filter_preconfig.mk
    endif

    ifeq ($(QUAD_MIX_4FS),Y)
        #  $(error QUAD_MIX_4FS=$(QUAD_MIX_4FS))
        include $(DSP_DIR)/quad_mix_4fs/quad_mix_4fs_preconfig.mk
    endif

    ifeq ($(FIR),Y)
        #  $(error FIR=$(FIR))
        include $(DSP_DIR)/fir/fir_preconfig.mk
    endif

    ifeq ($(FIR_INT),Y)
        #  $(error FIR_INT=$(FIR_INT))
        include $(DSP_DIR)/fir_int/fir_int_preconfig.mk
    endif

    ifeq ($(FOURIER_SERIES),Y)
        include $(DSP_DIR)/fourier_series/fourier_series_preconfig.mk
    endif

    ifeq ($(IIR),Y)
        #  $(error IIR=$(IIR))
        include $(DSP_DIR)/iir/iir_preconfig.mk
    endif

    ifeq ($(SCHMITT_TRIGGER),Y)
        #  $(error SCHMITT_TRIGGER=$(SCHMITT_TRIGGER))
        include $(DSP_DIR)/schmitt_trigger/schmitt_trigger_preconfig.mk
    endif
endif