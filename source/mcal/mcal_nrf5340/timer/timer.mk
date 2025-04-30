$(info NRF_TIMER_DRV_MK_INC=$(NRF_TIMER_DRV_MK_INC) )

ifneq ($(NRF_TIMER_DRV_MK_INC),Y)
    NRF_TIMER_DRV_MK_INC=Y

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )

    NRF_TIMER_DIR = $(MCAL_NRF5340_DIR)/timer
    #@echo $(error NRF_TIMER_DIR=$(NRF_TIMER_DIR))

    INCDIR += -I$(NRF_TIMER_DIR)
    OPT += -DHAS_TIMER

    ifeq ($(NRF_TIMER_INTERRUPT),Y)
        #@echo $(error NRF_TIMER_INTERRUPT=$(NRF_TIMER_INTERRUPT))
        OPT += -DHAS_NRF_TIMER_INTERRUPT
    endif

    SOURCES_C += $(NRF_TIMER_DIR)/timer_mcal.c

    ifeq ($(DIAG),Y)
        ifeq ($(TIMER_DIAG),Y)
            SOURCES_C += $(NRF_TIMER_DIR)/timer_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(TIMER_COMMANDS),Y)
            OPT += -DHAS_TIMER_COMMANDS
            SOURCES_C += $(NRF_TIMER_DIR)/timer_custom_commands.c
        endif
    endif
endif
