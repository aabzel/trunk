$(info CLI_PRECONFIG_MK_LOG=$(CLI_PRECONFIG_MK_LOG))

ifneq ($(CLI_PRECONFIG_MK_LOG),Y)
    CLI_PRECONFIG_MK_LOG=Y

    CLI_DRV_DIR = $(PROTOCOLS_DIR)/cli_drv


    ifeq ($(CLI_CORE),Y)
        include $(CLI_DRV_DIR)/cli_core_commands.mk
    endif


    #TABLE_UTILS=Y
    CLI=Y
    DIAG=Y
    STRING=Y
    STRING_READER=Y
    CSV=Y
endif