
ifneq ($(CLOCK_CUSTOM_MK_INC),Y)
    CLOCK_CUSTOM_MK_INC=Y

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )

    CLOCK_CUSTOM_DIR = $(BOARD_CFG_DIR)/clock
    #@echo $(error CLOCK_CUSTOM_DIR=$(CLOCK_CUSTOM_DIR))

    INCDIR += -I$(CLOCK_CUSTOM_DIR)
    OPT += -DHAS_CLOCK
    OPT += -DHAS_CLOCK_CUSTOM

    SOURCES_CONFIGURATION_C += $(CLOCK_CUSTOM_DIR)/clock.c

    ifeq ($(DIAG),Y)
        OPT += -DHAS_CLOCK_CUSTOM_DIAG
        SOURCES_CONFIGURATION_C += $(CLOCK_CUSTOM_DIR)/clock_custom_diag.c
    endif

    ifeq ($(CLI),Y)
        ifeq ($(CLOCK_COMMANDS),Y)
            OPT += -DHAS_CLOCK_CUSTOM_COMMANDS
            SOURCES_CONFIGURATION_C += $(CLOCK_CUSTOM_DIR)/clock_custom_commands.c
        endif
    endif
endif
