ifneq ($(TBFP_PROTOCOL_MK),Y)
    TBFP_PROTOCOL_MK=Y
    $(info Build TBFP)

    TBFP_PROTOCOL_DIR = $(PROTOCOLS_DIR)/tbfp_protocol
    # $(error TBFP_PROTOCOL_DIR = $(TBFP_PROTOCOL_DIR)) 

    INCDIR += -I$(TBFP_PROTOCOL_DIR)

    OPT += -DHAS_TBFP
    OPT += -DHAS_TBFP_PROC

    ifeq ($(TBFP_ACK),Y)
        OPT += -DHAS_TBFP_ACK
    endif

    ifeq ($(TBFP_EXT),Y)
        OPT += -DHAS_TBFP_EXT
    endif

    ifeq ($(TBFP_FLOW_CONTROL),Y)
        OPT += -DHAS_TBFP_FLOW_CONTROL
    endif

    ifeq ($(TBFP_RETRANSMIT),Y)
        OPT += -DHAS_TBFP_RETRANSMIT
        ifeq ($(TBFP_DIAG),Y)
            SOURCES_DIAG_C +=$(TBFP_PROTOCOL_DIR)/tbfp_retx_diag.c
        endif
    endif

    SOURCES_C +=$(TBFP_PROTOCOL_DIR)/tbfp.c
    SOURCES_C +=$(TBFP_PROTOCOL_DIR)/tbfp_isr.c
    SOURCES_C +=$(TBFP_PROTOCOL_DIR)/tbfp_protocol_parser.c


    ifeq ($(DIAG),Y)
        ifeq ($(TBFP_DIAG),Y)
            OPT += -DHAS_TBFP_DIAG
            SOURCES_DIAG_C +=$(TBFP_PROTOCOL_DIR)/tbfp_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(TBFP_COMMANDS),Y)
            OPT += -DHAS_TBFP_COMMANDS
            SOURCES_C +=$(TBFP_PROTOCOL_DIR)/tbfp_commands.c
        endif
    endif
endif
