ifneq ($(WAV_PLAYER_MK_INC),Y)
    WAV_PLAYER_MK_INC=Y

    WAV_PLAYER_DIR = $(APPLICATIONS_DIR)/wav_player
    # $(error WAV_PLAYER_DIR=$(WAV_PLAYER_DIR))

    INCDIR += -I$(WAV_PLAYER_DIR)

    MCAL_OPT += -DHAS_WAV_PLAYER
    MCAL_OPT += -DHAS_WAV_PLAYER_PROC

    SOURCES_C += $(WAV_PLAYER_DIR)/wav_player_mcal.c

    MCAL_OPT += -DPLAYER_MEM_SIZE=$(PLAYER_MEM_SIZE)
    
    ifeq ($(WAV_PLAYER_INTERRUPTS),Y)
        MCAL_OPT += -DHAS_WAV_PLAYER_INTERRUPTS
        SOURCES_C += $(WAV_PLAYER_DIR)/wav_player_isr.c
    endif

    # must be outside
    SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/wav_player_config.c

    ifeq ($(DIAG),Y)
        ifeq ($(WAV_PLAYER_DIAG),Y)
            MCAL_OPT += -DHAS_WAV_PLAYER_DIAG
            SOURCES_DIAG_C += $(WAV_PLAYER_DIR)/wav_player_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(WAV_PLAYER_COMMANDS),Y)
            MCAL_OPT += -DHAS_WAV_PLAYER_COMMANDS
            SOURCES_C += $(WAV_PLAYER_DIR)/wav_player_commands.c
        endif
    endif
endif
