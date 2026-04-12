ifneq ($(HIST_FILTER_MK_INC),Y)
    HIST_FILTER_MK_INC=Y

    HIST_FILTER_DIR = $(DSP_DIR)/hist_filter
    # $(error HIST_FILTER_DIR=$(HIST_FILTER_DIR))

    INCDIR += -I$(HIST_FILTER_DIR)

    MCAL_OPT += -DHAS_HIST_FILTER

    ifeq ($(HIST_FILTER_PROC),Y)
        MCAL_OPT += -DHAS_HIST_FILTER_PROC
    endif

    SOURCES_C += $(HIST_FILTER_DIR)/hist_filter_mcal.c

    ifeq ($(HIST_FILTER_INTERRUPTS),Y)
        MCAL_OPT += -DHAS_HIST_FILTER_INTERRUPTS
        SOURCES_C += $(HIST_FILTER_DIR)/hist_filter_isr.c
    endif

    # must be outside
    SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/hist_filter_config.c

    ifeq ($(DIAG),Y)
        ifeq ($(HIST_FILTER_DIAG),Y)
            MCAL_OPT += -DHAS_HIST_FILTER_DIAG
            SOURCES_DIAG_C += $(HIST_FILTER_DIR)/hist_filter_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(HIST_FILTER_COMMANDS),Y)
            MCAL_OPT += -DHAS_HIST_FILTER_COMMANDS
            SOURCES_C += $(HIST_FILTER_DIR)/hist_filter_commands.c
        endif
    endif
endif
