ifneq ($(DS3231_MK_INC),Y)
    DS3231_MK_INC=Y

    DS3231_DIR = $(ASICS_DIR)/ds3231
    #@echo $(error DS3231_DIR= $(DS3231_DIR))
    MCAL_OPT += -DHAS_DS3231
    MCAL_OPT += -DHAS_EXTERNAL_RTC
    MCAL_OPT += -DHAS_RTC_EXTERNAL

    INCDIR += -I$(DS3231_DIR)

    SOURCES_C += $(DS3231_DIR)/ds3231_drv.c

    ifeq ($(DIAG),Y)
        ifeq ($(DS3231_DIAG),Y)
            MCAL_OPT += -DHAS_DS3231_DIAG
            SOURCES_C += $(DS3231_DIR)/ds3231_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(DS3231_COMMANDS),Y)
            #@echo $(error DS3231_COMMANDS=$(DS3231_COMMANDS))
            MCAL_OPT += -DHAS_DS3231_COMMANDS
            SOURCES_C += $(DS3231_DIR)/ds3231_commands.c
        endif
    endif
endif