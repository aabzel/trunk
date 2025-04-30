    
    
    TEST_IWDG_DIR = $(TEST_SET_HW_DIR)/test_iwdg
#@echo $(error TEST_IWDG_DIR=$(TEST_IWDG_DIR))
INCDIR += -I$(TEST_IWDG_DIR)

OPT += -DHAS_TEST_IWDG

SOURCES_C += $(TEST_IWDG_DIR)/test_iwdg.c

