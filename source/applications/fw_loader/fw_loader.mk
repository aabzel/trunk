ifneq ($(FW_LOADER_MK_INC),Y)
    FW_LOADER_MK_INC=Y

    FW_LOADER_DIR = $(APPLICATIONS_DIR)/fw_loader

    #@ echo $(error FW_LOADER_DIR = $(FW_LOADER_DIR))
    OPT += -DHAS_FW_LOADER
    OPT += -DHAS_FW_LOADER_PROC

    INCDIR += -I$(FW_LOADER_DIR)

    SOURCES_C += $(FW_LOADER_DIR)/fw_loader.c

    ifeq ($(DIAG),Y)
        SOURCES_C += $(FW_LOADER_DIR)/fw_loader_diag.c
    endif
    #SOURCES_C += $(FW_LOADER_DIR)/fw_loader_config.c

    ifeq ($(CLI),Y)
        ifeq ($(FW_LOADER_COMMANDS),Y)
            OPT += -DHAS_FW_LOADER_COMMANDS
            SOURCES_C += $(FW_LOADER_DIR)/fw_loader_commands.c
        endif
    endif
endif


