#protection against repeated include as in C preprocessor
$(info STM32F415RG_MK_INC=$(STM32F415RG_MK_INC) )
ifneq ($(STM32F415RG_MK_INC),Y)
    STM32F415RG_MK_INC=Y

    MCU_CUSTOM_DIR = $(MICROCONTROLLER_DIR)/stm32f415rg
    #@echo $(error MCU_CUSTOM_DIR=$(MCU_CUSTOM_DIR))
    OPT += -DHAS_STM32F415RG
    OPT += -DHAS_STM32
    OPT += -DSTM32F4xxxx
    OPT += -DSTM32F415xx
    OPT += -DSTM32F415RG
    OPT += -DSTM32F415xG
    OPT += -DSTM32F415Rx
    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )
    FIRMWARE_TYPE_SELECTED=N
    BOARD=Y
    CORTEX_M4=Y
    CMSIS=Y
    MICROCONTROLLER=Y
    STM32F415RG=Y
    STM32=Y
    STM32F4XX_HAL_DRIVER=Y

    INCDIR += -I$(MCU_CUSTOM_DIR)

    ifeq ($(CLOCK),Y)
        SOURCES_C += $(MCU_CUSTOM_DIR)/clock_config.c
    endif

    ifeq ($(BOOTLOADER),Y)
        # link script
        #@echo $(error BOOTLOADER=$(BOOTLOADER))
        FIRMWARE_TYPE_SELECTED=Y
        LDSCRIPT = $(MCU_CUSTOM_DIR)/gcc_arm_boot.ld
    endif

    ifeq ($(FLASH),Y)
        $(info Config Flash)
        #@echo $(error FLASH=$(FLASH))
        ifeq ($(GENERIC_MONOLITHIC),Y)
            OPT += -DHAS_GENERIC_MONOLITHIC
            SOURCES_C += $(MCU_CUSTOM_DIR)/flash_config_monolithic.c
        else
            SOURCES_C += $(MCU_CUSTOM_DIR)/flash_config.c
        endif
    endif

    ifeq ($(FLASH_FS),Y)
        $(info Add config FlashFs)
        SOURCES_C += $(MCU_CUSTOM_DIR)/flash_fs_config.c
    endif

    ifeq ($(MBR),Y)
        #@echo $(error MBR=$(MBR))
        FIRMWARE_TYPE_SELECTED=Y
        ifeq ($(MBR_ADVANCED),Y)
            LDSCRIPT = $(MCU_CUSTOM_DIR)/gcc_arm_mbr_advanced.ld
        else
            LDSCRIPT = $(MCU_CUSTOM_DIR)/gcc_arm_mbr.ld
        endif
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

    ifeq ($(GENERIC),Y)
        # link script
        FIRMWARE_TYPE_SELECTED=Y
        ifeq ($(GENERIC_MONOLITHIC),Y)
            OPT += -DVECT_TAB_OFFSET=0
            $(info Generic Monilitic)
            LDSCRIPT = $(MCU_CUSTOM_DIR)/gcc_arm_generic_monolithic.ld
        else
            $(info Generic separate)
            LDSCRIPT = $(MCU_CUSTOM_DIR)/gcc_arm_generic.ld
        endif
    endif

    SOURCES_C += $(MCU_CUSTOM_DIR)/system_stm32f4xx.c

    ifeq ($(GPIO),Y)
        SOURCES_C += $(MCU_CUSTOM_DIR)/stm32f415rg.c
    endif

    ifeq ($(SDIO),Y)
        $(info Config SDIO)
        SOURCES_C += $(MCU_CUSTOM_DIR)/sdio_config.c
    endif

    ifeq ($(SYSTICK),Y)
        SOURCES_C += $(MCU_CUSTOM_DIR)/systick_general_config.c
    endif

    SOURCES_ASM += $(MCU_CUSTOM_DIR)/startup_stm32f415xx.S

    MICROCONTROLLER_SELECTED=Y
endif