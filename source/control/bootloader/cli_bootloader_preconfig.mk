$(info CLI_BOOTLOADER_MK_INC=$(CLI_BOOTLOADER_MK_INC) )
ifneq ($(CLI_BOOTLOADER_MK_INC),Y)
    CLI_BOOTLOADER_MK_INC=Y

    # $(error CLI_BOOTLOADER=$(CLI_BOOTLOADER))
        
    BOOT_COMMANDS=Y
    BOOTLOADER_COMMANDS=Y
    CONTROL_COMMANDS=Y
    PROTOCOLS_COMMANDS=Y
    BIT_UTILS=Y
    CLI=Y
    CLI_NATIVE_COMMANDS=Y

    ifeq ($(CLOCK),Y)
        CLOCK_COMMANDS=N
    endif
    
    ifeq ($(LOG),Y)
        LOG_COMMANDS=Y
    endif
    
    ifeq ($(PARAM),Y)
        PARAM_COMMANDS=Y
    endif
    
    ifeq ($(FLASH),Y)
        FLASH_COMMANDS=Y
    endif

    ifeq ($(FLASH_FS),Y)
        #Need for flash_fs formating
        FLASH_FS_COMMANDS=Y
    endif

    ifeq ($(STORAGE),Y)
        STORAGE_COMMANDS=Y
    endif

    ifeq ($(CONNECTIVITY),Y)
        CONNECTIVITY_COMMANDS=Y
    endif
endif
