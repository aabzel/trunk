
ifneq ($(NRFX_NVS_MK),Y)
    NRFX_NVS_MK=Y
    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )

    NRFX_NVS_DIR = $(MCAL_NRF5340_DIR)/nvs
    #@echo $(error NRFX_NVS_DIR=$(NRFX_NVS_DIR))
    
    INCDIR += -I$(NRFX_NVS_DIR)
    OPT += -DHAS_NRFX_NVS
    OPT += -DHAS_NVS

    SOURCES_C += $(NRFX_NVS_DIR)/nvs_drv.c

    ifeq ($(NVS_DIAG),Y)
        #@echo $(error NVS_DIAG=$(NVS_DIAG))
        OPT += -DHAS_NVS_DIAG
        SOURCES_C += $(NRFX_NVS_DIR)/nvs_custom_diag.c
    endif

    ifeq ($(NVS_WRITE),Y)
        #@echo $(error NVS_WRITE=$(NVS_WRITE))
        OPT += -DHAS_NVS_WRITE
    endif

    ifeq ($(CLI),Y)
        ifeq ($(NRFX_NVS_COMMANDS),Y)
            SOURCES_C += $(NRFX_NVS_DIR)/nvs_custom_commands.c
        endif
    endif
endif
