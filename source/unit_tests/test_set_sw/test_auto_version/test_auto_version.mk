ifneq ($(TEST_AUTO_VERSION_MK),Y)
    TEST_AUTO_VERSION_MK=Y

    $(info Add Time tests)
    
    TEST_AUTO_VERSION_DIR = $(TEST_SET_SW_DIR)/test_auto_version
    #@echo $(error TEST_AUTO_VERSION_DIR= $(TEST_AUTO_VERSION_DIR))
    #@echo $(error CFLAGS= $(CFLAGS))
    
    INCDIR += -I$(TEST_AUTO_VERSION_DIR)
    
    OPT += -DHAS_TEST_SUIT_AUTO_VERSION
    OPT += -DHAS_TEST_AUTO_VERSION
    
    SOURCES_C += $(TEST_AUTO_VERSION_DIR)/test_auto_version.c

endif

