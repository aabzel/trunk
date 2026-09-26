ifneq ($(DMA_CHANNEL_CUSTOM_MK_INC),Y)
    DMA_CHANNEL_CUSTOM_MK_INC=Y

    DMA_CHANNEL_DIR = $(MCAL_CUSTOM_DIR)/dma_channel
    # $(error DMA_DIR=$(DMA_DIR))

    INCDIR += -I$(DMA_CHANNEL_DIR)
    MCAL_OPT += -DHAS_DMA_CHANNEL_CUSTOM

    SOURCES_C += $(DMA_DIR)/dma_channel_mcal.c
    SOURCES_C += $(DMA_DIR)/dma_channel_custom_bindings.c
    SOURCES_C += $(DMA_DIR)/dma_channel_config_memcpy.c

    ifeq ($(DMA_CHANNEL_INTERRUPT),Y)
        MCAL_OPT += -DHAS_DMA_CHANNEL_CUSTOM_INTERRUPT
        SOURCES_C += $(DMA_DIR)/dma_channel_custom_isr.c
    endif

    ifeq ($(DMA_CHANNEL_DIAG),Y)
        SOURCES_C += $(DMA_CHANNEL_DIR)/dma_channel_custom_diag.c
    endif

    ifeq ($(CLI),Y)
        ifeq ($(DMA_CHANNEL_COMMANDS),Y)
            MCAL_OPT += -DHAS_DMA_CHANNEL_CUSTOM_COMMANDS
            SOURCES_C += $(DMA_CHANNEL_DIR)/dma_channel_custom_commands.c
        endif
    endif
endif