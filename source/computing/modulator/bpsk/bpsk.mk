$(info BPSK_MK_INC=$(BPSK_MK_INC))

ifneq ($(BPSK_MK_INC),Y)
    BPSK_MK_INC=Y

    BPSK_DIR = $(MODULATOR_DIR)/bpsk
    #@echo $(error BPSK_DIR=$(BPSK_DIR))
    INCDIR += -I$(BPSK_DIR)
    MCAL_OPT +=-DHAS_BPSK

    SOURCES_C += $(BPSK_DIR)/bpsk.c
    #MCAL_OPT +=-DHAS_BPSK_PHASE_ERROR_ASIN
    #MCAL_OPT +=-DHAS_BPSK_PHASE_ERROR_ATAN
    MCAL_OPT +=-DHAS_BPSK_PHASE_ERROR_VECTOR

    ifeq ($(DIAG),Y)
        ifeq ($(BPSK_DIAG),Y)
            MCAL_OPT +=-DHAS_BPSK_DIAG
            SOURCES_C += $(BPSK_DIR)/bpsk_diag.c
        endif
    endif
    
    ifeq ($(CLI),Y)
        ifeq ($(BPSK_COMMANDS),Y)
            MCAL_OPT +=-DHAS_BPSK_COMMANDS
            SOURCES_C += $(BPSK_DIR)/bpsk_commands.c
        endif
    endif
endif







