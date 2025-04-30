$(info ASICS_MK_INC=$(ASICS_MK_INC) )
ifneq ($(ASICS_MK_INC),Y)
    ASICS_MK_INC=Y

    ASICS_DIR = $(WORKSPACE_LOC)/asics
    #@echo $(error ASICS_DIR=$(ASICS_DIR))

    INCDIR += -I$(ASICS_DIR)

    OPT += -DHAS_ASICS
    ifeq ($(ASICS_COMMANDS),Y)
        OPT += -DHAS_ASICS_COMMANDS
    endif

    #SOURCES_C += $(ASICS_DIR)/asics_drv.c

    ifeq ($(AT24C02),Y)
        include $(ASICS_DIR)/at24cxx/at24cxx.mk
    endif
 
    ifeq ($(AD9833),Y)
        include $(ASICS_DIR)/ad9833/ad9833.mk
    endif

    ifeq ($(BQ24079),Y)
        include $(ASICS_DIR)/bq24079/bq24079.mk
    endif

    ifeq ($(BC127),Y)
        include $(ASICS_DIR)/bc127/bc127.mk
    endif

    ifeq ($(BT1026),Y)
        include $(ASICS_DIR)/bt1026/bt1026.mk
    endif

    ifeq ($(BH1750),Y)
        #@echo $(error BH1750=$(BH1750))
        include $(ASICS_DIR)/bh1750/bh1750.mk
    endif

    ifeq ($(DECADRIVER),Y)
        #@echo $(error DECADRIVER= $(DECADRIVER))
        include $(ASICS_DIR)/decadriver/decadriver.mk
    endif

    ifeq ($(DS3231),Y)
        #@echo $(error DS3231= $(DS3231))
        include $(ASICS_DIR)/ds3231/ds3231.mk
    endif

    ifeq ($(DW1000),Y)
        include $(ASICS_DIR)/dw1000/dw1000.mk
    endif

    ifeq ($(LTR390),Y)
        #@echo $(error LTR390=$(LTR390))
        include $(ASICS_DIR)/ltr390/ltr390.mk
    endif

    ifeq ($(FDA801),Y)
        include $(ASICS_DIR)/fda801/fda801.mk
    endif

    ifeq ($(GM67),Y)
        include $(ASICS_DIR)/gm67/gm67.mk
    endif

    ifeq ($(W25Q16BV),Y)
        include $(ASICS_DIR)/w25q16bv/w25q16bv.mk
    endif

    ifeq ($(W25Q32JV),Y)
        include $(ASICS_DIR)/w25q32jv/w25q32jv.mk
    endif
    
    ifeq ($(MAX9860),Y)
        include $(ASICS_DIR)/max9860/max9860.mk
    endif

    ifeq ($(RS2058),Y)
        include $(ASICS_DIR)/rs2058/rs2058.mk
    endif

    ifeq ($(MAX98357),Y)
        include $(ASICS_DIR)/max98357/max98357.mk
    endif

    ifeq ($(MIC2026),Y)
        include $(ASICS_DIR)/mic2026/mic2026.mk
    endif

    ifeq ($(MX25R6435F),Y)
        include $(ASICS_DIR)/mx25r6435f/mx25r6435f.mk
    endif

    ifeq ($(SI4703),Y)
        include $(ASICS_DIR)/si4703/si4703.mk
    endif

    ifeq ($(SI4737),Y)
        include $(ASICS_DIR)/si4737/si4737.mk
    endif

    ifeq ($(SD_CARD),Y)
        #@echo $(error SD_CARD=$(SD_CARD))
        include $(ASICS_DIR)/sd_card/sd_card.mk
    endif

    ifeq ($(SX1262),Y)
        include $(ASICS_DIR)/sx1262/sx1262.mk
    endif

    ifeq ($(SSD1306),Y)
        include $(ASICS_DIR)/ssd1306/ssd1306.mk
    endif

    ifeq ($(TPA2013D1),Y)
        include $(ASICS_DIR)/tpa2013d1/tpa2013d1.mk
    endif

    ifeq ($(WM8731),Y)
        include $(ASICS_DIR)/wm8731/wm8731.mk
    endif

    ifeq ($(UBLOX_NEO_6M),Y)
        include $(ASICS_DIR)/ublox_neo_6m/ublox_neo_6m.mk
    endif

endif