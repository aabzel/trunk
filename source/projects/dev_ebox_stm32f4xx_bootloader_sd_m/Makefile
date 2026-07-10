MK_PATH:=$(dir $(realpath $(lastword $(MAKEFILE_LIST))))
#@echo $(error MK_PATH=$(MK_PATH))
WORKSPACE_LOC:=$(MK_PATH)../../

INCDIR += -I$(MK_PATH)
INCDIR += -I$(WORKSPACE_LOC)


TARGET=dev_ebox_stm32f4xx_bootloader_sd_m

#@echo $(error SOURCES_C=$(SOURCES_C))
include $(MK_PATH)config.mk
include $(MK_PATH)cli_config.mk
include $(MK_PATH)diag_config.mk

include $(WORKSPACE_LOC)code_base.mk
include $(WORKSPACE_LOC)rules.mk
 