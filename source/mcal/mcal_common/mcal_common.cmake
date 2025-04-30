
message(STATUS "MCAL_COMMMON_MK_INC=${MCAL_COMMMON_MK_INC}")

if( NOT (MCAL_COMMMON_MK_INC STREQUAL Y))
    set(MCAL_COMMMON_MK_INC Y)

    set(MCAL_COMMON_DIR ${MCAL_DIR}/mcal_common)
    message(STATUS "+ MCAL Common")
    message(STATUS "MCAL_COMMON_DIR=${MCAL_COMMON_DIR}")

    target_compile_definitions(app PUBLIC HAS_MCAL_COMMON)
    target_compile_definitions(app PUBLIC HAS_MCAL_COMMANDS)
    target_include_directories(app PUBLIC ${MCAL_COMMON_DIR})

    if(ADC STREQUAL Y)
        message(STATUS "+ ADC Common")
        include(${MCAL_COMMON_DIR}/adc/adc.cmake)
    endif()

    if(CLOCK STREQUAL Y)
        message(STATUS "+ CLOCK Common")
        include(${MCAL_COMMON_DIR}/clock/clock.cmake)
    endif()

    if(GPIO STREQUAL Y)
        message(STATUS "+ GPIO Common")
        include(${MCAL_COMMON_DIR}/gpio/gpio.cmake)
    endif()

    if(I2C STREQUAL Y)
        message(STATUS "+ I2C Common")
        include(${MCAL_COMMON_DIR}/i2c/i2c.cmake)
    endif()

    if(I2S STREQUAL Y)
        message(STATUS "+ I2S Common")
        include(${MCAL_COMMON_DIR}/i2s/i2s.cmake)
    endif()

    if(NVS STREQUAL Y)
        message(STATUS "+ NVS Common")
        include(${MCAL_COMMON_DIR}/nvs/nvs.cmake)
    endif()

    if(PWM STREQUAL Y)
        message(STATUS "+ PWM Common")
        include(${MCAL_COMMON_DIR}/pwm/pwm.cmake)
    endif()

    if(RTC STREQUAL Y)
        include(${MCAL_COMMON_DIR}/rtc/rtc.cmake)
    endif()

    if(SPI STREQUAL Y)
        include(${MCAL_COMMON_DIR}/spi/spi.cmake)
    endif()

    if(FLASH STREQUAL Y)
        include(${MCAL_COMMON_DIR}/flash/flash.cmake)
    endif()

    if(UART STREQUAL Y)
        include(${MCAL_COMMON_DIR}/uart/uart.cmake)
    endif()

    if(USB STREQUAL Y)
        include(${MCAL_COMMON_DIR}/usb/usb.cmake)
    endif()
endif()