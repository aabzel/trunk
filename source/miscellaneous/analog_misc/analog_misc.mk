ifneq ($(ANALOG_MISC_GENERAL_MK_INC),Y)
    ANALOG_MISC_GENERAL_MK_INC=Y

    ANALOG_MISC_MCAL_DIR = $(MISCELLANEOUS_DIR)/analog_misc
    # $(error ANALOG_MISC_MCAL_DIR=$(ANALOG_MISC_MCAL_DIR))

    INCDIR += -I$(ANALOG_MISC_MCAL_DIR)
    MCAL_OPT += -DHAS_ANALOG_MISC

    SOURCES_C += $(ANALOG_MISC_MCAL_DIR)/analog_misc.c

    ifeq ($(DIAG),Y)
        ifeq ($(ANALOG_DIAG),Y)
            MCAL_OPT += -DHAS_ANALOG_DIAG
            SOURCES_DIAG_C += $(ANALOG_MISC_MCAL_DIR)/analog_misc_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(ANALOG_MISC_COMMANDS),Y)
            # $(error ANALOG_MISC_COMMANDS=$(ANALOG_MISC_COMMANDS))
            $(info Add ANALOG commands)
            MCAL_OPT += -DHAS_ANALOG_MISC_COMMANDS
            SOURCES_C += $(ANALOG_MISC_MCAL_DIR)/analog_misc_commands.c
        endif
    endif
endif