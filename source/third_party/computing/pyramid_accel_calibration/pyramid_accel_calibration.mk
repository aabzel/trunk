$(info PYRAMID_ACCEL_CALIBRATION_EHAL_MK_INC=$(PYRAMID_ACCEL_CALIBRATION_EHAL_MK_INC))

ifneq ($(PYRAMID_ACCEL_CALIBRATION_EHAL_MK_INC),Y)
    PYRAMID_ACCEL_CALIBRATION_EHAL_MK_INC=Y

    $(info Build  + Accelerometer calibration with a pyramid)

    PYRAMID_ACCEL_CALIBRATION_TP_DIR = $(COMPUTING_DIRECTORY)/pyramid_accel_calibration
    #$(error PYRAMID_ACCEL_CALIBRATION_TP_DIR=$(PYRAMID_ACCEL_CALIBRATION_TP_DIR))
    COMPUTING=Y
    INCDIR += -I$(PYRAMID_ACCEL_CALIBRATION_TP_DIR)

    SOURCES_THIRD_PARTY_C+= $(PYRAMID_ACCEL_CALIBRATION_TP_DIR)/pyramid_accel_calibration.c
    SOURCES_THIRD_PARTY_C+= $(PYRAMID_ACCEL_CALIBRATION_TP_DIR)/pyramid_accel_calibration_configuration.c

    OPT += -DPYRAMID_ACCEL_CALIB_IN_USE
    OPT += -DHAS_PYRAMID_ACCEL_CALIBRATION

    ifeq ($(DIAG),Y)
        ifeq ($(PYRAMID_ACCEL_CALIBRATION_DIAG),Y)
            OPT += -DPYRAMID_ACCEL_CALIBRATION_DIAG_IN_USE
            SOURCES_THIRD_PARTY_C+= $(PYRAMID_ACCEL_CALIBRATION_TP_DIR)/pyramid_accel_calibration_diagnostic.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(PYRAMID_ACCEL_CALIBRATION_COMMANDS),Y)
            #@echo $(error PYRAMID_ACCEL_CALIBRATION_COMMANDS=$(PYRAMID_ACCEL_CALIBRATION_COMMANDS))
            OPT += -DPYRAMID_ACCEL_CALIBRATION_CLI_IN_USE
            SOURCES_THIRD_PARTY_C+= $(PYRAMID_ACCEL_CALIBRATION_TP_DIR)/pyramid_accel_calibration_cli.c
        endif
    endif
    
    
    SOURCES_EHAL_C+= $(PYRAMID_ACCEL_CALIBRATION_TP_DIR)/pyramid_accel_calibration.c
    SOURCES_EHAL_C+= $(PYRAMID_ACCEL_CALIBRATION_TP_DIR)/pyramid_accel_calibration_configuration.c
    SOURCES_EHAL_C+= $(PYRAMID_ACCEL_CALIBRATION_TP_DIR)/pyramid_accel_calibration_cli.c
    SOURCES_EHAL_C+= $(PYRAMID_ACCEL_CALIBRATION_TP_DIR)/pyramid_accel_calibration_diagnostic.c
    
    SOURCES_EHAL_H += $(PYRAMID_ACCEL_CALIBRATION_TP_DIR)/pyramid_accel_calibration.h
    SOURCES_EHAL_H += $(PYRAMID_ACCEL_CALIBRATION_TP_DIR)/pyramid_accel_calibration_configuration.h
    SOURCES_EHAL_H += $(PYRAMID_ACCEL_CALIBRATION_TP_DIR)/pyramid_accel_calibration_diagnostic.h
    SOURCES_EHAL_H += $(PYRAMID_ACCEL_CALIBRATION_TP_DIR)/pyramid_accel_calibration_cli.h
    
    # code style check index
    #https://habr.com/ru/articles/843746/
    
    SOURCES_CODE_STYLE_C += $(PYRAMID_ACCEL_CALIBRATION_TP_DIR)/pyramid_accel_calibration.c
    SOURCES_CODE_STYLE_H += $(PYRAMID_ACCEL_CALIBRATION_TP_DIR)/pyramid_accel_calibration.h
    
    SOURCES_CODE_STYLE_C += $(PYRAMID_ACCEL_CALIBRATION_TP_DIR)/pyramid_accel_calibration_configuration.c
    SOURCES_CODE_STYLE_H += $(PYRAMID_ACCEL_CALIBRATION_TP_DIR)/pyramid_accel_calibration_configuration.h
   
    SOURCES_CODE_STYLE_H += $(PYRAMID_ACCEL_CALIBRATION_TP_DIR)/pyramid_accel_calibration_constants.h
    SOURCES_CODE_STYLE_H += $(PYRAMID_ACCEL_CALIBRATION_TP_DIR)/pyramid_accel_calibration_types.h
    SOURCES_CODE_STYLE_H += $(PYRAMID_ACCEL_CALIBRATION_TP_DIR)/pyramid_accel_calibration_dependencies.h
    
    
endif