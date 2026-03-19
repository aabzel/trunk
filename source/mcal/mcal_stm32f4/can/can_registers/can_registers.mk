$(info CAN_REGISTERS_MK_INC=  $(CAN_REGISTERS_MK_INC) )
ifneq ($(CAN_REGISTERS_MK_INC),Y)
    CAN_REGISTERS_MK_INC=Y

    CAN_REGISTERS_DIR = $(CAN_CUSTOM_DIR)/can_registers
    # $(error CAN_REGISTERS_DIR=$(CAN_REGISTERS_DIR))
    INCDIR += -I$(CAN_REGISTERS_DIR)
    MCAL_OPT += -DHAS_CAN_REGISTERS

    SOURCES_C += $(CAN_REGISTERS_DIR)/can_registers.c

    ifeq ($(CLI),Y)
        ifeq ($(CAN_DIAG),Y)
            SOURCES_C += $(CAN_REGISTERS_DIR)/can_registers_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(CAN_COMMANDS),Y)
            SOURCES_C += $(CAN_REGISTERS_DIR)/can_registers_commands.c
        endif
    endif
endif