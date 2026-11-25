$(info TEST_CORE_MK_INC=$(TEST_CORE_MK_INC) )
ifneq ($(TEST_CORE_MK_INC),Y)
    TEST_CORE_MK_INC=Y
    TEST_CORE_DIR = $(TEST_SET_HW_DIR)/test_core
    # $(error TEST_CORE_DIR=$(TEST_CORE_DIR))
    INCDIR += -I$(TEST_CORE_DIR)

    MCAL_OPT += -DHAS_TEST_CORE
    SOURCES_C += $(TEST_CORE_DIR)/test_core.c
endif