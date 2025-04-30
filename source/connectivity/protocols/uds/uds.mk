ifneq ($(UDS_MK),Y)
    UDS_MK=Y

    $(info Build  UDS )

    UDS_PROTOCOL_DIR = $(PROTOCOLS_DIR)/uds
    #@ echo $(error UDS_PROTOCOL_DIR = $(UDS_PROTOCOL_DIR)) 
    #@ echo $(error CFLAGS = $(CFLAGS))
    OPT += -DHAS_UDS
    OPT += -DHAS_UDS_PROC

    INCDIR += -I$(UDS_PROTOCOL_DIR)

    SOURCES_C +=$(UDS_PROTOCOL_DIR)/uds.c

    ifeq ($(DIAG),Y)
        ifeq ($(UDS_DIAG),Y)
            OPT += -DHAS_UDS_DIAG
            SOURCES_C +=$(UDS_PROTOCOL_DIR)/uds_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(UDS_COMMANDS),Y)
            OPT += -DHAS_UDS_COMMANDS
            SOURCES_C +=$(UDS_PROTOCOL_DIR)/uds_commands.c
        endif
    endif
endif
