
    
    TEST_UBLOX_PROTO_DIR = $(TEST_SET_SW_DIR)/test_ublox_proto
#@echo $(error TEST_UBLOX_PROTO_DIR= $(TEST_UBLOX_PROTO_DIR))
#@echo $(error CFLAGS= $(CFLAGS))

INCDIR += -I$(TEST_UBLOX_PROTO_DIR)

SOURCES_C += $(TEST_UBLOX_PROTO_DIR)/test_ublox_proto.c
