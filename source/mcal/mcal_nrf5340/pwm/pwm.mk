ifneq ($(PWM_NRF_DRV_MK_INC),Y)
    PWM_NRF_DRV_MK_INC=Y
    $(info + PWM NRF)
    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )

    PWM_DIR = $(MCAL_NRF5340_DIR)/pwm
    #@echo $(error PWM_DIR=$(PWM_DIR))

    INCDIR += -I$(PWM_DIR)
    OPT += -DHAS_PWM
    OPT += -DHAS_PWM_INIT
    OPT += -DHAS_PWM_NRFX

    SOURCES_C += $(PWM_DIR)/pwm_drv.c
    SOURCES_C += $(PWM_DIR)/pwm_isr.c

    ifeq ($(PWM0),Y)
        $(info + PWM0)
        OPT += -DHAS_PWM0
    endif

    ifeq ($(PWM1),Y)
        $(info + PWM1)
        OPT += -DHAS_PWM1
    endif

    ifeq ($(PWM2),Y)
        $(info + PWM2)
        OPT += -DHAS_PWM2
    endif

    ifeq ($(PWM3),Y)
        $(info + PWM3)
        OPT += -DHAS_PWM3
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(DIAG_PWM),Y)
            $(info + PWM Diag)
            SOURCES_C += $(PWM_DIR)/pwm_custom_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(PWM_COMMANDS),Y)
            $(info + PWM Commands)
            OPT += -DHAS_PWM_COMMANDS
            SOURCES_C += $(PWM_DIR)/pwm_custom_commands.c
        endif
    endif
endif
