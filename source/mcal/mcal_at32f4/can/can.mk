$(info CAN_DRV_MK_INC=  $(CAN_DRV_MK_INC) )
ifneq ($(CAN_DRV_MK_INC),Y)
    CAN_DRV_MK_INC=Y

    CAN_CUSTOM_DIR = $(MCAL_AT32F4_DIR)/can
    #@echo $(error CAN_CUSTOM_DIR=$(CAN_CUSTOM_DIR))

    INCDIR += -I$(CAN_CUSTOM_DIR)
    OPT += -DHAS_CAN

    ifeq ($(CAN1),Y)
        OPT += -DHAS_CAN1
    endif

    ifeq ($(CAN2),Y)
        OPT += -DHAS_CAN2
    endif

    SOURCES_C += $(CAN_CUSTOM_DIR)/can_mcal.c
    SOURCES_C += $(CAN_CUSTOM_DIR)/can_custom_isr.c

    ifeq ($(CLI),Y)
        ifeq ($(CAN_DIAG),Y)
            OPT += -DHAS_CAN_DIAG
            SOURCES_C += $(CAN_CUSTOM_DIR)/can_custom_diag.c
        endif
    endif
    
    ifeq ($(CLI),Y)
        ifeq ($(CAN_COMMANDS),Y)
            OPT += -DHAS_CAN_COMMANDS
            SOURCES_C += $(CAN_CUSTOM_DIR)/can_custom_commands.c
        endif
    endif
endif