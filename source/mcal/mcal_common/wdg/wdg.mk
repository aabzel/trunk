
mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
$(info Build  $(mkfile_path) )

WDG_DIR = $(MCAL_COMMON_DIR)/wdg
#@echo $(error WDG_DIR=$(WDG_DIR))
WATCHDOG=Y
OPT += -DHAS_WATCHDOG

INCDIR += -I$(WDG_DIR)




