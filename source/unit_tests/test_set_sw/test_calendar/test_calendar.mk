
    
    
TEST_CALENDAR_DIR = $(TEST_SET_SW_DIR)/test_calendar
#@echo $(error TEST_CALENDAR_DIR= $(TEST_CALENDAR_DIR))
#@echo $(error CFLAGS= $(CFLAGS))

INCDIR += -I$(TEST_CALENDAR_DIR)

SOURCES_C += $(TEST_CALENDAR_DIR)/test_calendar.c
