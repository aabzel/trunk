ifneq ($(MANCHESTER_DECODE_MK_INC),Y)
    MANCHESTER_DECODE_MK_INC=Y

    MANCHESTER_DECODE_DIR = $(DSP_DIR)/manchester_decode
    # $(error MANCHESTER_DECODE_DIR=$(MANCHESTER_DECODE_DIR))

    INCDIR += -I$(MANCHESTER_DECODE_DIR)

    MCAL_OPT += -DHAS_MANCHESTER_DECODE

    SOURCES_C += $(MANCHESTER_DECODE_DIR)/manchester_decode_mcal.c

    # must be outside
    SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/manchester_decode_config.c

    ifeq ($(DIAG),Y)
        ifeq ($(MANCHESTER_DECODE_DIAG),Y)
            MCAL_OPT += -DHAS_MANCHESTER_DECODE_DIAG
            SOURCES_DIAG_C += $(MANCHESTER_DECODE_DIR)/manchester_decode_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(MANCHESTER_DECODE_COMMANDS),Y)
            MCAL_OPT += -DHAS_MANCHESTER_DECODE_COMMANDS
            SOURCES_C += $(MANCHESTER_DECODE_DIR)/manchester_decode_commands.c
        endif
    endif
endif
