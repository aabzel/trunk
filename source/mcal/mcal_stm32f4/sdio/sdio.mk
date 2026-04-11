$(info SDIO_CUSTOM_MK_INC=$(SDIO_CUSTOM_MK_INC) )
ifneq ($(SDIO_CUSTOM_MK_INC),Y)
    SDIO_CUSTOM_MK_INC=Y

    SDIO_CUSTOM_DIR = $(MCAL_STM32F4_DIR)/sdio
    # $(error SDIO_CUSTOM_DIR=$(SDIO_CUSTOM_DIR))

    INCDIR += -I$(SDIO_CUSTOM_DIR)

    SOURCES_C += $(SDIO_CUSTOM_DIR)/sdio_mcal.c
    MCAL_OPT += -DHAS_SDIO_4BIT
    MCAL_OPT += -DHAS_SDIO_CUSTOM

    ifeq ($(SDIO_DMA),Y)
          MCAL_OPT += -DHAS_SDIO_DMA
        SOURCES_C += $(SDIO_CUSTOM_DIR)/sdio_dma.c
    endif

    ifeq ($(SDIO_POLL),Y)
        MCAL_OPT += -DHAS_SDIO_POLL
        SOURCES_C += $(SDIO_CUSTOM_DIR)/sdio_poll.c
    endif

    ifeq ($(SDIO_INTERRUPT),Y)
       #  $(error SDIO_INTERRUPT=$(SDIO_INTERRUPT))
        MCAL_OPT += -DHAS_SDIO_ISR
        MCAL_OPT += -DHAS_SDIO_INTERRUPT
        SOURCES_C += $(SDIO_CUSTOM_DIR)/sdio_int.c
        SOURCES_C += $(SDIO_CUSTOM_DIR)/sdio_isr.c
    endif

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
            MCAL_OPT += -DHAS_SDIO_CUSTOM_DIAG
            SOURCES_C += $(SDIO_CUSTOM_DIR)/sdio_custom_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(SDIO_COMMANDS),Y)
            MCAL_OPT += -DHAS_SDIO_CUSTOM_COMMANDS
            SOURCES_C += $(SDIO_CUSTOM_DIR)/sdio_custom_commands.c
        endif
    endif
endif