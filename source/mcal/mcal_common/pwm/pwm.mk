
ifneq ($(PWM_GENERAL_DRV_MK_INC),Y)
    PWM_GENERAL_DRV_MK_INC=Y

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build $(mkfile_path) )

    PWM_MCAL_DIR = $(MCAL_COMMON_DIR)/pwm
    #@echo $(error PWM_MCAL_DIR=$(PWM_MCAL_DIR))

    INCDIR += -I$(PWM_MCAL_DIR)
    OPT += -DHAS_PWM
    OPT += -DHAS_PWM_INIT

    SOURCES_C += $(PWM_MCAL_DIR)/pwm_general_drv.c

    ifeq ($(DIAG),Y)
        ifeq ($(PWM_DIAG),Y)
            #@echo $(error DIAG_PWM=$(DIAG_PWM))
            SOURCES_C += $(PWM_MCAL_DIR)/pwm_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(PWM_COMMANDS),Y)
            OPT += -DHAS_PWM_COMMANDS
            SOURCES_C += $(PWM_MCAL_DIR)/pwm_commands.c
        endif
    endif
endif
