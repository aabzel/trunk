if(NOT (SYSTICK_CORTEX_M_MK_INC STREQUAL Y))
    set(SYSTICK_CORTEX_M_MK_INC Y )

    set(SYSTICK_DIR "${CORE_DIR}/systick")
    include_directories( ${SYSTICK_DIR})

    set(SYSTICK_INTERRUPT Y)

    string(APPEND MCAL_OPT " -DHAS_SYSTICK")

    if(SYSTICK_INTERRUPT STREQUAL Y)
        string(APPEND MCAL_OPT " -DHAS_SYSTICK_INTERRUPT")
        string(APPEND SOURCES_C " ${SYSTICK_DIR}/systick_isr.c")
    endif()

    string(APPEND SOURCES_C " ${SYSTICK_DIR}/systick_general.c")

    if(DIAG STREQUAL Y)
        if(SYSTICK_DIAG STREQUAL Y)
            string(APPEND MCAL_OPT " -DHAS_SYSTICK_DIAG")
            string(APPEND SOURCES_C " ${SYSTICK_DIR}/systick_diag.c")
        endif()
    endif()

    if(CLI STREQUAL Y)
        if(SYSTICK_COMMANDS STREQUAL Y)
            string(APPEND MCAL_OPT " -DHAS_SYSTICK_COMMANDS")
            string(APPEND SOURCES_C " ${SYSTICK_DIR}/systick_commands.c")
        endif()
    endif()

endif()