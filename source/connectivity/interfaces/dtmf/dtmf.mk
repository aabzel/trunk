
$(info DTMF_MK_INC=$(DTMF_MK_INC) )
ifneq ($(DTMF_MK_INC),Y)
    DTMF_MK_INC=Y
    DTMF_DIR = $(INTERFACES_DIR)/dtmf
    #@echo $(error DTMF_DIR=$(DTMF_DIR))

    INCDIR += -I$(DTMF_DIR)
    OPT += -DHAS_DTMF

    #SOURCES_C += $(DTMF_DIR)/dtmf_config.c
    SOURCES_C += $(DTMF_DIR)/dtmf_drv.c

    ifeq ($(DIAG),Y)
        ifeq ($(DTMF_DIAG),Y)
            #@echo $(error DTMF_DIAG=$(DTMF_DIAG))
            OPT += -DHAS_DTMF_DIAG
            SOURCES_C += $(DTMF_DIR)/dtmf_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(DTMF_COMMANDS),Y)
            #@echo $(error DTMF_COMMANDS=$(DTMF_COMMANDS))
            OPT += -DHAS_DTMF_COMMANDS
            SOURCES_C += $(DTMF_DIR)/dtmf_commands.c
        endif
    endif
endif
