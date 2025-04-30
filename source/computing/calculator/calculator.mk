
$(info CALCULATOR_MK_INC=$(CALCULATOR_MK_INC))

ifneq ($(CALCULATOR_MK_INC),Y)
    CALCULATOR_MK_INC=Y

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )

    CALCULATOR_DIR = $(COMPUTING_DIR)/calculator
    #@echo $(error CALCULATOR_DIR = $(CALCULATOR_DIR))

    OPT += -DHAS_CALCULATOR
    INCDIR += -I$(CALCULATOR_DIR)

    SOURCES_C += $(CALCULATOR_DIR)/calculator.c

    ifeq ($(DIAG),Y)
        ifeq ($(CALCULATOR_DIAG),Y)
            OPT += -DHAS_CALCULATOR_DIAG
            SOURCES_C += $(CALCULATOR_DIR)/calculator_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(CALCULATOR_COMMANDS),Y)
            #@echo $(error CALCULATOR_COMMANDS = $(CALCULATOR_COMMANDS))
            OPT += -DHAS_CALCULATOR_COMMANDS
            SOURCES_C += $(CALCULATOR_DIR)/calculator_commands.c
        endif
    endif
endif
