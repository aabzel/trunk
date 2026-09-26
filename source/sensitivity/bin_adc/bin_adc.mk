ifneq ($(BIN_ADC_MK_INC),Y)
    BIN_ADC_MK_INC=Y

    BIN_ADC_DIR = $(SENSITIVITY_DIR)/bin_adc
    # $(error BIN_ADC_DIR=$(BIN_ADC_DIR))

    INCDIR += -I$(BIN_ADC_DIR)

    MCAL_OPT += -DHAS_BIN_ADC

    ifeq ($(BIN_ADC_PROC),Y)
        MCAL_OPT += -DHAS_BIN_ADC_PROC
    endif

    SOURCES_C += $(BIN_ADC_DIR)/bin_adc_mcal.c

    ifeq ($(BIN_ADC_INTERRUPTS),Y)
        MCAL_OPT += -DHAS_BIN_ADC_INTERRUPTS
        SOURCES_C += $(BIN_ADC_DIR)/bin_adc_isr.c
    endif

    # must be outside
    SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/bin_adc_config.c

    ifeq ($(DIAG),Y)
        ifeq ($(BIN_ADC_DIAG),Y)
            MCAL_OPT += -DHAS_BIN_ADC_DIAG
            SOURCES_DIAG_C += $(BIN_ADC_DIR)/bin_adc_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(BIN_ADC_COMMANDS),Y)
            MCAL_OPT += -DHAS_BIN_ADC_COMMANDS
            SOURCES_C += $(BIN_ADC_DIR)/bin_adc_commands.c
        endif
    endif
endif
