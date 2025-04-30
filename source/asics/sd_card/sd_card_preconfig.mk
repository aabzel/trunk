
ifneq ($(SD_CARD_PRECONFIG_MK_INC),Y)
    SD_CARD_PRECONFIG_MK_INC=Y

    SD_CARD_DIR = $(ASICS_DIR)/sd_card
    #@echo $(error SD_CARD_DIR= $(SD_CARD_DIR))

    CRC7=Y
    SPI=Y
    GPIO=Y
    CRC16=Y
    SD_CARD=Y
    SD_CARD_CRC7=Y
    SD_CARD_CRC16=Y

endif