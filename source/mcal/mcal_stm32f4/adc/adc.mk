$(info ADC_DRV_CUSTOM_MK_INC=$(ADC_DRV_CUSTOM_MK_INC) )
ifneq ($(ADC_DRV_CUSTOM_MK_INC),Y)
    ADC_DRV_CUSTOM_MK_INC=Y

    ADC_CUSTOM_DIR = $(MCAL_STM32F4_DIR)/adc
    # $(error ADC_CUSTOM_DIR=$(ADC_CUSTOM_DIR))
    MCAL_OPT += -DHAS_ADC_CUSTOM

    INCDIR += -I$(ADC_CUSTOM_DIR)

    SOURCES_C += $(ADC_CUSTOM_DIR)/adc_mcal.c
    SOURCES_C += $(ADC_CUSTOM_DIR)/adc_custom_isr.c

    ifeq ($(ADC1),Y)
        MCAL_OPT += -DHAS_ADC1
    endif

    ifeq ($(ADC2),Y)
        MCAL_OPT += -DHAS_ADC2
    endif

    ifeq ($(ADC3),Y)
        MCAL_OPT += -DHAS_ADC3
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(ADC_DIAG),Y)
            MCAL_OPT += -DHAS_ADC_CUSTOM_DIAG
            SOURCES_C += $(ADC_CUSTOM_DIR)/adc_custom_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(ADC_COMMANDS),Y)
            MCAL_OPT += -DHAS_ADC_CUSTOM_COMMANDS
            SOURCES_C += $(ADC_CUSTOM_DIR)/adc_custom_commands.c
        endif
    endif
    
endif