ifneq ($(TEST_PASTILDA_MK_INC),Y)
    TEST_PASTILDA_MK_INC=Y

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )
    
    TEST_PASTILDA_DIR = $(TEST_SET_SW_DIR)/test_pastilda
    #TEST_PASTILDA_DIR = $(TEST_SET_SW_DIR)/test_pastilda
   
    #@echo $(error TEST_PASTILDA_DIR=$(TEST_PASTILDA_DIR))
             
    OPT += -DHAS_TEST_SUIT_PASTILDA

    INCDIR += -I$(TEST_PASTILDA_DIR)
    SOURCES_C += $(TEST_PASTILDA_DIR)/test_pastilda.c
endif