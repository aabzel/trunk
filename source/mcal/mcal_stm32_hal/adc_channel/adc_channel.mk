$(info ADC_DRV_CUSTOM_MK_INC=$(ADC_DRV_CUSTOM_MK_INC) )
ifneq ($(ADC_CHANNEL_DRV_CUSTOM_MK_INC),Y)
    ADC_CHANNEL_DRV_CUSTOM_MK_INC=Y

    ADC_CHANNEL_CUSTOM_DIR = $(MCAL_CUSTOM_DIR)/adc_channel
    # $(error ADC_CUSTOM_DIR=$(ADC_CUSTOM_DIR))
    MCAL_OPT += -DHAS_ADC_CHANNEL_CUSTOM
    
    MCAL_OPT += -DHAS_ADC_CHANNEL_PROC

    INCDIR += -I$(ADC_CHANNEL_CUSTOM_DIR)

    SOURCES_C += $(ADC_CHANNEL_CUSTOM_DIR)/adc_channel_mcal.c

    ifeq ($(DIAG),Y)
        ifeq ($(ADC_CHANNEL_DIAG),Y)
            MCAL_OPT += -DHAS_ADC_CHANNEL_CUSTOM_DIAG
            SOURCES_DIAG_C += $(ADC_CHANNEL_CUSTOM_DIR)/adc_channel_custom_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(ADC_CHANNEL_COMMANDS),Y)
            MCAL_OPT += -DHAS_ADC_CHANNEL_CUSTOM_COMMANDS
            SOURCES_C += $(ADC_CHANNEL_CUSTOM_DIR)/adc_channel_custom_commands.c
        endif
    endif
    
endif