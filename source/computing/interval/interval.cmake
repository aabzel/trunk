message(STATUS "INTERVAL_MK_INC=${INTERVAL_MK_INC}")
if( NOT (INTERVAL_MK_INC STREQUAL Y))
    set(INTERVAL_MK_INC Y)

    message(STATUS "+ INTERVAL")

    set(INTERVAL_DIR ${COMPUTING_DIR}/interval)
    message(STATUS "INTERVAL_DIR=${INTERVAL_DIR}")

    target_compile_definitions(app PUBLIC HAS_INTERVAL)
    target_sources(app PRIVATE ${INTERVAL_DIR}/interval.c)

    if(DIAG STREQUAL Y)
        if(INTERVAL_DIAG STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_INTERVAL_DIAG)
            target_sources(app PRIVATE ${INTERVAL_DIR}/interval_diag.c)
        endif()
    endif()

    #include_directories(${INTERVAL_DIR})
    target_include_directories(app PUBLIC ${INTERVAL_DIR})
endif()

