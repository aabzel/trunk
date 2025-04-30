ifneq ($(CALENDAR_MK_INC),Y)
    CALENDAR_MK_INC=Y

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )

    CALENDAR_DIR = $(COMPUTING_DIR)/calendar
    #@echo $(error CALENDAR_DIR=$(CALENDAR_DIR))
    INCDIR += -I$(CALENDAR_DIR)

    CALENDAR=Y
    OPT += -DHAS_CALENDAR
    SOURCES_C += $(CALENDAR_DIR)/calendar.c
endif
