$(info NRFX_FLASH_DRV_MK_INC=$(NRFX_FLASH_DRV_MK_INC) )
ifneq ($(NRFX_FLASH_DRV_MK_INC),Y)
    NRFX_FLASH_DRV_MK_INC=Y

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path))

    NRFX_FLASH_DIR = $(MCAL_NRF5340_DIR)/flash
    #@echo $(error NRFX_FLASH_DIR=$(NRFX_FLASH_DIR))

    INCDIR += -I$(NRFX_FLASH_DIR)

    OPT += -DHAS_FLASH
    OPT += -DHAS_FLASH_CUSTOM
    OPT += -DHAS_ON_CHIP_FLASH

    SOURCES_C += $(NRFX_FLASH_DIR)/flash_drv.c

    ifeq ($(CRC16),N)
        @echo $(warning Add CRC16)
    endif
    #CRC16=Y
    #OPT += -DHAS_CRC16

    ifeq ($(FLASH_EX),Y)
        OPT += -DHAS_FLASH_EX
    endif

    ifeq ($(FLASH_WRITE),Y)
        #@echo $(error FLASH_WRITE=$(FLASH_WRITE))
        OPT += -DHAS_FLASH_WRITE
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(FLASH_DIAG),Y)
            OPT += -DHAS_FLASH_DIAG
            SOURCES_C += $(NRFX_FLASH_DIR)/flash_custom_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(FLASH_COMMANDS),Y)
            OPT += -DHAS_FLASH_COMMANDS
            SOURCES_C += $(NRFX_FLASH_DIR)/flash_custom_commands.c
        endif
    endif
endif

