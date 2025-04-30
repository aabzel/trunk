message(STATUS "NRF5340_ADK_INC=${NRF5340_ADK_INC}")
if(NOT (NRF5340_ADK_INC STREQUAL Y))
    set(NRF5340_ADK_INC Y)

    set(NRF5340_ADK_DIR ${BOARDS_DIR}/NRF5340_ADK)
    include_directories(${NRF5340_ADK_DIR})
    target_include_directories(app PUBLIC ${NRF5340_ADK_DIR})

    message(STATUS "Add nrf5340-DK configurations")
    message(STATUS "NRF5340_ADK_DIR=${NRF5340_ADK_DIR}")

    add_compile_definitions(HAS_NRF5340)
    target_compile_definitions(app PUBLIC HAS_NRF5340)

    target_sources(app PRIVATE ${NRF5340_ADK_DIR}/board_config.c)

    if(FDA801 STREQUAL Y)
        message(STATUS "Add FDA801 configs")
        target_sources(app PRIVATE ${NRF5340_ADK_DIR}/fda801_config.c)
    endif()

    if(PINS STREQUAL Y)
        message(STATUS "Add PINS configs")
        target_compile_definitions(app PUBLIC HAS_PINS)
    endif()

    if(BUTTON STREQUAL Y)
        message(STATUS "Add BUTTON configs")
        target_sources(app PRIVATE ${NRF5340_ADK_DIR}/button_config.c)
    endif()

    if(GPIO STREQUAL Y)
        message(STATUS "Add GPIO configs")
        target_sources(app PRIVATE ${NRF5340_ADK_DIR}/gpio_config.c)
    endif()

    if(I2C STREQUAL Y)
        message(STATUS "Add I2C configs")
        target_sources(app PRIVATE ${NRF5340_ADK_DIR}/i2c_config.c)
    endif()

    if(I2S STREQUAL Y)
        message(STATUS "Add I2S configs")
        target_sources(app PRIVATE ${NRF5340_ADK_DIR}/i2s_config.c)
    endif()

    if(CLI STREQUAL Y)
        message(STATUS "Add CLI configs")
        target_sources(app PRIVATE ${NRF5340_ADK_DIR}/cli_config.c)
    endif()

    if(SPI STREQUAL Y)
        message(STATUS "Add SPI configs")
        target_sources(app PRIVATE ${NRF5340_ADK_DIR}/spi_config.c)
    endif()

    if(UART STREQUAL Y)
        message(STATUS "Add UART configs")
        target_sources(app PRIVATE ${NRF5340_ADK_DIR}/uart_config.c)
    endif()

    if(WM8731 STREQUAL Y)
        message(STATUS "Add WM8731 configs")
        target_sources(app PRIVATE ${NRF5340_ADK_DIR}/wm8731_config.c)
    endif()
endif()


