$(info SHA256_MK_INC=$(SHA256_MK_INC))

ifneq ($(SHA256_MK_INC),Y)
    SHA256_MK_INC=Y

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )

    SHA256_DIR=$(COMPUTING_DIR)/sha256
    #@echo $(error SHA256_DIR=$(SHA256_DIR))

    INCDIR += -I$(SHA256_DIR)

    OPT += -DHAS_SHA256
    SOURCES_C += $(SHA256_DIR)/sha256.c
endif
