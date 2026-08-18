
mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
$(info Build  $(mkfile_path) )

GFSK_DIR = $(WORKSPACE_LOC)Drivers/sx1262/gfsk
#@ echo $(error GFSK_DIR = $(GFSK_DIR))
#@ echo $(error CFLAGS = $(CFLAGS)) 
INCDIR += -I$(GFSK_DIR)
MCAL_OPT += -DHAS_GFSK

SOURCES_C += $(GFSK_DIR)/gfsk_diag.c
SOURCES_C += $(GFSK_DIR)/gfsk_drv.c

ifeq ($(CLI),Y)
    MCAL_OPT += -DHAS_GFSK_COMMANDS
    SOURCES_C += $(GFSK_DIR)/sx1262_gfsk_commands.c
endif
