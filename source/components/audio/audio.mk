$(info AUDIO_MK_INC=$(AUDIO_MK_INC))

ifneq ($(AUDIO_MK_INC),Y)
    AUDIO_MK_INC=Y

    AUDIO_DIR = $(COMPONENTS_DIR)/audio
    #@echo $(error AUDIO_DIR = $(AUDIO_DIR))

    OPT += -DHAS_AUDIO

    INCDIR += -I$(AUDIO_DIR)
    
    ifeq ($(PCM_16_BIT),Y)
        OPT += -DPCM_SAMPLE_SIZE=2
        OPT += -DHAS_PCM_16_BIT
    endif

    ifeq ($(PCM_32_BIT),Y)
        OPT += -DPCM_SAMPLE_SIZE=4
        OPT += -DHAS_PCM_32_BIT
    endif

    SOURCES_C += $(AUDIO_DIR)/audio.c

    ifeq ($(AUDIO_DIAG),Y)
        SOURCES_C += $(AUDIO_DIR)/audio_diag.c
    endif

    ifeq ($(NRFX),Y)
        ifneq ($(NORTOS),Y)
            SOURCES_C += $(AUDIO_DIR)/uicr.c
            SOURCES_C += $(AUDIO_DIR)/channel_assignment.c
            SOURCES_C += $(AUDIO_DIR)/pcm_stream_channel_modifier.c
        endif
    endif

endif
