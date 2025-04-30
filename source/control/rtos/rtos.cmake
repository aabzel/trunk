message(STATUS "RTOS_MK_INC=${RTOS_MK_INC}")
if( NOT (RTOS_MK_INC STREQUAL Y))
    set(RTOS_MK_INC Y)
    message(STATUS "+ RTOS")

    set(RTOS_DIR ${CONTROL_DIR}/rtos)
    message(STATUS "RTOS_DIR=${RTOS_DIR}")

    target_include_directories(app PUBLIC ${RTOS_DIR})
    message(STATUS "ZEPHYR_BASE=${ZEPHYR_BASE}")

    target_compile_definitions(app PUBLIC HAS_RTOS)
    target_sources(app PRIVATE ${RTOS_DIR}/rtos_drv.c)

    if(DIAG STREQUAL Y)
        if(RTOS_DIAG STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_RTOS_DIAG)
            target_sources(app PRIVATE ${RTOS_DIR}/rtos_diag.c)
        endif()
    endif()

    if(CLI STREQUAL Y)
        if(RTOS_COMMANDS STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_RTOS_COMMANDS)
            target_sources(app PRIVATE ${RTOS_DIR}/rtos_commands.c)
        endif()
    endif()
endif()
