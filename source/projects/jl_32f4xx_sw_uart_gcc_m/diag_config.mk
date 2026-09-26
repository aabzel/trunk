
DIAG=Y
NUM_DIAG=Y
BIT_DIAG=Y

ifeq ($(MCAL),Y)
    MCAL_DIAG=Y
endif

ifeq ($(BUTTON),Y)
    BUTTON_DIAG=Y
endif

ifeq ($(FLOAT),Y)
    FLOAT_DIAG=Y
endif

ifeq ($(MATH),Y)
    MATH_DIAG=Y
endif

ifeq ($(EXT_INT),Y)
    EXT_INT_DIAG=Y
endif

ifeq ($(ASICS),Y)
    ASICS_DIAG=Y
endif

ifeq ($(CLOCK),Y)
    CLOCK_DIAG=Y
endif

ifeq ($(DMA_CHANNEL),Y)
    DMA_CHANNEL_DIAG=Y
endif

ifeq ($(ARRAY),Y)
    ARRAY_DIAG=Y
endif

    ifeq ($(BIN_DAC),Y)
        BIN_DAC_DIAG=Y
    endif

    ifeq ($(DMA),Y)
        DMA_DIAG=Y
    endif

    ifeq ($(FILE_CLI),Y)
        FILE_CLI_DIAG=Y
    endif
    
    ifeq ($(BIN_ADC),Y)
        BIN_ADC_DIAG=Y
    endif

ifeq ($(BIT_FIFO),Y)
    BIT_FIFO_DIAG=Y
endif

    ifeq ($(RUNNING_LINE),Y)
        RUNNING_LINE_DIAG=Y
    endif

    ifeq ($(INTERFACE),Y)
        INTERFACE_DIAG=Y
    endif

    ifeq ($(DISK),Y)
        DISK_DIAG=Y
    endif

    ifeq ($(PROBING_PULSE),Y)
        PROBING_PULSE_DIAG=Y
    endif

    ifeq ($(CORTEX_M4),Y)
        CORTEX_M4_DIAG=Y
    endif

ifeq ($(BOOT),Y)
    BOOT_DIAG=Y
endif

    ifeq ($(MPU),Y)
        MPU_DIAG=Y
    endif

    ifeq ($(CORE),Y)
        CORE_DIAG=Y
    endif

ifeq ($(DDS),Y)
    DDS_DIAG=Y
endif

ifeq ($(TIME),Y)
    TIME_DIAG=Y
endif


ifeq ($(RTC),Y)
        RTC_DIAG=Y
endif

ifeq ($(GPIO),Y)
    GPIO_DIAG=Y
endif

    ifeq ($(SYSTICK),Y)
        SYSTICK_DIAG=Y
    endif
    
    ifeq ($(LED),Y)
        LED_DIAG=Y
    endif
    
ifeq ($(SYSTEM),Y)
    SYSTEM_DIAG=Y
endif

ifeq ($(NVIC),Y)
    NVIC_DIAG=Y
endif

ifeq ($(NVS),Y)
    NVS_DIAG=Y
endif

    ifeq ($(LED_MONO),Y)
        LED_MONO_DIAG=Y
    endif
    
    ifeq ($(BIT_FIFO),Y)
        BIT_FIFO_DIAG=Y
    endif

ifeq ($(FLASH),Y)
    FLASH_DIAG=Y
endif
    
    ifeq ($(INTERRUPT),Y)
        INTERRUPT_DIAG=Y
    endif
    
    ifeq ($(INTERVAL),Y)
        INTERVAL_DIAG=Y
    endif
    
    ifeq ($(FILE_MCAL),Y)
        FILE_MCAL_DIAG=Y
    endif
    
    ifeq ($(FAT_FS),Y)
        FAT_FS_DIAG=Y
    endif

ifeq ($(SDIO),Y)
    SDIO_DIAG=Y
endif

ifeq ($(AUDIO),Y)
    AUDIO_DIAG=Y
endif

ifeq ($(LOOPBACK_AUDIO),Y)
    LOOPBACK_AUDIO_DIAG=Y
endif

ifeq ($(SOFTWARE_TIMER),Y)
    SOFTWARE_TIMER_DIAG=Y
endif

ifeq ($(TIMER),Y)
    TIMER_DIAG=Y
endif

ifeq ($(SUPER_CYCLE),Y)
    SUPER_CYCLE_DIAG=Y
endif

ifeq ($(EXT_INT),Y)
    EXT_INT_DIAG=Y
endif

    ifeq ($(SCHEDULER),Y)
        SCHEDULER_DIAG=Y
    endif
    
ifeq ($(WAV),Y)
    WAV_DIAG=Y
endif

ifeq ($(POSTPONE_FUN),Y)
    POSTPONE_FUN_DIAG=Y
endif

ifeq ($(SW_UART),Y)
    SW_UART_DIAG=Y
endif


ifeq ($(BIN_DAC),Y)
    BIN_DAC_DIAG=Y
endif

 

ifeq ($(JUMPER_CODE),Y)
    JUMPER_CODE_DIAG=Y
endif


ifeq ($(UART),Y)
    UART_DIAG=Y
endif

    ifeq ($(SONAR),Y)
        SONAR_DIAG=Y
    endif
    
    
ifeq ($(SPI),Y)
    SPI_DIAG=Y
endif

ifeq ($(M_SEQ),Y)
    M_SEQ_DIAG=Y
endif

ifeq ($(WAV_PLAYER),Y)
    WAV_PLAYER_DIAG=Y
endif