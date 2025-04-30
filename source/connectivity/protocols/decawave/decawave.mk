ifneq ($(DECAWAVE_MK_INC),Y)
    DECAWAVE_MK_INC=Y

    DECAWAVE=Y
    OPT += -DHAS_DECAWAVE

    ifeq ($(DECAWAVE_SNIFFER),Y)
        OPT += -DHAS_DECAWAVE_SNIFFER
    endif

    DECAWAVE_PROTO_DIR = $(PROTOCOLS_DIR)/decawave
    INCDIR += -I$(DECAWAVE_PROTO_DIR)

    SOURCES_C += $(DECAWAVE_PROTO_DIR)/decawave.c

    ifeq ($(CLI),Y)
        ifeq ($(DECAWAVE_COMMANDS),Y)
            OPT += -DHAS_DECAWAVE_COMMANDS
            SOURCES_C += $(DECAWAVE_PROTO_DIR)/decawave_commands.c
        endif
    endif

    ifeq ($(DIAG),Y)
        OPT += -DHAS_DECAWAVE_DIAG
        SOURCES_C += $(DECAWAVE_PROTO_DIR)/decawave_diag.c
    endif
endif