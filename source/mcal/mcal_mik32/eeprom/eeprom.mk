$(info EEPROM_DRV_MK_INC=$(EEPROM_DRV_MK_INC) )
ifneq ($(EEPROM_DRV_MK_INC),Y)
    EEPROM_DRV_MK_INC=Y

    EEPROM_DIR = $(MCAL_MIK32_DIR)/eeprom
    #@echo $(error EEPROM_DIR=$(EEPROM_DIR))

    INCDIR += -I$(EEPROM_DIR)
    OPT += -DHAS_EEPROM_CUSTOM

    SOURCES_C += $(EEPROM_DIR)/eeprom_mcal.c

    ifeq ($(EEPROM_EX),Y)
        OPT += -DHAS_EEPROM_EX
    endif

    ifeq ($(EEPROM_WRITE),Y)
        #    $(error EEPROM_WRITE=$(EEPROM_WRITE))
        OPT += -DHAS_EEPROM_WRITE
        SOURCES_C += $(EEPROM_DIR)/eeprom_write.c
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(EEPROM_DIAG),Y)
            OPT += -DHAS_EEPROM_DIAG
            SOURCES_C += $(EEPROM_DIR)/eeprom_custom_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(EEPROM_COMMANDS),Y)
            OPT += -DHAS_EEPROM_COMMANDS
            SOURCES_C += $(EEPROM_DIR)/eeprom_custom_commands.c
        endif
    endif
endif

