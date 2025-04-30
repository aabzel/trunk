ifneq ($(DSP_MK_INC),Y)
    DSP_MK_INC=Y

    DSP_DIR = $(COMPUTING_DIR)/dsp
    #@echo $(error DSP_DIR= $(DSP_DIR))

    OPT += -DHAS_DSP
    SOURCES_C += $(DSP_DIR)/dsp.c

    INCDIR += -I$(DSP_DIR)

    ifeq ($(DECIMATOR),Y)
        include $(DSP_DIR)/decimator/decimator.mk
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
        #@echo $(error FIR=$(FIR))
        include $(DSP_DIR)/fir/fir.mk
    endif

    ifeq ($(PHASE_DETECTOR),Y)
        #@echo $(error phase_detector=$(phase_detector))
        include $(DSP_DIR)/phase_detector/phase_detector.mk
    endif

    ifeq ($(FIR_INT),Y)
        #@echo $(error FIR_INT=$(FIR_INT))
        include $(DSP_DIR)/fir_int/fir_int.mk
    endif

    ifeq ($(IIR),Y)
        #@echo $(error IIR=$(IIR))
        include $(DSP_DIR)/iir/iir.mk
    endif

    ifeq ($(CLI),Y)
        ifeq ($(DSP_COMMANDS),Y)
            OPT += -DHAS_DSP_COMMANDS
        endif
    endif

    ifeq ($(SCHMITT_TRIGGER),Y)
        #@echo $(error SCHMITT_TRIGGER=$(SCHMITT_TRIGGER))
        include $(DSP_DIR)/schmitt_trigger/schmitt_trigger.mk
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(DSP_DIAG),Y)
            OPT += -DHAS_DSP_DIAG
            SOURCES_C += $(DSP_DIR)/dsp_diag.c
        endif
    endif
    
endif