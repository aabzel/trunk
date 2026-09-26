ifneq ($(I2C_CUSTOM_MK_INC),Y)
    I2C_CUSTOM_MK_INC=Y

    I2C_CUSTMOM_DIR = $(MCAL_X86_DIR)/i2c
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
    
    ifeq ($(X863X),Y)
        #@echo $(error X863X=$(X863X))
        include $(I2C_CUSTMOM_DIR)/i2c_x86x3x/i2c_x86x3x.mk
    endif
    
    ifeq ($(X86),Y)
        #@echo $(error X86=$(X86))
        include $(I2C_CUSTMOM_DIR)/i2c_x86xx/i2c_x86xx.mk
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