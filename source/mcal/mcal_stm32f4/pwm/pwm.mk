ifneq ($(PWM_DRV_MK_INC),Y)
    PWM_DRV_MK_INC=Y


    PWM_DIR = $(MCAL_STM32F4_DIR)/pwm
    #@echo $(error PWM_DIR=$(PWM_DIR))

    INCDIR += -I$(PWM_DIR)
    OPT += -DHAS_PWM_CUSTOM

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
