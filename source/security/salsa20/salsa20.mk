$(info Build SALSA20_MK=$(SALSA20_MK))

ifneq ($(SALSA20_MK),Y)
    SALSA20_MK=Y
    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build $(mkfile_path))

    SALSA20_DIR = $(SECURITY_DIR)/salsa20
    #@echo $(error SALSA20_DIR=$(SALSA20_DIR))
    INCDIR += -I$(SALSA20_DIR)
    OPT += -DHAS_SALSA20

    ifeq ($(SALSA20_DIAG),Y)
        OPT += -DHAS_SALSA20_DIAG
    endif

    SOURCES_C += $(SALSA20_DIR)/salsa20.c
    SOURCES_C += $(SALSA20_DIR)/salsa20_util.c

    ifeq ($(CLI),Y)
        ifeq ($(SALSA20_COMMANDS),Y)
            OPT += -DHAS_SALSA20_COMMANDS
            SOURCES_C += $(SALSA20_DIR)/salsa20_commands.c
        endif
    endif
endif
