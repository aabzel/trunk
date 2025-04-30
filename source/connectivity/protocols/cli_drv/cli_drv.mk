$(info CLI_DRV_MK_LOG=$(CLI_DRV_MK_LOG))

ifneq ($(CLI_DRV_MK_LOG),Y)
    CLI_DRV_MK_LOG=Y
    CLI_DRV_DIR = $(PROTOCOLS_DIR)/cli_drv
    #@echo $(error CLI_DRV_DIR= $(CLI_DRV_DIR))

    INCDIR += -I$(CLI_DRV_DIR)

    CLI=Y
    OPT += -DHAS_CLI
    #OPT += -DHAS_CLI_PROC

    ifeq ($(CLI_SUB_COMMAND),Y)
        OPT += -DHAS_CLI_SUB_COMMAND
    endif

    ifeq ($(TEST_FIRMWARE_COMMANDS),Y)
        OPT += -DHAS_TEST_FIRMWARE_COMMANDS
    endif

    ifeq ($(CLI_CMD_HISTORY),Y)
        OPT += -DHAS_CLI_CMD_HISTORY
    endif

    SOURCES_C += $(CLI_DRV_DIR)/cli_drv.c
    SOURCES_C += $(CLI_DRV_DIR)/cli_general_config.c
    #SOURCES_C += $(CLI_DRV_DIR)/string_reader.c

    ifeq ($(CLI_DIAG),Y)
        OPT += -DHAS_CLI_DIAG
        SOURCES_C +=  $(CLI_DRV_DIR)/cli_diag.c
    endif

    ifeq ($(CLI_NATIVE_COMMANDS),Y)
        OPT += -DHAS_CLI_NATIVE_COMMANDS
        #@echo $(error CLI_NATIVE_COMMANDS= $(CLI_NATIVE_COMMANDS))
        SOURCES_C +=  $(CLI_DRV_DIR)/cli_native_commands.c
    endif
endif