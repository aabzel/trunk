ifneq ($(PDM_GENERAL_DRV_MK_INC),Y)
    PDM_GENERAL_DRV_MK_INC=Y

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build $(mkfile_path) )

    PDM_MCAL_DIR = $(MCAL_COMMON_DIR)/pdm
    #@echo $(error PDM_MCAL_DIR=$(PDM_MCAL_DIR))

    INCDIR += -I$(PDM_MCAL_DIR)
    OPT += -DHAS_PDM

    SOURCES_C += $(PDM_MCAL_DIR)/pdm_general_drv.c

    ifeq ($(DIAG),Y)
        ifeq ($(PDM_DIAG),Y)
            OPT += -DHAS_PDM_DIAG
            SOURCES_C += $(PDM_MCAL_DIR)/pdm_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(PDM_COMMANDS),Y)
            OPT += -DHAS_PDM_COMMANDS
            SOURCES_C += $(PDM_MCAL_DIR)/pdm_commands.c
        endif
    endif
endif
