$(info THIRD_PARTY_STORAGE_PRECONFIG_INC=$(THIRD_PARTY_STORAGE_PRECONFIG_INC) )
ifneq ($(THIRD_PARTY_STORAGE_PRECONFIG_INC),Y)
    THIRD_PARTY_STORAGE_PRECONFIG_INC=Y

    THIRD_PARTY_STORAGE_DIR = $(THIRD_PARTY_DIR)/storage
    # $(error THIRD_PARTY_STORAGE_DIR=$(THIRD_PARTY_STORAGE_DIR))

    ifeq ($(EEPROM_EMULATION),Y)
        # $(error MEMORY_MANAGER=$(MEMORY_MANAGER))
        include $(THIRD_PARTY_STORAGE_DIR)/eeprom_emulation/eeprom_emulation_preconfig.mk
    endif

    ifeq ($(FAT_FS),Y)
        # $(error FAT_FS=$(FAT_FS))
        include $(THIRD_PARTY_STORAGE_DIR)/fat_fs/fat_fs_preconfig.mk
    endif    

    ifeq ($(MEMORY_MANAGER),Y)
        # $(error MEMORY_MANAGER=$(MEMORY_MANAGER))
        include $(THIRD_PARTY_STORAGE_DIR)/memory_manager/memory_manager_preconfig.mk
    endif
endif