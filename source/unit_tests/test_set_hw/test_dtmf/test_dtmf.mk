
$(info TEST_DTMF_MK_INC=$(TEST_DTMF_MK_INC))

ifneq ($(TEST_DTMF_MK_INC),Y)
    TEST_DTMF_MK_INC=Y


    TEST_DTMF_DIR = $(TEST_SET_HW_DIR)/test_dtmf
    #@echo $(error TEST_DTMF_DIR=$(TEST_DTMF_DIR))
    INCDIR += -I$(TEST_DTMF_DIR)
    OPT += -DHAS_TEST_DTMF
    OPT += -DHAS_DTMF_TEST

    SOURCES_C += $(TEST_DTMF_DIR)/test_dtmf.c
endif