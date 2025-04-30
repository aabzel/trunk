
message(STATUS "ISO_TP_MK_INC=${ISO_TP_MK_INC}")
if( NOT (ISO_TP_MK_INC STREQUAL Y))
    set(ISO_TP_MK_INC Y)
    message(STATUS "+ ISO_TP")

    set(ISO_TP_PROTOCOL_DIR ${PROTOCOLS_DIR}/iso_tp)
    message(STATUS "ISO_TP_PROTOCOL_DIR=${ISO_TP_PROTOCOL_DIR}")

    target_compile_definitions(app PUBLIC HAS_ISO_TP)

    include_directories(${ISO_TP_PROTOCOL_DIR})
    target_include_directories(app PUBLIC ${ISO_TP_PROTOCOL_DIR})

    #Source code
    target_sources(app PRIVATE ${ISO_TP_PROTOCOL_DIR}/iso_tp.c)
    target_sources(app PRIVATE ${ISO_TP_PROTOCOL_DIR}/iso_tp_parser.c)

    if (ISO_TP_FLOW_CONTROL STREQUAL Y)
        target_compile_definitions(app PUBLIC HAS_ISO_TP_FLOW_CONTROL)
    endif()

    if (TEST_FIRMWARE_COMMANDS STREQUAL Y)
        target_compile_definitions(app PUBLIC HAS_TEST_FIRMWARE_COMMANDS)
    endif()

    if (DIAG STREQUAL Y)
        if (ISO_TP_DIAG STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_ISO_TP_DIAG)
            target_sources(app PRIVATE ${ISO_TP_PROTOCOL_DIR}/iso_tp_diag.c)
        endif()
    endif()

    if (CLI STREQUAL Y)
        if (ISO_TP_COMMANDS STREQUAL Y)
             message(STATUS "+ CLI native commands")
             target_compile_definitions(app PUBLIC HAS_ISO_TP_COMMANDS)
             target_sources(app PRIVATE ${ISO_TP_PROTOCOL_DIR}/iso_tp_commands.c)
        endif()
    endif()
endif()




