ifneq ($(MAX9860_ADC_MK_INC),Y)
    MAX9860_ADC_MK_INC=Y

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )

    MAX9860_ADC_DIR = $(MAX9860_DIR)/adc
    #@echo $(error MAX9860_ADC_DIR=$(MAX9860_ADC_DIR))

    INCDIR += -I$(MAX9860_ADC_DIR)

    MCAL_OPT += -DHAS_MAX9860_ADC
    SOURCES_C += $(MAX9860_ADC_DIR)/max9860_adc_drv.c

    ifeq ($(DIAG),Y)
        ifeq ($(MAX9860_DIAG),Y)
            MCAL_OPT += -DHAS_MAX9860_ADC_DIAG
            SOURCES_C += $(MAX9860_ADC_DIR)/max9860_adc_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(MAX9860_COMMANDS),Y)
                MCAL_OPT += -DHAS_MAX9860_ADC_COMMANDS
                SOURCES_C += $(MAX9860_ADC_DIR)/max9860_adc_commands.c
        endif
    endif
endif
