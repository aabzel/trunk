ifneq ($(GPIO_DAC_MK_INC),Y)
    GPIO_DAC_MK_INC=Y

    GPIO_DAC_DIR = $(CONTROL_DIR)/gpio_dac
    # $(error GPIO_DAC_DIR=$(GPIO_DAC_DIR))

    INCDIR += -I$(GPIO_DAC_DIR)

    MCAL_OPT += -DHAS_GPIO_DAC

    ifeq ($(GPIO_DAC_PROC),Y)
        MCAL_OPT += -DHAS_GPIO_DAC_PROC
    endif

    SOURCES_C += $(GPIO_DAC_DIR)/gpio_dac_mcal.c

    ifeq ($(GPIO_DAC_INTERRUPTS),Y)
        MCAL_OPT += -DHAS_GPIO_DAC_INTERRUPTS
        SOURCES_C += $(GPIO_DAC_DIR)/gpio_dac_isr.c
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(GPIO_DAC_DIAG),Y)
            MCAL_OPT += -DHAS_GPIO_DAC_DIAG
            SOURCES_C += $(GPIO_DAC_DIR)/gpio_dac_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(GPIO_DAC_COMMANDS),Y)
            MCAL_OPT += -DHAS_GPIO_DAC_COMMANDS
            SOURCES_C += $(GPIO_DAC_DIR)/gpio_dac_commands.c
        endif
    endif
endif
