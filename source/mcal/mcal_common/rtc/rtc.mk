$(info RTC_GENERAL_MCAL_MK_INC=$(RTC_GENERAL_MCAL_MK_INC) )

ifneq ($(RTC_GENERAL_MCAL_MK_INC),Y)
    RTC_GENERAL_MCAL_MK_INC=Y

    RTC_MCAL_DIR = $(MCAL_COMMON_DIR)/rtc
    #@echo $(error RTC_MCAL_DIR=[$(RTC_MCAL_DIR)])

    OPT += -DHAS_RTC
    INCDIR += -I$(RTC_MCAL_DIR)

    SOURCES_C += $(RTC_MCAL_DIR)/rtc_common.c

    ifeq ($(DIAG),Y)
        ifeq ($(RTC_DIAG),Y)
            #@echo $(error RTC_DIAG=[$(RTC_DIAG)])
            OPT += -DHAS_RTC_DIAG
            SOURCES_C += $(RTC_MCAL_DIR)/rtc_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(RTC_COMMANDS),Y)
            #@echo $(error RTC_COMMANDS=[$(RTC_COMMANDS)])
            OPT += -DHAS_RTC_COMMANDS
            SOURCES_C += $(RTC_MCAL_DIR)/rtc_commands.c
        endif
    endif
endif






