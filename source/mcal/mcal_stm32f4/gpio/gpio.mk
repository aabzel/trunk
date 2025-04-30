$(info GPIO_DRV_MK_INC=$(GPIO_DRV_MK_INC))
ifneq ($(GPIO_DRV_MK_INC),Y)
    GPIO_DRV_MK_INC=Y


    GPIO_DIR = $(MCAL_STM32F4_DIR)/gpio
    #@echo $(error GPIO_DIR=$(GPIO_DIR))
    OPT += -DHAS_GPIO_CUSTOM

    INCDIR += -I$(GPIO_DIR)

    SOURCES_C += $(GPIO_DIR)/gpio_mcal.c
    SOURCES_C += $(GPIO_DIR)/gpio_custom_isr.c

    ifeq ($(CLI),Y)
        ifeq ($(GPIO_COMMANDS),Y)
            OPT += -DHAS_GPIO_COMMANDS
            SOURCES_C += $(GPIO_DIR)/gpio_custom_commands.c
        endif
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(GPIO_DIAG),Y)
            OPT += -DHAS_GPIO_DIAG
            #@echo $(error GPIO_DIAG=$(GPIO_DIAG))
            SOURCES_C += $(GPIO_DIR)/gpio_custom_diag.c
        endif
    endif
    
endif