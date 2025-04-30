mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
$(info Build  $(mkfile_path) )

TEST_SHA256_DIR = $(TEST_SET_SW_DIR)/test_sha256
#@echo $(error TEST_SHA256_DIR= $(TEST_SHA256_DIR))
#@echo $(error CFLAGS= $(CFLAGS))

OPT += -DHAS_TEST_SUIT_SHA256
INCDIR  += -I$(TEST_SHA256_DIR)

SOURCES_C += $(TEST_SHA256_DIR)/test_sha256.c

