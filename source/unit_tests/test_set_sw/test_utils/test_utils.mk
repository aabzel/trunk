ifneq ($(TEST_UTILS_MK),Y)
    TEST_UTILS_MK=Y
    TEST_UTILS_DIR = $(TEST_SET_SW_DIR)/test_utils
    #@echo $(error TEST_UTILS_DIR= $(TEST_UTILS_DIR))
    #@echo $(error CFLAGS= $(CFLAGS))
    $(info + Utils Test)
    INCDIR += -I$(TEST_UTILS_DIR)

    OPT += -DHAS_TEST_SUIT_UTILS

    SOURCES_C += $(TEST_UTILS_DIR)/bit_utils_test.c
    SOURCES_C += $(TEST_UTILS_DIR)/byte_utils_test.c
    SOURCES_C += $(TEST_UTILS_DIR)/data_utils_test.c
    SOURCES_C += $(TEST_UTILS_DIR)/test_system.c

    ifeq ($(TEST_FLOAT),Y)
        # $(error TEST_FLOAT=$(TEST_FLOAT))
        OPT += -DHAS_TEST_SUIT_FLOAT
        SOURCES_C += $(TEST_UTILS_DIR)/float_utils_test.c
    endif

endif