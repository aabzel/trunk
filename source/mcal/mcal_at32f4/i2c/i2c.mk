ifneq ($(I2C_CUSTOM_MK_INC),Y)
    I2C_CUSTOM_MK_INC=Y

    I2C_CUSTMOM_DIR = $(MCAL_AT32F4_DIR)/i2c
    #@echo $(error I2C_CUSTMOM_DIR=$(I2C_CUSTMOM_DIR))
    INCDIR += -I$(I2C_CUSTMOM_DIR)

    OPT += -DHAS_I2C
    OPT += -DHAS_I2C_TASKS
    OPT += -DHAS_I2C_CUSTOM

    SOURCES_C += $(I2C_CUSTMOM_DIR)/i2c_mcal.c
    SOURCES_C += $(I2C_CUSTMOM_DIR)/i2c_custom_isr.c

    ifeq ($(I2C1),Y)
        OPT += -DHAS_I2C1
    endif

    ifeq ($(I2C2),Y)
        OPT += -DHAS_I2C2
    endif

    ifeq ($(I2C3),Y)
        OPT += -DHAS_I2C3
    endif
    
    ifeq ($(AT32F43X),Y)
        #@echo $(error AT32F43X=$(AT32F43X))
        include $(I2C_CUSTMOM_DIR)/i2c_at32f43x/i2c_at32f43x.mk
    endif
    
    ifeq ($(AT32F413X),Y)
        #@echo $(error AT32F413X=$(AT32F413X))
        include $(I2C_CUSTMOM_DIR)/i2c_at32f413x/i2c_at32f413x.mk
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(I2C_DIAG),Y)
            OPT += -DHAS_I2C_CUSTOM_DIAG
            SOURCES_C += $(I2C_CUSTMOM_DIR)/i2c_custom_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(I2C_COMMANDS),Y)
            OPT += -DHAS_I2C_CUSTOM_COMMANDS
            SOURCES_C += $(I2C_CUSTMOM_DIR)/i2c_custom_commands.c
        endif
    endif
endif