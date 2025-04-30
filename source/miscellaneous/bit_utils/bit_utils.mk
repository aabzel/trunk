ifneq ($(BIT_GENERAL_MK_INC),Y)
    BIT_GENERAL_MK_INC=Y

    BIT_MCAL_DIR = $(MISCELLANEOUS_DIR)/bit_utils
    # $(error BIT_MCAL_DIR=$(BIT_MCAL_DIR))

    INCDIR += -I$(BIT_MCAL_DIR)
    OPT += -DHAS_BIT_UTILS

    SOURCES_C += $(BIT_MCAL_DIR)/bit_utils.c

    ifeq ($(DIAG),Y)
        ifeq ($(BIT_DIAG),Y)
            OPT += -DHAS_BIT_DIAG
            SOURCES_C += $(BIT_MCAL_DIR)/bit_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(BIT_COMMANDS),Y)
            #@echo $(error BIT_COMMANDS=$(BIT_COMMANDS))
            $(info Add BIT commands)
            OPT += -DHAS_BIT_COMMANDS
            SOURCES_C += $(BIT_MCAL_DIR)/bit_commands.c
        endif
    endif
endif