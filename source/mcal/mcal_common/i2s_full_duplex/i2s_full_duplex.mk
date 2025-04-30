
$(info I2S_GENERAL_MK_INC=  $(I2S_GENERAL_MK_INC) )
ifneq ($(I2S_GENERAL_MK_INC),Y)
    I2S_GENERAL_MK_INC=Y

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )

    #I2S_VOLUME=Y

    I2S_MCAL_DIR = $(MCAL_COMMON_DIR)/i2s
    #@echo $(error I2S_MCAL_DIR=$(I2S_MCAL_DIR))

    INCDIR += -I$(I2S_MCAL_DIR)

    ifeq ($(I2S_VOLUME),Y)
        OPT += -DHAS_I2S_VOLUME
        SOURCES_C += $(I2S_MCAL_DIR)/i2s_volume.c
    endif

    #SOURCES_C += $(I2S_MCAL_DIR)/i2s_diag.c
    SOURCES_C += $(I2S_MCAL_DIR)/i2s_drv_general.c

    ifeq ($(DIAG),Y)
        ifeq ($(I2S_DIAG),Y)
            OPT += -DHAS_I2S_DIAG
            SOURCES_C += $(I2S_MCAL_DIR)/i2s_diag.c
        endif
    endif
    
    ifeq ($(CLI),Y)
        ifeq ($(I2S_COMMANDS),Y)
            OPT += -DHAS_I2S_COMMANDS
            SOURCES_C += $(I2S_MCAL_DIR)/i2s_commands.c
        endif
    endif
endif