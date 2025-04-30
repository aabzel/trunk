$(info SENSITIVITY_MK_INC=$(SENSITIVITY_MK_INC) )
ifneq ($(SENSITIVITY_MK_INC),Y)
    SENSITIVITY_MK_INC=Y

    OPT += -DHAS_SENSITIVITY
    SENSITIVITY_DIR = $(WORKSPACE_LOC)/sensitivity
    #@echo $(error SENSITIVITY_DIR=$(SENSITIVITY_DIR))

    INCDIR += -I$(SENSITIVITY_DIR)

    ifeq ($(CROSS_DETECT),Y)
        include $(SENSITIVITY_DIR)/cross_detect/cross_detect.mk
    endif

    ifeq ($(FM_TUNER),Y)
        include $(SENSITIVITY_DIR)/fm_tuner/fm_tuner.mk
    endif

    ifeq ($(KEYBOARD),Y)
        include $(SENSITIVITY_DIR)/keyboard/keyboard.mk
    endif

    ifeq ($(BUTTON),Y)
        include $(SENSITIVITY_DIR)/button_fsm/button.mk
    endif

    ifeq ($(DISTANCE),Y)
        #@echo $(error DISTANCE=$(DISTANCE))
        include $(SENSITIVITY_DIR)/distance/distance.mk
    endif
    
    ifeq ($(LIGHT_SENSOR),Y)
        include $(SENSITIVITY_DIR)/light_sensor/light_sensor.mk
    endif

    ifeq ($(HEALTH_MONITOR),Y)
        include $(SENSITIVITY_DIR)/health_monitor/health_monitor.mk
    endif

    ifeq ($(HW_VERSION),Y)
        include $(SENSITIVITY_DIR)/hw_version/hw_version.mk
    endif

    ifeq ($(LOAD_DETECT),Y)
        #@echo $(error LOAD_DETECT= $(LOAD_DETECT))
        include $(SENSITIVITY_DIR)/load_detect/load_detect.mk
    endif

    ifeq ($(PHOTORESISTOR),Y)
        include $(SENSITIVITY_DIR)/photoresistor/photoresistor.mk
    endif

    ifeq ($(TIME),Y)
        #@echo $(error TIME=$(TIME))
        include $(SENSITIVITY_DIR)/time/time.mk
    endif

    SOURCES_C += $(SENSITIVITY_DIR)/sensitivity.c

    ifeq ($(DIAG),Y)
        SOURCES_C += $(SENSITIVITY_DIR)/sensitivity_diag.c
    endif

    ifeq ($(SENSITIVITY_COMMANDS),Y)
        OPT += -DHAS_SENSITIVITY_COMMANDS
        SOURCES_C += $(SENSITIVITY_DIR)/sensitivity_commands.c
    endif
        
endif