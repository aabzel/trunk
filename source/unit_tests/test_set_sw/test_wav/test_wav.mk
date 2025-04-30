ifneq ($(TEST_WAV_MK_INC),Y)
    TEST_WAV_MK_INC=Y

    TEST_WAV_DIR = $(TEST_SET_SW_DIR)/test_wav
    #TEST_WAV_DIR = $(TEST_SET_SW_DIR)/test_wav
    INCDIR += -I$(TEST_WAV_DIR)

    #@echo $(error TEST_WAV_DIR=$(TEST_WAV_DIR))

    OPT += -DHAS_TEST_SUIT_WAV
    OPT += -DHAS_TEST_WAV

    SOURCES_C += $(TEST_WAV_DIR)/test_wav.c
endif