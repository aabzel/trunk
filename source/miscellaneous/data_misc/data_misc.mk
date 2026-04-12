ifneq ($(DATA_MISC_MK_INC),Y)
    DATA_MISC_MK_INC=Y

    DATA_MCAL_DIR = $(MISCELLANEOUS_DIR)/data_misc
    # $(error DATA_MCAL_DIR=$(DATA_MCAL_DIR))

    INCDIR += -I$(DATA_MCAL_DIR)
    MCAL_OPT += -DHAS_DATA_UTILS
    MCAL_OPT += -DHAS_DATA_MISC
    
    SOURCES_C += $(DATA_MCAL_DIR)/data_utils.c

    ifeq ($(DIAG),Y)
        ifeq ($(DATA_DIAG),Y)
            MCAL_OPT += -DHAS_DATA_DIAG
            SOURCES_C += $(DATA_MCAL_DIR)/data_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(DATA_COMMANDS),Y)
            # $(error DATA_COMMANDS=$(DATA_COMMANDS))
            $(info Add DATA commands)
            MCAL_OPT += -DHAS_DATA_COMMANDS
            SOURCES_C += $(DATA_MCAL_DIR)/data_commands.c
        endif
    endif
endif