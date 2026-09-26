ifneq ($(FILE_MCAL_MK_INC),Y)
    FILE_MCAL_MK_INC=Y

    FILE_MCAL_DIR = $(STORAGE_DIR)/file_mcal
    # $(error FILE_MCAL_DIR = $(FILE_MCAL_DIR))

    MCAL_OPT += -DHAS_FILE_MCAL

    INCDIR += -I$(FILE_MCAL_DIR)

    ifeq ($(FILE_MCAL_PROC),Y)
        MCAL_OPT += -DHAS_FILE_MCAL_PROC
    endif

    SOURCES_C += $(FILE_MCAL_DIR)/file_mcal.c

    ifeq ($(DIAG),Y)
        ifeq ($(FILE_MCAL_DIAG),Y)
            MCAL_OPT += -DHAS_FILE_MCAL_DIAG
            SOURCES_DIAG_C += $(FILE_MCAL_DIR)/file_mcal_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(FILE_MCAL_COMMANDS),Y)
            MCAL_OPT += -DHAS_FILE_MCAL_COMMANDS
            SOURCES_C += $(FILE_MCAL_DIR)/file_mcal_commands.c
        endif
    endif
endif

