
ifneq ($(TEST_CRC_MK_INC),Y)
    TEST_CRC_MK_INC=Y

    TEST_CRC_DIR = $(TEST_SET_SW_DIR)/test_crc
    #@echo $(error TEST_CRC_DIR= $(TEST_CRC_DIR))
    
    INCDIR += -I$(TEST_CRC_DIR)
    OPT += -DHAS_TEST_SUIT_CRC
    OPT += -DHAS_TEST_CRC
    
    SOURCES_C += $(TEST_CRC_DIR)/test_crc.c
endif