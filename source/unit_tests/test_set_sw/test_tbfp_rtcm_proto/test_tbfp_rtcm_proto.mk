    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )TEST_TBFP_RTCM_DIR = $(WORKSPACE_LOC)unit_tests/test_set_sw/test_tbfp_rtcm_proto
#@echo $(error TEST_TBFP_RTCM_DIR= $(TEST_TBFP_RTCM_DIR))
#@echo $(error CFLAGS= $(CFLAGS))

INCDIR += -I$(TEST_TBFP_RTCM_DIR)

SOURCES_C += $(TEST_TBFP_RTCM_DIR)/test_tbfp_rtcm_proto.c