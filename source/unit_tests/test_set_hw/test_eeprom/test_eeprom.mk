
$(info TEST_EEPROM_MK_INC=$(TEST_EEPROM_MK_INC) )
ifneq ($(TEST_EEPROM_MK_INC),Y)
    TEST_EEPROM_MK_INC=Y

    $(info + eeprom tests)
    TEST_EEPROM_DIR = $(TEST_SET_HW_DIR)/test_eeprom
    # $(error TEST_EEPROM_DIR=$(TEST_EEPROM_DIR))

    INCDIR += -I$(TEST_EEPROM_DIR)
    OPT += -DHAS_TEST_EEPROM

    ifeq ($(EEPROM_WRITE),Y)
        OPT += -DHAS_TEST_EEPROM_WRITE
    endif

    SOURCES_C += $(TEST_EEPROM_DIR)/test_eeprom.c
endif

