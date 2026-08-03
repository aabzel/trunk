ifneq ($(M_SEQ_MK_INC),Y)
    M_SEQ_MK_INC=Y

    M_SEQ_DIR = $(COMPUTING_DIR)/m_seq
    # $(error M_SEQ_DIR=$(M_SEQ_DIR))

    INCDIR += -I$(M_SEQ_DIR)

    MCAL_OPT += -DHAS_M_SEQ

    ifeq ($(M_SEQ_PROC),Y)
        MCAL_OPT += -DHAS_M_SEQ_PROC
    endif

    SOURCES_C += $(M_SEQ_DIR)/m_seq_mcal.c


    # must be outside
    SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/m_seq_config.c

    ifeq ($(DIAG),Y)
        ifeq ($(M_SEQ_DIAG),Y)
            # $(error M_SEQ_DIAG=$(M_SEQ_DIAG))
            MCAL_OPT += -DHAS_M_SEQ_DIAG
            SOURCES_DIAG_C += $(M_SEQ_DIR)/m_seq_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(M_SEQ_COMMANDS),Y)
            # $(error M_SEQ_COMMANDS=$(M_SEQ_COMMANDS))
            MCAL_OPT += -DHAS_M_SEQ_COMMANDS
            SOURCES_C += $(M_SEQ_DIR)/m_seq_commands.c
        endif
    endif
endif
