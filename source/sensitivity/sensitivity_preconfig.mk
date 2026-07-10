$(info SENSITIVITY_PRECONFIG_MK_INC=$(SENSITIVITY_PRECONFIG_MK_INC) )
ifneq ($(SENSITIVITY_PRECONFIG_MK_INC),Y)
    SENSITIVITY_PRECONFIG_MK_INC=Y

    MCAL_OPT += -DHAS_SENSITIVITY
    SENSITIVITY_DIR = $(WORKSPACE_LOC)/sensitivity
    # $(error SENSITIVITY_DIR=$(SENSITIVITY_DIR))

    INCDIR += -I$(SENSITIVITY_DIR)

    ifeq ($(DCF77),Y)
        include $(SENSITIVITY_DIR)/dcf77/dcf77_preconfig.mk
    endif

    ifeq ($(INCREMENTAL_ENCODER),Y)
        include $(SENSITIVITY_DIR)/incremental_encoder/incremental_encoder_preconfig.mk
    endif

    ifeq ($(CROSS_DETECT),Y)
        include $(SENSITIVITY_DIR)/cross_detect/cross_detect_preconfig.mk
    endif

    ifeq ($(FM_TUNER),Y)
        include $(SENSITIVITY_DIR)/fm_tuner/fm_tuner_preconfig.mk
    endif

    ifeq ($(GAME_PAD_PS2),Y)
        include $(SENSITIVITY_DIR)/game_pad_ps2/game_pad_ps2_preconfig.mk
    endif

    ifeq ($(KEYBOARD),Y)
        include $(SENSITIVITY_DIR)/keyboard/keyboard_preconfig.mk
    endif

    ifeq ($(DISTANCE),Y)
        # $(error DISTANCE=$(DISTANCE))
        include $(SENSITIVITY_DIR)/distance/distance_preconfig.mk
    endif
    
    ifeq ($(LIGHT_SENSOR),Y)
        include $(SENSITIVITY_DIR)/light_sensor/light_sensor_preconfig.mk
    endif

    ifeq ($(HEALTH_MONITOR),Y)
        include $(SENSITIVITY_DIR)/health_monitor/health_monitor_preconfig.mk
    endif

    ifeq ($(HW_VERSION),Y)
        include $(SENSITIVITY_DIR)/hw_version/hw_version_preconfig.mk
    endif

    ifeq ($(LOAD_DETECT),Y)
        # $(error LOAD_DETECT= $(LOAD_DETECT))
        include $(SENSITIVITY_DIR)/load_detect/load_detect_preconfig.mk
    endif

    ifeq ($(IR_RECEIVER),Y)
        include $(SENSITIVITY_DIR)/ir_receiver/ir_receiver_preconfig.mk
    endif

    ifeq ($(PHOTORESISTOR),Y)
        include $(SENSITIVITY_DIR)/photoresistor/photoresistor_preconfig.mk
    endif

    ifeq ($(TIME),Y)
        # $(error TIME=$(TIME))
        include $(SENSITIVITY_DIR)/time/time_preconfig.mk
    endif


        
endif