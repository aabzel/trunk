$(info PHASE_DETECTOR_MK_INC=$(PHASE_DETECTOR_MK_INC) )

ifneq ($(PHASE_DETECTOR_MK_INC),Y)
    PHASE_DETECTOR_MK_INC=Y

    PHASE_DETECTOR_DIR = $(DSP_DIR)/phase_detector
    #@echo $(error PHASE_DETECTOR_DIR=[$(PHASE_DETECTOR_DIR)])
    INCDIR += -I$(PHASE_DETECTOR_DIR)

    OPT += -DHAS_PHASE_DETECTOR

    SOURCES_C += $(PHASE_DETECTOR_DIR)/phase_detector.c
    SOURCES_C += $(PHASE_DETECTOR_DIR)/phase_detector_isr.c

    ifeq ($(DIAG),Y)
        ifeq ($(PHASE_DETECTOR_DIAG),Y)
            OPT += -DHAS_PHASE_DETECTOR_DIAG
            SOURCES_C += $(PHASE_DETECTOR_DIR)/phase_detector_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(PHASE_DETECTOR_COMMANDS),Y)
            #@echo $(error PHASE_DETECTOR_COMMANDS=[$(PHASE_DETECTOR_COMMANDS)])
            OPT += -DHAS_PHASE_DETECTOR_COMMANDS
            SOURCES_C += $(PHASE_DETECTOR_DIR)/phase_detector_commands.c
        endif
    endif
endif






