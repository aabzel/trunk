mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
$(info Build  $(mkfile_path) )

TEST_AES256_DIR = $(TEST_SET_SW_DIR)/test_aes
#@echo $(error TEST_AES256_DIR= $(TEST_AES256_DIR))
#@echo $(error CFLAGS= $(CFLAGS))
         
OPT += -DHAS_TEST_SUIT_AES256
INCDIR  += -I$(TEST_AES256_DIR)

SOURCES_C += $(TEST_AES256_DIR)/test_aes.c

