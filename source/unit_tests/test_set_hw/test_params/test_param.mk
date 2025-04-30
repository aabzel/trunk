    
    TEST_PARAM_DIR = $(TEST_SET_HW_DIR)/test_params
#@echo $(error TEST_PARAM_DIR=$(TEST_PARAM_DIR))
INCDIR += -I$(TEST_PARAM_DIR)

OPT += -DHAS_TEST_PARAM

SOURCES_C += $(TEST_PARAM_DIR)/test_params.c

