message(STATUS "DISTANCE_MK_INC=${DISTANCE_MK_INC}")
if(NOT (DISTANCE_MK_INC STREQUAL Y))
    set(DISTANCE_MK_INC Y)
    message(STATUS "+ DISTANCE")

    set(DISTANCE_DIR ${SENSITIVITY_DIR}/distance)
    message(STATUS "DISTANCE_DIR=${DISTANCE_DIR}")

    add_compile_definitions(HAS_DISTANCE)
    target_compile_definitions(app PUBLIC HAS_DISTANCE)
    target_compile_definitions(app PUBLIC HAS_DISTANCE_PROC)
    
    include_directories(${DISTANCE_DIR})
    target_include_directories(app PUBLIC ${DISTANCE_DIR})

    target_sources(app PRIVATE ${DISTANCE_DIR}/distance_drv.c)
    
    if(DIAG STREQUAL Y)
        if(DISTANCE_DIAG STREQUAL Y)
            message(STATUS "+ distance diag")
            target_compile_definitions(app PUBLIC HAS_DISTANCE_DIAG)
            target_sources(app PRIVATE ${DISTANCE_DIR}/distance_diag.c)
        endif()
    endif()

    if(CLI STREQUAL Y)
        if(DISTANCE_COMMANDS STREQUAL Y)
            message(STATUS "+ distance commands")
            target_compile_definitions(app PUBLIC HAS_DISTANCE_COMMANDS)
            target_sources(app PRIVATE ${DISTANCE_DIR}/distance_commands.c)
        endif()
    endif()
    
endif()