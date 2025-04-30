$(info I2S_MK_INC=$(I2S_MK_INC))

ifneq ($(I2S_MK_INC),Y)
    I2S_MK_INC=Y


    I2S_CUSTOM_DIR = $(MCAL_STM32F4_DIR)/i2s
    #@echo $(error I2S_CUSTOM_DIR=$(I2S_CUSTOM_DIR))

    INCDIR += -I$(I2S_CUSTOM_DIR)
    OPT += -DHAS_I2S_CUSTOM

    OPT += -DHAS_I2S_ISR
    SOURCES_C += $(I2S_CUSTOM_DIR)/i2s_drv.c

    ifeq ($(I2S1),Y)
        $(info Add I2S1)
        OPT += -DHAS_I2S1
    endif

    ifeq ($(I2S2),Y)
        $(info Add I2S2)
        OPT += -DHAS_I2S2
    endif
    
    ifeq ($(I2S3),Y)
        $(info Add I2S3)
        OPT += -DHAS_I2S3
    endif

    ifeq ($(DIAG),Y)
        OPT += -DHAS_I2S_DIAG
        SOURCES_C += $(I2S_CUSTOM_DIR)/i2s_custom_diag.c
    endif

    ifeq ($(CLI),Y)
        ifeq ($(I2S_COMMANDS),Y)
            OPT += -DHAS_I2S_COMMANDS
            SOURCES_C += $(I2S_CUSTOM_DIR)/i2s_custom_commands.c
        endif
    endif
endif
