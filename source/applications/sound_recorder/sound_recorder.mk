ifneq ($(SOUND_RECORDER_MK_INC),Y)
    SOUND_RECORDER_MK_INC=Y

    SOUND_RECORDER_DIR = $(APPLICATIONS_DIR)/sound_recorder
    # $(error SOUND_RECORDER_DIR=$(SOUND_RECORDER_DIR))

    INCDIR += -I$(SOUND_RECORDER_DIR)

    MCAL_OPT += -DHAS_SOUND_RECORDER
    MCAL_OPT += -DHAS_SOUND_RECORDER_PROC

    SOURCES_C += $(SOUND_RECORDER_DIR)/sound_recorder_mcal.c
    SOURCES_C += $(SOUND_RECORDER_DIR)/sound_recorder_isr.c

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
