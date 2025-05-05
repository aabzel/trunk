ifneq ($(FILE_API_COM_MK_INC),Y)
    FILE_API_COM_MK_INC=Y
    FILE_API_COM_DIR = $(STORAGE_DIR)/file_api
    #@echo $(error FILE_API_DIR = $(FILE_API_DIR))
    OPT += -DHAS_FILE_API
    INCDIR += -I$(FILE_API_COM_DIR)
    SOURCES_C += $(FILE_API_COM_DIR)/file_api.c

    ifeq ($(DIAG),Y)
        ifeq ($(FILE_API_DIAG),Y)
            OPT += -DHAS_FILE_API_DIAG
            SOURCES_C += $(FILE_API_COM_DIR)/file_api_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        #@echo $(error CLI=$(CLI))
        ifeq ($(FILE_API_COMMANDS),Y)
            #@echo $(error FILE_API_COMMANDS = $(FILE_API_COMMANDS))
            OPT += -DHAS_FILE_API_COMMANDS
            SOURCES_C += $(FILE_API_COM_DIR)/file_api_commands.c
        endif
    endif
endif

