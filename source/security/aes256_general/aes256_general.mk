
ifneq ($(AES256_GENERAL_MK_INC),Y)
    AES256_GENERAL_MK_INC=Y

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )

    AES256_GENERAL_DIR = $(SECURITY_DIR)/aes256_general
    INCDIR += -I$(AES256_GENERAL_DIR)
    #@echo $(error AES256_GENERAL_DIR = $(AES256_GENERAL_DIR))

    OPT += -DHAS_AES
    OPT += -DHAS_AES256
    OPT += -DBACK_TO_TABLES

    ifeq ($(AES256_V1),Y)
        include $(AES256_GENERAL_DIR)/aes256_v1/aes256_v1.mk
    else
        include $(AES256_GENERAL_DIR)/aes256/aes256.mk
    endif

    SOURCES_C += $(AES256_GENERAL_DIR)/aes256_general.c
    ifeq ($(CLI),Y)
        ifeq ($(AES256_GENERAL_COMMANDS),Y)
            OPT += -DHAS_AES256_GENERAL_COMMANDS
            SOURCES_C += $(AES256_GENERAL_DIR)/aes256_general_commands.c
        endif
    endif
endif
