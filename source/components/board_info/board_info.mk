$(info BOARD_INFO_MK_INC=$(BOARD_INFO_MK_INC))

ifneq ($(BOARD_INFO_MK_INC),Y)
    BOARD_INFO_MK_INC=Y

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path))
    $(info + BoardInfo)

    BOARD_INFO_DIR = $(COMPONENTS_DIR)/board_info
    #@echo $(error BOARD_INFO_DIR=$(BOARD_INFO_DIR))

    OPT += -DHAS_BOARD_INFO
    INCDIR += -I$(BOARD_INFO_DIR)

    SOURCES_C += $(BOARD_INFO_DIR)/board_info.c

    ifeq ($(BOARD_INFO_DIAG),Y)
        OPT += -DHAS_BOARD_INFO_DIAG
        SOURCES_C += $(BOARD_INFO_DIR)/board_diag.c
    endif
    #@echo $(error WORKSPACE_LOC=$(WORKSPACE_LOC))
    #@echo $(error BOARD_DIR=$(BOARD_DIR))
endif
