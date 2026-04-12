ifneq ($(ADC_GENERAL_MK_INC),Y)
    ADC_GENERAL_MK_INC=Y


    ADC_MCAL_DIR = $(MCAL_COMMON_DIR)/adc
    # $(error ADC_MCAL_DIR=$(ADC_MCAL_DIR))

    INCDIR += -I$(ADC_MCAL_DIR)
    MCAL_OPT += -DHAS_ADC
    MCAL_OPT += -DHAS_ADC_PROC

    SOURCES_C += $(ADC_MCAL_DIR)/adc_general_api.c

    ifeq ($(DIAG),Y)
        ifeq ($(ADC_DIAG),Y)
            MCAL_OPT += -DHAS_ADC_DIAG
            SOURCES_C += $(ADC_MCAL_DIR)/adc_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(ADC_COMMANDS),Y)
            # $(error ADC_COMMANDS=$(ADC_COMMANDS))
            $(info Add ADC commands)
            MCAL_OPT += -DHAS_ADC_COMMANDS
            SOURCES_C += $(ADC_MCAL_DIR)/adc_commands.c
        endif
    endif
endif