ifneq ($(DC_CUT_FILTER_MK_INC),Y)
    DC_CUT_FILTER_MK_INC=Y

    DC_CUT_FILTER_DIR = $(DSP_DIR)/dc_cut_filter
    # $(error DC_CUT_FILTER_DIR=$(DC_CUT_FILTER_DIR))

    INCDIR += -I$(DC_CUT_FILTER_DIR)

    MCAL_OPT += -DHAS_DC_CUT_FILTER

    SOURCES_C += $(DC_CUT_FILTER_DIR)/dc_cut_filter_mcal.c

    # must be outside
    SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/dc_cut_filter_config.c

    ifeq ($(DIAG),Y)
        ifeq ($(DC_CUT_FILTER_DIAG),Y)
            MCAL_OPT += -DHAS_DC_CUT_FILTER_DIAG
            SOURCES_DIAG_C += $(DC_CUT_FILTER_DIR)/dc_cut_filter_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(DC_CUT_FILTER_COMMANDS),Y)
            MCAL_OPT += -DHAS_DC_CUT_FILTER_COMMANDS
            SOURCES_C += $(DC_CUT_FILTER_DIR)/dc_cut_filter_commands.c
        endif
    endif
endif
