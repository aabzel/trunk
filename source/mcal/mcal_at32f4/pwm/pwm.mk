ifneq ($(PWM_CUSTOM_DRV_MK_INC),Y)
    PWM_CUSTOM_DRV_MK_INC=Y

    PWM_CUSTOM_DIR = $(MCAL_AT32F4_DIR)/pwm
    #@echo $(error PWM_CUSTOM_DIR=$(PWM_CUSTOM_DIR))

    INCDIR += -I$(PWM_CUSTOM_DIR)
    OPT += -DHAS_PWM

    SOURCES_C += $(PWM_CUSTOM_DIR)/pwm_mcal.c

    ifeq ($(DIAG),Y)
        ifeq ($(PWM_DIAG),Y)
            OPT += -DHAS_PWM_CUSTOM_DIAG
            SOURCES_C += $(PWM_CUSTOM_DIR)/pwm_custom_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(PWM_COMMANDS),Y)
            OPT += -DHAS_PWM_CUSTOM_COMMANDS
            SOURCES_C += $(PWM_CUSTOM_DIR)/pwm_custom_commands.c
        endif
    endif
endif
