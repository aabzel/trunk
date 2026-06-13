$(info CLI_CONFIG_MK_INC=$(CLI_CONFIG_MK_INC) )
ifneq ($(CLI_CONFIG_MK_INC),Y)
    CLI_CONFIG_MK_INC=Y
    CONNECTIVITY_COMMANDS=Y
    STORAGE_COMMANDS=Y
    PARAM_COMMANDS=Y
    ifeq ($(CLI_NATIVE),Y)
        CLI_NATIVE_COMMANDS=Y
    endif
    
    ifeq ($(FLASH),Y)
        FLASH_COMMANDS=Y
    endif
    BOOTLOADER_COMMANDS=N
    IWDG_COMMANDS=N
    ifeq ($(CONTROL),Y)
        CONTROL_COMMANDS=Y
    endif
    ifeq ($(SUPER_CYCLE),Y)
        SUPER_CYCLE_COMMANDS=Y
    endif
    ifeq ($(CONNECTIVITY),Y)
        CONNECTIVITY_COMMANDS=Y
    endif

    ifeq ($(INTERFACES),Y)
        INTERFACES_COMMANDS=Y
    endif
    ifeq ($(FLASH_FS),Y)
        FLASH_FS_COMMANDS=Y
    endif
    ifeq ($(STORAGE),Y)
        STORAGE_COMMANDS=Y
    endif
    ifeq ($(STRING_READER),Y)
        STRING_READER_COMMANDS=Y
    endif
    GPIO_COMMANDS=Y
    LED_COMMANDS=Y
    LOG_COMMANDS=Y
    TASK_COMMANDS=Y
    UART_COMMANDS=Y
    UNIT_TEST_COMMANDS=Y
endif