$(info DMA_GENERAL_DRV_MK_INC=$(DMA_GENERAL_DRV_MK_INC) )
ifneq ($(DMA_GENERAL_DRV_MK_INC),Y)
    DMA_GENERAL_DRV_MK_INC=Y

    DMA_MCAL_DIR = $(MCAL_COMMON_DIR)/dma
    #@echo $(error DMA_MCAL_DIR=$(DMA_MCAL_DIR))

    INCDIR += -I$(DMA_MCAL_DIR)
    MCAL_OPT += -DHAS_DMA
    MCAL_OPT += -DHAS_DMA_TIME_OUT

    ifeq ($(DMA_INTERRUPT),Y)
        MCAL_OPT += -DHAS_DMA_INTERRUPT
        SOURCES_C += $(DMA_MCAL_DIR)/dma_isr.c
    endif

    SOURCES_C += $(DMA_MCAL_DIR)/dma_general.c

    ifeq ($(DIAG),Y)
        ifeq ($(DMA_DIAG),Y)
            MCAL_OPT += -DHAS_DMA_DIAG
            SOURCES_DIAG_C += $(DMA_MCAL_DIR)/dma_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(DMA_COMMANDS),Y)
            MCAL_OPT += -DHAS_DMA_COMMANDS
            SOURCES_C += $(DMA_MCAL_DIR)/dma_commands.c
        endif
    endif
    
endif