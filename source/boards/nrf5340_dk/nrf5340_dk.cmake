message(STATUS "NRF5340_DK_INC=${NRF5340_DK_INC}")
if(NOT (NRF5340_DK_INC  STREQUAL  Y))
    set(NRF5340_DK_INC Y)

    set(BOARD_CFG_DIR ${BOARDS_DIR}/nrf5340_dk)
    include_directories(${BOARD_CFG_DIR})
    target_include_directories(app PUBLIC ${BOARD_CFG_DIR})

    message(STATUS "+ nrf5340-DK configurations")
    message(STATUS "BOARD_CFG_DIR=${BOARD_CFG_DIR}")

    add_compile_definitions(HAS_NRF5340)
    target_compile_definitions(app PUBLIC HAS_NRF5340)

    target_sources(app PRIVATE ${BOARD_CFG_DIR}/board_config.c)

    if (AUTO_BRIGHTNESS STREQUAL Y)
        message(STATUS "+ AUTO_BRIGHTNESS configs")
        target_sources(app PRIVATE ${BOARD_CFG_DIR}/auto_brightness_config.c)
    endif()
    
    if (BT_BLE_UWB_TAG_CFG STREQUAL Y)
        message(STATUS "+ BT_BLE_UWB_TAG_CFG")
        target_compile_definitions(app PUBLIC HAS_BT_BLE_UWB_TAG_CFG)
    endif()

    if (DASHBOARD STREQUAL Y)
        message(STATUS "+ DASHBOARD configs")
        target_sources(app PRIVATE ${BOARD_CFG_DIR}/dashboard_config.c)
    endif()

    if (DECAWAVE STREQUAL Y)
        message(STATUS "+ DECAWAVE configs")
        target_sources(app PRIVATE ${BOARD_CFG_DIR}/decawave_proto_config.c)
    endif()

    if (DISTANCE STREQUAL Y)
        message(STATUS "+ DISTANCE configs")
        target_sources(app PRIVATE ${BOARD_CFG_DIR}/distance_config.c)
    endif()

    if (DS_TWR STREQUAL Y)
        message(STATUS "+ DS_TWR configs")
        target_sources(app PRIVATE ${BOARD_CFG_DIR}/ds_twr_config.c)
    endif()

    if(BT1026 STREQUAL Y)
        message(STATUS "+ BT1026 configs")
        target_sources(app PRIVATE ${BOARD_CFG_DIR}/bt1026_config.c)
    endif()

    if(BUTTON STREQUAL Y)
        message(STATUS "+ BUTTON configs")
        target_sources(app PRIVATE ${BOARD_CFG_DIR}/button_config.c)
    endif()

    if (CLI STREQUAL Y)
        message(STATUS "+ CLI configs")
        target_sources(app PRIVATE ${BOARD_CFG_DIR}/cli_config.c)
    endif()

    if(DW1000 STREQUAL Y)
        message(STATUS "+ DW1000 configs")
        target_sources(app PRIVATE ${BOARD_CFG_DIR}/dw1000_config.c)
    endif()

    if(DWM1000 STREQUAL Y)
        message(STATUS "+ DWM1000 configs")
        target_sources(app PRIVATE ${BOARD_CFG_DIR}/dwm1000_config.c)
    endif()

    if (DECADRIVER STREQUAL Y)
        message(STATUS "+ DECADRIVER configs")
        target_sources(app PRIVATE ${BOARD_CFG_DIR}/decadriver_config.c)
    endif()

    if (FDA801 STREQUAL Y)
        message(STATUS "+ FDA801 configs")
        target_sources(app PRIVATE ${BOARD_CFG_DIR}/fda801_config.c)
    endif()

    if (GPIO STREQUAL Y)
        message(STATUS "+ GPIO configs")
        target_sources(app PRIVATE ${BOARD_CFG_DIR}/gpio_config.c)
    endif()

    if (I2C STREQUAL Y)
        message(STATUS "+ I2C configs")
        target_sources(app PRIVATE ${BOARD_CFG_DIR}/i2c_config.c)
    endif()

    if (I2S STREQUAL Y)
        message(STATUS "+ I2S configs")
        target_sources(app PRIVATE ${BOARD_CFG_DIR}/i2s_config.c)
    endif()

    if (LED_MONO STREQUAL Y)
        message(STATUS "+ LED_MONO configs")
        target_sources(app PRIVATE ${BOARD_CFG_DIR}/led_mono_config.c)
    endif()

    if (MAX98357 STREQUAL Y)
        message(STATUS "+ MAX98357 configs")
        target_sources(app PRIVATE ${BOARD_CFG_DIR}/max98357_config.c)
    endif()

    if (PINS STREQUAL Y)
        message(STATUS "+ PINS configs")
        target_compile_definitions(app PUBLIC HAS_PINS)
    endif()

    if (PWM STREQUAL Y)
        message(STATUS "+ PWM configs")
        target_sources(app PRIVATE ${BOARD_CFG_DIR}/pwm_config.c)
    endif()

    if (SPI STREQUAL Y)
        message(STATUS "+ SPI configs")
        target_sources(app PRIVATE ${BOARD_CFG_DIR}/spi_config.c)
    endif()

    if (SSD1306 STREQUAL Y)
        message(STATUS "+ SSD1306 configs")
        target_sources(app PRIVATE ${BOARD_CFG_DIR}/ssd1306_config.c)
    endif()

    if (TBFP STREQUAL Y)
        message(STATUS "+ TBFP configs")
        target_compile_definitions(app PUBLIC TBFP_MAX_PAYLOAD=350)
        target_sources(app PRIVATE ${BOARD_CFG_DIR}/tbfp_config.c)
    endif()

    if (SCHMITT_TRIGGER STREQUAL Y)
        message(STATUS "+ SCHMITT_TRIGGER configs")
        target_sources(app PRIVATE ${BOARD_CFG_DIR}/schmitt_trigger_config.c)
    endif()

    if (UART STREQUAL Y)
        message(STATUS "+ UART configs")
        target_sources(app PRIVATE ${BOARD_CFG_DIR}/uart_config.c)
    endif() 

    if (WM8731 STREQUAL Y)
        message(STATUS "+ WM8731 configs")
        target_sources(app PRIVATE ${BOARD_CFG_DIR}/wm8731_config.c)
    endif()

    if (ZEPHYR_RTOS STREQUAL Y)
        message(STATUS "+ ZEPHYR_RTOS configs")
        target_sources(app PRIVATE ${BOARD_CFG_DIR}/zephyr_rtos_config.c)
    endif()
endif()


