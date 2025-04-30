$(info TEST_RTC_DIR = $(TEST_RTC_MK_INC))
ifneq ($(TEST_RTC_MK_INC),Y)
    TEST_RTC_MK_INC=Y
    
    $(info + RTC tests)
    TEST_RTC_DIR = $(TEST_SET_HW_DIR)/test_rtc

    #@echo $(error TEST_RTC_DIR=$(TEST_RTC_DIR))
    INCDIR += -I$(TEST_RTC_DIR)

    OPT += -DHAS_TEST_RTC
    
    SOURCES_C += $(TEST_RTC_DIR)/test_rtc.c
endif