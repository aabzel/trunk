message(STATUS "HEALTH_MONITOR_MK_INC=${HEALTH_MONITOR_MK_INC}")
if(NOT (HEALTH_MONITOR_MK_INC STREQUAL Y))
    set(HEALTH_MONITOR_MK_INC Y)
    message(STATUS "+ HEALTH_MONITOR")

    set(HEALTH_MONITOR_DIR ${SENSITIVITY_DIR}/health_monitor)
    message(STATUS "HEALTH_MONITOR_DIR=${HEALTH_MONITOR_DIR}")

    add_compile_definitions(HAS_HEALTH_MONITOR)
    target_compile_definitions(app PUBLIC HAS_HEALTH_MONITOR)
    target_compile_definitions(app PUBLIC HAS_HEALTH_MONITOR_PROC)

    include_directories(${HEALTH_MONITOR_DIR})
    target_include_directories(app PUBLIC ${HEALTH_MONITOR_DIR})

    target_sources(app PRIVATE ${HEALTH_MONITOR_DIR}/health_monitor.c)

    if(DIAG STREQUAL Y)
        if(HEALTH_MONITOR_DIAG STREQUAL Y)
            message(STATUS "+ health_monitor diag")
            target_compile_definitions(app PUBLIC HAS_HEALTH_MONITOR_DIAG)
            target_sources(app PRIVATE ${HEALTH_MONITOR_DIR}/health_monitor_diag.c)
        endif()
    endif()

    if(CLI STREQUAL Y)
        if(HEALTH_MONITOR_COMMANDS STREQUAL Y)
            message(STATUS "+ health_monitor commands")
            target_compile_definitions(app PUBLIC HAS_HEALTH_MONITOR_COMMANDS)
            target_sources(app PRIVATE ${HEALTH_MONITOR_DIR}/health_monitor_commands.c)
        endif()
    endif()
    
endif()