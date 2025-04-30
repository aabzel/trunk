$(info BLE_DRV_MK_INC=  $(BLE_DRV_MK_INC) )
ifneq ($(BLE_DRV_MK_INC),Y)
    BLE_DRV_MK_INC=Y
    
    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )

    BLE_DIR = $(MCAL_NRF5340_DIR)/ble
    #@echo $(error BLE_DIR=$(BLE_DIR))

    INCDIR += -I$(BLE_DIR)
    OPT += -DHAS_BLE

    ifeq ($(BLE_INTERRUPT),Y)
        #@echo $(error BLE_INTERRUPT=$(BLE_INTERRUPT))
        OPT += -DHAS_BLE_INTERRUPT
    endif

    SOURCES_C += $(BLE_DIR)/ble_drv.c

    ifeq ($(CLI),Y)
        ifeq ($(BLE_COMMANDS),Y)
            OPT += -DHAS_BLE_COMMANDS
            SOURCES_C += $(BLE_DIR)/ble_commands.c
        endif
    endif
endif