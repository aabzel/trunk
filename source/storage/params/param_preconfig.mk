
ifneq ($(PARAM_PRECONFIG_INC),Y)
    PARAM_PRECONFIG_INC=Y
    
    PARAM_DIR = $(STORAGE_DIR)/params
    #@echo $(error PARAM_DIR= $(PARAM_DIR))
    PARAM=Y
    FLASH_FS=Y
    CRC8=Y
    CRC=Y
    FLASH=Y
    STORAGE=Y
    NVS=Y
endif