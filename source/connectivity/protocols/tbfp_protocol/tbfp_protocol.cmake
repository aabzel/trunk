
message(STATUS "TBFP_MK_INC=${TBFP_MK_INC}")
if( NOT (TBFP_MK_INC STREQUAL Y))
    set(TBFP_MK_INC Y)
    message(STATUS "+ TBFP")

    set(TBFP_PROTOCOL_DIR ${PROTOCOLS_DIR}/tbfp_protocol)
    message(STATUS "TBFP_PROTOCOL_DIR=${TBFP_PROTOCOL_DIR}")

    target_compile_definitions(app PUBLIC HAS_TBFP)

    include_directories(${TBFP_PROTOCOL_DIR})
    target_include_directories(app PUBLIC ${TBFP_PROTOCOL_DIR})

    #Source code
    target_sources(app PRIVATE ${TBFP_PROTOCOL_DIR}/tbfp_protocol.c)
    target_sources(app PRIVATE ${TBFP_PROTOCOL_DIR}/tbfp_protocol_parser.c)

    if (TBFP_FLOW_CONTROL STREQUAL Y)
        target_compile_definitions(app PUBLIC HAS_TBFP_FLOW_CONTROL)
    endif()

    if (TEST_FIRMWARE_COMMANDS STREQUAL Y)
        target_compile_definitions(app PUBLIC HAS_TEST_FIRMWARE_COMMANDS)
    endif()

    if (TBFP_RETRANSMIT STREQUAL Y)
        target_compile_definitions(app PUBLIC HAS_TBFP_RETRANSMIT)
        if (TBFP_DIAG STREQUAL Y)
            target_sources(app PRIVATE ${TBFP_PROTOCOL_DIR}/tbfp_retx_diag.c)
        endif()
    endif()

    if (DIAG STREQUAL Y)
        if (TBFP_DIAG STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_TBFP_DIAG)
            target_sources(app PRIVATE ${TBFP_PROTOCOL_DIR}/tbfp_diag.c)
        endif()
    endif()

    if (CLI STREQUAL Y)
        if (TBFP_COMMANDS STREQUAL Y)
             message(STATUS "+ CLI native commands")
             target_compile_definitions(app PUBLIC HAS_TBFP_COMMANDS)
             target_sources(app PRIVATE ${TBFP_PROTOCOL_DIR}/tbfp_commands.c)
        endif()
    endif()
endif()




