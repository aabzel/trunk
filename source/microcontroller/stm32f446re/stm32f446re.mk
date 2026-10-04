#protection against repeated include as in C preprocessor
ifneq ($(STM32F446RE_MK_INC),Y)
    STM32F446RE_MK_INC=Y

    MCU_CUSTOM_DIR = $(MICROCONTROLLER_DIR)/stm32f446re
    # $(error MCU_CUSTOM_DIR= $(MCU_CUSTOM_DIR))
    # $(error MCU_CUSTOM_DIR=$(MCU_CUSTOM_DIR))
    # $(error CFLAGS=$(CFLAGS))
    MCAL_OPT += -DHAS_STM32
    MCAL_OPT += -DHAS_STM32F446RE
    MCAL_OPT += -DSTM32F446xx
    MCAL_OPT += -DSTM32F446RE
    MCAL_OPT += -DSTM32F446xE
    MCAL_OPT += -DSTM32F446Rx

    BOARD=Y
    CORTEX_M4=Y
    CMSIS=Y
    MICROCONTROLLER=Y
    STM32=Y
    STM32F446RE=Y
    STM32F4XX_HAL_DRIVER=Y

    INCDIR += -I$(MCU_CUSTOM_DIR)

    ifeq ($(BOOT),Y)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/boot_config.c
    endif


    ifeq ($(MBR),Y)
        # link script
        LDSCRIPT = $(MCU_CUSTOM_DIR)/gcc_arm_mbr.ld
    endif

    ifeq ($(DAC),Y)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/dac_config.c
    endif
    
    ifeq ($(DAC_CHANNEL),Y)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/dac_channel_config.c
    endif
    
    ifeq ($(DMA),Y)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/dma_config.c
    endif

    ifeq ($(DMA_CHANNEL),Y)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/dma_channel_config.c
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/dma_channel_config_memcpy.c

        ifeq ($(ADC),Y)
            SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/dma_channel_config_adc.c
        endif
    endif
    
    ifeq ($(PIN),Y)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/pin_config.c
    endif
    
    ifeq ($(CLOCK),Y)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/clock_config.c
    endif

    ifeq ($(BOOTLOADER),Y)
        # link script
        FIRMWARE_TYPE_SELECTED=Y
        MCAL_OPT += -DAPP_START_ADDRESS=0x08010000
        ifeq ($(BOOTLOADER_MONOLITHIC),Y)
            MCAL_OPT +=-DBOOT_START_ADDRESS=0x08000000
            LDSCRIPT = $(MCU_CUSTOM_DIR)/gcc_arm_bootloader_monolithic.ld
        else
            MCAL_OPT +=-DBOOT_START_ADDRESS=0x08060000
            LDSCRIPT = $(MCU_CUSTOM_DIR)/gcc_arm_boot.ld
        endif
    endif
    
    ifeq ($(GENERIC),Y)
        # link script
        LDSCRIPT = $(MCU_CUSTOM_DIR)/gcc_arm_generic.ld
    endif

    ifeq ($(GENERIC),Y)
        # link script
        FIRMWARE_TYPE_SELECTED=Y
        ifeq ($(GENERIC_MONOLITHIC),Y)
            MCAL_OPT +=-DBOOT_START_ADDRESS=0x08000000
            MCAL_OPT += -DAPP_START_ADDRESS=0x08000000
            LDSCRIPT = $(MCU_CUSTOM_DIR)/gcc_arm_generic_monolithic.ld
        else
            MCAL_OPT += -DAPP_START_ADDRESS=0x08010000
            MCAL_OPT +=-DBOOT_START_ADDRESS=0x08060000
            LDSCRIPT = $(MCU_CUSTOM_DIR)/gcc_arm_generic.ld
        endif
    endif

    MCAL_OPT += -DHAS_LINKER_INFO
    ifeq ($(MBR),Y)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/mbr_config.c
        FIRMWARE_TYPE_SELECTED=Y
        MCAL_OPT +=-DBOOT_START_ADDRESS=0x08000000
        MCAL_OPT +=-DAPP_START_ADDRESS=0x08000000
        ifeq ($(MBR_ADVANCED),Y)
            #LDSCRIPT = $(MCU_CUSTOM_DIR)/gcc_arm_mbr_advanced.ld
            LDSCRIPT = $(MCU_CUSTOM_DIR)/stm32f407xx_flash.icf
        else
            #$(error MBR=$(MBR))
            ifeq ($(GCC),Y)
                LDSCRIPT = $(MCU_CUSTOM_DIR)/gcc_arm_mbr.ld
            endif
            ifeq ($(IAR),Y)
                LDSCRIPT = $(MCU_CUSTOM_DIR)/stm32f407xx_flash.icf
            endif
        endif
    endif

    ifeq ($(MPU),Y)
        $(info Add config MPU)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/mpu_config.c
    endif

    ifeq ($(SDIO),Y)
        $(info Config SDIO)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/sdio_config.c
    endif
    
    ifeq ($(INTERRUPT),Y)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/interrupt_config.c
    endif

    ifeq ($(SYSTICK),Y)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/systick_config.c
    endif
    
    ifeq ($(NVS),Y)
        $(info Add config NVS)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/nvs_config.c
    endif

    ifeq ($(SCHEDULER),Y)
        $(info Add config SCHEDULER)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/scheduler_config.c
    endif

    ifeq ($(FLASH),Y)
        $(info Config Flash)
        # $(error FLASH=$(FLASH))
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/flash_config.c
    endif
    
    ifeq ($(FLASH_FS),Y)
        $(info Add config FlashFs)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/flash_fs_config.c
    endif
    
    ifeq ($(SUPER_CYCLE),Y)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/super_cycle_config.c
    endif
    
    ifeq ($(WATCHDOG),Y)
        $(info Config WATCHDOG)
        #  $(error WATCHDOG=$(WATCHDOG))
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/watchdog_config.c
    endif
    
    SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/system_stm32f4xx.c
    SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/stm32f446re.c
    
    ifeq ($(STORE_FS),Y)
        #  $(error STORE_FS=$(STORE_FS))
        $(info Add config STORE_FS)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/storage_config.c
    endif

    ifeq ($(GCC),Y)
        SOURCES_ASM += $(MCU_CUSTOM_DIR)/startup_stm32f446xe.S
    endif
    MICROCONTROLLER_SELECTED=Y
endif