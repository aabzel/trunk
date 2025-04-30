
$(info LIGHT_SENSOR_MK_INC=$(LIGHT_SENSOR_MK_INC))

ifneq ($(LIGHT_SENSOR_MK_INC),Y)
    LIGHT_SENSOR_MK_INC=Y

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build LIGHT_SENSOR)

    #FLASH_FS_DIR = $(WORKSPACE_LOC)Drivers/flash_fs
    #@echo $(error WORKSPACE_LOC=$(WORKSPACE_LOC))
    LIGHT_SENSOR_DIR = $(SENSITIVITY_DIR)/light_sensor
    #@echo $(error LIGHT_SENSOR_DIR=$(LIGHT_SENSOR_DIR))

    ifneq ($(LIGHT_SENSOR),Y)
        @echo $(error Add General LIGHT_SENSOR driver)
    endif

    INCDIR += -I$(LIGHT_SENSOR_DIR)
    SOURCES_C += $(LIGHT_SENSOR_DIR)/light_sensor_drv.c

    OPT += -DHAS_LIGHT_SENSOR

    ifeq ($(DIAG),Y)
        ifeq ($(LIGHT_SENSOR_DIAG),Y)
            OPT += -DHAS_LIGHT_SENSOR_DIAG
            SOURCES_C += $(LIGHT_SENSOR_DIR)/light_sensor_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(LIGHT_SENSOR_COMMANDS),Y)
            OPT += -DHAS_LIGHT_SENSOR_COMMANDS
            SOURCES_C += $(LIGHT_SENSOR_DIR)/light_sensor_commands.c
        endif
    endif
    #@echo $(error LIGHT_SENSOR=$(LIGHT_SENSOR))
endif