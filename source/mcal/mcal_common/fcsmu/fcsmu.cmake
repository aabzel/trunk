
message(STATUS "FCSMU_GENERAL_MK_INC=${FCSMU_GENERAL_MK_INC}")
if( NOT (Y STREQUAL FCSMU_GENERAL_MK_INC))
    set(FCSMU_GENERAL_MK_INC Y)
    message(STATUS "+ FCSMU General")

    set(FCSMU_GENERAL_DIR ${MCAL_COMMON_DIR}/fcsmu)
    message(STATUS "FCSMU_GENERAL_DIR=${FCSMU_GENERAL_DIR}")

    add_compile_definitions(HAS_FCSMU)
    target_compile_definitions(app PUBLIC HAS_FCSMU)

    include_directories(${FCSMU_GENERAL_DIR})
    target_include_directories(app PUBLIC ${FCSMU_GENERAL_DIR})

    target_sources(app PRIVATE ${FCSMU_GENERAL_DIR}/fcsmu_general.c)
    target_sources(app PRIVATE ${FCSMU_GENERAL_DIR}/fcsmu_isr.c)

    if(DIAG STREQUAL Y)
        if(FCSMU_DIAG STREQUAL Y)
            message(STATUS "+ FCSMU diag")
            target_compile_definitions(app PUBLIC HAS_FCSMU_DIAG)
            target_sources(app PRIVATE ${FCSMU_GENERAL_DIR}/fcsmu_diag.c)
        endif()
    endif()

    if(CLI STREQUAL Y)
        if(FCSMU_COMMANDS STREQUAL Y)
            message(STATUS "+ FCSMU commands")
            target_compile_definitions(app PUBLIC HAS_FCSMU_COMMANDS)
            target_sources(app PRIVATE ${FCSMU_GENERAL_DIR}/fcsmu_commands.c)
        endif()
    endif()
endif()
