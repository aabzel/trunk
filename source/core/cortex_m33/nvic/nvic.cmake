
message(STATUS "NVIC_MK_INC=${NVIC_MK_INC}")
if( NOT (NVIC_MK_INC STREQUAL Y))
    set(NVIC_MK_INC Y)
    message(STATUS "Add NVIC")

    set(NVIC_DIR ${CORTEX_M33_DIR}/nvic)
    message(STATUS "NVIC_DIR=${NVIC_DIR}")

    add_compile_definitions(HAS_NVIC)
    target_compile_definitions(app PUBLIC HAS_NVIC)

    include_directories(${NVIC_DIR})
    target_include_directories(app PUBLIC ${NVIC_DIR})
    target_sources(app PRIVATE ${NVIC_DIR}/nvic_drv.c)

    if(DIAG STREQUAL Y)
        if(NVIC_DIAG STREQUAL Y)
            message(STATUS "Add NVIC_DIAG")
            target_sources(app PRIVATE ${NVIC_DIR}/nvic_diag.c)
        endif()
    endif()

    if(CLI STREQUAL Y)
        if(NVIC_COMMANDS STREQUAL Y)
            message(STATUS "Add NVIC_COMMANDS")
            target_compile_definitions(app PUBLIC HAS_NVIC_COMMANDS)
            target_sources(app PRIVATE ${NVIC_DIR}/nvic_commands.c)
        endif()
    endif()
endif()

