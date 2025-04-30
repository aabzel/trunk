$(info TEST_DISK_MK_INC=$(TEST_DISK_MK_INC))
ifneq ($(TEST_DISK_MK_INC),Y)
    TEST_DISK_MK_INC=Y


    TEST_DISK_DIR = $(TEST_SET_HW_DIR)/test_disk
    #@echo $(error TEST_DISK_DIR=$(TEST_DISK_DIR))

    INCDIR += -I$(TEST_DISK_DIR)
    OPT += -DHAS_TEST_DISK
    SOURCES_C += $(TEST_DISK_DIR)/test_disk.c
endif