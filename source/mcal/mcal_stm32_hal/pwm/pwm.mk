ifneq ($(PWM_CUSTOM_DRV_MK_INC),Y)
    PWM_CUSTOM_DRV_MK_INC=Y

    PWM_CUSTOM_DIR = $(MCAL_CUSTOM_DIR)/pwm
    # $(error PWM_CUSTOM_DIR=$(PWM_CUSTOM_DIR))

    INCDIR += -I$(PWM_CUSTOM_DIR)
    MCAL_OPT += -DHAS_PWM_CUSTOM
    MCAL_OPT += -DHAS_HAL_TIM_OC
    MCAL_OPT += -DHAS_HAL_TIM_PWM

    SOURCES_C += $(PWM_CUSTOM_DIR)/pwm_mcal.c

    ifeq ($(PWM_INTERRUPT),Y)
        SOURCES_C += $(PWM_CUSTOM_DIR)/pwm_custom_isr.c
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(DIAG_PWM),Y)
            MCAL_OPT += -DHAS_PWM_CUSTOM_DIAG
            SOURCES_C += $(PWM_CUSTOM_DIR)/pwm_custom_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(PWM_COMMANDS),Y)
            MCAL_OPT += -DHAS_PWM_CUSTOM_COMMANDS
            SOURCES_C += $(PWM_CUSTOM_DIR)/pwm_custom_commands.c
        endif
    endif
endif
