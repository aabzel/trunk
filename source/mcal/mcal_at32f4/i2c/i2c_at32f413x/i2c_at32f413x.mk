ifneq ($(I2C_AT32F413X_MK_INC),Y)
    I2C_AT32F413X_MK_INC=Y

    I2C_AT32F413X_DIR = $(I2C_CUSTMOM_DIR)/i2c_at32f413x
    #@echo $(error I2C_AT32F413X_DIR=$(I2C_AT32F413X_DIR))
    INCDIR += -I$(I2C_AT32F413X_DIR)

    MCAL_OPT += -DHAS_I2C_AT32F413X

    SOURCES_C += $(I2C_AT32F413X_DIR)/i2c_at32f413x.c

    ifeq ($(DIAG),Y)
        ifeq ($(I2C_DIAG),Y)
            MCAL_OPT += -DHAS_I2C_AT32F413X_DIAG
            SOURCES_C += $(I2C_AT32F413X_DIR)/i2c_at32f413x_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(I2C_COMMANDS),Y)
            MCAL_OPT += -DHAS_I2C_AT32F413X_COMMANDS
            #SOURCES_C += $(I2C_AT32F413X_DIR)/i2c_at32f413x_commands.c
        endif
    endif
endif