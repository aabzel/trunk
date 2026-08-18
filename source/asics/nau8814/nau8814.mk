ifneq ($(NAU8814_MK_INC),Y)
    NAU8814_MK_INC=Y

    NAU8814_DIR = $(ASICS_DIR)/nau8814
    #@echo $(error NAU8814_DIR=$(NAU8814_DIR))

    INCDIR += -I$(NAU8814_DIR)

    OPT += -DHAS_NAU8814
    OPT += -DHAS_NAU8814_PROC

    ifeq ($(NAU8814_VERIFY),Y)
        OPT += -DHAS_NAU8814_VERIFY
    endif

    ifeq ($(NAU8814_I2S_SLAVE),Y)
        OPT += -DHAS_NAU8814_I2S_SLAVE
    endif

    ifeq ($(NAU8814_I2S_MASTER),Y)
        OPT += -DHAS_NAU8814_I2S_MASTER
    endif

    SOURCES_C += $(NAU8814_DIR)/nau8814_drv.c

    ifeq ($(NAU8814_DAC),Y)
        #@echo $(error NAU8814_DAC=$(NAU8814_DAC))
        include $(NAU8814_DIR)/dac/dac.mk
    endif

    ifeq ($(NAU8814_ADC),Y)
        include $(NAU8814_DIR)/adc/adc.mk
    endif

    ifneq ($(NAU8814_DAC),Y)
        ifneq ($(NAU8814_ADC),Y)
            $(info Select some part of driver)
        endif
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(NAU8814_DIAG),Y)
            OPT += -DHAS_NAU8814_DIAG
            SOURCES_C += $(NAU8814_DIR)/nau8814_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(NAU8814_COMMANDS),Y)
            OPT += -DHAS_NAU8814_COMMANDS
            SOURCES_C += $(NAU8814_DIR)/nau8814_commands.c
        endif
    endif
endif
