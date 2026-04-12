ifneq ($(BYTE_GENERAL_MK_INC),Y)
    BYTE_GENERAL_MK_INC=Y

    BYTE_MCAL_DIR = $(MISCELLANEOUS_DIR)/byte_misc
    # $(error BYTE_MCAL_DIR=$(BYTE_MCAL_DIR))

    INCDIR += -I$(BYTE_MCAL_DIR)
    MCAL_OPT += -DHAS_BYTE_MICS

    SOURCES_C += $(BYTE_MCAL_DIR)/byte_utils.c

    ifeq ($(DIAG),Y)
        #ifeq ($(BYTE_DIAG),Y)
            MCAL_OPT += -DHAS_BYTE_DIAG
            SOURCES_C += $(BYTE_MCAL_DIR)/byte_diag.c
        #endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(BYTE_COMMANDS),Y)
            # $(error BYTE_COMMANDS=$(BYTE_COMMANDS))
            $(info Add BYTE commands)
            MCAL_OPT += -DHAS_BYTE_COMMANDS
            SOURCES_C += $(BYTE_MCAL_DIR)/byte_commands.c
        endif
    endif
endif