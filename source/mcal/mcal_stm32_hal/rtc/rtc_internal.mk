ifneq ($(RTC_CUSTOM_MK_INC),Y)
    RTC_CUSTOM_MK_INC=Y

    RTC_CUSTOM_DIR = $(MCAL_CUSTOM_DIR)/rtc
    # $(error RTC_CUSTOM_DIR=$(RTC_CUSTOM_DIR))

    INCDIR += -I$(RTC_CUSTOM_DIR)
    MCAL_OPT += -DHAS_RTC_CUSTOM
    MCAL_OPT += -DHAS_RTC_INTERNAL

    SOURCES_C += $(RTC_CUSTOM_DIR)/rtc_internal.c

    ifeq ($(DIAG),Y)
        ifeq ($(DIAG_RTC),Y)
            SOURCES_C += $(RTC_CUSTOM_DIR)/rtc_internal_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(RTC_COMMANDS),Y)
            MCAL_OPT += -DHAS_RTC_COMMANDS
            SOURCES_C += $(RTC_CUSTOM_DIR)/rtc_internal_commands.c
        endif
    endif
endif
