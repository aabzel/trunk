$(info I2S_NRF_MK_INC=$(I2S_NRF_MK_INC))
ifneq ($(I2S_NRF_MK_INC),Y)
    I2S_NRF_MK_INC=Y
    $(info Link nrfx I2S driver)
    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )

    I2S_NRF_DIR = $(MCAL_NRF5340_DIR)/i2s
    #@echo $(error I2S_NRF_DIR=$(I2S_NRF_DIR))

    INCDIR += -I$(I2S_NRF_DIR)
    OPT += -DHAS_I2S
    OPT += -DHAS_I2S_PROC
    OPT += -DHAS_NRFX_I2S
    OPT += -DHAS_I2S_NRFX

    SOURCES_C += $(I2S_NRF_DIR)/i2s_drv.c

    ifeq ($(I2S_ISR),Y)
        $(info Add I2S ISR)
        OPT += -DHAS_I2S_ISR
        SOURCES_C += $(I2S_NRF_DIR)/i2s_isr.c
    endif

    ifeq ($(I2S0_MASTER),Y)
        $(info Add I2S0 MASTER)
        OPT += -DHAS_I2S0_MASTER
    endif

    ifeq ($(I2S0_SLAVE),Y)
        $(info Add I2S0 SLAVE)
        OPT += -DHAS_I2S0_SLAVE
    endif

    ifeq ($(I2S0_LOOPBACK),Y)
        $(info Add I2S0 LoopBack)
        OPT += -DHAS_I2S0_LOOPBACK
    endif

    ifeq ($(I2S0),Y)
        $(info Add I2S0)
        OPT += -DHAS_I2S0
    endif

    ifeq ($(DIAG),Y)
        #@echo $(error DIAG=$(DIAG))
        ifeq ($(I2S_DIAG),Y)
            #@echo $(error I2S_DIAG=$(I2S_DIAG))
            $(info Link nrfx I2S diag)
            OPT += -DHAS_I2S_DIAG
            SOURCES_C += $(I2S_NRF_DIR)/i2s_nrf_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(I2S_COMMANDS),Y)
            $(info Add NRFX I2S Commands)
            OPT += -DHAS_I2S_CUSTOM_COMMANDS
            SOURCES_C += $(I2S_NRF_DIR)/i2s_custom_commands.c
        endif
    endif
endif
