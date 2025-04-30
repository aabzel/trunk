$(info IPC_DRV_MK_INC=  $(IPC_DRV_MK_INC) )
ifneq ($(IPC_DRV_MK_INC),Y)
    IPC_DRV_MK_INC=Y

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )

    IPC_DIR = $(MCAL_NRF5340_DIR)/ipc
    #@echo $(error IPC_DIR=$(IPC_DIR))

    INCDIR += -I$(IPC_DIR)
    OPT += -DHAS_IPC

    ifeq ($(IPC_INTERRUPT),Y)
        #@echo $(error IPC_INTERRUPT=$(IPC_INTERRUPT))
        OPT += -DHAS_IPC_INTERRUPT
    endif

    SOURCES_C += $(IPC_DIR)/ipc_drv.c
    SOURCES_C += $(IPC_DIR)/ipc_config.c

    ifeq ($(CLI),Y)
        ifeq ($(IPC_COMMANDS),Y)
            OPT += -DHAS_IPC_COMMANDS
            SOURCES_C += $(IPC_DIR)/ipc_commands.c
        endif
    endif
endif