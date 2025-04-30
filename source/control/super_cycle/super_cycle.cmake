message(STATUS "SUPER_CYCLE_MK_INC=${SUPER_CYCLE_MK_INC}")
if ( NOT ("${SUPER_CYCLE_MK_INC}" STREQUAL "Y"))
    set(SUPER_CYCLE_MK_INC Y)

    set(SUPER_CYCLE_DIR ${CONTROL_DIR}/super_cycle)
    message(STATUS "+ Super Cycle")
    message(STATUS "SUPER_CYCLE_DIR=${SUPER_CYCLE_DIR}")

    message(STATUS "DIAG=[${DIAG}]")
    message(STATUS "SUPER_CYCLE_COMMANDS=[${SUPER_CYCLE_COMMANDS}]")
    message(STATUS "SUPER_CYCLE_DIAG=[${SUPER_CYCLE_DIAG}]")

    target_compile_definitions(app PUBLIC HAS_SUPER_CYCLE)

    target_include_directories(app PUBLIC ${SUPER_CYCLE_DIR})

    target_sources(app PRIVATE ${SUPER_CYCLE_DIR}/super_cycle.c)
    target_sources(app PRIVATE ${SUPER_CYCLE_DIR}/super_cycle_config.c)

    if(DIAG STREQUAL Y)
        if(SUPER_CYCLE_DIAG STREQUAL Y)
            message(STATUS "+ Super Cycle Diag")
            target_compile_definitions(app PUBLIC HAS_SUPER_CYCLE_DIAG)
            target_sources(app PRIVATE ${SUPER_CYCLE_DIR}/super_cycle_diag.c)
        endif()
    endif()

    if(CLI STREQUAL Y)
        if(SUPER_CYCLE_COMMANDS STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_SUPER_CYCLE_COMMANDS)
            message(STATUS "+ Super Cycle Commands")
            target_sources(app PRIVATE ${SUPER_CYCLE_DIR}/super_cycle_commands.c)
        endif()
    endif()

endif()
