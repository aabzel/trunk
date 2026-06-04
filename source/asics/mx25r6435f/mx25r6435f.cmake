message(STATUS "MX25R6435F_MK_INC=${MX25R6435F_MK_INC}")
if( NOT (MX25R6435F_MK_INC STREQUAL Y))
    set(MX25R6435F_MK_INC Y)
    message(STATUS "+ Mx25r6435f")

    set(MX25R6435F_DIR ${ASICS_DIR}/mx25r6435f)
    message(STATUS "MX25R6435F_DIR=${MX25R6435F_DIR}")

    #message( SEND_ERROR "Check Compile" )

    add_compile_definitions(HAS_MX25R6435F)
    target_compile_definitions(app PUBLIC HAS_MX25R6435F)

    target_include_directories(app PUBLIC ${MX25R6435F_DIR})
    target_sources(app PRIVATE ${MX25R6435F_DIR}/mx25r6435f_drv.c)

    if(DIAG STREQUAL Y)
        if(MX25R6435F_DIAG STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_MX25R6435F_DIAG)
            target_sources(app PRIVATE ${MX25R6435F_DIR}/mx25r6435f_diag.c)
        endif()
    endif()

    if(CLI STREQUAL Y)
        if(MX25R6435F_COMMANDS STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_MX25R6435F_COMMANDS)
            target_sources(app PRIVATE ${MX25R6435F_DIR}/mx25r6435f_commands.c)
        endif()
    endif()
endif()
