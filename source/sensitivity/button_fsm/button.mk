
$(info BUTTON_MK_INC=$(BUTTON_MK_INC))

ifneq ($(BUTTON_MK_INC),Y)
    BUTTON_MK_INC=Y

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )

    BUTTON_DIR = $(SENSITIVITY_DIR)/button_fsm
    #@echo $(error BUTTON_DIR=$(BUTTON_DIR))

    INCDIR += -I$(BUTTON_DIR)
    SOURCES_C += $(BUTTON_DIR)/button_drv.c
    SOURCES_H += $(BUTTON_DIR)/button_drv.h

    BUTTON=Y
    OPT += -DHAS_BUTTON
    OPT += -DHAS_BUTTON_PROC

    ifeq ($(BUTTON_DIAG),Y)
        OPT += -DHAS_BUTTON_DIAG
        SOURCES_C += $(BUTTON_DIR)/button_diag.c
    endif

    ifeq ($(CLI),Y)
        ifeq ($(BUTTON_COMMANDS),Y)
            OPT += -DHAS_BUTTON_COMMANDS
            SOURCES_C += $(BUTTON_DIR)/button_commands.c
        endif
    endif
endif