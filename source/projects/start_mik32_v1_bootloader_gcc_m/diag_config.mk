
$(info Add Diag)

DIAG=Y
LOG_DIAG=Y
FLASH_DIAG=Y
SYSTEM_DIAG=Y
PARAM_DIAG=Y
BOOTLOADER_DIAG=Y
    ifeq ($(UART),Y)
        UART_DIAG=Y
    endif
    ifeq ($(ARRAY),Y)
        ARRAY_DIAG=Y
    endif
    ifeq ($(ASICS),Y)
        ASICS_DIAG=Y
    endif
    ifeq ($(COMPUTING),Y)
        COMPUTING_DIAG=Y
    endif
    ifeq ($(FLASH_FS),Y)
        FLASH_FS_DIAG=Y
    endif
    ifeq ($(FLASH),Y)
        FLASH_DIAG=Y
    endif
    ifeq ($(LED_MONO),Y)
        LED_MONO_DIAG=N
    endif
    ifeq ($(GPIO),Y)
        GPIO_DIAG=Y
    endif
    ifeq ($(LED),Y)
        LED_DIAG=Y
    endif
    ifeq ($(NVS),Y)
        NVS_DIAG=Y
    endif
    ifeq ($(SUPER_CYCLE),Y)
        SUPER_CYCLE_DIAG=N
    endif

    ifeq ($(PARAM),Y)
        PARAM_DIAG=Y
    endif
    ifeq ($(TIME),Y)
        TIME_DIAG=Y
    endif
    ifeq ($(SPI),Y)
        SPI_DIAG=N
    endif
    ifeq ($(SYSTEM),Y)
        SYSTEM_DIAG=Y
    endif