ifneq ($(I2C_CUSTOM_MK_INC),Y)
    I2C_CUSTOM_MK_INC=Y

    I2C_CUSTMOM_DIR = $(MCAL_FC7300X_DIR)/i2c
    #@echo $(error I2C_CUSTMOM_DIR=$(I2C_CUSTMOM_DIR))
    INCDIR += -I$(I2C_CUSTMOM_DIR)

    MCAL_OPT += -DHAS_I2C
    MCAL_OPT += -DHAS_I2C_TASKS
    MCAL_OPT += -DHAS_I2C_CUSTOM

    SOURCES_C += $(I2C_CUSTMOM_DIR)/i2c_mcal.c
    SOURCES_C += $(I2C_CUSTMOM_DIR)/i2c_custom_isr.c

    ifeq ($(I2C1),Y)
        MCAL_OPT += -DHAS_I2C1
    endif

    ifeq ($(I2C2),Y)
        MCAL_OPT += -DHAS_I2C2
    endif

    ifeq ($(I2C3),Y)
        MCAL_OPT += -DHAS_I2C3
    endif
    
    ifeq ($(FC7300X3X),Y)
        #@echo $(error FC7300X3X=$(FC7300X3X))
        include $(I2C_CUSTMOM_DIR)/i2c_fc7300x3x/i2c_fc7300x3x.mk
    endif
    
    ifeq ($(FC7300X),Y)
        #@echo $(error FC7300X=$(FC7300X))
        include $(I2C_CUSTMOM_DIR)/i2c_fc7300xx/i2c_fc7300xx.mk
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(I2C_DIAG),Y)
            MCAL_OPT += -DHAS_I2C_CUSTOM_DIAG
            SOURCES_C += $(I2C_CUSTMOM_DIR)/i2c_custom_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(I2C_COMMANDS),Y)
            MCAL_OPT += -DHAS_I2C_CUSTOM_COMMANDS
            SOURCES_C += $(I2C_CUSTMOM_DIR)/i2c_custom_commands.c
        endif
    endif
endif