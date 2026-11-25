$(info CAN_FLAGSHIP_MK_INC=  $(CAN_FLAGSHIP_MK_INC) )
ifneq ($(CAN_FLAGSHIP_MK_INC),Y)
    CAN_FLAGSHIP_MK_INC=Y

    CAN_FLAGSHIP_DIR = $(MCAL_FLAGSHIP_DIR)/can
    # $(error CAN_FLAGSHIP_DIR=$(CAN_FLAGSHIP_DIR))

    CAN_INTERRUPT=Y

    INCDIR += -I$(CAN_FLAGSHIP_DIR)
    MCAL_OPT += -DHAS_CAN_FLAGSHIP
    MCAL_OPT += -DHAS_CAN_CUSTOM

    MCAL_OPT += -DCAN_CLOCK_FROM_BUS=1

    SOURCES_C += $(CAN_FLAGSHIP_DIR)/can_mcal.c
    SOURCES_C += $(CAN_FLAGSHIP_DIR)/can_misc.c
    SOURCES_C += $(CAN_FLAGSHIP_DIR)/can_core.c

    include $(CAN_FLAGSHIP_DIR)/canNode/canNode.mk

    ifeq ($(CAN_FD_HEARTBEAT_PROC),Y)
        MCAL_OPT += -DHAS_CAN_FD_HEARTBEAT_PROC
    endif

    ifeq ($(CAN0),Y)
        MCAL_OPT += -DCAN_NODE0_IS_USED=1
        MCAL_OPT += -DHAS_CAN0
    endif
    
    ifeq ($(CAN1),Y)
        MCAL_OPT += -DCAN_NODE1_IS_USED=1
        MCAL_OPT += -DHAS_CAN1
    endif

    ifeq ($(CAN2),Y)
        MCAL_OPT += -DCAN_NODE2_IS_USED=1
        MCAL_OPT += -DHAS_CAN2
    endif

    ifeq ($(CAN3),Y)
        MCAL_OPT += -DCAN_NODE3_IS_USED=1
        MCAL_OPT += -DHAS_CAN3
    endif

    ifeq ($(CAN4),Y)
        MCAL_OPT += -DCAN_NODE4_IS_USED=1
        MCAL_OPT += -DHAS_CAN4
    endif

    ifeq ($(CAN5),Y)
        MCAL_OPT += -DCAN_NODE5_IS_USED=1
        MCAL_OPT += -DHAS_CAN5
    endif

    ifeq ($(CAN6),Y)
        MCAL_OPT += -DCAN_NODE6_IS_USED=1
        MCAL_OPT += -DHAS_CAN6
    endif

    ifeq ($(CAN7),Y)
        MCAL_OPT += -DCAN_NODE7_IS_USED=1
        MCAL_OPT += -DHAS_CAN7
    endif

    ifeq ($(CAN8),Y)
        MCAL_OPT += -DCAN_NODE8_IS_USED=1
        MCAL_OPT += -DHAS_CAN8
    endif

    ifeq ($(CAN9),Y)
        MCAL_OPT += -DCAN_NODE9_IS_USED=1
        MCAL_OPT += -DHAS_CAN9
    endif


    ifeq ($(CAN_INTERRUPT),Y)
        MCAL_OPT += -DHAS_CAN_INTERRUPT
        SOURCES_C += $(CAN_FLAGSHIP_DIR)/can_custom_isr.c
    endif

    ifeq ($(CLI),Y)
        ifeq ($(CAN_DIAG),Y)
            MCAL_OPT += -DHAS_CAN_CUSTOM_DIAG
            SOURCES_DIAG_C += $(CAN_FLAGSHIP_DIR)/can_custom_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(CAN_COMMANDS),Y)
            MCAL_OPT += -DHAS_CAN_CUSTOM_COMMANDS
            SOURCES_C += $(CAN_FLAGSHIP_DIR)/can_custom_commands.c
        endif
    endif

    include $(CAN_FLAGSHIP_DIR)/can_registers/can_registers.mk
    include $(CAN_FLAGSHIP_DIR)/can_message_buffer/can_message_buffer.mk
    include $(CAN_FLAGSHIP_DIR)/can_enhanced_fifo/can_enhanced_fifo.mk
    include $(CAN_FLAGSHIP_DIR)/can_legacy_fifo/can_legacy_fifo.mk
endif