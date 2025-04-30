message(STATUS "CORE_CMK_INC=${CORE_CMK_INC}")
if( NOT (CORE_CMK_INC STREQUAL Y))
    set(CORE_CMK_INC Y)
    message(STATUS "+ Core")

    set(CORE_DIR ${WORKSPACE_LOC}/core)
    message(STATUS "CORE_DIR=${CORE_DIR}")
    add_compile_definitions(HAS_CORE)

    target_include_directories(app PUBLIC ${CORE_DIR})

    target_sources(app PRIVATE ${CORE_DIR}/core_driver.c)

    if(CLI STREQUAL Y)
        if(CORE_COMMANDS STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_CORE_COMMANDS)
            target_sources(app PRIVATE ${CORE_DIR}/core_commsnds.c)
        endif()
    endif()

    if(CORTEX_M33 STREQUAL Y)
        message(STATUS "+ CORTEX_M33")
        include(${CORE_DIR}/cortex_m33/cortex_m33.cmake)
    endif()

    if(CORTEX_M4 STREQUAL Y)
        message(STATUS "+ CORTEX_M4")
        include(${CORE_DIR}/cortex_m4/cortex_m4.cmake)
    endif()
endif()
