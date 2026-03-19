ifneq ($(TP_NAU8814_ADC_MK_INC),Y)
    TP_NAU8814_ADC_MK_INC=Y

    TP_NAU8814_ADC_DIR = $(TP_NAU8814_DIR)/adc
    #@echo $(error TP_NAU8814_ADC_DIR=$(TP_NAU8814_ADC_DIR))
    
    $(info +TP_NAU8814_ADC)
    INCDIR += -I$(TP_NAU8814_ADC_DIR)

    OPT += -DNAU8814_ADC_IN_USE

    SOURCES_THIRD_PARTY_C += $(TP_NAU8814_ADC_DIR)/nau8814_adc_driver.c

    ifeq ($(DIAG),Y)
        ifeq ($(NAU8814_DIAG),Y)
            OPT += -DHAS_NAU8814_ADC_DIAG
            SOURCES_THIRD_PARTY_C += $(TP_NAU8814_ADC_DIR)/nau8814_adc_diagnostic.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(NAU8814_COMMANDS),Y)
            #@echo $(error NAU8814_COMMANDS=$(NAU8814_COMMANDS))
            $(info +HAS_NAU8814_ADC_CLI)
            OPT += -DHAS_NAU8814_ADC_CLI
            SOURCES_THIRD_PARTY_C += $(TP_NAU8814_ADC_DIR)/nau8814_adc_cli.c
        endif
    endif
endif
