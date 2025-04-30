mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
$(info Build  $(mkfile_path) )

TEST_DS_TWR_DIR = $(TEST_SET_SW_DIR)/test_ds_twr
#@echo $(error TEST_DS_TWR_DIR= $(TEST_DS_TWR_DIR))
#@echo $(error CFLAGS= $(CFLAGS))

INCDIR += -I$(TEST_DS_TWR_DIR)

OPT += -DHAS_TEST_SUIT_DS_TWR
OPT += -DHAS_TEST_DS_TWR
SOURCES_C += $(TEST_DS_TWR_DIR)/test_ds_twr.c
