message(STATUS "W25M02GV_CMAKE_INC=${W25M02GV_CMAKE_INC}")
if( NOT (W25M02GV_CMAKE_INC STREQUAL Y))
    set(W25M02GV_CMAKE_INC Y)
    message(STATUS "+ W25m02gv")

    set(W25M02GV_DIR ${ASICS_DIR}/w25m02gv)
    message(STATUS "W25M02GV_DIR=${W25M02GV_DIR}")

    message(STATUS "W25M02GV_VERIFY=[${W25M02GV_VERIFY}]")
    message(STATUS "W25M02GV_I2S_SLAVE=[${W25M02GV_I2S_SLAVE}]")
    message(STATUS "W25M02GV_I2S_MASTER=[${W25M02GV_I2S_MASTER}]")
    message(STATUS "W25M02GV_DIAG=[${W25M02GV_DIAG}]")
    message(STATUS "W25M02GV_COMMANDS=[${W25M02GV_COMMANDS}]")
    message(STATUS "W25M02GV_ADC=[${W25M02GV_ADC}]")
    message(STATUS "W25M02GV_DAC=[${W25M02GV_DAC}]")

    target_compile_definitions(app PUBLIC HAS_W25M02GV)
    target_compile_definitions(app PUBLIC HAS_W25M02GV_PROC)

    if (W25M02GV_VERIFY STREQUAL Y)
        message(STATUS "+W25M02GV_VERIFY")
        target_compile_definitions(app PUBLIC HAS_W25M02GV_VERIFY)
    endif()


    #message( SEND_ERROR "Check Compile" )

    #add_compile_definitions(HAS_W25M02GV)

    target_include_directories(app PUBLIC ${W25M02GV_DIR})
    target_sources(app PRIVATE ${W25M02GV_DIR}/w25m02gv.c)

    if(DIAG STREQUAL Y)
        if(W25M02GV_DIAG STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_W25M02GV_DIAG)
            target_sources(app PRIVATE ${W25M02GV_DIR}/w25m02gv_diag.c)
        endif()
    endif()

    if(CLI STREQUAL Y)
        if(W25M02GV_COMMANDS STREQUAL Y)
            message(STATUS "+W25M02GV_COMMANDS")
            target_compile_definitions(app PUBLIC HAS_W25M02GV_COMMANDS)
            target_sources(app PRIVATE ${W25M02GV_DIR}/w25m02gv_commands.c)
        endif()
    endif()
endif()
