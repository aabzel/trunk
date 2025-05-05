
ifneq ($(FILE_PC_COM_MK_INC),Y)
    FILE_PC_COM_MK_INC=Y

    FILE_PC_DIR = $(STORAGE_DIR)/file_pc
    #@echo $(error FILE_PC_DIR = $(FILE_PC_DIR))

    OPT += -DHAS_FILE_PC
    OPT += -DHAS_FILE_API_CUSTOM

    INCDIR += -I$(FILE_PC_DIR)
    SOURCES_C += $(FILE_PC_DIR)/file_pc.c

    ifeq ($(DIAG),Y)
        ifeq ($(FILE_PC_DIAG),Y)
            OPT += -DHAS_FILE_PC_DIAG
            SOURCES_C += $(FILE_PC_DIR)/file_pc_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        #@echo $(error CLI=$(CLI))
        ifeq ($(FILE_PC_COMMANDS),Y)
            #@echo $(error FILE_PC_COMMANDS = $(FILE_PC_COMMANDS))
            OPT += -DHAS_FILE_PC_COMMANDS
            SOURCES_C += $(FILE_PC_DIR)/file_pc_commands.c
        endif
    endif
endif
