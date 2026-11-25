ifneq ($(I2C_FSM_CUSTOM_MK_INC),Y)
    I2C_FSM_CUSTOM_MK_INC=Y

    I2C_FSM_CUSTMOM_DIR = $(MCAL_FC7300X_DIR)/i2c_fsm
    #@echo $(error I2C_FSM_CUSTMOM_DIR=$(I2C_FSM_CUSTMOM_DIR))
    INCDIR += -I$(I2C_FSM_CUSTMOM_DIR)

    MCAL_OPT += -DHAS_I2C_FSM_CUSTOM
    MCAL_OPT += -DHAS_I2C_FSM_CUSTOM_TASKS

    SOURCES_C += $(I2C_FSM_CUSTMOM_DIR)/i2c_fsm_custom.c
    SOURCES_C += $(I2C_FSM_CUSTMOM_DIR)/i2c_fsm_custom_isr.c

    ifeq ($(FC7300X3X),Y)
        include $(I2C_FSM_CUSTMOM_DIR)/i2c_fsm_fc7300x3x/i2c_fsm_f43x.mk
    endif

    ifeq ($(FC7300X),Y)
        include $(I2C_FSM_CUSTMOM_DIR)/i2c_fsm_fc7300xx/i2c_fsm_f413x.mk
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(I2C_DIAG),Y)
            MCAL_OPT += -DHAS_I2C_FSM_CUSTOM_DIAG
            SOURCES_C += $(I2C_FSM_CUSTMOM_DIR)/i2c_fsm_custom_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(I2C_COMMANDS),Y)
            MCAL_OPT += -DHAS_I2C_FSM_CUSTOM_COMMANDS
            SOURCES_C += $(I2C_FSM_CUSTMOM_DIR)/i2c_fsm_custom_commands.c
        endif
    endif
endif