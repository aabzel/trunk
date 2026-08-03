$(info TEST_M_SEQ_MK_INC=$(TEST_M_SEQ_MK_INC))
ifneq ($(TEST_M_SEQ_MK_INC),Y)
    TEST_M_SEQ_MK_INC=Y
    TEST_M_SEQ_DIR = $(TEST_SET_SW_DIR)/test_m_seq
    # $(error TEST_M_SEQ_DIR= $(TEST_M_SEQ_DIR))
    MCAL_OPT += -DHAS_TEST_SUIT_M_SEQ
    MCAL_OPT += -DHAS_TEST_M_SEQ
    INCDIR  += -I$(TEST_M_SEQ_DIR)
    SOURCES_C += $(TEST_M_SEQ_DIR)/test_m_seq.c
endif
