ifneq ($(STORAGE_MK_INC),Y)
    STORAGE_MK_INC=Y

    MCAL_OPT += -DHAS_STORAGE
    STORAGE_DIR = $(WORKSPACE_LOC)/storage
    # $(error STORAGE_DIR= $(STORAGE_DIR))

    INCDIR += -I$(STORAGE_DIR)

    ifeq ($(HEX_BIN),Y)
        include $(STORAGE_DIR)/hex_bin/hex_bin.mk
    endif
    
    ifeq ($(ALLOCATOR),Y)
        include $(STORAGE_DIR)/allocator/allocator.mk
    endif

    ifeq ($(BLACK_BOX),Y)
        include $(STORAGE_DIR)/black_box/black_box.mk
    endif

    ifeq ($(CALIBRATION_DATA),Y)
        # $(error CALIBRATION_DATA=$(CALIBRATION_DATA))
        include $(STORAGE_DIR)/calibration_data/calibration_data.mk
    endif

    ifeq ($(DISK),Y)
        include $(STORAGE_DIR)/disk/disk.mk
    endif
    
    ifeq ($(LITTLE_FS),Y)
        include $(STORAGE_DIR)/little_fs/little_fs.mk
    endif

    ifeq ($(FLASH_FS),Y)
        # $(error FLASH_FS=$(FLASH_FS))
        include $(STORAGE_DIR)/flash_fs/flash_fs.mk
    endif

    ifeq ($(STORE_FS),Y)
        # $(error STORE_FS=$(STORE_FS))
        include $(STORAGE_DIR)/store_fs/store_fs.mk
    endif

    ifeq ($(NOR_FLASH_OFF_CHIP),Y)
        include $(STORAGE_DIR)/nor_flash_off_chip/nor_flash_off_chip.mk
    endif

    ifeq ($(FILE_API),Y)
        include $(STORAGE_DIR)/file_api/file_api.mk
    endif

    ifeq ($(FAT_FS),Y)
        include $(STORAGE_DIR)/fat_fs/fat_fs.mk
    endif

    ifeq ($(FONT),Y)
        include $(STORAGE_DIR)/font/font.mk
    endif

    ifeq ($(FILE_PC),Y)
        # $(error FILE_PC=$(FILE_PC)) 
        include $(STORAGE_DIR)/file_pc/file_pc.mk
    endif

    ifeq ($(NOR_FLASH),Y)
        # $(error NOR_FLASH=$(NOR_FLASH)) 
        include $(STORAGE_DIR)/nor_flash/nor_flash.mk
    endif

    ifeq ($(PARAM),Y)
        include $(STORAGE_DIR)/params/param.mk
    endif

    ifeq ($(RUNNING_LINE),Y)
        include $(STORAGE_DIR)/running_line/running_line.mk
    endif
    
    ifeq ($(SW_NOR_FLASH),Y)
        # $(error SW_NOR_FLASH= $(SW_NOR_FLASH)) 
        include $(STORAGE_DIR)/sw_nor_flash/sw_nor_flash.mk
    endif

    ifeq ($(SW_NVRAM),Y)
        include $(STORAGE_DIR)/sw_nvram/sw_nvram.mk
    endif

    ifeq ($(SW_SD_CARD),Y)
        include $(STORAGE_DIR)/sw_sd_card/sw_sd_card.mk
    endif

    ifeq ($(XML),Y)
        include $(STORAGE_DIR)/xml/xml.mk
    endif

    ifeq ($(WAV),Y)
        include $(STORAGE_DIR)/wav/wav.mk
    endif

    # $(error STORAGE=$(STORAGE))
    SOURCES_C += $(STORAGE_DIR)/storage.c

     ifeq ($(DIAG),Y)
        # $(error STORAGE_DIAG=$(STORAGE_DIAG))
        MCAL_OPT += -DHAS_STORAGE_DIAG
        SOURCES_DIAG_C += $(STORAGE_DIR)/storage_diag.c
    endif

    ifeq ($(STORAGE_COMMANDS),Y)
        # $(error STORAGE_COMMANDS=$(STORAGE_COMMANDS))
        MCAL_OPT += -DHAS_STORAGE_COMMANDS
        SOURCES_C += $(STORAGE_DIR)/storage_commands.c
    endif
endif