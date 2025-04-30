$(info CAN_COMMON_MCAL_MK_INC=$(CAN_COMMON_MCAL_MK_INC) )

ifneq ($(CAN_COMMON_MCAL_MK_INC),Y)
    CAN_COMMON_MCAL_MK_INC=Y

    CAN_MCAL_DIR = $(MCAL_COMMON_DIR)/can
    #@echo $(error CAN_MCAL_DIR=$(CAN_MCAL_DIR))

    INCDIR += -I$(CAN_MCAL_DIR)
    OPT += -DHAS_CAN
    OPT += -DHAS_CAN_PROC

    SOURCES_C += $(CAN_MCAL_DIR)/can_general.c

    ifeq ($(CAN_DIAG),Y)
        OPT += -DHAS_CAN_DIAG
        SOURCES_C += $(CAN_MCAL_DIR)/can_diag.c
    endif

    ifeq ($(CAN_COMMANDS),Y)
        OPT += -DHAS_CAN_COMMANDS
        SOURCES_C += $(CAN_MCAL_DIR)/can_commands.c
    endif
endif



