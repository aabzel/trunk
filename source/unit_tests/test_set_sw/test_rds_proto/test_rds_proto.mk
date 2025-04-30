mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
$(info Build  $(mkfile_path) )TEST_RDS_DIR = $(TEST_SET_SW_DIR)/test_rds_proto
#@echo $(error TEST_RDS_DIR= $(TEST_RDS_DIR))
#@echo $(error CFLAGS= $(CFLAGS))

INCDIR += -I$(TEST_RDS_DIR)
OPT += -DHAS_TEST_SUIT_RDS
SOURCES_C += $(TEST_RDS_DIR)/test_rds_proto.c