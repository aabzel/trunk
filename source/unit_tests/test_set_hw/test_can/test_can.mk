

$(info TEST_CAN_MK_INC=$(TEST_CAN_MK_INC))
ifneq ($(TEST_CAN_MK_INC),Y)
    TEST_CAN_MK_INC=Y

    TEST_CAN_DIR = $(TEST_SET_HW_DIR)/test_can

    #@echo $(error TEST_CAN_DIR=$(TEST_CAN_DIR))
    INCDIR += -I$(TEST_CAN_DIR)

    OPT += -DHAS_TEST_CAN

    SOURCES_C += $(TEST_CAN_DIR)/test_can.c
endif