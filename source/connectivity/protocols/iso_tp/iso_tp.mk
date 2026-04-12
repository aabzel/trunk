ifneq ($(ISO_TP_MK),Y)
    ISO_TP_MK=Y

    ISO_TP_PROTOCOL_DIR = $(PROTOCOLS_DIR)/iso_tp
    # $(error ISO_TP_PROTOCOL_DIR = $(ISO_TP_PROTOCOL_DIR)) 

    MCAL_OPT += -DHAS_ISO_TP
    MCAL_OPT += -DHAS_ISO_TP_PROC

    INCDIR += -I$(ISO_TP_PROTOCOL_DIR)

    SOURCES_C +=$(ISO_TP_PROTOCOL_DIR)/iso_tp_mcal.c

    ifeq ($(DIAG),Y)
        ifeq ($(ISO_TP_DIAG),Y)
            MCAL_OPT += -DHAS_ISO_TP_DIAG
            SOURCES_DIAG_C +=$(ISO_TP_PROTOCOL_DIR)/iso_tp_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(ISO_TP_COMMANDS),Y)
            MCAL_OPT += -DHAS_ISO_TP_COMMANDS
            SOURCES_C +=$(ISO_TP_PROTOCOL_DIR)/iso_tp_commands.c
        endif
    endif
endif
