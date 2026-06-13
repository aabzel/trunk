
$(info Add Diag)

DIAG=Y
LOG_DIAG=Y
BOOTLOADER_DIAG=Y

    ifeq ($(DEBUGGER),Y)
        DEBUGGER_DIAG=Y
    endif

    ifeq ($(FLOAT),Y)
        FLOAT_DIAG=Y
    endif

    ifeq ($(INTERRUPT),Y)
        INTERRUPT_DIAG=Y
    endif
    
    ifeq ($(UART),Y)
        UART_DIAG=Y
    endif

    ifeq ($(EEPROM),Y)
        EEPROM_DIAG=Y
    endif

    ifeq ($(SPIFI),Y)
        SPIFI_DIAG=Y
    endif

    ifeq ($(W25Q32JV),Y)
        W25Q32JV_DIAG=Y
    endif
 
    ifeq ($(NOR_FLASH),Y)
        NOR_FLASH_DIAG=Y
    endif
 
    ifeq ($(SCR1_TIMER),Y)
        SCR1_TIMER_DIAG=Y
    endif

    ifeq ($(BOOT_MANAGER),Y)
        BOOT_MANAGER_DIAG=Y
    endif

    ifeq ($(BOOT),Y)
        BOOT_DIAG=Y
    endif

    ifeq ($(RV32IMC),Y)
        RV32IMC_DIAG=Y
    endif

    ifeq ($(ARRAY),Y)
        ARRAY_DIAG=Y
    endif
    
    ifeq ($(ASICS),Y)
        ASICS_DIAG=Y
    endif
    
    ifeq ($(BUTTON),Y)
        BUTTON_DIAG=Y
    endif
    
    ifeq ($(COMPUTING),Y)
        COMPUTING_DIAG=Y
    endif
    
    ifeq ($(FIR),Y)
        FIR_DIAG=Y
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
    
    ifeq ($(LOAD_DETECT),Y)
        LOAD_DETECT_DIAG=N
    endif
    
    ifeq ($(GPIO),Y)
        GPIO_DIAG=Y
    endif
    
    ifeq ($(LED),Y)
        LED_DIAG=Y
    endif
    
    ifeq ($(I2C),Y)
        I2C_DIAG=Y
    endif

    ifeq ($(NVS),Y)
        NVS_DIAG=Y
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
    
    ifeq ($(TIMER),Y)
        TIMER_DIAG=N
    endif
    
    ifeq ($(SPI),Y)
        SPI_DIAG=N
    endif
    
    ifeq ($(SSD1306),Y)
        SSD1306_DIAG=Y
    endif
    
    ifeq ($(SYSTEM),Y)
        SYSTEM_DIAG=Y
    endif