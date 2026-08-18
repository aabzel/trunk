ifneq ($(NAU8814_DAC_MK_INC),Y)
    NAU8814_DAC_MK_INC=Y

    NAU8814_DAC_DIR = $(NAU8814_DIR)/dac
    #@echo $(error NAU8814_DAC_DIR=$(NAU8814_DAC_DIR))
    INCDIR += -I$(NAU8814_DAC_DIR)

    OPT += -DHAS_NAU8814_DAC

    SOURCES_C += $(NAU8814_DAC_DIR)/nau8814_dac.c
    #SOURCES_C += $(NAU8814_DAC_DIR)/nau8814_config.c

    ifeq ($(DIAG),Y)
        ifeq ($(NAU8814_DIAG),Y)
            OPT += -DHAS_NAU8814_DAC_DIAG
            SOURCES_C += $(NAU8814_DAC_DIR)/nau8814_dac_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(NAU8814_COMMANDS),Y)
            OPT += -DHAS_NAU8814_DAC_COMMANDS
            SOURCES_C += $(NAU8814_DAC_DIR)/nau8814_dac_commands.c
        endif
    endif
endif
