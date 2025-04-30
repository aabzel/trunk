#protection against repeated include as in C preprocessor
ifneq ($(STM32F401RE_MK_INC),Y)
    STM32F401RE_MK_INC=Y

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )

    MCU_CUSTOM_DIR = $(MICROCONTROLLER_DIR)/stm32f401re
    #@echo $(error MCU_CUSTOM_DIR= $(MCU_CUSTOM_DIR))
    #@echo $(error MCU_CUSTOM_DIR=$(MCU_CUSTOM_DIR))
    #@echo $(error CFLAGS=$(CFLAGS))
    OPT += -DHAS_STM32
    OPT += -DHAS_STM32F401RE
    OPT += -DSTM32F401xx
    OPT += -DSTM32F401RE
    OPT += -DSTM32F401xE
    OPT += -DSTM32F401Rx

    BOARD=Y
    CORTEX_M4=Y
    CMSIS=Y
    MICROCONTROLLER=Y
    STM32=Y
    STM32F401RE=Y
    STM32F4XX_HAL_DRIVER=Y

    INCDIR += -I$(MCU_CUSTOM_DIR)

    ifeq ($(MBR),Y)
        # link script
        LDSCRIPT = $(MCU_CUSTOM_DIR)/gcc_arm_mbr.ld
    endif

    ifeq ($(BOOTLOADER),Y)
        # link script
        LDSCRIPT = $(MCU_CUSTOM_DIR)/gcc_arm_boot.ld
    endif

    ifeq ($(FLASH),Y)
        SOURCES_C += $(MCU_CUSTOM_DIR)/flash_config.c
    endif

    SOURCES_C += $(MCU_CUSTOM_DIR)/clock_config.c
    ifeq ($(NVS),Y)
        SOURCES_C += $(MCU_CUSTOM_DIR)/nvs_config.c
    endif

    ifeq ($(FLASH_FS),Y)
        SOURCES_C += $(MCU_CUSTOM_DIR)/flash_fs_config.c
    endif
    
    ifeq ($(PARAM),Y)
        SOURCES_C += $(MCU_CUSTOM_DIR)/param_config.c
    endif
    
    ifeq ($(GENERIC),Y)
        # link script
        LDSCRIPT = $(MCU_CUSTOM_DIR)/gcc_arm_generic.ld
    endif

    ifeq ($(SYSTICK),Y)
        SOURCES_C += $(MCU_CUSTOM_DIR)/systick_general_config.c
    endif

    SOURCES_C += $(MCU_CUSTOM_DIR)/system_stm32f4xx.c
    SOURCES_C += $(MCU_CUSTOM_DIR)/stm32f401re.c

    SOURCES_ASM += $(MCU_CUSTOM_DIR)/startup_stm32f401xe.S
    MICROCONTROLLER_SELECTED=Y
endif