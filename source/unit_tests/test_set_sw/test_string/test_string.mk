
$(info TEST_STRING_MK_INC=$(TEST_STRING_MK_INC))

ifneq ($(TEST_STRING_MK_INC),Y)
    TEST_STRING_MK_INC=Y

    ifneq ($(STRING),Y)
        @echo $(error +STRING)
    endif

    TEST_STRING_DIR = $(TEST_SET_SW_DIR)/test_string
    #@echo $(error TEST_STRING_DIR= $(TEST_STRING_DIR))

    OPT += -DHAS_TEST_SUIT_STRING_UTILS
    OPT += -DHAS_TEST_SUIT_STRING
    OPT += -DHAS_TEST_SUIT_CONVERT
    OPT += -DHAS_TEST_STRING
    INCDIR  += -I$(TEST_STRING_DIR)

    SOURCES_C += $(TEST_STRING_DIR)/test_convert.c
    SOURCES_C += $(TEST_STRING_DIR)/test_string_utils.c
endif
