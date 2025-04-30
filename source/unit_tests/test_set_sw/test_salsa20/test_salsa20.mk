mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
$(info Build  $(mkfile_path))

TEST_SALSA20_DIR = $(TEST_SET_SW_DIR)/test_salsa20
#@echo $(error TEST_SALSA20_DIR= $(TEST_SALSA20_DIR))
#@echo $(error CFLAGS= $(CFLAGS))

OPT += -DHAS_TEST_SUIT_SALSA20
INCDIR  += -I$(TEST_SALSA20_DIR)

SOURCES_C += $(TEST_SALSA20_DIR)/test_salsa20.c

