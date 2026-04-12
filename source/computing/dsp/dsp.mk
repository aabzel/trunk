ifneq ($(DSP_MK_INC),Y)
    DSP_MK_INC=Y

    DSP_DIR = $(COMPUTING_DIR)/dsp
    #  $(error DSP_DIR= $(DSP_DIR))

    MCAL_OPT += -DHAS_DSP
    SOURCES_C += $(DSP_DIR)/dsp.c

    INCDIR += -I$(DSP_DIR)

    ifeq ($(DECIMATOR),Y)
        include $(DSP_DIR)/decimator/decimator.mk
    endif

    ifeq ($(HIST_FILTER),Y)
        include $(DSP_DIR)/hist_filter/hist_filter.mk
    endif

    ifeq ($(DFT),Y)
        include $(DSP_DIR)/dft/dft.mk
    endif

    ifeq ($(CORRELATOR),Y)
        include $(DSP_DIR)/correlator/correlator.mk
    endif


    ifeq ($(QUADRATURE_MIXER),Y)
        include $(DSP_DIR)/quadrature_mixer/quadrature_mixer.mk
    endif

    ifeq ($(ECHO_EFFECT),Y)
        include $(DSP_DIR)/echo_effect/echo_effect.mk
    endif
    
    ifeq ($(FOURIER_SERIES),Y)
        include $(DSP_DIR)/fourier_series/fourier_series.mk
    endif

    ifeq ($(SCAN),Y)
        # $(error SCAN=$(SCAN))
        include $(DSP_DIR)/scan/scan.mk
    endif
    
    ifeq ($(FFT),Y)
        include $(DSP_DIR)/fft/fft.mk
    endif
    
    ifeq ($(FIR),Y)
        #  $(error FIR=$(FIR))
        include $(DSP_DIR)/fir/fir.mk
    endif

    ifeq ($(MEDIAN_FILTER),Y)
        #  $(error MEDIAN_FILTER=$(MEDIAN_FILTER))
        include $(DSP_DIR)/median_filter/median_filter.mk
    endif
    
    ifeq ($(MEDIAN_FILTER_FAST),Y)
        #  $(error MEDIAN_FILTER_FAST=$(MEDIAN_FILTER_FAST))
        include $(DSP_DIR)/median_filter_fast/median_filter_fast.mk
    endif
    
    ifeq ($(PHASE_DETECTOR),Y)
        #  $(error phase_detector=$(phase_detector))
        include $(DSP_DIR)/phase_detector/phase_detector.mk
    endif

    ifeq ($(FIR_INT),Y)
        #  $(error FIR_INT=$(FIR_INT))
        include $(DSP_DIR)/fir_int/fir_int.mk
    endif

    ifeq ($(IIR),Y)
        #  $(error IIR=$(IIR))
        include $(DSP_DIR)/iir/iir.mk
    endif

    ifeq ($(CLI),Y)
        ifeq ($(DSP_COMMANDS),Y)
            MCAL_OPT += -DHAS_DSP_COMMANDS
        endif
    endif

    ifeq ($(SCHMITT_TRIGGER),Y)
        #  $(error SCHMITT_TRIGGER=$(SCHMITT_TRIGGER))
        include $(DSP_DIR)/schmitt_trigger/schmitt_trigger.mk
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(DSP_DIAG),Y)
            MCAL_OPT += -DHAS_DSP_DIAG
            SOURCES_C += $(DSP_DIR)/dsp_diag.c
        endif
    endif
    
endif