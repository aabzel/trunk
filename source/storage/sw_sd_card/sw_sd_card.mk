ifneq ($(SW_SD_CARD_MK_INC),Y)
    SW_SD_CARD_MK_INC=Y

    SW_SD_CARD_DIR = $(STORAGE_DIR)/sw_sd_card
    # $(error SW_SD_CARD_DIR=$(SW_SD_CARD_DIR))

    INCDIR += -I$(SW_SD_CARD_DIR)

    MCAL_OPT += -DHAS_SW_SD_CARD

    SOURCES_C += $(SW_SD_CARD_DIR)/sw_sd_card.c

    ifeq ($(SW_SD_CARD_INTERRUPTS),Y)
        MCAL_OPT += -DHAS_SW_SD_CARD_INTERRUPTS
        SOURCES_C += $(SW_SD_CARD_DIR)/sw_sd_card_isr.c
    endif

    # must be outside
    SOURCES_C += $(SW_SD_CARD_DIR)/sw_sd_card_config.c

    ifeq ($(DIAG),Y)
        ifeq ($(SW_SD_CARD_DIAG),Y)
            MCAL_OPT += -DHAS_SW_SD_CARD_DIAG
            SOURCES_C += $(SW_SD_CARD_DIR)/sw_sd_card_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(SW_SD_CARD_COMMANDS),Y)
            MCAL_OPT += -DHAS_SW_SD_CARD_COMMANDS
            SOURCES_C += $(SW_SD_CARD_DIR)/sw_sd_card_commands.c
        endif
    endif
endif
