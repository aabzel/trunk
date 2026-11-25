ifneq ($(CAN_RX_HIST_MK_INC),Y)
    CAN_RX_HIST_MK_INC=Y

    CAN_RX_HIST_DIR = $(APPLICATIONS_DIR)/can_rx_hist
    # $(error CAN_RX_HIST_DIR=$(CAN_RX_HIST_DIR))

    INCDIR += -I$(CAN_RX_HIST_DIR)

    MCAL_OPT += -DHAS_CAN_RX_HIST
    MCAL_OPT += -DHAS_CAN_RX_HIST_PROC

    #ifeq ($(CAN_RX_HIST_PROC),Y)
    #endif

    SOURCES_C += $(CAN_RX_HIST_DIR)/can_rx_hist_mcal.c

    ifeq ($(CAN_RX_HIST_INTERRUPTS),Y)
        MCAL_OPT += -DHAS_CAN_RX_HIST_INTERRUPTS
        SOURCES_C += $(CAN_RX_HIST_DIR)/can_rx_hist_isr.c
    endif

    # must be outside
    SOURCES_C += $(CAN_RX_HIST_DIR)/can_rx_hist_config.c

    ifeq ($(DIAG),Y)
        ifeq ($(CAN_RX_HIST_DIAG),Y)
            MCAL_OPT += -DHAS_CAN_RX_HIST_DIAG
            SOURCES_DIAG_C += $(CAN_RX_HIST_DIR)/can_rx_hist_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(CAN_RX_HIST_COMMANDS),Y)
            MCAL_OPT += -DHAS_CAN_RX_HIST_COMMANDS
            SOURCES_C += $(CAN_RX_HIST_DIR)/can_rx_hist_commands.c
        endif
    endif
endif
