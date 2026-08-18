message(STATUS "SA51034_CMAKE_INC=${SA51034_CMAKE_INC}")
if( NOT (SA51034_CMAKE_INC STREQUAL Y))
    set(SA51034_CMAKE_INC Y)
    message(STATUS "+ Sa51034")

    set(SA51034_DIR ${ASICS_DIR}/sa51034)
    message(STATUS "SA51034_DIR=${SA51034_DIR}")

    message(STATUS "SA51034_VERIFY=[${SA51034_VERIFY}]")
    message(STATUS "SA51034_I2S_SLAVE=[${SA51034_I2S_SLAVE}]")
    message(STATUS "SA51034_I2S_MASTER=[${SA51034_I2S_MASTER}]")
    message(STATUS "SA51034_DIAG=[${SA51034_DIAG}]")
    message(STATUS "SA51034_COMMANDS=[${SA51034_COMMANDS}]")
    message(STATUS "SA51034_ADC=[${SA51034_ADC}]")
    message(STATUS "SA51034_DAC=[${SA51034_DAC}]")

    target_compile_definitions(app PUBLIC HAS_SA51034)
    target_compile_definitions(app PUBLIC HAS_SA51034_PROC)

    if (SA51034_VERIFY STREQUAL Y)
        message(STATUS "+SA51034_VERIFY")
        target_compile_definitions(app PUBLIC HAS_SA51034_VERIFY)
    endif()


    #message( SEND_ERROR "Check Compile" )

    #add_compile_definitions(HAS_SA51034)

    target_include_directories(app PUBLIC ${SA51034_DIR})
    target_sources(app PRIVATE ${SA51034_DIR}/sa51034_drv.c)

    if(DIAG STREQUAL Y)
        if(SA51034_DIAG STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_SA51034_DIAG)
            target_sources(app PRIVATE ${SA51034_DIR}/sa51034_diag.c)
        endif()
    endif()

    if(CLI STREQUAL Y)
        if(SA51034_COMMANDS STREQUAL Y)
            message(STATUS "+SA51034_COMMANDS")
            target_compile_definitions(app PUBLIC HAS_SA51034_COMMANDS)
            target_sources(app PRIVATE ${SA51034_DIR}/sa51034_commands.c)
        endif()
    endif()
endif()
