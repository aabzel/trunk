ifneq ($(I2C_GENERAL_MK_INC),Y)
    I2C_GENERAL_MK_INC=Y

    I2C_MCAL_DIR = $(MCAL_COMMON_DIR)/i2c
    #@echo $(error I2C_MCAL_DIR=$(I2C_MCAL_DIR))

    INCDIR += -I$(I2C_MCAL_DIR)

    SOURCES_C += $(I2C_MCAL_DIR)/i2c_general.c
    SOURCES_C += $(I2C_MCAL_DIR)/i2c_database.c
    SOURCES_C += $(I2C_MCAL_DIR)/i2c_isr.c

    ifeq ($(I2C_SCAN_IN_INIT),Y)
        OPT += -DHAS_I2C_SCAN_IN_INIT
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(I2C_DIAG),Y)
            #@echo $(error I2C_DIAG=$(I2C_DIAG))
            OPT += -DHAS_I2C_DIAG
            SOURCES_C += $(I2C_MCAL_DIR)/i2c_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(I2C_COMMANDS),Y)
            #@echo $(error I2C_COMMANDS=$(I2C_COMMANDS))
            OPT += -DHAS_I2C_COMMANDS
            SOURCES_C += $(I2C_MCAL_DIR)/i2c_commands.c
        endif
    endif
endif