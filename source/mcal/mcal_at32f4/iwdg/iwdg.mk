$(info IWDG_MK_INC=$(IWDG_MK_INC) )
ifneq ($(IWDG_MK_INC),Y)
    IWDG_MK_INC=Y
    
    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )

    IWDG_DIR = $(MCAL_AT32F4_DIR)/iwdg
    #@echo $(error IWDG_DIR=$(IWDG_DIR))
    IWDG=Y
    INCDIR += -I$(IWDG_DIR)
    OPT += -DHAS_IWDG

    SOURCES_C += $(IWDG_DIR)/iwdg_drv.c

    ifeq ($(CLI),Y)
        ifeq ($(IWDG_COMMANDS),Y)
            OPT += -DHAS_IWDG_COMMANDS
            SOURCES_C += $(IWDG_DIR)/iwdg_commands.c
        endif
    endif
endif


