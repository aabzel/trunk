mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
$(info Build  $(mkfile_path))
    
TEST_MATH_DIR = $(TEST_SET_SW_DIR)/test_math
#@echo $(error TEST_MATH_DIR= $(TEST_MATH_DIR))
#@echo $(error CFLAGS= $(CFLAGS))

INCDIR += -I$(TEST_MATH_DIR)
OPT += -DHAS_TEST_SUIT_MATH
SOURCES_C += $(TEST_MATH_DIR)/test_math.c
