$(info TP_ACCELEROMETER_MK_INC=$(TP_ACCELEROMETER_MK_INC))

ifneq ($(TP_ACCELEROMETER_MK_INC),Y)
    TP_ACCELEROMETER_MK_INC=Y
    $(info Build EHAL ACCELEROMETER)
    ACCELEROMETER_EHAL=Y
    #@echo $(error WORKSPACE_LOC=$(WORKSPACE_LOC))
    TP_ACCELEROMETER_DIR = $(TP_SENSITIVITY_DIR)/accelerometer
    #@echo $(error TP_ACCELEROMETER_DIR=$(TP_ACCELEROMETER_DIR))

    INCDIR += -I$(TP_ACCELEROMETER_DIR)
    SOURCES_THIRD_PARTY_C+= $(TP_ACCELEROMETER_DIR)/accelerometer.c
    SOURCES_THIRD_PARTY_C+= $(TP_ACCELEROMETER_DIR)/accelerometer_configuration.c

    OPT += -DHAS_ACCEL
    ifeq ($(ACCELEROMETER_EHAL_PROC),Y)
        OPT += -DHAS_ACCEL_PROC
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(ACCELEROMETER_EHAL_DIAG),Y)
            OPT += -DHAS_ACCELEROMETER_EHAL_DIAG
            SOURCES_THIRD_PARTY_C+= $(TP_ACCELEROMETER_DIR)/accelerometer_diagnostic.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(ACCELEROMETER_EHAL_COMMANDS),Y)
            OPT += -DHAS_ACCELEROMETER_EHAL_COMMANDS
            SOURCES_THIRD_PARTY_C+= $(TP_ACCELEROMETER_DIR)/accelerometer_cli.c
        endif
    endif
    #@echo $(error ACCELEROMETER=$(ACCELEROMETER))

    SOURCES_EHAL_C+= $(TP_ACCELEROMETER_DIR)/accelerometer_cli.c
    SOURCES_EHAL_C+= $(TP_ACCELEROMETER_DIR)/accelerometer_configuration.c
    SOURCES_EHAL_C+= $(TP_ACCELEROMETER_DIR)/accelerometer_diagnostic.c
    SOURCES_EHAL_C+= $(TP_ACCELEROMETER_DIR)/accelerometer_driver.c

    SOURCES_EHAL_H += $(TP_ACCELEROMETER_DIR)/accelerometer_cli.h
    SOURCES_EHAL_H += $(TP_ACCELEROMETER_DIR)/accelerometer_configuration.h
    SOURCES_EHAL_H += $(TP_ACCELEROMETER_DIR)/accelerometer_diagnostic.h
    SOURCES_EHAL_H += $(TP_ACCELEROMETER_DIR)/accelerometer_driver.h

    # code style check index
    #https://habr.com/ru/articles/843746/

    SOURCES_CODE_STYLE_C += $(TP_ACCELEROMETER_DIR)/accelerometer.c
    SOURCES_CODE_STYLE_H += $(TP_ACCELEROMETER_DIR)/accelerometer.h

    SOURCES_CODE_STYLE_C += $(TP_ACCELEROMETER_DIR)/accelerometer_configuration.c
    SOURCES_CODE_STYLE_H += $(TP_ACCELEROMETER_DIR)/accelerometer_configuration.h

    SOURCES_CODE_STYLE_H += $(TP_ACCELEROMETER_DIR)/accelerometer_constants.h
    SOURCES_CODE_STYLE_H += $(TP_ACCELEROMETER_DIR)/accelerometer_dependencies.h
    SOURCES_CODE_STYLE_H += $(TP_ACCELEROMETER_DIR)/accelerometer_known_asics.h
    SOURCES_CODE_STYLE_H += $(TP_ACCELEROMETER_DIR)/accelerometer_type.h
endif