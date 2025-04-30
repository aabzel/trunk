$(info LED_GENERAL_MK_INC=$(LED_GENERAL_MK_INC) )
ifneq ($(LED_GENERAL_MK_INC),Y)
    LED_GENERAL_MK_INC=Y
    $(info + LED General)

    LED_GENERAL_DIR = $(CONTROL_DIR)/led
    #@echo $(error LED_GENERAL_DIR=$(LED_GENERAL_DIR))

    OPT += -DHAS_LED
    OPT += -DHAS_LED_PROC
    
    SOURCES_C += $(LED_GENERAL_DIR)/led_drv.c
    INCDIR += -I$(LED_GENERAL_DIR)

 
    ifeq ($(LED_MONO),Y)
        $(info + LED Mono)
        #@echo $(error LED_MONO=$(LED_MONO))
        include $(LED_GENERAL_DIR)/led_mono/led_mono.mk
    endif

    ifeq ($(LED_EXT),Y)
        OPT += -DHAS_LED_EXT
    endif

    ifeq ($(LED_RGB),Y)
        $(info + LED RGB)
        include $(LED_GENERAL_DIR)/led_rgb/led_rgb.mk
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(LED_DIAG),Y)
            $(info + LED DIAG)
            OPT += -DHAS_LED_DIAG
            SOURCES_C += $(LED_GENERAL_DIR)/led_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(LED_COMMANDS),Y)
            OPT += -DHAS_LED_COMMANDS
        endif
    endif
endif