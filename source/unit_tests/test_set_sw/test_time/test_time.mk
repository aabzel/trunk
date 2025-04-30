ifneq ($(TEST_TIME_MK),Y)
    TEST_TIME_MK=Y

    $(info Add Time tests)

    TEST_TIME_DIR = $(TEST_SET_SW_DIR)/test_time
    #@echo $(error TEST_TIME_DIR= $(TEST_TIME_DIR))
    #@echo $(error CFLAGS= $(CFLAGS))

    INCDIR += -I$(TEST_TIME_DIR)

    OPT += -DHAS_TEST_SUIT_UTILS_TIME
    OPT += -DHAS_TEST_UTILS_TIME
    OPT += -DHAS_TEST_TIME

    SOURCES_C += $(TEST_TIME_DIR)/test_time_utils.c

endif

