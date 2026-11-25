ifneq ($(CAN_TX_PLANNER_MK_INC),Y)
    CAN_TX_PLANNER_MK_INC=Y

    CAN_TX_PLANNER_DIR = $(APPLICATIONS_DIR)/can_tx_planner
    # $(error CAN_TX_PLANNER_DIR=$(CAN_TX_PLANNER_DIR))
    # TODO move to applications
    INCDIR += -I$(CAN_TX_PLANNER_DIR)

    MCAL_OPT += -DHAS_CAN_TX_PLANNER
    MCAL_OPT += -DHAS_CAN_TX_PLANNER_PROC

    SOURCES_C += $(CAN_TX_PLANNER_DIR)/can_tx_planner_mcal.c

    # must be outside
    SOURCES_C += $(CAN_TX_PLANNER_DIR)/can_tx_planner_config.c

    ifeq ($(DIAG),Y)
        ifeq ($(CAN_TX_PLANNER_DIAG),Y)
            MCAL_OPT += -DHAS_CAN_TX_PLANNER_DIAG
            SOURCES_DIAG_C += $(CAN_TX_PLANNER_DIR)/can_tx_planner_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(CAN_TX_PLANNER_COMMANDS),Y)
            # $(error CAN_TX_PLANNER_DIR=$(CAN_TX_PLANNER_DIR))
            MCAL_OPT += -DHAS_CAN_TX_PLANNER_COMMANDS
            SOURCES_C += $(CAN_TX_PLANNER_DIR)/can_tx_planner_commands.c
        endif
    endif
endif
