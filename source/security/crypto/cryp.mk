$(info CRYP_MCAL_MK_INC=$(CRYP_MCAL_MK_INC) )

ifneq ($(CRYP_MCAL_MK_INC),Y)
    CRYP_MCAL_MK_INC=Y
    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path))
    $(info Add Cryp)

    OPT += -DHAS_CRYP
    CRYP_MCAL_DIR = $(MCAL_COMMON_DIR)/cryp
    #@echo $(error CRYP_MCAL_DIR=[$(CRYP_MCAL_DIR)])

    INCDIR += -I$(CRYP_MCAL_DIR)

    SOURCES_C += $(CRYP_MCAL_DIR)/cryp_api.c

    ifeq ($(DIAG),Y)
        ifeq ($(CRYP_DIAG),Y)
            $(info Add Cryp Diag)
            OPT += -DHAS_CRYP_DIAG
            SOURCES_C += $(CRYP_MCAL_DIR)/cryp_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(CRYP_COMMANDS),Y)
            $(info Add Cryp commands)
            OPT += -DHAS_CRYP_COMMANDS
            SOURCES_C += $(CRYP_MCAL_DIR)/cryp_commands.c
        endif
    endif
endif
