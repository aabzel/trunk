
ifneq ($(FILE_PC_COM_MK_INC),Y)
    FILE_PC_COM_MK_INC=Y

    FILE_PC_DIR = $(STORAGE_DIR)/file_pc
    # $(error FILE_PC_DIR = $(FILE_PC_DIR))

    MCAL_OPT += -DHAS_FILE_PC
    MCAL_OPT += -DHAS_FILE_CUSTOM

    INCDIR += -I$(FILE_PC_DIR)
    SOURCES_C += $(FILE_PC_DIR)/file_pc.c

    ifeq ($(DIAG),Y)
        ifeq ($(FILE_PC_DIAG),Y)
            MCAL_OPT += -DHAS_FILE_PC_DIAG
            SOURCES_C += $(FILE_PC_DIR)/file_pc_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        # $(error CLI=$(CLI))
        ifeq ($(FILE_PC_COMMANDS),Y)
            # $(error FILE_PC_COMMANDS = $(FILE_PC_COMMANDS))
            MCAL_OPT += -DHAS_FILE_PC_COMMANDS
            SOURCES_C += $(FILE_PC_DIR)/file_pc_commands.c
        endif
    endif
endif
