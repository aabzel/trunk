
message(STATUS "EXT_INT_GENERAL_MK_INC=${EXT_INT_GENERAL_MK_INC}")
if( NOT (Y STREQUAL EXT_INT_GENERAL_MK_INC))
    set(EXT_INT_GENERAL_MK_INC Y)
    message(STATUS "+ EXT_INT General")

    set(EXT_INT_GENERAL_DIR ${MCAL_COMMON_DIR}/ext_int)
    message(STATUS "EXT_INT_GENERAL_DIR=${EXT_INT_GENERAL_DIR}")

    add_compile_definitions(HAS_EXT_INT)
    target_compile_definitions(app PUBLIC HAS_EXT_INT)

    include_directories(${EXT_INT_GENERAL_DIR})
    target_include_directories(app PUBLIC ${EXT_INT_GENERAL_DIR})

    target_sources(app PRIVATE ${EXT_INT_GENERAL_DIR}/ext_int_general.c)
    target_sources(app PRIVATE ${EXT_INT_GENERAL_DIR}/ext_int_isr.c)

    if(DIAG STREQUAL Y)
        if(EXT_INT_DIAG STREQUAL Y)
            message(STATUS "+ EXT_INT diag")
            target_compile_definitions(app PUBLIC HAS_EXT_INT_DIAG)
            target_sources(app PRIVATE ${EXT_INT_GENERAL_DIR}/ext_int_diag.c)
        endif()
    endif()

    if(CLI STREQUAL Y)
        if(EXT_INT_COMMANDS STREQUAL Y)
            message(STATUS "+ EXT_INT commands")
            target_compile_definitions(app PUBLIC HAS_EXT_INT_COMMANDS)
            target_sources(app PRIVATE ${EXT_INT_GENERAL_DIR}/ext_int_commands.c)
        endif()
    endif()
endif()
