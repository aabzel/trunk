
$(info EEPROM_MCAL_MK_INC=$(EEPROM_MCAL_MK_INC))
ifneq ($(EEPROM_MCAL_MK_INC),Y)
    EEPROM_MCAL_MK_INC=Y

    EEPROM_MCAL_DIR = $(MCAL_COMMON_DIR)/eeprom
    #@echo $(error EEPROM_MCAL_DIR=$(EEPROM_MCAL_DIR))

    INCDIR += -I$(EEPROM_MCAL_DIR)
    OPT += -DHAS_EEPROM

    SOURCES_C += $(EEPROM_MCAL_DIR)/eeprom_common.c

    #CRC16=Y
    #OPT += -DHAS_CRC16

    ifeq ($(EEPROM_EX),Y)
        OPT += -DHAS_EEPROM_EX
    endif

    ifeq ($(EEPROM_WRITE),Y)
        #@echo $(error EEPROM_WRITE=$(EEPROM_WRITE))
        OPT += -DHAS_EEPROM_WRITE
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(EEPROM_DIAG),Y)
            OPT += -DHAS_EEPROM_DIAG
            SOURCES_C += $(EEPROM_MCAL_DIR)/eeprom_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        #@echo $(error CLI=$(CLI))
        ifeq ($(EEPROM_COMMANDS),Y)
            #@echo $(error EEPROM_COMMANDS=$(EEPROM_COMMANDS))
            OPT += -DHAS_EEPROM_COMMANDS
            SOURCES_C += $(EEPROM_MCAL_DIR)/eeprom_commands.c
        endif
    endif
endif


