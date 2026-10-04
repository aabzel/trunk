#protection against repeated include as in C preprocessor
ifneq ($(STM32F401RE_MK_INC),Y)
    STM32F401RE_MK_INC=Y

    MCU_CUSTOM_DIR = $(MICROCONTROLLER_DIR)/stm32f401re
    #  $(error MCU_CUSTOM_DIR= $(MCU_CUSTOM_DIR))

    MCAL_OPT += -DHAS_STM32
    MCAL_OPT += -DHAS_STM32F401RE
    MCAL_OPT += -DSTM32F401xx
    MCAL_OPT += -DSTM32F401x
    MCAL_OPT += -DSTM32F401RE
    MCAL_OPT += -DSTM32F401xE
    MCAL_OPT += -DSTM32F401Rx
    MCAL_OPT += -DHAS_STM32F401XE

    BOARD=Y
    CORTEX_M4=Y
    CMSIS=Y
    MICROCONTROLLER=Y
    STM32=Y
    STM32F401RE=Y
    STM32F4XX_HAL_DRIVER=Y

    INCDIR += -I$(MCU_CUSTOM_DIR)

    ifeq ($(BOOT),Y)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/boot_config.c
    endif

    ifeq ($(MBR),Y)
        # link script
        LDSCRIPT = $(MCU_CUSTOM_DIR)/gcc_arm_mbr.ld
    endif

    ifeq ($(BOOTLOADER),Y)
        # link script
        LDSCRIPT = $(MCU_CUSTOM_DIR)/gcc_arm_boot.ld
    endif

    ifeq ($(FLASH_FS),Y)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/flash_fs_config.c
    endif
    
    ifeq ($(INTERRUPT),Y)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/interrupt_config.c
    endif
    
    ifeq ($(FLASH),Y)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/flash_config.c
    endif

    SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/clock_config.c
    
    ifeq ($(NVS),Y)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/nvs_config.c
    endif
    
    ifeq ($(PARAM),Y)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/param_config.c
    endif
    
    ifeq ($(SDIO),Y)
        $(info Config SDIO)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/sdio_config.c
    endif
    
    ifeq ($(GENERIC),Y)
        # link script
        FIRMWARE_TYPE_SELECTED=Y
        ifeq ($(GENERIC_MONOLITHIC),Y)
            MCAL_OPT += -DVECT_TAB_OFFSET=0
            MCAL_OPT += -DAPP_START_ADDRESS=0x08000000
            $(info Generic Monilitic)
            LDSCRIPT = $(MCU_CUSTOM_DIR)/gcc_arm_generic_monolithic.ld
        else
            $(info Generic separate)
            MCAL_OPT += -DAPP_START_ADDRESS=0x08010000
            LDSCRIPT = $(MCU_CUSTOM_DIR)/gcc_arm_generic.ld
        endif
    endif
    # $(error LDSCRIPT=$(LDSCRIPT))

    ifeq ($(SYSTICK),Y)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/systick_config.c
    endif

    ifeq ($(SUPER_CYCLE),Y)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/super_cycle_config.c
    endif
    
    ifeq ($(SCHEDULER),Y)
        $(info Add config SCHEDULER)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/scheduler_config.c
    endif

    
    SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/stm32f401re.c
    
    SOURCES_THIRD_PARTY_C += $(MCU_CUSTOM_DIR)/system_stm32f4xx.c

    ifeq ($(STORE_FS),Y)
        #  $(error STORE_FS=$(STORE_FS))
        $(info Add config STORE_FS)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/storage_config.c
    endif
        
    SOURCES_ASM += $(MCU_CUSTOM_DIR)/startup_stm32f401xe.S
    MICROCONTROLLER_SELECTED=Y
endif