ifneq ($(ISO_TP_MK),Y)
    ISO_TP_MK=Y

    $(info Build  ISO_TP )

    ISO_TP_PROTOCOL_DIR = $(PROTOCOLS_DIR)/iso_tp
    #@ echo $(error ISO_TP_PROTOCOL_DIR = $(ISO_TP_PROTOCOL_DIR)) 
    #@ echo $(error CFLAGS = $(CFLAGS))
    OPT += -DHAS_ISO_TP
    OPT += -DHAS_ISO_TP_PROC

    INCDIR += -I$(ISO_TP_PROTOCOL_DIR)

    SOURCES_C +=$(ISO_TP_PROTOCOL_DIR)/iso_tp.c

    ifeq ($(DIAG),Y)
        ifeq ($(ISO_TP_DIAG),Y)
            OPT += -DHAS_ISO_TP_DIAG
            SOURCES_C +=$(ISO_TP_PROTOCOL_DIR)/iso_tp_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(ISO_TP_COMMANDS),Y)
            OPT += -DHAS_ISO_TP_COMMANDS
            SOURCES_C +=$(ISO_TP_PROTOCOL_DIR)/iso_tp_commands.c
        endif
    endif
endif
