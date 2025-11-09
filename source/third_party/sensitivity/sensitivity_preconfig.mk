$(info TP_SENSITIVITY_PRECONFIG_INC=$(TP_SENSITIVITY_PRECONFIG_INC) )
ifneq ($(TP_SENSITIVITY_PRECONFIG_INC),Y)
    TP_SENSITIVITY_PRECONFIG_INC=Y
    TP_SENSITIVITY_DIR = $(THIRD_PARTY_DIR)/sensitivity
    #@echo $(error TP_SENSITIVITY_DIR=$(TP_SENSITIVITY_DIR))

    ifeq ($(ACCELEROMETER_EHAL),Y)
        include $(TP_SENSITIVITY_DIR)/accelerometer/accelerometer_preconfig.mk
    endif
endif