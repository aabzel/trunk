ifneq ($(STORAGE_PRECONFIG_INC),Y)
    STORAGE_PRECONFIG_INC=Y

    STORAGE_DIR = $(WORKSPACE_LOC)/storage
    #@echo $(error STORAGE_DIR= $(STORAGE_DIR))


    ifeq ($(HEX_BIN),Y)
        include $(STORAGE_DIR)/hex_bin/hex_bin_preconfig.mk
    endif

    ifeq ($(ALLOCATOR),Y)
        include $(STORAGE_DIR)/allocator/allocator_preconfig.mk
    endif

    ifeq ($(BLACK_BOX),Y)
        include $(STORAGE_DIR)/black_box/black_box_preconfig.mk
    endif

    ifeq ($(CALIBRATION_DATA),Y)
        #@echo $(error CALIBRATION_DATA=$(CALIBRATION_DATA))
        include $(STORAGE_DIR)/calibration_data/calibration_data_preconfig.mk
    endif

    ifeq ($(FLASH_FS),Y)
        #@echo $(error FLASH_FS=$(FLASH_FS))
        include $(STORAGE_DIR)/flash_fs/flash_fs_preconfig.mk
    endif

    ifeq ($(NOR_FLASH_OFF_CHIP),Y)
        include $(STORAGE_DIR)/nor_flash_off_chip/nor_flash_off_chip_preconfig.mk
    endif

    ifeq ($(FILE_API),Y)
        include $(STORAGE_DIR)/file_api/file_api_preconfig.mk
    endif

    ifeq ($(FAT_FS),Y)
        include $(STORAGE_DIR)/fat_fs/fat_fs_preconfig.mk
    endif

    ifeq ($(FONT),Y)
        include $(STORAGE_DIR)/font/font_preconfig.mk
    endif

    ifeq ($(FILE_PC),Y)
        #@echo $(error FILE_PC=$(FILE_PC)) 
        include $(STORAGE_DIR)/file_pc/file_pc_preconfig.mk
    endif

    ifeq ($(NOR_FLASH),Y)
        #@echo $(error NOR_FLASH=$(NOR_FLASH)) 
        include $(STORAGE_DIR)/nor_flash/nor_flash_preconfig.mk
    endif

    ifeq ($(PARAM),Y)
        include $(STORAGE_DIR)/params/param_preconfig.mk
    endif
    
    ifeq ($(SW_NOR_FLASH),Y)
        #@echo $(error SW_NOR_FLASH= $(SW_NOR_FLASH)) 
        include $(STORAGE_DIR)/sw_nor_flash/sw_nor_flash_preconfig.mk
    endif

    ifeq ($(SW_NVRAM),Y)
        include $(STORAGE_DIR)/sw_nvram/sw_nvram_preconfig.mk
    endif

    ifeq ($(XML),Y)
        include $(STORAGE_DIR)/xml/xml_preconfig.mk
    endif

    ifeq ($(WAV),Y)
        include $(STORAGE_DIR)/wav/wav_preconfig.mk
    endif


endif