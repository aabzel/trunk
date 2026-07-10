$(info CLI_CONFIG_MK_INC=$(CLI_CONFIG_MK_INC) )
ifneq ($(CLI_CONFIG_MK_INC),Y)
    CLI_CONFIG_MK_INC=Y

    BOOTLOADER_COMMANDS=Y
    CORTEX_M4_COMMANDS=Y
    ifeq ($(FAT_FS),Y)
        FAT_FS_COMMANDS=Y
    endif

    ifeq ($(HEX_BIN),Y)
        HEX_BIN_COMMANDS=Y
    endif

    ifeq ($(STORAGE),Y)
        STORAGE_COMMANDS=Y
    endif
    IWDG_COMMANDS=N
endif