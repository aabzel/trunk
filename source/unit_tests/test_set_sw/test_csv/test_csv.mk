$(info TEST_CSV_MK_INC=$(TEST_CSV_MK_INC))

ifneq ($(TEST_CSV_MK_INC),Y)
    TEST_CSV_MK_INC=Y

    CSV=Y

    TEST_CSV_DIR = $(TEST_SET_SW_DIR)/test_csv
    #@echo $(error TEST_CSV_DIR= $(TEST_CSV_DIR))

    OPT += -DHAS_TEST_SUIT_CSV
    OPT += -DHAS_TEST_CSV

    INCDIR  += -I$(TEST_CSV_DIR)

    SOURCES_C += $(TEST_CSV_DIR)/test_csv.c
endif
