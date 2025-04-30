
$(info CORRELATOR_MK_INC=$(CORRELATOR_MK_INC))

ifneq ($(CORRELATOR_MK_INC),Y)
    CORRELATOR_MK_INC=Y

    CORRELATOR_DIR = $(DSP_DIR)/correlator
    #@echo $(error CORRELATOR_DIR = $(CORRELATOR_DIR))

    OPT += -DHAS_CORRELATOR

    INCDIR += -I$(CORRELATOR_DIR)
    
    SOURCES_C += $(CORRELATOR_DIR)/correlator.c

    ifeq ($(DIAG),Y)
        ifeq ($(CORRELATOR_DIAG),Y)
            OPT += -DHAS_CORRELATOR_DIAG
            SOURCES_C += $(CORRELATOR_DIR)/correlator_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(CORRELATOR_COMMANDS),Y)
            #@echo $(error CORRELATOR_COMMANDS = $(CORRELATOR_COMMANDS))
            OPT += -DHAS_CORRELATOR_COMMANDS
            SOURCES_C += $(CORRELATOR_DIR)/correlator_commands.c
        endif
    endif
endif
