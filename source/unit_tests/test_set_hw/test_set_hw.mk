ifneq ($(TEST_SET_HW_MK_INC),Y)
    TEST_SET_HW_MK_INC=Y

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )
    TEST_SET_HW_DIR = $(UNIT_TESTS_DIR)/test_set_hw
    #@echo $(error TEST_SET_HW_DIR= $(TEST_SET_HW_DIR))

    INCDIR += -I$(TEST_SET_HW_DIR)

    ifeq ($(TEST_ADC),Y)
        include $(TEST_SET_HW_DIR)/test_adc/test_adc.mk
    endif

    ifeq ($(TEST_AUTO_VOLUME),Y)
        include $(TEST_SET_HW_DIR)/test_auto_volume/test_auto_volume.mk
    endif

    ifeq ($(TEST_BC127),Y)
        #@echo $(error TEST_BC127=$(TEST_BC127))
        include $(TEST_SET_HW_DIR)/test_bc127/test_bc127.mk
    endif

    ifeq ($(TEST_BUTTON),Y)
        include $(TEST_SET_HW_DIR)/test_button/test_button.mk
    endif

    ifeq ($(TEST_CAN),Y)
        include $(TEST_SET_HW_DIR)/test_can/test_can.mk
    endif

    ifeq ($(TEST_CRYP_HW),Y)
        #@echo $(error TEST_CRYP_HW=$(TEST_CRYP_HW))
        include $(TEST_SET_HW_DIR)/test_cryp_hw/test_cryp_hw.mk
    endif

    ifeq ($(TEST_LTR390),Y)
        include $(TEST_SET_HW_DIR)/test_ltr390/test_ltr390.mk
    endif

    ifeq ($(TEST_DTMF),Y)
        include $(TEST_SET_HW_DIR)/test_dtmf/test_dtmf.mk
    endif

    ifeq ($(TEST_DMA),Y)
        include $(TEST_SET_HW_DIR)/test_dma/test_dma.mk
    endif

    ifeq ($(TEST_DS3231),Y)
        include $(TEST_SET_HW_DIR)/test_ds3231/test_ds3231.mk
    endif

    ifeq ($(TEST_DECADRIVER),Y)
        include $(TEST_SET_HW_DIR)/test_decadriver/test_decadriver.mk
    endif

    ifeq ($(TEST_DW1000),Y)
        include $(TEST_SET_HW_DIR)/test_dw1000/test_dw1000.mk
    endif

    ifeq ($(TEST_DWM3000),Y)
        include $(TEST_SET_HW_DIR)/test_dwm3000/test_dwm3000.mk
    endif

    ifeq ($(TEST_IWDG),Y)
        include $(TEST_SET_HW_DIR)/test_iwdg/test_iwdg.mk
    endif

    ifeq ($(TEST_EEPROM),Y)
        include $(TEST_SET_HW_DIR)/test_eeprom/test_eeprom.mk
    endif
    
    ifeq ($(TEST_FDA801),Y)
        include $(TEST_SET_HW_DIR)/test_fda801/test_fda801.mk
    endif

    ifeq ($(TEST_FLASH),Y)
        #ifeq ($(NRF5340),Y)
        #    include $(TEST_SET_HW_DIR)/test_flash_nrf5340/test_flash_nrf5340.mk
        #endif
        #@echo $(error TEST_FLASH=$(TEST_FLASH))
        include $(TEST_SET_HW_DIR)/test_flash/test_flash.mk
    endif

    ifeq ($(TEST_FLASH_FS),Y)
        include $(TEST_SET_HW_DIR)/test_flash_fs/test_flash_fs.mk
    endif

    ifeq ($(TEST_MAX9860),Y)
        include $(TEST_SET_HW_DIR)/test_max9860/test_max9860.mk
    endif

    ifeq ($(TEST_AT24CXX),Y)
        include $(TEST_SET_HW_DIR)/test_at24cxx/test_at24cxx.mk
    endif

    ifeq ($(TEST_MX25R6435F),Y)
        include $(TEST_SET_HW_DIR)/test_mx25r6435f/test_mx25r6435f.mk
    endif

    ifeq ($(TEST_MX25R6435F),Y)
        include $(TEST_SET_HW_DIR)/test_mx25r6435f/test_mx25r6435f.mk
    endif

    ifeq ($(TEST_GPIO),Y)
        #@echo $(error TEST_GPIO=$(TEST_GPIO))
        include $(TEST_SET_HW_DIR)/test_gpio/test_gpio.mk
    endif

    ifeq ($(TEST_LED_MONO),Y)
        include $(TEST_SET_HW_DIR)/test_led_mono/test_led_mono.mk
    endif

    ifeq ($(TEST_LED_RGB),Y)
        include $(TEST_SET_HW_DIR)/test_led_rgb/test_led_rgb.mk
    endif

    ifeq ($(TEST_SCR1_TIMER),Y)
        include $(TEST_SET_HW_DIR)/test_scr1_timer/test_scr1_timer.mk
    endif
    
    ifeq ($(TEST_MIC2026),Y)
        include $(TEST_SET_HW_DIR)/test_mic2026/test_mic2026.mk
    endif

    ifeq ($(TEST_NVS),Y)
        include $(TEST_SET_HW_DIR)/test_nvs/test_nvs.mk
    endif

    ifeq ($(TEST_PDM),Y)
        include $(TEST_SET_HW_DIR)/test_pdm/test_pdm.mk
    endif

    ifeq ($(TEST_DISK),Y)
        include $(TEST_SET_HW_DIR)/test_disk/test_disk.mk
    endif

    ifeq ($(TEST_SDIO),Y)
        include $(TEST_SET_HW_DIR)/test_sdio/test_sdio.mk
    endif

    ifeq ($(TEST_SOFTWARE_TIMER),Y)
        include $(TEST_SET_HW_DIR)/test_sw_timer/test_sw_timer.mk
    endif

    ifeq ($(TEST_SD_CARD),Y)
        include $(TEST_SET_HW_DIR)/test_sd_card/test_sd_card.mk
    endif

    ifeq ($(TEST_SSD1306),Y)
        include $(TEST_SET_HW_DIR)/test_ssd1306/test_ssd1306.mk
    endif

    ifeq ($(TEST_I2S),Y)
        include $(TEST_SET_HW_DIR)/test_i2s/test_i2s.mk
    endif

    ifeq ($(TEST_PARAM),Y)
        include $(TEST_SET_HW_DIR)/test_params/test_param.mk
    endif

    ifeq ($(TEST_RTC),Y)
        include $(TEST_SET_HW_DIR)/test_rtc/test_rtc.mk
    endif

    ifeq ($(TEST_SPI),Y)
        include $(TEST_SET_HW_DIR)/test_spi/test_spi.mk
    endif

    ifeq ($(TEST_SI4703),Y)
        include $(TEST_SET_HW_DIR)/test_si4703/test_si4703.mk
    endif

    ifeq ($(TEST_SI4737),Y)
        include $(TEST_SET_HW_DIR)/test_si4737/test_si4737.mk
    endif

    ifeq ($(TEST_SX1262),Y)
        include $(TEST_SET_HW_DIR)/test_sx1262/test_sx1262.mk
    endif

    ifeq ($(TEST_SYSTICK),Y)
        include $(TEST_SET_HW_DIR)/test_systick/test_systick.mk
    endif

    ifeq ($(TEST_TIM),Y)
        include $(TEST_SET_HW_DIR)/test_tim/test_tim.mk
    endif

    ifeq ($(TEST_UART),Y)
        #@echo $(error TEST_SET_HW_DIR=$(TEST_SET_HW_DIR))
        include $(TEST_SET_HW_DIR)/test_uart/test_uart.mk
    endif

    ifeq ($(TEST_WM8731),Y)
        include $(TEST_SET_HW_DIR)/test_wm8731/test_wm8731.mk
    endif
    
     
    ifeq ($(TEST_SPIFI),Y)
        include $(TEST_SET_HW_DIR)/test_spifi/test_spifi.mk
    endif
    

    ifeq ($(TEST_ZED_F9P),Y)
        include $(TEST_SET_HW_DIR)/test_zed_f9p/test_zed_f9p.mk
    endif

    SOURCES_C += $(TEST_SET_HW_DIR)/test_hw_list.c
endif
