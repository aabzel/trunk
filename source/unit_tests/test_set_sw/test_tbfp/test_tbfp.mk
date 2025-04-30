ifneq ($(TEST_TBFP_MK_INC),Y)
    TEST_TBFP_MK_INC=Y

    TEST_TBFP_DIR = $(TEST_SET_SW_DIR)/test_tbfp
    #@echo $(error TEST_TBFP_DIR= $(TEST_TBFP_DIR))
    
    INCDIR += -I$(TEST_TBFP_DIR)
    OPT += -DHAS_TEST_SUIT_TBFP
    OPT += -DHAS_TEST_TBFP
    
    SOURCES_C += $(TEST_TBFP_DIR)/test_tbfp.c
endif
