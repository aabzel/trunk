
mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
$(info Build  $(mkfile_path) )

UBX_PROTO_DIR = $(WORKSPACE_LOC)protocols/ubx_protocol
#@ echo $(error UBX_PROTO_DIR = $(UBX_PROTO_DIR)) 
#@ echo $(error CFLAGS = $(CFLAGS))

INCDIR += -I$(UBX_PROTO_DIR)

SOURCES_C += $(UBX_PROTO_DIR)/ubx_protocol.c
SOURCES_C += $(UBX_PROTO_DIR)/ubx_diag.c
