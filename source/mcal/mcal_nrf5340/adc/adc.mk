$(info ADC_NRF_DRV_MK_INCLUDE=$(ADC_NRF_DRV_MK_INCLUDE))
ifneq ($(ADC_NRF_DRV_MK_INCLUDE),Y)
    ADC_NRF_DRV_MK_INCLUDE=Y

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path))

    ADC_NRF_DIR = $(MCAL_NRF5340_DIR)/adc
    #@echo $(error ADC_NRF_DIR=$(ADC_NRF_DIR))

    INCDIR += -I$(ADC_NRF_DIR)
    ADC=Y
    OPT += -DHAS_ADC
    OPT += -DHAS_ADC1
    OPT += -DHAS_ADC_PROC
    OPT += -DHAS_ADC_CUSTOM
    OPT += -DHAS_ADC_NRF53

    SOURCES_C += $(ADC_NRF_DIR)/adc_drv.c

    ifeq ($(ADC_ISR),Y)
        #@echo $(error ADC_INTERRUPT=$(ADC_INTERRUPT))
        OPT += -DHAS_ADC_INTERRUPT
        OPT += -DHAS_ADC_ISR
        SOURCES_C += $(ADC_NRF_DIR)/adc_isr.c
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(ADC_DIAG),Y)
            OPT += -DHAS_ADC_DIAG
            SOURCES_C += $(ADC_NRF_DIR)/adc_custom_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(ADC_COMMANDS),Y)
            OPT += -DHAS_ADC_COMMANDS
            SOURCES_C += $(ADC_NRF_DIR)/adc_custom_commands.c
        endif
    endif
endif