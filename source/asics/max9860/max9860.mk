ifneq ($(MAX9860_MK_INC),Y)
    MAX9860_MK_INC=Y

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )

    MAX9860_DIR = $(ASICS_DIR)/max9860
    #@echo $(error MAX9860_DIR=$(MAX9860_DIR))

    INCDIR += -I$(MAX9860_DIR)

    MCAL_OPT += -DHAS_MAX9860
    MCAL_OPT += -DHAS_MAX9860_PROC

    ifeq ($(MAX9860_VERIFY),Y)
        MCAL_OPT += -DHAS_MAX9860_VERIFY
    endif

    ifeq ($(MAX9860_I2S_SLAVE),Y)
        MCAL_OPT += -DHAS_MAX9860_I2S_SLAVE
    endif

    ifeq ($(MAX9860_I2S_MASTER),Y)
        MCAL_OPT += -DHAS_MAX9860_I2S_MASTER
    endif

    SOURCES_C += $(MAX9860_DIR)/max9860_drv.c

    ifeq ($(MAX9860_DAC),Y)
        #@echo $(error MAX9860_DAC=$(MAX9860_DAC))
        include $(MAX9860_DIR)/dac/dac.mk
    endif

    ifeq ($(MAX9860_ADC),Y)
        include $(MAX9860_DIR)/adc/adc.mk
    endif

    ifneq ($(MAX9860_DAC),Y)
        ifneq ($(MAX9860_ADC),Y)
            @echo $(error Select some part of driver)
        endif
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(MAX9860_DIAG),Y)
            MCAL_OPT += -DHAS_MAX9860_DIAG
            SOURCES_C += $(MAX9860_DIR)/max9860_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(MAX9860_COMMANDS),Y)
            MCAL_OPT += -DHAS_MAX9860_COMMANDS
            SOURCES_C += $(MAX9860_DIR)/max9860_commands.c
        endif
    endif
endif
