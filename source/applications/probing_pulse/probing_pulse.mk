ifneq ($(PROBING_PULSE_MK_INC),Y)
    PROBING_PULSE_MK_INC=Y

    PROBING_PULSE_DIR = $(APPLICATIONS_DIR)/probing_pulse
    # $(error PROBING_PULSE_DIR=$(PROBING_PULSE_DIR))

    INCDIR += -I$(PROBING_PULSE_DIR)

    MCAL_OPT += -DHAS_PROBING_PULSE

    ifeq ($(PROBING_PULSE_PROC),Y)
        MCAL_OPT += -DHAS_PROBING_PULSE_PROC
    endif

    SOURCES_C += $(PROBING_PULSE_DIR)/probing_pulse_mcal.c

    ifeq ($(PROBING_PULSE_INTERRUPTS),Y)
        MCAL_OPT += -DHAS_PROBING_PULSE_INTERRUPTS
        SOURCES_C += $(PROBING_PULSE_DIR)/probing_pulse_isr.c
    endif

    # must be outside
    SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/probing_pulse_config.c

    ifeq ($(DIAG),Y)
        ifeq ($(PROBING_PULSE_DIAG),Y)
            MCAL_OPT += -DHAS_PROBING_PULSE_DIAG
            SOURCES_DIAG_C += $(PROBING_PULSE_DIR)/probing_pulse_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(PROBING_PULSE_COMMANDS),Y)
            MCAL_OPT += -DHAS_PROBING_PULSE_COMMANDS
            SOURCES_C += $(PROBING_PULSE_DIR)/probing_pulse_commands.c
        endif
    endif
endif
