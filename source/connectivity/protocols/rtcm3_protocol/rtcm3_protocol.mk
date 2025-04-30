
mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
$(info Build  $(mkfile_path) )

RTCM3_PROTOCOL_DIR = $(WORKSPACE_LOC)protocols/rtcm3_protocol
#@ echo $(error RTCM3_PROTOCOL_DIR = $(RTCM3_PROTOCOL_DIR)) 
#@ echo $(error CFLAGS = $(CFLAGS))

INCDIR += -I$(RTCM3_PROTOCOL_DIR)

SOURCES_C +=$(RTCM3_PROTOCOL_DIR)/rtcm3_protocol.c
