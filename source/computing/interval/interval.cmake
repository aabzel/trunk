message(STATUS "INTERVAL_MK_INC=${INTERVAL_MK_INC}")
if(NOT (INTERVAL_MK_INC STREQUAL Y))
    set(INTERVAL_MK_INC Y )
    
    set(INTERVAL_DIR "${COMPUTING_DIR}/interval")
    
    string(APPEND MCAL_OPT " -DHAS_INTERVAL")
    string(APPEND INCDIR " ${INTERVAL_DIR}")
    
    string(APPEND SOURCES_C " ${INTERVAL_DIR}/interval.c")
    
    if(INTERVAL_DIAG STREQUAL Y)
        string(APPEND MCAL_OPT " -DHAS_INTERVAL_DIAG")
        string(APPEND SOURCES_C " ${INTERVAL_DIR}/interval_diag.c")
    endif()
    
    if(CLI STREQUAL Y)
        if(INTERVAL_COMMANDS STREQUAL Y)
            # message(STATUS "INTERVAL_COMMANDS = ${INTERVAL_COMMANDS}")
            string(APPEND MCAL_OPT " -DHAS_INTERVAL_COMMANDS")
            string(APPEND SOURCES_C " ${INTERVAL_DIR}/interval_commands.c")
        endif()
    endif()
    
endif()