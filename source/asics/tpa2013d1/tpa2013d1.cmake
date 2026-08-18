message(STATUS "TPA2013D1_MK_INC=${TPA2013D1_MK_INC}")
if( NOT (TPA2013D1_MK_INC STREQUAL Y))
    set(TPA2013D1_MK_INC Y)
    message(STATUS "+ TPA2013D1")

    set(TPA2013D1_DIR ${ASICS_DIR}/tpa2013d1)
    message(STATUS "TPA2013D1_DIR=${TPA2013D1_DIR}")

    #message( SEND_ERROR "Check Compile" )

    add_compile_definitions(HAS_TPA2013D1)
    target_compile_definitions(app PUBLIC HAS_TPA2013D1)

    target_include_directories(app PUBLIC ${TPA2013D1_DIR})
    target_sources(app PRIVATE ${TPA2013D1_DIR}/tpa2013d1_drv.c)

    if(DIAG STREQUAL Y)
        if(TPA2013D1_DIAG STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_TPA2013D1_DIAG)
            target_sources(app PRIVATE ${TPA2013D1_DIR}/tpa2013d1_diag.c)
        endif()
    endif()

    if(CLI STREQUAL Y)
        if(TPA2013D1_COMMANDS STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_TPA2013D1_COMMANDS)
            target_sources(app PRIVATE ${TPA2013D1_DIR}/tpa2013d1_commands.c)
        endif()
    endif()
endif()
