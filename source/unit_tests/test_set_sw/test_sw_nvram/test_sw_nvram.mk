
ifneq ($(TEST_SW_NVRAM_MK_INC),Y)
    TEST_SW_NVRAM_MK_INC=Y
    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path))

    TEST_SW_NVRAM_DIR = $(TEST_SET_SW_DIR)/test_sw_nvram
    #@echo $(error TEST_SW_NVRAM_DIR= $(TEST_SW_NVRAM_DIR))
    
    INCDIR += -I$(TEST_SW_NVRAM_DIR)
    OPT += -DHAS_TEST_SUIT_SW_NVRAM
    OPT += -DHAS_TEST_SW_NVRAM
    
    SOURCES_C += $(TEST_SW_NVRAM_DIR)/test_sw_nvram.c
endif