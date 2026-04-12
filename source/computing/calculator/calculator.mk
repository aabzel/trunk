
$(info CALCULATOR_MK_INC=$(CALCULATOR_MK_INC))

ifneq ($(CALCULATOR_MK_INC),Y)
    CALCULATOR_MK_INC=Y

    CALCULATOR_DIR = $(COMPUTING_DIR)/calculator
    #@echo $(error CALCULATOR_DIR = $(CALCULATOR_DIR))

    MCAL_OPT += -DHAS_CALCULATOR
    INCDIR += -I$(CALCULATOR_DIR)

    SOURCES_C += $(CALCULATOR_DIR)/calculator.c

    ifeq ($(DIAG),Y)
        ifeq ($(CALCULATOR_DIAG),Y)
            MCAL_OPT += -DHAS_CALCULATOR_DIAG
            SOURCES_C += $(CALCULATOR_DIR)/calculator_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(CALCULATOR_COMMANDS),Y)
            #@echo $(error CALCULATOR_COMMANDS = $(CALCULATOR_COMMANDS))
            MCAL_OPT += -DHAS_CALCULATOR_COMMANDS
            SOURCES_C += $(CALCULATOR_DIR)/calculator_commands.c
        endif
    endif
endif
