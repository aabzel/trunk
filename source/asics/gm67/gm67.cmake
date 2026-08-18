message(STATUS "GM67_MK_INC=${GM67_MK_INC}")
if( NOT (GM67_MK_INC STREQUAL Y))
    set(GM67_MK_INC Y)
    message(STATUS "+ GM67")

    set(GM67_DIR ${ASICS_DIR}/gm67)
    message(STATUS "GM67_DIR=${GM67_DIR}")

    #message(SEND_ERROR "Check Compile")

    target_compile_definitions(app PUBLIC HAS_GM67)
    target_compile_definitions(app PUBLIC HAS_GM67_PROC)

    target_include_directories(app PUBLIC ${GM67_DIR})

    target_sources(app PRIVATE ${GM67_DIR}/gm67_drv.c)

    if(DIAG STREQUAL Y)
        if(GM67_DIAG STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_GM67_DIAG)
            target_sources(app PRIVATE ${GM67_DIR}/gm67_diag.c)
        endif()
    endif()

    if(CLI STREQUAL Y)
        if(GM67_COMMANDS STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_GM67_COMMANDS)
            target_sources(app PRIVATE ${GM67_DIR}/gm67_commands.c)
        endif()
    endif()
endif()
