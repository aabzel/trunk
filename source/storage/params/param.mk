
ifneq ($(PARAM_MK_INC),Y)
    PARAM_MK_INC=Y
    PARAM_DIR = $(STORAGE_DIR)/params
    #@echo $(error PARAM_DIR= $(PARAM_DIR))
    INCDIR += -I$(PARAM_DIR)

    OPT += -DHAS_PARAM

    ifeq ($(PARAM_SET),Y)
        #@echo $(error PARAM_SET= $(PARAM_SET))
        OPT += -DHAS_PARAM_SET
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(PARAM_DIAG),Y)
            OPT += -DHAS_PARAM_DIAG
            SOURCES_C += $(PARAM_DIR)/param_diag.c
        endif
    endif

    SOURCES_C += $(PARAM_DIR)/param_drv.c

    ifeq ($(CLI),Y)
        ifeq ($(PARAM_COMMANDS),Y)
            #@echo $(error PARAM_COMMANDS=$(PARAM_COMMANDS))
            OPT += -DHAS_PARAM_COMMANDS
            SOURCES_C += $(PARAM_DIR)/param_commands.c
        endif
    endif
endif