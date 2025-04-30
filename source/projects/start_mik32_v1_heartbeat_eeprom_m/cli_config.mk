$(info CLI_CONFIG_MK_INC=$(CLI_CONFIG_MK_INC) )
ifneq ($(CLI_CONFIG_MK_INC),Y)
    CLI_CONFIG_MK_INC=Y
    CONNECTIVITY_COMMANDS=Y
    STORAGE_COMMANDS=Y
    CLI=Y
    CLI_CMD_HISTORY=Y

    ifeq ($(PARAM),Y)
        PARAM_COMMANDS=Y
    endif
    
    ifeq ($(BOOT),Y)
        BOOT_COMMANDS=Y
    endif
    
    ifeq ($(SYSTEM),Y)
        SYSTEM_COMMANDS=Y
    endif
    
    ifeq ($(DEBUGGER),Y)
        DEBUGGER_COMMANDS=Y
    endif

    ifeq ($(NVS),Y)
        NVS_COMMANDS=Y
    endif

    ifeq ($(FLOAT),Y)
        FLOAT_COMMANDS=Y
    endif

    ifeq ($(EEPROM),Y)
        EEPROM_COMMANDS=Y
    endif

    ifeq ($(ASICS),Y)
        ASICS_COMMANDS=Y
    endif
    
    ifeq ($(RV32IMC),Y)
        RV32IMC_COMMANDS=Y
    endif
    
    ifeq ($(W25Q32JV),Y)
        W25Q32JV_COMMANDS=Y
    endif
    
    ifeq ($(SPIFI),Y)
        SPIFI_COMMANDS=Y
    endif

    ifeq ($(SENSITIVITY),Y)
        SENSITIVITY_COMMANDS=Y
    endif

    ifeq ($(SCR1_TIMER),Y)
        SCR1_TIMER_COMMANDS=Y
    endif

    ifeq ($(TIME),Y)
        TIME_COMMANDS=Y
    endif
    
    ifeq ($(NOR_FLASH),Y)
        NOR_FLASH_COMMANDS=Y
    endif
    
    ifeq ($(INTERRUPT),Y)
        INTERRUPT_COMMANDS=Y
    endif

    ifeq ($(BOOT_MANAGER),Y)
        BOOT_MANAGER_COMMANDS=Y
    endif

    ifeq ($(CORE),Y)
        CORE_COMMANDS=Y
    endif
    

    ifeq ($(CLI_NATIVE),Y)
        CLI_NATIVE_COMMANDS=Y
    endif
    
    ifeq ($(FLASH),Y)
        FLASH_COMMANDS=Y
    endif

    BOOTLOADER_COMMANDS=N
    IWDG_COMMANDS=N
    ifeq ($(BOARD),Y)
        BOARD_COMMANDS=Y
    endif
    
    ifeq ($(CONTROL),Y)
        CONTROL_COMMANDS=Y
    endif
    
    ifeq ($(ADC),Y)
       ADC_COMMANDS=N
    endif
    
    ifeq ($(SUPER_CYCLE),Y)
        SUPER_CYCLE_COMMANDS=Y
    endif
    ifeq ($(CONNECTIVITY),Y)
        CONNECTIVITY_COMMANDS=Y
    endif

    ifeq ($(CLOCK),Y)
        CLOCK_COMMANDS=Y
    endif

    ifeq ($(INTERFACES),Y)
        INTERFACES_COMMANDS=Y
    endif
    
    ifeq ($(DMA),Y)
        DMA_COMMANDS=Y
    endif
    
    ifeq ($(FLASH_FS),Y)
        FLASH_FS_COMMANDS=Y
    endif
    
    ifeq ($(FAT_FS),Y)
        FAT_FS_COMMANDS=Y
    endif
    
    ifeq ($(STORAGE),Y)
        STORAGE_COMMANDS=Y
    endif

    ifeq ($(STRING_READER),Y)
        STRING_READER_COMMANDS=Y
    endif
    
    ifeq ($(I2C),Y)
        I2C_COMMANDS=Y
    endif
    
    ifeq ($(LED),Y)
        LED_COMMANDS=Y
    endif
    
    ifeq ($(GPIO),Y)
        GPIO_COMMANDS=Y
    endif

    
    ifeq ($(LOG),Y)
        LOG_COMMANDS=Y
    endif
    
    ifeq ($(TASK),Y)
        TASK_COMMANDS=Y
    endif
    
    ifeq ($(UART),Y)
        UART_COMMANDS=Y
    endif

    ifeq ($(UNIT_TEST),Y)
        UNIT_TEST_COMMANDS=Y
    endif
    
endif