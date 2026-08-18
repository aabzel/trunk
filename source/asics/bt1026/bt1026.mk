$(info BT1026_MK_INC=$(BT1026_MK_INC) )

ifneq ($(BT1026_MK_INC),Y)
    BT1026_MK_INC=Y
    BT1026_DIR = $(ASICS_DIR)/bt1026

    #@echo $(error BT1026_DIR=$(BT1026_DIR))
    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Add BT1026 Bluetooth Module )

    INCDIR += -I$(BT1026_DIR)
    MCAL_OPT += -DHAS_BT1026
    MCAL_OPT += -DHAS_BT1026_PROC

    I2S=Y
    MCAL_OPT += -DHAS_I2S

    UART=Y
    MCAL_OPT += -DHAS_UART

    SOURCES_C += $(BT1026_DIR)/bt1026_drv.c

    ifeq ($(BT1026_I2S_MASTER),Y)
        $(info Add BT1026_I2S_MASTER)
        MCAL_OPT += -DHAS_BT1026_I2S_MASTER
        ifeq ($(I2S0_MASTER),Y)
            @echo $(error Double Master on I2S bus)
        endif
    endif

    ifeq ($(BT1026_I2S_SLAVE),Y)
        $(info Add BT1026_I2S_SLAVE)
        MCAL_OPT += -DHAS_BT1026_I2S_SLAVE
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(BT1026_DIAG),Y)
            $(info Add BT1026_DIAG)
            MCAL_OPT += -DHAS_BT1026_DIAG
            SOURCES_C += $(BT1026_DIR)/bt1026_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(BT1026_COMMANDS),Y)
            #@echo $(error BT1026_COMMANDS=$(BT1026_COMMANDS))
            $(info Add BT1026_COMMANDS)
            MCAL_OPT += -DHAS_BT1026_COMMANDS
            MCAL_OPT += -DHAS_MULTIMEDIA_COMMANDS
            SOURCES_C += $(BT1026_DIR)/bt1026_commands.c
        endif
    endif
endif
