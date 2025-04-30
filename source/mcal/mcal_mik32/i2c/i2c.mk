ifneq ($(I2C_MK_INC),Y)
    I2C_MK_INC=Y

    I2C_CUMIKO_DIR = $(MCAL_MIK32_DIR)/i2c
    #@echo $(error I2C_CUMIKO_DIR=$(I2C_CUMIKO_DIR))

    INCDIR += -I$(I2C_CUMIKO_DIR)
    OPT += -DHAS_I2C

    SOURCES_C += $(I2C_CUMIKO_DIR)/i2c_mcal.c
    SOURCES_C += $(I2C_CUMIKO_DIR)/i2c_custom_isr.c

    ifeq ($(I2C1),Y)
        OPT += -DHAS_I2C1
    endif

    ifeq ($(I2C2),Y)
        OPT += -DHAS_I2C2
    endif

    ifeq ($(I2C3),Y)
        OPT += -DHAS_I2C3
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(I2C_DIAG),Y)
            OPT += -DHAS_I2C_CUSTOM_DIAG
            SOURCES_C += $(I2C_CUMIKO_DIR)/i2c_custom_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(I2C_COMMANDS),Y)
            OPT += -DHAS_I2C_CUSTOM_COMMANDS
            SOURCES_C += $(I2C_CUMIKO_DIR)/i2c_custom_commands.c
        endif
    endif
endif