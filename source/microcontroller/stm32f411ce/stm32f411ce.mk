
#protection against repeated include as in C preprocessor
$(info STM32F411CE_MK_INC=$(STM32F411CE_MK_INC) )
ifneq ($(STM32F411CE_MK_INC),Y)
    STM32F411CE_MK_INC=Y
    STM32F411CE_DIR = $(MICROCONTROLLER_DIR)/stm32f411ce
    #@echo $(error STM32F411CE_DIR=$(STM32F411CE_DIR))
    OPT += -DHAS_STM32F411CE
    OPT += -DHAS_STM32
    OPT += -DSTM32F4xxxx
    OPT += -DSTM32F411xx
    OPT += -DSTM32F411CE
    OPT += -DSTM32F411xE
    OPT += -DSTM32F411Cx
    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )
    FIRMWARE_TYPE_SELECTED=N
    BOARD=Y
    CORTEX_M4=Y
    CMSIS=Y
    MICROCONTROLLER=Y
    STM32F411CE=Y
    STM32F4XX_HAL_DRIVER=Y

    INCDIR += -I$(STM32F411CE_DIR)

    ifeq ($(MBR),Y)
        #@echo $(error MBR=$(MBR))
        FIRMWARE_TYPE_SELECTED=Y
        ifeq ($(MBR_ADVANCED),Y)
            LDSCRIPT = $(STM32F411CE_DIR)/gcc_arm_mbr_advanced.ld
        else
            LDSCRIPT = $(STM32F411CE_DIR)/gcc_arm_mbr.ld
        endif  
    endif

    ifeq ($(BOOTLOADER),Y)
        # link script
        #@echo $(error BOOTLOADER=$(BOOTLOADER))
        FIRMWARE_TYPE_SELECTED=Y
        LDSCRIPT = $(STM32F411CE_DIR)/gcc_arm_boot.ld
    endif

    ifeq ($(GENERIC),Y)
        # link script
        FIRMWARE_TYPE_SELECTED=Y
        ifeq ($(GENERIC_MONOLITHIC),Y)
            $(info Generic Monilitic)
            LDSCRIPT = $(STM32F411CE_DIR)/gcc_arm_generic_monolithic.ld
        else
            $(info Generic separate)
            LDSCRIPT = $(STM32F411CE_DIR)/gcc_arm_generic.ld
        endif
    endif

    SOURCES_C += $(STM32F411CE_DIR)/system_stm32f4xx.c

    ifeq ($(GPIO),Y)
        SOURCES_C += $(STM32F411CE_DIR)/stm32f411ce.c
    endif

    ifeq ($(SYSTICK),Y)
        SOURCES_C += $(STM32F411CE_DIR)/systick_general_config.c
    endif

    SOURCES_ASM += $(STM32F411CE_DIR)/startup_stm32f411xe.S

    MICROCONTROLLER_SELECTED=Y
endif