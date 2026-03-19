ifneq ($(DMA_CHANNEL_MCAL_MK_INC),Y)
    DMA_CHANNEL_MCAL_MK_INC=Y

    DMA_CHANNEL_MCAL_DIR = $(MCAL_COMMON_DIR)/dma_channel
    # $(error DMA_CHANNEL_MCAL_DIR=$(DMA_CHANNEL_MCAL_DIR))

    INCDIR += -I$(DMA_CHANNEL_MCAL_DIR)

    MCAL_OPT += -DHAS_DMA_CHANNEL

    ifeq ($(DMA_CHANNEL_PROC),Y)
        MCAL_OPT += -DHAS_DMA_CHANNEL_PROC
    endif

    SOURCES_C += $(DMA_CHANNEL_MCAL_DIR)/dma_channel_general.c

    ifeq ($(DMA_INTERRUPT),Y)
        MCAL_OPT += -DHAS_DMA_INTERRUPT
        SOURCES_C += $(DMA_CHANNEL_MCAL_DIR)/dma_channel_isr.c
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(DMA_CHANNEL_DIAG),Y)
            MCAL_OPT += -DHAS_DMA_CHANNEL_DIAG
            SOURCES_C += $(DMA_CHANNEL_MCAL_DIR)/dma_channel_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(DMA_COMMANDS),Y)
            MCAL_OPT += -DHAS_DMA_CHANNEL_COMMANDS
            SOURCES_C += $(DMA_CHANNEL_MCAL_DIR)/dma_channel_commands.c
        endif
    endif
endif
