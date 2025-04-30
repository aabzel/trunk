message(STATUS "SCAN_MK_INC=${SCAN_MK_INC}")
if( NOT (SCAN_MK_INC  STREQUAL Y))
    set(SCAN_MK_INC Y)

    message(STATUS "+ Scan driver")

    set(SCAN_DIR  ${COMPUTING_DIR}/scan)

    add_compile_definitions(HAS_SCAN)
    target_compile_definitions(app PUBLIC HAS_SCAN)

    target_include_directories(app PUBLIC ${SCAN_DIR})
    target_sources(app PRIVATE ${SCAN_DIR}/scan.c)

    if(DIAG  STREQUAL Y)
        target_compile_definitions(app PUBLIC HAS_SCAN_DIAG)
        target_sources(app PRIVATE ${SCAN_DIR}/scan_diag.c)
    endif()

    if(CLI STREQUAL Y)
        if(SCAN_COMMANDS  STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_SCAN_COMMANDS)
            target_sources(app PRIVATE ${SCAN_DIR}/scan_commands.c)
        endif()
    endif()
endif()