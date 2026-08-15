ifneq ($(SOUND_RECORDER_MK_INC),Y)
    SOUND_RECORDER_MK_INC=Y

    SOUND_RECORDER_DIR = $(APPLICATIONS_DIR)/sound_recorder
    # $(error SOUND_RECORDER_DIR=$(SOUND_RECORDER_DIR))

    INCDIR += -I$(SOUND_RECORDER_DIR)

    MCAL_OPT += -DHAS_SOUND_RECORDER
    MCAL_OPT += -DHAS_SOUND_RECORDER_PROC

    MCAL_OPT += -DREC_MEM_SAM_CNT=$(REC_MEM_SAM_CNT)

    SOURCES_C += $(SOUND_RECORDER_DIR)/sound_recorder_mcal.c
    
    ifeq ($(SOUND_RECORDER_INTERRUPT),Y)
        SOURCES_C += $(SOUND_RECORDER_DIR)/sound_recorder_isr.c
    endif
    
    # must be outside
    SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/sound_recorder_config.c

    ifeq ($(DIAG),Y)
        ifeq ($(SOUND_RECORDER_DIAG),Y)
            MCAL_OPT += -DHAS_SOUND_RECORDER_DIAG
            SOURCES_DIAG_C += $(SOUND_RECORDER_DIR)/sound_recorder_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(SOUND_RECORDER_COMMANDS),Y)
            MCAL_OPT += -DHAS_SOUND_RECORDER_COMMANDS
            SOURCES_C += $(SOUND_RECORDER_DIR)/sound_recorder_commands.c
        endif
    endif
endif
