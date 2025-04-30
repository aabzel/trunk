    
TEST_I2C_DIR = $(TEST_SET_HW_DIR)/test_i2c
#@echo $(error TEST_I2C_DIR=$(TEST_I2C_DIR))
INCDIR += -I$(TEST_I2C_DIR)

OPT += -DHAS_TEST_I2C

SOURCES_C += $(TEST_I2C_DIR)/test_i2c.c

