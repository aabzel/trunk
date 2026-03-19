
message(STATUS "LOCKSTEP_GENERAL_MK_INC=${LOCKSTEP_GENERAL_MK_INC}")
if( NOT (Y STREQUAL LOCKSTEP_GENERAL_MK_INC))
    set(LOCKSTEP_GENERAL_MK_INC Y)
    message(STATUS "+ LOCKSTEP General")

    set(LOCKSTEP_GENERAL_DIR ${MCAL_COMMON_DIR}/lockstep)
    message(STATUS "LOCKSTEP_GENERAL_DIR=${LOCKSTEP_GENERAL_DIR}")

    add_compile_definitions(HAS_LOCKSTEP)
    target_compile_definitions(app PUBLIC HAS_LOCKSTEP)

    include_directories(${LOCKSTEP_GENERAL_DIR})
    target_include_directories(app PUBLIC ${LOCKSTEP_GENERAL_DIR})

    target_sources(app PRIVATE ${LOCKSTEP_GENERAL_DIR}/lockstep_general.c)
    target_sources(app PRIVATE ${LOCKSTEP_GENERAL_DIR}/lockstep_isr.c)

    if(DIAG STREQUAL Y)
        if(LOCKSTEP_DIAG STREQUAL Y)
            message(STATUS "+ LOCKSTEP diag")
            target_compile_definitions(app PUBLIC HAS_LOCKSTEP_DIAG)
            target_sources(app PRIVATE ${LOCKSTEP_GENERAL_DIR}/lockstep_diag.c)
        endif()
    endif()

    if(CLI STREQUAL Y)
        if(LOCKSTEP_COMMANDS STREQUAL Y)
            message(STATUS "+ LOCKSTEP commands")
            target_compile_definitions(app PUBLIC HAS_LOCKSTEP_COMMANDS)
            target_sources(app PRIVATE ${LOCKSTEP_GENERAL_DIR}/lockstep_commands.c)
        endif()
    endif()
endif()
