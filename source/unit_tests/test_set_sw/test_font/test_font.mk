
ifneq ($(TEST_FONT_MK_INC),Y)
    TEST_FONT_MK_INC=Y

    $(info Build  $(mkfile_path) )
    TEST_FONT_DIR = $(TEST_SET_SW_DIR)/test_font
    #@echo $(error TEST_FONT_DIR= $(TEST_FONT_DIR))

    OPT += -DHAS_TEST_SUIT_FONT
    OPT += -DHAS_TEST_FONT

    INCDIR += -I$(TEST_FONT_DIR)
    SOURCES_C += $(TEST_FONT_DIR)/test_font.c
endif