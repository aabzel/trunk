ifneq ($(TEST_HEX_BIN_MK_INC),Y)
    TEST_HEX_BIN_MK_INC=Y


    TEST_HEX_BIN_DIR = $(TEST_SET_SW_DIR)/test_hex_bin
    #@echo $(error TEST_HEX_BIN_DIR= $(TEST_HEX_BIN_DIR))
    OPT += -DHAS_TEST_SUIT_HEX_BIN
    OPT += -DHAS_TEST_HEX_BIN

    INCDIR += -I$(TEST_HEX_BIN_DIR)
    SOURCES_C += $(TEST_HEX_BIN_DIR)/test_hex_bin.c
endif