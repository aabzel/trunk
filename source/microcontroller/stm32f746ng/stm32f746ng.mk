#protection against repeated include as in C preprocessor
$(info STM32F746NG_MK_INC=$(STM32F746NG_MK_INC) )
ifneq ($(STM32F746NG_MK_INC),Y)
    STM32F746NG_MK_INC=Y

    MCU_CUSTOM_DIR = $(MICROCONTROLLER_DIR)/stm32f746ng
    #  $(error MCU_CUSTOM_DIR=$(MCU_CUSTOM_DIR))
    MCAL_OPT += -DHAS_STM32
    MCAL_OPT += -DHAS_STM32X
    MCAL_OPT += -DHAS_STM32F746NG
    MCAL_OPT += -DHAS_STM32F746X
    MCAL_OPT += -DSTM32F746x
    MCAL_OPT += -DSTM32F746X
    MCAL_OPT += -DSTM32F7X
    MCAL_OPT += -DSTM32F746NG
    MCAL_OPT += -DSTM32F746NGX
    #HAL macros
    MCAL_OPT += -DSTM32F7x
    MCAL_OPT += -DSTM32F7xxxx
    MCAL_OPT += -DSTM32F746xG
    MCAL_OPT += -DSTM32F746xx
    MCAL_OPT += -DSTM32F746Nx
    
    FIRMWARE_TYPE_SELECTED=N
    BOARD=Y
    CMSIS=Y
    MICROCONTROLLER=Y
    STM32=Y
    STM32F746NG=Y
    STM32F7XX_HAL_DRIVER=Y
    ifeq ($(DAC),Y)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/dac_config.c
    endif

    ifeq ($(DAC_CHANNEL),Y)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/dac_channel_config.c
    endif

    INCDIR += -I$(MCU_CUSTOM_DIR)
    ifeq ($(DMA),Y)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/dma_config.c
    endif

    ifeq ($(DMA_CHANNEL),Y)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/dma_channel_config.c
        #SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/dma_channel_config_adc.c
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/dma_channel_config_memcpy.c
    endif


    ifeq ($(INTERRUPT),Y)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/interrupt_config.c
    endif

    ifeq ($(CLOCK),Y)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/clock_config.c
    endif

    ifeq ($(BOOT),Y)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/boot_config.c
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


    ifeq ($(MBR),Y)
        MCAL_OPT += -DMBR_START_ADDRESS=0x08000000
        FIRMWARE_TYPE_SELECTED=Y
        ifeq ($(MBR_ADVANCED),Y)
            LDSCRIPT = $(MCU_CUSTOM_DIR)/gcc_arm_mbr_advanced.ld
        else
            LDSCRIPT = $(MCU_CUSTOM_DIR)/gcc_arm_mbr.ld
        endif
    endif

    ifeq ($(SDIO),Y)
        $(info Config SDIO)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/sdio_config.c
    endif

    ifeq ($(PIN),Y)
        SOURCES_THIRD_PARTY_C += $(MCU_CUSTOM_DIR)/pin_config.c
    endif

    ifeq ($(GENERIC),Y)
        # link script
        FIRMWARE_TYPE_SELECTED=Y
        ifeq ($(GENERIC_MONOLITHIC),Y)
            MCAL_OPT += -DVECT_TAB_OFFSET=0x08000000
            MCAL_OPT += -DAPP_START_ADDRESS=0x08000000
            $(info Generic Monilitic)
            LDSCRIPT = $(MCU_CUSTOM_DIR)/gcc_arm_generic_monolithic.ld
        else
            $(info Generic separate)
            MCAL_OPT += -DVECT_TAB_OFFSET=0x08010000
            MCAL_OPT += -DAPP_START_ADDRESS=0x08010000
            LDSCRIPT = $(MCU_CUSTOM_DIR)/gcc_arm_generic.ld
        endif
    endif

    SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/system_stm32f7xx.c

    ifeq ($(GPIO),Y)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/stm32f746ng.c
    endif
    
    SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/stm32f746ng_diag.c

    ifeq ($(SUPER_CYCLE),Y)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/super_cycle_config.c
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

    ifeq ($(STORAGE),Y)
        $(info Config Param)
        #  $(error STORAGE=$(STORAGE))
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/storage_config.c
    endif

    ifeq ($(MBR),Y)
        #  $(error MBR=$(MBR))
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/mbr_config.c
    endif

    ifeq ($(FLASH),Y)
        $(info Config Flash)
        #  $(error FLASH=$(FLASH))
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/flash_config.c
    endif

    ifeq ($(FLASH_FS),Y)
        $(info Add config FlashFs)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/flash_fs_config.c
    endif


    ifeq ($(WATCHDOG),Y)
        $(info Config WATCHDOG)
        #  $(error WATCHDOG=$(WATCHDOG))
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/watchdog_config.c
    endif

    ifeq ($(STORE_FS),Y)
        #  $(error STORE_FS=$(STORE_FS))
        $(info Add config STORE_FS)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/storage_config.c
    endif

    ifeq ($(GCC),Y)
        SOURCES_ASM += $(MCU_CUSTOM_DIR)/startup_stm32f746xx.S
    endif

    ifeq ($(IAR),Y)
        SOURCES_ASM += $(MCU_CUSTOM_DIR)/startup_stm32f746xx_iar.s
    endif

    MICROCONTROLLER_SELECTED=Y
endif
