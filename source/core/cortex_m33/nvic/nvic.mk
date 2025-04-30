ifneq ($(NVIC_DRV_MK_INC),Y)
    NVIC_DRV_MK_INC=Y
    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )

    NVIC_DIR = $(CORTEX_M33_DIR)/nvic
    #@echo $(error NVIC_DIR=$(NVIC_DIR))

    INCDIR += -I$(NVIC_DIR)
    OPT += -DHAS_NVIC
    SOURCES_C += $(NVIC_DIR)/nvic_drv.c

    ifeq ($(DIAG),Y)
        SOURCES_C += $(NVIC_DIR)/nvic_diag.c
    endif

    ifeq ($(CLI),Y)
        ifeq ($(NVIC_COMMANDS),Y)
            OPT += -DHAS_NVIC_COMMANDS
            SOURCES_C += $(NVIC_DIR)/nvic_commands.c
        endif
    endif
endif