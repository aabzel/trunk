
ifneq ($(KEYBOARD_MK_INC),Y)
    KEYBOARD_MK_INC=Y

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )

    KEYBOARD_DIR = $(SENSITIVITY_DIR)/keyboard
    #@echo $(error KEYBOARD_DIR= $(KEYBOARD_DIR))

    INCDIR += -I$(KEYBOARD_DIR)
    SOURCES_C += $(KEYBOARD_DIR)/key_board_drv.c
    SOURCES_C += $(KEYBOARD_DIR)/keyboard.c

    OPT += -DHAS_KEYBOARD
    ifeq ($(DIAG),Y)
        ifeq ($(KEYBOARD_DIAG),Y)
            OPT += -DHAS_KEYBOARD_DIAG
            SOURCES_C += $(KEYBOARD_DIR)/keyboard_diag.c
        endif
    endif


    ifeq ($(CLI),Y)
        ifeq ($(KEYBOARD_COMMANDS),Y)
            SOURCES_C += $(KEYBOARD_DIR)/keyboard_commands.c
        endif
    endif
    
endif