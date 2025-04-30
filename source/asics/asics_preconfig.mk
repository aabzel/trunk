$(info ASICS_PRECONFIG_MK_INC=$(ASICS_PRECONFIG_MK_INC) )
ifneq ($(ASICS_PRECONFIG_MK_INC),Y)
    ASICS_PRECONFIG_MK_INC=Y

    ASICS_DIR = $(WORKSPACE_LOC)/asics
    #@echo $(error ASICS_DIR=$(ASICS_DIR))


    ifeq ($(AT24C02),Y)
        include $(ASICS_DIR)/at24cxx/at24cxx_preconfig.mk
    endif
    
    ifeq ($(RS2058),Y)
        include $(ASICS_DIR)/rs2058/rs2058_preconfig.mk
    endif

    ifeq ($(AD9833),Y)
        include $(ASICS_DIR)/ad9833/ad9833_preconfig.mk
    endif

    ifeq ($(BQ24079),Y)
        include $(ASICS_DIR)/bq24079/bq24079_preconfig.mk
    endif

    ifeq ($(BC127),Y)
        include $(ASICS_DIR)/bc127/bc127_preconfig.mk
    endif

    ifeq ($(BT1026),Y)
        include $(ASICS_DIR)/bt1026/bt1026_preconfig.mk
    endif

    ifeq ($(AT24C02),Y)
        include $(ASICS_DIR)/at24cxx/at24cxx_preconfig.mk
    endif

    ifeq ($(BH1750),Y)
        #@echo $(error BH1750=$(BH1750))
        include $(ASICS_DIR)/bh1750/bh1750_preconfig.mk
    endif

    ifeq ($(DECADRIVER),Y)
        #@echo $(error DECADRIVER= $(DECADRIVER))
        include $(ASICS_DIR)/decadriver/decadriver_preconfig.mk
    endif

    ifeq ($(DS3231),Y)
        #@echo $(error DS3231= $(DS3231))
        include $(ASICS_DIR)/ds3231/ds3231_preconfig.mk
    endif

    ifeq ($(DW1000),Y)
        include $(ASICS_DIR)/dw1000/dw1000_preconfig.mk
    endif

    ifeq ($(DWM1000),Y)
        include $(ASICS_DIR)/dwm1000/dwm1000_preconfig.mk
    endif

    ifeq ($(DWM3000),Y)
        include $(ASICS_DIR)/dwm3000/dwm3000_preconfig.mk
    endif

    ifeq ($(LTR390),Y)
        include $(ASICS_DIR)/ltr390/ltr390_preconfig.mk
    endif

    ifeq ($(DWS3000),Y)
        include $(ASICS_DIR)/dws3000/dws3000_preconfig.mk
    endif

    ifeq ($(FDA801),Y)
        include $(ASICS_DIR)/fda801/fda801_preconfig.mk
    endif

    ifeq ($(GM67),Y)
        include $(ASICS_DIR)/gm67/gm67_preconfig.mk
    endif

    ifeq ($(MAX9860),Y)
        include $(ASICS_DIR)/max9860/max9860_preconfig.mk
    endif

    ifeq ($(MAX98357),Y)
        include $(ASICS_DIR)/max98357/max98357_preconfig.mk
    endif

    ifeq ($(MIC2026),Y)
        include $(ASICS_DIR)/mic2026/mic2026_preconfig.mk
    endif

    ifeq ($(MX25R6435F),Y)
        include $(ASICS_DIR)/mx25r6435f/mx25r6435f_preconfig.mk
    endif

    ifeq ($(SI4703),Y)
        include $(ASICS_DIR)/si4703/si4703_preconfig.mk
    endif

    ifeq ($(SI4737),Y)
        include $(ASICS_DIR)/si4737/si4737_preconfig.mk
    endif

    ifeq ($(SD_CARD),Y)
        #@echo $(error SD_CARD=$(SD_CARD))
        include $(ASICS_DIR)/sd_card/sd_card_preconfig.mk
    endif
    
    ifeq ($(SX1262),Y)
        include $(ASICS_DIR)/sx1262/sx1262_preconfig.mk
    endif

    ifeq ($(SSD1306),Y)
        include $(ASICS_DIR)/ssd1306/ssd1306_preconfig.mk
    endif

    ifeq ($(TPA2013D1),Y)
        include $(ASICS_DIR)/tpa2013d1/tpa2013d1_preconfig.mk
    endif

    ifeq ($(WM8731),Y)
        include $(ASICS_DIR)/wm8731/wm8731_preconfig.mk
    endif

    ifeq ($(ZED_F9P),Y)
        include $(ASICS_DIR)/zed_f9p/zed_f9p_preconfig.mk
    endif
endif