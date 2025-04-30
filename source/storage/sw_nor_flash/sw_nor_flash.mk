ifneq ($(SW_NOR_FLASH_MK_INC),Y)
    SW_NOR_FLASH_MK_INC=Y

    SW_NOR_FLASH_DIR = $(STORAGE_DIR)/sw_nor_flash
    #@echo $(error SW_NOR_FLASH_DIR=$(SW_NOR_FLASH_DIR))

    INCDIR += -I$(SW_NOR_FLASH_DIR)

    OPT += -DHAS_SW_NOR_FLASH
    OPT += -DHAS_NOR_FLASH_SW
    OPT += -DHAS_NOR_FLASH

    SOURCES_C += $(SW_NOR_FLASH_DIR)/sw_nor_flash_drv.c
endif
