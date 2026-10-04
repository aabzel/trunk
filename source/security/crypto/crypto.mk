$(info CRYPTO_MK_INC=$(CRYPTO_MK_INC))

ifneq ($(CRYPTO_MK_INC),Y)
    CRYPTO_MK_INC=Y

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path))

    CRYPTO_DIR=$(SECURITY_DIR)/crypto

    INCDIR += -I$(CRYPTO_DIR)

    MCAL_OPT += -DHAS_CRYPTO
    MCAL_OPT += -DHAS_CRYP

    SOURCES_C += $(CRYPTO_DIR)/crypto-ms.c
    SOURCES_C += $(CRYPTO_DIR)/cryp_api.c

    ifeq ($(DIAG),Y)
        ifeq ($(CRYP_DIAG),Y)
            $(info Add Cryp Diag)
            MCAL_OPT += -DHAS_CRYP_DIAG
            SOURCES_C += $(CRYPTO_DIR)/cryp_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(CRYP_COMMANDS),Y)
            $(info Add Cryp commands)
            MCAL_OPT += -DHAS_CRYP_COMMANDS
            SOURCES_C += $(CRYPTO_DIR)/cryp_commands.c
        endif
    endif
endif
