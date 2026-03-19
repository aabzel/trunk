$(info GPIO_GENERAL_DRV_MK_INC=$(GPIO_GENERAL_DRV_MK_INC) )
ifneq ($(GPIO_GENERAL_DRV_MK_INC),Y)
    GPIO_GENERAL_DRV_MK_INC=Y

    GPIO_MCAL_DIR = $(MCAL_COMMON_DIR)/gpio
    # $(error GPIO_MCAL_DIR=$(GPIO_MCAL_DIR))

    INCDIR += -I$(GPIO_MCAL_DIR)
    MCAL_OPT += -DHAS_GPIO

    ifeq ($(GPIO_PROC),Y)
        MCAL_OPT += -DHAS_GPIO_PROC
    endif

    ifeq ($(GPIO_EXT),Y)
        MCAL_OPT += -DHAS_GPIO_EXT
    endif

    SOURCES_C += $(GPIO_MCAL_DIR)/gpio_general.c

    ifeq ($(DIAG),Y)
        ifeq ($(GPIO_DIAG),Y)
            MCAL_OPT += -DHAS_GPIO_DIAG
            SOURCES_C += $(GPIO_MCAL_DIR)/gpio_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(GPIO_COMMANDS),Y)
            MCAL_OPT += -DHAS_GPIO_COMMANDS
            SOURCES_C += $(GPIO_MCAL_DIR)/gpio_commands.c
        endif
    endif
    
endif