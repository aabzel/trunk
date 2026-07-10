ifneq ($(REC_PLAY_MK_INC),Y)
    REC_PLAY_MK_INC=Y

    REC_PLAY_DIR = $(APPLICATIONS_DIR)/rec_play
    # $(error REC_PLAY_DIR=$(REC_PLAY_DIR))

    INCDIR += -I$(REC_PLAY_DIR)

    MCAL_OPT += -DHAS_REC_PLAY
    MCAL_OPT += -DHAS_REC_PLAY_PROC

    SOURCES_C += $(REC_PLAY_DIR)/rec_play_mcal.c

    ifeq ($(REC_PLAY_INTERRUPTS),Y)
        MCAL_OPT += -DHAS_REC_PLAY_INTERRUPTS
        SOURCES_C += $(REC_PLAY_DIR)/rec_play_isr.c
    endif

    # must be outside
    SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/rec_play_config.c

    ifeq ($(DIAG),Y)
        ifeq ($(REC_PLAY_DIAG),Y)
            MCAL_OPT += -DHAS_REC_PLAY_DIAG
            SOURCES_DIAG_C += $(REC_PLAY_DIR)/rec_play_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(REC_PLAY_COMMANDS),Y)
            MCAL_OPT += -DHAS_REC_PLAY_COMMANDS
            SOURCES_C += $(REC_PLAY_DIR)/rec_play_commands.c
        endif
    endif
endif
