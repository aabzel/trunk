ifneq ($(TEST_KEEPASS_MK_INC),Y)
    TEST_KEEPASS_MK_INC=Y

    TEST_KEEPASS_DIR = $(TEST_SET_SW_DIR)/test_keepass
    #TEST_KEEPASS_DIR = $(TEST_SET_SW_DIR)/test_keepass
   
    #@echo $(error TEST_KEEPASS_DIR=$(TEST_KEEPASS_DIR))

    OPT += -DHAS_TEST_SUIT_KEEPASS

    INCDIR += -I$(TEST_KEEPASS_DIR)
    SOURCES_C += $(TEST_KEEPASS_DIR)/test_keepass.c
endif