$(info TEST_CAN_FD_MK_INC=$(TEST_CAN_FD_MK_INC))
ifneq ($(TEST_CAN_FD_MK_INC),Y)
    TEST_CAN_FD_MK_INC=Y

    TEST_CAN_FD_DIR = $(TEST_SET_HW_DIR)/test_can_fd

    # $(error TEST_CAN_FD_DIR=$(TEST_CAN_FD_DIR))
    INCDIR += -I$(TEST_CAN_FD_DIR)

    OPT += -DHAS_TEST_CAN_FD

    SOURCES_C += $(TEST_CAN_FD_DIR)/test_can_fd.c
endif