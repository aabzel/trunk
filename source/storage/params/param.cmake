
message(STATUS "PARAM_MK_INC=${PARAM_MK_INC}")
if( NOT (PARAM_MK_INC STREQUAL Y))
    set(PARAM_MK_INC Y)
    message(STATUS "+PARAM")

    set(PARAM_DIR ${STORAGE_DIR}/params)
    message(STATUS "PARAM_DIR=${PARAM_DIR}")
    target_include_directories(app PUBLIC ${PARAM_DIR})

    add_compile_definitions(HAS_PARAM)
    target_compile_definitions(app PUBLIC HAS_PARAM)

    target_sources(app PRIVATE ${PARAM_DIR}/param_drv.c)

    if(PARAM_SET STREQUAL Y)
        target_compile_definitions(app PUBLIC HAS_PARAM_SET)
    endif()

    if(DIAG STREQUAL Y)
        if(PARAM_DIAG STREQUAL Y)
            message(STATUS "+PARAM_DIAG")
            target_compile_definitions(app PUBLIC HAS_PARAM_DIAG)
            target_sources(app PRIVATE ${PARAM_DIR}/param_diag.c)
        endif()
    endif()

    if(CLI STREQUAL Y)
        if(PARAM_COMMANDS STREQUAL Y)
            message(STATUS "+PARAM_COMMANDS")
            target_compile_definitions(app PUBLIC HAS_PARAM_COMMANDS)
            target_sources(app PRIVATE ${PARAM_DIR}/param_commands.c)
        endif()
    endif()
	
endif()
