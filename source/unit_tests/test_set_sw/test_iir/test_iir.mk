$(info TEST_IIR_MK_INC=$(TEST_IIR_MK_INC))

ifneq ($(TEST_IIR_MK_INC),Y)
    TEST_IIR_MK_INC=Y

    TEST_IIR_DIR = $(TEST_SET_SW_DIR)/test_iir

    #@echo $(error TEST_IIR_DIR= $(TEST_IIR_DIR))
    INCDIR  += -I$(TEST_IIR_DIR)

    OPT += -DHAS_TEST_SUIT_IIR
    OPT += -DHAS_TEST_IIR

    SOURCES_C += $(TEST_IIR_DIR)/test_iir.c
endif
