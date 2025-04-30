
$(info VOLTAGE_DIVIDER_MK_INC=$(VOLTAGE_DIVIDER_MK_INC))

ifneq ($(VOLTAGE_DIVIDER_MK_INC),Y)
    VOLTAGE_DIVIDER_MK_INC=Y

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )
    $(info Build  + voltage divider)

    VOLTAGE_DIVIDER_DIR = $(COMPUTING_DIR)/voltage_divider
    #@echo $(error VOLTAGE_DIVIDER_DIR=$(VOLTAGE_DIVIDER_DIR))

    INCDIR += -I$(VOLTAGE_DIVIDER_DIR)

    SOURCES_C += $(VOLTAGE_DIVIDER_DIR)/voltage_divider.c

    OPT += -DHAS_VOLTAGE_DIVIDER

    ifeq ($(DIAG),Y)
        ifeq ($(VOLTAGE_DIVIDER_DIAG),Y)
            OPT += -DHAS_VOLTAGE_DIVIDER_DIAG
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(VOLTAGE_DIVIDER_COMMANDS),Y)
            #@echo $(error VOLTAGE_DIVIDER_COMMANDS=$(VOLTAGE_DIVIDER_COMMANDS))
            OPT += -DHAS_VOLTAGE_DIVIDER_COMMANDS
            SOURCES_C += $(VOLTAGE_DIVIDER_DIR)/voltage_divider_commands.c
        endif
    endif
endif