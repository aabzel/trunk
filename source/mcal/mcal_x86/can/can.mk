$(info CAN_DRV_MK_INC=  $(CAN_DRV_MK_INC) )
ifneq ($(CAN_DRV_MK_INC),Y)
    CAN_DRV_MK_INC=Y

    CAN_CUSTOM_DIR = $(MCAL_X86_DIR)/can
    #@echo $(error CAN_CUSTOM_DIR=$(CAN_CUSTOM_DIR))

    INCDIR += -I$(CAN_CUSTOM_DIR)
    MCAL_OPT += -DHAS_CAN_CUSTOM

    ifeq ($(CAN_FD_HEARTBEAT_PROC),Y)
        MCAL_OPT += -DHAS_CAN_FD_HEARTBEAT_PROC
    endif

    ifeq ($(CAN0),Y)
        MCAL_OPT += -DHAS_CAN0
    endif
    
    ifeq ($(CAN1),Y)
        MCAL_OPT += -DHAS_CAN1
    endif

    ifeq ($(CAN2),Y)
        MCAL_OPT += -DHAS_CAN2
    endif

    ifeq ($(CAN3),Y)
        MCAL_OPT += -DHAS_CAN3
    endif

    ifeq ($(CAN4),Y)
        MCAL_OPT += -DHAS_CAN4
    endif

    ifeq ($(CAN5),Y)
        MCAL_OPT += -DHAS_CAN5
    endif

    SOURCES_C += $(CAN_CUSTOM_DIR)/can_mcal.c
    SOURCES_C += $(CAN_CUSTOM_DIR)/can_custom_isr.c

    ifeq ($(CLI),Y)
        ifeq ($(CAN_DIAG),Y)
            MCAL_OPT += -DHAS_CAN_CUSTOM_DIAG
            SOURCES_C += $(CAN_CUSTOM_DIR)/can_custom_diag.c
        endif
    endif
    
    ifeq ($(CLI),Y)
        ifeq ($(CAN_COMMANDS),Y)
            MCAL_OPT += -DHAS_CAN_CUSTOM_COMMANDS
            SOURCES_C += $(CAN_CUSTOM_DIR)/can_custom_commands.c
        endif
    endif
endif