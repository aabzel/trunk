ifneq ($(PDM_CUSTOM_DRIVERV_MK_INC),Y)
    PDM_CUSTOM_DRIVERV_MK_INC=Y
    $(info + PDM NRF)

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )

    PDM_DIR = $(MCAL_NRF5340_DIR)/pdm
    #@echo $(error PDM_DIR=$(PDM_DIR))

    INCDIR += -I$(PDM_DIR)
    OPT += -DHAS_PDM
    OPT += -DHAS_PDM_CUSTOM

    OPT += -DHAS_PDM0

    SOURCES_C += $(PDM_DIR)/pdm_drv.c
    PDM_ISR=Y

    ifeq ($(PDM_ISR),Y)
        OPT += -DHAS_PDM_ISR
        SOURCES_C += $(PDM_DIR)/pdm_isr.c
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(PDM_DIAG),Y)
            $(info + PDM Diag)
            SOURCES_C += $(PDM_DIR)/pdm_custom_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(PDM_COMMANDS),Y)
            $(info + PDM Commands)
            OPT += -DHAS_PDM_COMMANDS
            SOURCES_C += $(PDM_DIR)/pdm_custom_commands.c
        endif
    endif
endif
