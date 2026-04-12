ifneq ($(I2C_FSM_F43X_MK_INC),Y)
    I2C_FSM_F43X_MK_INC=Y

    I2C_FSM_F43X_DIR = $(I2C_FSM_CUSTMOM_DIR)/i2c_fsm_at32f43x
    #@echo $(error I2C_FSM_F43X_DIR=$(I2C_FSM_F43X_DIR))
    INCDIR += -I$(I2C_FSM_F43X_DIR)

    MCAL_OPT += -DHAS_I2C_FSM_F43X

    SOURCES_C += $(I2C_FSM_F43X_DIR)/i2c_fsm_f43x.c

    ifeq ($(DIAG),Y)
        ifeq ($(I2C_DIAG),Y)
            MCAL_OPT += -DHAS_I2C_FSM_F43X_DIAG
            SOURCES_C += $(I2C_FSM_F43X_DIR)/i2c_fsm_f43x_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(I2C_COMMANDS),Y)
            MCAL_OPT += -DHAS_I2C_FSM_F43X_COMMANDS
            #SOURCES_C += $(I2C_FSM_F43X_DIR)/i2c_fsm_f43x_commands.c
        endif
    endif
endif