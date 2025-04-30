
ifneq ($(AES256_V1_MK_INC),Y)
    AES256_V1_MK_INC=Y

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )

    AES256_V1_DIR = $(WORKSPACE_LOC)components/aes256_general/aes256_v1
    #@echo $(error AES256_V1_DIR = $(AES256_V1_DIR))

    OPT += -DHAS_AES
    OPT += -DHAS_AES256_V1
    INCDIR += -I$(AES256_V1_DIR)

    SOURCES_C += $(AES256_V1_DIR)/aes256.c
    ifeq ($(CLI),Y)
        ifeq ($(AES256_V1_COMMANDS),Y)
            OPT += -DHAS_AES256_V1_COMMANDS
            SOURCES_C += $(AES256_V1_DIR)/aes256_commands.c
        endif
    endif
endif
