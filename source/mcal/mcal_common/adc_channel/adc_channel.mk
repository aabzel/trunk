ifneq ($(ADC_CHANNEL_GENERAL_MK_INC),Y)
    ADC_CHANNEL_GENERAL_MK_INC=Y

    ADC_CHANNEL_MCAL_DIR = $(MCAL_COMMON_DIR)/adc_channel
    # $(error ADC_MCAL_DIR=$(ADC_MCAL_DIR))

    INCDIR += -I$(ADC_CHANNEL_MCAL_DIR)
    MCAL_OPT += -DHAS_ADC_CHANNEL
    
    ifeq ($(ADC_CHANNEL_PROC),Y)
        MCAL_OPT += -DHAS_ADC_CHANNEL_PROC
    endif

    SOURCES_C += $(ADC_CHANNEL_MCAL_DIR)/adc_channel_general.c

    ifeq ($(DIAG),Y)
        ifeq ($(ADC_DIAG),Y)
            MCAL_OPT += -DHAS_ADC_CHANNEL_DIAG
            SOURCES_DIAG_C += $(ADC_MCAL_DIR)/adc_channel_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(ADC_CHANNEL_COMMANDS),Y)
            # $(error ADC_COMMANDS=$(ADC_COMMANDS))
            $(info Add ADC commands)
            MCAL_OPT += -DHAS_ADC_CHANNEL_COMMANDS
            SOURCES_C += $(ADC_MCAL_DIR)/adc_channel_commands.c
        endif
    endif
endif