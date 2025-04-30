$(info TEST_BUTTON_MK_INC=$(TEST_BUTTON_MK_INC))

ifneq ($(TEST_BUTTON_MK_INC),Y)
    TEST_BUTTON_MK_INC=Y
    $(info + button test)
    TEST_BUTTON_DIR = $(TEST_SET_HW_DIR)/test_button
    #@echo $(error TEST_BUTTON=$(TEST_BUTTON))
    #@echo $(error TEST_BUTTON_DIR=$(TEST_BUTTON_DIR))
    INCDIR += -I$(TEST_BUTTON_DIR)

    OPT += -DHAS_TEST_BUTTON

    SOURCES_C += $(TEST_BUTTON_DIR)/test_button.c

endif