MK_PATH:=$(dir $(realpath $(lastword $(MAKEFILE_LIST))))
#@echo $(error MK_PATH=$(MK_PATH))

WORKSPACE_LOC:=$(MK_PATH)../../

WORKSPACE_LOC:= $(realpath $(WORKSPACE_LOC))
MK_PATH:= $(realpath $(MK_PATH))

INCDIR += -I$(MK_PATH)
INCDIR += -I$(WORKSPACE_LOC)

include $(MK_PATH)/config.mk

ifeq ($(CLI),Y)
    include $(MK_PATH)/cli_config.mk
endif

ifeq ($(DIAG),Y)
    include $(MK_PATH)/diag_config.mk
endif

ifeq ($(UNIT_TEST),Y)
    include $(MK_PATH)/test_config.mk
endif

include $(WORKSPACE_LOC)/make_scripts/code_base.mk

# $(error SOURCES_C=$(SOURCES_C))

include $(WORKSPACE_LOC)/make_scripts/rules.mk
