message(STATUS "MAX9860_CMAKE_INC=${MAX9860_CMAKE_INC}")
if( NOT (MAX9860_CMAKE_INC STREQUAL Y))
    set(MAX9860_CMAKE_INC Y)
    message(STATUS "+ Max9860")

    set(MAX9860_DIR ${ASICS_DIR}/max9860)
    message(STATUS "MAX9860_DIR=${MAX9860_DIR}")

    message(STATUS "MAX9860_VERIFY=[${MAX9860_VERIFY}]")
    message(STATUS "MAX9860_I2S_SLAVE=[${MAX9860_I2S_SLAVE}]")
    message(STATUS "MAX9860_I2S_MASTER=[${MAX9860_I2S_MASTER}]")
    message(STATUS "MAX9860_DIAG=[${MAX9860_DIAG}]")
    message(STATUS "MAX9860_COMMANDS=[${MAX9860_COMMANDS}]")
    message(STATUS "MAX9860_ADC=[${MAX9860_ADC}]")
    message(STATUS "MAX9860_DAC=[${MAX9860_DAC}]")

    target_compile_definitions(app PUBLIC HAS_MAX9860)
    target_compile_definitions(app PUBLIC HAS_MAX9860_PROC)

    if (MAX9860_VERIFY STREQUAL Y)
        message(STATUS "+MAX9860_VERIFY")
        target_compile_definitions(app PUBLIC HAS_MAX9860_VERIFY)
    endif()

    if(MAX9860_I2S_SLAVE STREQUAL Y)
        message(STATUS "+HAS_MAX9860_I2S_SLAVE")
        target_compile_definitions(app PUBLIC HAS_MAX9860_I2S_SLAVE)
    endif()


    if(MAX9860_I2S_MASTER STREQUAL Y)
        message(STATUS "+HAS_MAX9860_I2S_MASTER")
        target_compile_definitions(app PUBLIC HAS_MAX9860_I2S_MASTER)
    endif()
    #message( SEND_ERROR "Check Compile" )

    #add_compile_definitions(HAS_MAX9860)

    target_include_directories(app PUBLIC ${MAX9860_DIR})
    target_sources(app PRIVATE ${MAX9860_DIR}/max9860_drv.c)

    if (MAX9860_DAC STREQUAL Y)
        #@echo ${error MAX9860_DAC=${MAX9860_DAC))
        include(${MAX9860_DIR}/dac/dac.cmake)
    endif()

    if (MAX9860_ADC STREQUAL Y)
        include(${MAX9860_DIR}/adc/adc.cmake)
    endif()

    if( NOT (MAX9860_DAC STREQUAL Y))
        if( NOT (MAX9860_ADC STREQUAL Y))
            message( SEND_ERROR "Select something")
        endif()
    endif()

    if(DIAG STREQUAL Y)
        if(MAX9860_DIAG STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_MAX9860_DIAG)
            target_sources(app PRIVATE ${MAX9860_DIR}/max9860_diag.c)
        endif()
    endif()

    if(CLI STREQUAL Y)
        if(MAX9860_COMMANDS STREQUAL Y)
            message(STATUS "+MAX9860_COMMANDS")
            target_compile_definitions(app PUBLIC HAS_MAX9860_COMMANDS)
            target_sources(app PRIVATE ${MAX9860_DIR}/max9860_commands.c)
        endif()
    endif()
endif()
