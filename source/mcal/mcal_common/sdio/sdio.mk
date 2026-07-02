$(info SDIO_MCAL_MK_INC=$(SDIO_MCAL_MK_INC) )

ifneq ($(SDIO_MCAL_MK_INC),Y)
    SDIO_MCAL_MK_INC=Y

    SDIO_MCAL_DIR = $(MCAL_COMMON_DIR)/sdio
    # $(error SDIO_MCAL_DIR=$(SDIO_MCAL_DIR))

    INCDIR += -I$(SDIO_MCAL_DIR)

    MCAL_OPT += -DHAS_SDIO

    ifeq ($(SDIO_PROC),Y)
        MCAL_OPT += -DHAS_SDIO_PROC
    endif

    SOURCES_C += $(SDIO_MCAL_DIR)/sdio_general.c
    SOURCES_C += $(SDIO_MCAL_DIR)/sdio_isr.c

    ifeq ($(DIAG),Y)
        ifeq ($(SDIO_DIAG),Y)
            MCAL_OPT += -DHAS_SDIO_DIAG
            SOURCES_C += $(SDIO_MCAL_DIR)/sdio_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(SDIO_COMMANDS),Y)
            MCAL_OPT += -DHAS_SDIO_COMMANDS
            SOURCES_C += $(SDIO_MCAL_DIR)/sdio_commands.c
        endif
    endif
endif
