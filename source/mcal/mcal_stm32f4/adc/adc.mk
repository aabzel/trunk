$(info ADC_DRV_MK_INC=$(ADC_DRV_MK_INC) )
ifneq ($(ADC_DRV_MK_INC),Y)
    ADC_DRV_MK_INC=Y


    ADC_DIR = $(MCAL_STM32F4_DIR)/adc
    #@echo $(error ADC_DIR=$(ADC_DIR))
    OPT += -DHAS_ADC_CUSTOM

    INCDIR += -I$(ADC_DIR)

    SOURCES_C += $(ADC_DIR)/adc_drv.c

    ifeq ($(ADC1),Y)
        OPT += -DHAS_ADC1
    endif

    ifeq ($(ADC2),Y)
        OPT += -DHAS_ADC2
    endif

    ifeq ($(ADC3),Y)
        OPT += -DHAS_ADC3
    endif

    ifeq ($(CLI),Y)
        ifeq ($(ADC_COMMANDS),Y)
            OPT += -DHAS_ADC_COMMANDS
            SOURCES_C += $(ADC_DIR)/adc_commands.c
        endif
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(ADC_DIAG),Y)
            SOURCES_C += $(ADC_DIR)/adc_custom_diag.c
        endif
    endif
endif