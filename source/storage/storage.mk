ifneq ($(STORAGE_MK_INC),Y)
    STORAGE_MK_INC=Y

    OPT += -DHAS_STORAGE
    STORAGE_DIR = $(WORKSPACE_LOC)/storage
    #@echo $(error STORAGE_DIR= $(STORAGE_DIR))

    INCDIR += -I$(STORAGE_DIR)

    ifeq ($(HEX_BIN),Y)
        include $(STORAGE_DIR)/hex_bin/hex_bin.mk
    endif

    ifeq ($(WAV),Y)
        include $(STORAGE_DIR)/wav/wav.mk
    endif
    
    ifeq ($(ALLOCATOR),Y)
        include $(STORAGE_DIR)/allocator/allocator.mk
    endif

    ifeq ($(RUNNING_LINE),Y)
        include $(STORAGE_DIR)/running_line/running_line.mk
    endif

    ifeq ($(BLACK_BOX),Y)
        include $(STORAGE_DIR)/black_box/black_box.mk
    endif

    ifeq ($(CALIBRATION_DATA),Y)
        #@echo $(error CALIBRATION_DATA=$(CALIBRATION_DATA))
        include $(STORAGE_DIR)/calibration_data/calibration_data.mk
    endif

    ifeq ($(FLASH_FS),Y)
        #@echo $(error FLASH_FS=$(FLASH_FS))
        include $(STORAGE_DIR)/flash_fs/flash_fs.mk
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
        #@echo $(error FILE_PC=$(FILE_PC)) 
        include $(STORAGE_DIR)/file_pc/file_pc.mk
    endif

    ifeq ($(NOR_FLASH),Y)
        #@echo $(error NOR_FLASH=$(NOR_FLASH)) 
        include $(STORAGE_DIR)/nor_flash/nor_flash.mk
    endif

    ifeq ($(PARAM),Y)
        include $(STORAGE_DIR)/params/param.mk
    endif
    
    ifeq ($(SW_NOR_FLASH),Y)
        #@echo $(error SW_NOR_FLASH= $(SW_NOR_FLASH)) 
        include $(STORAGE_DIR)/sw_nor_flash/sw_nor_flash.mk
    endif

    ifeq ($(SW_NVRAM),Y)
        include $(STORAGE_DIR)/sw_nvram/sw_nvram.mk
    endif

    ifeq ($(XML),Y)
        include $(STORAGE_DIR)/xml/xml.mk
    endif

    #@echo $(error STORAGE=$(STORAGE))
    SOURCES_C += $(STORAGE_DIR)/storage.c

     ifeq ($(DIAG),Y)
        #@echo $(error STORAGE_DIAG=$(STORAGE_DIAG))
        OPT += -DHAS_STORAGE_DIAG
        SOURCES_C += $(STORAGE_DIR)/storage_diag.c
    endif

    ifeq ($(STORAGE_COMMANDS),Y)
        #@echo $(error STORAGE_COMMANDS=$(STORAGE_COMMANDS))
        OPT += -DHAS_STORAGE_COMMANDS
        SOURCES_C += $(STORAGE_DIR)/storage_commands.c
    endif
endif