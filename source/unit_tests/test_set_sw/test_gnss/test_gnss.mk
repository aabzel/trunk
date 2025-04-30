
$(info TEST_GNSS_MK_INC=$(TEST_GNSS_MK_INC))

ifneq ($(TEST_GNSS_MK_INC),Y)
    TEST_GNSS_MK_INC=Y

    TEST_GNSS_DIR = $(TEST_SET_SW_DIR)/test_gnss
    #@echo $(error TEST_GNSS_DIR=$(TEST_GNSS_DIR))
    INCDIR += -I$(TEST_GNSS_DIR)
    OPT += -DHAS_TEST_GNSS
    OPT += -DHAS_TEST_SUIT_GNSS

    SOURCES_C += $(TEST_GNSS_DIR)/test_gnss.c
endif
