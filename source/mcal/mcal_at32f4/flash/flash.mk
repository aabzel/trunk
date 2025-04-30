$(info FLASH_DRV_MK_INC=$(FLASH_DRV_MK_INC) )
ifneq ($(FLASH_DRV_MK_INC),Y)
    FLASH_DRV_MK_INC=Y


    FLASH_DIR = $(MCAL_AT32F4_DIR)/flash
    #@echo $(error FLASH_DIR=$(FLASH_DIR))

    INCDIR += -I$(FLASH_DIR)
    OPT += -DHAS_FLASH
    OPT += -DHAS_FLASH_CUSTOM

    SOURCES_C += $(FLASH_DIR)/flash_mcal.c

    CRC16=Y
    OPT += -DHAS_CRC16

    ifeq ($(FLASH_EX),Y)
        OPT += -DHAS_FLASH_EX
    endif

    ifeq ($(FLASH_WRITE),Y)
        #@echo $(error FLASH_WRITE=$(FLASH_WRITE))
        OPT += -DHAS_FLASH_WRITE
        SOURCES_C += $(FLASH_DIR)/flash_mcal_writeite_drv.c
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(FLASH_DIAG),Y)
            OPT += -DHAS_FLASH_DIAG
            SOURCES_C += $(FLASH_DIR)/flash_custom_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(FLASH_COMMANDS),Y)
            OPT += -DHAS_FLASH_COMMANDS
            SOURCES_C += $(FLASH_DIR)/flash_custom_commands.c
        endif
    endif
endif

