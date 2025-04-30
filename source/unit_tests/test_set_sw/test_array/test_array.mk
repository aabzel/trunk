ifneq ($(TEST_ARRAY_MK),Y)
    TEST_ARRAY_MK=Y

    TEST_ARRAY_DIR = $(TEST_SET_SW_DIR)/test_array
    #@echo $(error TEST_ARRAY_DIR= $(TEST_ARRAY_DIR))
    $(info + Array Test)
    INCDIR += -I$(TEST_ARRAY_DIR)

    OPT += -DHAS_TEST_SUIT_ARRAY
    OPT += -DHAS_TEST_ARRAY

    SOURCES_C += $(TEST_ARRAY_DIR)/test_array.c

endif