ifneq ($(IQUEUE_MK),Y)
    IQUEUE_MK=Y
    IQUEUE_ADT_DIR = $(THIRD_PARTY_ADT_DIR)/iqueue
    # $(error IQUEUE_ADT_DIR = $(IQUEUE_ADT_DIR)) 
    MCAL_OPT += -DHAS_IQUEUE

    INCDIR += -I$(IQUEUE_ADT_DIR)

    SOURCES_C +=$(IQUEUE_ADT_DIR)/iqueue.c
    SOURCES_THIRD_PARTY_C +=$(IQUEUE_ADT_DIR)/lib_iqueue.c

    ifeq ($(DIAG),Y)
        ifeq ($(IQUEUE_DIAG),Y)
            MCAL_OPT += -DHAS_IQUEUE_DIAG
            SOURCES_DIAG_C += $(IQUEUE_ADT_DIR)/iqueue_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(IQUEUE_COMMANDS),Y)
            MCAL_OPT += -DHAS_IQUEUE_CLI
            SOURCES_C += $(IQUEUE_ADT_DIR)/iqueue_cli.c
        endif
    endif
endif
