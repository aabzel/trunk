
$(info TEST_SPIFI_MK_INC=$(TEST_SPIFI_MK_INC))

ifneq ($(TEST_SPIFI_MK_INC),Y)
    TEST_SPIFI_MK_INC=Y

    TEST_SPIFI_DIR = $(TEST_SET_HW_DIR)/test_spifi
    #@echo $(error TEST_SPIFI_DIR=$(TEST_SPIFI_DIR))
    INCDIR += -I$(TEST_SPIFI_DIR)
    OPT += -DHAS_TEST_SPIFI

    SOURCES_C += $(TEST_SPIFI_DIR)/test_spifi.c
endif