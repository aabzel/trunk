message(STATUS "BUTTON_MK_INC=${BUTTON_MK_INC}")
if( NOT (BUTTON_MK_INC STREQUAL Y))
    set(BUTTON_MK_INC Y)

    message(STATUS "+ Button driver")

    set(BUTTON_DIR  ${SENSITIVITY_DIR}/button_fsm)

	#add_compile_definitions(HAS_BUTTON)
    target_compile_definitions(app PUBLIC HAS_BUTTON)
    target_compile_definitions(app PUBLIC HAS_BUTTON_PROC)
    
    target_include_directories(app PUBLIC ${BUTTON_DIR})
    target_sources(app PRIVATE ${BUTTON_DIR}/button_drv.c)

    if(DIAG STREQUAL Y)
        target_compile_definitions(app PUBLIC HAS_BUTTON_DIAG)
        target_sources(app PRIVATE ${BUTTON_DIR}/button_diag.c)
    endif()

    if(CLI STREQUAL Y)
        if(BUTTON_COMMANDS STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_BUTTON_COMMANDS)
            target_sources(app PRIVATE ${BUTTON_DIR}/button_commands.c)
        endif()
    endif()
endif()