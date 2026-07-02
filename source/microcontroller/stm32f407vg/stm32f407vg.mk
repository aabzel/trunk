#protection against repeated include as in C preprocessor
$(info STM32f407VG_MK_INC=$(STM32f407VG_MK_INC) )
ifneq ($(STM32f407VG_MK_INC),Y)
    STM32f407VG_MK_INC=Y

    MCU_CUSTOM_DIR = $(MICROCONTROLLER_DIR)/stm32f407vg
    #  $(error MCU_CUSTOM_DIR=$(MCU_CUSTOM_DIR))
    MCAL_OPT += -DHAS_STM32
    MCAL_OPT += -DHAS_STM32X
    MCAL_OPT += -DHAS_STM32F4x
    MCAL_OPT += -DHAS_STM32F407VG
    MCAL_OPT += -DHAS_STM32F407X
    MCAL_OPT += -DHAS_STM32F4X
    MCAL_OPT += -DSTM32F407x
    MCAL_OPT += -DSTM32F407X
    MCAL_OPT += -DSTM32F4X
    MCAL_OPT += -DSTM32f407VG
    MCAL_OPT += -DSTM32f407VGX
    #HAL macros
    MCAL_OPT += -DSTM32F4x
    MCAL_OPT += -DSTM32F4xxxx
    MCAL_OPT += -DSTM32F407xG
    MCAL_OPT += -DSTM32F407xx
    MCAL_OPT += -DSTM32F407Vx
    
    FIRMWARE_TYPE_SELECTED=N
    BOARD=Y
    CMSIS=Y
    MICROCONTROLLER=Y
    STM32=Y
    STM32f407VG=Y
    STM32F4XX_HAL_DRIVER=Y

    INCDIR += -I$(MCU_CUSTOM_DIR)

    ifeq ($(DMA),Y)
        # $(error DMA=$(DMA))
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/dma_config.c
    endif

    ifeq ($(DMA_CHANNEL),Y)
        ifeq ($(ADC_DMA),Y)
            # $(error ADC_DMA=$(ADC_DMA))
            #SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/dma_channel_config_adc.c
        endif

        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/dma_channel_config_memcpy.c
        # $(error DMA_CHANNEL=$(DMA_CHANNEL))
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/dma_channel_config.c
    endif

    ifeq ($(INTERRUPT),Y)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/interrupt_config.c
    endif

    ifeq ($(CLOCK),Y)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/clock_config.c
    endif

    ifeq ($(CLOCK_OUT),Y)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/clock_out_config.c
    endif
    
    ifeq ($(BOOT),Y)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/boot_config.c
    endif

    ifeq ($(MBR),Y)
        FIRMWARE_TYPE_SELECTED=Y
        ifeq ($(MBR_ADVANCED),Y)
            LDSCRIPT = $(MCU_CUSTOM_DIR)/gcc_arm_mbr_advanced.ld
        else
            LDSCRIPT = $(MCU_CUSTOM_DIR)/gcc_arm_mbr.ld
        endif
    endif  

    ifeq ($(MPU),Y)
        $(info Add config MPU)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/mpu_config.c
    endif

    ifeq ($(BOOTLOADER),Y)
        # link script
        FIRMWARE_TYPE_SELECTED=Y
        LDSCRIPT = $(MCU_CUSTOM_DIR)/gcc_arm_boot.ld
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

    SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/system_stm32f4xx.c

    ifeq ($(GPIO),Y)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/stm32f407vg.c
    endif
    
    SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/stm32f407vg_diag.c

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

    ifeq ($(DAC),Y)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/dac_config.c
    endif
    ifeq ($(STORAGE),Y)
        $(info Config Param)
        #  $(error STORAGE=$(STORAGE))
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/storage_config.c
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

    ifeq ($(STORE_FS),Y)
        # $(error STORE_FS=$(STORE_FS))
        $(info Add config STORE_FS)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/storage_config.c
    endif
    
    ifeq ($(WATCHDOG),Y)
        $(info Config WATCHDOG)
        # $(error WATCHDOG=$(WATCHDOG))
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/watchdog_config.c
    endif

    SOURCES_ASM += $(MCU_CUSTOM_DIR)/startup_stm32f407xx.S

    MICROCONTROLLER_SELECTED=Y
endif
