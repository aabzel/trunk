
DIAG=Y
NUM_DIAG=Y
BIT_DIAG=Y

ifeq ($(MCAL),Y)
    MCAL_DIAG=Y
endif

ifeq ($(FLASH_FS),Y)
    FLASH_FS_DIAG=Y
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

    ifeq ($(DMA),Y)
        DMA_DIAG=Y
    endif

    ifeq ($(FILE_CLI),Y)
        FILE_CLI_DIAG=Y
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

ifeq ($(LITTLE_FS),Y)
    LITTLE_FS_DIAG=Y
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

ifeq ($(SPI),Y)
    SPI_DIAG=Y
endif

ifeq ($(ILI9341),Y)
    ILI9341_DIAG=Y
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

ifeq ($(UTF8_STR),Y)
    UTF8_STR_DIAG=Y
endif

ifeq ($(UART),Y)
    UART_DIAG=Y
endif

    ifeq ($(STORE_FS),Y)
        STORE_FS_DIAG=Y
    endif
    
    
ifeq ($(SPI),Y)
    SPI_DIAG=Y
endif

ifeq ($(M_SEQ),Y)
    M_SEQ_DIAG=Y
endif

ifeq ($(GPIO),Y)
    GPIO_DIAG=Y
endif