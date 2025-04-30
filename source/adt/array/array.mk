ifneq ($(ARRAY_MK_INC),Y)
    ARRAY_MK_INC=Y

    ARRAY_DIR = $(ADT_DIR)/array

    $(info Build ARRAY)
    #$(error ARRAY_DIR=$(ARRAY_DIR) )

    INCDIR += -I$(ARRAY_DIR)

    OPT += -DHAS_ARRAY

    ifeq ($(ARRAY_EXT),Y)
        OPT += -DHAS_ARRAY_EXT
    endif

    SOURCES_C += $(ARRAY_DIR)/array.c

    ifeq ($(DIAG),Y)
        ifeq ($(ARRAY_DIAG),Y)
            OPT += -DHAS_ARRAY_DIAG
            SOURCES_C += $(ARRAY_DIR)/array_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(ARRAY_COMMANDS),Y)
            $(info +ARRAY_COMMANDS)
            OPT += -DHAS_ARRAY_COMMANDS
            SOURCES_C += $(ARRAY_DIR)/array_commands.c
        endif
    endif
endif
