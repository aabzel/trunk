#protection against repeated include as in C preprocessor
ifneq ($(STM32F413ZH_MK_INC),Y)
    STM32F413ZH_MK_INC=Y

    MCU_SELECT_DIR = $(MICROCONTROLLER_DIR)/stm32f413zh
    #@echo $(error MCU_SELECT_DIR=$(MCU_SELECT_DIR))
    #@echo $(error CFLAGS=$(CFLAGS))
    OPT += -DHAS_STM32F413ZH
    OPT += -DHAS_STM32
    OPT += -DSTM32F4xxxx
    OPT += -DSTM32F413xx
    OPT += -DSTM32F413ZH
    OPT += -DSTM32F413xH
    OPT += -DSTM32F413Zx

    OPT += -DHAS_STM32F4xxxx
    OPT += -DHAS_STM32F413xx
    OPT += -DHAS_STM32F413ZH
    OPT += -DHAS_STM32F413xH
    OPT += -DHAS_STM32F413Zx
    
    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path))

    BOARD=Y
    CMSIS=Y
    MCU=Y
    CORTEX_M4=Y
    STM32F413ZH=Y
    STM32F4XX_HAL_DRIVER=Y
    #include $(WORKSPACE_LOC)/core/cortex_m4/cortex_m4.mk
    SOURCES_C += $(MCU_SELECT_DIR)/system_stm32f4xx.c
    SOURCES_ASM += $(MCU_SELECT_DIR)/startup_stm32f413xx.S

    ifeq ($(CLOCK),Y)
        SOURCES_C += $(MCU_SELECT_DIR)/clock_config.c
    endif
    
    ifeq ($(GPIO),Y)
        SOURCES_C += $(MCU_SELECT_DIR)/stm32f413zh.c
    endif

    INCDIR += -I$(MCU_SELECT_DIR)
    ifeq ($(MBR),Y)
        ifeq ($(MBR_ADVANCED),Y)
            LDSCRIPT = $(MCU_SELECT_DIR)/gcc_arm_mbr_advanced.ld
        else
            LDSCRIPT = $(MCU_SELECT_DIR)/gcc_arm_mbr.ld
        endif
    endif

    ifeq ($(BOOTLOADER),Y)
        # link script
        LDSCRIPT = $(MCU_SELECT_DIR)/gcc_arm_boot.ld
    endif

    ifeq ($(GENERIC),Y)
        # link script
        LDSCRIPT = $(MCU_SELECT_DIR)/gcc_arm_generic.ld
    endif

    ifeq ($(SYSTICK),Y)
        SOURCES_C += $(STM32F401RE_DIR)/systick_general_config.c
    endif

    MICROCONTROLLER_SELECTED=Y
endif
