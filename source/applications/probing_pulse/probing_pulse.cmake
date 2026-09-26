message(STATUS "PROBING_PULSE_MK_INC=${PROBING_PULSE_MK_INC}")
if( NOT (PROBING_PULSE_MK_INC  STREQUAL  Y))
    set(PROBING_PULSE_MK_INC Y)
    message(STATUS "+ PROBING_PULSE")

    set(PROBING_PULSE_DIR ${ROOT_DIR}/probing_pulse)
    message(STATUS "PROBING_PULSE_DIR=${PROBING_PULSE_DIR}")

    #message( SEND_ERROR "Check Compile")

    add_compile_definitions(HAS_PROBING_PULSE)
    target_compile_definitions(app PUBLIC HAS_PROBING_PULSE)
    target_compile_definitions(app PUBLIC HAS_PROBING_PULSE_PROC)

    target_include_directories(app PUBLIC ${PROBING_PULSE_DIR})
    target_sources(app PRIVATE ${PROBING_PULSE_DIR}/probing_pulse.c)

    if(DIAG  STREQUAL  Y)
        if(PROBING_PULSE_DIAG  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_PROBING_PULSE_DIAG)
            target_sources(app PRIVATE ${PROBING_PULSE_DIR}/probing_pulse_diag.c)
        endif()
    endif()

    if(CLI  STREQUAL  Y)
        if(PROBING_PULSE_COMMANDS  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_PROBING_PULSE_COMMANDS)
            target_sources(app PRIVATE ${PROBING_PULSE_DIR}/probing_pulse_commands.c)
        endif()
    endif()
endif()
