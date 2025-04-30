ifneq ($(TEST_KEYBOARD_MK_INC),Y)
    TEST_KEYBOARD_MK_INC=Y

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )

    TEST_KEYBOARD_DIR = $(TEST_SET_SW_DIR)/test_keyboard
    #TEST_KEYBOARD_DIR = $(TEST_SET_SW_DIR)/test_keyboard

    #@echo $(error TEST_KEYBOARD_DIR=$(TEST_KEYBOARD_DIR))

    OPT += -DHAS_TEST_SUIT_KEYBOARD
    OPT += -DHAS_TEST_KEYBOARD

    INCDIR += -I$(TEST_KEYBOARD_DIR)
    SOURCES_C += $(TEST_KEYBOARD_DIR)/test_keyboard.c
endif