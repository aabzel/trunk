
TEST_NVS_DIR = $(TEST_SET_HW_DIR)/test_nvs
#@echo $(error TEST_NVS_DIR=$(TEST_NVS_DIR))
INCDIR += -I$(TEST_NVS_DIR)

OPT += -DHAS_TEST_NVS

SOURCES_C += $(TEST_NVS_DIR)/test_nvs.c

