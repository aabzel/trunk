ifneq ($(FLOAT_GENERAL_MK_INC),Y)
    FLOAT_GENERAL_MK_INC=Y

    FLOAT_MCAL_DIR = $(MISCELLANEOUS_DIR)/float_utils
    # $(error FLOAT_MCAL_DIR=$(FLOAT_MCAL_DIR))

    INCDIR += -I$(FLOAT_MCAL_DIR)
    OPT += -DHAS_FLOAT_UTILS

    SOURCES_C += $(FLOAT_MCAL_DIR)/float_utils.c

    ifeq ($(DIAG),Y)
        ifeq ($(FLOAT_DIAG),Y)
            OPT += -DHAS_FLOAT_DIAG
            SOURCES_C += $(FLOAT_MCAL_DIR)/float_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(FLOAT_COMMANDS),Y)
            #@echo $(error FLOAT_COMMANDS=$(FLOAT_COMMANDS))
            $(info Add FLOAT commands)
            OPT += -DHAS_FLOAT_COMMANDS
            SOURCES_C += $(FLOAT_MCAL_DIR)/float_commands.c
        endif
    endif
endif