
if(NOT (SCHEDULER_DRV_MK_INC STREQUAL Y))
    set(SCHEDULER_DRV_MK_INC Y)

    set(SCHEDULER_DIR "${CONTROL_DIR}/scheduler")

    include_directories(${SCHEDULER_DIR})

    string(APPEND MCAL_OPT " -DHAS_SCHEDULER")

    if(SCHEDULER_EXT STREQUAL Y)
        string(APPEND MCAL_OPT " -DHAS_SCHEDULER_EXT")
    endif()

    string(APPEND SOURCES_C " ${SCHEDULER_DIR}/scheduler_mcal.c")

    if(SCHEDULER_DIAG STREQUAL Y)
        string(APPEND MCAL_OPT " -DHAS_SCHEDULER_DIAG")
        string(APPEND SOURCES_C " ${SCHEDULER_DIR}/scheduler_diag.c")
    endif()

    if(CLI STREQUAL Y)
        if(SCHEDULER_COMMANDS STREQUAL Y)
            string(APPEND MCAL_OPT " -DHAS_SCHEDULER_COMMANDS")
            string(APPEND SOURCES_C " ${SCHEDULER_DIR}/scheduler_commands.c")
        endif()
    endif()
endif()

