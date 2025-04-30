ifneq ($(PROTOCOL_GENERAL_MK),Y)
    PROTOCOL_GENERAL_MK=Y

    PROTOCOL_GENERAL_DIR = $(PROTOCOLS_DIR)/protocol
    #@echo $(error PROTOCOL_DIR=$(PROTOCOL_GENERAL_DIR))

    OPT += -DHAS_PROTOCOL

    ifeq ($(PROTOCOL_EXT),Y)
        OPT += -DHAS_PROTOCOL_EXT
    endif

    INCDIR += -I$(PROTOCOL_GENERAL_DIR)

    SOURCES_C += $(PROTOCOL_GENERAL_DIR)/protocol.c

    ifeq ($(PROTOCOL_DIAG),Y)
        OPT += -DHAS_PROTOCOL_DIAG
        SOURCES_C += $(PROTOCOL_GENERAL_DIR)/protocol_diag.c
    endif
endif