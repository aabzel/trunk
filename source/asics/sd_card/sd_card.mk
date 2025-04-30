
ifneq ($(SD_CARD_MK_INC),Y)
    SD_CARD_MK_INC=Y

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path))
    $(info + SD card SPI driver)

    SD_CARD_DIR = $(ASICS_DIR)/sd_card
    #@echo $(error SD_CARD_DIR= $(SD_CARD_DIR))

    INCDIR += -I$(SD_CARD_DIR)
    #@echo $(error INCDIR= $(INCDIR))

    OPT += -DHAS_CRC7
    OPT += -DHAS_CRC16
    OPT += -DHAS_SD_CARD
    OPT += -DHAS_SD_CARD_CRC7
    OPT += -DHAS_SD_CARD_CRC16

    SOURCES_C += $(SD_CARD_DIR)/sd_card_drv.c
    SOURCES_C += $(SD_CARD_DIR)/sd_card_crc.c
    SOURCES_C += $(SD_CARD_DIR)/sd_card_crc16.c

    ifeq ($(DIAG),Y)
        ifeq ($(SD_CARD_DIAG),Y)
            $(info + SD card diag)
            OPT += -DHAS_SD_CARD_DIAG
            SOURCES_C += $(SD_CARD_DIR)/sd_card_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(SD_CARD_COMMANDS),Y)
            $(info + SD card commands)
            OPT += -DHAS_SD_CARD_COMMANDS
            SOURCES_C += $(SD_CARD_DIR)/sd_card_commands.c
        endif
    endif
    
endif