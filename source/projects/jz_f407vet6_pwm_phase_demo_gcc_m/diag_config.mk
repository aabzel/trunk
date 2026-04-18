
$(info Add Diag)

DIAG=Y

CONTROL_DIAG=Y
BIT_DIAG=Y
NUM_DIAG=Y

ifeq ($(LASER_SIGHT),Y)
    LASER_SIGHT_DIAG=Y
endif


ifeq ($(SEGGER_RTT),Y)
    SEGGER_RTT_DIAG=Y
endif

ifeq ($(CLI),Y)
    CLI_DIAG=Y
endif

ifeq ($(CAN_DIFF),Y)
    CAN_DIFF_DIAG=Y
endif

ifeq ($(DWT),Y)
    DWT_DIAG=Y
endif

ifeq ($(FLASH_FS),Y)
    FLASH_FS_DIAG=Y
endif


ifeq ($(USB_SERIAL),Y)
    USB_SERIAL_DIAG=Y
endif

ifeq ($(IQUEUE),Y)
    IQUEUE_DIAG=Y
endif

ifeq ($(BUTTON),Y)
    BUTTON_DIAG=Y
endif

ifeq ($(INTERVAL),Y)
    INTERVAL_DIAG=Y
endif

ifeq ($(CONNECTIVITY),Y)
    CONNECTIVITY_DIAG=Y
endif

ifeq ($(PWM),Y)
    PWM_DIAG=Y
endif

ifeq ($(CAN_TX_PLANNER),Y)
    CAN_TX_PLANNER_DIAG=Y
endif

ifeq ($(CAN_RX_HIST),Y)
    CAN_RX_HIST_DIAG=Y
endif


ifeq ($(LOG),Y)
    LOG_DIAG=Y
endif

ifeq ($(USB),Y)
    USB_DIAG=Y
endif

ifeq ($(PCAN),Y)
    PCAN_DIAG=Y
endif

ifeq ($(APPLICATIONS),Y)
    APPLICATIONS_DIAG=Y
endif

ifeq ($(USB_DEVICE),Y)
    USB_DEVICE_DIAG=Y
endif

ifeq ($(CORE),Y)
    CORE_DIAG=Y
endif

ifeq ($(ARRAY),Y)
    ARRAY_DIAG=Y
endif

ifeq ($(PLL_CALC),Y)
    PLL_CALC_DIAG=Y
endif


ifeq ($(FPU),Y)
    FPU_DIAG=Y
endif

ifeq ($(BOOTLOADER),Y)
    BOOTLOADER_DIAG=Y
endif

ifeq ($(CLOCK_OUT),Y)
    CLOCK_OUT_DIAG=Y
endif

ifeq ($(FLOAT),Y)
    FLOAT_DIAG=Y
endif


ifeq ($(CLOCK),Y)
    CLOCK_DIAG=Y
endif

ifeq ($(CAN),Y)
    CAN_DIAG=Y
endif

ifeq ($(SYSTEM),Y)
    SYSTEM_DIAG=Y
endif

ifeq ($(DMA),Y)
    DMA_DIAG=Y
endif





ifeq ($(INTERFACE),Y)
    INTERFACE_DIAG=Y
endif

ifeq ($(FLASH),Y)
    FLASH_DIAG=Y
endif

ifeq ($(SUPER_CYCLE),Y)
    SUPER_CYCLE_DIAG=Y
endif


ifeq ($(MEMORY),Y)
    MEMORY_DIAG=Y
endif


ifeq ($(INTERRUPT),Y)
    INTERRUPT_DIAG=Y
endif

ifeq ($(SW_COMPONENT),Y)
    SW_COMPONENT_DIAG=Y
endif

ifeq ($(EXT_INT),Y)
    EXT_INT_DIAG=Y
endif

ifeq ($(GPIO),Y)
    GPIO_DIAG=Y
endif

ifeq ($(SCHEDULER),Y)
    SCHEDULER_DIAG=Y
endif

ifeq ($(SYSTICK),Y)
    SYSTICK_DIAG=Y
endif

ifeq ($(STRING_PARSER),Y)
    STRING_PARSER_DIAG=Y
endif


ifeq ($(LED_MONO),Y)
    LED_MONO_DIAG=Y
endif

ifeq ($(MPU),Y)
    MPU_DIAG=Y
endif

ifeq ($(NVIC),Y)
    NVIC_DIAG=Y
endif
ifeq ($(CORTEX_M4),Y)
    CORTEX_M4_DIAG=Y
endif
ifeq ($(POSTPONE_FUN),Y)
    POSTPONE_FUN_DIAG=Y
endif

ifeq ($(TIME),Y)
    TIME_DIAG=Y
endif

ifeq ($(VOLTAGE_DIVIDER),Y)
    VOLTAGE_DIVIDER_DIAG=Y
endif

ifeq ($(ISO_TP),Y)
    ISO_TP_DIAG=Y
endif

ifeq ($(UDS),Y)
    UDS_DIAG=Y
endif

ifeq ($(PROTOCOL),Y)
    PROTOCOL_DIAG=Y
endif

ifeq ($(PARAM),Y)
    PARAM_DIAG=Y
endif

ifeq ($(RATIONAL_NUM),Y)
    RATIONAL_NUM_DIAG=Y
endif

ifeq ($(DMA_CHANNEL),Y)
    DMA_CHANNEL_DIAG=Y
endif

ifeq ($(LIMITER),Y)
    LIMITER_DIAG=Y
endif


ifeq ($(TIMER),Y)
    TIMER_DIAG=Y
endif

ifeq ($(NVS),Y)
    NVS_DIAG=Y
endif

ifeq ($(LED),Y)
    LED_DIAG=Y
endif

ifeq ($(TBFP),Y)
    TBFP_DIAG=Y
endif

ifeq ($(STORE_FS),Y)
    STORE_FS_DIAG=Y
endif

ifeq ($(SOFTWARE_TIMER),Y)
    SOFTWARE_TIMER_DIAG=Y
endif
    
ifeq ($(STRING_READER),Y)
    STRING_READER_DIAG=Y
endif

ifeq ($(UART),Y)
    UART_DIAG=Y
endif

ifeq ($(WATCHDOG),Y)
    WATCHDOG_DIAG=Y
endif