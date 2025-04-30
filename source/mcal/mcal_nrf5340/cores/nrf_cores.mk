$(info NRF_CORES_DRV_MK_INC = $(NRF_CORES_DRV_MK_INC) )
ifneq ($(NRF_CORES_DRV_MK_INC),Y)
    NRF_CORES_DRV_MK_INC=Y

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build $(mkfile_path))

    NRF_CORES_NRF_DIR = $(MCAL_NRF5340_DIR)/cores
    #@echo $(error NRF_CORES_NRF_DIR=$(NRF_CORES_NRF_DIR))
    OPT += -DHAS_NRF_CORES
    OPT += -DHAS_NRFX_CORE

    INCDIR += -I$(NRF_CORES_NRF_DIR)

    SOURCES_C += $(NRF_CORES_NRF_DIR)/nrf_cores_drv.c

    ifeq ($(CLI),Y)
        ifeq ($(NRF_CORES_COMMANDS),Y)
            OPT += -DHAS_NRF_CORES_COMMANDS
            SOURCES_C += $(NRF_CORES_NRF_DIR)/nrf_cores_commands.c
        endif
    endif

    ifeq ($(DIAG),Y)
        SOURCES_C += $(NRF_CORES_NRF_DIR)/nrf_cores_diag.c
    endif
endif