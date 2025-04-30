mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
$(info Build  $(mkfile_path) )

TEST_LIFO_DIR = $(TEST_SET_SW_DIR)/test_lifo
#@echo $(error TEST_LIFO_DIR= $(TEST_LIFO_DIR))
#@echo $(error CFLAGS= $(CFLAGS))

INCDIR += -I$(TEST_LIFO_DIR)

OPT += -DHAS_TEST_SUIT_LIFO
SOURCES_C += $(TEST_LIFO_DIR)/test_lifo_array.c
SOURCES_C += $(TEST_LIFO_DIR)/test_lifo_indexer.c
