$(info SDIO_MK_INC=$(SDIO_MK_INC) )
ifneq ($(SDIO_MK_INC),Y)
    SDIO_MK_INC=Y
    $(info Add STM32 SDIO driver)

    SDIO_DIR = $(MCAL_STM32F4_DIR)/sdio
    #@echo $(error SDIO_DIR=$(SDIO_DIR))

    INCDIR += -I$(SDIO_DIR)
    DMA=Y
    #OPT += -DHAS_DMA
    SOURCES_C += $(SDIO_DIR)/sdio_drv.c
    SOURCES_C += $(SDIO_DIR)/sdio_isr.c

    OPT += -DHAS_SDIO_4BIT
    OPT += -DHAS_SDIO_CUSTOM
    OPT += -DHAS_SDIO_ISR
    OPT += -DHAS_SDIO_INTERRUPT
    OPT += -DSDMMC_DATATIMEOUT=12000

    #OPT += -DHAS_SDIO_INT
    OPT += -DHAS_SD_CARD_INIT

    ifeq ($(SDIO1),Y)
        OPT += -DHAS_SDIO1
    endif

    ifeq ($(SDIO2),Y)
        OPT += -DHAS_SDIO2
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(SDIO_DIAG),Y)
            OPT += -DHAS_SDIO_DIAG
            SOURCES_C += $(SDIO_DIR)/sdio_diag.c
        endif
    endif
    
    ifeq ($(CLI),Y)
        ifeq ($(SDIO_COMMANDS),Y)
            OPT += -DHAS_SDIO_COMMANDS
            SOURCES_C += $(SDIO_DIR)/sdio_commands.c
        endif
    endif
    
endif