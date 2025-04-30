$(info GPIO_DRV_MK_INC=  $(GPIO_DRV_MK_INC) )
ifneq ($(GPIO_DRV_MK_INC),Y)
    GPIO_DRV_MK_INC=Y

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )

    GPIO_NRF_DIR = $(MCAL_NRF5340_DIR)/gpio
    #@echo $(error GPIO_NRF_DIR=$(GPIO_NRF_DIR))
    OPT += -DHAS_GPIO
    OPT += -DHAS_GPIO_NRFX
    OPT += -DHAS_GPIO_CUSTOM
    OPT += -DCONFIG_NFCT_PINS_AS_GPIOS

    INCDIR += -I$(GPIO_NRF_DIR)

    SOURCES_C += $(GPIO_NRF_DIR)/gpio_drv.c

    ifeq ($(CLI),Y)
        ifeq ($(GPIO_COMMANDS),Y)
            OPT += -DHAS_GPIO_CUSTOM_COMMANDS
            SOURCES_C += $(GPIO_NRF_DIR)/gpio_custom_commands.c
        endif
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(GPIO_DIAG),Y)
            SOURCES_C += $(GPIO_NRF_DIR)/gpio_custom_diag.c
        endif
    endif
endif