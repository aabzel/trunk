ifneq ($(SEGGER_RTT_MK_INC),Y)
    SEGGER_RTT_MK_INC=Y

    SEGGER_RTT_DIR = $(INTERFACES_DIR)/segger_rtt
    # $(error SEGGER_RTT_DIR=$(SEGGER_RTT_DIR))

    INCDIR += -I$(SEGGER_RTT_DIR)

    MCAL_OPT += -DHAS_SEGGER_RTT

    ifeq ($(SEGGER_RTT_PROC),Y)
        MCAL_OPT += -DHAS_SEGGER_RTT_PROC
    endif

    SOURCES_C += $(SEGGER_RTT_DIR)/segger_rtt_mcal.c

    ifeq ($(SEGGER_RTT_INTERRUPTS),Y)
        MCAL_OPT += -DHAS_SEGGER_RTT_INTERRUPTS
        SOURCES_C += $(SEGGER_RTT_DIR)/segger_rtt_isr.c
    endif

    # must be outside
    SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/segger_rtt_config.c

    ifeq ($(DIAG),Y)
        ifeq ($(SEGGER_RTT_DIAG),Y)
            MCAL_OPT += -DHAS_SEGGER_RTT_DIAG
            SOURCES_DIAG_C += $(SEGGER_RTT_DIR)/segger_rtt_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(SEGGER_RTT_COMMANDS),Y)
            MCAL_OPT += -DHAS_SEGGER_RTT_COMMANDS
            SOURCES_C += $(SEGGER_RTT_DIR)/segger_rtt_commands.c
        endif
    endif
endif
