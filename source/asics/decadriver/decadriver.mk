ifneq ($(DECADRIVER_API_MK_INC),Y)
    DECADRIVER_API_MK_INC=Y

    DECADRIVER_API_DIR = $(ASICS_DIR)/decadriver
    #@echo $(error DECADRIVER_API_DIR=$(DECADRIVER_API_DIR))
    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build $(mkfile_path) )
    $(info + DECADRIVER_API)

    INCDIR += -I$(DECADRIVER_API_DIR)
    MCAL_OPT += -DHAS_DECADRIVER
    MCAL_OPT += -DHAS_DW1000
    MCAL_OPT += -DHAS_DWM1000
    MCAL_OPT += -DHAS_DECADRIVER_PROC

    ifeq ($(DECA_POLL_CONNECTED),Y)
        MCAL_OPT += -DHAS_DECA_POLL_CONNECTED
    endif

    ifeq ($(DECADRIVER_INIT),Y)
        MCAL_OPT += -DHAS_DECADRIVER_INIT
    endif

    ifeq ($(DECADRIVER_TX),Y)
        MCAL_OPT += -DHAS_DECADRIVER_TX
    endif

    MCAL_OPT += -DHAS_UWB

    SOURCES_C += $(DECADRIVER_API_DIR)/decadriver.c
    SOURCES_C += $(DECADRIVER_API_DIR)/decadriver_callback.c
    SOURCES_C += $(DECADRIVER_API_DIR)/decadriver_low_level.c

    ifeq ($(DIAG),Y)
        ifeq ($(DECADRIVER_DIAG),Y)
            $(info +DECADRIVER_DIAG)
            MCAL_OPT += -DHAS_DECADRIVER_DIAG
            SOURCES_C += $(DECADRIVER_API_DIR)/decadriver_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(DECADRIVER_COMMANDS),Y)
            $(info +DECADRIVER_COMMANDS)
            MCAL_OPT += -DHAS_DECADRIVER_COMMANDS
            SOURCES_C += $(DECADRIVER_API_DIR)/decadriver_commands.c
        endif
    endif
endif
