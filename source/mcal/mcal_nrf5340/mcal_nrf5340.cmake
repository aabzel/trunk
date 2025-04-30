
message(STATUS "MCAL_NRF5340_MK_INC=${MCAL_NRF5340_MK_INC}")
if( NOT (Y STREQUAL MCAL_NRF5340_MK_INC))
    set(MCAL_NRF5340_MK_INC Y)
    message(STATUS "+ MCAL for Nrf5340")

    set(MCAL_NRF5340_DIR ${MCAL_DIR}/mcal_nrf5340)
    include_directories(${MCAL_NRF5340_DIR})

    message(STATUS "MCAL_NRF5340_DIR=${MCAL_NRF5340_DIR}")
    message(STATUS "I2S_NRFX=${I2S_NRFX}")
    message(STATUS "In MCAL for NRF5340 NRF_SDK_DIR=${NRF_SDK_DIR}")
    add_compile_definitions(HAS_NRF5340)
    target_compile_definitions(app PUBLIC HAS_NRF5340)
    target_compile_definitions(app PUBLIC HAS_MCAL_NRF5340)
    target_compile_definitions(app PUBLIC NRFX_CUSTOM_ERROR_CODES=1)

    target_include_directories(app PUBLIC ${MCAL_NRF5340_DIR})

    include_directories(${NRF_SDK_DIR}/modules/hal/nordic/nrfx)
    include_directories(${NRF_SDK_DIR}/modules/hal/nordic/nrfx/mdk)
    include_directories(${NRF_SDK_DIR}/modules/hal/nordic/nrfx/drivers/include)

    target_sources(app PRIVATE ${MCAL_NRF5340_DIR}/hal_nrfx_diag.c)

    message(STATUS "MCAL_NRF5340_DIR=${MCAL_NRF5340_DIR}")

    if(ADC_NRFX STREQUAL Y)
        message(STATUS "+ ADC Nrfx")
        include(${MCAL_NRF5340_DIR}/adc/adc.cmake)
    endif()

    if(GPIO_NRFX STREQUAL Y)
        message(STATUS "+ GPIO Nrfx")
        include(${MCAL_NRF5340_DIR}/gpio/gpio.cmake)
    endif()

    if(I2S_NRFX STREQUAL Y)
        message(STATUS "+ I2S Nrfx")
        include(${MCAL_NRF5340_DIR}/i2s/i2s.cmake)
    endif()

    if(I2C_NRFX STREQUAL Y)
        message(STATUS "+ I2C Nrfx")
        include(${MCAL_NRF5340_DIR}/i2c/i2c.cmake)
    endif()

    if(FLASH_NRFX STREQUAL Y)
        message(STATUS "+ FLASH Nrfx")
        include(${MCAL_NRF5340_DIR}/flash/flash.cmake)
    endif()

    if(NVS_NRFX STREQUAL Y)
        message(STATUS "+ NVS Nrfx")
        include(${MCAL_NRF5340_DIR}/nvs/nvs.cmake)
    endif()

    if(PWM_NRFX STREQUAL Y)
        message(STATUS "+ PWM_NRFX")
        include(${MCAL_NRF5340_DIR}/pwm/pwm.cmake)
    endif()

    if(RTC_NRFX STREQUAL Y)
        message(STATUS "+ RTC Nrfx")
        include(${MCAL_NRF5340_DIR}/rtc/rtc.cmake)
    endif()

    if(SPI_NRFX STREQUAL Y)
        message(STATUS "+ SPI Nrfx")
        include(${MCAL_NRF5340_DIR}/spi/spi.cmake)
    endif()

    if(UART_NRFX STREQUAL Y)
        message(STATUS "+ UART Nrfx")
        include(${MCAL_NRF5340_DIR}/uart/uart.cmake)
    endif()
endif()