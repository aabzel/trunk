ifneq ($(TEST_FFT_MK_INC),Y)
    TEST_FFT_MK_INC=Y

    TEST_FFT_DIR = $(TEST_SET_SW_DIR)/test_fft
    #@echo $(error TEST_FFT_DIR= $(TEST_FFT_DIR))
    #@echo $(error CFLAGS= $(CFLAGS))
    
    OPT += -DHAS_TEST_SUIT_FFT
    OPT += -DHAS_TEST_FFT
    
    INCDIR  += -I$(TEST_FFT_DIR)
    
    SOURCES_C += $(TEST_FFT_DIR)/test_fft.c


endif

