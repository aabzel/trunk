ifneq ($(NAU8814_EHAL_MK_INC),Y)
    NAU8814_EHAL_MK_INC=Y

    TP_NAU8814_DIR = $(THIRD_PARTY_ASICS_DIR)/nau8814
    #@echo $(error TP_NAU8814_DIR=$(TP_NAU8814_DIR))

    INCDIR += -I$(TP_NAU8814_DIR)

    $(info +TP_NAU8814)
    
    OPT += -DNAU8814_IN_USE
    OPT += -DHAS_NAU8814_EHAL
    OPT += -DHAS_NAU8814_EHAL_PROC

    ifeq ($(NAU8814_VERIFY),Y)
        OPT += -DHAS_NAU8814_VERIFY
    endif

    ifeq ($(NAU8814_I2S_SLAVE),Y)
        OPT += -DHAS_NAU8814_I2S_SLAVE
    endif

    ifeq ($(NAU8814_I2S_MASTER),Y)
        OPT += -DHAS_NAU8814_I2S_MASTER
    endif

    SOURCES_THIRD_PARTY_C += $(TP_NAU8814_DIR)/nau8814_driver.c
    SOURCES_THIRD_PARTY_C += $(TP_NAU8814_DIR)/nau8814_configuration.c

    ifeq ($(NAU8814_ADC),Y)
        $(info +NAU8814_ADC)
        #@echo $(error NAU8814_ADC=$(NAU8814_ADC))
        include $(TP_NAU8814_DIR)/adc/adc.mk
    endif

    ifeq ($(NAU8814_DAC),Y)
        $(info +NAU8814_DAC)
        #@echo $(error NAU8814_DAC=$(NAU8814_DAC))
        include $(TP_NAU8814_DIR)/dac/dac.mk
    endif

    ifneq ($(NAU8814_DAC),Y)
        ifneq ($(NAU8814_ADC),Y)
            $(info Select some part of driver)
        endif
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(NAU8814_DIAG),Y)
            OPT += -DHAS_NAU8814_DIAG
            SOURCES_THIRD_PARTY_C += $(TP_NAU8814_DIR)/nau8814_diagnostic.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(NAU8814_COMMANDS),Y)
            OPT += -DHAS_NAU8814_CLI
            SOURCES_THIRD_PARTY_C += $(TP_NAU8814_DIR)/nau8814_cli.c
        endif
    endif
endif
