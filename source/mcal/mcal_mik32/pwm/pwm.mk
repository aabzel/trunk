ifneq ($(PWM_DRV_MK_INC),Y)
    PWM_DRV_MK_INC=Y

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )

    PWM_DIR = $(MCAL_MIK32_DIR)/pwm
    #@echo $(error PWM_DIR=$(PWM_DIR))

    INCDIR += -I$(PWM_DIR)
    OPT += -DHAS_PWM

    SOURCES_C += $(PWM_DIR)/pwm_drv.c

    ifeq ($(DIAG),Y)
        ifeq ($(DIAG_PWM),Y)
            SOURCES_C += $(PWM_DIR)/pwm_stm32_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(PWM_COMMANDS),Y)
            OPT += -DHAS_PWM_COMMANDS
            SOURCES_C += $(PWM_DIR)/pwm_commands.c
        endif
    endif
endif
