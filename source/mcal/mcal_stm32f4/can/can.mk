$(info CAN_CUSTOM_MK_INC=  $(CAN_CUSTOM_MK_INC) )
ifneq ($(CAN_CUSTOM_MK_INC),Y)
    CAN_CUSTOM_MK_INC=Y

    CAN_CUSTOM_DIR = $(MCAL_STM32F4_DIR)/can
    # $(error CAN_CUSTOM_DIR=$(CAN_CUSTOM_DIR))

    INCDIR += -I$(CAN_CUSTOM_DIR)
    MCAL_OPT += -DHAS_CAN_CUSTOM

    SOURCES_C += $(CAN_CUSTOM_DIR)/can_misc.c
    SOURCES_C += $(CAN_CUSTOM_DIR)/can_core.c

    ifeq ($(CAN1),Y)
        MCAL_OPT += -DHAS_CAN1
    endif

    ifeq ($(CAN2),Y)
        MCAL_OPT += -DHAS_CAN2
    endif

    ifeq ($(CAN_CUSTOM_INTERRUPT),Y)
        MCAL_OPT += -DHAS_CAN_INTERRUPT
        MCAL_OPT += -DHAS_CAN_CUSTOM_INTERRUPT
        SOURCES_C += $(CAN_CUSTOM_DIR)/can_call_backs.c
        SOURCES_C += $(CAN_CUSTOM_DIR)/can_custom_isr.c
    endif

    ifeq ($(CAN_STM32),Y)
        # $(error CAN_STM32=$(CAN_STM32))
        MCAL_OPT += -DHAS_CAN_STM32
    endif
    
    SOURCES_C += $(CAN_CUSTOM_DIR)/can_mcal.c

    ifeq ($(DIAG),Y)
        ifeq ($(CAN_DIAG),Y)
            MCAL_OPT += -DHAS_CAN_CUSTOM_DIAG
            SOURCES_DIAG_C += $(CAN_CUSTOM_DIR)/can_custom_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(CAN_COMMANDS),Y)
            MCAL_OPT += -DHAS_CAN_CUSTOM_COMMANDS
            SOURCES_C += $(CAN_CUSTOM_DIR)/can_custom_commands.c
        endif
    endif

    include $(CAN_CUSTOM_DIR)/can_registers/can_registers.mk
endif