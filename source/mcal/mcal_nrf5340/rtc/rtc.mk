ifneq ($(RTC_CUSTOM_DRIVERV_MK_INC),Y)
    RTC_CUSTOM_DRIVERV_MK_INC=Y
    $(info + RTC NRF)

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )

    RTC_DIR = $(MCAL_NRF5340_DIR)/rtc
    #@echo $(error RTC_DIR=$(RTC_DIR))

    INCDIR += -I$(RTC_DIR)
    OPT += -DHAS_RTC
    #OPT += -DHAS_RTC_CUSTOM

    SOURCES_C += $(RTC_DIR)/rtc_drv.c
    RTC_ISR=Y

    ifeq ($(RTC_ISR),Y)
        OPT += -DHAS_RTC_ISR
        $(info + RTC_ISR)
        SOURCES_C += $(RTC_DIR)/rtc_isr.c
    endif

    ifeq ($(RTC0),Y)
        OPT += -DHAS_RTC0
    endif

    ifeq ($(RTC1),Y)
        OPT += -DHAS_RTC1
    endif

    ifeq ($(RTC2),Y)
        OPT += -DHAS_RTC2
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(RTC_DIAG),Y)
            $(info + RTC Diag)
            SOURCES_C += $(RTC_DIR)/rtc_custom_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(RTC_COMMANDS),Y)
            $(info + RTC Commands)
            OPT += -DHAS_RTC_CUSTOM_COMMANDS
            SOURCES_C += $(RTC_DIR)/rtc_custom_commands.c
        endif
    endif
endif
