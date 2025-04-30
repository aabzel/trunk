$(info BASE16_MK_INC=$(BASE16_MK_INC))

ifneq ($(BASE16_MK_INC),Y)
    BASE16_MK_INC=Y

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )

    BASE16_DIR = $(PROTOCOLS_DIR)/base16
    #@echo $(error BASE16_DIR = $(BASE16_DIR))

    OPT += -DHAS_BASE16
    INCDIR += -I$(BASE16_DIR)

    SOURCES_C += $(BASE16_DIR)/base16.c
    ifeq ($(DIAG),Y)
        SOURCES_C += $(BASE16_DIR)/base16_diag.c
    endif

    ifeq ($(CLI),Y)
        ifeq ($(BASE16_COMMANDS),Y)
            OPT += -DHAS_BASE16_COMMANDS
            SOURCES_C += $(BASE16_DIR)/base16_commands.c
        endif
    endif
endif
