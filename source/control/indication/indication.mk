
$(info INDICATION_MK_INC=$(INDICATION_MK_INC))

ifneq ($(INDICATION_MK_INC),Y)
    INDICATION_MK_INC=Y

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )
    $(info Build  Add Indication)

    INDICATION_DIR = $(CONTROL_DIR)/indication
    #@echo $(error INDICATION_DIR=$(INDICATION_DIR))

    INCDIR += -I$(INDICATION_DIR)

    SOURCES_C += $(INDICATION_DIR)/indication.c

    OPT += -DHAS_INDICATION

    ifeq ($(DIAG),Y)
        ifeq ($(INDICATION_DIAG),Y)
            OPT += -DHAS_INDICATION_DIAG
            SOURCES_C += $(INDICATION_DIR)/indication_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(INDICATION_COMMANDS),Y)
            OPT += -DHAS_INDICATION_COMMANDS
            SOURCES_C += $(INDICATION_DIR)/indication_commands.c
        endif
    endif
endif