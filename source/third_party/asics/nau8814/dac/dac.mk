ifneq ($(TP_NAU8814_DAC_MK_INC),Y)
    TP_NAU8814_DAC_MK_INC=Y

    TP_NAU8814_DAC_DIR = $(TP_NAU8814_DIR)/dac
    #@echo $(error TP_NAU8814_DAC_DIR=$(TP_NAU8814_DAC_DIR))
    INCDIR += -I$(TP_NAU8814_DAC_DIR)

    $(info +TP_NAU8814_DAC)

    OPT += -DNAU8814_DAC_IN_USE

    SOURCES_THIRD_PARTY_C += $(TP_NAU8814_DAC_DIR)/nau8814_dac_driver.c

    ifeq ($(DIAG),Y)
        ifeq ($(NAU8814_DIAG),Y)
            OPT += -DHAS_NAU8814_DAC_DIAG
            SOURCES_THIRD_PARTY_C += $(TP_NAU8814_DAC_DIR)/nau8814_dac_diagnostic.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(NAU8814_COMMANDS),Y)
            $(info +NAU8814_DAC_CLI)
            OPT += -DHAS_NAU8814_DAC_CLI
            SOURCES_THIRD_PARTY_C += $(TP_NAU8814_DAC_DIR)/nau8814_dac_cli.c
        endif
    endif
endif
