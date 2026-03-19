$(info CAN_COMMON_MCAL_MK_INC=$(CAN_COMMON_MCAL_MK_INC) )

ifneq ($(CAN_COMMON_MCAL_MK_INC),Y)
    CAN_COMMON_MCAL_MK_INC=Y

    CAN_MCAL_DIR = $(MCAL_COMMON_DIR)/can
    # $(error CAN_MCAL_DIR=$(CAN_MCAL_DIR))

    INCDIR += -I$(CAN_MCAL_DIR)
    MCAL_OPT += -DHAS_CAN

    ifeq ($(CAN_PROC),Y)
        #$(error CAN_PROC=$(CAN_PROC))
        MCAL_OPT += -DHAS_CAN_PROC
    endif

    ifeq ($(CAN1),Y)
        MCAL_OPT += -DHAS_CAN1
    endif

    ifeq ($(CAN2),Y)
        MCAL_OPT += -DHAS_CAN2
    endif

    SOURCES_C += $(CAN_MCAL_DIR)/can_general.c

    ifeq ($(CAN_FD_HEARTBEAT_PROC),Y)
        MCAL_OPT += -DHAS_CAN_FD_HEARTBEAT_PROC
    endif

    ifeq ($(CAN_HEARTBEAT),Y)
        MCAL_OPT += -DHAS_CAN_HEARTBEAT_PROC
    endif

    ifeq ($(CAN_INTERRUPT),Y)
        # $(error CAN_INTERRUPT=$(CAN_INTERRUPT))
        MCAL_OPT += -DHAS_CAN_INTERRUPT
        SOURCES_C += $(CAN_MCAL_DIR)/can_isr.c  
    endif

    ifeq ($(CAN_FD),Y)
        MCAL_OPT += -DHAS_CAN_FD
        SOURCES_C += $(CAN_MCAL_DIR)/can_fd_general.c

        ifeq ($(CAN_FD_HEARTBEAT),Y)
            MCAL_OPT += -DHAS_CAN_FD_HEARTBEAT_PROC
        endif
    endif

    ifeq ($(CAN_DIAG),Y)
        MCAL_OPT += -DHAS_CAN_DIAG
        SOURCES_DIAG_C += $(CAN_MCAL_DIR)/can_diag.c
    endif

    ifeq ($(CAN_COMMANDS),Y)
        MCAL_OPT += -DHAS_CAN_COMMANDS
        SOURCES_C += $(CAN_MCAL_DIR)/can_commands.c
    endif
endif



