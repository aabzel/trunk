#protection against repeated include as in C preprocessor
$(info STM32f407ZG_MK_INC=$(STM32f407ZG_MK_INC) )
ifneq ($(STM32f407ZG_MK_INC),Y)
    STM32f407ZG_MK_INC=Y

    MCU_CUSTOM_DIR = $(MICROCONTROLLER_DIR)/stm32f407zg
    #@echo $(error MCU_CUSTOM_DIR=$(MCU_CUSTOM_DIR))
    OPT += -DHAS_STM32F407ZG
    OPT += -DHAS_STM32F407X
    OPT += -DHAS_STM32
    OPT += -DSTM32F4xxxx
    OPT += -DSTM32F4x
    OPT += -DSTM32F407x
    OPT += -DSTM32F407xx
    OPT += -DSTM32f407ZG
    OPT += -DSTM32F4x
    OPT += -DSTM32F4xxxx
    OPT += -DSTM32F407xG
    OPT += -DSTM32F407Zx

    FIRMWARE_TYPE_SELECTED=N
    BOARD=Y
    CORTEX_M4=Y
    CMSIS=Y
    MICROCONTROLLER=Y
    STM32=Y
    STM32x=Y
    STM32Fx=Y
    STM32F4x=Y
    STM32F40x=Y
    STM32F407x=Y
    STM32F407Zx=Y
    STM32F407ZG=Y
    STM32F407ZGx=Y
    STM32F4XX_HAL_DRIVER=Y

    INCDIR += -I$(MCU_CUSTOM_DIR)

    ifeq ($(BOOT),Y)
        SOURCES_C += $(MCU_CUSTOM_DIR)/boot_config.c
    endif

    ifeq ($(CLOCK),Y)
        SOURCES_C += $(MCU_CUSTOM_DIR)/clock_config.c
    endif

    ifeq ($(MBR),Y)
        FIRMWARE_TYPE_SELECTED=Y
        ifeq ($(MBR_ADVANCED),Y)
            LDSCRIPT = $(MCU_CUSTOM_DIR)/gcc_arm_mbr_advanced.ld
        else
            LDSCRIPT = $(MCU_CUSTOM_DIR)/gcc_arm_mbr.ld
        endif  
    endif  

    ifeq ($(BOOTLOADER),Y)
        # link script
        FIRMWARE_TYPE_SELECTED=Y
        LDSCRIPT = $(MCU_CUSTOM_DIR)/gcc_arm_boot.ld
    endif

    ifeq ($(SDIO),Y)
        $(info Config SDIO)
        SOURCES_C += $(MCU_CUSTOM_DIR)/sdio_config.c
    endif
    
    ifeq ($(GENERIC),Y)
        # link script
        OPT += -DVECT_TAB_OFFSET=0x08010000
        FIRMWARE_TYPE_SELECTED=Y
        LDSCRIPT = $(MCU_CUSTOM_DIR)/gcc_arm_generic.ld
    endif

    SOURCES_C += $(MCU_CUSTOM_DIR)/system_stm32f4xx.c

    ifeq ($(GPIO),Y)
        SOURCES_C += $(MCU_CUSTOM_DIR)/stm32f407zg.c
    endif

    ifeq ($(INTERRUPT),Y)
        SOURCES_C += $(MCU_CUSTOM_DIR)/interrupt_config.c
    endif
    
    ifeq ($(SYSTICK),Y)
        SOURCES_C += $(MCU_CUSTOM_DIR)/systick_general_config.c
    endif
    
    ifeq ($(NVS),Y)
        $(info Add config NVS)
        SOURCES_C += $(MCU_CUSTOM_DIR)/nvs_config.c
    endif

    ifeq ($(PARAM),Y)
        $(info Config Param)
        #@echo $(error PARAM=$(PARAM))
        SOURCES_C += $(MCU_CUSTOM_DIR)/param_config.c
    endif

    ifeq ($(FLASH),Y)
        $(info Config Flash)
        #@echo $(error FLASH=$(FLASH))
        SOURCES_C += $(MCU_CUSTOM_DIR)/flash_config.c
    endif

    ifeq ($(WATCHDOG),Y)
        $(info Config WATCHDOG)
        #@echo $(error WATCHDOG=$(WATCHDOG))
        SOURCES_C += $(MCU_CUSTOM_DIR)/watchdog_config.c
    endif

    ifeq ($(FLASH_FS),Y)
        #@echo $(error FLASH_FS=$(FLASH_FS))
        $(info Add config FlashFs)
        SOURCES_C += $(MCU_CUSTOM_DIR)/flash_fs_config.c
    endif


    SOURCES_ASM += $(MCU_CUSTOM_DIR)/startup_stm32f407xx.S

    MICROCONTROLLER_SELECTED=Y
endif
