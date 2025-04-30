ifneq ($(SET_MK_INC),Y)
    SET_MK_INC=Y

    SET_DIR = $(ADT_DIR)/set
    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))

    $(info Build $(mkfile_path))
    $(info + set)

    INCDIR += -I$(SET_DIR)

    OPT += -DHAS_SET

    SOURCES_C += $(SET_DIR)/set.c

    ifeq ($(DIAG),Y)
        ifeq ($(SET_DIAG),Y)
            OPT += -DHAS_SET_DIAG
            SOURCES_C += $(SET_DIR)/set_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(SET_COMMANDS),Y)
            $(info +SET_COMMANDS)
            OPT += -DHAS_SET_COMMANDS
            SOURCES_C += $(SET_DIR)/set_commands.c
        endif
    endif
endif
