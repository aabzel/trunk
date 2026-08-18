
mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
$(info Build  $(mkfile_path) )

SX1262_DIR = $(ASICS_DIR)/sx1262
#@ echo $(error SX1262_DIR = $(SX1262_DIR))
#@ echo $(error CFLAGS = $(CFLAGS)) 

INCDIR += -I$(SX1262_DIR)

RADIO=Y
MCAL_OPT += -DHAS_SX1262
MCAL_OPT += -DHAS_SX1262_DEBUG
MCAL_OPT += -DHAS_SX1262_BIT_RATE
MCAL_OPT += -DHAS_SX1262_POLL
MCAL_OPT += -DHAS_LEGAL_BAND_CHECK
MCAL_OPT += -DHAS_SPI_SW_CHIP_SELECT

SOURCES_C += $(SX1262_DIR)/legal_band.c
SOURCES_C += $(SX1262_DIR)/sx1262_drv.c
SOURCES_C += $(SX1262_DIR)/sx1262_re_tx.c
SOURCES_C += $(SX1262_DIR)/sx1262_registers.c


ifeq ($(DIAG),Y)
    SOURCES_C += $(SX1262_DIR)/sx1262_diag.c
endif


ifeq ($(CLI),Y)
    MCAL_OPT += -DHAS_SX1262_COMMANDS
    SOURCES_C += $(SX1262_DIR)/sx1262_commands.c
endif

ifeq ($(LORA),Y)
    include $(SX1262_DIR)/lora/lora.mk
endif

ifeq ($(GFSK),Y)
    #@ echo $(error GFSK = $(GFSK))
    include $(SX1262_DIR)/gfsk/gfsk.mk
endif
