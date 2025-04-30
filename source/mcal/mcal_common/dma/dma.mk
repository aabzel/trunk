$(info DMA_GENERAL_DRV_MK_INC=$(DMA_GENERAL_DRV_MK_INC) )
ifneq ($(DMA_GENERAL_DRV_MK_INC),Y)
    DMA_GENERAL_DRV_MK_INC=Y

    DMA_MCAL_DIR = $(MCAL_COMMON_DIR)/dma
    #@echo $(error DMA_MCAL_DIR=$(DMA_MCAL_DIR))

    INCDIR += -I$(DMA_MCAL_DIR)
    OPT += -DHAS_DMA
    OPT += -DHAS_DMA_TIME_OUT

    SOURCES_C += $(DMA_MCAL_DIR)/dma_general.c
    SOURCES_C += $(DMA_MCAL_DIR)/dma_isr.c

    ifeq ($(DIAG),Y)
        ifeq ($(DMA_DIAG),Y)
            OPT += -DHAS_DMA_DIAG
            SOURCES_C += $(DMA_MCAL_DIR)/dma_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(DMA_COMMANDS),Y)
            OPT += -DHAS_DMA_COMMANDS
            SOURCES_C += $(DMA_MCAL_DIR)/dma_commands.c
        endif
    endif
    
endif