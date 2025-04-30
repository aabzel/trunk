message(STATUS "CONFIG_VERIFY_INC=${CONFIG_VERIFY_INC}")
if(NOT (CONFIG_VERIFY_INC STREQUAL Y))
    set(CONFIG_VERIFY_INC Y)


    message(STATUS "Vefify configurations")

    if(FDA801 STREQUAL Y)
        message(STATUS "Add FDA801 configs")
    endif()

    if(PINS STREQUAL Y)
        message(STATUS "Add PINS configs")
    endif()

    if(BUTTON STREQUAL Y)
        message(STATUS "Add BUTTON configs")
    endif()

    if(GPIO STREQUAL Y)
        message(STATUS "Add GPIO configs")
    endif()

    if(I2C STREQUAL Y)
        message(STATUS "Add I2C configs")
    endif()

    if(I2S STREQUAL Y)
        message(STATUS "Add I2S configs")
    endif()

    if(SPI STREQUAL Y)
        message(STATUS "Add SPI configs")
    endif()
endif()


