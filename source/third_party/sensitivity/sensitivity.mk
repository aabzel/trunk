$(info TP_SENSITIVITY_MK_INC=$(TP_SENSITIVITY_MK_INC) )
ifneq ($(TP_SENSITIVITY_MK_INC),Y)
    TP_SENSITIVITY_MK_INC=Y

    TP_SENSITIVITY_DIR = $(THIRD_PARTY_DIR)/sensitivity
    #@echo $(error TP_SENSITIVITY_DIR=$(TP_SENSITIVITY_DIR))

    INCDIR += -I$(TP_SENSITIVITY_DIR)

    OPT += -DHAS_SENSITIVITY
    OPT += -DHAS_THIRD_PARTY_SENSITIVITY

    ifeq ($(SENSITIVITY_COMMANDS),Y)
        OPT += -DHAS_SENSITIVITY_CLI
        OPT += -DSENSITIVITY_CLI_IN_USE
    endif

    ifeq ($(ACCELEROMETER_EHAL),Y)
        include $(TP_SENSITIVITY_DIR)/accelerometer/accelerometer.mk
    endif

    SOURCES_THIRD_PARTY_C +=  $(TP_SENSITIVITY_DIR)/sensitivity_initialize.c
    SOURCES_THIRD_PARTY_C +=  $(TP_SENSITIVITY_DIR)/sensitivity_routines.c
endif