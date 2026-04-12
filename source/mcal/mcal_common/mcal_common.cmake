

if(NOT (MCAL_COMMON_MK_INC STREQUAL Y))
    set(MCAL_COMMON_MK_INC Y)

    set(MCAL_COMMON_DIR "${MCAL_DIR}/mcal_common")

    include_directories(${MCAL_COMMON_DIR})

    string(APPEND MCAL_OPT " -DHAS_MCAL")
    string(APPEND MCAL_OPT " -DHAS_MCAL_COMMANDS")

    if(DIAG STREQUAL Y)
        string(APPEND SOURCES_C " ${MCAL_COMMON_DIR}/mcal_diag.c")
    endif()

    if(ACC STREQUAL Y)
        include(${MCAL_COMMON_DIR}/acc/acc.cmake)
    endif()

    if(ADC STREQUAL Y)
        include(${MCAL_COMMON_DIR}/adc/adc.cmake)
    endif()

    if(LOCKSTEP STREQUAL Y)
        include(${MCAL_COMMON_DIR}/lockstep/lockstep.cmake)
    endif()

    if(MULTICORE STREQUAL Y)
        include(${MCAL_COMMON_DIR}/multicore/multicore.cmake)
    endif()

    if(MAILBOX STREQUAL Y)
        include(${MCAL_COMMON_DIR}/mailbox/mailbox.cmake)
    endif()

    if(CLOCK_OUT STREQUAL Y)
        include(${MCAL_COMMON_DIR}/clock_out/clock_out.cmake)
    endif()

    if(CAN STREQUAL Y)
        include(${MCAL_COMMON_DIR}/can/can.cmake)
    endif()

    if(EIM STREQUAL Y)
        include(${MCAL_COMMON_DIR}/eim/eim.cmake)
    endif()

    if(ERM STREQUAL Y)
        include(${MCAL_COMMON_DIR}/erm/erm.cmake)
    endif()

    if(EEPROM STREQUAL Y)
        include(${MCAL_COMMON_DIR}/eeprom/eeprom.cmake)
    endif()

    if(CLOCK STREQUAL Y)
        include(${MCAL_COMMON_DIR}/clock/clock.cmake)
    endif()

    if(POWER STREQUAL Y)
        include(${MCAL_COMMON_DIR}/power/power.cmake)
    endif()

    if(PIN STREQUAL Y)
        include(${MCAL_COMMON_DIR}/pin/pin.cmake)
    endif()

    if(DAC STREQUAL Y)
        include(${MCAL_COMMON_DIR}/dac/dac.cmake)
    endif()

    if(DMA STREQUAL Y)
        include(${MCAL_COMMON_DIR}/dma/dma.cmake)
    endif()

    if(DMA_CHANNEL STREQUAL Y)
        include(${MCAL_COMMON_DIR}/dma_channel/dma_channel.cmake)
    endif()

    if(EXT_INT STREQUAL Y)
        include(${MCAL_COMMON_DIR}/ext_int/ext_int.cmake)
    endif()

    if(FCSMU STREQUAL Y)
        include(${MCAL_COMMON_DIR}/fcsmu/fcsmu.cmake)
    endif()

    if(FLASH STREQUAL Y)
        include(${MCAL_COMMON_DIR}/flash/flash.cmake)
    endif()

    if(GPIO STREQUAL Y)
        include(${MCAL_COMMON_DIR}/gpio/gpio.cmake)
    endif()

    if(INTERRUPT STREQUAL Y)
        include(${MCAL_COMMON_DIR}/interrupt/interrupt.cmake)
    endif()

    if(I2C STREQUAL Y)
        include(${MCAL_COMMON_DIR}/i2c/i2c.cmake)

        if(I2C_FSM STREQUAL Y)
            include(${MCAL_COMMON_DIR}/i2c_fsm/i2c_fsm.cmake)
        endif()
    endif()

    if(I2S STREQUAL Y)
        include(${MCAL_COMMON_DIR}/i2s/i2s.cmake)
    endif()

    if(I2S_FULL_DUPLEX STREQUAL Y)
        include(${MCAL_COMMON_DIR}/i2s_full_duplex/i2s_full_duplex.cmake)
    endif()

    if(INPUT_CAPTURE STREQUAL Y)
        include(${MCAL_COMMON_DIR}/input_capture/input_capture.cmake)
    endif()

    if(IOMUX STREQUAL Y)
        include(${MCAL_COMMON_DIR}/iomux/iomux.cmake)
    endif()

    if(NVS STREQUAL Y)
        include(${MCAL_COMMON_DIR}/nvs/nvs.cmake)
    endif()

    if(MAM STREQUAL Y)
        include(${MCAL_COMMON_DIR}/mam/mam.cmake)
    endif()

    if(MPU STREQUAL Y)
        include(${MCAL_COMMON_DIR}/mpu/mpu.cmake)
    endif()

    if(PDM STREQUAL Y)
        include(${MCAL_COMMON_DIR}/pdm/pdm.cmake)
    endif()

    if(RTC STREQUAL Y)
        include(${MCAL_COMMON_DIR}/rtc/rtc.cmake)
    endif()

    if(PWM STREQUAL Y)
        include(${MCAL_COMMON_DIR}/pwm/pwm.cmake)
    endif()

    if(QSPI STREQUAL Y)
        include(${MCAL_COMMON_DIR}/qspi/qspi.cmake)
    endif()

    if(SPIFI STREQUAL Y)
        include(${MCAL_COMMON_DIR}/spifi/spifi.cmake)
    endif()

    if(SWD STREQUAL Y)
        include(${MCAL_COMMON_DIR}/swd/swd.cmake)
    endif()

    if(SDIO STREQUAL Y)
        include(${MCAL_COMMON_DIR}/sdio/sdio.cmake)
    endif()

    if(SPI STREQUAL Y)
        include(${MCAL_COMMON_DIR}/spi/spi.cmake)
    endif()

    if(TRNG STREQUAL Y)
        include(${MCAL_COMMON_DIR}/trng/trng.cmake)
    endif()

    if(TIMER STREQUAL Y)
        include(${MCAL_COMMON_DIR}/timer/timer.cmake)
    endif()

    if(UART STREQUAL Y)
        include(${MCAL_COMMON_DIR}/uart/uart.cmake)
    endif()

    if(TRG STREQUAL Y)
        include(${MCAL_COMMON_DIR}/trg/trg.cmake)
    endif()

    if(MCAL_USB STREQUAL Y)
        include(${MCAL_COMMON_DIR}/usb/usb.cmake)
    endif()

    if(WATCHDOG STREQUAL Y)
        include(${MCAL_COMMON_DIR}/watchdog/watchdog.cmake)
    endif()
endif()
