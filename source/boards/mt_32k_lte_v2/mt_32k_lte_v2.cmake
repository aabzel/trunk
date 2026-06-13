if(NOT (MT_32K_LTE_V2_MK_INC STREQUAL Y))
    set(MT_32K_LTE_V2_MK_INC Y )

    set(BOARD_CFG_DIR "${BOARD_DIR}/mt_32k_lte_v2")
    include_directories(${BOARD_CFG_DIR})
    
    string(APPEND MCAL_OPT " -DHAS_MT_32K_LTE_V2")
    string(APPEND MCAL_OPT " -DHSE_VALUE=25000000U")

    if(BOARD_PROC STREQUAL Y)
        string(APPEND MCAL_OPT " -DHAS_BOARD_PROC")
    endif()

    string(APPEND SOURCES_CONFIGURATION_C " ${BOARD_CFG_DIR}/board_config.c")

    if(EXT_INT STREQUAL Y)
        string(APPEND SOURCES_CONFIGURATION_C " ${BOARD_CFG_DIR}/ext_int_config.c")
    endif()

    if(GNSS STREQUAL Y)
        string(APPEND SOURCES_CONFIGURATION_C " ${BOARD_CFG_DIR}/gnss_config.c")
    endif()

    if(BH1750 STREQUAL Y)
        string(APPEND SOURCES_CONFIGURATION_C " ${BOARD_CFG_DIR}/bh1750_config.c")
    endif()

    if(BUTTON STREQUAL Y)
        string(APPEND SOURCES_CONFIGURATION_C " ${BOARD_CFG_DIR}/button_config.c")
    endif()

    if(BOARD_COMMANDS STREQUAL Y)
        string(APPEND MCAL_OPT " -DHAS_BOARD_COMMANDS")
        string(APPEND SOURCES_CONFIGURATION_C " ${BOARD_CFG_DIR}/board_commands.c")
    endif()

    if(CAN STREQUAL Y)
        string(APPEND SOURCES_CONFIGURATION_C " ${BOARD_CUSTOM_DIR}/can_config.c")
    endif()

    if(CLI STREQUAL Y)
        string(APPEND SOURCES_CONFIGURATION_C " ${BOARD_CFG_DIR}/cli_config.c")
    endif()

    if(CRYP STREQUAL Y)
        string(APPEND SOURCES_CONFIGURATION_C " ${BOARD_CFG_DIR}/cryp_config.c")
    endif()

    if(GPIO STREQUAL Y)
        string(APPEND SOURCES_CONFIGURATION_C " ${BOARD_CFG_DIR}/gpio_config.c")
    endif()

    if(DASHBOARD STREQUAL Y)
        string(APPEND SOURCES_CONFIGURATION_C " ${BOARD_CFG_DIR}/dashboard_config.c")
    endif()

    if(LIGHT_NAVIGATOR STREQUAL Y)
        string(APPEND SOURCES_CONFIGURATION_C " ${LIGHT_NAVIGATOR_DIR}/light_navigator_config.c")
    endif()

    if(HEALTH_MONITOR STREQUAL Y)
        string(APPEND SOURCES_CONFIGURATION_C " ${BOARD_CFG_DIR}/board_monitor.c")
    endif()

    if(BUZZER STREQUAL Y)
        string(APPEND SOURCES_CONFIGURATION_C " ${BOARD_CFG_DIR}/buzzer_config.c")
    endif()

    if(DS3231 STREQUAL Y)
        string(APPEND SOURCES_CONFIGURATION_C " ${BOARD_CFG_DIR}/ds3231_config.c")
    endif()

    if(FAT_FS STREQUAL Y)
        string(APPEND SOURCES_CONFIGURATION_C " ${BOARD_CFG_DIR}/fat_fs_config.c")
    endif()

    if(FREE_RTOS STREQUAL Y)
        string(APPEND SOURCES_CONFIGURATION_C " ${BOARD_CFG_DIR}/FreeRTOSConfig.c")
    endif()

    if(ISO_TP STREQUAL Y)
        string(APPEND SOURCES_CONFIGURATION_C " ${BOARD_CFG_DIR}/iso_tp_config.c")
    endif()

    if(IQUEUE STREQUAL Y)
        string(APPEND SOURCES_CONFIGURATION_C " ${BOARD_CFG_DIR}/iqueue_config.c")
    endif()

    if(KEEPASS STREQUAL Y)
        string(APPEND SOURCES_CONFIGURATION_C " ${BOARD_CFG_DIR}/keepass_config.c")
    endif()

    if(LTR390 STREQUAL Y)
        string(APPEND SOURCES_CONFIGURATION_C " ${BOARD_CFG_DIR}/ltr390_config.c")
    endif()

    if(LED_MONO STREQUAL Y)
        string(APPEND SOURCES_CONFIGURATION_C " ${BOARD_CFG_DIR}/led_mono_config.c")
    endif()

    if(LOG STREQUAL Y)
        string(APPEND SOURCES_CONFIGURATION_C " ${BOARD_CFG_DIR}/log_config.c")
    endif()

    if(MIC2026 STREQUAL Y)
        string(APPEND SOURCES_CONFIGURATION_C " ${BOARD_CFG_DIR}/mic2026_config.c")
    endif()

    if(DISK STREQUAL Y)
        string(APPEND SOURCES_CONFIGURATION_C " ${BOARD_CFG_DIR}/disk_config.c")
    endif()

    if(NMEA STREQUAL Y)
        string(APPEND SOURCES_CONFIGURATION_C " ${BOARD_CFG_DIR}/nmea_config.c")
    endif()

    if(LIGHT_SENSOR STREQUAL Y)
        string(APPEND SOURCES_CONFIGURATION_C " ${BOARD_CFG_DIR}/light_sensor_config.c")
    endif()

    if(PINS STREQUAL Y)
        string(APPEND MCAL_OPT " -DHAS_PINS")
    endif()

    if(POSTPONE_FUN STREQUAL Y)
        string(APPEND SOURCES_CONFIGURATION_C " ${BOARD_CUSTOM_DIR}/postpone_fun_config.c")
    endif()

    if(STRING_READER STREQUAL Y)
        string(APPEND SOURCES_CONFIGURATION_C " ${BOARD_CFG_DIR}/string_reader_config.c")
    endif()

    if(PWM STREQUAL Y)
        string(APPEND SOURCES_CONFIGURATION_C " ${BOARD_CUSTOM_DIR}/pwm_config.c")
    endif()

    if(I2C STREQUAL Y)
        string(APPEND MCAL_OPT " -DHAS_I2C")
        string(APPEND SOURCES_CONFIGURATION_C " ${BOARD_CFG_DIR}/i2c_config.c")
    endif()

    if(RTOS STREQUAL Y)
        string(APPEND SOURCES_CONFIGURATION_C " ${BOARD_CFG_DIR}/rtos_task_config.c")
    endif()

    if(SCHMITT_TRIGGER STREQUAL Y)
        string(APPEND SOURCES_CONFIGURATION_C " ${BOARD_CFG_DIR}/schmitt_trigger_config.c")
    endif()

    if(SPI STREQUAL Y)
        string(APPEND SOURCES_CONFIGURATION_C " ${BOARD_CFG_DIR}/spi_config.c")
    endif()

    if(SW_NVRAM STREQUAL Y)
        string(APPEND SOURCES_CONFIGURATION_C " ${BOARD_CUSTOM_DIR}/sw_nvram_config.c")
    endif()

    if(SSD1306 STREQUAL Y)
        string(APPEND SOURCES_CONFIGURATION_C " ${BOARD_CFG_DIR}/ssd1306_config.c")
    endif()

    if(SOFTWARE_TIMER STREQUAL Y)
        string(APPEND SOURCES_CONFIGURATION_C " ${BOARD_CFG_DIR}/sw_timer_config.c")
    endif()

    if(TIME STREQUAL Y)
        string(APPEND SOURCES_CONFIGURATION_C " ${BOARD_CFG_DIR}/time_config.c")
    endif()

    if(TIMER STREQUAL Y)
        string(APPEND SOURCES_CONFIGURATION_C " ${BOARD_CFG_DIR}/timer_config.c")
    endif()

    if(GARLAND STREQUAL Y)
        string(APPEND SOURCES_CONFIGURATION_C " ${BOARD_CUSTOM_DIR}/garland_config.c")
    endif()

    if(UART STREQUAL Y)
        string(APPEND SOURCES_CONFIGURATION_C " ${BOARD_CFG_DIR}/uart_config.c")
    endif()

    if(UBLOX_NEO_6M STREQUAL Y)
        string(APPEND SOURCES_CONFIGURATION_C " ${BOARD_CFG_DIR}/ublox_neo_6m_config.c")
    endif()

    if(MCAL_USB STREQUAL Y)
        string(APPEND SOURCES_CONFIGURATION_C " ${BOARD_CFG_DIR}/usb_config.c")
    endif()

    if(WRITER STREQUAL Y)
        string(APPEND SOURCES_CONFIGURATION_C " ${BOARD_CFG_DIR}/writer_config.c")
    endif()

    if(I2S STREQUAL Y)
        string(APPEND SOURCES_CONFIGURATION_C " ${BOARD_CFG_DIR}/i2s_config.c")
    endif()

    if(DMA STREQUAL Y)
        string(APPEND SOURCES_CONFIGURATION_C " ${BOARD_CFG_DIR}/dma_config.c")
    endif()

    if(UDS STREQUAL Y)
        string(APPEND SOURCES_CONFIGURATION_C " ${BOARD_CUSTOM_DIR}/uds_config.c")
    endif()

    if(ESP_01 STREQUAL Y)
        string(APPEND SOURCES_CONFIGURATION_C " ${BOARD_CFG_DIR}/esp_01_config.c")
    endif()

    if(RTC STREQUAL Y)
        string(APPEND SOURCES_CONFIGURATION_C " ${BOARD_CFG_DIR}/rtc_config.c")
    endif()

    if(XML STREQUAL Y)
        string(APPEND SOURCES_CONFIGURATION_C " ${BOARD_CFG_DIR}/xml_config.c")
    endif()

    if(TBFP STREQUAL Y)
        string(APPEND MCAL_OPT " -DTBFP_MAX_PAYLOAD=20")
        string(APPEND SOURCES_CONFIGURATION_C " ${BOARD_CFG_DIR}/tbfp_config.c")
    endif()

    if(W25Q16BV STREQUAL Y)
        string(APPEND SOURCES_CONFIGURATION_C " ${BOARD_CFG_DIR}/w25q16bv_config.c")
    endif()
    
    set(BOARD_SELECTED Y )
endif()