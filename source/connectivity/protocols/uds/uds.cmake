
message(STATUS "UDS_MK_INC=${UDS_MK_INC}")
if( NOT (UDS_MK_INC STREQUAL Y))
    set(UDS_MK_INC Y)
    message(STATUS "+ UDS")

    set(UDS_PROTOCOL_DIR ${PROTOCOLS_DIR}/uds)
    message(STATUS "UDS_PROTOCOL_DIR=${UDS_PROTOCOL_DIR}")

    target_compile_definitions(app PUBLIC HAS_UDS)

    include_directories(${UDS_PROTOCOL_DIR})
    target_include_directories(app PUBLIC ${UDS_PROTOCOL_DIR})

    #Source code
    target_sources(app PRIVATE ${UDS_PROTOCOL_DIR}/uds.c)
    target_sources(app PRIVATE ${UDS_PROTOCOL_DIR}/uds_parser.c)

    if (UDS_FLOW_CONTROL STREQUAL Y)
        target_compile_definitions(app PUBLIC HAS_UDS_FLOW_CONTROL)
    endif()

    if (TEST_FIRMWARE_COMMANDS STREQUAL Y)
        target_compile_definitions(app PUBLIC HAS_TEST_FIRMWARE_COMMANDS)
    endif()

    if (DIAG STREQUAL Y)
        if (UDS_DIAG STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_UDS_DIAG)
            target_sources(app PRIVATE ${UDS_PROTOCOL_DIR}/uds_diag.c)
        endif()
    endif()

    if (CLI STREQUAL Y)
        if (UDS_COMMANDS STREQUAL Y)
             message(STATUS "+ CLI native commands")
             target_compile_definitions(app PUBLIC HAS_UDS_COMMANDS)
             target_sources(app PRIVATE ${UDS_PROTOCOL_DIR}/uds_commands.c)
        endif()
    endif()
endif()




