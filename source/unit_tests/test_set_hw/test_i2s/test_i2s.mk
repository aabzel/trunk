
$(info TEST_I2S_MK_INC=$(TEST_I2S_MK_INC))

ifneq ($(TEST_I2S_MK_INC),Y)
    TEST_I2S_MK_INC=Y


    TEST_I2S_DIR = $(TEST_SET_HW_DIR)/test_i2s
    #@echo $(error TEST_I2S_DIR=$(TEST_I2S_DIR))
    INCDIR += -I$(TEST_I2S_DIR)
    OPT += -DHAS_TEST_I2S
    OPT += -DHAS_I2S_TEST

    SOURCES_C += $(TEST_I2S_DIR)/test_i2s.c
endif