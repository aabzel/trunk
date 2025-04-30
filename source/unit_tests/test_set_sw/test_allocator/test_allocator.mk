
$(info TEST_ALLOCATOR_MK_INC=$(TEST_ALLOCATOR_MK_INC))

ifneq ($(TEST_ALLOCATOR_MK_INC),Y)
    TEST_ALLOCATOR_MK_INC=Y
    
    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path))
    
    TEST_ALLOCATOR_DIR = $(TEST_SET_SW_DIR)/test_allocator
    #@echo $(error TEST_ALLOCATOR_DIR=$(TEST_ALLOCATOR_DIR))
    INCDIR += -I$(TEST_ALLOCATOR_DIR)
    OPT += -DHAS_TEST_HEAP
    OPT += -DHAS_TEST_SUIT_ALLOCATOR
    OPT += -DHAS_TEST_ALLOCATOR
    SOURCES_C += $(TEST_ALLOCATOR_DIR)/test_allocator.c
endif
