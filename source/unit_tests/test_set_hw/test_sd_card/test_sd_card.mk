$(info TEST_SD_CARD_MK_INC=$(TEST_SD_CARD_MK_INC))
ifneq ($(TEST_SD_CARD_MK_INC),Y)
    TEST_SD_CARD_MK_INC=Y


    TEST_SD_CARD_DIR = $(TEST_SET_HW_DIR)/test_sd_card
    #@echo $(error TEST_SD_CARD_DIR=$(TEST_SD_CARD_DIR))

    INCDIR += -I$(TEST_SD_CARD_DIR)
    OPT += -DHAS_TEST_SD_CARD
    SOURCES_C += $(TEST_SD_CARD_DIR)/test_sd_card.c
    SOURCES_C += $(TEST_SD_CARD_DIR)/test_sd_card_crc.c
endif