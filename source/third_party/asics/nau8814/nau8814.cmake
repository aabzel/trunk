message(STATUS "NAU8814_CMAKE_INC=${NAU8814_CMAKE_INC}")
if( NOT (NAU8814_CMAKE_INC STREQUAL Y))
    set(NAU8814_CMAKE_INC Y)
    message(STATUS "+ Nau8814")

    set(NAU8814_DIR ${ASICS_DIR}/nau8814)
    message(STATUS "NAU8814_DIR=${NAU8814_DIR}")

    message(STATUS "NAU8814_VERIFY=[${NAU8814_VERIFY}]")
    message(STATUS "NAU8814_I2S_SLAVE=[${NAU8814_I2S_SLAVE}]")
    message(STATUS "NAU8814_I2S_MASTER=[${NAU8814_I2S_MASTER}]")
    message(STATUS "NAU8814_DIAG=[${NAU8814_DIAG}]")
    message(STATUS "NAU8814_CLI=[${NAU8814_CLI}]")
    message(STATUS "NAU8814_ADC=[${NAU8814_ADC}]")
    message(STATUS "NAU8814_DAC=[${NAU8814_DAC}]")

    target_compile_definitions(app PUBLIC HAS_NAU8814)
    target_compile_definitions(app PUBLIC HAS_NAU8814_PROC)

    if (NAU8814_VERIFY STREQUAL Y)
        message(STATUS "+NAU8814_VERIFY")
        target_compile_definitions(app PUBLIC HAS_NAU8814_VERIFY)
    endif()

    if(NAU8814_I2S_SLAVE STREQUAL Y)
        message(STATUS "+HAS_NAU8814_I2S_SLAVE")
        target_compile_definitions(app PUBLIC HAS_NAU8814_I2S_SLAVE)
    endif()


    if(NAU8814_I2S_MASTER STREQUAL Y)
        message(STATUS "+HAS_NAU8814_I2S_MASTER")
        target_compile_definitions(app PUBLIC HAS_NAU8814_I2S_MASTER)
    endif()
    #message( SEND_ERROR "Check Compile" )

    #add_compile_definitions(HAS_NAU8814)

    target_include_directories(app PUBLIC ${NAU8814_DIR})
    target_sources(app PRIVATE ${NAU8814_DIR}/nau8814_driver.c)

    if (NAU8814_DAC STREQUAL Y)
        #@echo ${error NAU8814_DAC=${NAU8814_DAC))
        include(${NAU8814_DIR}/dac/dac.cmake)
    endif()

    if (NAU8814_ADC STREQUAL Y)
        include(${NAU8814_DIR}/adc/adc.cmake)
    endif()

    if( NOT (NAU8814_DAC STREQUAL Y))
        if( NOT (NAU8814_ADC STREQUAL Y))
            message( SEND_ERROR "Select something")
        endif()
    endif()

    if(DIAG STREQUAL Y)
        if(NAU8814_DIAG STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_NAU8814_DIAG)
            target_sources(app PRIVATE ${NAU8814_DIR}/nau8814_diagnostic.c)
        endif()
    endif()

    if(CLI STREQUAL Y)
        if(NAU8814_CLI STREQUAL Y)
            message(STATUS "+NAU8814_CLI")
            target_compile_definitions(app PUBLIC HAS_NAU8814_CLI)
            target_sources(app PRIVATE ${NAU8814_DIR}/nau8814_cli.c)
        endif()
    endif()
endif()
