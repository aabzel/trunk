if(NOT SYSTICK_CUSTOM_MK_INC)
    set(SYSTICK_CUSTOM_MK_INC Y)

    set(CUSTOM_SYSTICK_DIR ${MCAL_CUSTOM_DIR}/systick)

    include_directories(${CUSTOM_SYSTICK_DIR})
    
    string(APPEND MCAL_OPT " -DHAS_SYSTICK_CUSTOM")
    string(APPEND MCAL_OPT " -DHAS_SYSTICK_INTERRUPT")

    string(APPEND SOURCES_C " ${CUSTOM_SYSTICK_DIR}/systick_custom.c")

    if(DIAG STREQUAL Y)
        string(APPEND SOURCES_C " ${CUSTOM_SYSTICK_DIR}/systick_custom_diag.c")
    endif()

    if(CLI STREQUAL Y)
        if(CUSTOM_SYSTICK_COMMANDS STREQUAL Y)
            string(APPEND MCAL_OPT " -DHAS_CUSTOM_SYSTICK_COMMANDS")
            string(APPEND SOURCES_C " ${CUSTOM_SYSTICK_DIR}/systick_custom_commands.c")
        endif()
    endif()

endif()