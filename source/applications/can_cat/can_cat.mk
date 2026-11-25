ifneq ($(CAN_CAT_MK_INC),Y)
    CAN_CAT_MK_INC=Y

    CAN_CAT_DIR = $(APPLICATIONS_DIR)/can_cat
    # $(error CAN_CAT_DIR=$(CAN_CAT_DIR))

    INCDIR += -I$(CAN_CAT_DIR)

    MCAL_OPT += -DHAS_CAN_CAT

    ifeq ($(CAN_CAT_PROC),Y)
        MCAL_OPT += -DHAS_CAN_CAT_PROC
    endif

    SOURCES_C += $(CAN_CAT_DIR)/can_cat_general.c

    # must be outside
    SOURCES_C += $(CAN_CAT_DIR)/can_cat_config.c

    ifeq ($(DIAG),Y)
        ifeq ($(CAN_CAT_DIAG),Y)
            MCAL_OPT += -DHAS_CAN_CAT_DIAG
            SOURCES_C += $(CAN_CAT_DIR)/can_cat_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(CAN_CAT_COMMANDS),Y)
            MCAL_OPT += -DHAS_CAN_CAT_COMMANDS
            SOURCES_C += $(CAN_CAT_DIR)/can_cat_commands.c
        endif
    endif
endif
