$(info BPSK_4FS_MK_INC=$(BPSK_4FS_MK_INC))

ifneq ($(BPSK_4FS_MK_INC),Y)
    BPSK_4FS_MK_INC=Y

    BPSK_4FS_DIR = $(MODULATOR_DIR)/bpsk_4fs
    # $(error BPSK_4FS_DIR=$(BPSK_4FS_DIR))
    INCDIR += -I$(BPSK_4FS_DIR)
    MCAL_OPT +=-DHAS_BPSK_4FS
    
    ifeq ($(BPSK_4FS_PROC),Y)
        MCAL_OPT +=-DHAS_BPSK_4FS_PROC
    endif

    SOURCES_C += $(BPSK_4FS_DIR)/bpsk_4fs_mcal.c
    #MCAL_OPT +=-DHAS_BPSK_4FS_PHASE_ERROR_ASIN
    #MCAL_OPT +=-DHAS_BPSK_4FS_PHASE_ERROR_ATAN
    MCAL_OPT +=-DHAS_BPSK_4FS_PHASE_ERROR_VECTOR

    ifeq ($(BPSK_DEBUG),Y)
        MCAL_OPT +=-DHAS_BPSK_DEBUG
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(BPSK_4FS_DIAG),Y)
            MCAL_OPT +=-DHAS_BPSK_4FS_DIAG
            SOURCES_C += $(BPSK_4FS_DIR)/bpsk_4fs_diag.c
        endif
    endif
    
    ifeq ($(CLI),Y)
        ifeq ($(BPSK_4FS_COMMANDS),Y)
            MCAL_OPT +=-DHAS_BPSK_4FS_COMMANDS
            SOURCES_C += $(BPSK_4FS_DIR)/bpsk_4fs_commands.c
        endif
    endif
endif







