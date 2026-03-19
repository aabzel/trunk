ifneq ($(I2C_FSM_MK_INC),Y)
    I2C_FSM_MK_INC=Y

    I2C_FSM_MCAL_DIR = $(MCAL_COMMON_DIR)/i2c_fsm
    #@echo $(error I2C_FSM_MCAL_DIR=$(I2C_FSM_MCAL_DIR))

    INCDIR += -I$(I2C_FSM_MCAL_DIR)

    SOURCES_C += $(I2C_FSM_MCAL_DIR)/i2c_fsm.c
    SOURCES_C += $(I2C_FSM_MCAL_DIR)/i2c_fsm_isr.c

    MCAL_OPT += -DHAS_I2C_FSM

    ifeq ($(I2C_SCAN_IN_INIT),Y)
        MCAL_OPT += -DHAS_I2C_SCAN_IN_INIT
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(I2C_FSM_DIAG),Y)
            #@echo $(error I2C_FSM_DIAG=$(I2C_FSM_DIAG))
            MCAL_OPT += -DHAS_I2C_FSM_DIAG
            SOURCES_C += $(I2C_FSM_MCAL_DIR)/i2c_fsm_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(I2C_FSM_COMMANDS),Y)
            #@echo $(error I2C_FSM_COMMANDS=$(I2C_FSM_COMMANDS))
            MCAL_OPT += -DHAS_I2C_FSM_COMMANDS
            SOURCES_C += $(I2C_FSM_MCAL_DIR)/i2c_fsm_commands.c
        endif
    endif
endif