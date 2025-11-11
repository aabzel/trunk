message(STATUS "LIS3DH_CMAKE_INC=${LIS3DH_CMAKE_INC}")
if( NOT (LIS3DH_CMAKE_INC STREQUAL Y))
    set(LIS3DH_CMAKE_INC Y)
    message(STATUS "+ LIS3DH_")

    set(LIS3DH_DIR ${ASICS_DIR}/LIS3DH)
    message(STATUS "LIS3DH_DIR=${LIS3DH_DIR}")

    message(STATUS "LIS3DH_VERIFY=[${LIS3DH_VERIFY}]")
    message(STATUS "LIS3DH_I2S_SLAVE=[${LIS3DH_I2S_SLAVE}]")
    message(STATUS "LIS3DH_I2S_MASTER=[${LIS3DH_I2S_MASTER}]")
    message(STATUS "LIS3DH_DIAG=[${LIS3DH_DIAG}]")
    message(STATUS "LIS3DH_COMMANDS=[${LIS3DH_COMMANDS}]")
    message(STATUS "LIS3DH_ADC=[${LIS3DH_ADC}]")
    message(STATUS "LIS3DH_DAC=[${LIS3DH_DAC}]")

    target_compile_definitions(app PUBLIC HAS_LIS3DH)
    target_compile_definitions(app PUBLIC HAS_LIS3DH_PROC)

    if (LIS3DH_VERIFY STREQUAL Y)
        message(STATUS "+LIS3DH_VERIFY")
        target_compile_definitions(app PUBLIC HAS_LIS3DH_VERIFY)
    endif()


    #message( SEND_ERROR "Check Compile" )

    #add_compile_definitions(HAS_LIS3DH)

    target_include_directories(app PUBLIC ${LIS3DH_DIR})
    target_sources(app PRIVATE ${LIS3DH_DIR}/lis3dh_driver.c)

    if(DIAG STREQUAL Y)
        if(LIS3DH_DIAG STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_LIS3DH_DIAG)
            target_sources(app PRIVATE ${LIS3DH_DIR}/LIS3DH_Diag.c)
        endif()
    endif()

    if(CLI STREQUAL Y)
        if(LIS3DH_COMMANDS STREQUAL Y)
            message(STATUS "+LIS3DH_COMMANDS")
            target_compile_definitions(app PUBLIC HAS_LIS3DH_COMMANDS)
            target_sources(app PRIVATE ${LIS3DH_DIR}/LIS3DH_commands.c)
        endif()
    endif()
endif()
