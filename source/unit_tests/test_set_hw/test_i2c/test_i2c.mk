$(info TEST_I2C_MK_INC=$(TEST_I2C_MK_INC))
ifneq ($(TEST_I2C_MK_INC),Y)
    TEST_I2C_MK_INC=Y

    TEST_I2C_DIR = $(TEST_SET_HW_DIR)/test_i2c
    #@echo $(error TEST_I2C_DIR=$(TEST_I2C_DIR))
    INCDIR += -I$(TEST_I2C_DIR)
    MCAL_OPT += -DHAS_TEST_I2C
    MCAL_OPT += -DHAS_I2C_TEST

    SOURCES_C += $(TEST_I2C_DIR)/test_i2c.c
endif
