ifneq ($(PWM_GENERAL_DRV_MK_INC),Y)
    PWM_GENERAL_DRV_MK_INC=Y

    PWM_MCAL_DIR = $(MCAL_COMMON_DIR)/pwm
    # $(error PWM_MCAL_DIR=$(PWM_MCAL_DIR))

    INCDIR += -I$(PWM_MCAL_DIR)
    MCAL_OPT += -DHAS_PWM
    MCAL_OPT += -DHAS_PWM_INIT

    SOURCES_C += $(PWM_MCAL_DIR)/pwm_general.c
    SOURCES_C += $(PWM_MCAL_DIR)/pwm_isr.c

    ifeq ($(DIAG),Y)
        ifeq ($(PWM_DIAG),Y)
            #$(error DIAG_PWM=$(DIAG_PWM))
            MCAL_OPT += -DHAS_PWM_DIAG
            SOURCES_C += $(PWM_MCAL_DIR)/pwm_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(PWM_COMMANDS),Y)
            MCAL_OPT += -DHAS_PWM_COMMANDS
            SOURCES_C += $(PWM_MCAL_DIR)/pwm_commands.c
        endif
    endif
endif
