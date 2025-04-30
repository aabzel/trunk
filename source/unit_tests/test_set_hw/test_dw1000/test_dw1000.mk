$(info TEST_DW1000_MK_INC=$(TEST_DW1000_MK_INC) )
ifneq ($(TEST_DW1000_MK_INC),Y)
    TEST_DW1000_MK_INC=Y

    $(info + dw1000 tests)
    TEST_DW1000_DIR = $(TEST_SET_HW_DIR)/test_dw1000

    #@echo $(error TEST_DW1000_DIR=$(TEST_DW1000_DIR))
    INCDIR += -I$(TEST_DW1000_DIR)

    OPT += -DHAS_TEST_DW1000
    SOURCES_C += $(TEST_DW1000_DIR)/test_dw1000.c

    ifeq ($(TEST_DW1000_GPIO),Y)
        OPT += -DHAS_TEST_DW1000_GPIO
        SOURCES_C += $(TEST_DW1000_DIR)/test_dw1000_gpio.c
    endif
endif
