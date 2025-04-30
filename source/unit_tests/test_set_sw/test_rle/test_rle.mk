$(info TEST_RLE_MK_INC=$(TEST_RLE_MK_INC))

ifneq ($(TEST_RLE_MK_INC),Y)
    TEST_RLE_MK_INC=Y


    ifneq ($(RLE),Y)
        @echo $(error +RLE)
    endif

    TEST_RLE_DIR = $(TEST_SET_SW_DIR)/test_rle
    #@echo $(error TEST_RLE_DIR= $(TEST_RLE_DIR))

    OPT += -DHAS_TEST_SUIT_RLE
    INCDIR  += -I$(TEST_RLE_DIR)

    SOURCES_C += $(TEST_RLE_DIR)/test_rle.c
endif
