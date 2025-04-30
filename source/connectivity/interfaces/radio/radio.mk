

RADIO_DRV_DIR = $(INTERFACES_DIR)/radio
#@echo $(error RADIO_DRV_DIR = $(RADIO_DRV_DIR)) 
#@ echo $(error CFLAGS = $(CFLAGS)) 

INCDIR += -I$(RADIO_DRV_DIR)

OPT += -DHAS_RADIO

SOURCES_C += $(RADIO_DRV_DIR)/radio_drv.c

ifeq ($(CLI),Y)
    OPT += -DHAS_RADIO_COMMANDS
    SOURCES_C += $(RADIO_DIR)/radio_commands.c
endif