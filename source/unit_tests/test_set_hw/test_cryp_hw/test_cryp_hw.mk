ifneq ($(TEST_CRYP_HW_MK_INC),Y)
    TEST_CRYP_HW_MK_INC=Y


    TEST_CRYP_HW_DIR = $(TEST_SET_HW_DIR)/test_cryp_hw
    #@echo $(error TEST_CRYP_HW_DIR=$(TEST_CRYP_HW_DIR))
    INCDIR += -I$(TEST_CRYP_HW_DIR)

    OPT += -DHAS_TEST_CRYP_HW

    SOURCES_C += $(TEST_CRYP_HW_DIR)/test_cryp_hw.c
endif