ifneq ($(BACK_COUNT_MK_INC),Y)
    BACK_COUNT_MK_INC=Y

    BACK_COUNT_DIR = $(COMPUTING_DIR)/back_count
    # $(error BACK_COUNT_DIR=$(BACK_COUNT_DIR))

    INCDIR += -I$(BACK_COUNT_DIR)

    MCAL_OPT += -DHAS_BACK_COUNT

    ifeq ($(BACK_COUNT_PROC),Y)
        MCAL_OPT += -DHAS_BACK_COUNT_PROC
    endif

    SOURCES_C += $(BACK_COUNT_DIR)/back_count_mcal.c

    # must be outside
    SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/back_count_config.c

    ifeq ($(DIAG),Y)
        ifeq ($(BACK_COUNT_DIAG),Y)
            MCAL_OPT += -DHAS_BACK_COUNT_DIAG
            SOURCES_DIAG_C += $(BACK_COUNT_DIR)/back_count_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(BACK_COUNT_COMMANDS),Y)
            MCAL_OPT += -DHAS_BACK_COUNT_COMMANDS
            SOURCES_C += $(BACK_COUNT_DIR)/back_count_commands.c
        endif
    endif
endif
