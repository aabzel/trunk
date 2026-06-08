ifneq ($(INCREMENTAL_ENCODER_MK_INC),Y)
    INCREMENTAL_ENCODER_MK_INC=Y

    INCREMENTAL_ENCODER_DIR = $(SENSITIVITY_DIR)/incremental_encoder
    # $(error INCREMENTAL_ENCODER_DIR=$(INCREMENTAL_ENCODER_DIR))

    INCDIR += -I$(INCREMENTAL_ENCODER_DIR)

    MCAL_OPT += -DHAS_INCREMENTAL_ENCODER

    ifeq ($(INCREMENTAL_ENCODER_PROC),Y)
        MCAL_OPT += -DHAS_INCREMENTAL_ENCODER_PROC
    endif

    SOURCES_C += $(INCREMENTAL_ENCODER_DIR)/incremental_encoder_mcal.c

    MCAL_OPT += -DHAS_INCREMENTAL_ENCODER_INTERRUPTS
    SOURCES_C += $(INCREMENTAL_ENCODER_DIR)/incremental_encoder_isr.c

    # must be outside
    SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/incremental_encoder_config.c

    ifeq ($(DIAG),Y)
        ifeq ($(INCREMENTAL_ENCODER_DIAG),Y)
            MCAL_OPT += -DHAS_INCREMENTAL_ENCODER_DIAG
            SOURCES_DIAG_C += $(INCREMENTAL_ENCODER_DIR)/incremental_encoder_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(INCREMENTAL_ENCODER_COMMANDS),Y)
            MCAL_OPT += -DHAS_INCREMENTAL_ENCODER_COMMANDS
            SOURCES_C += $(INCREMENTAL_ENCODER_DIR)/incremental_encoder_commands.c
        endif
    endif
endif
