$(info GPIO_CUSTOM_MK_INC=$(GPIO_CUSTOM_MK_INC))
ifneq ($(GPIO_CUSTOM_MK_INC),Y)
    GPIO_CUSTOM_MK_INC=Y

    GPIO_CUSTOM_DIR = $(MCAL_X86_DIR)/gpio
    #@echo $(error GPIO_CUSTOM_DIR=$(GPIO_CUSTOM_DIR))
    MCAL_OPT += -DHAS_GPIO_CUSTOM

    INCDIR += -I$(GPIO_CUSTOM_DIR)

    SOURCES_C += $(GPIO_CUSTOM_DIR)/gpio_mcal.c
    SOURCES_C += $(GPIO_CUSTOM_DIR)/gpio_isr.c

    ifeq ($(CLI),Y)
        ifeq ($(GPIO_COMMANDS),Y)
            MCAL_OPT += -DHAS_GPIO_COMMANDS
            SOURCES_C += $(GPIO_CUSTOM_DIR)/gpio_custom_commands.c
        endif
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(GPIO_DIAG),Y)
            MCAL_OPT += -DHAS_GPIO_DIAG
            #@echo $(error GPIO_DIAG=$(GPIO_DIAG))
            SOURCES_C += $(GPIO_CUSTOM_DIR)/gpio_custom_diag.c
        endif
    endif
    
endif