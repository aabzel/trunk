ifneq ($(DMA_CUSTOM_MK_INC),Y)
    DMA_CUSTOM_MK_INC=Y

    DMA_DIR = $(MCAL_STM32F4_DIR)/dma
    #@echo $(error DMA_DIR=$(DMA_DIR))

    INCDIR += -I$(DMA_DIR)
    OPT += -DHAS_DMA_CUSTOM

    SOURCES_C += $(DMA_DIR)/dma_mcal.c
    SOURCES_C += $(DMA_DIR)/dma_custom_bindings.c

    ifeq ($(DMA1),Y)
        OPT += -DHAS_DMA1
    endif

    ifeq ($(DMA2),Y)
        OPT += -DHAS_DMA2
    endif

    ifeq ($(DIAG),Y)
        SOURCES_C += $(DMA_DIR)/dma_custom_diag.c
    endif

    ifeq ($(CLI),Y)
        ifeq ($(DMA_COMMANDS),Y)
            OPT += -DHAS_DMA_CUSTOM_COMMANDS
            SOURCES_C += $(DMA_DIR)/dma_custom_commands.c
        endif
    endif
endif