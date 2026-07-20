ifneq ($(LOOPBACK_AUDIO_MK_INC),Y)
    LOOPBACK_AUDIO_MK_INC=Y

    LOOPBACK_AUDIO_DIR = $(APPLICATIONS_DIR)/loopback_audio
    # $(error LOOPBACK_AUDIO_DIR=$(LOOPBACK_AUDIO_DIR))

    INCDIR += -I$(LOOPBACK_AUDIO_DIR)

    MCAL_OPT += -DHAS_LOOPBACK_AUDIO

    ifeq ($(LOOPBACK_AUDIO_PROC),Y)
        MCAL_OPT += -DHAS_LOOPBACK_AUDIO_PROC
    endif

    SOURCES_C += $(LOOPBACK_AUDIO_DIR)/loopback_audio_mcal.c

    ifeq ($(LOOPBACK_AUDIO_INTERRUPTS),Y)
        MCAL_OPT += -DHAS_LOOPBACK_AUDIO_INTERRUPTS
        SOURCES_C += $(LOOPBACK_AUDIO_DIR)/loopback_audio_isr.c
    endif

    # must be outside
    SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/loopback_audio_config.c

    ifeq ($(DIAG),Y)
        ifeq ($(LOOPBACK_AUDIO_DIAG),Y)
            MCAL_OPT += -DHAS_LOOPBACK_AUDIO_DIAG
            SOURCES_DIAG_C += $(LOOPBACK_AUDIO_DIR)/loopback_audio_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(LOOPBACK_AUDIO_COMMANDS),Y)
            MCAL_OPT += -DHAS_LOOPBACK_AUDIO_COMMANDS
            SOURCES_C += $(LOOPBACK_AUDIO_DIR)/loopback_audio_commands.c
        endif
    endif
endif
