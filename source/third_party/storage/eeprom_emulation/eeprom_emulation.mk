ifneq ($(TP_EEPROM_EMULATION_MK_INC),Y)
    TP_EEPROM_EMULATION_MK_INC=Y

    TP_EEPROM_EMULATION_DIR = $(THIRD_PARTY_STORAGE_DIR)/eeprom_emulation
    #@echo $(error TP_EEPROM_EMULATION_DIR=$(TP_EEPROM_EMULATION_DIR))

    INCDIR += -I$(TP_EEPROM_EMULATION_DIR)

    MCAL_OPT += -DHAS_EEPROM_EMULATION
    #MCAL_OPT += -DEEPROM_EMULATION_IN_USE

    ifeq ($(EEPROM_EMULATION_PROC),Y)
        MCAL_OPT += -DHAS_EEPROM_EMULATION_PROC
    endif

    SOURCES_THIRD_PARTY_C+= $(TP_EEPROM_EMULATION_DIR)/eeprom_emulation.c
    SOURCES_THIRD_PARTY_C+= $(TP_EEPROM_EMULATION_DIR)/eeprom_emulation_ext.c

    ifeq ($(DIAG),Y)
        ifeq ($(EEPROM_EMULATION_DIAG),Y)
            MCAL_OPT += -DHAS_EEPROM_EMULATION_DIAGNOSTIC
            SOURCES_THIRD_PARTY_C+= $(TP_EEPROM_EMULATION_DIR)/eeprom_emulation_diagnostic.c
            SOURCES_EHAL_C+= $(TP_EEPROM_EMULATION_DIR)/eeprom_emulation_diagnostic.c
            SOURCES_EHAL_H += $(TP_EEPROM_EMULATION_DIR)/eeprom_emulation_diagnostic.h
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(EEPROM_EMULATION_COMMANDS),Y)
            #@echo $(error EEPROM_EMULATION_COMMANDS=$(EEPROM_EMULATION_COMMANDS))
            MCAL_OPT += -DHAS_EEPROM_EMULATION_CLI
            SOURCES_THIRD_PARTY_C+= $(TP_EEPROM_EMULATION_DIR)/eeprom_emulation_cli.c
            SOURCES_EHAL_C+= $(TP_EEPROM_EMULATION_DIR)/eeprom_emulation_cli.c
            SOURCES_EHAL_H += $(TP_EEPROM_EMULATION_DIR)/eeprom_emulation_cli.h
        endif
    endif
    
    # Autoformat index
    
    SOURCES_EHAL_C+= $(TP_EEPROM_EMULATION_DIR)/eeprom_emulation.c
    SOURCES_EHAL_H += $(TP_EEPROM_EMULATION_DIR)/eeprom_emulation.h
    
    # code style check index
    #https://habr.com/ru/articles/843746/
    
    SOURCES_CODE_STYLE_C += $(TP_EEPROM_EMULATION_DIR)/eeprom_emulation.c
    SOURCES_CODE_STYLE_H += $(TP_EEPROM_EMULATION_DIR)/eeprom_emulation.h
endif
