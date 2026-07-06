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
    
    ifeq ($(CLOCK),Y)
        CLOCK_COMMANDS=Y
    endif

    ifeq ($(SMOOTH_LAMP),Y)
        SMOOTH_LAMP_COMMANDS=Y
    endif

    ifeq ($(PWM),Y)
        PWM_COMMANDS=Y
    endif

    ifeq ($(GAME_PAD_PS2),Y)
        GAME_PAD_PS2_COMMANDS=Y
    endif
    
    ifeq ($(FLASH),Y)
        FLASH_COMMANDS=Y
    endif
    
    ifeq ($(IR_RECEIVER),Y)
        IR_RECEIVER_COMMANDS=Y
    endif

    ifeq ($(RC_CAR),Y)
        RC_CAR_COMMANDS=Y
    endif

    ifeq ($(DRV8870),Y)
        DRV8870_COMMANDS=Y
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
    
    ifeq ($(IR_SAMSUNG),Y)
        IR_SAMSUNG_COMMANDS=Y
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
    


    ifeq ($(CONNECTIVITY),Y)
        CONNECTIVITY_COMMANDS=Y
    endif

    ifeq ($(SCHMITT_TRIGGER),Y)
        SCHMITT_TRIGGER_COMMANDS=Y
    endif
    
    ifeq ($(MIC2026),Y)
        MIC2026_COMMANDS=N
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

    ifeq ($(TIMER),Y)
        TIMER_COMMANDS=Y
    endif
    SUPER_CYCLE_COMMANDS=Y

    ifeq ($(LOG),Y)
        LOG_COMMANDS=Y
    endif
    
    #PARAM_COMMANDS=N
    SYSTICK_COMMANDS=Y
    #SYSTICK_COMMANDS=N
    
    #TIMER_COMMANDS=N
    ifeq ($(UNIT_TEST),Y)
        UNIT_TEST_COMMANDS=Y
    endif
    DEBUGGER_COMMANDS=Y
    ifeq ($(WATCHDOG),Y)
        WATCHDOG_COMMANDS=Y
    endif
    
endif