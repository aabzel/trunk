ifneq ($(TP_MEMORY_MANAGER_MK_INC),Y)
    TP_MEMORY_MANAGER_MK_INC=Y

    TP_MEMORY_MANAGER_DIR = $(THIRD_PARTY_STORAGE_DIR)/memory_manager
    #@echo $(error TP_MEMORY_MANAGER_DIR=$(TP_MEMORY_MANAGER_DIR))

    INCDIR += -I$(TP_MEMORY_MANAGER_DIR)

    MCAL_OPT += -DHAS_MEMORY_MANAGER
    #MCAL_OPT += -DMEMORY_MANAGER_IN_USE

    ifeq ($(MEMORY_MANAGER_PROC),Y)
        MCAL_OPT += -DHAS_MEMORY_MANAGER_PROC
    endif

    SOURCES_THIRD_PARTY_C+= $(TP_MEMORY_MANAGER_DIR)/memory_manager.c

    ifeq ($(DIAG),Y)
        ifeq ($(MEMORY_MANAGER_DIAG),Y)
            MCAL_OPT += -DHAS_MEMORY_MANAGER_DIAGNOSTIC
            SOURCES_THIRD_PARTY_C+= $(TP_MEMORY_MANAGER_DIR)/memory_manager_diagnostic.c
            SOURCES_EHAL_C+= $(TP_MEMORY_MANAGER_DIR)/memory_manager_diagnostic.c
            SOURCES_EHAL_H += $(TP_MEMORY_MANAGER_DIR)/memory_manager_diagnostic.h
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(MEMORY_MANAGER_COMMANDS),Y)
            MCAL_OPT += -DHAS_MEMORY_MANAGER_CLI
            SOURCES_THIRD_PARTY_C+= $(TP_MEMORY_MANAGER_DIR)/memory_manager_cli.c
            SOURCES_EHAL_C+= $(TP_MEMORY_MANAGER_DIR)/memory_manager_cli.c
            SOURCES_EHAL_H += $(TP_MEMORY_MANAGER_DIR)/memory_manager_cli.h
        endif
    endif
    
    # Autoformat index
    
    SOURCES_EHAL_C+= $(TP_MEMORY_MANAGER_DIR)/memory_manager.c
    SOURCES_EHAL_H += $(TP_MEMORY_MANAGER_DIR)/memory_manager.h
    
    # code style check index
    #https://habr.com/ru/articles/843746/
    
    SOURCES_CODE_STYLE_C += $(TP_MEMORY_MANAGER_DIR)/memory_manager.c
    SOURCES_CODE_STYLE_H += $(TP_MEMORY_MANAGER_DIR)/memory_manager.h
endif
