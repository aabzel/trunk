ifneq ($(CALIBRATION_DATA_MK_INC),Y)
    CALIBRATION_DATA_MK_INC=Y

    CALIBRATION_DATA_DIR = $(STORAGE_DIR)/calibration_data
    #@ echo $(error CALIBRATION_DATA_DIR = $(CALIBRATION_DATA_DIR))
    #@ echo $(error CFLAGS = $(CFLAGS)) 
    OPT += -DHAS_CALIBRATION_DATA

    INCDIR += -I$(CALIBRATION_DATA_DIR)


    SOURCES_C += $(CALIBRATION_DATA_DIR)/calibration_data.c

    ifeq ($(DIAG),Y)
        ifeq ($(CALIBRATION_DATA_DIAG),Y)
            OPT += -DHAS_CALIBRATION_DATA_DIAG
            SOURCES_C += $(CALIBRATION_DATA_DIR)/calibration_data_diag.c
        endif
    endif

    ifeq ($(CALIBRATION_DATA_WRITE),Y)
        #@echo $(error CALIBRATION_DATA_WRITE = $(CALIBRATION_DATA_WRITE)) 
        OPT += -DHAS_CALIBRATION_DATA_WRITE
    endif

    ifeq ($(CLI),Y)
        ifeq ($(CALIBRATION_DATA_COMMANDS),Y)
            OPT += -DHAS_CALIBRATION_DATA_COMMANDS
            SOURCES_C += $(CALIBRATION_DATA_DIR)/calibration_data_commands.c
        endif
    endif
endif


