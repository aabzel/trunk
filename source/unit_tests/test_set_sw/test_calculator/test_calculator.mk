mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
$(info Build  $(mkfile_path) )

TEST_CALCULATOR_DIR = $(TEST_SET_SW_DIR)/test_calculator
#@echo $(error TEST_CALCULATOR_DIR= $(TEST_CALCULATOR_DIR))
#@echo $(error CFLAGS= $(CFLAGS))

OPT += -DHAS_TEST_SUIT_CALCULATOR
OPT += -DHAS_TEST_CALCULATOR
INCDIR  += -I$(TEST_CALCULATOR_DIR)

SOURCES_C += $(TEST_CALCULATOR_DIR)/test_calculator.c

