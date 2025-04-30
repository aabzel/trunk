ifneq ($(TEST_ADC_MK_INC),Y)
    TEST_ADC_MK_INC=Y

    TEST_ADC_DIR = $(TEST_SET_HW_DIR)/test_adc
    #@echo $(error TEST_ADC_DIR=$(TEST_ADC_DIR))
    INCDIR += -I$(TEST_ADC_DIR)
    OPT += -DHAS_TEST_ADC

    SOURCES_C += $(TEST_ADC_DIR)/test_adc.c
endif
