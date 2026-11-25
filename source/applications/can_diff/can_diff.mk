ifneq ($(CAN_DIFF_MK_INC),Y)
    CAN_DIFF_MK_INC=Y

    CAN_DIFF_DIR = $(APPLICATIONS_DIR)/can_diff
    # $(error CAN_DIFF_DIR=$(CAN_DIFF_DIR))

    INCDIR += -I$(CAN_DIFF_DIR)

    MCAL_OPT += -DHAS_CAN_DIFF

    ifeq ($(CAN_DIFF_PROC),Y)
        MCAL_OPT += -DHAS_CAN_DIFF_PROC
    endif

    SOURCES_C += $(CAN_DIFF_DIR)/can_diff_mcal.c

    ifeq ($(CAN_DIFF_INTERRUPTS),Y)
        MCAL_OPT += -DHAS_CAN_DIFF_INTERRUPTS
        SOURCES_C += $(CAN_DIFF_DIR)/can_diff_isr.c
    endif

    # must be outside
    SOURCES_C += $(CAN_DIFF_DIR)/can_diff_config.c

    ifeq ($(DIAG),Y)
        ifeq ($(CAN_DIFF_DIAG),Y)
            MCAL_OPT += -DHAS_CAN_DIFF_DIAG
            SOURCES_DIAG_C += $(CAN_DIFF_DIR)/can_diff_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(CAN_DIFF_COMMANDS),Y)
            MCAL_OPT += -DHAS_CAN_DIFF_COMMANDS
            SOURCES_C += $(CAN_DIFF_DIR)/can_diff_commands.c
        endif
    endif
endif
