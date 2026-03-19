#protection against repeated include as in C preprocessor
$(info STM32F407VE_MK_INC=$(STM32F407VE_MK_INC) )
ifneq ($(STM32F407VE_MK_INC),Y)
    STM32F407VE_MK_INC=Y

    MCU_CUSTOM_DIR = $(MICROCONTROLLER_DIR)/stm32f407ve
    # $(error MCU_CUSTOM_DIR=$(MCU_CUSTOM_DIR))
    MCAL_OPT += -DHAS_STM32F407VE
    MCAL_OPT += -DHAS_STM32
    MCAL_OPT += -DSTM32F4xxxx
    MCAL_OPT += -DSTM32F4x
    MCAL_OPT += -DSTM32F407xx
    MCAL_OPT += -DSTM32F407x
    MCAL_OPT += -DSTM32F407VE
    MCAL_OPT += -DSTM32F407xE
    MCAL_OPT += -DSTM32F407Vx
    MCAL_OPT += -DHAS_STM32F407X

    FIRMWARE_TYPE_SELECTED=N
    BOARD=Y
    CMSIS=Y
    MICROCONTROLLER=Y
    STM32=Y
    STM32F407VE=Y
    STM32F4XX_HAL_DRIVER=Y

    INCDIR += -I$(MCU_CUSTOM_DIR)

    ifeq ($(BOOT),Y)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/boot_config.c
    endif
    
    ifeq ($(CLOCK),Y)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/clock_config.c
    endif

    ifeq ($(BOOTLOADER),Y)
        # link script
        FIRMWARE_TYPE_SELECTED=Y

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
        FIRMWARE_TYPE_SELECTED=Y
        ifeq ($(GENERIC_MONOLITHIC),Y)
            MCAL_OPT +=-DBOOT_START_ADDRESS=0x08000000
            MCAL_OPT += -DAPP_START_ADDRESS=0x08000000
            LDSCRIPT = $(MCU_CUSTOM_DIR)/gcc_arm_generic_monolithic.ld
        else
            MCAL_OPT += -DAPP_START_ADDRESS=0x08010000
            MCAL_OPT +=-DBOOT_START_ADDRESS=0x08010000
            LDSCRIPT = $(MCU_CUSTOM_DIR)/gcc_arm_generic.ld
        endif
    endif

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

    SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/system_stm32f4xx.c

    ifeq ($(GPIO),Y)
        #SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/stm32f407ve.c
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

    ifeq ($(STORAGE),Y)
        $(info Config STORAGE)
        # $(error STORAGE=$(STORAGE))
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/storage_config.c
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

    ifeq ($(STORE_FS),Y)
        #  $(error STORE_FS=$(STORE_FS))
        $(info Add config STORE_FS)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/storage_config.c
    endif

    SOURCES_DIAG_C += $(MCU_CUSTOM_DIR)/stm32f407ve_diag.c

    ifeq ($(GCC),Y)
        SOURCES_ASM += $(MCU_CUSTOM_DIR)/startup_stm32f407xx.S
    endif

    ifeq ($(IAR),Y)
        SOURCES_ASM += $(MCU_CUSTOM_DIR)/startup_stm32f407xx_iar.s
    endif

    MICROCONTROLLER_SELECTED=Y
endif
