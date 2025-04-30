
ifneq ($(AES262_MK_INC),Y)
    AES262_MK_INC=Y

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )

    AES262_DIR = $(SECURITY_DIR)/aes256_general/aes256
    #@echo $(error AES262_DIR = $(AES262_DIR))

    OPT += -DHAS_AES
    OPT += -DHAS_AES256
    OPT += -DBACK_TO_TABLES
    INCDIR += -I$(AES262_DIR)

    SOURCES_C += $(AES262_DIR)/aes256.c
    SOURCES_C += $(AES262_DIR)/aes256cbc.c
    ifeq ($(CLI),Y)
        ifeq ($(AES262_COMMANDS),Y)
            OPT += -DHAS_AES262_COMMANDS
            SOURCES_C += $(AES262_DIR)/aes256_commands.c
        endif
    endif
endif
