ifneq ($(CRYP_MK_INC),Y)
    CRYP_MK_INC=Y

    #mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    #$(info Build  $(mkfile_path) )
    $(info Add CRYP HW)

    CRYP_DIR = $(MCAL_AT32F4_DIR)/cryp
    #@echo $(error CRYP_DIR=$(CRYP_DIR))

    INCDIR += -I$(CRYP_DIR)
    OPT += -DCRYP
    OPT += -DHAS_CRYP_HW
    OPT += -DHAS_HW_CRYP

    SOURCES_C += $(CRYP_DIR)/cryp_drv.c
    SOURCES_C += $(CRYP_DIR)/cryp_isr.c
    SOURCES_C += $(CRYP_DIR)/cryp_ecb_drv.c
    SOURCES_C += $(CRYP_DIR)/cryp_cbc_drv.c

    ifeq ($(CRYP1),Y)
        OPT += -DHAS_CRYP1
    endif

    ifeq ($(CRYP2),Y)
        OPT += -DHAS_CRYP2
    endif

    ifeq ($(CRYP_DIAG),Y)
        $(info Add CRYP HW Diag)
        SOURCES_C += $(CRYP_DIR)/cryp_custom_diag.c
    endif

    ifeq ($(CLI),Y)
        ifeq ($(CRYP_COMMANDS),Y)
            $(info Add CRYP commands)
            OPT += -DHAS_CRYP_CUSTOM_COMMANDS
            SOURCES_C += $(CRYP_DIR)/cryp_custom_commands.c
        endif
    endif
endif