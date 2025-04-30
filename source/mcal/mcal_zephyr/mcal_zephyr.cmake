message(STATUS "MCAL_ZEPHYR_MK_INC=${MCAL_ZEPHYR_MK_INC}")
if( NOT (Y STREQUAL MCAL_ZEPHYR_MK_INC))
    set(MCAL_ZEPHYR_MK_INC Y)
    message(STATUS "MCAL_ZEPHYR_MK_INC=${MCAL_ZEPHYR_MK_INC}")
    message(STATUS "+ MCAL for Zephyr")

    set(MCAL_ZEPHYR_DIR ${MCAL_DIR}/mcal_zephyr)
    message(STATUS "MCAL_ZEPHYR_DIR=${MCAL_ZEPHYR_DIR}")

    target_compile_definitions(app PUBLIC HAS_ZEPHYR)
    target_compile_definitions(app PUBLIC HAS_MCAL_ZEPHYR)

    include_directories(${MCAL_ZEPHYR_DIR})
    target_include_directories(app PUBLIC ${MCAL_ZEPHYR_DIR})

    target_include_directories(app PUBLIC ${NRF_SDK_DIR}/zephyr/lib/libc/minimal/include)
    target_sources(app PRIVATE ${MCAL_ZEPHYR_DIR}/zephyr_diag.c)

    if (BLUETOOTH STREQUAL Y)
        message(STATUS "+ Zephyr bluetooth driver")
        include(${MCAL_ZEPHYR_DIR}/bluetooth/bluetooth.cmake)
    endif()

    if (CLOCK STREQUAL Y)
        message(STATUS "+ Zephyr CLOCK driver")
        message(STATUS "CLOCK=[${CLOCK}]")
        include(${MCAL_ZEPHYR_DIR}/clock/clock.cmake)
    endif()

    if (GPIO_ZEPHYR STREQUAL Y)
        message(STATUS "+ Zephyr GPIO driver")
        include(${MCAL_ZEPHYR_DIR}/gpio/z_gpio.cmake)
    endif()

    if (I2S_ZEPHYR STREQUAL Y)
        message(STATUS "+ Zephyr I2S driver")
        include(${MCAL_ZEPHYR_DIR}/i2s/i2s.cmake)
    endif()

    if (NVS_ZEPHYR STREQUAL Y)
        message(STATUS "+ NVS_ZEPHYR driver")
        include(${MCAL_ZEPHYR_DIR}/nvs/nvs.cmake)
    endif()

    if (FLASH_ZEPHYR STREQUAL Y)
        message(STATUS "+ FLASH_ZEPHYR driver")
        include(${MCAL_ZEPHYR_DIR}/flash/flash.cmake)
    endif()

    if (I2C STREQUAL Y)
        message(STATUS "+ Zephyr I2C driver")
        include(${MCAL_ZEPHYR_DIR}/i2c/i2c.cmake)
    endif()

    if (PWM_ZEPHYR STREQUAL Y)
        message(STATUS "+ Zephyr PWM driver")
        include(${MCAL_ZEPHYR_DIR}/pwm/pwm.cmake)
    endif()

    if (SPI_ZEPHYR STREQUAL Y)
        message(STATUS "+ Zephyr SPI driver")
        include(${MCAL_ZEPHYR_DIR}/spi/spi.cmake)
    endif()

    if (TIMER STREQUAL Y)
        message(STATUS "+ Zephyr TIMER driver")
        include(${MCAL_ZEPHYR_DIR}/timer/timer.cmake)
    endif()

    if (UART_ZEPHYR STREQUAL Y)
        message(STATUS "+ Zephyr UART driver")
        include(${MCAL_ZEPHYR_DIR}/uart/uart.cmake)
    endif()

    if (USB STREQUAL Y)
        message(STATUS "+ Zephyr USB driver")
        include(${MCAL_ZEPHYR_DIR}/usb/usb.cmake)
    endif()
endif()
