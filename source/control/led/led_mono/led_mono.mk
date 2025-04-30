$(info LED_MONO_MK_INC=$(LED_MONO_MK_INC))

ifneq ($(LED_MONO_MK_INC),Y)
    LED_MONO_MK_INC=Y

    $(info Build LED Mono)

    LED_MONO_DIR = $(LED_GENERAL_DIR)/led_mono
    #@echo $(error LED_MONO_DIR=$(LED_MONO_DIR))

    INCDIR += -I$(LED_MONO_DIR)
    SOURCES_C += $(LED_MONO_DIR)/led_mono_drv.c

    OPT += -DHAS_LED_MONO
    OPT += -DHAS_LED_MONO_PROC
    #MATH=Y

    ifeq ($(DIAG),Y)
        ifeq ($(LED_MONO_DIAG),Y)
            OPT += -DHAS_LED_MONO_DIAG
            SOURCES_C += $(LED_MONO_DIR)/led_mono_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(LED_MONO_COMMANDS),Y)
            #@echo $(error LED_MONO_COMMANDS=$(LED_MONO_COMMANDS))
            OPT += -DHAS_LED_MONO_COMMANDS
            SOURCES_C += $(LED_MONO_DIR)/led_mono_commands.c
        endif
    endif
    #@echo $(error LED_MONO=$(LED_MONO))
endif