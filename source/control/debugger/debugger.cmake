if(NOT (DEBUGGER_MK_INC STREQUAL Y))
    set(DEBUGGER_MK_INC Y)

    set(DEBUGGER_DIR "${CONTROL_DIR}/debugger")
    include_directories(${DEBUGGER_DIR})
    
    string(APPEND MCAL_OPT " -DHAS_DEBUGGER")

    if(WRITE_ADDR STREQUAL Y)
        string(APPEND MCAL_OPT " -DHAS_WRITE_ADDR")
    endif()

    string(APPEND SOURCES_C " ${DEBUGGER_DIR}/debugger.c")

    if(CLI STREQUAL Y)
        if(DEBUGGER_COMMANDS STREQUAL Y)
            string(APPEND MCAL_OPT " -DHAS_DEBUGGER_COMMANDS")
            string(APPEND SOURCES_C " ${DEBUGGER_DIR}/debugger_commands.c")
        endif()
    endif()
endif()
