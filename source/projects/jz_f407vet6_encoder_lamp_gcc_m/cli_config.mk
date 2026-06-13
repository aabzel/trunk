$(info CLI_CONFIG_MK_INC=$(CLI_CONFIG_MK_INC) )
ifneq ($(CLI_CONFIG_MK_INC),Y)
    CLI_CONFIG_MK_INC=Y

    #BOOT_COMMANDS=Y
    CLI=Y
    CLI_CMD_HISTORY=Y
    CLI_NATIVE_COMMANDS=Y

    BIT_COMMANDS=Y
    INTERFACES_COMMANDS=Y

    ifeq ($(DWT),Y)
        DWT_COMMANDS=Y
    endif

    ifeq ($(STORE_FS),Y)
        STORE_FS_COMMANDS=Y
    endif

    ifeq ($(DRV8870),Y)
        DRV8870_COMMANDS=Y
    endif
    
    ifeq ($(SLIDING_INTEGRAL),Y)
        SLIDING_INTEGRAL_COMMANDS=Y
    endif

    ifeq ($(STORE_FS),Y)
        STORE_FS_COMMANDS=Y
    endif

    ifeq ($(RATIONAL_NUM),Y)
        RATIONAL_NUM_COMMANDS=Y
    endif

    ifeq ($(SMOOTH_LAMP),Y)
        SMOOTH_LAMP_COMMANDS=Y
    endif
    
 
    
    ifeq ($(IQUEUE),Y)
        IQUEUE_COMMANDS=Y
    endif

    ifeq ($(PWM),Y)
        PWM_COMMANDS=Y
    endif

    ifeq ($(CORE),Y)
        CORE_COMMANDS=Y
    endif
 

    ifeq ($(XPRINTF),Y)
        XPRINTF_COMMANDS=Y
    endif

    ifeq ($(IR_RECEIVER),Y)
        IR_RECEIVER_COMMANDS=Y
    endif

    ifeq ($(CLI),Y)
        CLI_COMMANDS=Y
    endif

    ifeq ($(SYSTEM),Y)
        SYSTEM_COMMANDS=Y
    endif


    ifeq ($(DRV8870),Y)
        DRV8870_COMMANDS=Y
    endif
    
    ifeq ($(DSP),Y)
        DSP_COMMANDS=Y
    endif

    ifeq ($(INCREMENTAL_ENCODER),Y)
        INCREMENTAL_ENCODER_COMMANDS=Y
    endif

    ifeq ($(CAN_TX_PLANNER),Y)
        CAN_TX_PLANNER_COMMANDS=Y
    endif
    
    ifeq ($(CLOCK),Y)
        CLOCK_COMMANDS=Y
    endif
   
    ifeq ($(PWM),Y)
        PWM_COMMANDS=Y
    endif
    
    ifeq ($(APPLICATIONS),Y)
        APPLICATIONS_COMMANDS=Y
    endif

    ifeq ($(ENCODER_LAMP),Y)
        ENCODER_LAMP_COMMANDS=Y
    endif

    ifeq ($(PLL_CALC),Y)
        PLL_CALC_COMMANDS=Y
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

    ifeq ($(FPU),Y)
        FPU_COMMANDS=Y
    endif

    ifeq ($(MEMORY),Y)
        MEMORY_COMMANDS=Y
    endif

    ifeq ($(ASICS),Y)
        ASICS_COMMANDS=Y
    endif

    ifeq ($(CLOCK_OUT),Y)
        CLOCK_OUT_COMMANDS=Y
    endif
    
    ifeq ($(INTERFACE),Y)
        INTERFACE_COMMANDS=Y
    endif

    ifeq ($(DELTA_SIGMA),Y)
        DELTA_SIGMA_COMMANDS=Y
    endif

    ifeq ($(SW_COMPONENT),Y)
        SW_COMPONENT_COMMANDS=Y
    endif
    
    ifeq ($(SOFTWARE_TIMER),Y)
        SOFTWARE_TIMER_COMMANDS=Y
    endif
    
    ifeq ($(CORTEX_M4),Y)
        CORTEX_M4_COMMANDS=Y
    endif

    ifeq ($(TIME),Y)
        TIME_COMMANDS=Y
    endif

    #FLASH_COMMANDS=Y

    ifeq ($(FLASH_FS),Y)
        FLASH_FS_COMMANDS=Y
    endif

    ifeq ($(LITTLE_FS),Y)
        LITTLE_FS_COMMANDS=Y
    endif

    ifeq ($(BOARD),Y)
        BOARD_COMMANDS=Y
    endif

    ifeq ($(INTERFACE),Y)
        INTERFACE_COMMANDS=Y
    endif
    
    ifeq ($(BUTTON),Y)
        BUTTON_COMMANDS=Y
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

    ifeq ($(BICYCLE_HEADLAMP),Y)
        BICYCLE_HEADLAMP_COMMANDS=Y
    endif

    ifeq ($(ADC),Y)
        ADC_COMMANDS=Y
    endif

    ifeq ($(ADC_CHANNEL),Y)
        ADC_CHANNEL_COMMANDS=Y
    endif

    ifeq ($(FLASH),Y)
        FLASH_COMMANDS=Y
    endif

    ifeq ($(MPU),Y)
        MPU_COMMANDS=Y
    endif

    ifeq ($(INTERRUPT),Y)
        INTERRUPT_COMMANDS=Y
    endif

    ifeq ($(GPIO),Y)
        GPIO_COMMANDS=Y
    endif

    ifeq ($(INTERRUPT),Y)
       INTERRUPT_COMMANDS=Y
    endif

    ifeq ($(SDIO),Y)
        SDIO_COMMANDS=Y
    endif
    
    ifeq ($(LED),Y)
        LED_COMMANDS=Y
    endif
    
    ifeq ($(HEALTH_MONITOR),Y)
        HEALTH_MONITOR_COMMANDS=Y
    endif
    
    ifeq ($(COMPUTING),Y)
        COMPUTING_COMMANDS=Y
    endif
    
    ifeq ($(CAN),Y)
        CAN_COMMANDS=Y
    endif
    
    ifeq ($(PROTOCOLS),Y)
        PROTOCOLS_COMMANDS=Y
    endif

    ifeq ($(CONNECTIVITY),Y)
        CONNECTIVITY_COMMANDS=Y
    endif

    ifeq ($(ENCODER_LAMP),Y)
        ENCODER_LAMP_COMMANDS=Y
    endif
    
    ifeq ($(SCHMITT_TRIGGER),Y)
        SCHMITT_TRIGGER_COMMANDS=Y
    endif

    ifeq ($(NVS),Y)
        NVS_COMMANDS=Y
    endif

    ifeq ($(MPU),Y)
        MPU_COMMANDS=Y
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

    ifeq ($(BOOT),Y)
        BOOT_COMMANDS=Y
    endif
    
    ifeq ($(DAC),Y)
        DAC_COMMANDS=Y
    endif
    
    ifeq ($(IWDG),Y)
        IWDG_COMMANDS=Y
    endif
    
    SENSITIVITY_COMMANDS=Y

    ASICS_COMMANDS=Y

    ifeq ($(STRING_READER),Y)
        STRING_READER_COMMANDS=Y
    endif

    ifeq ($(POSTPONE_FUN),Y)
        POSTPONE_FUN_COMMANDS=Y
    endif
    
    ifeq ($(DDS),Y)
        DDS_COMMANDS=Y
    endif
    
    ifeq ($(DELTA_SIGMA),Y)
        DELTA_SIGMA_COMMANDS=Y
    endif

    ifeq ($(IIR),Y)
        IIR_COMMANDS=Y
    endif

    ifeq ($(FLOAT),Y)
        FLOAT_COMMANDS=Y
    endif

    ifeq ($(INTERRUPT),Y)
        INTERRUPT_COMMANDS=Y
    endif

    ifeq ($(SUPER_CYCLE),Y)
        SUPER_CYCLE_COMMANDS=Y
    endif

    ifeq ($(LED),Y)
        LED_COMMANDS=Y
    endif

    ifeq ($(SCHEDULER),Y)
        SCHEDULER_COMMANDS=Y
    endif

    ifeq ($(LED_MONO),Y)
        LED_MONO_COMMANDS=Y
    endif

    ifeq ($(TBFP),Y)
        TBFP_COMMANDS=Y
    endif
    
    ifeq ($(TIMER),Y)
        TIMER_COMMANDS=Y
    endif

    ifeq ($(LOG),Y)
        LOG_COMMANDS=Y
    endif
    #PARAM_COMMANDS=N
    #STM32_SYSTICK_COMMANDS=N

    ifeq ($(SYSTICK),Y)
        SYSTICK_COMMANDS=Y
    endif

    #TIMER_COMMANDS=N

    ifeq ($(UART),Y)
        UART_COMMANDS=Y
    endif

    ifeq ($(SEGGER_RTT),Y)
        SEGGER_RTT_COMMANDS=Y
    endif

    ifeq ($(DAC_CHANNEL),Y)
        DAC_CHANNEL_COMMANDS=Y
    endif


    ifeq ($(DMA_CHANNEL),Y)
        DMA_CHANNEL_COMMANDS=Y
    endif

    ifeq ($(DEBUGGER),Y)
        DEBUGGER_COMMANDS=Y
    endif

    ifeq ($(SENSITIVITY),Y)
        SENSITIVITY_COMMANDS=Y
    endif
    
    ifeq ($(UNIT_TEST),Y)
        UNIT_TEST_COMMANDS=Y
    endif
    
    ifeq ($(WATCHDOG),Y)
        WATCHDOG_COMMANDS=Y
    endif
endif