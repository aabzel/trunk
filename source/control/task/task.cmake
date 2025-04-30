
if( NOT (Y STREQUAL TASK_DRV_CMAKE_INC))
    set(TASK_DRV_CMAKE_INC Y)
    set(LIMITER Y)
    set(TASK Y)

    message(STATUS "+ Task component")
    set(TASK_DIR ${CONTROL_DIR}/task)

    target_include_directories(app PUBLIC ${TASK_DIR})

    target_compile_definitions(app PUBLIC HAS_TASK)
    target_compile_definitions(app PUBLIC HAS_LIMITER)
    target_compile_definitions(app PUBLIC HAS_SCHEDULER)

    #message( SEND_ERROR "TASK=${TASK}")
    target_sources(app PRIVATE ${TASK_DIR}/task_info.c)
    target_sources(app PRIVATE ${TASK_DIR}/task_config.c)

    if(DIAG STREQUAL Y)
        message(STATUS "+ TASK_DIAG")
        target_compile_definitions(app PUBLIC HAS_TASK_DIAG)
        target_sources(app PRIVATE ${TASK_DIR}/task_diag.c)
    endif()

    #message( SEND_ERROR "TASK_COMMANDS=${TASK_COMMANDS}")
    if(CLI STREQUAL Y)
         #message( SEND_ERROR "TASK_COMMANDS=${TASK_COMMANDS}")
         if(TASK_COMMANDS STREQUAL Y)
            message(STATUS "+ TASK_COMMANDS")
            target_compile_definitions(app PUBLIC HAS_TASK_COMMANDS)
            target_sources(app PRIVATE ${TASK_DIR}/task_commands.c)
        endif()
    endif()
endif()
