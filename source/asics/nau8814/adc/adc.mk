ifneq ($(NAU8814_ADC_MK_INC),Y)
    NAU8814_ADC_MK_INC=Y

    NAU8814_ADC_DIR = $(NAU8814_DIR)/adc
    #@echo $(error NAU8814_ADC_DIR=$(NAU8814_ADC_DIR))

    INCDIR += -I$(NAU8814_ADC_DIR)

    OPT += -DHAS_NAU8814_ADC

    SOURCES_C += $(NAU8814_ADC_DIR)/nau8814_adc.c

    ifeq ($(DIAG),Y)
        ifeq ($(NAU8814_DIAG),Y)
            OPT += -DHAS_NAU8814_ADC_DIAG
            SOURCES_C += $(NAU8814_ADC_DIR)/nau8814_adc_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(NAU8814_COMMANDS),Y)
                OPT += -DHAS_NAU8814_ADC_COMMANDS
                SOURCES_C += $(NAU8814_ADC_DIR)/nau8814_adc_commands.c
        endif
    endif
endif
