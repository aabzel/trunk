$(info SDIO_MK_INC=$(SDIO_MK_INC) )
ifneq ($(SDIO_MK_INC),Y)
    SDIO_MK_INC=Y
    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )
    $(info Add CUSTOM SDIO driver)

    SDIO_DIR = $(MCAL_AT32F4_DIR)/sdio
    #@echo $(error SDIO_DIR=$(SDIO_DIR))

    INCDIR += -I$(SDIO_DIR)
    DMA=Y
    #MCAL_OPT += -DHAS_DMA
    SOURCES_C += $(SDIO_DIR)/sdio_drv.c
    SOURCES_C += $(SDIO_DIR)/sdio_isr.c

    MCAL_OPT += -DHAS_SDIO_4BIT
    MCAL_OPT += -DHAS_SDIO
    MCAL_OPT += -DHAS_SDIO_ISR
    MCAL_OPT += -DHAS_SDIO_INTERRUPT
    MCAL_OPT += -DSDMMC_DATATIMEOUT=12000

    #MCAL_OPT += -DHAS_SDIO_INT
    MCAL_OPT += -DHAS_SD_CARD_INIT

    ifeq ($(SDIO1),Y)
        MCAL_OPT += -DHAS_SDIO1
    endif

    ifeq ($(SDIO2),Y)
        MCAL_OPT += -DHAS_SDIO2
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(SDIO_DIAG),Y)
            MCAL_OPT += -DHAS_SDIO_DIAG
            SOURCES_C += $(SDIO_DIR)/sdio_diag.c
        endif
    endif
    
    ifeq ($(CLI),Y)
        ifeq ($(SDIO_COMMANDS),Y)
            MCAL_OPT += -DHAS_SDIO_COMMANDS
            SOURCES_C += $(SDIO_DIR)/sdio_commands.c
        endif
    endif
    
endif