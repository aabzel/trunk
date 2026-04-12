
ifneq ($(GENERIC_MAKE_INC),Y)
    GENERIC_MAKE_INC=Y

    GENERIC_DIR = $(CONTROL_DIR)/generic
    #@echo $(error GENERIC=$(GENERIC))

    INCDIR += -I$(GENERIC_DIR)

    MCAL_OPT += -DHAS_GENERIC
    #MCAL_OPT += -DHAS_GENERIC_PROC
    
    SOURCES_C += $(GENERIC_DIR)/generic.c

    ifeq ($(DIAG),Y)
        ifeq ($(GENERIC_DIAG),Y)
            MCAL_OPT += -DHAS_GENERIC_DIAG
            SOURCES_C += $(GENERIC_DIR)/generic_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(GENERIC_COMMANDS),Y)
            MCAL_OPT += -DHAS_GENERIC_COMMANDS
            SOURCES_C += $(GENERIC_DIR)/generic_commands.c
        endif
    endif
endif