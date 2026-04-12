$(info THIRD_PARTY_STORAGE_MK_INC=$(THIRD_PARTY_STORAGE_MK_INC) )
ifneq ($(THIRD_PARTY_STORAGE_MK_INC),Y)
    THIRD_PARTY_STORAGE_MK_INC=Y

    THIRD_PARTY_STORAGE_DIR = $(THIRD_PARTY_DIR)/storage
    # $(error THIRD_PARTY_STORAGE_DIR=$(THIRD_PARTY_STORAGE_DIR))

    INCDIR += -I$(THIRD_PARTY_STORAGE_DIR)

    MCAL_OPT += -DHAS_THIRD_PARTY_STORAGE

    ifeq ($(STORAGE_COMMANDS),Y)
        MCAL_OPT += -DSTORAGE_CLI_IN_USE
        MCAL_OPT += -DHAS_STORAGE_CLI
        MCAL_OPT += -DHAS_STORAGE_COMMANDS
    endif

    ifeq ($(FAT_FS),Y)
        # $(error FAT_FS=$(FAT_FS))
        include $(THIRD_PARTY_STORAGE_DIR)/fat_fs/fat_fs.mk
    endif

    ifeq ($(LITTLE_FS),Y)
        # $(error LITTLE_FS=$(LITTLE_FS))
        include $(THIRD_PARTY_STORAGE_DIR)/little_fs/little_fs.mk
    endif

    ifeq ($(MEMORY_MANAGER),Y)
        # $(error MEMORY_MANAGER=$(MEMORY_MANAGER))
        include $(THIRD_PARTY_STORAGE_DIR)/memory_manager/memory_manager.mk
    endif

    ifeq ($(EEPROM_EMULATION),Y)
        # $(error EEPROM_EMULATION=$(EEPROM_EMULATION))
        include $(THIRD_PARTY_STORAGE_DIR)/eeprom_emulation/eeprom_emulation.mk
    endif

    ifeq ($(MEMORY_MANAGER),Y)
        # $(error MEMORY_MANAGER=$(MEMORY_MANAGER))
        include $(THIRD_PARTY_STORAGE_DIR)/memory_manager/memory_manager.mk
    endif

    ifeq ($(NVRAM),Y)
        # $(error NVRAM=$(NVRAM))
        include $(THIRD_PARTY_STORAGE_DIR)/nvram/nvram.mk
    endif

    ifeq ($(EHAL_STORAGE_DIAG),Y)
        SOURCES_THIRD_PARTY_C +=  $(THIRD_PARTY_STORAGE_DIR)/storage_diagnostic.c
    endif

    ifeq ($(EHAL_STORAGE),Y)
        SOURCES_THIRD_PARTY_C +=  $(THIRD_PARTY_STORAGE_DIR)/storage_routines.c
        SOURCES_THIRD_PARTY_C +=  $(THIRD_PARTY_STORAGE_DIR)/storage_initialize.c
    endif 
endif