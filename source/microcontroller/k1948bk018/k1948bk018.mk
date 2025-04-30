#protection against repeated include as in C preprocessor
$(info MCU_CUSTOM_MK_INC=$(MCU_CUSTOM_MK_INC) )
ifneq ($(MCU_CUSTOM_MK_INC),Y)
    MCU_CUSTOM_MK_INC=Y

    MCU_CUSTOM_DIR = $(MICROCONTROLLER_DIR)/k1948bk018
    #@echo $(error MCU_CUSTOM_DIR=$(MCU_CUSTOM_DIR))
    K1948BK018=Y
    MCU_OPEN_OCD_CONFIG=mik32.cfg
    
    OPT += -DHAS_K1948BK018
    #OPT += -DEFM_CTRL_WE_MASK
    SOURCES_ASM += $(MCU_CUSTOM_DIR)/crt0.S
        
    #FLOAT-ABI += -mfloat-abi=soft
    #MICROPROCESSOR = $(CPU)  $(FPU) $(FLOAT-ABI)
    
    FIRMWARE_TYPE_SELECTED=N

    #SOURCES_THIRD_PARTY_C += $(MCU_CUSTOM_DIR)/system_K1948BK018.c

    INCDIR += -I$(MCU_CUSTOM_DIR)

    ifeq ($(BOOTLOADER),Y)
        # link script
        FIRMWARE_TYPE_SELECTED=Y
        OPT += -DVECT_TAB_OFFSET=0x00000000
        LDSCRIPT = $(MCU_CUSTOM_DIR)/spifi.ld
    endif

    ifeq ($(BOOT),Y)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/boot_config.c
    endif

    ifeq ($(CLOCK),Y)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/clock_config.c
    endif

    ifeq ($(CLI),Y)
        OPT += -DHAS_K1948BK018_COMMANDS
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/mcu_custom_commands.c
    endif

    ifeq ($(DIAG),Y)
        SOURCES_THIRD_PARTY_C += $(MCU_CUSTOM_DIR)/k1948bk018_diag.c
    endif

    ifeq ($(EEPROM),Y)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/eeprom_config.c
    endif

    ifeq ($(GPIO),Y)
        SOURCES_THIRD_PARTY_C += $(MCU_CUSTOM_DIR)/k1948bk018.c
    endif

    ifeq ($(DMA),Y)
        $(info Config DMA)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/dma_config.c
    endif

    ifeq ($(FLASH),Y)
        # $(error FLASH=$(FLASH))
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/flash_config.c
    endif

    ifeq ($(FLASH_FS),Y)
        #@echo $(error FLASH_FS=$(FLASH_FS))
        $(info Add config FlashFs)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/flash_fs_config.c
    endif
    
    ifeq ($(INTERRUPT),Y)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/interrupt_config.c
    endif

    ifeq ($(MBR),Y)
        # $(error MBR=$(MBR))
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/mbr_config.c
    endif

    ifeq ($(POWER),Y)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/power_config.c
    endif

    ifeq ($(GENERIC),Y)
        # link script
        ifeq ($(GENERIC_MONOLITHIC),Y)
            #@echo $(error GENERIC_MONOLITHIC=$(GENERIC_MONOLITHIC))
            FIRMWARE_TYPE_SELECTED=Y
            OPT += -DHAS_GENERIC_MONOLITHIC
            #LDSCRIPT = $(MCU_CUSTOM_DIR)/eeprom.ld
        else
            FIRMWARE_TYPE_SELECTED=Y
        endif
        LDSCRIPT = $(MCU_CUSTOM_DIR)/spifi.ld
    endif

    ifeq ($(MBR),Y)
        BOOT_EEPROM=Y
        FIRMWARE_TYPE_SELECTED=Y
    endif

    ifeq ($(BOOT_EEPROM),Y)
        #@echo $(error BOOT_EEPROM=$(BOOT_EEPROM))
        LDSCRIPT = $(MCU_CUSTOM_DIR)/eeprom.ld
    endif
    
    ifeq ($(NVS),Y)
        $(info Add config NVS)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/nvs_config.c
    endif

    ifeq ($(PARAM),Y)
        $(info Config Param)
        #@echo $(error PARAM=$(PARAM))
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/param_config.c
    endif

    ifeq ($(WATCHDOG),Y)
        $(info Config WATCHDOG)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/watchdog_config.c
    endif

    MICROCONTROLLER_SELECTED=Y
endif
