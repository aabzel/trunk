
ifneq ($(TEST_DFT_MK_INC),Y)
    TEST_DFT_MK_INC=Y

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )
    
    TEST_DFT_DIR = $(TEST_SET_SW_DIR)/test_dft
    #@echo $(error TEST_DFT_DIR= $(TEST_DFT_DIR))
    #@echo $(error CFLAGS= $(CFLAGS))
    
    OPT += -DHAS_TEST_SUIT_DFT
    OPT += -DHAS_TEST_DFT
    
    INCDIR  += -I$(TEST_DFT_DIR)
    
    SOURCES_C += $(TEST_DFT_DIR)/test_dft.c


endif

