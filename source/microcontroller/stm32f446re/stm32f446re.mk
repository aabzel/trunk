#protection against repeated include as in C preprocessor
ifneq ($(STM32F446RE_MK_INC),Y)
    STM32F446RE_MK_INC=Y

    STM32F446RE_DIR = $(MICROCONTROLLER_DIR)/stm32f446re
    #@echo $(error STM32F446RE_DIR= $(STM32F446RE_DIR))
    #@echo $(error STM32F446RE_DIR=$(STM32F446RE_DIR))
    #@echo $(error CFLAGS=$(CFLAGS))
    OPT += -DHAS_STM32
    OPT += -DHAS_STM32F446RE
    OPT += -DSTM32F446xx
    OPT += -DSTM32F446RE
    OPT += -DSTM32F446xE
    OPT += -DSTM32F446Rx

    BOARD=Y
    CORTEX_M4=Y
    CMSIS=Y
    MICROCONTROLLER=Y
    STM32=Y
    STM32F446RE=Y
    STM32F4XX_HAL_DRIVER=Y

    INCDIR += -I$(STM32F446RE_DIR)

    ifeq ($(MBR),Y)
        # link script
        LDSCRIPT = $(STM32F446RE_DIR)/gcc_arm_mbr.ld
    endif

    ifeq ($(BOOTLOADER),Y)
        # link script
        LDSCRIPT = $(STM32F446RE_DIR)/gcc_arm_boot.ld
    endif

    ifeq ($(GENERIC),Y)
        # link script
        LDSCRIPT = $(STM32F446RE_DIR)/gcc_arm_generic.ld
    endif

    ifeq ($(SYSTICK),Y)
        SOURCES_C += $(STM32F446RE_DIR)/systick_general_config.c
    endif

    SOURCES_C += $(STM32F446RE_DIR)/system_stm32f4xx.c
    SOURCES_C += $(STM32F446RE_DIR)/stm32f446re.c

    SOURCES_ASM += $(STM32F446RE_DIR)/startup_stm32f446xe.S
    MICROCONTROLLER_SELECTED=Y
endif