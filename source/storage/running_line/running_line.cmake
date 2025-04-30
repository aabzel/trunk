
message(STATUS "RUNNING_LINE_MK_INC=${RUNNING_LINE_MK_INC}")
if( NOT (RUNNING_LINE_MK_INC STREQUAL Y))
    set(RUNNING_LINE_MK_INC Y)
    message(STATUS "+RUNNING_LINE")

    set(RUNNING_LINE_DIR ${STORAGE_DIR}/running_line)
    message(STATUS "RUNNING_LINE_DIR=${RUNNING_LINE_DIR}")
    target_include_directories(app PUBLIC ${RUNNING_LINE_DIR})

    add_compile_definitions(HAS_RUNNING_LINE)
    target_compile_definitions(app PUBLIC HAS_RUNNING_LINE)

    target_sources(app PRIVATE ${RUNNING_LINE_DIR}/running_line.c)

    if(DIAG STREQUAL Y)
        if(RUNNING_LINE_DIAG STREQUAL Y)
            message(STATUS "+RUNNING_LINE_DIAG")
            target_compile_definitions(app PUBLIC HAS_RUNNING_LINE_DIAG)
            target_sources(app PRIVATE ${RUNNING_LINE_DIR}/running_line_diag.c)
        endif()
    endif()

    if(CLI STREQUAL Y)
        if(RUNNING_LINE_COMMANDS STREQUAL Y)
            message(STATUS "+RUNNING_LINE_COMMANDS")
            target_compile_definitions(app PUBLIC HAS_RUNNING_LINE_COMMANDS)
            target_sources(app PRIVATE ${RUNNING_LINE_DIR}/running_line_commands.c)
        endif()
    endif()
	
endif()
