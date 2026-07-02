ifneq ($(WAV_MK_INC),Y)
    WAV_MK_INC=Y

    WAV_DIR = $(STORAGE_DIR)/wav
    #@ echo $(error WAV_DIR = $(WAV_DIR))

    MCAL_OPT += -DHAS_WAV

    INCDIR += -I$(WAV_DIR)

    SOURCES_C += $(WAV_DIR)/wav.c

    ifeq ($(DIAG),Y)
        ifeq ($(WAV_DIAG),Y)
            MCAL_OPT += -DHAS_WAV_DIAG
            SOURCES_C += $(WAV_DIR)/wav_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(WAV_COMMANDS),Y)
            MCAL_OPT += -DHAS_WAV_COMMANDS
            SOURCES_C += $(WAV_DIR)/wav_commands.c
        endif
    endif
endif


