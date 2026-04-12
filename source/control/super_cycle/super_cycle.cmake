message(STATUS "SUPER_CYCLE_MK_INC=${SUPER_CYCLE_MK_INC}")
if(NOT (SUPER_CYCLE_MK_INC STREQUAL Y))
    set(SUPER_CYCLE_MK_INC Y)

    set(SUPER_CYCLE_DIR "${CONTROL_DIR}/super_cycle")
    include_directories( ${SUPER_CYCLE_DIR})
    
    string(APPEND MCAL_OPT " -DHAS_SUPER_CYCLE")

    string(APPEND SOURCES_C " ${SUPER_CYCLE_DIR}/super_cycle.c")

    if(SUPER_CYCLE_MAX_PERF STREQUAL Y)
        string(APPEND MCAL_OPT " -DHAS_SUPER_CYCLE_MAX_PERF")
    endif()

    if(SUPER_CYCLE_DIAG STREQUAL Y)
        string(APPEND MCAL_OPT " -DHAS_SUPER_CYCLE_DIAG")
        string(APPEND SOURCES_C " ${SUPER_CYCLE_DIR}/super_cycle_diag.c")
    endif()

    if(CLI STREQUAL Y)
        if(SUPER_CYCLE_COMMANDS STREQUAL Y)
            string(APPEND MCAL_OPT " -DHAS_SUPER_CYCLE_COMMANDS")
            string(APPEND SOURCES_C " ${SUPER_CYCLE_DIR}/super_cycle_commands.c")
        endif()
    endif()
endif()

