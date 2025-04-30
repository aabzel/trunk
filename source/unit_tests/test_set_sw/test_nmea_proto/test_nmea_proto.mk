    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )TEST_NMEA_DIR = $(WORKSPACE_LOC)unit_tests/test_set_sw/test_nmea_proto
#@echo $(error TEST_NMEA_DIR= $(TEST_NMEA_DIR))
#@echo $(error CFLAGS= $(CFLAGS))

INCDIR += -I$(TEST_NMEA_DIR)

SOURCES_C += $(TEST_NMEA_DIR)/test_nmea_proto.c