$(info BASE64_MK_INC=$(BASE64_MK_INC))

ifneq ($(BASE64_MK_INC),Y)
    BASE64_MK_INC=Y

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )

    BASE64_DIR = $(PROTOCOLS_DIR)/base64
    #@echo $(error BASE64_DIR = $(BASE64_DIR))

    OPT += -DHAS_BASE64
    INCDIR += -I$(BASE64_DIR)

    SOURCES_C += $(BASE64_DIR)/base64.c
    ifeq ($(DIAG),Y)
        SOURCES_C += $(BASE64_DIR)/base64_diag.c
    endif

    ifeq ($(CLI),Y)
        ifeq ($(BASE64_COMMANDS),Y)
            OPT += -DHAS_BASE64_COMMANDS
            SOURCES_C += $(BASE64_DIR)/base64_commands.c
        endif
    endif
endif
