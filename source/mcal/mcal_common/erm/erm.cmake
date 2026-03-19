
message(STATUS "ERM_GENERAL_MK_INC=${ERM_GENERAL_MK_INC}")
if( NOT (Y STREQUAL ERM_GENERAL_MK_INC))
    set(ERM_GENERAL_MK_INC Y)
    message(STATUS "+ ERM General")

    set(ERM_GENERAL_DIR ${MCAL_COMMON_DIR}/erm)
    message(STATUS "ERM_GENERAL_DIR=${ERM_GENERAL_DIR}")

    add_compile_definitions(HAS_ERM)
    target_compile_definitions(app PUBLIC HAS_ERM)

    include_directories(${ERM_GENERAL_DIR})
    target_include_directories(app PUBLIC ${ERM_GENERAL_DIR})

    target_sources(app PRIVATE ${ERM_GENERAL_DIR}/erm_general.c)
    target_sources(app PRIVATE ${ERM_GENERAL_DIR}/erm_isr.c)

    if(DIAG STREQUAL Y)
        if(ERM_DIAG STREQUAL Y)
            message(STATUS "+ ERM diag")
            target_compile_definitions(app PUBLIC HAS_ERM_DIAG)
            target_sources(app PRIVATE ${ERM_GENERAL_DIR}/erm_diag.c)
        endif()
    endif()

    if(CLI STREQUAL Y)
        if(ERM_COMMANDS STREQUAL Y)
            message(STATUS "+ ERM commands")
            target_compile_definitions(app PUBLIC HAS_ERM_COMMANDS)
            target_sources(app PRIVATE ${ERM_GENERAL_DIR}/erm_commands.c)
        endif()
    endif()
endif()
