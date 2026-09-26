$(info CLI_CONFIG_MK_INC=$(CLI_CONFIG_MK_INC) )
ifneq ($(CLI_CONFIG_MK_INC),Y)
    CLI_CONFIG_MK_INC=Y
    CLI=Y
    CLI_CMD_HISTORY=Y
    CLI_NATIVE_COMMANDS=Y

    ifeq ($(APPLICATIONS),Y)
        APPLICATIONS_COMMANDS=Y
    endif

    ifeq ($(BUTTON),Y)
        BUTTON_COMMANDS=Y
    endif

    ifeq ($(BIN_ADC_FULL_DUPLEX),Y)
        BIN_ADC_FULL_DUPLEX_COMMANDS=Y
    endif

    ifeq ($(INCREMENTAL_ENCODER),Y)
        INCREMENTAL_ENCODER_COMMANDS=Y
    endif

    ifeq ($(REC_PLAY),Y)
        REC_PLAY_COMMANDS=Y
    endif

    ifeq ($(CORE),Y)
        CORE_COMMANDS=Y
    endif
    
    ifeq ($(FILE_MCAL),Y)
        FILE_MCAL_COMMANDS=Y
    endif
    
    ifeq ($(MATH),Y)
        MATH_COMMANDS=N
    endif
    
    ifeq ($(CLOCK),Y)
        CLOCK_COMMANDS=Y
    endif

    ifeq ($(UART),Y)
        UART_COMMANDS=Y
    endif
    
    ifeq ($(DMA_CHANNEL),Y)
        DMA_CHANNEL_COMMANDS=Y
    endif

    ifeq ($(CORTEX_M4),Y)
        CORTEX_M4_COMMANDS=Y
    endif

    ifeq ($(DEBUGGER),Y)
        DEBUGGER_COMMANDS=Y
    endif
    
    ifeq ($(RUNNING_LINE),Y)
        RUNNING_LINE_COMMANDS=Y
    endif

    ifeq ($(SUPER_CYCLE),Y)
        SUPER_CYCLE_COMMANDS=Y
    endif
    
    ifeq ($(FLASH),Y)
        FLASH_COMMANDS=Y
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


    ifeq ($(FLASH_FS),Y)
        FLASH_FS_COMMANDS=Y
    endif

    ifeq ($(SDIO),Y)
        SDIO_COMMANDS=N
    endif

    ifeq ($(INTERFACE),Y)
        INTERFACE_COMMANDS=Y
    endif
    
    ifeq ($(BIT_FIFO),Y)
        BIT_FIFO_COMMANDS=Y
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


    ifeq ($(INTERRUPT),Y)
        INTERRUPT_COMMANDS=Y
    endif

    ifeq ($(SW_UART),Y)
        SW_UART_COMMANDS=Y
    endif


    ifeq ($(CONNECTIVITY),Y)
        CONNECTIVITY_COMMANDS=Y
    endif
    
    ifeq ($(BIT_FIFO),Y)
        BIT_FIFO_COMMANDS=Y
    endif

    ifeq ($(SCHMITT_TRIGGER),Y)
        SCHMITT_TRIGGER_COMMANDS=Y
    endif
    
    ifeq ($(BIT_FIFO),Y)
        BIT_FIFO_COMMANDS=Y
    endif

    ifeq ($(FILE_CLI),Y)
        FILE_CLI_COMMANDS=Y
    endif

    ifeq ($(BIN_ADC),Y)
        BIN_ADC_COMMANDS=Y
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

    ifeq ($(UART),Y)
        UART_COMMANDS=Y
    endif

    ifeq ($(IWDG),Y)
        IWDG_COMMANDS=N
    endif
    
    SENSITIVITY_COMMANDS=Y

    ASICS_COMMANDS=Y

    ifeq ($(BIN_DAC),Y)
        BIN_DAC_COMMANDS=Y
    endif

    ifeq ($(FLOAT),Y)
        FLOAT_COMMANDS=Y
    endif

    #INTERRUPT_COMMANDS=N

    ifeq ($(LOOPBACK_AUDIO),Y)
        LOOPBACK_AUDIO_COMMANDS=Y
    endif

    ifeq ($(JUMPER_CODE),Y)
        JUMPER_CODE_COMMANDS=Y
    endif
    
    ifeq ($(LED),Y)
        LED_COMMANDS=Y
    endif

    ifeq ($(SCHEDULER),Y)
        SCHEDULER_COMMANDS=Y
    endif
    
    ifeq ($(SDIO),Y)
        SDIO_COMMANDS=Y
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

    ifeq ($(BIT_FIFO),Y)
        BIT_FIFO_COMMANDS=Y
    endif

    ifeq ($(SONAR),Y)
        SONAR_COMMANDS=Y
    endif


    ifeq ($(TIMER),Y)
        TIMER_COMMANDS=Y
    endif

    ifeq ($(SUPER_CYCLE),Y)
        SUPER_CYCLE_COMMANDS=Y
    endif

    ifeq ($(LOG),Y)
        LOG_COMMANDS=Y
    endif

    ifeq ($(SYSTICK),Y)
        SYSTICK_COMMANDS=Y
    endif

    ifeq ($(UNIT_TEST),Y)
        UNIT_TEST_COMMANDS=Y
    endif

    ifeq ($(WAV),Y)
        WAV_COMMANDS=Y
    endif
    
    ifeq ($(WATCHDOG),Y)
        WATCHDOG_COMMANDS=Y
    endif

    ifeq ($(WAV_PLAYER),Y)
        WAV_PLAYER_COMMANDS=Y
    endif
    
endif