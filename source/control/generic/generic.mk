
ifneq ($(GENERIC_MAKE_INC),Y)
    GENERIC_MAKE_INC=Y

    GENERIC_DIR = $(CONTROL_DIR)/generic
    #@echo $(error GENERIC_DIR=$(GENERIC_DIR))
    #@echo $(error GENERIC=$(GENERIC))

    INCDIR += -I$(GENERIC_DIR)

    OPT += -DHAS_GENERIC
    SOURCES_C += $(GENERIC_DIR)/generic.c

    ifeq ($(GENERIC_DIAG),Y)
        OPT += -DHAS_GENERIC_DIAG
        SOURCES_C += $(GENERIC_DIR)/generic_diag.c
    endif

    ifeq ($(CLI),Y)
        ifeq ($(GENERIC_COMMANDS),Y)
            OPT += -DHAS_GENERIC_COMMANDS
            SOURCES_C += $(GENERIC_DIR)/generic_commands.c
        endif
    endif
endif