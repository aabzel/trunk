ifneq ($(TEST_LIBC_MK),Y)
    TEST_LIBC_MK=Y
    
    TEST_LIBC_DIR = $(TEST_SET_SW_DIR)/test_libc
    #@echo $(error TEST_LIBC_DIR= $(TEST_LIBC_DIR))
    $(info + Utils Test)
    INCDIR += -I$(TEST_LIBC_DIR)
    OPT += -DHAS_TEST_SUIT_LIBC
    SOURCES_C += $(TEST_LIBC_DIR)/test_libc.c
endif