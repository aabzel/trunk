ifneq ($(MAX9860_DAC_MK_INC),Y)
    MAX9860_DAC_MK_INC=Y

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )

    MAX9860_DAC_DIR = $(MAX9860_DIR)/dac
    #@echo $(error MAX9860_DAC_DIR=$(MAX9860_DAC_DIR))

    INCDIR += -I$(MAX9860_DAC_DIR)
    MCAL_OPT += -DHAS_MAX9860_DAC

    SOURCES_C += $(MAX9860_DAC_DIR)/max9860_dac_drv.c
    #SOURCES_C += $(MAX9860_DAC_DIR)/max9860_config.c

    ifeq ($(DIAG),Y)
        ifeq ($(MAX9860_DIAG),Y)
            MCAL_OPT += -DHAS_MAX9860_DAC_DIAG
            SOURCES_C += $(MAX9860_DAC_DIR)/max9860_dac_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(MAX9860_COMMANDS),Y)
            MCAL_OPT += -DHAS_MAX9860_DAC_COMMANDS
            SOURCES_C += $(MAX9860_DAC_DIR)/max9860_dac_commands.c
        endif
    endif
endif
