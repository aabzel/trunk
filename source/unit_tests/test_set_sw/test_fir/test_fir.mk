$(info TEST_FIR_MK_INC=$(TEST_FIR_MK_INC))

ifneq ($(TEST_FIR_MK_INC),Y)
    TEST_FIR_MK_INC=Y

    ifneq ($(FIR),Y)
        @echo $(error +FIR)
    endif

    TEST_FIR_DIR = $(TEST_SET_SW_DIR)/test_fir
    #@echo $(error TEST_FIR_DIR= $(TEST_FIR_DIR))

    OPT += -DHAS_TEST_SUIT_FIR
    OPT += -DHAS_TEST_FIR
    INCDIR  += -I$(TEST_FIR_DIR)

    SOURCES_C += $(TEST_FIR_DIR)/test_fir.c
endif
