
message(STATUS "MULTICORE_GENERAL_MK_INC=${MULTICORE_GENERAL_MK_INC}")
if( NOT (Y STREQUAL MULTICORE_GENERAL_MK_INC))
    set(MULTICORE_GENERAL_MK_INC Y)
    message(STATUS "+ MULTICORE General")

    set(MULTICORE_GENERAL_DIR ${MCAL_COMMON_DIR}/multicore)
    message(STATUS "MULTICORE_GENERAL_DIR=${MULTICORE_GENERAL_DIR}")

    add_compile_definitions(HAS_MULTICORE)
    target_compile_definitions(app PUBLIC HAS_MULTICORE)

    include_directories(${MULTICORE_GENERAL_DIR})
    target_include_directories(app PUBLIC ${MULTICORE_GENERAL_DIR})

    target_sources(app PRIVATE ${MULTICORE_GENERAL_DIR}/multicore_general.c)
    target_sources(app PRIVATE ${MULTICORE_GENERAL_DIR}/multicore_isr.c)

    if(DIAG STREQUAL Y)
        if(MULTICORE_DIAG STREQUAL Y)
            message(STATUS "+ MULTICORE diag")
            target_compile_definitions(app PUBLIC HAS_MULTICORE_DIAG)
            target_sources(app PRIVATE ${MULTICORE_GENERAL_DIR}/multicore_diag.c)
        endif()
    endif()

    if(CLI STREQUAL Y)
        if(MULTICORE_COMMANDS STREQUAL Y)
            message(STATUS "+ MULTICORE commands")
            target_compile_definitions(app PUBLIC HAS_MULTICORE_COMMANDS)
            target_sources(app PRIVATE ${MULTICORE_GENERAL_DIR}/multicore_commands.c)
        endif()
    endif()
endif()
