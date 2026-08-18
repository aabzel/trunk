message(STATUS "FDA801_MK_INC=${FDA801_MK_INC}")
if( NOT (FDA801_MK_INC STREQUAL Y))
    set(FDA801_MK_INC Y)
    message(STATUS "+ Fda801")

    set(FDA801_DIR ${ASICS_DIR}/fda801)
    message(STATUS "FDA801_DIR=${FDA801_DIR}")

    #message( SEND_ERROR "Check Compile")

    add_compile_definitions(HAS_FDA801)
    target_compile_definitions(app PUBLIC HAS_FDA801)

    target_include_directories(app PUBLIC ${FDA801_DIR})
    target_sources(app PRIVATE ${FDA801_DIR}/fda801_drv.c)

    if(DIAG STREQUAL Y)
        if(FDA801_DIAG STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_FDA801_DIAG)
            target_sources(app PRIVATE ${FDA801_DIR}/fda801_diag.c)
        endif()
    endif()

    if(CLI STREQUAL Y)
        if(FDA801_COMMANDS STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_FDA801_COMMANDS)
            target_sources(app PRIVATE ${FDA801_DIR}/fda801_commands.c)
        endif()
    endif()
endif()
