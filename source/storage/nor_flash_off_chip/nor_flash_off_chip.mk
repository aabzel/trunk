ifneq ($(NOR_FLASH_OFF_CHIP_MK_INC),Y)
    NOR_FLASH_OFF_CHIP_MK_INC=Y


    NOR_FLASH_OFF_CHIP_DIR = $(STORAGE_DIR)/nor_flash_off_chip
    #@echo $(error NOR_FLASH_OFF_CHIP_DIR=$(NOR_FLASH_OFF_CHIP_DIR))

    INCDIR += -I$(NOR_FLASH_OFF_CHIP_DIR)

    OPT += -DHAS_NOR_FLASH_OFF_CHIP
    SOURCES_C += $(NOR_FLASH_OFF_CHIP_DIR)/nor_flash_off_chip_api.c
endif
