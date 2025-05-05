MK_PATH:=$(dir $(realpath $(lastword $(MAKEFILE_LIST))))
#$(info MK_PATH=$(MK_PATH))
WORKSPACE_LOC:=$(MK_PATH)../../
MK_PATH:= $(realpath $(MK_PATH))
WORKSPACE_LOC:= $(realpath $(WORKSPACE_LOC))
# $(error WORKSPACE_LOC=$(WORKSPACE_LOC))
INCDIR += -I$(MK_PATH)

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
include $(WORKSPACE_LOC)/host_build/host_rules.mk

