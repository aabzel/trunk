ifneq ($(TEST_CALIBRATION_DATA_MK_INC),Y)
    TEST_CALIBRATION_DATA_MK_INC=Y

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )
    
    TEST_CALIBRATION_DATA_DIR = $(TEST_SET_SW_DIR)/test_calibration_data
    #TEST_CALIBRATION_DATA_DIR = $(TEST_SET_SW_DIR)/test_calibration_data
   
    #@echo $(error TEST_CALIBRATION_DATA_DIR=$(TEST_CALIBRATION_DATA_DIR))

    OPT += -DHAS_TEST_SUIT_CALIBRATION_DATA
    OPT += -DHAS_TEST_CALIBRATION_DATA

    INCDIR += -I$(TEST_CALIBRATION_DATA_DIR)
    SOURCES_C += $(TEST_CALIBRATION_DATA_DIR)/test_calibration_data.c
endif