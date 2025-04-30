$(info LED_GENERAL_PRECONFIG_INC=$(LED_GENERAL_PRECONFIG_INC) )
ifneq ($(LED_GENERAL_PRECONFIG_INC),Y)
    LED_GENERAL_PRECONFIG_INC=Y

    LED_GENERAL_DIR = $(CONTROL_DIR)/led
    #@echo $(error LED_GENERAL_DIR=$(LED_GENERAL_DIR))
    LED=Y
    GPIO=Y
    PINS=Y
    #TIME=Y
    ifeq ($(LED_MONO),Y)
        include $(LED_GENERAL_DIR)/led_mono/led_mono_preconfig.mk
    endif

    ifeq ($(LED_RGB),Y)
        include $(LED_GENERAL_DIR)/led_rgb/led_rgb_preconfig.mk
    endif

endif