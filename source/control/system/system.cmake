message(STATUS "SYSTEM_CMK_INC=[${SYSTEM_CMK_INC}]")

if(NOT (SYSTEM_MK_INC STREQUAL Y))
    set(SYSTEM_MK_INC Y)

    set(SYSTEM_DIR "${CONTROL_DIR}/system")

    include_directories( ${SYSTEM_DIR})
    string(APPEND MCAL_OPT " -DHAS_SYSTEM")

    if(SYSTEM_EXT STREQUAL Y)
        string(APPEND MCAL_OPT " -DHAS_SYSTEM_EXT")
    endif()

    string(APPEND SOURCES_C " ${SYSTEM_DIR}/system.c")
    set(SYSTEM_FACILITY_TOKENS "${SYSTEM_DIR}/system_facility_tokens.h")

    if(DIAG STREQUAL Y)
        if(SYSTEM_DIAG STREQUAL Y)
            string(APPEND MCAL_OPT " -DHAS_SYSTEM_DIAG")
            string(APPEND SOURCES_DIAG_C " ${SYSTEM_DIR}/system_diag.c")
        endif()
    endif()

    if(CLI STREQUAL Y)
        if(SYSTEM_COMMANDS STREQUAL Y)
            string(APPEND MCAL_OPT " -DHAS_SYSTEM_COMMANDS")
            string(APPEND SOURCES_C " ${SYSTEM_DIR}/system_commands.c")
        endif()
    endif()

endif()

