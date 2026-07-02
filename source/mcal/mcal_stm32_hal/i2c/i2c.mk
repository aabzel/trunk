ifneq ($(I2C_MK_INC),Y)
    I2C_MK_INC=Y

    I2C_CUSTMO_DIR = $(MCAL_CUSTOM_DIR)/i2c
    #@echo $(error I2C_CUSTMO_DIR=$(I2C_CUSTMO_DIR))

    INCDIR += -I$(I2C_CUSTMO_DIR)
    MCAL_OPT += -DHAS_I2C_CUSTOM

    SOURCES_C += $(I2C_CUSTMO_DIR)/i2c_mcal.c
    SOURCES_C += $(I2C_CUSTMO_DIR)/i2c_custom_isr.c

    ifeq ($(I2C1),Y)
        MCAL_OPT += -DHAS_I2C1
    endif

    ifeq ($(I2C2),Y)
        MCAL_OPT += -DHAS_I2C2
    endif

    ifeq ($(I2C3),Y)
        MCAL_OPT += -DHAS_I2C3
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(I2C_DIAG),Y)
            MCAL_OPT += -DHAS_I2C_CUSTOM_DIAG
            SOURCES_DIAG_C += $(I2C_CUSTMO_DIR)/i2c_custom_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(I2C_COMMANDS),Y)
            MCAL_OPT += -DHAS_I2C_CUSTOM_COMMANDS
            SOURCES_C += $(I2C_CUSTMO_DIR)/i2c_custom_commands.c
        endif
    endif
endif