ifneq ($(LED_MONO_PWM_MK_INC),Y)
    LED_MONO_PWM_MK_INC=Y

    LED_MONO_PWM_DIR = $(LED_GENERAL_DIR)/led_mono_pwm
    # $(error LED_MONO_PWM_DIR=$(LED_MONO_PWM_DIR))

    INCDIR += -I$(LED_MONO_PWM_DIR)

    MCAL_OPT += -DHAS_LED_MONO_PWM

    MCAL_OPT += -DHAS_LED_MONO_PWM_PROC
    #ifeq ($(LED_MONO_PWM_PROC),Y)
    #endif

    SOURCES_C += $(LED_MONO_PWM_DIR)/led_mono_pwm.c

    ifeq ($(LED_MONO_PWM_INTERRUPTS),Y)
        MCAL_OPT += -DHAS_LED_MONO_PWM_INTERRUPTS
        SOURCES_C += $(LED_MONO_PWM_DIR)/led_mono_pwm_isr.c
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(LED_MONO_PWM_DIAG),Y)
            MCAL_OPT += -DHAS_LED_MONO_PWM_DIAG
            SOURCES_C += $(LED_MONO_PWM_DIR)/led_mono_pwm_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(LED_MONO_PWM_COMMANDS),Y)
            MCAL_OPT += -DHAS_LED_MONO_PWM_COMMANDS
            SOURCES_C += $(LED_MONO_PWM_DIR)/led_mono_pwm_commands.c
        endif
    endif
endif
