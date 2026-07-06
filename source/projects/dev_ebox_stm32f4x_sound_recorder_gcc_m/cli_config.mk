$(info CLI_CONFIG_MK_INC=$(CLI_CONFIG_MK_INC) )
ifneq ($(CLI_CONFIG_MK_INC),Y)
    CLI_CONFIG_MK_INC=Y

    #BOOT_COMMANDS=Y
    CLI=Y
    CLI_CMD_HISTORY=Y
    CLI_NATIVE_COMMANDS=Y

    ifeq ($(APPLICATIONS),Y)
        APPLICATIONS_COMMANDS=Y
    endif

    ifeq ($(CORE),Y)
        CORE_COMMANDS=Y
    endif
    
    ifeq ($(FILE_MCAL),Y)
        FILE_MCAL_COMMANDS=Y
    endif

    
    ifeq ($(UART),Y)
        UART_COMMANDS=Y
    endif
    
    ifeq ($(CLOCK),Y)
        CLOCK_COMMANDS=Y
    endif

    ifeq ($(DMA_CHANNEL),Y)
        DMA_CHANNEL_COMMANDS=Y
    endif

    ifeq ($(PWM),Y)
        PWM_COMMANDS=Y
    endif

    ifeq ($(SUPER_CYCLE),Y)
        SUPER_CYCLE_COMMANDS=Y
    endif
    
    ifeq ($(FLASH),Y)
        FLASH_COMMANDS=Y
    endif
    
    ifeq ($(WM8731),Y)
        WM8731_COMMANDS=Y
    endif

    ifeq ($(DDS),Y)
        DDS_COMMANDS=Y
    endif

    ifeq ($(EXT_INT),Y)
        EXT_INT_COMMANDS=Y
    endif

    ifeq ($(FAT_FS),Y)
        FAT_FS_COMMANDS=Y
    endif

    ifeq ($(RTC),Y)
        RTC_COMMANDS=Y
    endif

    ifeq ($(FLASH_FS),Y)
        FLASH_FS_COMMANDS=Y
    endif
    
    ifeq ($(WAV),Y)
        WAV_COMMANDS=Y
    endif

    ifeq ($(INTERFACE),Y)
        INTERFACE_COMMANDS=Y
    endif

    ifeq ($(INTERFACES),Y)
        INTERFACES_COMMANDS=Y
    endif
    
    ifeq ($(DISK),Y)
        DISK_COMMANDS=Y
    endif

    ifeq ($(SOFTWARE_TIMER),Y)
        SOFTWARE_TIMER_COMMANDS=Y
    endif
    
    CORTEX_M4_COMMANDS=Y
    #FLASH_COMMANDS=Y
    
    ifeq ($(FLASH_FS),Y)
        FLASH_FS_COMMANDS=Y
    endif

    ifeq ($(SDIO),Y)
        SDIO_COMMANDS=Y
    endif

    ifeq ($(INTERFACE),Y)
        INTERFACE_COMMANDS=Y
    endif
    
    ifeq ($(I2C),Y)
        I2C_COMMANDS=Y
    endif
    
    ifeq ($(CORTEX_M4),Y)
        CORTEX_M4_COMMANDS=Y
    endif

    ifeq ($(NVIC),Y)
        NVIC_COMMANDS=Y
    endif

    ifeq ($(DMA),Y)
        DMA_COMMANDS=Y
    endif
    
    ifeq ($(MPU),Y)
        MPU_COMMANDS=Y
    endif
    
    ifeq ($(INTERRUPT),Y)
        INTERRUPT_COMMANDS=Y
    endif

    ifeq ($(SOUND_RECORDER),Y)
        SOUND_RECORDER_COMMANDS=Y
    endif


    ifeq ($(CONNECTIVITY),Y)
        CONNECTIVITY_COMMANDS=Y
    endif

    ifeq ($(I2S),Y)
        I2S_COMMANDS=Y
    endif

    ifeq ($(STORAGE),Y)
        STORAGE_COMMANDS=Y
    endif

    ifeq ($(GPIO),Y)
        GPIO_COMMANDS=Y
    endif
    
    ifeq ($(HEALTH_MONITOR),Y)
        HEALTH_MONITOR_COMMANDS=N
    endif
    
    BOOT_COMMANDS=Y
    
    ifeq ($(IWDG),Y)
        IWDG_COMMANDS=N
    endif
    
    SENSITIVITY_COMMANDS=Y
    ASICS_COMMANDS=Y
    SYSTICK_COMMANDS=Y

    ifeq ($(FLOAT),Y)
        FLOAT_COMMANDS=Y
    endif

    #INTERRUPT_COMMANDS=N

    ifeq ($(LED),Y)
        LED_COMMANDS=Y
    endif

    ifeq ($(SCHEDULER),Y)
        SCHEDULER_COMMANDS=Y
    endif

    ifeq ($(SPI),Y)
        SPI_COMMANDS=Y
    endif
    
    ifeq ($(LED_MONO),Y)
        LED_MONO_COMMANDS=Y
    endif

    ifeq ($(TIME),Y)
        TIME_COMMANDS=Y
    endif

    ifeq ($(COMPUTING),Y)
        COMPUTING_COMMANDS=Y
    endif

    ifeq ($(TIMER),Y)
        TIMER_COMMANDS=Y
    endif

    SUPER_CYCLE_COMMANDS=Y

    ifeq ($(LOG),Y)
        LOG_COMMANDS=Y
    endif
    
    SYSTICK_COMMANDS=Y
    
    ifeq ($(UNIT_TEST),Y)
        UNIT_TEST_COMMANDS=Y
    endif
    
    DEBUGGER_COMMANDS=Y

    ifeq ($(WATCHDOG),Y)
        WATCHDOG_COMMANDS=Y
    endif

    ifeq ($(WAV_PLAYER),Y)
        WAV_PLAYER_COMMANDS=Y
    endif
    
endif