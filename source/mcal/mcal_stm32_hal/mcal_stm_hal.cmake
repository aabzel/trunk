if(NOT MCAL_STM32F4_DRV_MK_INC)
    set(MCAL_STM32F4_DRV_MK_INC Y)

    set(MCAL_CUSTOM_DIR ${MCAL_DIR}/mcal_stm_hal)

    include_directories( ${MCAL_CUSTOM_DIR})

    set(MCAL_STM32 Y)
    string(APPEND MCAL_OPT " -DHAS_MCAL_STM32")

    if(DIAG STREQUAL Y)
        string(APPEND MCAL_OPT " -DHAS_HAL_DIAG")
        string(APPEND SOURCES_DIAG_C " ${MCAL_CUSTOM_DIR}/hal_diag.c")
    endif()

    if(HAL_MSP STREQUAL Y)
        string(APPEND SOURCES_C " ${MCAL_CUSTOM_DIR}/stm32fx_hal_msp.c")
    endif()

    string(APPEND SOURCES_C " ${MCAL_CUSTOM_DIR}/stm32f4xx_it.c")
    string(APPEND SOURCES_C " ${MCAL_CUSTOM_DIR}/hal_mcal.c")

    if(ADC STREQUAL Y)
        include(${MCAL_CUSTOM_DIR}/adc/adc.cmake)
    endif()

    if(CAN STREQUAL Y)
        include(${MCAL_CUSTOM_DIR}/can/can.cmake)
    endif()

    if(CRYP_HW STREQUAL Y)
        message("Add Crypto Driver")
        include(${MCAL_CUSTOM_DIR}/cryp/cryp.cmake)
    endif()

    if(CLOCK STREQUAL Y)
        include(${MCAL_CUSTOM_DIR}/clock/clock.cmake)
    endif()

    if(CLOCK_OUT STREQUAL Y)
        include(${MCAL_CUSTOM_DIR}/clock_out/clock_out.cmake)
    endif()
    
    if(DMA STREQUAL Y)
        include(${MCAL_CUSTOM_DIR}/dma/dma.cmake)
    endif()

    if(EXT_INT STREQUAL Y)
        include(${MCAL_CUSTOM_DIR}/ext_int/ext_int.cmake)
    endif()

    if(FLASH STREQUAL Y)
        include(${MCAL_CUSTOM_DIR}/flash/flash.cmake)
    endif()

    if(GPIO STREQUAL Y)
        include(${MCAL_CUSTOM_DIR}/gpio/gpio.cmake)
    endif()

    if(I2C STREQUAL Y)
        include(${MCAL_CUSTOM_DIR}/i2c/i2c.cmake)
    endif()
    
    if(I2S STREQUAL Y)
        include(${MCAL_CUSTOM_DIR}/i2s/i2s.cmake)
    endif()

    if(INPUT_CAPTURE STREQUAL Y)
        include(${MCAL_CUSTOM_DIR}/input_capture/input_capture.cmake)
    endif()

    if(INTERRUPT STREQUAL Y)
        include(${MCAL_CUSTOM_DIR}/interrupt/interrupt.cmake)
    endif()

    if(IOMUX STREQUAL Y)
        include(${MCAL_CUSTOM_DIR}/iomux/iomux.cmake)
    endif()

    if(MPU STREQUAL Y)
        include(${MCAL_CUSTOM_DIR}/mpu/mpu.cmake)
    endif()

    if(NVS STREQUAL Y)
        include(${MCAL_CUSTOM_DIR}/nvs/nvs.cmake)
    endif()

    if(PWM STREQUAL Y)
        include(${MCAL_CUSTOM_DIR}/pwm/pwm.cmake)
    endif()

    if(RTC STREQUAL Y)
        include(${MCAL_CUSTOM_DIR}/rtc/rtc_internal.cmake)
    endif()

    if(SDIO STREQUAL Y)
        include(${MCAL_CUSTOM_DIR}/sdio/sdio.cmake)
    endif()

    if(SPI STREQUAL Y)
        include(${MCAL_CUSTOM_DIR}/spi/spi.cmake)
    endif()

    if(SYSTICK STREQUAL Y)
        include(${MCAL_CUSTOM_DIR}/systick/systick.cmake)
    endif()

    if(SWD STREQUAL Y)
        include(${MCAL_CUSTOM_DIR}/swd/swd.cmake)
    endif()

    if(TIMER STREQUAL Y)
        include(${MCAL_CUSTOM_DIR}/timer/timer.cmake)
    endif()

    if(UART STREQUAL Y)
        include(${MCAL_CUSTOM_DIR}/uart/uart.cmake)
    endif()

    if(STM32_USB STREQUAL Y)
        include(${MCAL_CUSTOM_DIR}/usb/usb.cmake)
    endif()

    if(WATCHDOG STREQUAL Y)
        include(${MCAL_CUSTOM_DIR}/watchdog/watchdog.cmake)
    endif()

endif()