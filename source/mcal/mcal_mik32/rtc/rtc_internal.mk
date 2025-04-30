ifneq ($(RTC_DRV_MK_INC),Y)
    RTC_DRV_MK_INC=Y

    RTC_DIR = $(MCAL_MIK32_DIR)/rtc
    #@echo $(error RTC_DIR=$(RTC_DIR))

    INCDIR += -I$(RTC_DIR)
    OPT += -DHAS_RTC

    SOURCES_C += $(RTC_DIR)/rtc_internal.c

    ifeq ($(DIAG),Y)
        ifeq ($(DIAG_RTC),Y)
            SOURCES_C += $(RTC_DIR)/rtc_internal_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(RTC_COMMANDS),Y)
            OPT += -DHAS_RTC_COMMANDS
            SOURCES_C += $(RTC_DIR)/rtc_internal_commands.c
        endif
    endif
endif
