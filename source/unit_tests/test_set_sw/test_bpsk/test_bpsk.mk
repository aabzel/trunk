$(info TEST_BPSK_MK_INC=$(TEST_BPSK_MK_INC))

ifneq ($(TEST_BPSK_MK_INC),Y)
    TEST_BPSK_MK_INC=Y

    TEST_BPSK_DIR = $(TEST_SET_SW_DIR)/test_bpsk
    #@echo $(error TEST_BPSK_DIR= $(TEST_BPSK_DIR))
    INCDIR  += -I$(TEST_BPSK_DIR)

    OPT += -DHAS_TEST_SUIT_BPSK

    SOURCES_C += $(TEST_BPSK_DIR)/test_bpsk.c
endif
