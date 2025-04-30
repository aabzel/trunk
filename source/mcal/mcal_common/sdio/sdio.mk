$(info SDIO_MCAL_MK_INC=$(SDIO_MCAL_MK_INC) )

ifneq ($(SDIO_MCAL_MK_INC),Y)
    SDIO_MCAL_MK_INC=Y
    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path))
    SDIO_MCAL_DIR = $(MCAL_COMMON_DIR)/sdio
    #@echo $(error SDIO_MCAL_DIR=$(SDIO_MCAL_DIR))
    OPT += -DHAS_SDIO

    INCDIR += -I$(SDIO_MCAL_DIR)
    SOURCES_C += $(SDIO_MCAL_DIR)/sdio_general.c
endif