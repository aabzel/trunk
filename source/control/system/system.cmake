message(STATUS "SYSTEM_CMK_INC=[${SYSTEM_CMK_INC}]")
if( NOT (Y STREQUAL SYSTEM_CMK_INC))
    set(SYSTEM_CMK_INC Y)
    message(STATUS "SYSTEM_CMK_INC=[${SYSTEM_CMK_INC}]")
    message(STATUS "Link System")

    set(SYSTEM_DIR ${CONTROL_DIR}/system)

    target_compile_definitions(app PUBLIC HAS_SYSTEM)
    target_include_directories(app PUBLIC ${SYSTEM_DIR})


    target_sources(app PRIVATE ${SYSTEM_DIR}/system.c)

    if(DIAG STREQUAL Y)
        if(SYSTEM_DIAG STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_SYSTEM_DIAG)
            target_sources(app PRIVATE ${SYSTEM_DIR}/system_diag.c)
        endif()
    endif()

    if(CLI STREQUAL Y)
        if(SYSTEM_COMMANDS STREQUAL Y)
            target_sources(app PRIVATE ${SYSTEM_DIR}/system_commands.c)
        endif()
    endif()
endif()
