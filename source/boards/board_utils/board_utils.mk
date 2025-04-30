$(info BOARD_UTILS_H_MK_INC= $(BOARD_UTILS_H_MK_INC))
ifneq ($(BOARD_UTILS_H_MK_INC),Y)
    BOARD_UTILS_H_MK_INC=Y

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )

    BOARD_UTILS_H_DIR = $(WORKSPACE_LOC)boards/board_utils
    #@echo $(error BOARD_UTILS_H_DIR=$(BOARD_UTILS_H_DIR))

    INCDIR += -I$(BOARD_UTILS_H_DIR)

    OPT += -DHAS_BOARD_UTILS

endif