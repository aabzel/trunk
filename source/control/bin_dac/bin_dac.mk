ifneq ($(BIN_DAC_MK_INC),Y)
    BIN_DAC_MK_INC=Y

    BIN_DAC_DIR = $(CONTROL_DIR)/bin_dac
    # $(error BIN_DAC_DIR=$(BIN_DAC_DIR))

    INCDIR += -I$(BIN_DAC_DIR)

    MCAL_OPT += -DHAS_BIN_DAC

    ifeq ($(BIN_DAC_PROC),Y)
        MCAL_OPT += -DHAS_BIN_DAC_PROC
    endif

    SOURCES_C += $(BIN_DAC_DIR)/bin_dac_mcal.c

    #ifeq ($(BIN_DAC_INTERRUPTS),Y)
    #    MCAL_OPT += -DHAS_BIN_DAC_INTERRUPTS
    #endif
    SOURCES_C += $(BIN_DAC_DIR)/bin_dac_isr.c

    # must be outside
    SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/bin_dac_config.c

    ifeq ($(DIAG),Y)
        ifeq ($(BIN_DAC_DIAG),Y)
            MCAL_OPT += -DHAS_BIN_DAC_DIAG
            SOURCES_DIAG_C += $(BIN_DAC_DIR)/bin_dac_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(BIN_DAC_COMMANDS),Y)
            MCAL_OPT += -DHAS_BIN_DAC_COMMANDS
            SOURCES_C += $(BIN_DAC_DIR)/bin_dac_commands.c
        endif
    endif
endif
