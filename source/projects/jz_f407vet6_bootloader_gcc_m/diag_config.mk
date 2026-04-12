
$(info Add Diag)

DIAG=Y
LOG_DIAG=Y
NUM_DIAG=Y
CORE_DIAG=Y
INTERVAL_DIAG=Y
INTERVAL_DIAG=Y

ifeq ($(BOOT),Y)
    BOOT_DIAG=Y
endif

ifeq ($(ARRAY),Y)
    ARRAY_DIAG=Y
endif


ifeq ($(RATIONAL_NUM),Y)
    RATIONAL_NUM_DIAG=Y
endif

ifeq ($(CLI),Y)
    CLI_DIAG=Y
endif



ifeq ($(BOOTLOADER),Y)
    BOOTLOADER_DIAG=Y
endif


ifeq ($(UART),Y)
    UART_DIAG=Y
endif

ifeq ($(FLOAT),Y)
    FLOAT_DIAG=Y
endif


ifeq ($(CLOCK),Y)
    CLOCK_DIAG=Y
endif

ifeq ($(SYSTEM),Y)
    SYSTEM_DIAG=Y
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


ifeq ($(INTERRUPT),Y)
    INTERRUPT_DIAG=Y
endif

ifeq ($(SW_COMPONENT),Y)
    SW_COMPONENT_DIAG=Y
endif

ifeq ($(SCHEDULER),Y)
    SCHEDULER_DIAG=Y
endif

ifeq ($(SYSTICK),Y)
    SYSTICK_DIAG=N
endif

ifeq ($(TIME),Y)
    TIME_DIAG=Y
endif

ifeq ($(PARAM),Y)
    PARAM_DIAG=Y
endif