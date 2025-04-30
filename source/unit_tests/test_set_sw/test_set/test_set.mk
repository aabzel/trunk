mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
$(info Build  $(mkfile_path))

TEST_SET_DIR = $(TEST_SET_SW_DIR)/test_set
#@echo $(error TEST_SET_DIR= $(TEST_SET_DIR))
#@echo $(error CFLAGS= $(CFLAGS))

INCDIR += -I$(TEST_SET_DIR)

OPT += -DHAS_TEST_SUIT_SET
SOURCES_C += $(TEST_SET_DIR)/test_set.c
