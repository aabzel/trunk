
$(info AD9833_MK_INC=$(AD9833_MK_INC))

ifneq ($(AD9833_MK_INC),Y)
    AD9833_MK_INC=Y
    AD9833_DIR = $(ASICS_DIR)/ad9833
    #@echo $(error AD9833_DIR=$(AD9833_DIR))
    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Add AD9833 Module)

    INCDIR += -I$(AD9833_DIR)
    MCAL_OPT += -DHAS_AD9833

    SOURCES_C += $(AD9833_DIR)/ad9833_drv.c
    SOURCES_C += $(AD9833_DIR)/ad9833_config.c

    ifeq ($(DIAG),Y)
        ifeq ($(AD9833_DIAG),Y)
            $(info Add AD9833_DIAG)
            MCAL_OPT += -DHAS_AD9833_DIAG
            SOURCES_C += $(AD9833_DIR)/ad9833_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(AD9833_COMMANDS),Y)
            #@echo $(error AD9833_COMMANDS=$(AD9833_COMMANDS))
            $(info Add AD9833_COMMANDS)
            MCAL_OPT += -DHAS_AD9833_COMMANDS
            SOURCES_C += $(AD9833_DIR)/ad9833_commands.c
        endif
    endif
endif
