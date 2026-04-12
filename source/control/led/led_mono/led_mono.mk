$(info LED_MONO_MK_INC=$(LED_MONO_MK_INC))

ifneq ($(LED_MONO_MK_INC),Y)
    LED_MONO_MK_INC=Y

    $(info Build LED Mono)

    LED_MONO_DIR = $(LED_GENERAL_DIR)/led_mono
    # $(error LED_MONO_DIR=$(LED_MONO_DIR))

    INCDIR += -I$(LED_MONO_DIR)

    SOURCES_C += $(LED_MONO_DIR)/led_mono_drv.c

    ifeq ($(PWM),Y)
        SOURCES_C += $(LED_MONO_DIR)/led_mono_pwm.c
    endif

    MCAL_OPT += -DHAS_LED_MONO
    MCAL_OPT += -DHAS_LED_MONO_PROC

    ifeq ($(DIAG),Y)
        ifeq ($(LED_MONO_DIAG),Y)
            MCAL_OPT += -DHAS_LED_MONO_DIAG
            SOURCES_C += $(LED_MONO_DIR)/led_mono_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(LED_MONO_COMMANDS),Y)
            # $(error LED_MONO_COMMANDS=$(LED_MONO_COMMANDS))
            MCAL_OPT += -DHAS_LED_MONO_COMMANDS
            SOURCES_C += $(LED_MONO_DIR)/led_mono_commands.c
        endif
    endif
    # $(error LED_MONO=$(LED_MONO))
endif