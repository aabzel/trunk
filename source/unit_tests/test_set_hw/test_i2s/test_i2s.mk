
$(info TEST_I2S_MK_INC=$(TEST_I2S_MK_INC))

ifneq ($(TEST_I2S_MK_INC),Y)
    TEST_I2S_MK_INC=Y


    TEST_I2S_DIR = $(TEST_SET_HW_DIR)/test_i2s
    # $(error TEST_I2S_DIR=$(TEST_I2S_DIR))
    INCDIR += -I$(TEST_I2S_DIR)
    MCAL_OPT += -DHAS_TEST_I2S
    MCAL_OPT += -DHAS_I2S_TEST

    SOURCES_C += $(TEST_I2S_DIR)/test_i2s.c
    SOURCES_C += $(TEST_I2S_DIR)/test_i2s_dma.c
endif