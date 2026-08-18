
mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
$(info Build  $(mkfile_path) )

LORA_DIR = $(WORKSPACE_LOC)Drivers/sx1262/lora
#@echo $(error LORA_DIR = $(LORA_DIR))
#@ echo $(error CFLAGS = $(CFLAGS)) 

INCDIR += -I$(LORA_DIR)

MCAL_OPT += -DHAS_LORA
#@echo $(error MCAL_OPT = $(MCAL_OPT))

ifeq ($(DIAG),Y)
    SOURCES_C += $(LORA_DIR)/lora_diag.c
endif

SOURCES_C += $(LORA_DIR)/lora_drv.c
SOURCES_C += $(LORA_DIR)/writer_lora.c

ifeq ($(CLI),Y)
    MCAL_OPT += -DHAS_LORA_COMMANDS
    SOURCES_C += $(LORA_DIR)/sx1262_lora_commands.c
endif

