$(info BOARD_INFO_MK_INC=$(BOARD_INFO_MK_INC))

ifneq ($(BOARD_INFO_MK_INC),Y)
    BOARD_INFO_MK_INC=Y

    $(info + BoardInfo)

    BOARD_INFO_DIR = $(COMPONENTS_DIR)/board_info
    # $(error BOARD_INFO_DIR=$(BOARD_INFO_DIR))

    MCAL_OPT += -DHAS_BOARD_INFO
    INCDIR += -I$(BOARD_INFO_DIR)

    SOURCES_C += $(BOARD_INFO_DIR)/board_info.c

    ifeq ($(BOARD_INFO_DIAG),Y)
        MCAL_OPT += -DHAS_BOARD_INFO_DIAG
        MCAL_OPT += -DHAS_BOARD_DIAG
        SOURCES_C += $(BOARD_INFO_DIR)/board_diag.c
    endif
    # $(error WORKSPACE_LOC=$(WORKSPACE_LOC))
    # $(error BOARD_DIR=$(BOARD_DIR))
endif
