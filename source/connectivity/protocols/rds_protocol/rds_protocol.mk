ifneq ($(RDS_PROTOCOL_MK_INC),Y)
    RDS_PROTOCOL_MK_INC=Y

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )
    RDS=Y
    OPT += -DHAS_RDS
    RDS_PROTO_DIR = $(PROTOCOLS_DIR)/rds_protocol
    #@ echo $(error RDS_PROTO_DIR = $(RDS_PROTO_DIR)) 
    #@ echo $(error CFLAGS = $(CFLAGS))

    INCDIR += -I$(RDS_PROTO_DIR)
    ifeq ($(CLI),Y)
        ifeq ($(RDS_COMMANDS),Y)
            OPT += -DHAS_RDS_COMMANDS
            SOURCES_C += $(RDS_PROTO_DIR)/rds_commands.c
        endif
    endif

    SOURCES_C += $(RDS_PROTO_DIR)/rds_protocol.c
    SOURCES_C += $(RDS_PROTO_DIR)/rds_diag.c
endif