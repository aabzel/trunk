message(STATUS "TEST_SET_HW_MK_INC=${TEST_SET_HW_MK_INC}")
if( NOT (TEST_SET_HW_MK_INC STREQUAL Y))
    set(TEST_SET_HW_MK_INC Y)
    message(STATUS "+ HW Tests")

    set(TEST_SET_HW_DIR ${UNIT_TESTS_DIR}/test_set_hw)
    message(STATUS "TEST_SET_HW_DIR=${TEST_SET_HW_DIR}")

    target_include_directories(app PUBLIC ${TEST_SET_HW_DIR})

    target_sources(app PRIVATE ${TEST_SET_HW_DIR}/test_hw_list.c)

    message(STATUS "TEST_SYSTICK=[${TEST_SYSTICK}]")

    if (TEST_AT24CXX STREQUAL Y)
        message(STATUS "+ AT24CXX Tests")
        include(${TEST_SET_HW_DIR}/test_at24cxx/test_at24cxx.cmake)
    endif()

    if (TEST_SYSTICK STREQUAL Y)
        message(STATUS "+ SysTick Tests")
        include(${TEST_SET_HW_DIR}/test_systick/test_systick.cmake)
    endif()

    if(TEST_BC127 STREQUAL Y)
        #@echo $(error TEST_BC127=$(TEST_BC127))
        include(${TEST_SET_HW_DIR}/test_bc127/test_bc127.cmake)
    endif()

    if(TEST_MIC2026 STREQUAL Y)
        include(${TEST_SET_HW_DIR}/test_mic2026/test_mic2026.cmake)
    endif()
    
    if(TEST_SDIO STREQUAL Y)
        include(${TEST_SET_HW_DIR}/test_sdio/test_sdio.cmake)
    endif()
    
    if(TEST_CAN STREQUAL Y)
        include(${TEST_SET_HW_DIR}/test_can/test_can.cmake)
    endif()

    if(TEST_SOFTWARE_TIMER STREQUAL Y)
        include(${TEST_SET_HW_DIR}/test_sw_timer/test_sw_timer.cmake)
    endif()

    if(TEST_IWDG STREQUAL Y)
        include(${TEST_SET_HW_DIR}/test_iwdg/test_iwdg.cmake)
    endif()

    if(TEST_SD_CARD STREQUAL Y)
        include(${TEST_SET_HW_DIR}/test_sd_card/test_sd_card.cmake)
    endif()

    if(TEST_DMA STREQUAL Y)
        include(${TEST_SET_HW_DIR}/test_dma/test_dma.cmake)
    endif()

    if(TEST_FDA801 STREQUAL Y)
        include(${TEST_SET_HW_DIR}/test_fda801/test_fda801.cmake)
    endif()

    if(TEST_ALLOCATOR STREQUAL Y)
        include(${TEST_SET_HW_DIR}/test_allocator/test_allocator.cmake)
    endif()

    if(TEST_FLASH STREQUAL Y)
        include(${TEST_SET_HW_DIR}/test_flash/test_flash.cmake)
    endif()

    if(TEST_FLASH_FS STREQUAL Y)
        include(${TEST_SET_HW_DIR}/test_flash_fs/test_flash_fs.cmake)
    endif()

    if(TEST_GPIO STREQUAL Y)
        #@echo $(error TEST_GPIO=$(TEST_GPIO))
        include(${TEST_SET_HW_DIR}/test_gpio/test_gpio.cmake)
    endif()

    if(TEST_ADC STREQUAL Y)
        include(${TEST_SET_HW_DIR}/test_adc/test_adc.cmake)
    endif()

    if(TEST_I2S STREQUAL Y)
        message(STATUS "Add I2s Tests")
        include(${TEST_SET_HW_DIR}/test_i2s/test_i2s.cmake)
    endif()

    if(TEST_PARAM STREQUAL Y)
        include(${TEST_SET_HW_DIR}/test_params/test_param.cmake)
    endif()

    if(TEST_PDM STREQUAL Y)
        include(${TEST_SET_HW_DIR}/test_pdm/test_pdm.cmake)
    endif()

    if(TEST_RTC STREQUAL Y)
        include(${TEST_SET_HW_DIR}/test_rtc/test_rtc.cmake)
    endif()

    if(TEST_SPI STREQUAL Y)
        include(${TEST_SET_HW_DIR}/test_spi/test_spi.cmake)
    endif()

    if(TEST_SI4703 STREQUAL Y)
        include(${TEST_SET_HW_DIR}/test_si4703/test_si4703.cmake)
    endif()

    if(TEST_SI4737 STREQUAL Y)
        include(${TEST_SET_HW_DIR}/test_si4737/test_si4737.cmake)
    endif()

    if(TEST_SX1262 STREQUAL Y)
        include(${TEST_SET_HW_DIR}/test_sx1262/test_sx1262.cmake)
    endif()

    if(TEST_DECADRIVER STREQUAL Y)
        message(STATUS "+ test_DECADRIVER.cmake")
        include(${TEST_SET_HW_DIR}/test_decadriver/test_decadriver.cmake)
    endif()

    if(TEST_TIM STREQUAL Y)
        message(STATUS "+ test_tim.cmake")
        include(${TEST_SET_HW_DIR}/test_tim/test_tim.cmake)
    endif()

    if(TEST_WM8731 STREQUAL Y)
        message(STATUS "+ test_wm8731.cmake")
        include(${TEST_SET_HW_DIR}/test_wm8731/test_wm8731.cmake)
    endif()

    if(TEST_ZED_F9P STREQUAL Y)
        message(STATUS "+ test_zed_f9p.cmake")
        include(${TEST_SET_HW_DIR}/test_zed_f9p/test_zed_f9p.cmake)
    endif()

    if(TEST_UART STREQUAL Y)
        #@echo $(error TEST_SET_HW_DIR=${TEST_SET_HW_DIR})
        include(${TEST_SET_HW_DIR}/test_uart/test_uart.cmake)
    endif()

endif()
