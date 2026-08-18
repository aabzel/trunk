$(info BC127_MK_INC=$(BC127_MK_INC) )

ifneq ($(BC127_MK_INC),Y)
    BC127_MK_INC=Y
    BC127_DIR = $(WORKSPACE_LOC)Drivers/bc127
    #@echo $(error BC127_DIR=$(BC127_DIR))
    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )

    INCDIR += -I$(BC127_DIR)
    MCAL_OPT += -DHAS_BC127
    
    I2S=Y
    MCAL_OPT += -DHAS_I2S
    
    UART=Y
    MCAL_OPT += -DHAS_UART

    SOURCES_C += $(BC127_DIR)/bc127_config.c
    SOURCES_C += $(BC127_DIR)/bc127_diag.c
    SOURCES_C += $(BC127_DIR)/bc127_drv.c
    
    ifeq ($(CLI),Y)
        ifeq ($(BC127_COMMANDS),Y)
            #@echo $(error BC127_COMMANDS=$(BC127_COMMANDS))
            MCAL_OPT += -DHAS_BC127_COMMANDS
            SOURCES_C += $(BC127_DIR)/bc127_commands.c
        endif
    endif
endif
