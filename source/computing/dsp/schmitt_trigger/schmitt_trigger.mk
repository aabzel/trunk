
$(info SCHMITT_TRIGGER_MK_INC=$(SCHMITT_TRIGGER_MK_INC))

ifneq ($(SCHMITT_TRIGGER_MK_INC),Y)
    SCHMITT_TRIGGER_MK_INC=Y

    SCHMITT_TRIGGER_DIR = $(DSP_DIR)/schmitt_trigger
    #@echo $(error SCHMITT_TRIGGER_DIR=$(SCHMITT_TRIGGER_DIR))

    INCDIR += -I$(SCHMITT_TRIGGER_DIR)
    SOURCES_C += $(SCHMITT_TRIGGER_DIR)/schmitt_trigger.c
    #SOURCES_H += $(SCHMITT_TRIGGER_DIR)/schmitt_trigger.h

    SCHMITT_TRIGGER=Y
    OPT += -DHAS_SCHMITT_TRIGGER

    ifeq ($(DIAG),Y)
        OPT += -DHAS_SCHMITT_TRIGGER_DIAG
        SOURCES_C += $(SCHMITT_TRIGGER_DIR)/schmitt_trigger_diag.c
    endif

    ifeq ($(CLI),Y)
        ifeq ($(SCHMITT_TRIGGER_COMMANDS),Y)
            OPT += -DHAS_SCHMITT_TRIGGER_COMMANDS
            SOURCES_C += $(SCHMITT_TRIGGER_DIR)/schmitt_trigger_commands.c
        endif
    endif
endif