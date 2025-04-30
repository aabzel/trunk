
message(STATUS "SWD_MK_INC=${SWD_MK_INC}")
if( NOT (SWD_MK_INC STREQUAL Y))
    set(SWD_MK_INC Y)
    message(STATUS "Link SWD General")

    set(SWD_GENERAL_DIR ${MCAL_COMMON_DIR}/swd)
    message(STATUS "SWD_GENERAL_DIR=${SWD_GENERAL_DIR}")

    #message( SEND_ERROR "Check Compile" )

    add_compile_definitions(HAS_SWD)
    target_compile_definitions(app PUBLIC HAS_SWD)

    include_directories(${SWD_GENERAL_DIR})
    target_include_directories(app PUBLIC ${SWD_GENERAL_DIR})
    
    target_sources(app PRIVATE ${SWD_GENERAL_DIR}/swd_bsp.c)

    if(SWD0 STREQUAL Y)
        target_compile_definitions(app PUBLIC HAS_SWD0)
    endif()

    if(SWD1 STREQUAL Y)
        target_compile_definitions(app PUBLIC HAS_SWD1)
    endif()

    if(SWD2 STREQUAL Y)
        target_compile_definitions(app PUBLIC HAS_SWD2)
    endif()

    if(SWD3 STREQUAL Y)
        target_compile_definitions(app PUBLIC HAS_SWD3)
    endif()

    if(DIAG STREQUAL Y)
        if(SWD_DIAG STREQUAL Y)
            target_sources(app PRIVATE ${SWD_GENERAL_DIR}/swd_diag.c)
        endif()
    endif()

    if(CLI STREQUAL Y)
        if(SWD_COMMANDS STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_SWD_COMMANDS)
            target_sources(app PRIVATE ${SWD_GENERAL_DIR}/swd_commands.c)
        endif()
    endif()
endif()

